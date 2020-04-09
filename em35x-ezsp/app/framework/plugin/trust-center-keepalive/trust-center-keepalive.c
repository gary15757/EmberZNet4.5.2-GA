// *****************************************************************************
// * trust-center-keepalive.c
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include "app/framework/include/af.h"
#include "app/framework/plugin/smart-energy-registration/smart-energy-registration.h"
#include "trust-center-keepalive.h"

// NOTE: This code is intended only for routers, so we do not consider sleepy
// devices and their hibernating/napping issues.  As per the spec, only routers
// have to keep track of the TC.  Sleepies just keep track of their parent.

//------------------------------------------------------------------------------
// Globals

typedef enum {
  STATE_INITIAL,
  STATE_SEND_KEEPALIVE_SIGNAL,
  STATE_INITIATE_TRUST_CENTER_SEARCH,
} TrustCenterKeepaliveState;
static TrustCenterKeepaliveState state = STATE_INITIAL;

EmberEventControl emAfPluginTrustCenterKeepaliveEventControl;

static int8u failures = 0;

static boolean waitingForResponse = FALSE;

#define KEEPALIVE_WAIT_TIME_MS (5 * MILLISECOND_TICKS_PER_SECOND)

//------------------------------------------------------------------------------
// Forward Declarations

static void sendKeepaliveSignal(void);
static void initiateTrustCenterSearch(void);
static void delayUntilNextKeepalive(void);
static void trustCenterKeepaliveStart(void);

//------------------------------------------------------------------------------

void emberAfTrustCenterKeepaliveAbortCallback(void)
{
  emberAfCorePrintln("Setting trust center keepalive inactive.");
  state = STATE_INITIAL;
  emberEventControlSetInactive(emAfPluginTrustCenterKeepaliveEventControl);
}

void emberAfTrustCenterKeepaliveUpdateCallback(boolean registrationComplete)
{
  // Note:  registartion complete does NOT necessarily mean registration went
  // through and completed successfully.  We may have been called after a rejoin
  // failed and the router just came back up on the network.

  if (state == STATE_INITIAL) {
    trustCenterKeepaliveStart();
    return;

  } else if (state == STATE_INITIATE_TRUST_CENTER_SEARCH) {
    EmberKeyStruct keyStruct;
    EmberStatus status = emberGetKey(EMBER_TRUST_CENTER_LINK_KEY,
                                     &keyStruct);
    if (status == EMBER_SUCCESS
        && !(keyStruct.bitmask & EMBER_KEY_IS_AUTHORIZED)) {
      // If the TC link key is not authorized, that means we rejoined
      // to a new TC and key establishment did not complete successfully.
      emberAfCorePrintln("Registration failed after TC change.");
      emberAfCorePrintln("Forcing reboot to forget old network.");
      emberAfCoreFlush();
      halReboot();
    }
    state = STATE_SEND_KEEPALIVE_SIGNAL;
    delayUntilNextKeepalive();
  }

  // If the Trust Center's EUI changed and we completed registration,
  // this means that the we have found a new network and must
  // start persistently storing our tokens again.  Everything is a-okay.

  // If this callback was executed without a Trust Center search in progress
  // or after a failed trust center search, the call below has no effect, 
  // because we didn't call emberStopWritingStackTokens() previously.
  emberStartWritingStackTokens();
} 

static void trustCenterKeepaliveStart(void)
{
  if (emberGetNodeId() == EMBER_TRUST_CENTER_NODE_ID) {
    // If this code is executing, then the trust center must be alive.
    return;
  }

  failures = 0;
  sendKeepaliveSignal();
}

static void delayUntilNextKeepalive(void)
{
  emberAfEventControlSetDelay(&emAfPluginTrustCenterKeepaliveEventControl,
                              EMBER_AF_PLUGIN_TRUST_CENTER_KEEPALIVE_DELAY_INTERVAL);
}

static void messageTimeout(void)
{
  waitingForResponse = FALSE;
  if (failures != 255) {
    failures++;
  }

  emberAfSecurityPrintln("ERR: Trust center did not acknowledge"
                         " previous keepalive signal");

  if (failures >= EMBER_AF_PLUGIN_TRUST_CENTER_KEEPALIVE_FAILURE_LIMIT) {
    emberAfSecurityPrintln("ERR: Keepalive failure limit reached (%d)",
                           EMBER_AF_PLUGIN_TRUST_CENTER_KEEPALIVE_FAILURE_LIMIT);
    initiateTrustCenterSearch();
  } else {
    delayUntilNextKeepalive();
  }
}

void emAfPluginTrustCenterKeepaliveTick(void)
{
  emberEventControlSetInactive(emAfPluginTrustCenterKeepaliveEventControl);

  if (waitingForResponse) {
    messageTimeout();
    return;
  }

  switch (state) {
  case STATE_SEND_KEEPALIVE_SIGNAL:
    sendKeepaliveSignal();
    break;
  default:
    break;
  }
}

static void sendKeepaliveSignal(void)
{
  EmberStatus status;
  int8u attributeIds[] = {
    LOW_BYTE(ZCL_KEY_ESTABLISHMENT_SUITE_SERVER_ATTRIBUTE_ID),
    HIGH_BYTE(ZCL_KEY_ESTABLISHMENT_SUITE_SERVER_ATTRIBUTE_ID),
  };
  int8u endpoint = emAfPluginSmartEnergyRegistrationTrustCenterKeyEstablishmentEndpoint();

  // The keepalive is an attempt to read a Key Establishment attribute on the
  // trust center.  In general, APS encryption is not required for Key
  // Establishment commands, but it is required by the spec for the keepalive,
  // so the option is explicitly set here.
  emberAfSecurityPrintln("Sending keepalive signal"
                         " to trust center endpoint 0x%x",
                         endpoint);
  emberAfFillCommandGlobalClientToServerReadAttributes(ZCL_KEY_ESTABLISHMENT_CLUSTER_ID,
                                                       attributeIds,
                                                       sizeof(attributeIds));

  // It is possible we will retrieve an undefined endpoint (0xFF) if we rebooted
  // and the TC is not around.  Nonetheless we will still use it as the broadcast
  // endpoint in the hopes that the trust center will respond.
  emberAfGetCommandApsFrame()->sourceEndpoint = emberAfEndpointFromIndex(0);
  emberAfGetCommandApsFrame()->destinationEndpoint = endpoint;
  emberAfGetCommandApsFrame()->options |= EMBER_APS_OPTION_ENCRYPTION;
  status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,
                                     EMBER_TRUST_CENTER_NODE_ID);
  if (status != EMBER_SUCCESS) {
    emberAfSecurityPrintln("ERR: Failed to send keepalive signal"
                           " to trust center endpoint 0x%x (0x%x)",
                           endpoint,
                           status);
  }
  state = STATE_SEND_KEEPALIVE_SIGNAL;
  waitingForResponse = (status == EMBER_SUCCESS);
  emberAfEventControlSetDelay(&emAfPluginTrustCenterKeepaliveEventControl,
                              (status == EMBER_SUCCESS
                               ? KEEPALIVE_WAIT_TIME_MS
                               : EMBER_AF_PLUGIN_TRUST_CENTER_KEEPALIVE_DELAY_INTERVAL));
}

void emAfPluginTrustCenterKeepaliveReadAttributesResponseCallback(int8u *buffer,
                                                                  int16u bufLen)
{
  // We don't care about the contents of the response, just that we got one.
  if (emberAfCurrentCommand()->source == EMBER_TRUST_CENTER_NODE_ID
      && state == STATE_SEND_KEEPALIVE_SIGNAL) {
    emberAfSecurityPrintln("Trust center acknowledged keepalive signal");
    waitingForResponse = FALSE;
    failures = 0;
    delayUntilNextKeepalive();
  }
}

static void initiateTrustCenterSearch(void)
{
  EmberStatus status;
  emberAfSecurityFlush();
  emberAfSecurityPrintln("Initiating trust center search");
  emberAfSecurityFlush();
  status = emberStopWritingStackTokens();
  if (status == EMBER_SUCCESS) {
    status = emberFindAndRejoinNetwork(FALSE, EMBER_ALL_802_15_4_CHANNELS_MASK);
  } 
  
  if (status == EMBER_SUCCESS) {
    state = STATE_INITIATE_TRUST_CENTER_SEARCH;
  } else {
    emberAfSecurityPrintln("ERR: Could not initiate TC search (0x%x)", status);
    emberStartWritingStackTokens();
  }
}
