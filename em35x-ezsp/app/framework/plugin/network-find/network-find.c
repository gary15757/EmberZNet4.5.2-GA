// *****************************************************************************
// * network-find.c
// *
// * Routines for finding and joining any viable network via scanning, rather
// * than joining a specific network. 
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include "app/framework/include/af.h"
#include "app/util/common/form-and-join.h"

#include "app/framework/plugin/network-find/gen/network-find-callback.h"

//------------------------------------------------------------------------------
// Forward Declaration

// Ideally we would put this in 'network-cli.h', but then that requires
// us to include all the CLI header files as well.  As a simple solution, we 
// forward declare this here outside of a header.
void emberAfPrintChannelListFromMask(int32u channelMask);
extern int8u emAfExtendedPanId[];

//------------------------------------------------------------------------------
// Globals

enum {
  NETWORK_FIND_NONE,
  NETWORK_FIND_FORM,
  NETWORK_FIND_JOIN,
};
static int8u state = NETWORK_FIND_NONE;

//------------------------------------------------------------------------------

void emberAfUnusedPanIdFoundCallback(EmberPanId panId, int8u channel)
{
  EmberNetworkParameters networkParams;
  EmberStatus status;

  MEMSET(&networkParams, 0, sizeof(EmberNetworkParameters));
  MEMCOPY(networkParams.extendedPanId, emAfExtendedPanId, EXTENDED_PAN_ID_SIZE);
  networkParams.panId = panId;
  networkParams.radioTxPower = EMBER_AF_RADIO_POWER;
  networkParams.radioChannel = channel;

  status = emberAfFormNetwork(&networkParams);
  if (status != EMBER_SUCCESS) {
    emberAfAppPrintln("%p error 0x%x %p", "Form", 
                      status,
                      "aborting");
    emberAfAppFlush();
    emberAfScanErrorCallback(status);
  }
}

void emberAfJoinableNetworkFoundCallback(EmberZigbeeNetwork *networkFound,
                                         int8u lqi,
                                         int8s rssi)
{
  EmberNetworkParameters networkParams;
  EmberStatus status;

  // NOTE: It's not necessary to check the networkFound->extendedPanId here
  // because the form-and-join utilities ensure this handler is only called
  // when the beacon in the found network has the same EPID as what we asked
  // for when we initiated the scan.  If the scan was requested for the EPID of
  // all zeroes, that's a special case that means any network is OK.  Either
  // way we can trust that it's OK to try joining the network params found in
  // the beacon.

  // Now construct the network parameters to join
  MEMSET(&networkParams, 0, sizeof(EmberNetworkParameters));
  MEMCOPY(networkParams.extendedPanId,
          networkFound->extendedPanId,
          EXTENDED_PAN_ID_SIZE);
  networkParams.panId = networkFound->panId;
  networkParams.radioTxPower = EMBER_AF_RADIO_POWER;
  networkParams.radioChannel = networkFound->channel;

  emberAfAppPrintln("Nwk found, ch %d, panId 0x%2X, joining",
                    networkFound->channel,
                    networkFound->panId);

  // Note that if this call fails we can't continue the scan from here (by
  // calling emberScanForNextJoinableNetwork or its wrapper function,
  // emberAfContinueJoinableNetworkSearch) because that's the function that
  // called this handler in the first place, and we don't want to be recurse.
  // TODO: Implement a scheduled event that will continue the scan process
  // outside of this context so that users don't need to invoke the scan again
  // to make it keep going.
  status = emberAfJoinNetwork(&networkParams);
  if (status != EMBER_SUCCESS) {
    emberAfAppPrintln("%p error 0x%x, %p", 
                      "Join", 
                      status,
                      "aborting");
    emberAfAppFlush();
    emberAfScanErrorCallback(status);
  }
}

void emberAfScanErrorCallback(EmberStatus status)
{
  if (status == EMBER_NO_BEACONS) {
    emberAfCorePrintln("%p and join scan done", "Form");
  } else {
    emberAfCorePrintln("%p error 0x%x", "Scan", status);
  }
  emberAfCoreFlush();
  state = NETWORK_FIND_NONE;
  emberAfPluginNetworkFindFinishedCallback(status);
}

EmberStatus emberAfFindUnusedPanIdAndFormCallback(void)
{
  EmberStatus status = EMBER_INVALID_CALL;
#if (ZA_DEVICE_TYPE == ZA_COORDINATOR)
  if (state != NETWORK_FIND_NONE) {
    emberAfAppPrintln("%pForm and join ongoing", "Error: ");
    return EMBER_INVALID_CALL;
  }

  status = emberScanForUnusedPanId(EMBER_AF_CHANNEL_MASK,
                                   EMBER_AF_PLUGIN_NETWORK_FIND_DURATION);
  if (status == EMBER_SUCCESS) {
    state = NETWORK_FIND_FORM;
  }
#endif
  return status;
}

EmberStatus emberAfStartSearchForJoinableNetworkCallback(void)
{
  EmberStatus status;
  if (state != NETWORK_FIND_NONE) {
    emberAfAppPrintln("%pForm and join ongoing", "Error: ");
    return EMBER_INVALID_CALL;
  }

  emberAfAppPrint("Search for %p\nChannels: ", "joinable network");
  emberAfAppDebugExec(emberAfPrintChannelListFromMask(EMBER_AF_CHANNEL_MASK));
  emberAfAppPrintln("");

  status = emberScanForJoinableNetwork(EMBER_AF_CHANNEL_MASK,
                                       emAfExtendedPanId);
  if (status == EMBER_SUCCESS) {
    state = NETWORK_FIND_JOIN;
  }
  return status;
}

void emberAfContinueJoinableNetworkSearchCallback(void)
{
  if (state == NETWORK_FIND_JOIN) {
    emberAfAppPrintln("Continue %p search", "joinable network");
    emberScanForNextJoinableNetwork();
  }
}

void emberAfNetworkFindOperationCompleteCallback(void)
{
  state = NETWORK_FIND_NONE;
  emberAfPluginNetworkFindFinishedCallback(EMBER_SUCCESS);
}
