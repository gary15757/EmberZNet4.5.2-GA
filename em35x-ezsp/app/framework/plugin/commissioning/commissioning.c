// *******************************************************************
// * commissioning.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "app/framework/include/af.h"
#include "app/framework/security/af-security.h"
#include "app/util/common/form-and-join.h"

static int8u startupControl;
static EmberEUI64 globalEPID;
static int8u scanAttempts;

static EmberAfStatus formNetwork(int8u endpoint);
static EmberAfStatus findNetwork(int8u endpoint);

void emberAfCommissioningClusterServerInitCallback(int8u endpoint)
{
  scanAttempts = 0;
  emberAfScheduleClusterTick(endpoint,
                             ZCL_COMMISSIONING_CLUSTER_ID,
                             EMBER_AF_SERVER_CLUSTER_TICK,
                             MILLISECOND_TICKS_PER_SECOND,
                             EMBER_AF_OK_TO_HIBERNATE);
}

// This function should be called once every second
void emberAfCommissioningClusterServerTickCallback(int8u endpoint)
{
  EmberAfStatus status;
  EmberNetworkStatus networkState;

  // If we're on a network or joining, get out.
  networkState = emberNetworkState();
  if (networkState == EMBER_JOINED_NETWORK
      || networkState == EMBER_JOINING_NETWORK) {
    return;
  }

  status = emberAfReadAttribute(endpoint,
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_STARTUP_CONTROL_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&startupControl,
                                sizeof(startupControl),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading startup control %x",
                                       status);
    return;
  }

  switch (startupControl) {
  case EMBER_ZCL_COMMISSIONING_STARTUP_CONTROL_NO_ACTION:
    // We are part of a network, do nothing
    break;
  case EMBER_ZCL_COMMISSIONING_STARTUP_CONTROL_FORM_NETWORK:
    // We should form a network
    formNetwork(endpoint);
    break;
  case EMBER_ZCL_COMMISSIONING_STARTUP_CONTROL_REJOIN_NETWORK:
    // We should try to find a network based on epid.
    findNetwork(endpoint);
    break;
  case EMBER_ZCL_COMMISSIONING_STARTUP_CONTROL_START_FROM_SCRATCH:
    // Start from scratch
    emberLeaveNetwork();
    halReboot();
    break;
  default:
    emberAfCommissioningClusterPrintln("ERR: unrecog startup control %x",
                                       startupControl);
    break;
  }

  // reschedule the tick
  emberAfScheduleClusterTick(endpoint,
                             ZCL_COMMISSIONING_CLUSTER_ID,
                             EMBER_AF_SERVER_CLUSTER_TICK,
                             MILLISECOND_TICKS_PER_SECOND,
                             EMBER_AF_OK_TO_HIBERNATE);
}

// This function does all the work. Reads startup parameters stored in the
// commissioning cluster attributes, and uses them to commission the network.
boolean emberAfCommissioningClusterRestartDeviceCallback(int8u options,
                                                         int8u delay,
                                                         int8u jitter)
{
  EmberStatus emStatus;
  EmberAfStatus status;
  int8u startupControl;
  EmberNetworkParameters networkParameters;
  EmberInitialSecurityState initialSecurityState;

  emberAfCommissioningClusterPrintln("RX: RestartDevice 0x%x, 0x%x, 0x%x",
                                     options,
                                     delay,
                                     jitter);

  // TODO: Consider options, delay, and jitter.

  // Read the startup control byte
  status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_STARTUP_CONTROL_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&startupControl,
                                sizeof(startupControl),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading startup control %x",
                                       status);
    goto failure;
  }

  // For form, rejoin, or start from scratch, send a success, leave, and let the
  // tick handle the work.
  if (startupControl != EMBER_ZCL_COMMISSIONING_STARTUP_CONTROL_NO_ACTION) {
    scanAttempts = 0;
    emberAfFillCommandCommissioningClusterRestartDeviceResponse(EMBER_ZCL_STATUS_SUCCESS);
    emberAfSendResponse();
    emberLeaveNetwork();
    return TRUE;
  }

  // Read all the appropriate network parameters, if we don't have one of the
  // attributes we need we should bail with an error.
  status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_EXTENDED_PAN_ID_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)networkParameters.extendedPanId,
                                sizeof(networkParameters.extendedPanId),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading extended pan id %x",
                                       status);
    goto failure;
  }

  status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_PAN_ID_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&networkParameters.panId,
                                sizeof(networkParameters.panId),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading pan id %x", status);
    goto failure;
  }

  status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_CHANNEL_MASK_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&networkParameters.channels,
                                sizeof(networkParameters.channels),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading channel mask %x", status);
    goto failure;
  }

  status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_NETWORK_MANAGER_ADDRESS_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&networkParameters.nwkManagerId,
                                sizeof(networkParameters.nwkManagerId),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading network manager address %x",
                                       status);
    goto failure;
  }

  status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_PRECONFIGURED_LINK_KEY_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&initialSecurityState.preconfiguredKey,
                                sizeof(initialSecurityState.preconfiguredKey),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading preconfigured link key %x",
                                       status);
    goto failure;
  }

  status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_NETWORK_KEY_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&initialSecurityState.networkKey,
                                sizeof(initialSecurityState.networkKey),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading network key %x", status);
    goto failure;
  }

  status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_NETWORK_KEY_SEQUENCE_NUMBER_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&initialSecurityState.networkKeySequenceNumber,
                                sizeof(initialSecurityState.networkKeySequenceNumber),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading network key sequence number %x",
                                       status);
    goto failure;
  }

  status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_TRUST_CENTER_ADDRESS_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)initialSecurityState.preconfiguredTrustCenterEui64,
                                sizeof(initialSecurityState.preconfiguredTrustCenterEui64),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading trust center address %x",
                                       status);
    goto failure;
  }

  // If we made it this far, reading attributes, we can run the network
  // setup proceedures with the values we have pulled from attributes.  Send
  // a response and leave the current network first.  If anything goes wrong,
  // we can't do anything because we'll be off the network.
  emberAfFillCommandCommissioningClusterRestartDeviceResponse(EMBER_ZCL_STATUS_SUCCESS);
  emberAfSendResponse();
  emberLeaveNetwork();

  emStatus = emberSetInitialSecurityState(&initialSecurityState);
  if (emStatus != EMBER_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: setting initial security state %x",
                                       emStatus);
    return TRUE;
  }

  emStatus = emberAfJoinNetwork(&networkParameters);
  if (emStatus != EMBER_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: joining network %x", emStatus);
  }

  return TRUE;

failure:
  emberAfFillCommandCommissioningClusterRestartDeviceResponse(EMBER_ZCL_STATUS_INCONSISTENT_STARTUP_STATE);
  emberAfSendResponse();
  return TRUE;
}

boolean emberAfCommissioningClusterResetStartupParametersCallback(int8u options,
                                                                  int8u index)
{
  // Since none of our attributes are held in flash, the easiest way to reset
  // the startup paramebers held in the attributes table is to simply reset the
  // device.
  emberAfCommissioningClusterPrintln("RX: ResetStartupParameters 0x%x, 0x%x",
                                     options,
                                     index);
  emberAfCorePrintln("Reset requested, restarting device.");
  // The reponse to a Reset Startup Parameters command is always a Reset Startup
  // Parameters Response with status SUCCESS.  Because we're rebooting here, we
  // have to send the response immediately.
  emberAfFillCommandCommissioningClusterResetStartupParametersResponse(EMBER_ZCL_STATUS_SUCCESS);
  emberAfSendResponse();
  halReboot();
  return TRUE;
}

static EmberAfStatus formNetwork(int8u endpoint)
{
  EmberAfStatus status;
  int32u channelMask;

  if (emberFormAndJoinIsScanning()) {
    return EMBER_ZCL_STATUS_SUCCESS;
  }

  //get the scan channel mask and the extended pan id
  status = emberAfReadAttribute(endpoint,
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_CHANNEL_MASK_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&channelMask,
                                sizeof(channelMask),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading channel mask %x", status);
    return status;
  }

  emberScanForUnusedPanId(channelMask, EMBER_AF_PLUGIN_COMMISSIONING_DURATION);
  return EMBER_ZCL_STATUS_SUCCESS;
}

static EmberAfStatus findNetwork(int8u endpoint)
{
  EmberAfStatus status;
  int32u channelMask;
  int8u scanAttemptLimit;

  if (emberFormAndJoinIsScanning()) {
    return EMBER_ZCL_STATUS_SUCCESS;
  }

  status = emberAfReadAttribute(endpoint,
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_SCAN_ATTEMPTS_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&scanAttemptLimit,
                                sizeof(scanAttemptLimit),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading scan attempts %x", status);
    return status;
  } else if (scanAttempts >= scanAttemptLimit) {
    emberAfDebugPrintln("scan limit reached %x", scanAttempts);
    return status;
  }

  status = emberAfReadAttribute(endpoint,
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_CHANNEL_MASK_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&channelMask,
                                sizeof(channelMask),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading channel mask %x", status);
    return status;
  }

  status = emberAfReadAttribute(endpoint,
                                ZCL_COMMISSIONING_CLUSTER_ID,
                                ZCL_EXTENDED_PAN_ID_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                globalEPID,
                                sizeof(globalEPID),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfCommissioningClusterPrintln("ERR: reading extended pan id %x",
                                       status);
    return status;
  }

  emberAfCommissioningClusterPrintln("scan for commissioning network...");
  emberScanForJoinableNetwork(channelMask, globalEPID);
  scanAttempts++;
  return EMBER_ZCL_STATUS_SUCCESS;
}

void emberAfUnusedPanIdFoundCallback(EmberPanId panId, int8u channel)
{
  EmberNetworkParameters np;
  EmberStatus status;

  emberAfCommissioningClusterPrintln("unused found: %2x %x", panId, channel);

  if (startupControl == EMBER_ZCL_COMMISSIONING_STARTUP_CONTROL_FORM_NETWORK) {
    MEMCOPY(np.extendedPanId, (int8u *)globalEPID, EUI64_SIZE);
    np.panId = panId;
    np.radioChannel = channel;
    np.radioTxPower = EMBER_AF_RADIO_POWER;

    status = emberAfFormNetwork(&np);
    if (status != EMBER_SUCCESS) {
      emberAfCommissioningClusterPrintln("ERR: forming network %x", status);
    }
  }
}

void emberAfJoinableNetworkFoundCallback(EmberZigbeeNetwork *networkFound,
                                         int8u lqi,
                                         int8s rssi)
{
  EmberNetworkParameters np;
  EmberStatus status;

  emberAfCommissioningClusterPrintln("Found joinable network...");

  if (startupControl == EMBER_ZCL_COMMISSIONING_STARTUP_CONTROL_REJOIN_NETWORK) {
    MEMCOPY(np.extendedPanId, networkFound->extendedPanId, EUI64_SIZE);
    np.panId = networkFound->panId;
    np.radioChannel = networkFound->channel;
    np.radioTxPower = EMBER_AF_RADIO_POWER;
    np.joinMethod = EMBER_USE_MAC_ASSOCIATION;

    status = emberAfJoinNetwork(&np);
    if (status != EMBER_SUCCESS) {
      emberAfCommissioningClusterPrintln("ERR: joining network %x", status);
    }
  }
}

void emberAfScanErrorCallback(EmberStatus status)
{
  emberAfDebugPrintln("ERR: scanning %x", status);
}

void emberAfContinueJoinableNetworkSearchCallback(void)
{
  emberScanForNextJoinableNetwork();
}
