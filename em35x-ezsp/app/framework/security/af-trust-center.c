// *****************************************************************************
// * trust-center.c
// *
// * Security code for a Trust Center node.
// *
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include PLATFORM_HEADER //compiler/micro specifics, types

#if defined EZSP_HOST
  #include "stack/include/ember-types.h"
  #include "stack/include/error.h"

  #include "app/util/ezsp/ezsp-protocol.h"
  #include "app/util/ezsp/ezsp.h"
  #include "app/util/ezsp/ezsp-utils.h"
  #include "app/util/ezsp/serial-interface.h"

#else // Stack App
  #include "stack/include/ember.h"
#endif

// This is needed when security-config.h is included so that the functions below
// are correctly defined and not stubbed.  Only needed by this file.
#define USE_REAL_SECURITY_PROTOTYPES

#include "app/framework/util/print.h"

// to get access to the emberAfSecurityPrint macro and security-config.h
#include "app/framework/util/af-main.h"

#include "app/framework/security/af-security.h"

// HAL - hardware abstraction layer
#include "hal/hal.h"
#include "app/util/serial/serial.h"

#include "app/framework/util/util.h"

#include "app/framework/include/af.h"
#include "app/framework/gen/callback.h"   // emberAfTrustCenterJoinCallback()

//------------------------------------------------------------------------------
// Globals

// PRECONFIGURED_KEY is defined based on the Application's Security Profile
// in security-config.h
static PGM EmberKeyData preconfiguredKey = PRECONFIGURED_KEY;

// It is HIGHLY RECOMENDEND to use a RANDOM network key when
// creating a network.  For purposes of DEBUG only a well-known key
// can be used.  When switching, we alternate between these two keys.
#if defined ZA_SECURITY_STATIC_DEBUG_NETWORK_KEY
  static PGM EmberKeyData networkKey =  ZA_SECURITY_STATIC_DEBUG_NETWORK_KEY;
  static PGM EmberKeyData networkKey2 = ZA_SECURITY_STATIC_DEBUG_NETWORK_KEY_2;
#endif

#if defined(EMBER_AF_PRINT_SECURITY)
  // Corresponds to the EmberJoinDecision status codes
  static PGM_NO_CONST PGM_P joinDecisionText[] = {
    EMBER_JOIN_DECISION_STRINGS
  };

  // Corresponds to the EmberDeviceUpdate status codes
  static PGM_NO_CONST PGM_P deviceUpdateText[] = {
    EMBER_DEVICE_UPDATE_STRINGS
  };

#endif // EMBER_AF_PRINT_APP

// a timer to remind us to send the network key update after we have sent
// out the network key. We must wait a period equal to the broadcast 
// timeout so that all routers have a chance to receive the broadcast 
// of the new network key
#define NETWORK_KEY_UPDATE_TIME 120; // 30 seconds
static int8u sendNetworkKeyUpdateTimer = 0;
static int16u lastBlinkTime = 0;
static int32u keySwitchQuarterSecondsPassed = 0;

#if defined (ZA_SECURITY_RANDOM_LINK_KEY)
static boolean sendingKeyInTheClear = FALSE;
static int32u allowJoinInTheClearQuarterSecondsPassed = 0;
#endif

#define JOIN_IN_THE_CLEAR_INTERVAL (4 * 30) // quarter seconds

static EmberStatus permitRequestingTrustCenterLinkKey(boolean allow);
static EmberStatus permitRequestingApplicationLinkKey(boolean allow);

static EmberStatus setJoinPolicy(EmberJoinDecision decision);

//------------------------------------------------------------------------------

EmberStatus zaTrustCenterSetJoinPolicy(EmberJoinDecision decision)
{
  // Call the platform specific method to do this.
  EmberStatus status = setJoinPolicy(decision);

  // One of the reasons we #ifdef this is to prevent it from accidentally
  // being included in the code, since joining in the clear poses a security
  // risk.
#if defined (ZA_SECURITY_RANDOM_LINK_KEY)
  if (status == EMBER_SUCCESS && decision == EMBER_SEND_KEY_IN_THE_CLEAR) {
    sendingKeyInTheClear = TRUE;
    allowJoinInTheClearQuarterSecondsPassed = 0;
  }
#endif

  return status;
}

EmberStatus zaTrustCenterSecurityPolicyInit(void)
{
  EmberStatus status = permitRequestingTrustCenterLinkKey(TC_LINK_KEY_REQUEST_POLICY);
  if (status == EMBER_SUCCESS) {
    status = permitRequestingApplicationLinkKey(APP_LINK_KEY_REQUEST_POLICY);
  }
  if (status != EMBER_SUCCESS) {
    return status;
  }

  // We always set the join policy to EMBER_USE_PRECONFIGURED_KEY
  // even in the case where the joining device doesn't have one.  This
  // is the safest thing to do.
  // In cases where devices don't have a preconfigured key, the TC must be
  // explicitly told to allow joining by calling the function below with
  // EMBER_SEND_KEY_IN_THE_CLEAR.  Once the device finishes joining the TC 
  // should set the policy back to EMBER_USE_PRECONFIGURED_KEY.
  return zaTrustCenterSetJoinPolicy(EMBER_USE_PRECONFIGURED_KEY);
}

EmberStatus zaTrustCenterSecurityInit(void)
{
  EmberInitialSecurityState state;
  EmberStatus status;
  MEMSET(&state, 0, sizeof(EmberInitialSecurityState));

  // NOTE:  We must use the PGM version of memcopy() for those
  // platforms where the program and data space are segregrated.
  halCommonMemPGMCopy(emberKeyContents(&(state.preconfiguredKey)), 
                      emberKeyContents(&preconfiguredKey),
                      EMBER_ENCRYPTION_KEY_SIZE);

  state.bitmask = ((TC_SECURITY_BITMASK 
                    | ADDITIONAL_BITMASK_OPTIONS)
                   & ~CLEARED_BITMASK_OPTIONS);

  // Clear the install code bit since it is only viable as an option
  // when joining a network, not when acting as the TC.
  state.bitmask &= ~EMBER_GET_PRECONFIGURED_KEY_FROM_INSTALL_CODE;

#if defined(ZA_SECURITY_RANDOM_LINK_KEY) && defined(ZA_TC_GLOBAL_LINK_KEY)
  // Custom Security profile without a preconfigured link key.
  // Nodes will join and request the link key.

  status = generateRandomKey(&(state.preconfiguredKey));
  if (status != EMBER_SUCCESS) {
    return status;
  }
  state.bitmask |= EMBER_HAVE_PRECONFIGURED_KEY;
#endif

  // Random network key (highly recommended)
#if !defined ZA_SECURITY_STATIC_DEBUG_NETWORK_KEY
  status = generateRandomKey(&(state.networkKey));
  if (status != EMBER_SUCCESS) {
    return status;
  }

#else // Static Network key (for testing only)
  // NOTE:  We must use the PGM version of memcopy() for those
  // platforms where the program and data space are segregrated.
  halCommonMemPGMCopy(emberKeyContents(&state.networkKey), 
                      emberKeyContents(&networkKey),
                      EMBER_ENCRYPTION_KEY_SIZE);
#endif

  state.bitmask |= EMBER_HAVE_NETWORK_KEY;


#if defined ZA_CLI_FULL
  // These functions will only be called if the full CLI is enabled and key 
  // values have been previously set on the CLI via the "changekey" command.
  getLinkKeyFromCli(&(state.preconfiguredKey));
  getNetworkKeyFromCli(&(state.networkKey));
#endif

  emberAfSecurityPrintln("set state to: 0x%2x", state.bitmask);
  status = emberSetInitialSecurityState(&state);
  emberAfSecurityPrintln("security init TC: 0x%x", status);

  if (EMBER_SUCCESS == status) {
    return zaTrustCenterSecurityPolicyInit();
  }

  return status;
}

static void securityJoinNotify(EmberNodeId newNodeId,
                               EmberEUI64 newNodeEui64,
                               EmberNodeId parentOfNewNode,
                               EmberDeviceUpdate status,
                               EmberJoinDecision decision)
{
  // Allow users of the framework an opportunity to see this notification.
  emberAfTrustCenterJoinCallback(newNodeId, 
                                 newNodeEui64, 
                                 parentOfNewNode, 
                                 status, 
                                 decision);

#if defined(EMBER_AF_PRINT_SECURITY)
  emberAfSecurityPrintln("Trust Center Join Handler: status = %p, decision = %p (%x), shortid 0x%2x",
                 deviceUpdateText[status],
                 joinDecisionText[decision],
                 decision,
                 newNodeId);
  emberAfSecurityFlush();
#endif
}

// The Network Key Update is sent out first and all routers will store
// the value of the new key but won't start using it yet.
// Once that broadcast has had enough time to propagate, we will send out
// a stack message (Network Key Switch) to start using the new key.
// End Devices (sleepies and non-sleepies alike) are expected to miss
// the update & switch commands.  When they discover that they have 
// missed a key update & switch, they will perform a Rejoin without NWK
// security.  The Trust Center will unicast the new network key encrypted
// with their link key.

EmberStatus zaTrustCenterStartNetworkKeySwitch(void)
{
  EmberStatus status;
  EmberKeyData newKey;

#if !defined(ZA_SECURITY_STATIC_DEBUG_NETWORK_KEY)
  // Most secure method for changing the network key is to pick a random
  // one.  
  status = generateRandomKey(&newKey);

#else
  // INSECURE!  For TEST SYSTEMS ONLY.  
  // Use two hardcoded network keys and switch back and forth.
  {
    EmberKeyStruct keyStruct;
    status = emberGetKey(EMBER_CURRENT_NETWORK_KEY,
                         &keyStruct);
    if (status == EMBER_SUCCESS) {
      // For even number key sequence numbers we use
      // ZA_SECURITY_STATIC_DEBUG_NETWORK_KEY and for
      // odd sequence numbers we use 
      // ZA_SECURITY_STATIC_DEBUG_NETWORK_KEY_2.  This makes it easy
      // to know which key to switch to.
      halCommonMemPGMCopy(emberKeyContents(&newKey), 
                          emberKeyContents(keyStruct.sequenceNumber & 0x01
                                           ? &networkKey2
                                           : &networkKey),
                          sizeof(EmberKeyData));
    }
  }
#endif //ZA_SECURITY_NETWORK_KEY_2

  if (status != EMBER_SUCCESS) {
    // make this a separate call to save CONST
    emberAfSecurityPrint("key-update: "); 
    emberAfSecurityPrintln("gen FAIL!");
    return status;
  }

  // print out the key so that users know what it is
  // (i.e. to potentially copy into ISD)
  emberAfSecurityPrint("key-update: new key: ");
  emberAfPrintZigbeeKey(newKey.contents);

  status = emberBroadcastNextNetworkKey(&newKey);

  // make this a separate call to save CONST
  emberAfSecurityPrint("key-update broadcast: "); 
  emberAfSecurityDebugExec(emAfPrintStatus("next key",
                                           status));
  if (status != EMBER_SUCCESS) {
    return status;
  }
  emberAfSecurityPrint("waiting 30 sec. to send key-switch"); 
  // set a flag so we know to send the key switch at a later time
  sendNetworkKeyUpdateTimer = NETWORK_KEY_UPDATE_TIME;
  return EMBER_SUCCESS;
}

void zaTrustCenterTick(void)
{
  int16u time;
  EmberStatus status = EMBER_SUCCESS;
  (void)status; //remove warning if not used

  time = halCommonGetInt16uMillisecondTick();
  if (elapsedTimeInt16u(lastBlinkTime, time)
      > MILLISECOND_TICKS_PER_QUARTERSECOND) {
    lastBlinkTime = time;

#if defined(ZA_KEY_SWITCH_INTERVAL) && ZA_KEY_SWITCH_INTERVAL > 0
      keySwitchQuarterSecondsPassed++;
      if (keySwitchQuarterSecondsPassed > (ZA_KEY_SWITCH_INTERVAL * 4)) {
        if (emberAfGetNodeId() != 0x0000
            || emberNetworkState() != EMBER_JOINED_NETWORK) {
          return;
        }
        zaTrustCenterStartNetworkKeySwitch();
        keySwitchQuarterSecondsPassed = 0;
      }
#endif

#if defined (ZA_SECURITY_RANDOM_LINK_KEY)
    // Only a custom security profile uses random link keys 
    // (i.e. no preconfigured key)
    // For that case we have temporarily allow sending the key
    // in the clear.
    if (sendingKeyInTheClear) {
      allowJoinInTheClearQuarterSecondsPassed++;
      if (allowJoinInTheClearQuarterSecondsPassed
          > JOIN_IN_THE_CLEAR_INTERVAL) {
        sendingKeyInTheClear = FALSE;
        emberAfSecurityPrintln("trust-center: no longer sending NWK key in the clear");
        zaTrustCenterSetJoinPolicy(EMBER_USE_PRECONFIGURED_KEY);
      }
    }
#endif

    // handle transmission of key switch if necessary
    if (sendNetworkKeyUpdateTimer > 0) {
      sendNetworkKeyUpdateTimer--;
      if (sendNetworkKeyUpdateTimer == 0) {
        status = emberBroadcastNetworkKeySwitch();
        // make this a separate call to save CONST
        emberAfSecurityPrint("key-update broadcast: "); 
        emberAfSecurityDebugExec(emAfPrintStatus("key switch",
                                                 status));
      }
    }
  }
}

//==============================================================================
// Platform Dependent Implementations

#if defined (EZSP_HOST)

static PGM_NO_CONST PGM_P ezspJoinPolicyText[] = {
  "Allow Joins",
  "Allow preconfigured key joins",
  "Allow rejoins only",
  "Disallow all joins and rejoins",
  "Allow Joins, rejoins have link key",
};

void ezspTrustCenterJoinHandler(EmberNodeId newNodeId,
                                EmberEUI64 newNodeEui64,
                                EmberDeviceUpdate status,
                                EmberJoinDecision policyDecision,
                                EmberNodeId parentOfNewNode)
{
  securityJoinNotify(newNodeId,
                     newNodeEui64,
                     parentOfNewNode,
                     status,
                     policyDecision);
}

static EmberStatus setJoinPolicy(EmberJoinDecision decision)
{
  EzspDecisionId id;
  if (decision == EMBER_USE_PRECONFIGURED_KEY) {
    id = EZSP_ALLOW_PRECONFIGURED_KEY_JOINS;
  } else if (decision == EMBER_SEND_KEY_IN_THE_CLEAR) {
    id = EZSP_ALLOW_JOINS_REJOINS_HAVE_LINK_KEY;
  } else {  // EMBER_DENY_JOIN or EMBER_NO_ACTION
    id = EZSP_DISALLOW_ALL_JOINS_AND_REJOINS;
  }
  return emberAfSetEzspPolicy(EZSP_TRUST_CENTER_POLICY,
                          id,
                          "Trust Center Policy",
                          ezspJoinPolicyText[id]);
}

static EmberStatus permitRequestingTrustCenterLinkKey(boolean allow)
{
  return emberAfSetEzspPolicy(EZSP_TC_KEY_REQUEST_POLICY,
                          (allow
                           ? EZSP_ALLOW_TC_KEY_REQUESTS
                           : EZSP_DENY_TC_KEY_REQUESTS),
                          "TC Key Request",
                          (allow ? "Allow" : "Deny"));
}

static EmberStatus permitRequestingApplicationLinkKey(boolean allow)
{
  return emberAfSetEzspPolicy(EZSP_APP_KEY_REQUEST_POLICY,
                          (allow
                           ? EZSP_ALLOW_APP_KEY_REQUESTS
                           : EZSP_DENY_APP_KEY_REQUESTS),
                          "App. Key Request",
                          (allow ? "Allow" : "Deny"));
}

//------------------------------------------------------------------------------
// System-on-a-chip

#else 

static EmberJoinDecision defaultDecision = EMBER_USE_PRECONFIGURED_KEY;

EmberJoinDecision emberTrustCenterJoinHandler(EmberNodeId newNodeId,
                                              EmberEUI64 newNodeEui64,
                                              EmberDeviceUpdate status,
                                              EmberNodeId parentOfNewNode)
{
  EmberJoinDecision joinDecision = defaultDecision;

  if (status == EMBER_STANDARD_SECURITY_SECURED_REJOIN
      || status == EMBER_DEVICE_LEFT
      || status == EMBER_HIGH_SECURITY_SECURED_REJOIN) {
    joinDecision = EMBER_NO_ACTION;
  }

  securityJoinNotify(newNodeId,
                     newNodeEui64,
                     parentOfNewNode,
                     status,
                     joinDecision);
  return joinDecision;
}

static EmberStatus setJoinPolicy(EmberJoinDecision decision)
{
  defaultDecision = decision;
  return EMBER_SUCCESS;
}

static EmberStatus permitRequestingTrustCenterLinkKey(boolean allow)
{
  emberTrustCenterLinkKeyRequestPolicy = (allow
                                          ? EMBER_ALLOW_KEY_REQUESTS
                                          : EMBER_DENY_KEY_REQUESTS);
  return EMBER_SUCCESS;
}

static EmberStatus permitRequestingApplicationLinkKey(boolean allow)
{
  emberAppLinkKeyRequestPolicy = (allow
                                  ? EMBER_ALLOW_KEY_REQUESTS
                                  : EMBER_DENY_KEY_REQUESTS);
  return EMBER_SUCCESS;
}

#endif // EZSP_HOST

