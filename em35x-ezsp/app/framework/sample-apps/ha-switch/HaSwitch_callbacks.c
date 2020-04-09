// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
//

// This callback file is created for your convenience. You may add application code
// to this file. If you regenerate this file over a previous version, the previous
// version will be overwritten and any code you have added will be lost.

#include "app/framework/include/af.h"
#include "hal/hal.h"

#define HA_PROFILE_ID 0x0104

static boolean foundLight = FALSE;
static boolean lookingForLight = FALSE;
static EmberNodeId lightId = EMBER_NULL_NODE_ID;
  
static void lightDiscoveryCallback(const EmberAfServiceDiscoveryResult* result)
{
  int8u i;
  
  if (emberAfHaveDiscoveryResponseStatus(result->status)) {
    const EmberAfEndpointList* epList
      = (const EmberAfEndpointList*)result->responseData;
    emberAfCorePrintln("found light: 0x%2x", result->matchAddress);
    for (i = 0; i < epList->count; i++) {
      emberAfCorePrintln("  ept: 0x%x", epList->list[i]);
    }
    // store information of the first light we found
    if(!foundLight) {
      // We must copy the data locally because the HAL routine wants
      // a non-const pointer.
      EmberNodeId nodeId = result->matchAddress;
      int8u ep = epList->list[0];

      // we store the values in token for SoC platform and store the values
      // in RAM for host platform.
#ifndef EZSP_HOST
      halCommonSetToken(TOKEN_HALIGHT_NODE, &nodeId);
      halCommonSetToken(TOKEN_HALIGHT_ENDPOINT, &ep);
#else
      lightId = nodeId;
#endif // EZSP_HOST
      foundLight = TRUE;
    }
  } else if (result->status == EMBER_AF_BROADCAST_SERVICE_DISCOVERY_COMPLETE) {
    emberAfCorePrintln("This is all the lights found.");
    lookingForLight = FALSE;
  }
}

/** @brief Main Tick
 *
 * Whenever main application tick is called, this callback will be called at
 * the end of the main tick execution.
 *
 */
void emberAfMainTickCallback(void)
{
  EmberStatus status;
  
#ifndef EZSP_HOST
  halCommonGetToken(&lightId, TOKEN_HALIGHT_NODE);
#endif
    
  // if we are not part of the network, clear the tokens associated with 
  // HALight; if not already done so.
  if (emberNetworkState() != EMBER_JOINED_NETWORK) {
    if (lightId != EMBER_NULL_NODE_ID) {
      lightId = EMBER_NULL_NODE_ID;
      foundLight = FALSE;
#ifndef EZSP_HOST
      halCommonSetToken(TOKEN_HALIGHT_NODE, &lightId);
#endif
    }
  } else {
    // if we are on the network, discover the light if we have not done it
    // already.
    if (lightId == EMBER_NULL_NODE_ID && !foundLight && !lookingForLight) {
      emberAfCorePrintln("Find a light");
      status
        = emberAfFindDevicesByProfileAndCluster(
            EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS,
            HA_PROFILE_ID,
            ZCL_ON_OFF_CLUSTER_ID,
            EMBER_AF_SERVER_CLUSTER_DISCOVERY,
            lightDiscoveryCallback);
      if (status != EMBER_SUCCESS) { // server cluster
        emberAfDebugPrintln("Cannot find light, error 0x%x", status);
      } else {
        // the boolean is used so we do not keep sending match descriptor
        // request everytime mainTick is call while waiting for match
        // descriptor response.
        lookingForLight = TRUE;
      }
    } // check lightId value
  }
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
