// *******************************************************************
// * ias-ace-server.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the zcl-util
#include "../../util/common.h"

// clusters specific header
#include "ias-zone-table.h"


static int8u armMode[MAX_ENDPOINT_COUNT];

void emberAfIasAceClusterServerInitCallback(int8u endpoint) 
{
  armMode[emberAfIndexFromEndpoint(endpoint)] = 0;
}

boolean emberAfIasAceClusterArmCallback(int8u mode) {
  // set mode and send response
  int8u endpointIndex = emberAfIndexFromEndpoint(emberAfCurrentEndpoint());
  armMode[endpointIndex] = mode;
  emberAfResponseApsFrame.clusterId = ZCL_IAS_ACE_CLUSTER_ID;
  appResponseData[0] = ZCL_CLUSTER_SPECIFIC_COMMAND | 0x8;
  appResponseData[1] = emberAfIncomingZclSequenceNumber;
  appResponseData[2] = ZCL_ARM_RESPONSE_COMMAND_ID;
  appResponseData[3] = armMode[endpointIndex];
  appResponseLength = 4;
  emberAfSendResponse();
  return TRUE;
}

boolean emberAfIasAceClusterGetZoneIdMapCallback(void) {
  int8u i;
  int16u mapEntry;
  int16u map[ZONE_TABLE_MAP_SIZE];
  for (i=0; i<ZONE_TABLE_MAP_SIZE; i++) {
    map[i] = 0;
  }

  emberAfIasAceClusterPrintln("rx zid map");
  getZoneIdMap(map);

  emberAfResponseApsFrame.clusterId = ZCL_IAS_ACE_CLUSTER_ID;
  appResponseData[0] = ZCL_CLUSTER_SPECIFIC_COMMAND | 0x8;
  appResponseData[1] = emberAfIncomingZclSequenceNumber;
  appResponseData[2] = ZCL_GET_ZONE_ID_MAP_RESPONSE_COMMAND_ID;
  for (i=0;i<ZONE_TABLE_MAP_SIZE;i++)
  {
    mapEntry = map[i];
    emberAfIasAceClusterPrintln("mapEntry: %2x", mapEntry);

    appResponseData[i+3] = (mapEntry & 0xff);
    appResponseData[i+4] = ((mapEntry >> 8) & 0xff);
  }
  appResponseLength = 3 + (2*ZONE_TABLE_MAP_SIZE);
  emberAfSendResponse();
  return TRUE;
}

boolean emberAfIasAceClusterGetZoneInformationCallback(int8u zoneId) {
  EmberAfIasZoneTableEntry *entry;
  int8u i;
  int16u  type;
  int8u*  address;
  
  entry = getZoneInfo(zoneId);
  type  = entry->zoneType;
  emberAfResponseApsFrame.clusterId = ZCL_IAS_ACE_CLUSTER_ID;
  appResponseData[0] = ZCL_CLUSTER_SPECIFIC_COMMAND | 0x8;
  appResponseData[1] = emberAfIncomingZclSequenceNumber;
  appResponseData[2] = ZCL_GET_ZONE_INFORMATION_RESPONSE_COMMAND_ID;
  appResponseData[3] = zoneId;
  appResponseData[4] = ((type >> 8) & 0xff);
  appResponseData[5] = (type & 0xff);
  address = entry->ieeeAdd;
  for (i=0;i<8;i++)
  {
    appResponseData[i+6] = *address;
    address++;
  }
  appResponseLength = 14;
  emberAfSendResponse();
  return TRUE;
}

/**
 * A server side function for printing state
**/
void emAfIasAcePrintInfo(void)
{
  int8u i;

  for ( i = 0; i<emberAfEndpointCount(); i++ )
    emberAfCorePrintln("EP %x, armMode: 0x%x", emberAfEndpointFromIndex(i), armMode[i]);
}



