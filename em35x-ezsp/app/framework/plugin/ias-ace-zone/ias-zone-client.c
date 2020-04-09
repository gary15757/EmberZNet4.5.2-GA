// *******************************************************************
// * ias-zone-client.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the util
#include "../../util/common.h"

// clusters specific header
#include "ias-zone-table.h"

#define ZCL_IAS_ZONE_STATE_NOT_ENROLLED 0x00
#define ZCL_IAS_ZONE_STATE_ENROLLED     0x01

#define ZCL_IAS_ZONE_ENROLL_RESPONSE_SUCCESS          0x00
#define ZCL_IAS_ZONE_ENROLL_RESPONSE_NOT_SUPPORTED    0x01
#define ZCL_IAS_ZONE_ENROLL_RESPONSE_NO_ENROLL_PERMIT 0x02
#define ZCL_IAS_ZONE_ENROLL_RESPONSE_TOO_MANY_ZONES   0x03

// Initialization function for the zone client
void emberAfIasZoneClusterClientInitCallback(int8u endpoint) {
  // Initialize the Zone Table, this should be and the
  // zone table put into persistent memory.
  initZoneTable();
}

/**
 * Zone table enrollment can result in four possible outcomes,
 * only two of which are handled in this sample code.
 * 0x00 Success                              //handled
 * 0x01 Zone type not supported              //implementation required.
 * 0x02 No enroll permit                     //implementation required.
 * 0x03 CIE reached limit of enrolled zones. //handled
 */
boolean emberAfIasZoneClusterZoneEnrollRequestCallback(int16u zoneType,
                                                       int16u manufacturerCode)
{
  int8u zoneId;

  EmberEUI64 senderIeeeAddress;
  if (emberGetSenderEui64(senderIeeeAddress) != EMBER_SUCCESS) {
    // Wipe it out...
    MEMSET(senderIeeeAddress, 0, sizeof(EmberEUI64));
  }

  // construct response header
  emberAfResponseApsFrame.clusterId = ZCL_IAS_ZONE_CLUSTER_ID;
  appResponseData[0] = ZCL_CLUSTER_SPECIFIC_COMMAND; //response is c2s
  appResponseData[1] = emberAfIncomingZclSequenceNumber;
  appResponseData[2] = ZCL_ZONE_ENROLL_RESPONSE_COMMAND_ID;
  emberAfResponseApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;

  //  attempt to enroll and send response
  if (getNextZoneId(&zoneId) != EMBER_ZCL_STATUS_SUCCESS) {
    // enroll failed
    appResponseData[3] = ZCL_IAS_ZONE_ENROLL_RESPONSE_TOO_MANY_ZONES;
    appResponseLength = 4;
  } else {
    //enroll and return success
    enroll(zoneId, zoneType, senderIeeeAddress);
    appResponseData[3] = ZCL_IAS_ZONE_ENROLL_RESPONSE_SUCCESS;
    appResponseData[4] = zoneId;
    appResponseLength = 5;
  }
  emberAfSendResponse();
  return TRUE;
}
