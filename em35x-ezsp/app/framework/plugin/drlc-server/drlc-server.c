// *******************************************************************
// * drlc-server.c
// *
// * For more information on the usage of this plugin see drlc-server.h
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "../../util/common.h"
#include "drlc-server.h"

static EmberAfLoadControlEvent scheduledLoadControlEventTable[EMBER_AF_PLUGIN_DRLC_SERVER_SCHEDULED_EVENT_TABLE_SIZE];

void emberAfDemandResponseLoadControlClusterServerInitCallback(int8u endpoint)
{
  emAfClearScheduledLoadControlEvents(); //clear all events at init
}

boolean emberAfDemandResponseLoadControlClusterGetScheduledEventsCallback(int32u startTime,
                                                                          int8u numberOfEvents)
{
  int8u i, sent = 0;
  EmberApsFrame *cmdApsFrame = emberAfGetCommandApsFrame();
  EmberAfClusterCommand *currentCommand = emberAfCurrentCommand();

  // Go through our table and send out the scheduled events
  for (i = 0; i < EMBER_AF_PLUGIN_DRLC_SERVER_SCHEDULED_EVENT_TABLE_SIZE; i++) {
    EmberAfLoadControlEvent *event = &scheduledLoadControlEventTable[i];
    
    // check how many we have sent, if they have a positive number of events
    // they want returned and we have hit it we should exit.
    if (numberOfEvents != 0 && sent >= numberOfEvents) {
      break;
    }

    // If the is inactive or the event's start time is 
    // positive and before the requested start time we ignore it.
    if (event->source[0] == 0xFF
        || (event->startTime != 0 && event->startTime < startTime)) {
      continue;
    }

    // send the event
    emberAfFillCommandDemandResponseLoadControlClusterLoadControlEvent(event->eventId,
                                                                       event->deviceClass,
                                                                       event->utilityEnrollmentGroup,
                                                                       event->startTime,
                                                                       event->duration,
                                                                       event->criticalityLevel,
                                                                       event->coolingTempOffset,
                                                                       event->heatingTempOffset,
                                                                       event->coolingTempSetPoint,
                                                                       event->heatingTempSetPoint,
                                                                       event->avgLoadPercentage,
                                                                       event->dutyCycle,
                                                                       event->eventControl);
    cmdApsFrame->sourceEndpoint = currentCommand->apsFrame->destinationEndpoint;
    cmdApsFrame->destinationEndpoint = currentCommand->apsFrame->sourceEndpoint;
    cmdApsFrame->options |= EMBER_APS_OPTION_SOURCE_EUI64;
    emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, currentCommand->source);
    sent++;  //record that we sent it. and continue
  }

  // Bug 13547:
  //   Only send a Default response if there were no events returned.
  //   The LCE messages are the "next" messages in the sequence so no
  //   default response is needed for that successful case.
  if (sent == 0) {
    emberAfSendDefaultResponse(emberAfCurrentCommand(), 
                               EMBER_ZCL_STATUS_NOT_FOUND);
  }

  return TRUE;;
}


boolean emberAfDemandResponseLoadControlClusterReportEventStatusCallback(int32u issuerEventId, 
                                                                         int8u eventStatus, 
                                                                         int32u eventStatusTime, 
                                                                         int8u criticalityLevelApplied, 
                                                                         int16s coolingTemperatureSetPointApplied, 
                                                                         int16s heatingTemperatureSetPointApplied, 
                                                                         int8s averageLoadAdjustmentPercentageApplied, 
                                                                         int8u dutyCycleApplied, 
                                                                         int8u eventControl, 
                                                                         int8u signatureType, 
                                                                         int8u* signature)
{
  emberAfDemandResponseLoadControlClusterPrintln("= RX Event Status =");
  emberAfDemandResponseLoadControlClusterPrintln("  eid: %4x", issuerEventId);
  emberAfDemandResponseLoadControlClusterPrintln("   es: %x", eventStatus);
  emberAfDemandResponseLoadControlClusterPrintln("  est: T%4x", eventStatusTime);
  emberAfDemandResponseLoadControlClusterFlush();
  emberAfDemandResponseLoadControlClusterPrintln("  cla: %x", criticalityLevelApplied);
  emberAfDemandResponseLoadControlClusterFlush();
  emberAfDemandResponseLoadControlClusterPrintln("ctspa: %2x (%d)", 
                                                 coolingTemperatureSetPointApplied, 
                                                 coolingTemperatureSetPointApplied);
  emberAfDemandResponseLoadControlClusterPrintln("htspa: %2x (%d)", 
                                                 heatingTemperatureSetPointApplied,
                                                 heatingTemperatureSetPointApplied);
  emberAfDemandResponseLoadControlClusterFlush();
  emberAfDemandResponseLoadControlClusterPrintln("  avg: %x", 
                                                 averageLoadAdjustmentPercentageApplied);
  emberAfDemandResponseLoadControlClusterPrintln("   dc: %x", dutyCycleApplied);
  emberAfDemandResponseLoadControlClusterPrintln("   ec: %x", eventControl);
  emberAfDemandResponseLoadControlClusterFlush();

  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}


void emAfClearScheduledLoadControlEvents(void) {
  int8u i;
  for (i = 0; i < EMBER_AF_PLUGIN_DRLC_SERVER_SCHEDULED_EVENT_TABLE_SIZE; i++) {
    EmberAfLoadControlEvent *event = &scheduledLoadControlEventTable[i];
    event->source[0] = 0xFF; // event inactive if first byte of source is 0xFF
  }
}


EmberAfLoadControlEvent *emAfGetScheduledLoadControlEvent(int8u index) {
  if (index > EMBER_AF_PLUGIN_DRLC_SERVER_SCHEDULED_EVENT_TABLE_SIZE) {
    emberAfDemandResponseLoadControlClusterPrintln("slce index out of range");
    return NULL;
  }
  return &scheduledLoadControlEventTable[index];
}

void emAfPluginDrlcServerPrintInfo(void)
{
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER)
  int8u i;
  for (i = 0; i < EMBER_AF_PLUGIN_DRLC_SERVER_SCHEDULED_EVENT_TABLE_SIZE; i++) {
    EmberAfLoadControlEvent *lce = &scheduledLoadControlEventTable[i];
    emberAfDemandResponseLoadControlClusterFlush();
    emberAfDemandResponseLoadControlClusterPrintln("= LCE %d =", i);
    emberAfDemandResponseLoadControlClusterPrintln("eid: 0x%4x", lce->eventId);
    emberAfDemandResponseLoadControlClusterPrintln("src: 0x%x",  lce->source[0]);
    emberAfDemandResponseLoadControlClusterPrintln("sep: 0x%x",  lce->sourceEndpoint);
    emberAfDemandResponseLoadControlClusterFlush();
    emberAfDemandResponseLoadControlClusterPrintln("dep: 0x%x",  lce->destinationEndpoint);
    emberAfDemandResponseLoadControlClusterPrintln("dev: 0x%2x", lce->deviceClass);
    emberAfDemandResponseLoadControlClusterPrintln("ueg: 0x%x",  lce->utilityEnrollmentGroup);
    emberAfDemandResponseLoadControlClusterPrintln(" st: 0x%4x", lce->startTime);
    emberAfDemandResponseLoadControlClusterFlush();
    emberAfDemandResponseLoadControlClusterPrintln("dur: 0x%2x", lce->duration);
    emberAfDemandResponseLoadControlClusterPrintln(" cl: 0x%x",  lce->criticalityLevel);
    emberAfDemandResponseLoadControlClusterPrintln("cto: 0x%x",  lce->coolingTempOffset);
    emberAfDemandResponseLoadControlClusterPrintln("hto: 0x%x",  lce->heatingTempOffset);
    emberAfDemandResponseLoadControlClusterFlush();
    emberAfDemandResponseLoadControlClusterPrintln("cts: 0x%2x", lce->coolingTempSetPoint);
    emberAfDemandResponseLoadControlClusterPrintln("hts: 0x%2x", lce->heatingTempSetPoint);
    emberAfDemandResponseLoadControlClusterPrintln("alp: 0x%x",  lce->avgLoadPercentage);
    emberAfDemandResponseLoadControlClusterPrintln(" dc: 0x%x",  lce->dutyCycle);
    emberAfDemandResponseLoadControlClusterFlush();
    emberAfDemandResponseLoadControlClusterPrintln(" ev: 0x%x",  lce->eventControl);
    emberAfDemandResponseLoadControlClusterPrintln(" sr: 0x%2x", lce->startRand);
    emberAfDemandResponseLoadControlClusterPrintln(" er: 0x%2x", lce->endRand);
    emberAfDemandResponseLoadControlClusterPrintln(" oc: 0x%x",  lce->optionControl);
    emberAfDemandResponseLoadControlClusterFlush();
  }
  emberAfDemandResponseLoadControlClusterPrintln("Table size: %d", 
                                                 EMBER_AF_PLUGIN_DRLC_SERVER_SCHEDULED_EVENT_TABLE_SIZE);
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER)
}
