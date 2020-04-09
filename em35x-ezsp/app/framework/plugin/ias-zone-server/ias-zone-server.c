// *******************************************************************
// * ias-zone-server.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the util
#include "../../include/af.h"
#include "../../util/util.h"

#define ZCL_IAS_ZONE_STATE_NOT_ENROLLED 0x00
#define ZCL_IAS_ZONE_STATE_ENROLLED     0x01

#define ZCL_IAS_ZONE_ENROLL_RESPONSE_SUCCESS          0x00
#define ZCL_IAS_ZONE_ENROLL_RESPONSE_NOT_SUPPORTED    0x01
#define ZCL_IAS_ZONE_ENROLL_RESPONSE_NO_ENROLL_PERMIT 0x02
#define ZCL_IAS_ZONE_ENROLL_RESPONSE_TOO_MANY_ZONES   0x03

boolean emberAfIasZoneClusterZoneEnrollResponseCallback(int8u enrollResponseCode,
                                                        int8u zoneId)
{
  EmberAfStatus status;
  EmberEUI64 senderIeeeAddress;
  if (emberGetSenderEui64(senderIeeeAddress) != EMBER_SUCCESS) {
    // Wipe it out...
    MEMSET(senderIeeeAddress, 0, sizeof(EmberEUI64));
  }

  emberAfIasZoneClusterPrintln("RX: IAS ZONE: enroll response,"
                               " code 0x%x zone 0x%x, ",
                               enrollResponseCode,
                               zoneId);

  if (enrollResponseCode == ZCL_IAS_ZONE_ENROLL_RESPONSE_SUCCESS) {
    int8u cieAddress[8];
    int8u dataType;

    // Check senders address against ias cie address
    status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                  ZCL_IAS_ZONE_CLUSTER_ID,
                                  ZCL_IAS_CIE_ADDRESS_ATTRIBUTE_ID,
                                  CLUSTER_MASK_SERVER,
                                  cieAddress,
                                  EUI64_SIZE,
                                  &dataType);
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      emberAfIasZoneClusterPrintln("fail read cie add");
    } else if (MEMCOMPARE(cieAddress, senderIeeeAddress, EUI64_SIZE) == 0) {
      // Set attribute
      int8u state = ZCL_IAS_ZONE_STATE_ENROLLED;
      status = emberAfWriteAttribute(emberAfCurrentEndpoint(),
                                     ZCL_IAS_ZONE_CLUSTER_ID,
                                     ZCL_ZONE_STATE_ATTRIBUTE_ID,
                                     CLUSTER_MASK_SERVER,
                                     &state,
                                     ZCL_ENUM8_ATTRIBUTE_TYPE);
    } else {
      emberAfIasZoneClusterPrint("cie: ");
      emberAfIasZoneClusterDebugExec(emberAfPrintBigEndianEui64(cieAddress));
      emberAfIasZoneClusterPrint(" sndr: ");
      emberAfIasZoneClusterDebugExec(emberAfPrintBigEndianEui64(senderIeeeAddress));
      emberAfIasZoneClusterPrintln("");
      emberAfIasZoneClusterPrintln("fail cie address match");
      status = EMBER_ZCL_STATUS_FAILURE;
    }
  } else {
    // Acknowledge a failure response with a success respones.
      status = EMBER_ZCL_STATUS_SUCCESS;
  }

  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}


