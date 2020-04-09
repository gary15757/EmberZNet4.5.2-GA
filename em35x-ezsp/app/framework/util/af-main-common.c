// *******************************************************************
// * af-main-common.c
// *
// * Code common to both the Host and SOC (system on a chip) versions
// * of the Application Framework.
// *
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include PLATFORM_HEADER     // Micro and compiler specific typedefs and macros

#if defined EZSP_HOST
  #include "stack/include/ember-types.h"
  #include "stack/include/error.h"
  #include "stack/include/library.h"
#else
  // Ember stack and related utilities
  #include "stack/include/ember.h"         // Main stack definitions
  #include "stack/include/cbke-crypto-engine.h"
#endif

// HAL - hardware abstraction layer
#include "hal/hal.h"
#include "app/util/serial/serial.h"  // Serial utility APIs

// CLI - command line interface
#include "app/util/serial/command-interpreter2.h"

#if defined EZSP_HOST
  // EZSP - ember serial host protocol
  #include "app/util/ezsp/ezsp-protocol.h"
  #include "app/util/ezsp/ezsp.h"
  #include "app/util/ezsp/serial-interface.h"
  #include "app/util/ezsp/ezsp-utils.h"
#endif

// Network Utilities (form, join and associated scan code)
#include "app/util/common/form-and-join.h"

// Concentrator library
#include "app/util/concentrator/concentrator.h"

// Fragmentation.
#include "app/framework/util/fragmentation.h"

// Service discovery library
#include "service-discovery.h"

// determines the number of in-clusters and out-clusters based on defines
// in config.h
#include "af-main.h"

#include "attribute-storage.h"
#include "attribute-table.h"
#include "util.h"
#include "app/framework/cli/zcl-cli.h"
#include "app/framework/gen/callback.h"
#include "print.h"
#include "config.h"
#include "app/framework/security/af-security.h"
#include "app/framework/security/crypto-state.h"
#include "app/framework/report/report-table.h"

// Querying the Ember Stack for what libraries are present.
#include "app/util/common/library.h"

// ZDO - ZigBee Device Object
#include "app/util/zigbee-framework/zigbee-device-common.h"

#include "app/framework/plugin/partner-link-key-exchange/partner-link-key-exchange.h"
#include "app/framework/plugin/ota-storage-common/ota-storage.h"

//------------------------------------------------------------------------------

#ifdef EMBER_AF_USE_BUTTONS
// variables turned on in an ISR when a button is pressed
boolean emberAfFirstButtonPressed;
boolean emberAfSecondButtonPressed;
#endif //EMBER_AF_USE_BUTTONS

// flags the user can turn on or off to make the printing behave differently
boolean emberAfPrintReceivedMessages = TRUE;

int8u emAfExtendedPanId[EXTENDED_PAN_ID_SIZE] = ZA_EXTENDED_PANID;

PGM EmberAfOtaImageId emberAfInvalidImageId = INVALID_OTA_IMAGE_ID;

EmberEventControl emAfMoveEventControl;
int8u emAfMoveAttempts = 0;

// For testing purposes only, we suppress the normal call to emberNetworkInit()
// at reboot.  This allows us to call it manually later and prevent the node from
// immediately coming back up on the network after reboot.
#if defined(EMBER_AF_TC_SWAP_OUT_TEST)
  EmberStatus emAfNetworkInitReturnCodeStatus = EMBER_NOT_JOINED;
  #define networkInit() emAfNetworkInitReturnCodeStatus

#else
  #define networkInit() emberNetworkInit()
#endif

//------------------------------------------------------------------------------
// Forward declarations
void emAfScheduleMoveEvent(void);

/**
 * @brief Returns true if the device is scheduled to attempt a move
 */
#define emberAfMoveInProgress() emberEventControlGetActive(emAfMoveEventControl)

boolean emberAfStartMove(void) {
  if (!emberAfMoveInProgress()) {
    emAfScheduleMoveEvent();
    return TRUE;
  }
  return FALSE;
}

/**
 * @brief Ceases the process of attempting to move to a new channel.
 */
void emberAfStopMove(void) {
  emberEventControlSetInactive(emAfMoveEventControl);
}

// Schedules or reschedules the move event
void emAfScheduleMoveEvent(void) {
  if (EMBER_AF_REJOIN_ATTEMPTS_MAX == 0xff ||
      emAfMoveAttempts < EMBER_AF_REJOIN_ATTEMPTS_MAX) {
    emberAfAppPrintln("Schedule move: %x", emAfMoveAttempts);    
    emberEventControlSetDelayQS(emAfMoveEventControl, 
              ((emAfMoveAttempts == 0) ? 0 : 40)); //try in 10 sec.
  } else {
    emberAfAppPrintln("Move limit reached: %x", emAfMoveAttempts);    
    emberAfStopMove();
  }
}

// The actual move event.
void emAfMoveEvent(void) {
  EmberStatus status;
  boolean secure = (emAfMoveAttempts == 0);
  int32u channels = ((emAfMoveAttempts == 0) ? 0 : 
                      EMBER_ALL_802_15_4_CHANNELS_MASK); 
  status = emberFindAndRejoinNetwork(secure, channels);
  emberAfDebugPrintln("Move attempt %x, status: %x", emAfMoveAttempts, status);
  emAfMoveAttempts++;
  emAfScheduleMoveEvent();
}


boolean emberAfIsFullSmartEnergySecurityPresent(void)
{
#if defined SE_SECURITY_PROFILE_ENABLED
  EmberCertificateData cert;
  if ((emberGetLibraryStatus(EMBER_ECC_LIBRARY_ID)
       & EMBER_LIBRARY_PRESENT_MASK)
      && (EMBER_SUCCESS == emberGetCertificate(&cert)) ) {
    return TRUE;
  }
#endif
  return FALSE;
}

EmberStatus emberAfSendInterPan(EmberPanId panId,
                                const EmberEUI64 eui64,
                                EmberNodeId nodeId,
                                EmberMulticastId multicastId,
                                EmberAfClusterId clusterId,
                                EmberAfProfileId profileId,
                                int16u messageLength,
                                int8u* messageBytes)
{
  EmberAfInterpanHeader header;
  MEMSET(&header, 0, sizeof(EmberAfInterpanHeader));
  header.panId = panId;
  header.shortAddress = nodeId;
  if (eui64 != NULL) {
    MEMCOPY(header.longAddress, eui64, EUI64_SIZE);
    header.options |= EMBER_AF_INTERPAN_OPTION_MAC_HAS_LONG_ADDRESS;
    header.messageType = INTER_PAN_UNICAST;
  } else {
    header.messageType = (nodeId < EMBER_BROADCAST_ADDRESS
                          ? INTER_PAN_UNICAST
                          : INTER_PAN_BROADCAST);
  }
  header.profileId = profileId;
  header.clusterId = clusterId;
  header.groupId = multicastId;
  return emberAfInterpanSendMessageCallback(&header,
                                            messageLength,
                                            messageBytes);
}

void emberAfPrintMessageData(int8u* data, int16u length)
{
#if defined EMBER_AF_PRINT_APP
  emberAfAppPrint(" payload (len %2x) [", length); 
  emberAfAppPrintBuffer(data, length, TRUE);
  emberAfAppPrintln("]"); 
#endif
}

static boolean checkMinimumLength(int16u minimum, int16u length)
{
  if (length < minimum) {
    emberAfDebugPrintln("Err: msg too short (<%d)", minimum);
    return FALSE;
  }
  return TRUE;
}


void emberAfPrintIncomingZclMessage(int8u endpoint,
                                    int16u clusterId,
                                    int8u* message,
                                    int16u len)
{
#ifdef EMBER_AF_PRINT_APP

  int8u zclFrameControl, zclSeqNum, zclCmd;
  int16u mfgId = 0;
  boolean isMfgSpecific = FALSE;

  if (!checkMinimumLength(3, len)) {
    return;
  }

  // get the ZCL header info
  zclFrameControl = message[0];
  if (zclFrameControl & ZCL_MANUFACTURER_SPECIFIC_MASK) {
    isMfgSpecific = TRUE;
    if (!checkMinimumLength(5, len)) {
      return;
    }
    mfgId = (message[2] << 8) + message[1];
    zclSeqNum = message[3];
    zclCmd = message[4];
  } else {
    zclSeqNum = message[1];
    zclCmd = message[2];
  }

  // print the ZCL details message if message printing is on
  if (emberAfPrintReceivedMessages == TRUE) {
    emberAfAppPrint("\r\nT%4x:", emberAfGetCurrentTime());
    emberAfAppPrint("RX len %d, ep %x, clus 0x%2x ", 
                    len, 
                    endpoint,
                    clusterId);

    emberAfAppDebugExec(emberAfDecodeAndPrintCluster(clusterId));

    if (isMfgSpecific) {
      emberAfAppPrint(" mfgId %2x", mfgId);
    }
    emberAfAppPrint(" FC %x seq %x cmd %x payload[",
                    zclFrameControl, zclSeqNum, zclCmd);
    
    emberAfAppFlush();
    emberAfAppPrintBuffer(message+3, len-3, TRUE);
    emberAfAppFlush();
    emberAfAppPrintln("]");
  }
#endif //EMBER_AF_PRINT_APP
}


void emAfPrintStatus(PGM_P task,
                     EmberStatus status)
{
  if (status == EMBER_SUCCESS) {
    emberAfPrint(emberAfPrintActiveArea,
                 "%p: %p", 
                 "Success",
                 task );
  } else {
    emberAfPrint(emberAfPrintActiveArea,
                 "%p: %p: 0x%x", 
                 "Error",
                 task, 
                 status);
  }
}

void emAfPermitJoin(int8u duration) 
{
  EmberStatus status = emberPermitJoining(duration);
  emberAfAppPrintln("pJoin for %d sec: 0x%x", duration, status); 
}

#ifdef EMBER_AF_USE_BUTTONS
// WARNING: this callback is an ISR so the best approach is to set a
// flag here when an action should be taken and then perform the action
// somewhere else. In this case the actions are serviced in the appTick
// function.
void halButtonIsr(int8u button, int8u state)
{
  if (state != BUTTON_PRESSED) {
    return;
  }
#ifdef EMBER_AF_FIRST_BUTTON
  if (button == EMBER_AF_FIRST_BUTTON) {
    emberAfFirstButtonPressed = TRUE;
  }
#endif //EMBER_AF_FIRST_BUTTON
#ifdef EMBER_AF_SECOND_BUTTON
  if (button == EMBER_AF_SECOND_BUTTON) {
    emberAfSecondButtonPressed = TRUE;
  }
#endif //EMBER_AF_SECOND_BUTTON
}
#endif //EMBER_AF_USE_BUTTONS


// ******************************************************************
// Functions called by the Serial Command Line Interface (CLI)
// ******************************************************************

boolean emAfProcessZdo(EmberNodeId sender,
                       EmberApsFrame* apsFrame,
                       int8u* message, 
                       int16u length)
{
  if (apsFrame->profileId != EMBER_ZDO_PROFILE_ID) {
    return FALSE;
  }
  emberAfZdoPrintln("RX: ZDO, command 0x%2x", apsFrame->clusterId);
    
#ifdef EMBER_AF_PRINT_ZDO
  if (apsFrame->clusterId == SIMPLE_DESCRIPTOR_RESPONSE) {
    emberAfZdoPrintln("RX: %p Desc Resp", "Simple");
  } else if (apsFrame->clusterId == MATCH_DESCRIPTORS_RESPONSE) {
    emberAfZdoPrintln("RX: %p Desc Resp", "Match");
  } else if (apsFrame->clusterId == END_DEVICE_BIND_RESPONSE) {
    emberAfZdoPrintln("RX: End dev bind response, status=%x", message[1]);
  } else if (apsFrame->clusterId == END_DEVICE_ANNOUNCE) {
    emberAfZdoPrintln("Device Announce: 0x%2x",
                      (int16u)(message[1])
                      + (int16u)(message[2] << 8));
  } else if (apsFrame->clusterId == IEEE_ADDRESS_RESPONSE) {
  }
#endif // EMBER_AF_PRINT_ZDO

  if (emberAfPreZDOMessageReceivedCallback(sender, apsFrame, message, length)) {
    goto zdoProcessingDone;
  }

  if (apsFrame->clusterId == BIND_RESPONSE) {
    emberAfPartnerLinkKeyExchangeResponseCallback(sender, message[1]);
  }

 zdoProcessingDone:
  // if it is a zdo response we can remove the zdo waiting task
  // and let a sleepy go back into hibernation
  if (apsFrame->clusterId > CLUSTER_ID_RESPONSE_MINIMUM) {
    emberAfRemoveFromCurrentAppTasks(EMBER_AF_WAITING_FOR_ZDO_RESPONSE);
  }

  return TRUE;
}

void emAfIncomingMessageHandler(EmberIncomingMessageType type,
                                EmberApsFrame *apsFrame,
                                int8u lastHopLqi,
                                int8s lastHopRssi,
                                EmberNodeId sender,
                                int8u bindingIndex,
                                int8u addressIndex,
                                int16u messageLength,
                                int8u *messageContents)
{
  EmberAfIncomingMessage im;
  boolean profileMatch = FALSE;

#ifdef EMBER_AF_ENABLE_FRAGMENTATION
  if (emAfFragmentationIncomingMessage(apsFrame,
                                       sender,
                                       &messageContents,
                                       &messageLength)) {
    emberAfDebugPrintln("%pfragment processed.", "Fragmentation:");
    return;
  }
#endif //EMBER_AF_ENABLE_FRAGMENTATION

  INCR_haNumPktsRxAll;

  emberAfDebugPrintln("Processing message: len=%d profile=%2x cluster=%2x",
                      messageLength,
                      apsFrame->profileId,
                      apsFrame->clusterId);
  emberAfDebugFlush();

  // Populate the incoming message struct to pass to the incoming message
  // callback.
  im.type              = type;
  im.apsFrame          = apsFrame;
  im.message           = messageContents;
  im.msgLen            = messageLength;
  im.source            = sender;
  im.lastHopLqi        = lastHopLqi;
  im.lastHopRssi       = lastHopRssi;
  im.bindingTableIndex = bindingIndex;
  im.addressTableIndex = addressIndex;
  if (emberAfPreMessageReceivedCallback(&im)) {
    return;
  }

  if (emAfServiceDiscoveryIncoming(sender,
                                   apsFrame,
                                   messageContents,
                                   messageLength)) {
    return;
  }

  if (emAfProcessZdo(sender, apsFrame, messageContents, messageLength)) {
    return;
  }

  // All messages must have the ZCL header.
  if (messageLength < EMBER_AF_ZCL_OVERHEAD) {
    emberAfAppPrintln("%pRX pkt too short!", "ERROR: ");
    INCR_haNumPktsRxLengthError;
    return;
  }

  emberAfPrintIncomingZclMessage(apsFrame->destinationEndpoint,
                                 apsFrame->clusterId,
                                 messageContents,
                                 messageLength);

  // If the destination endpoint does not match the profile id of the message,
  // the message is silently dropped.
  if (apsFrame->destinationEndpoint == EMBER_BROADCAST_ENDPOINT) {
    int8u index;
    for (index = 0; index < emberAfEndpointCount(); index++) {
      if (emberAfProfileIdFromIndex(index) == apsFrame->profileId) {
        profileMatch = TRUE;
        break;
      }
    }
  } else {
    int8u index = emberAfIndexFromEndpoint(apsFrame->destinationEndpoint);
    if (index == 0xFF) {
      emberAfAppPrintln("%p%pendpoint: 0x%x",
                        "ERROR: ",
                        "wrong ",
                        apsFrame->destinationEndpoint);
      INCR_haNumPktsRxWrongEndpoint;
      return;
    }
    profileMatch = (emberAfProfileIdFromIndex(index) == apsFrame->profileId);
  }

  if (!profileMatch) {
    emberAfAppPrintln("%p%pprofile: 0x%2x",
                      "ERROR: ",
                      "wrong ",
                      apsFrame->profileId);
    INCR_haNumPktsRxWrongProfile;
    return;
  }

  // Peel off the global and cluster-specific  messages. If this returns
  // TRUE it means the message was processed and we should return.
  if (emberAfProcessMessage(apsFrame,
                            type,
                            messageContents,
                            messageLength,
                            sender,
                            NULL)) { // no inter-pan header
    INCR_haNumPktsRxGivenToZCL;
    return;
  }
}

void emAfMessageSentHandler(EmberOutgoingMessageType type,
                            int16u indexOrDestination,
                            EmberApsFrame *apsFrame,
                            EmberStatus status,
                            int16u messageLength,
                            int8u *messageContents)
{
#ifdef EMBER_AF_CONCENTRATOR
  emberConcentratorNoteDeliveryFailure(type, status);
#endif

#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
  if (status != EMBER_SUCCESS) {
    emberAfAppPrintln("%ptx %x", "ERROR: ", status);
  }
#endif

  if (status == EMBER_SUCCESS
      && apsFrame->profileId == EMBER_ZDO_PROFILE_ID
      && apsFrame->clusterId < CLUSTER_ID_RESPONSE_MINIMUM) {
    emberAfAddToCurrentAppTasks(EMBER_AF_WAITING_FOR_ZDO_RESPONSE);
  }

  emberAfRemoveFromCurrentAppTasks(EMBER_AF_WAITING_FOR_DATA_ACK);

  if (messageContents[0] & ZCL_CLUSTER_SPECIFIC_COMMAND) {
    emberAfClusterMessageSentCallback(type,
                                      indexOrDestination,
                                      apsFrame,
                                      messageLength,
                                      messageContents,
                                      status);
  } else {
#ifndef ZA_NO_REPORTING_OPTIMIZATION
    int16u manufacturerCode;
    int8u commandId;
    if (messageContents[0] & ZCL_MANUFACTURER_SPECIFIC_MASK) {
      manufacturerCode = emberAfGetInt16u(messageContents, 1, messageLength);
      commandId = emberAfGetInt8u(messageContents, 4, messageLength);
    } else {
      manufacturerCode = EMBER_AF_NULL_MANUFACTURER_CODE;
      commandId = emberAfGetInt8u(messageContents, 2, messageLength);
    }
    if (commandId == ZCL_REPORT_ATTRIBUTES_COMMAND_ID) {
      emberAfUpdateReportEntryStatus(indexOrDestination,
                                     apsFrame->sourceEndpoint,
                                     apsFrame->destinationEndpoint,
                                     apsFrame->clusterId,
                                     ((messageContents[0]
                                       & ZCL_FRAME_CONTROL_DIRECTION_MASK)
                                      ? CLUSTER_MASK_SERVER
                                      : CLUSTER_MASK_CLIENT),
                                     manufacturerCode,
                                     status);
    }
#endif
  }

  emberAfMessageSentCallback(type,
                             indexOrDestination,
                             apsFrame,
                             messageLength,
                             messageContents,
                             status);
}

void emAfProcessSendStatus(EmberOutgoingMessageType type,
                           int16u indexOrDestination,
                           EmberApsFrame *apsFrame,
                           EmberStatus status,
                           int16u messageLength,
                           int8u *messageContents)
{
  if (apsFrame->options & EMBER_APS_OPTION_DSA_SIGN
      && status == EMBER_OPERATION_IN_PROGRESS) {
    // We consider "in progress" signed messages as being sent successfully.
    // The stack will send the message after signing.
    status = EMBER_SUCCESS;
    emAfSetCryptoOperationInProgress();
  }

  if (status == EMBER_SUCCESS) {
    emberAfAddToCurrentAppTasks(EMBER_AF_WAITING_FOR_DATA_ACK);
  } else {
    emAfMessageSentHandler(type,
                           indexOrDestination,
                           apsFrame,
                           status,
                           messageLength,
                           messageContents);
  }
}

#ifdef EMBER_AF_ENABLE_FRAGMENTATION
void emAfFragmentationMessageSentHandler(EmberOutgoingMessageType type,
                                         int16u indexOrDestination,
                                         EmberApsFrame *apsFrame,
                                         int8u *buffer,
                                         int16u bufLen,
                                         EmberStatus status)
{
  // the fragmented message is no longer in process
  emberAfDebugPrintln("%pend.", "Fragmentation:");
  emAfMessageSentHandler(type,
                         indexOrDestination,
                         apsFrame,
                         status,
                         bufLen,
                         buffer);
}
#endif //EMBER_AF_ENABLE_FRAGMENTATION

void emAfStackStatusHandler(EmberStatus status)
{
  if (emberAfStackStatusCallback(status)) {
    return;
  }

  emberAfAppFlush();

  switch (status) {
  case EMBER_NETWORK_UP:
  case EMBER_TRUST_CENTER_EUI_HAS_CHANGED:  // also means NETWORK_UP
    emberAfAppPrintln("%p%pUP", "EMBER_", "NETWORK_");
    emberAfAppFlush();
    if (status == EMBER_TRUST_CENTER_EUI_HAS_CHANGED) {
      emberAfAppPrintln("Trust Center EUI has changed.");
      // We abort registration because we want to clear out any previous
      // state and force it to start anew.  One of two results will occur:
      // (1) It succeeds and we are on a new network with a new TC, in which
      //     case we need to kick off key establishment to re-authenticate it 
      //     and also re-discover other ESIs.
      // (2) It will fail, in which case we have to reboot to forget the untrusted
      //     network and its settings.
      emberAfRegistrationAbortCallback();
    }

    // This kicks off registration for newly joined devices.  If registration
    // already occurred, nothing will happen here.
    emberAfRegistrationStartCallback();

    emberAfNetworkFindOperationCompleteCallback();

    // Stop moving if we were in the process
    emberAfStopMove();
    emAfMoveAttempts = 0;
    
    break;
  case EMBER_RECEIVED_KEY_IN_THE_CLEAR:
  case EMBER_NO_NETWORK_KEY_RECEIVED:
  case EMBER_PRECONFIGURED_KEY_REQUIRED:
  case EMBER_MOVE_FAILED:  
  case EMBER_JOIN_FAILED:
  case EMBER_NETWORK_DOWN:
    if (status == EMBER_NETWORK_DOWN) {
      emberAfAppPrintln("%p%pDOWN", "EMBER_", "NETWORK_");
    } else {
      emberAfAppPrintln("%pJOIN%p", "EMBER_", "_FAILED");
    }
    emberAfAppFlush();
    emberAfStackDown();
    if (status == EMBER_NETWORK_DOWN) {
#if defined(ZA_DEVICE_IS_SLEEPY) || defined(ZA_DEVICE_IS_NONSLEEPY_END_DEVICE)
      EmberNetworkStatus state = emberNetworkState();
      if (state == EMBER_JOINED_NETWORK_NO_PARENT) {
        emberAfStartMove();
      } else if (state == EMBER_NO_NETWORK) {
        emberAfStopMove();
      }
#endif
    } else {
      emberAfContinueJoinableNetworkSearchCallback(); 
    }
    break;
  default:
    emberAfDebugPrintln("EVENT: stackStatus 0x%x", status);
  }

  emberAfAppFlush();
}

EmberStatus emAfNetworkInit(void)
{
  return networkInit();
}

int8u emberAfCopyBigEndianEui64Argument(int8s index, EmberEUI64 destination)
{
  EmberEUI64 tmp;
  int8u length = emberCopyEui64Argument(index, tmp);
  emberReverseMemCopy(destination, tmp, EUI64_SIZE);
  return length;
}

// form-and-join library callbacks.
void emberUnusedPanIdFoundHandler(EmberPanId panId, int8u channel)
{
  emberAfUnusedPanIdFoundCallback(panId, channel);
}

void emberJoinableNetworkFoundHandler(EmberZigbeeNetwork *networkFound,
                                      int8u lqi,
                                      int8s rssi)
{
  emberAfJoinableNetworkFoundCallback(networkFound, lqi, rssi);
}

void emberScanErrorHandler(EmberStatus status)
{
  emberAfScanErrorCallback(status);
}

EmberStatus emberAfFormNetwork(EmberNetworkParameters *parameters)
{
  EmberStatus status = EMBER_INVALID_CALL;
#if (ZA_DEVICE_TYPE == ZA_COORDINATOR)
  zaTrustCenterSecurityInit();
  emberAfCorePrintln("%ping on ch %d, panId 0x%2X",
                     "Form", 
                     parameters->radioChannel,
                     parameters->panId);
  emberAfCoreFlush();
  status = emberFormNetwork(parameters);
#endif
  return status;
}

EmberStatus emberAfJoinNetwork(EmberNetworkParameters *parameters)
{
  EmberStatus status;
  zaNodeSecurityInit();
  emberAfCorePrintln("%ping on ch %d, panId 0x%2X",
                     "Join", 
                     parameters->radioChannel,
                     parameters->panId);
  emberAfCoreFlush();
  status = emberJoinNetwork((ZA_DEVICE_TYPE == EMBER_COORDINATOR
                             ? EMBER_ROUTER
                             : ZA_DEVICE_TYPE),
                            parameters);
  return status;
}
