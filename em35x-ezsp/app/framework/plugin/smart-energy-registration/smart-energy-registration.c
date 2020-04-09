// *****************************************************************************
// * smart-energy-registration.c
// *
// * This defines the state machine and procedure for a newly joined device to
// * perform the necessary steps to register in a network.
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include "app/framework/include/af.h"
#include "app/framework/util/af-main.h"                     //emberAfIsFullSmartEnergySecurityPresent
#include "app/util/zigbee-framework/zigbee-device-common.h" //emberBindRequest
#ifdef EZSP_HOST                                            //emberIeeeAddressRequest
  #include "app/util/zigbee-framework/zigbee-device-host.h"
#else //EZSP_HOST
  #include "stack/include/ember.h"
#endif //EZSP_HOST

#include "smart-energy-registration.h"
#include "app/framework/plugin/test-harness/test-harness.h"

EmberEventControl emAfPluginSmartEnergyRegistrationEventControl;

typedef enum {
  STATE_INITIAL,
  STATE_DISCOVER_KEY_ESTABLISHMENT_CLUSTER,
  STATE_PERFORM_KEY_ESTABLISHMENT,
#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
  STATE_DISCOVER_ENERGY_SERVICE_INTERFACES,
  STATE_DISCOVER_IEEE_ADDRESSES,
  STATE_PERFORM_PARTNER_LINK_KEY_EXCHANGE,
  STATE_PERFORM_BINDING,
  STATE_DETERMINE_AUTHORITATIVE_TIME_SOURCE,
#endif //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
  STATE_REGISTRATION_COMPLETE,
  STATE_REGISTRATION_FAILED,
} EmAfPluginSmartEnergyRegistrationState;
static EmAfPluginSmartEnergyRegistrationState state = STATE_INITIAL;
static int8u errors = 0;

#define UNDEFINED_ENDPOINT 0xFF
static int8u trustCenterKeyEstablishmentEndpoint = UNDEFINED_ENDPOINT;

#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
typedef struct {
  EmberEUI64 eui64;
  EmberNodeId nodeId;
  int8u endpoint;
} EmAfPluginSmartEnergyRegistrationEsi;
static EmAfPluginSmartEnergyRegistrationEsi esiTable[EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_TABLE_SIZE];
static int8u esiCount = 0;
static int8u esiIndex = 0;

typedef struct {
  boolean valid;
  int32u  time;
  int8u   timeStatus;
  int32u  lastSetTime;
  int32u  validUntilTime;
} EmAfPluginSmartEnergyRegistrationTimeSource;
static EmAfPluginSmartEnergyRegistrationTimeSource source;

#ifndef SE_PROFILE_ID
  #define SE_PROFILE_ID 0x0109
#endif

#define UNDEFINED_CLUSTER_ID 0xFFFF
static EmberAfClusterId clusterList[] = {
#ifdef ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT
  ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID,
#endif //ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT
#ifdef ZCL_USING_MESSAGING_CLUSTER_CLIENT
  ZCL_MESSAGING_CLUSTER_ID,
#endif //ZCL_USING_MESSAGING_CLUSTER_CLIENT
#ifdef ZCL_USING_PRICE_CLUSTER_CLIENT
  ZCL_PRICE_CLUSTER_ID,
#endif //ZCL_USING_PRICE_CLUSTER_CLIENT
  UNDEFINED_CLUSTER_ID,
};

#define NEXT_STATE STATE_DISCOVER_ENERGY_SERVICE_INTERFACES

#else //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED

  #define NEXT_STATE STATE_REGISTRATION_COMPLETE

#endif //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED

static boolean checkErrorCountAndSetEventControl(int32u delayMs, boolean errorFlag);
static boolean resumeAfterDelay(EmberStatus status, int32u delayMs);

#define resumeAfterFixedDelay(status) \
  resumeAfterDelay((status), \
                    EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_DELAY_RETRY)

#define transition(next) transitionAfterDelay((next), EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_DELAY_TRANSITION)
static boolean transitionAfterDelay(EmAfPluginSmartEnergyRegistrationState next,
                                    int32u delay);

static void performKeyEstablishment(void);

#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
  static void performPartnerLinkKeyExchange(void);
  static void partnerLinkKeyExchangeCallback(boolean success);
  static void performBinding(void);
  static void determineAuthoritativeTimeSource(void);
#endif //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED

static void stopRegistration(boolean success);

static void performDiscovery(void);
static void discoveryCallback(const EmberAfServiceDiscoveryResult *result);

//------------------------------------------------------------------------------

EmberStatus emberAfRegistrationStartCallback(void)
{
  if (state == STATE_REGISTRATION_COMPLETE) {
    // If we got called again after registration has already completed,
    // this means that it was due to a rejoin.  The trust center keepalive
    // may have initiated this rejoin due to a TC failure.
    emberAfTrustCenterKeepaliveUpdateCallback(TRUE);
    return EMBER_SUCCESS;
  }

  if (state != STATE_INITIAL) {
    return EMBER_INVALID_CALL;
  }

  if (!emAfTestHarnessAllowRegistration) {
    return EMBER_SECURITY_CONFIGURATION_INVALID;
  }

  // Registration is unnecessary for the trust center.  For other nodes, wait
  // for the network broadcast traffic to die down and neighbor information to
  // be populated before continuing.
  if (emberGetNodeId() == EMBER_TRUST_CENTER_NODE_ID) {
    transition(STATE_REGISTRATION_COMPLETE);
  } else {
    transitionAfterDelay(STATE_DISCOVER_KEY_ESTABLISHMENT_CLUSTER,
                         EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_DELAY_INITIAL);
  }
  emberAfAddToCurrentAppTasks(EMBER_AF_WAITING_FOR_REGISTRATION);
  return EMBER_SUCCESS;
}

void emberAfRegistrationAbortCallback(void)
{
  // We need registration to stop immediately because it may be started up again
  // in the same call chain.
  state = STATE_REGISTRATION_FAILED;
  emAfPluginSmartEnergyRegistrationTick();
}

void emAfPluginSmartEnergyRegistrationTick(void)
{
  emberEventControlSetInactive(emAfPluginSmartEnergyRegistrationEventControl);

  switch (state) {
  case STATE_INITIAL:
    emberAfRegistrationStartCallback();
    break;
  case STATE_DISCOVER_KEY_ESTABLISHMENT_CLUSTER:
    performDiscovery();
    break;
  case STATE_PERFORM_KEY_ESTABLISHMENT:
    performKeyEstablishment();
    break;
#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
  case STATE_DISCOVER_ENERGY_SERVICE_INTERFACES:
    performDiscovery();
    break;
  case STATE_DISCOVER_IEEE_ADDRESSES:
    performDiscovery();
    break;
  case STATE_PERFORM_PARTNER_LINK_KEY_EXCHANGE:
    performPartnerLinkKeyExchange();
    break;
  case STATE_PERFORM_BINDING:
    performBinding();
    break;
  case STATE_DETERMINE_AUTHORITATIVE_TIME_SOURCE:
    determineAuthoritativeTimeSource();
    break;
#endif //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
  case STATE_REGISTRATION_COMPLETE:
    // FALLTHROUGH
  case STATE_REGISTRATION_FAILED:
    stopRegistration(state == STATE_REGISTRATION_COMPLETE);
    break;
  default:
    emberAfRegistrationPrintln("ERR: Invalid state (0x%x)", state);
    emberAfRegistrationAbortCallback();
    break;
  }
}

int8u emAfPluginSmartEnergyRegistrationTrustCenterKeyEstablishmentEndpoint(void)
{
  return trustCenterKeyEstablishmentEndpoint;
}

static boolean checkErrorCountAndSetEventControl(int32u delayMs, boolean errorFlag)
{
  // Increment the error count if we're delaying due to an error; otherwise,
  // reset the error count so that failures in any particular state don't affect
  // subsequent states.
  if (errorFlag) {
    errors++;
    emberAfRegistrationPrintln("Registration error count %d of %d",
                               errors,
                               EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ERROR_LIMIT);
  } else {
    errors = 0;
  }
  if (errors >= EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ERROR_LIMIT) {
    emberAfRegistrationFlush();
    emberAfRegistrationPrintln("ERR: Aborting registration"
                               " because error limit reached (%d)",
                               EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ERROR_LIMIT);
    emberAfRegistrationAbortCallback();
    return FALSE;
  }

  if (delayMs == EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_DELAY_NONE) {
    emberEventControlSetActive(emAfPluginSmartEnergyRegistrationEventControl);
  } else {
    emberAfEventControlSetDelay(&emAfPluginSmartEnergyRegistrationEventControl,
                                delayMs);
  }
  return TRUE;
}

static boolean resumeAfterDelay(EmberStatus status, int32u delayMs)
{
  boolean errorFlag = (status != EMBER_SUCCESS);
  return checkErrorCountAndSetEventControl((errorFlag
                                            ? delayMs
                                            : EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_DELAY_RESUME),
                                           errorFlag);
}

static boolean transitionAfterDelay(EmAfPluginSmartEnergyRegistrationState next,
                                    int32u delay)
{
  state = next;
  return checkErrorCountAndSetEventControl(delay, FALSE);
}

static void performKeyEstablishment(void)
{
  EmberStatus status;
  emberAfRegistrationPrintln("Performing key establishment");

  // Transient failures may prevent us from performing key establishment.  If
  // so, we will try again later.
  status = emberAfInitiateKeyEstablishment(EMBER_TRUST_CENTER_NODE_ID,
                                           trustCenterKeyEstablishmentEndpoint);
  if (status != EMBER_SUCCESS) {
    emberAfRegistrationPrintln("ERR: Failed to start key establishment (0x%x)",
                               status);
    resumeAfterFixedDelay(status);
  }
}

boolean emberAfKeyEstablishmentCallback(EmberAfKeyEstablishmentNotifyMessage status,
                                        boolean amInitiator,
                                        EmberNodeId partnerShortId,
                                        int8u delayInSeconds)
{
  // The notification only matters if we are performing key establishment.
  if (state == STATE_PERFORM_KEY_ESTABLISHMENT) {
    if (status == LINK_KEY_ESTABLISHED) {
      transition(NEXT_STATE);
    } else if (status >= APP_NOTIFY_ERROR_CODE_START) {
      // We always bit shift by 10 (same as multiply by 1024) because we
      // want to avoid an actual 32-bit multiply, which is expensive on
      // the XAP.  1024 may not be the correct MILLISECOND_TICKS_PER_SECOND
      // value, but it is close enough.
      int32u delayMs = delayInSeconds << 10;
      emberAfRegistrationPrintln("ERR: Key establishment failed (0x%x)", status);
      resumeAfterDelay(EMBER_ERR_FATAL, 
                       delayMs);
    }
  }

  // Always allow key establishment to continue.
  return TRUE;
}

#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
static void performPartnerLinkKeyExchange(void)
{
  for (; esiIndex < esiCount; esiIndex++) {
    if (esiTable[esiIndex].nodeId != EMBER_TRUST_CENTER_NODE_ID) {
      EmberStatus status;
      emberAfRegistrationPrintln("Performing partner link key exchange"
                                 " with node 0x%2x endpoint 0x%x",
                                 esiTable[esiIndex].nodeId,
                                 esiTable[esiIndex].endpoint);
      status = emberAfInitiatePartnerLinkKeyExchange(esiTable[esiIndex].nodeId,
                                                     esiTable[esiIndex].endpoint,
                                                     partnerLinkKeyExchangeCallback);
      if (status != EMBER_SUCCESS) {
        emberAfRegistrationPrintln("ERR: Failed to initiate partner link key request"
                                   " with node 0x%2x endpoint 0x%x (0x%x)",
                                   esiTable[esiIndex].nodeId,
                                   esiTable[esiIndex].endpoint,
                                   status);
        resumeAfterFixedDelay(status);
      }
      return;
    }
  }

  esiIndex = 0;
  transition(STATE_PERFORM_BINDING);
}

static void partnerLinkKeyExchangeCallback(boolean success)
{
  if (state == STATE_PERFORM_PARTNER_LINK_KEY_EXCHANGE) {
    if (success) {
      emberAfRegistrationPrintln("Performed partner link key exchange"
                                 " with node 0x%2x endpoint 0x%x",
                                 esiTable[esiIndex].nodeId,
                                 esiTable[esiIndex].endpoint);
      esiIndex++;
    } else {
      emberAfRegistrationPrintln("ERR: Failed to perform partner link key exchange"
                                 " with node 0x%2x endpoint 0x%x",
                                 esiTable[esiIndex].nodeId,
                                 esiTable[esiIndex].endpoint);
    }
    resumeAfterFixedDelay(success
                          ? EMBER_SUCCESS
                          : EMBER_ERR_FATAL);
  }
}

static void performBinding(void)
{
  static int8u endpointIndex = 0;
  static int8u clusterIndex  = 0;
  EmberEUI64 eui64;

  emberAfGetEui64(eui64);

  // The spec requires that we bind in order to inform the ESI that we want
  // unsolicited updates, but the ESI is not required to use binding and may
  // send a negative response.  In addition, there is no recourse if a binding
  // is required but the ESI refuses.  So, send the bindings, but don't pay
  // attention to whether is works or not.
  for (; esiIndex < esiCount; esiIndex++) {
    for (; endpointIndex < emberAfEndpointCount(); endpointIndex++) {
      int8u endpoint = emberAfEndpointFromIndex(endpointIndex);
      for (; clusterList[clusterIndex] != UNDEFINED_CLUSTER_ID; clusterIndex++) {
        EmberAfClusterId clusterId = clusterList[clusterIndex];
        if (emberAfContainsClient(endpoint, clusterId)) {
          EmberStatus status;
          emberAfRegistrationPrintln("Performing binding"
                                     " to node 0x%2x endpoint 0x%x"
                                     " from endpoint 0x%x"
                                     " for cluster 0x%2x",
                                     esiTable[esiIndex].nodeId,
                                     esiTable[esiIndex].endpoint,
                                     endpoint,
                                     clusterId);
          status = emberBindRequest(esiTable[esiIndex].nodeId,
                                    esiTable[esiIndex].eui64,
                                    esiTable[esiIndex].endpoint,
                                    clusterId,
                                    UNICAST_BINDING,
                                    eui64,
                                    0, // multicast group identifier - ignored
                                    endpoint,
                                    EMBER_AF_DEFAULT_APS_OPTIONS);
          if (status == EMBER_SUCCESS) {
            clusterIndex++;
          } else {
            emberAfRegistrationPrintln("ERR: Failed to send bind request"
                                       " to node 0x%2x endpoint 0x%x"
                                       " from endpoint 0x%x"
                                       " for cluster 0x%2x (0x%x)",
                                       esiTable[esiIndex].nodeId,
                                       esiTable[esiIndex].endpoint,
                                       endpoint,
                                       clusterId,
                                       status);
          }

          // We may hit the error limit if we delay here due to an error.  If
          // so, we have to clear our internal static indices; otherwise, when
          // registration is restarted, we won't pick up from the beginning.
          if (!resumeAfterFixedDelay(status)) {
            endpointIndex = clusterIndex = 0;
          }
          return;
        }
      }
      clusterIndex = 0;
    }
    endpointIndex = 0;
  }

  esiIndex = 0;
  transition(STATE_DETERMINE_AUTHORITATIVE_TIME_SOURCE);
}

static void determineAuthoritativeTimeSource(void)
{
  static boolean resuming = FALSE;
  int8u attributeIds[] = {
    LOW_BYTE(ZCL_TIME_ATTRIBUTE_ID),             HIGH_BYTE(ZCL_TIME_ATTRIBUTE_ID),
    LOW_BYTE(ZCL_TIME_STATUS_ATTRIBUTE_ID),      HIGH_BYTE(ZCL_TIME_STATUS_ATTRIBUTE_ID),
    LOW_BYTE(ZCL_LAST_SET_TIME_ATTRIBUTE_ID),    HIGH_BYTE(ZCL_LAST_SET_TIME_ATTRIBUTE_ID),
    LOW_BYTE(ZCL_VALID_UNTIL_TIME_ATTRIBUTE_ID), HIGH_BYTE(ZCL_VALID_UNTIL_TIME_ATTRIBUTE_ID),
  };

  if (!resuming) {
    emberAfRegistrationPrintln("Determining authoritative time source");
    source.valid = FALSE;
  }

  while (esiIndex < esiCount) {
    EmberStatus status;
    emberAfRegistrationPrintln("Requesting time attributes"
                               " from node 0x%2x endpoint 0x%x",
                               esiTable[esiIndex].nodeId,
                               esiTable[esiIndex].endpoint);

    emberAfFillCommandGlobalClientToServerReadAttributes(ZCL_TIME_CLUSTER_ID,
                                                         attributeIds,
                                                         sizeof(attributeIds));
    emberAfGetCommandApsFrame()->sourceEndpoint = emberAfEndpointFromIndex(0);
    emberAfGetCommandApsFrame()->destinationEndpoint = esiTable[esiIndex].endpoint;
    status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,
                                       esiTable[esiIndex].nodeId);
    if (status == EMBER_SUCCESS) {
      esiIndex++;
      if (esiIndex == esiCount) {
        resuming = transitionAfterDelay(STATE_DETERMINE_AUTHORITATIVE_TIME_SOURCE,
                                        EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_DELAY_BRIEF);
        return;
      }
    } else {
      emberAfRegistrationPrintln("ERR: Failed to request time attributes"
                                 " from node 0x%2x endpoint 0x%x (0x%x)",
                                 esiTable[esiIndex].nodeId,
                                 esiTable[esiIndex].endpoint,
                                 status);
    }
    resuming = resumeAfterFixedDelay(status);
    return;
  }

  if (!source.valid) {
    emberAfRegistrationPrintln("ERR: Failed to determine"
                               " authoritative time source");
    resuming = resumeAfterFixedDelay(EMBER_ERR_FATAL);
  } else {
    emberAfRegistrationPrintln("Determined authoritative time source");
    esiIndex = 0;
    transition(STATE_REGISTRATION_COMPLETE);
  }
}

void emAfPluginSmartEnergyRegistrationReadAttributesResponseCallback(int8u *buffer,
                                                                     int16u bufLen)
{
  int32u time           = 0x00000000UL;
  int8u  timeStatus     = 0x00;
  int32u lastSetTime    = 0x00000000UL;
  int32u validUntilTime = 0xFFFFFFFFUL;
  int16u bufIndex = 0;

  if (state != STATE_DETERMINE_AUTHORITATIVE_TIME_SOURCE) {
    return;
  }

  // Each record in the response has a two-byte attribute id and a one-byte
  // status.  If the status is SUCCESS, there will also be a one-byte type and
  // variable-length data.
  while (bufIndex + 3 <= bufLen) {
    EmberAfAttributeId attributeId;
    EmberAfStatus status;
    attributeId = (EmberAfAttributeId)emberAfGetInt16u(buffer, bufIndex, bufLen);
    bufIndex += 2;
    status = (EmberAfStatus)emberAfGetInt8u(buffer, bufIndex, bufLen);
    bufIndex++;

    if (status == EMBER_ZCL_STATUS_SUCCESS) {
      EmberAfAttributeType type;
      type = (EmberAfAttributeType)emberAfGetInt8u(buffer, bufIndex, bufLen);
      bufIndex++;

      switch (attributeId) {
      case ZCL_TIME_ATTRIBUTE_ID:
        time = emberAfGetInt32u(buffer, bufIndex, bufLen);
        break;
      case ZCL_TIME_STATUS_ATTRIBUTE_ID:
        timeStatus = emberAfGetInt8u(buffer, bufIndex, bufLen);
        break;
      case ZCL_LAST_SET_TIME_ATTRIBUTE_ID:
        lastSetTime = emberAfGetInt32u(buffer, bufIndex, bufLen);
        break;
      case ZCL_VALID_UNTIL_TIME_ATTRIBUTE_ID:
        validUntilTime = emberAfGetInt32u(buffer, bufIndex, bufLen);
        break;
      }

      bufIndex += (emberAfIsThisDataTypeAStringType(type)
                   ? emberAfStringLength(buffer + bufIndex) + 1
                   : emberAfGetDataSize(type));
    }
  }

  // The process for determining the most authoritative time source is outlined
  // in section 5.7.2 of 105638r09, but the procedure is currently confusing and
  // and possibly incorrect.  This algorithm follows the spec, except that it
  // does not distinquish between Master and Synchronized servers.  Also, the
  // spec mentions "most recent LastSetTime" but does not define what it means.
  // Elapsed time since LastSetTime is used as the measure of "most recent
  // LastSetTime."
  if ((timeStatus & BIT(0)
       || timeStatus & BIT(1))
      && lastSetTime < time
      && time < validUntilTime
      && (!source.valid
          || (elapsedTimeInt32u(lastSetTime, time)
              < elapsedTimeInt32u(source.lastSetTime, source.time)))) {
    source.valid          = TRUE;
    source.time           = time;
    source.timeStatus     = timeStatus;
    source.lastSetTime    = lastSetTime;
    source.validUntilTime = validUntilTime;
    emberAfSetTime(time);
  }
}
#endif //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED

static void stopRegistration(boolean success)
{
  emberAfRemoveFromCurrentAppTasks(EMBER_AF_WAITING_FOR_REGISTRATION);
  emberAfRegistrationCallback(success);

  emberAfTrustCenterKeepaliveUpdateCallback(success);

#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_DELAY_PERIOD
  if (success) {
    transitionAfterDelay(STATE_INITIAL,
                         EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_DELAY_PERIOD);
    return;
  }
#endif //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_DELAY_PERIOD
  state = STATE_INITIAL;
}

static void performDiscovery(void)
{
  EmberStatus status;
  EmberNodeId target;
  EmberAfClusterId clusterId;

  // When performing key establishment, search the trust center for the Key
  // Establishment cluster.  When searching for ESIs, broadcast for the DRLC
  // server cluster, which only ESIs should have.
  if (state == STATE_DISCOVER_KEY_ESTABLISHMENT_CLUSTER) {
    emberAfRegistrationPrintln("Discovering Key Establishment cluster");
    trustCenterKeyEstablishmentEndpoint = UNDEFINED_ENDPOINT;
    target = EMBER_TRUST_CENTER_NODE_ID;
    clusterId = ZCL_KEY_ESTABLISHMENT_CLUSTER_ID;
#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
  } else if (state == STATE_DISCOVER_ENERGY_SERVICE_INTERFACES) {
    emberAfRegistrationPrintln("Discovering Energy Service Interfaces");
    esiCount = esiIndex = 0;
    target = EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS;
    clusterId = ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID;
  } else if (state == STATE_DISCOVER_IEEE_ADDRESSES) {
    emberAfRegistrationPrintln("Discovering IEEE address"
                               " for node 0x%2x",
                               esiTable[esiIndex].nodeId);
    status = emberAfFindIeeeAddress(esiTable[esiIndex].nodeId,
                                    discoveryCallback);
    goto kickout;
#endif //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
  } else {
    emberAfRegistrationPrintln("ERR: Invalid state for discovery (0x%x)", state);
    emberAfRegistrationAbortCallback();
    return;
  }

  // Transient failures may prevent us from performing discovery.  If so, we
  // will try again later.
  status = emberAfFindDevicesByProfileAndCluster(target,
                                                 SE_PROFILE_ID,
                                                 clusterId,
                                                 EMBER_AF_SERVER_CLUSTER_DISCOVERY,
                                                 discoveryCallback);
#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
kickout:
#endif //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
  if (status != EMBER_SUCCESS) {
    emberAfRegistrationPrintln("ERR: Failed to start discovery (0x%x)", status);
    resumeAfterFixedDelay(status);
  }
}

static void discoveryCallback(const EmberAfServiceDiscoveryResult *result)
{
  if (emberAfHaveDiscoveryResponseStatus(result->status)) {
    if (result->zdoRequestClusterId == MATCH_DESCRIPTORS_REQUEST) {
      const EmberAfEndpointList* endpointList = (const EmberAfEndpointList *)result->responseData;
      int8u i;
      for (i = 0; i < endpointList->count; i++) {
        if (state == STATE_DISCOVER_KEY_ESTABLISHMENT_CLUSTER) {
          // Key Establishment is global to the device so we can ignore anything
          // beyond the first endpoint that responds.
          if (trustCenterKeyEstablishmentEndpoint == UNDEFINED_ENDPOINT) {
            emberAfRegistrationPrintln("Discovered Key Establishment cluster"
                                       " on endpoint 0x%x",
                                       endpointList->list[i]);
            trustCenterKeyEstablishmentEndpoint = endpointList->list[i];
          } else {
            emberAfRegistrationPrintln("INFO: Ignored Key Establishment cluster"
                                       " on endpoint 0x%x",
                                       endpointList->list[i]);
          }
#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
        } else if (state == STATE_DISCOVER_ENERGY_SERVICE_INTERFACES) {
          emberAfRegistrationPrintln("Discovered Energy Server Interface"
                                     " on node 0x%2x endpoint 0x%x",
                                     result->matchAddress,
                                     endpointList->list[i]);
          if (esiCount
              < EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_TABLE_SIZE) {
            esiTable[esiCount].nodeId = result->matchAddress;
            esiTable[esiCount].endpoint = endpointList->list[i];
            esiCount++;
          } else {
            emberAfRegistrationPrintln("INFO: Ignored Energy Server Interface"
                                       " on node 0x%2x endpoint 0x%x"
                                       " because table is full",
                                       result->matchAddress,
                                       endpointList->list[i]);
          }
#endif //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
        }
      }
    }
  }

  if (state == STATE_DISCOVER_KEY_ESTABLISHMENT_CLUSTER) {
    if (trustCenterKeyEstablishmentEndpoint == UNDEFINED_ENDPOINT) {
      emberAfRegistrationPrintln("ERR: Failed to find Key Establishment cluster");
      resumeAfterFixedDelay(EMBER_ERR_FATAL);
    } else {
      EmberKeyStruct keyStruct;
      if (emberGetKey(EMBER_TRUST_CENTER_LINK_KEY, &keyStruct)
          != EMBER_SUCCESS) {
        emberAfRegistrationPrintln("ERR: Failed to get trust center link key");
        emberAfRegistrationAbortCallback();
        return;
      }

      // If we don't have full Smart Energy Security or if the key is already
      // authorized, we can skip key establishment and move on to ESI discovery.
      if (!emberAfIsFullSmartEnergySecurityPresent()) {
        emberAfRegistrationFlush();
        emberAfRegistrationPrintln("WARN: Skipping key establishment"
                                   " due to missing libraries or certificate"
                                   " - see 'info' command for more detail");
        emberAfRegistrationFlush();
        transition(NEXT_STATE);
      } else if (keyStruct.bitmask & EMBER_KEY_IS_AUTHORIZED) {
        emberAfRegistrationPrintln("Skipping key establishment"
                                   " because key is already authorized");
        transition(NEXT_STATE);
      } else {
        transition(STATE_PERFORM_KEY_ESTABLISHMENT);
      }
    }
#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
  } else if (state == STATE_DISCOVER_ENERGY_SERVICE_INTERFACES) {
    if (result->status == EMBER_AF_BROADCAST_SERVICE_DISCOVERY_COMPLETE) {
      if (esiCount == 0) {
        emberAfRegistrationPrintln("ERR: Failed to find Energy Service Interfaces");
        resumeAfterFixedDelay(EMBER_ERR_FATAL);
      } else {
        transition(STATE_DISCOVER_IEEE_ADDRESSES);
      }
    }
  } else if (state == STATE_DISCOVER_IEEE_ADDRESSES) {
    if (result->status == EMBER_AF_UNICAST_SERVICE_DISCOVERY_COMPLETE_WITH_RESPONSE) {
      emberAfRegistrationPrintln("Discovered IEEE address"
                                 " for node 0x%2x",
                                 esiTable[esiIndex].nodeId);
      MEMCOPY(esiTable[esiIndex].eui64, result->responseData, EUI64_SIZE);
      if ((emberAfAddAddressTableEntry(esiTable[esiIndex].eui64,
                                       esiTable[esiIndex].nodeId))
          == EMBER_NULL_ADDRESS_TABLE_INDEX) {
        emberAfRegistrationPrintln("WARN: Could not add address table entry"
                                   " for node 0x%2x",
                                   esiTable[esiIndex].nodeId);
      }
      esiIndex++;
      if (esiIndex == esiCount) {
        esiIndex = 0;
        transition(STATE_PERFORM_PARTNER_LINK_KEY_EXCHANGE);
      } else {
        resumeAfterFixedDelay(EMBER_SUCCESS);
      }
    } else {
      emberAfRegistrationPrintln("ERR: Failed to discover IEEE address"
                                 " for node 0x%2x",
                                 esiTable[esiIndex].nodeId);
      resumeAfterFixedDelay(EMBER_ERR_FATAL);
    }
#endif //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
  }
}
