// *******************************************************************
// * load-control-event-table.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// clusters specific header
#include "../../util/common.h"
#include "load-control-event-table.h"

static void emAfCallEventAction(EmberAfLoadControlEvent *event,
                                int8u eventStatus,
                                int8u sequenceNumber);

// This assumes that the Option Flag Enum uses only two bits
PGM int8u controlValueToStatusEnum[] = {
  EMBER_ZCL_AMI_EVENT_STATUS_EVENT_COMPLETED_NO_USER_PARTICIPATION_PREVIOUS_OPT_OUT, // ! EVENT_OPT_FLAG_PARTIAL
                                                                           // && ! EVENT_OPT_FLAG_OPT_IN
  EMBER_ZCL_AMI_EVENT_STATUS_EVENT_COMPLETED,                                        // ! EVENT_OPT_FLAG_PARTIAL
                                                                  // && EVENT_OPT_FLAG_OPT_IN
  EMBER_ZCL_AMI_EVENT_STATUS_EVENT_PARTIALLY_COMPLETED_WITH_USER_OPT_OUT,   // EVENT_OPT_FLAG_PARTIAL
                                                                  // && ! EVENT_OPT_FLAG_OPT_IN
  EMBER_ZCL_AMI_EVENT_STATUS_EVENT_PARTIALLY_COMPLETED_DUE_TO_USER_OPT_IN   // EVENT_OPT_FLAG_PARTIAL
                                                                  // && EVENT_OPT_FLAG_OPT_IN
};

typedef struct 
{
  EmberAfLoadControlEvent event;
  int8u entryStatus;
  int8u sequenceNumber;
} LoadControlEventTableEntry;

static LoadControlEventTableEntry loadControlEventTable[EMBER_AF_PLUGIN_DRLC_EVENT_TABLE_SIZE];

void afLoadControlEventTableInit(int8u endpoint)
{
  MEMSET(loadControlEventTable, 0, 
         sizeof(LoadControlEventTableEntry) * EMBER_AF_PLUGIN_DRLC_EVENT_TABLE_SIZE);
}

static boolean overlapFound(EmberAfLoadControlEvent *newEvent,
                            EmberAfLoadControlEvent *existingEvent) {
  if (newEvent->startTime < (existingEvent->startTime + ((int32u)existingEvent->duration * 60)) &&
      existingEvent->startTime < (newEvent->startTime + ((int32u)newEvent->duration * 60)))
    return TRUE;
  else
    return FALSE;
}

static boolean entryIsScheduledOrStarted(int8u entryStatus) {
  if (entryStatus == ENTRY_SCHEDULED ||
      entryStatus == ENTRY_STARTED)
    return TRUE;
  return FALSE;
}

static void initEventData(EmberAfLoadControlEvent *event) {
  MEMSET(event, 0, sizeof(EmberAfLoadControlEvent));
}

/**
 * Clears the table of any entries which pertain to a
 * specific eventId.
 **/
static void voidAllEntriesWithEventId(int32u eventId) {
  int8u i;
  LoadControlEventTableEntry *e;
  for (i=0;i<EMBER_AF_PLUGIN_DRLC_EVENT_TABLE_SIZE;i++)
  {
    e = &loadControlEventTable[i];
    if (e->event.eventId == eventId)
    {
      e->entryStatus = ENTRY_VOID;
    }
  }
}

/**
 * The tick function simply checks entries in the table
 * and sends informational messages about event start
 * and event complete.
 */
void emAfLoadControlEventTableTick(int8u endpoint) {
  int32u ct = emberAfGetCurrentTime();
  int8u i;
  LoadControlEventTableEntry *e;

  // Check for events that need to be run
  for( i=0; i<EMBER_AF_PLUGIN_DRLC_EVENT_TABLE_SIZE; i++ ) {
    e = &loadControlEventTable[i];
    if (e->entryStatus == ENTRY_SCHEDULED)
    {
      if (e->event.startTime+e->event.startRand <= ct)
      {
        // Bug: 13546
        // When the event starts always send a Report Event status message.
        // If user opted-out, then send that status instead of event started.
        emAfCallEventAction(&(e->event), 
                            ((e->event.optionControl & EVENT_OPT_FLAG_OPT_IN)
                             ? EMBER_ZCL_AMI_EVENT_STATUS_EVENT_STARTED
                             : EMBER_ZCL_AMI_EVENT_STATUS_USER_HAS_CHOOSE_TO_OPT_OUT),
                            e->sequenceNumber);
        e->entryStatus = ENTRY_STARTED;
        return;
      }
    } else if (e->entryStatus == ENTRY_STARTED) {
      if ((e->event.startTime 
           + ((int32u)e->event.duration * 60) 
           + e->event.endRand) <= ct) {
        emAfCallEventAction(&(e->event), 
                            controlValueToStatusEnum[e->event.optionControl],
                            e->sequenceNumber);
        voidAllEntriesWithEventId(e->event.eventId);
        return;
      }
    } else if (e->entryStatus == ENTRY_IS_SUPERSEDED_EVENT) {
      if (e->event.startTime <= ct) {
        emAfCallEventAction(&(e->event), 
                            EMBER_ZCL_AMI_EVENT_STATUS_THE_EVENT_HAS_BEEN_SUPERSEDED,
                            e->sequenceNumber);
        voidAllEntriesWithEventId(e->event.eventId);
        return;
      }
    } else if (e->entryStatus == ENTRY_IS_CANCELLED_EVENT)
    {
      if (e->event.startTime <= ct) {
        emAfCallEventAction(&(e->event), 
                            EMBER_ZCL_AMI_EVENT_STATUS_THE_EVENT_HAS_BEEN_CANCELED, 
                            e->sequenceNumber);
        voidAllEntriesWithEventId(e->event.eventId);
        return;
      }
    }
  }
}

/** 
 * This function is used to schedule events in the
 * load control event table.
 */
void emAfScheduleLoadControlEvent( EmberAfLoadControlEvent *newEvent) {
  int8u i;
  int32u ct;
  LoadControlEventTableEntry *e;
  ct = emberAfGetCurrentTime();

  //validate criticality level 
  if (newEvent->criticalityLevel >= 0x10) {
    emAfCallEventAction(newEvent, 
                        EMBER_ZCL_AMI_EVENT_STATUS_LOAD_CONTROL_EVENT_COMMAND_REJECTED, 
                        emberAfIncomingZclSequenceNumber);
    return;
  }
  //validate starttime + duration
  if (newEvent->startTime == 0xffffffffUL
      || newEvent->duration > 0x5a0) {
    emAfCallEventAction(newEvent, 
                        EMBER_ZCL_AMI_EVENT_STATUS_LOAD_CONTROL_EVENT_COMMAND_REJECTED, 
                        emberAfIncomingZclSequenceNumber);
    return;
  }

  //validate expiration
  if (ct > (newEvent->startTime + ((int32u)newEvent->duration * 60)))
  {
    emAfCallEventAction(newEvent, 
                        EMBER_ZCL_AMI_EVENT_STATUS_REJECTED_EVENT_EXPIRED, 
                        emberAfIncomingZclSequenceNumber);
    return;
  }

  //validate event id
  for (i = 0; i < EMBER_AF_PLUGIN_DRLC_EVENT_TABLE_SIZE; i++) {
    e = &loadControlEventTable[i];
    if (entryIsScheduledOrStarted(e->entryStatus) &&
        (e->event.eventId == newEvent->eventId))
    {
      // Bug: 13548.  Rather than send a Report Event status message,
      // to duplicate event IDs, we send a default response.
      //      emAfCallEventAction(newEvent, 
      //                          EMBER_ZCL_AMI_EVENT_STATUS_LOAD_CONTROL_EVENT_COMMAND_REJECTED, 
      //                          emberAfIncomingZclSequenceNumber);
      emberAfSendDefaultResponse(emberAfCurrentCommand(),
                                 EMBER_ZCL_STATUS_DUPLICATE_EXISTS);
      return;
    }
  }

  //locate empty table entry
  for (i = 0; i < EMBER_AF_PLUGIN_DRLC_EVENT_TABLE_SIZE; i++) {
    e = &loadControlEventTable[i];
    if (e->entryStatus == ENTRY_VOID) {
      MEMCOPY(&(e->event), newEvent, sizeof(EmberAfLoadControlEvent));

      //check for supercession
      for (i=0;i<EMBER_AF_PLUGIN_DRLC_EVENT_TABLE_SIZE;i++) {
        LoadControlEventTableEntry *currentEntry = &loadControlEventTable[i];
        if (currentEntry->entryStatus == ENTRY_SCHEDULED ||
            currentEntry->entryStatus == ENTRY_STARTED) 
        {
          if (overlapFound(newEvent, &(currentEntry->event))) 
          {
            if (currentEntry->entryStatus != ENTRY_STARTED)
              currentEntry->event.startTime = ct;
            else
              currentEntry->event.startTime = (newEvent->startTime + newEvent->startRand - 1);
            currentEntry->entryStatus = ENTRY_IS_SUPERSEDED_EVENT;
          }
        }
      }
      e->entryStatus = ENTRY_SCHEDULED;
      e->sequenceNumber = emberAfIncomingZclSequenceNumber;
      emAfCallEventAction(newEvent, 
                          EMBER_ZCL_AMI_EVENT_STATUS_LOAD_CONTROL_EVENT_COMMAND_RX, 
                          emberAfIncomingZclSequenceNumber);
      return;
    }
  }

  // If we get here we have failed to schedule the event
  // because we probably don't have any room in the table and 
  // must reject scheduling. We reject but others have chosen to bump the earliest event
  // There is an ongoing discussion on this issue will be discussed for possible CCB.
  emAfCallEventAction(newEvent, 
                      EMBER_ZCL_AMI_EVENT_STATUS_LOAD_CONTROL_EVENT_COMMAND_REJECTED, 
                      emberAfIncomingZclSequenceNumber);
  return;
}

void emAfLoadControlEventOptInOrOut(int32u eventId, boolean optIn) {
  int8u i;
  LoadControlEventTableEntry *e;
  for (i=0;i<EMBER_AF_PLUGIN_DRLC_EVENT_TABLE_SIZE;i++)
  {
    e = &loadControlEventTable[i];
    if (entryIsScheduledOrStarted(e->entryStatus) &&
        e->event.eventId == eventId)
    {
      // used to find out if we have opted in our out of a running event
      boolean previousEventOption = (e->event.optionControl & EVENT_OPT_FLAG_OPT_IN);
      
      // set the event opt in flag
      e->event.optionControl = 
        (optIn 
         ? (e->event.optionControl | EVENT_OPT_FLAG_OPT_IN) 
         : (e->event.optionControl & ~EVENT_OPT_FLAG_OPT_IN));

      // if we have opted in or out of a running event we need to set the
      // partial flag.
      if ((previousEventOption != optIn) &&
           e->entryStatus == ENTRY_STARTED)
      {
        e->event.optionControl |= EVENT_OPT_FLAG_PARTIAL;
      }

      // Bug: 13546
      // SE 1.0 and 1.1 dictate that if the event has not yet started,
      // and the user opts-out then don't send a status message.
      // Effectively the event is not changing so don't bother
      // notifying the ESI.  When the event would normally start, 
      // the opt-out takes effect and that is when we send the opt-out
      // message.
      if (!(e->event.optionControl & ~EVENT_OPT_FLAG_OPT_IN
            && e->entryStatus == ENTRY_SCHEDULED)) {

        emAfCallEventAction(
                            &(e->event), 
                            (optIn 
                             ? EMBER_ZCL_AMI_EVENT_STATUS_USER_HAS_CHOOSE_TO_OPT_IN 
                             : EMBER_ZCL_AMI_EVENT_STATUS_USER_HAS_CHOOSE_TO_OPT_OUT), 
                            e->sequenceNumber);
      }
      return;
    }
  }
}

void emAfCancelLoadControlEvent(int32u eventId, int8u cancelControl, int32u effectiveTime) {
  int8u i;
  LoadControlEventTableEntry *e;
  EmberAfLoadControlEvent undefEvent;
  int32u cancelTime = 0;

  for (i=0;i<EMBER_AF_PLUGIN_DRLC_EVENT_TABLE_SIZE; i++)
  {
    e = &loadControlEventTable[i];
    if (e->event.eventId == eventId &&
        e->entryStatus != ENTRY_VOID) {

      // Found the event, validate effective time
      if ((effectiveTime == 0xffffffffUL) ||
          (effectiveTime > (e->event.startTime + 
                            (((int32u) e->event.duration) * 60))))
      {
        emAfCallEventAction(&(e->event), 
          EMBER_ZCL_AMI_EVENT_STATUS_REJECTED_INVALID_CANCEL_COMMAND_INVALID_EFFECTIVE_TIME, 
          emberAfIncomingZclSequenceNumber);
        return;
      }

      // We're good, Run the cancel
      if (cancelControl & CANCEL_WITH_RANDOMIZATION)
      {
        if (effectiveTime == 0) {
          cancelTime = emberAfGetCurrentTime();
        }
        cancelTime += e->event.endRand;
      } else {
        cancelTime = effectiveTime;
      }
      e->entryStatus = ENTRY_IS_CANCELLED_EVENT; //will generate message on next tick
      e->event.startTime = cancelTime;
      return;
    }
  }

  // If we get here, we have failed to find the event
  // requested to cancel, send a fail message.
  initEventData(&undefEvent);
  emberLookupEui64ByNodeId(emberAfCurrentCommand()->source, undefEvent.source);
  undefEvent.sourceEndpoint = emberAfCurrentCommand()->apsFrame->destinationEndpoint;
  undefEvent.destinationEndpoint = emberAfCurrentCommand()->apsFrame->sourceEndpoint;
  undefEvent.eventId = eventId;
  emAfCallEventAction(&undefEvent, 
                      EMBER_ZCL_AMI_EVENT_STATUS_REJECTED_INVALID_CANCEL_UNDEFINED_EVENT, 
                      emberAfIncomingZclSequenceNumber);
}

boolean emAfCancelAllLoadControlEvents(int8u cancelControl) 
{
  int8u i;
  LoadControlEventTableEntry *e;
  boolean generatedResponse = FALSE;
  for (i=0;i<EMBER_AF_PLUGIN_DRLC_EVENT_TABLE_SIZE;i++)
  {
    e = &loadControlEventTable[i];
    if (e->entryStatus != ENTRY_VOID) {
      emAfCancelLoadControlEvent(e->event.eventId, cancelControl, 0);
      generatedResponse = TRUE;
    }
  }
  return generatedResponse;
}

static void emAfCallEventAction(EmberAfLoadControlEvent *event,
                                int8u eventStatus,
                                int8u sequenceNumber)
{
  emberAfEventAction(event, eventStatus, sequenceNumber);
}

void emAfNoteSignatureFailure(void)
{
  emberAfDemandResponseLoadControlClusterPrintln("Failed to append signature to message.");
}

void emAfLoadControlEventTablePrint(void) 
{
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER)
  LoadControlEventTableEntry *e;  
  int8u i;
 
  emberAfDemandResponseLoadControlClusterPrintln("ind  st id       sta      dur  ec oc"); 
  emberAfDemandResponseLoadControlClusterFlush();
 
  for(i = 0; i < EMBER_AF_PLUGIN_DRLC_EVENT_TABLE_SIZE; i++) {
    e = &loadControlEventTable[i];
    emberAfDemandResponseLoadControlClusterPrintln("[%x] %x %4x %4x %2x %x %x", 
                                              i, 
                                              e->entryStatus, 
                                              e->event.eventId, 
                                              e->event.startTime, 
                                              e->event.duration, 
                                              e->event.eventControl, 
                                              e->event.optionControl); 
    emberAfDemandResponseLoadControlClusterFlush();
  }
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER)
}
