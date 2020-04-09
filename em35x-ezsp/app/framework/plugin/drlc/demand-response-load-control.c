// *******************************************************************
// * demand-response-load-control.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "../../util/common.h"
#include "demand-response-load-control.h"
#include "gen/drlc-callback.h"

#ifdef ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT

//------------------------------------------------------------------------------
// Globals

#define SIGNATURE_TYPE_NONE  0x00
#define SIGNATURE_TYPE_DUMMY 0xFF  // non-standard by Zigbee

#if defined(EMBER_AF_PLUGIN_DRLC_APPEND_DUMMY_SIGNATURE)
  #define SIGNATURE_TYPE (SIGNATURE_TYPE_DUMMY)
#else
  #define SIGNATURE_TYPE (SIGNATURE_TYPE_NONE)
#endif

//------------------------------------------------------------------------------

/**
 * Checks to see if the passed UEG OR deviceClass match those stored in
 * the cluster attributes.
 *
 * Returns true if either the device class or the UEG match. This
 * is the assumed interpretation of the spec.. 
 **/
static boolean afMatchUegOrDeviceClass(int8u endpoint,
                                       int8u utilityEnrollmentGroup, 
                                       int16u deviceClass) 
{
  int8u       ueg      = 0;
  int16u      dc;
  int8u       dcArray[2];
  int8u       dataType = 0;
  int8u       status;
  
  status = 
    emberAfReadAttribute(endpoint, 
                         ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID, 
                         ZCL_UTILITY_ENROLLMENT_GROUP_ATTRIBUTE_ID,
                         CLUSTER_MASK_CLIENT,
                         (int8u*)&ueg,
                         1,
                         &dataType);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    return FALSE;
  }

  dataType = 0;
  status = 
    emberAfReadAttribute(endpoint, 
                         ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID, 
                         ZCL_DEVICE_CLASS_VALUE_ATTRIBUTE_ID,
                         CLUSTER_MASK_CLIENT,
                         (int8u*)dcArray,
                         2,
                         &dataType);
  dc = (int16u)dcArray[0] | ((int16u)dcArray[1] << 8);
  emberAfDemandResponseLoadControlClusterPrint("Device Class: 0x%2x, status: 0x%x\r\n",
                   dc,
                   status);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    return FALSE;
  }

  // Our thinking is that 
  // device class should always match otherwise there would be no way to 
  // narrow the group and there would be no way to address specific devices 
  // that are not in a specific group. - WEH
  else if (!(dc & deviceClass)) {
    return FALSE;
  }
  if (utilityEnrollmentGroup == 0 || (utilityEnrollmentGroup == ueg)) {
    return TRUE;
  }
  return FALSE;
}

static void addSignature(void)
{
  // The requirement of signing DRLC messages was removed from SE 1.1.
  // Signature support in the stack was required to do this,
  // however the app code allowed for the message to still be sent
  // if the stack support was not there.  If the stack support was NOT present
  // the Ember App Framework would use a signature type of 0x00 and
  // append 0xFFs to fill out the message.  This was non-standard but
  // didn't really matter because no one ever checked the signature.
  // The type of 0x00 is now being formally used in SE 1.1 to indicate
  // "no signature present", so we don't have to pad the messages.

  // As a backward compatibilty measure we do still support the old
  // non-standard dummy signature method.  We do not support adding real
  // signatures because the stack support has been removed.

  appResponseData[appResponseLength] = SIGNATURE_TYPE;
  appResponseLength++;
  
#if defined(EMBER_AF_PLUGIN_DRLC_APPEND_DUMMY_SIGNATURE)
  MEMSET(&(appResponseData[appResponseLength]), 0xFF, EMBER_SIGNATURE_SIZE);
  appResponseLength += EMBER_SIGNATURE_SIZE;
#endif
}

// -------------------------------------------------------
// DEMAND RESPONSE LOAD CONTROL CLIENT
// -------------------------------------------------------
static void fillReportEventData(int8u commandStatus,
                                int8u sequenceNumber,
                                EmberAfLoadControlEvent* e,
                                int32u statusTime)
{
  emberAfDemandResponseLoadControlClusterFlush();
  emberAfDemandResponseLoadControlClusterPrintln("= TX Report Event Status =");
  emberAfDemandResponseLoadControlClusterFlush();
  emberAfDemandResponseLoadControlClusterPrintln("  eid: %4x", 
                                                 e->eventId);
  emberAfDemandResponseLoadControlClusterFlush();
  emberAfDemandResponseLoadControlClusterPrintln("   ec: %x", 
                                                 commandStatus);
  emberAfDemandResponseLoadControlClusterPrintln("   st: T%4x", 
                                                 statusTime);
  emberAfDemandResponseLoadControlClusterFlush();
  emberAfDemandResponseLoadControlClusterPrintln("  cla: %x", 
                                                 e->criticalityLevel);
  emberAfDemandResponseLoadControlClusterPrintln("ctspa: %2x (%d)", 
                                                 e->coolingTempSetPoint, 
                                                 e->coolingTempSetPoint);
  emberAfDemandResponseLoadControlClusterFlush();
  emberAfDemandResponseLoadControlClusterPrintln("htspa: %2x (%d)", 
                                                 e->heatingTempSetPoint, 
                                                 e->heatingTempSetPoint);
  emberAfDemandResponseLoadControlClusterPrintln("  avg: %x", e->avgLoadPercentage);
  emberAfDemandResponseLoadControlClusterFlush();
  emberAfDemandResponseLoadControlClusterPrintln("   dc: %x", e->dutyCycle);
  emberAfDemandResponseLoadControlClusterPrintln("   ec: %x", e->eventControl);
  emberAfDemandResponseLoadControlClusterFlush();
  
  appResponseLength = 0;
  emberAfPutInt8uInResp(ZCL_CLUSTER_SPECIFIC_COMMAND
                        | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER);
  emberAfPutInt8uInResp(sequenceNumber);
  emberAfPutInt8uInResp(ZCL_REPORT_EVENT_STATUS_COMMAND_ID);
  emberAfPutInt32uInResp(e->eventId);
  emberAfPutInt8uInResp(commandStatus); //cmd rx
  emberAfPutInt32uInResp(statusTime);
  emberAfPutInt8uInResp(e->criticalityLevel);
  emberAfPutInt16uInResp(e->coolingTempSetPoint);
  emberAfPutInt16uInResp(e->heatingTempSetPoint);
  emberAfPutInt8uInResp(e->avgLoadPercentage);
  emberAfPutInt8uInResp(e->dutyCycle);
  emberAfPutInt8uInResp(e->eventControl);
  addSignature();

  // Set the destination to the source address from whence the event was
  // scheduled (generally, the ESP who scheduled the event) and reverse the
  // endpoints because we're sending in the opposite direction of the command
  // we received.
  emberAfResponseDestination = emberLookupNodeIdByEui64(e->source);
  emberAfSetEndpointsForResponse(e->destinationEndpoint, e->sourceEndpoint);
  emberAfResponseApsFrame.clusterId = ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID;
  emberAfSendResponse();
}

/**
 * A mechanism for retrieving the right amount of randomization
 * if startRand is true, the table is requesting the amount of 
 * start randomization, otherwise it is requesting the amount of
 * end randomization. The value returned represents seconds of
 * randomization.
 */
static int16u afGetRandomizationTime(int8u endpoint,
                                          boolean startRand) {
  int8u maxRandMin, dataType;
  EmberStatus status = 
    emberAfReadAttribute(endpoint, 
                         ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID, 
                         (startRand?
                          ZCL_START_RANDOMIZE_MINUTES_ATTRIBUTE_ID:
                          ZCL_STOP_RANDOMIZE_MINUTES_ATTRIBUTE_ID),
                         CLUSTER_MASK_CLIENT,
                         (int8u*)&maxRandMin,
                         1,
                         &dataType); 
  if ( (status != EMBER_ZCL_STATUS_SUCCESS) || (maxRandMin == 0) )
  {
    return 0; //not performed
  } else {
    int16u randNum, maxRandSec, randSec;
    randNum = halCommonGetRandom();
    maxRandSec = maxRandMin * 60;
    randSec = randNum % maxRandSec;
    return randSec; //return value rep in seconds.
  }
}

void emberAfDemandResponseLoadControlClusterClientInitCallback(int8u endpoint) 
{
  int16u deviceClass = EMBER_AF_PLUGIN_DRLC_DEVICE_CLASS;
  // Initialize device class
  emberAfWriteAttribute(endpoint, 
                        ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID, 
                        ZCL_DEVICE_CLASS_VALUE_ATTRIBUTE_ID,
                        CLUSTER_MASK_CLIENT,
                        (int8u*)(&deviceClass),
                        ZCL_INT16U_ATTRIBUTE_TYPE);
 

  // Start tick
  emberAfScheduleClusterTick(endpoint, 
                             ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID, 
                             EMBER_AF_CLIENT_CLUSTER_TICK, 
                             MILLISECOND_TICKS_PER_SECOND, 
                             EMBER_AF_OK_TO_HIBERNATE);
} 

void emberAfDemandResponseLoadControlClusterClientTickCallback(int8u endpoint) 
{
  emAfLoadControlEventTableTick(endpoint);
  emberAfScheduleClusterTick(endpoint, 
                             ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID, 
                             EMBER_AF_CLIENT_CLUSTER_TICK, 
                             MILLISECOND_TICKS_PER_SECOND, 
                             EMBER_AF_OK_TO_HIBERNATE);
}

boolean emberAfDemandResponseLoadControlClusterLoadControlEventCallback(int32u eventId,
                                                                    int16u deviceClass,
                                                                    int8u utilityEnrollmentGroup,
                                                                    int32u startTime,
                                                                    int16u duration,
                                                                    int8u criticalityLevel,
                                                                    int8u coolingTempOffset,
                                                                    int8u heatingTempOffset,
                                                                    int16s coolingTempSetPoint,
                                                                    int16s heatingTempSetPoint,
                                                                    int8s averageLoadAdjustPercent,
                                                                    int8u dutyCycle,
                                                                    int8u eventControl) 
{
  EmberAfLoadControlEvent e;
  EmberAfClusterCommand *cc = emberAfCurrentCommand();  

  emberAfDemandResponseLoadControlClusterPrintln("= RX Load Control Event =");
  emberAfDemandResponseLoadControlClusterPrintln("  eid: %4x", eventId);
  emberAfDemandResponseLoadControlClusterPrintln(" dc/g: %2x / %x", 
                                                 deviceClass, 
                                                 utilityEnrollmentGroup);
  emberAfDemandResponseLoadControlClusterPrintln("   st: T%4x", startTime);
  emberAfDemandResponseLoadControlClusterFlush();
  emberAfDemandResponseLoadControlClusterPrintln("  dur: %2x", duration);
  emberAfDemandResponseLoadControlClusterPrintln("  cla: %x", criticalityLevel);
  emberAfDemandResponseLoadControlClusterPrintln("co/ho: %x / %x", 
                                                 coolingTempOffset, 
                                                 heatingTempOffset);
  emberAfDemandResponseLoadControlClusterFlush();
  emberAfDemandResponseLoadControlClusterPrintln("ctspa: %2x (%d)", 
                                                 coolingTempSetPoint, 
                                                 coolingTempSetPoint);
  emberAfDemandResponseLoadControlClusterPrintln("htspa: %2x (%d)", 
                                                 heatingTempSetPoint,
                                                 heatingTempSetPoint);
  emberAfDemandResponseLoadControlClusterFlush();
  emberAfDemandResponseLoadControlClusterPrintln("  avg: %x", 
                                                 averageLoadAdjustPercent);
  emberAfDemandResponseLoadControlClusterPrintln("   dc: %x", dutyCycle);
  emberAfDemandResponseLoadControlClusterPrintln("   ec: %x", eventControl);
  emberAfDemandResponseLoadControlClusterFlush();

  if (!afMatchUegOrDeviceClass(emberAfCurrentEndpoint(),
                               utilityEnrollmentGroup, 
                               deviceClass)) {
    emberAfDemandResponseLoadControlClusterPrintln(
      "Neither UEG nor Device class matched.  Ignoring.");
    
    // don't send default response NTS test harness expects nothing
    // in this case
    emberAfSendDefaultResponse(emberAfCurrentCommand(), 
                               EMBER_ZCL_STATUS_NOT_FOUND);

    return TRUE;
  }
  
  emberLookupEui64ByNodeId(cc->source, e.source);
  e.sourceEndpoint = cc->apsFrame->sourceEndpoint;
  e.destinationEndpoint = cc->apsFrame->destinationEndpoint;

  e.eventId = eventId;
  e.deviceClass = deviceClass;
  e.utilityEnrollmentGroup = utilityEnrollmentGroup;
  if (startTime == 0)
  {
    e.startTime = emberAfGetCurrentTime();
  } else {
    e.startTime = startTime;
  }
  e.duration = duration;
  e.criticalityLevel = criticalityLevel;
  e.coolingTempOffset = coolingTempOffset;
  e.heatingTempOffset = heatingTempOffset;
  e.coolingTempSetPoint = coolingTempSetPoint;
  e.heatingTempSetPoint = heatingTempSetPoint;
  e.avgLoadPercentage = averageLoadAdjustPercent;
  e.dutyCycle = dutyCycle;
  e.eventControl = eventControl;
  e.optionControl = EVENT_OPT_IN_DEFAULT;
  e.startRand = 0;
  e.endRand = 0;

  if (eventControl & RANDOMIZE_START_TIME_FLAG) {
    e.startRand = afGetRandomizationTime(emberAfCurrentEndpoint(), TRUE);
  }
  if (eventControl & RANDOMIZE_END_TIME_FLAG) {
    e.endRand = afGetRandomizationTime(emberAfCurrentEndpoint(), FALSE);
  }

  emberAfDemandResponseLoadControlClusterPrintln(
    "schedule -- start: %4x, start-random: %2x end-random: %2x", 
    e.startTime, 
    e.startRand, 
    e.endRand);

  emAfScheduleLoadControlEvent(&e);
  return TRUE;
}

boolean emberAfDemandResponseLoadControlClusterCancelLoadControlEventCallback(
  int32u eventId,
  int16u deviceClass,
  int8u utilityEnrollmentGroup,
  int8u cancelControl,
  int32u effectiveTime) {
  
  // FILTER ON DEVICE CLASS AND UTILITY ENROLLMENT GROUP
  if (!afMatchUegOrDeviceClass(emberAfCurrentEndpoint(),
                               utilityEnrollmentGroup, 
                               deviceClass)) {
    emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_NOT_FOUND);
    return TRUE;
  }
  emAfCancelLoadControlEvent(eventId, cancelControl, effectiveTime);
  return TRUE;
}

boolean emberAfDemandResponseLoadControlClusterCancelAllLoadControlEventsCallback(
  int8u cancelControl) {

  if (!emAfCancelAllLoadControlEvents(cancelControl)) {
    // We didn't find any events to cancel but we were still successful in trying
    // So we return a default response of success.
    emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  }
  return TRUE;
}

void emberAfEventAction(EmberAfLoadControlEvent *event,
                        int8u eventStatus,
                        int8u sequenceNumber) 
{
  int32u statusTime;
  boolean sendReport;

  // Here we defer to custom callback which can do whatever it wants with 
  // the even.
  sendReport = emberAfPluginDrlcEventActionCallback(event,
                                                    eventStatus,
                                                    sequenceNumber);

  //Send over the air notification
  if ( sendReport ) {
    statusTime = emberAfGetCurrentTime();
    fillReportEventData(eventStatus,
                        sequenceNumber,
                        event,
                        statusTime);
  }
}
#endif //ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT
