// *******************************************************************
// * SeMeterGas_callbacks.c
// *
// * This file contains all application specific code for the 
// * gas meter sample application. This application is intended
// * to be used along with the meter mirror application 
// * SeMeterMirror
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "app/framework/util/common.h"

#define GAS_METER_ENDPOINT 0x01

// *******************************************************************
// * clusterInitCallback 
// * 
// * Make sure that the simple metering device type on endpoint 1
// * is set to gas meter.
// * 
// * 
// *******************************************************************
void emberAfClusterInitCallback(int8u endpointId, 
                         int16u clusterId) {
  int8u deviceType = EMBER_ZCL_METER_DEVICE_TYPE_MIRRORED_GAS_METER;
  if ((endpointId == GAS_METER_ENDPOINT) && 
      (clusterId == ZCL_SIMPLE_METERING_CLUSTER_ID)) {
        emberAfWriteAttribute(endpointId,
                              ZCL_SIMPLE_METERING_CLUSTER_ID, 
                              ZCL_METERING_DEVICE_TYPE_ATTRIBUTE_ID,
                              CLUSTER_MASK_SERVER,
                              (int8u*) &deviceType,
                              ZCL_INT8U_ATTRIBUTE_TYPE
                              );  
  }
}

// *******************************************************************
// * simpleMeteringClusterMirrorRemovedCallback
// * 
// * This callback simply prints out the endpoint from which
// * the mirror was removed. 
// * 
// *******************************************************************
boolean emberAfSimpleMeteringClusterMirrorRemovedCallback(int16u endpointId) {
  if (endpointId == 0xffff)
    emberAfCorePrintln("%premove FAILED", "Mirror ");
  else
    emberAfCorePrintln("%pREMOVED from %x", "Mirror ", endpointId);
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

// *******************************************************************
// * simpleMeteringClusterRequestMirrorResponseCallback
// * 
// * This callback simply prints out the endpoint to which the
// * mirror was added. 
// *
// * A more complex implementation of this sample
// * application would start writing attributes by sending
// * global attribute writes to the mirrored endpoint. 
// * I have not implemented a mechanism for
// * this and instead write the attributes using the cli commands
// * such as:
// *
// * zcl global write 0x0702 0x0306 0x18 {04}
// * send 0 1 3
// * 
// *******************************************************************
boolean emberAfSimpleMeteringClusterRequestMirrorResponseCallback(int16u endpointId) {
  if (endpointId == 0xffff)
    emberAfCorePrintln("%padd FAILED", "Mirror ");
  else
    emberAfCorePrintln("%pADDED on %x", "Mirror ", endpointId);
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

/** @brief Finished
 *
 * This callback is fired when the network-find plugin is finished with the
 * forming or joining process.  The result of the operation will be returned
 * in the status parameter.
 *
 * @param status   Ver.: always
 */
void emberAfPluginNetworkFindFinishedCallback(EmberStatus status) {
  
}
