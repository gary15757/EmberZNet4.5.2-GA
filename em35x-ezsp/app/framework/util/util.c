// *******************************************************************
// * util.c
// *
// * This file contains all of the common ZCL command and attribute handling 
// * code for Ember's ZCL implementation
// *
// * The actual compiled version of this code will vary depending on
// * #defines for clusters included in the built application.
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************


#include "../include/af.h"
#include "common.h"
#include "../report/report-table.h"
#include "../security/crypto-state.h"
#include "../plugin/time-client/time-client.h"
#include "../plugin/time-server/time-server.h"
#include "../../util/source-route-common.h"

//------------------------------------------------------------------------------


void emAfMessageSentHandler(EmberOutgoingMessageType type,
                            int16u indexOrDestination,
                            EmberApsFrame *apsFrame,
                            EmberStatus status,
                            int16u messageLength,
                            int8u *messageContents);

// Storage and functions for turning on and off devices
boolean afDeviceEnabled[MAX_ENDPOINT_COUNT];
// a variable containing the number of messages send from the utilities
// since emberAfInit was called.

#ifdef EMBER_AF_ENABLE_STATISTICS
int32u afNumPktsSent;
#endif

PGM EmberAfClusterName zclClusterNames[] = {
  CLUSTER_IDS_TO_NAMES                 // defined in print-cluster.h
  { ZCL_NULL_CLUSTER_ID, NULL },  // terminator
};

// A pointer to the current command being processed
// This struct is allocated on the stack inside
// emberAfProcessMessage. The pointer below is set
// to NULL when the function exits.
EmberAfClusterCommand *emAfCurrentCommand;

// variable used for turning off Aps Link security. Set by the CLI 
boolean afApsSecurityOff = FALSE;

// DEPRECATED.
int8u emberAfIncomingZclSequenceNumber = 0xFF;

static boolean afNoSecurityForDefaultResponse = FALSE;

// Sequence used for outgoing messages if they are
// not responses.
int8u emberAfSequenceNumber = 0xFF;

// A boolean value so we know when the device is performing
// key establishment.
boolean emAfDeviceIsPerformingKeyEstablishment = FALSE;

int8u emberAfApsRetryOverride = EMBER_AF_RETRY_OVERRIDE_NONE;

// Holds the response type
int8u emberAfResponseType = ZCL_UTIL_RESP_NORMAL;

static EmberAfInterpanHeader interpanResponseHeader;

// Time
#define SECONDS_IN_YEAR 31536000
#define SECONDS_IN_DAY 86400L
#define SECONDS_IN_HOUR 3600
PGM int8u emberAfDaysInMonth[] =
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static PGM int8u emberAfAnalogDiscreteThresholds[] 
  = { 0x08, EMBER_AF_DATA_TYPE_NONE,
      0x20, EMBER_AF_DATA_TYPE_DISCRETE,
      0x30, EMBER_AF_DATA_TYPE_ANALOG,
      0x38, EMBER_AF_DATA_TYPE_DISCRETE,
      0x40, EMBER_AF_DATA_TYPE_ANALOG,
      0x58, EMBER_AF_DATA_TYPE_DISCRETE,
      0xE0, EMBER_AF_DATA_TYPE_NONE,
      0xF0, EMBER_AF_DATA_TYPE_ANALOG,
      0xFF, EMBER_AF_DATA_TYPE_NONE };

static void doNothingTick(void);

typedef void (TickFunction)(void);

static TickFunction* PGM internalTickFunctions[] = {
  #if ZA_DEVICE_TYPE == ZA_COORDINATOR && defined(ZA_TRUST_CENTER_TICK)
    ZA_TRUST_CENTER_TICK,
  #endif

    // This is the main customer tick
    emberAfMainTickCallback,

    doNothingTick,  // must be second to last
    NULL            // terminator, must be last
};

//------------------------------------------------------------------------------

// Device enabled/disabled functions
boolean emberAfIsDeviceEnabled(int8u endpoint)
{
  int8u index;
#ifdef ZCL_USING_BASIC_CLUSTER_DEVICE_ENABLED_ATTRIBUTE
  boolean deviceEnabled;
  if (emberAfReadServerAttribute(endpoint,
                                 ZCL_BASIC_CLUSTER_ID,
                                 ZCL_DEVICE_ENABLED_ATTRIBUTE_ID,
                                 (int8u *)&deviceEnabled,
                                 sizeof(deviceEnabled))
      == EMBER_ZCL_STATUS_SUCCESS) {
    return deviceEnabled;
  }
#endif
  index = emberAfIndexFromEndpoint(endpoint);
  if (index != 0xFF && index < sizeof(afDeviceEnabled)) {
    return afDeviceEnabled[index];
  }
  return FALSE;
}

void emberAfSetDeviceEnabled(int8u endpoint, boolean enabled)
{
  int8u index = emberAfIndexFromEndpoint(endpoint);
  if (index != 0xFF && index < sizeof(afDeviceEnabled)) {
    afDeviceEnabled[index] = enabled;
  }
#ifdef ZCL_USING_BASIC_CLUSTER_DEVICE_ENABLED_ATTRIBUTE
  emberAfWriteServerAttribute(endpoint,
                              ZCL_BASIC_CLUSTER_ID,
                              ZCL_DEVICE_ENABLED_ATTRIBUTE_ID,
                              (int8u *)&enabled,
                              ZCL_BOOLEAN_ATTRIBUTE_TYPE);
#endif
}


// Calculates difference. Works only for dataSizes of 4 or less.
int32u emberAfGetDifference(int8u *pData, int32u value, int8u dataSize) 
{
  int32u value2 = 0, diff;
  int8u i;

  // only support data types up to 4 bytes
  if (dataSize > 4) {
    return 0;
  }

  // get the 32-bit value
  for (i = 0; i < dataSize; i++) {
    value2 = value2 << 8;
#if (BIGENDIAN_CPU)
    value2 += pData[i];
#else //BIGENDIAN
    value2 += pData[dataSize - i - 1];
#endif //BIGENDIAN
  }

  if (value > value2) {
    diff = value - value2; 
  } else {
    diff = value2 - value; 
  }

  //emberAfDebugPrintln("comparing 0x%4x and 0x%4x, diff is 0x%4x",
  //                    value, value2, diff);
  
  return diff;
}

// --------------------------------------------------

// DEPRECATED.
void emberAfSetEndpointsForResponse(int8u srcEndpoint, int8u destEndpoint)
{
  emberAfResponseApsFrame.sourceEndpoint = srcEndpoint;
  emberAfResponseApsFrame.destinationEndpoint = destEndpoint;
}

static void prepareForResponse(const EmberAfClusterCommand *cmd)
{
  emberAfResponseApsFrame.profileId           = cmd->apsFrame->profileId;
  emberAfResponseApsFrame.clusterId           = cmd->apsFrame->clusterId;
  emberAfResponseApsFrame.sourceEndpoint      = cmd->apsFrame->destinationEndpoint;
  emberAfResponseApsFrame.destinationEndpoint = cmd->apsFrame->sourceEndpoint;
  emberAfResponseApsFrame.options             = EMBER_AF_DEFAULT_APS_OPTIONS;
  if (cmd->apsFrame->options & EMBER_APS_OPTION_ENCRYPTION) {
    emberAfResponseApsFrame.options |= EMBER_APS_OPTION_ENCRYPTION;
  }

  if (cmd->interPanHeader == NULL) {
    emberAfResponseDestination = cmd->source;
    emberAfResponseType &= ~ZCL_UTIL_RESP_INTERPAN;
  } else {
    emberAfResponseType |= ZCL_UTIL_RESP_INTERPAN;
    MEMCOPY(&interpanResponseHeader, 
            cmd->interPanHeader, 
            sizeof(EmberAfInterpanHeader));
    // Always send responses as unicast
    interpanResponseHeader.messageType = EMBER_AF_INTER_PAN_UNICAST;
  }
}

// ****************************************
// Initialize Clusters
// ****************************************
void emberAfInit(void) 
{
#ifdef EMBER_AF_ENABLE_STATISTICS  
  afNumPktsSent = 0;
#endif
  emberAfLoadAttributesFromDefaults();
  emberAfLoadAttributesFromTokens();

  MEMSET(afDeviceEnabled, TRUE, emberAfEndpointCount());

  // Set up client API buffer.
  emberAfSetExternalBuffer(appResponseData,
                           EMBER_AF_RESPONSE_BUFFER_LEN,
                           &appResponseLength,
                           &emberAfResponseApsFrame);

  emAfCallInits();
}

static void doNothingTick(void)
{
  // No code should be placed in here.

  // This is used as a place-holder for the while() loop in emberAfTick()
  // so that after the last real tick is called, we loop one more
  // time to send any responses that are queued.
}

void emberAfTick(void) 
{
  int8u i = 0;

  while (internalTickFunctions[i] != NULL) {
    // if a response is waiting (generated from a zcl message coming in to
    // incomingMessageHandler, or from a previous tick function) then this
    // needs to be sent immediately
    if (emberAfResponseWaitingFlag) {
      emberAfSendResponse();
    }

    if (emAfIsCryptoOperationInProgress()) {
      // Wait until ECC operations are done.  Don't allow
      // any of the clusters to send messages.  This is necessary
      // on host or SOC application.
      return;
    }

    (internalTickFunctions[i])();
    i++;
  }
}

// ****************************************
// This function is called by the application when the stack goes down,
// such as after a leave network. This allows zcl utils to clear state 
// that should not be kept when changing networks
// ****************************************
void emberAfStackDown(void)
{
#ifndef ZA_NO_REPORTING_OPTIMIZATION
  // the report table should be cleared when the stack comes down. 
  // going to a new network means new report devices should be discovered.
  // if the table isnt cleared the device keeps trying to send messages.
  emberAfReportTableClear();
#endif //ZA_NO_REPORTING_OPTIMIZATION

  emberAfRegistrationAbortCallback();
  emberAfTrustCenterKeepaliveAbortCallback();
}

// ****************************************
// Print out information about each cluster
// ****************************************

int16u emberAfFindClusterNameIndex(int16u cluster)
{
  int16u index = 0;
  while (zclClusterNames[index].id != ZCL_NULL_CLUSTER_ID) {
    if (zclClusterNames[index].id == cluster) {
      return index;
    }
    index++;
  }  
  return 0xFFFF;
}

void emberAfDecodeAndPrintCluster(int16u cluster)
{
  int16u index = emberAfFindClusterNameIndex(cluster);
  if (index == 0xFFFF) { 
    emberAfPrint(emberAfPrintActiveArea,
                 "(Unknown clus. [0x%2x])", 
                 cluster);
  } else {
    emberAfPrint(emberAfPrintActiveArea, 
                 "(%p)", 
                 zclClusterNames[index].name);
  }
  emberAfFlush(emberAfPrintActiveArea);
}

//DEBUG
void emberAfPrintCommand(EmberAfClusterCommand *cmd, int8u caller) 
{
  emberAfCorePrintln("RX CMD %x:", caller);
  emberAfCorePrintln("  type %x", cmd->type);
  emberAfCorePrintln("  source %2x", cmd->source);
  emberAfCorePrintln("  bufLen %2x", cmd->bufLen);
  emberAfCorePrintln("  clusterSpecific %x", cmd->clusterSpecific);
  emberAfCoreFlush();
  emberAfCorePrintln("  cmd.direction %x", cmd->direction);
  emberAfCorePrintln("  cmd.mfgSpecific %x", cmd->mfgSpecific);
  emberAfCorePrintln("  cmd.mfgCode %2x", cmd->mfgCode);
  emberAfCorePrintln("  cmd.seqNum %x", cmd->seqNum);
  emberAfCoreFlush();
  emberAfCorePrintln("  cmd.cmdId %x", cmd->commandId);
  emberAfCorePrintln("  cmd.payloadStartIndex %x", cmd->payloadStartIndex);
  emberAfCorePrintBuffer(cmd->buffer, cmd->bufLen, TRUE);
  emberAfCorePrintln("");
  emberAfCoreFlush();  
}

// a single call to process global and cluster-specific messages and callbacks.
boolean emberAfProcessMessage(EmberApsFrame *apsFrame,
                              EmberIncomingMessageType type,
                              int8u *message,
                              int16u msgLen,
                              EmberNodeId source,
                              InterPanHeader *interPanHeader)
{
  EmberAfClusterCommand cmd;
  boolean msgHandled = FALSE;

  // Populate the cluster command struct for processing.
  cmd.apsFrame        = apsFrame;
  cmd.type            = type;
  cmd.source          = source;
  cmd.buffer          = message;
  cmd.bufLen          = msgLen;
  cmd.clusterSpecific = (message[0] & ZCL_CLUSTER_SPECIFIC_COMMAND);
  cmd.mfgSpecific     = (message[0] & ZCL_MANUFACTURER_SPECIFIC_MASK);
  cmd.direction       = ((message[0] & ZCL_FRAME_CONTROL_DIRECTION_MASK)
                          ? ZCL_DIRECTION_SERVER_TO_CLIENT
                          : ZCL_DIRECTION_CLIENT_TO_SERVER);
  cmd.payloadStartIndex = 1;
  if (cmd.mfgSpecific) {
    cmd.mfgCode = emberAfGetInt16u(message, cmd.payloadStartIndex, msgLen);
    cmd.payloadStartIndex += 2;
  }
  cmd.seqNum         = message[cmd.payloadStartIndex++];
  cmd.commandId      = message[cmd.payloadStartIndex++];
  cmd.interPanHeader = interPanHeader;
  emAfCurrentCommand = &cmd;

  // All of these should be covered by the EmberAfClusterCommand but are
  // still here until all the code is moved over to use the cmd. -WEH
  emberAfIncomingZclSequenceNumber = cmd.seqNum;

  if (interPanHeader 
      && !(interPanHeader->options
           & EMBER_AF_INTERPAN_OPTION_MAC_HAS_LONG_ADDRESS)) {
    // For safety, dump all interpan messages that don't have a long
    // source in the MAC layer.  In theory they should not get past
    // the MAC filters but this is insures they will not get processed.
    goto kickout;
  }

  prepareForResponse(&cmd);

  if (interPanHeader == NULL) {
    boolean broadcast = (type == EMBER_INCOMING_BROADCAST
                         || type == EMBER_INCOMING_BROADCAST_LOOPBACK
                         || type == EMBER_INCOMING_MULTICAST
                         || type == EMBER_INCOMING_MULTICAST_LOOPBACK);

    // if the cluster for the incoming message requires security and
    // doesnt have it return default response STATUS_FAILURE
    if (emberAfDetermineIfLinkSecurityIsRequired(cmd.commandId,
                                                 TRUE, // incoming
                                                 broadcast,
                                                 cmd.apsFrame->profileId,
                                                 cmd.apsFrame->clusterId)
        && (!(cmd.apsFrame->options & EMBER_APS_OPTION_ENCRYPTION))) {
      emberAfDebugPrintln("Drop clus %2x due to no aps security",
                          cmd.apsFrame->clusterId);
      afNoSecurityForDefaultResponse = TRUE;
      emberAfSendDefaultResponse(&cmd, EMBER_ZCL_STATUS_FAILURE);
      afNoSecurityForDefaultResponse = FALSE;

      // Mark the message as processed.  It failed security processing, so no
      // other parts of the code act should upon it.
      msgHandled = TRUE;
      goto kickout;
    }
  }

  if (emberAfPreCommandReceivedCallback(&cmd)) {
    msgHandled = TRUE;
    goto kickout;
  }

  if (cmd.apsFrame->destinationEndpoint == EMBER_BROADCAST_ENDPOINT) {
    int8u i;
    for (i = 0; i < emberAfEndpointCount(); i++) {
      // Skip endpoints whose profiles don't match that of the broadcast.
      if (emberAfProfileIdFromIndex(i) != cmd.apsFrame->profileId) {
        emberAfDebugPrintln("Drop broadcast cluster 0x%2x command 0x%x"
                            " for endpoint 0x%x due to wrong profile: 0x%2x",
                            cmd.apsFrame->clusterId,
                            cmd.commandId,
                            cmd.apsFrame->destinationEndpoint,
                            cmd.apsFrame->profileId);
        continue;
      }

      // Change the destination endpoint of the incoming command and the source
      // source endpoint of the response so they both reflect the endpoint the
      // message is actually being passed to in this iteration of the loop.
      cmd.apsFrame->destinationEndpoint      = emberAfEndpointFromIndex(i);
      emberAfResponseApsFrame.sourceEndpoint = emberAfEndpointFromIndex(i);

      switch (cmd.type) {
      case EMBER_INCOMING_MULTICAST:
      case EMBER_INCOMING_MULTICAST_LOOPBACK:
        if (!emberAfGroupsClusterEndpointInGroupCallback(cmd.apsFrame->destinationEndpoint,
                                                         cmd.apsFrame->groupId)) {
          continue;
        }
        // FALLTHROUGH
      case EMBER_INCOMING_BROADCAST:
      case EMBER_INCOMING_BROADCAST_LOOPBACK:
        // All endpoints will get a chance to process the message (assuming the
        // profile matches), but the message will be considered handled if at
        // least one endpoint takes it.
        msgHandled = ((cmd.clusterSpecific
                       ? emAfProcessClusterSpecificCommand(&cmd)
                       : emAfProcessGlobalCommand(&cmd))
                      || msgHandled);
        break;
      }
    }
  } else { // single endpoint
    msgHandled = (cmd.clusterSpecific
                  ? emAfProcessClusterSpecificCommand(&cmd)
                  : emAfProcessGlobalCommand(&cmd));
  }

kickout:
  emAfCurrentCommand = NULL;
  return msgHandled;
}

int8u emberAfNextSequence(void)
{
  return ++emberAfSequenceNumber;
}


// the caller to the library can set a flag to say do not respond to the
// next ZCL message passed in to the library. Passing TRUE means disable
// the reply for the next ZCL message. Setting to FALSE re-enables the
// reply (in the case where the app disables it and then doesnt send a 
// message that gets parsed).
void emberAfSetNoReplyForNextMessage(boolean set)
{
  if (set) {
    emberAfResponseType |= ZCL_UTIL_RESP_NONE;
  } else {
    emberAfResponseType &= ~ZCL_UTIL_RESP_NONE;
  }
}

// DEPRECATED.
void emberAfSetReplyForInterPAN(EmberPanId destPan)
{
  // don't change the type from "none". None means the user has disabled
  // responses from ZCL Utils, only the user can re-enable this
  emberAfResponseType |= ZCL_UTIL_RESP_INTERPAN;
  interpanResponseHeader.panId = destPan;
}

static EmberStatus sendZclMessage(boolean request)
{
  EmberStatus status;
  int8u sequenceNumber = (request
                          ? emberAfNextSequence()
                          : emberAfIncomingZclSequenceNumber);
  int8u label;

  if (emberAfApsRetryOverride == EMBER_AF_RETRY_OVERRIDE_SET) {
    emberAfResponseApsFrame.options |= EMBER_APS_OPTION_RETRY;
  } else if (emberAfApsRetryOverride == EMBER_AF_RETRY_OVERRIDE_UNSET) {
    emberAfResponseApsFrame.options &= ~EMBER_APS_OPTION_RETRY;
  }

  // Fill commands may increase the sequence. If we are sending the 
  // response, make sure the sequence is reset to what it should be.
  if (appResponseData[0] & ZCL_MANUFACTURER_SPECIFIC_MASK) {
    appResponseData[3] = sequenceNumber;
  } else {
    appResponseData[1] = sequenceNumber;
  }

  // send the message either using Inter-PAN or normal. These are
  // calls implemented in the app: af-main.c or af-main-host.c since
  // the sending is different for different platforms
  if (emberAfResponseType & ZCL_UTIL_RESP_INTERPAN) {
    label = 'I';
    status = emberAfInterpanSendMessageCallback(&interpanResponseHeader,
                                                appResponseLength,
                                                appResponseData);
    emberAfResponseType &= ~ZCL_UTIL_RESP_INTERPAN;
  } else if (emberAfResponseDestination < EMBER_BROADCAST_ADDRESS) {
    label = 'U';
    status = emberAfSendUnicast(EMBER_OUTGOING_DIRECT,
                                emberAfResponseDestination,
                                &emberAfResponseApsFrame,
                                appResponseLength,
                                appResponseData);
  } else {
    label = 'B';
    status = emberAfSendBroadcast(emberAfResponseDestination,
                                  &emberAfResponseApsFrame,
                                  appResponseLength,
                                  appResponseData);
  }

  emberAfDebugPrintln("T%4x:TX (%p) %ccast 0x%x%p",
                      emberAfGetCurrentTime(),
                      (request ? "req" : "resp"),
                      label,
                      status,
                      ((emberAfResponseApsFrame.options
                        & EMBER_APS_OPTION_ENCRYPTION)
                       ? " w/ link key" : ""));
  emberAfDebugPrint("TX buffer: [");
  emberAfDebugFlush();
  emberAfDebugPrintBuffer(appResponseData, appResponseLength, TRUE);
  emberAfDebugPrintln("]");
  emberAfDebugFlush();

#ifdef EMBER_AF_ENABLE_STATISTICS
  if (status == EMBER_SUCCESS) {
    afNumPktsSent++;
  }
#endif

  emberAfResponseWaitingFlag = FALSE;
  return status;
}

EmberStatus emberAfSendResponse(void)
{
  // If the no-response flag is set, dont send anything.
  if (emberAfResponseType & ZCL_UTIL_RESP_NONE) {
    emberAfDebugPrintln("ZCL Util: no response at user request");
    emberAfResponseWaitingFlag = FALSE;
    return EMBER_SUCCESS;
  } else {
    return sendZclMessage(FALSE); // request?
  }
}

// DEPRECATED.
EmberStatus emberAfSendRequest(void)
{
  return sendZclMessage(TRUE); // request?
}

EmberStatus emberAfSendDefaultResponse(const EmberAfClusterCommand *cmd,
                                       EmberAfStatus status)
{
  int8u frameControl;

  // Default Response commands are only sent in response to unicast commands.
  if (cmd->type != EMBER_INCOMING_UNICAST
      && cmd->type != EMBER_INCOMING_UNICAST_REPLY) {
    return EMBER_SUCCESS;
  }

  // If the Disable Default Response sub-field is set, Default Response commands
  // are only sent if there was an error.
  if ((cmd->buffer[0] & ZCL_DISABLE_DEFAULT_RESPONSE_MASK)
      && status == EMBER_ZCL_STATUS_SUCCESS) {
    return EMBER_SUCCESS;
  }

  // Default Response commands are never sent in response to other Default
  // Response commands.
  if (cmd->commandId == ZCL_DEFAULT_RESPONSE_COMMAND_ID) {
    return EMBER_SUCCESS;
  }

  appResponseLength = 0;
  frameControl = (ZCL_PROFILE_WIDE_COMMAND
                  | (cmd->direction == ZCL_DIRECTION_CLIENT_TO_SERVER
                     ? ZCL_FRAME_CONTROL_SERVER_TO_CLIENT
                     : ZCL_FRAME_CONTROL_CLIENT_TO_SERVER));
  if (!cmd->mfgSpecific) {
    emberAfPutInt8uInResp(frameControl & ~ZCL_MANUFACTURER_SPECIFIC_MASK);
  } else {
    emberAfPutInt8uInResp(frameControl | ZCL_MANUFACTURER_SPECIFIC_MASK);
    emberAfPutInt16uInResp(cmd->mfgCode);
  }
  emberAfPutInt8uInResp(cmd->seqNum);
  emberAfPutInt8uInResp(ZCL_DEFAULT_RESPONSE_COMMAND_ID);
  emberAfPutInt8uInResp(cmd->commandId);
  emberAfPutInt8uInResp(status);

  prepareForResponse(cmd);
  return emberAfSendResponse();
}

// DEPRECATED.
boolean emberAfReadyMessageToSend(EmberNodeId destination,
                                  EmberApsFrame* apsFrame,
                                  int16u len,
                                  int8u* message)
{
  if (len > EMBER_AF_RESPONSE_BUFFER_LEN) {
    return FALSE;
  }
  MEMCOPY(&emberAfResponseApsFrame, apsFrame, sizeof(EmberApsFrame));
  MEMCOPY(appResponseData, message, len);
  emberAfResponseDestination = destination;
  appResponseLength = len;
  emberAfSetResponseWaiting();
  return TRUE;
}

EmberStatus emAfProcessOutgoingMessage(EmberOutgoingMessageType type,
                                       int16u indexOrDestination,
                                       EmberApsFrame *apsFrame,
                                       int16u messageLength,
                                       int8u *message)
{
  boolean broadcast;
  int8u commandId;

  if (messageLength < EMBER_AF_ZCL_OVERHEAD
      || (message[0] & ZCL_MANUFACTURER_SPECIFIC_MASK
          && messageLength < EMBER_AF_ZCL_MANUFACTURER_SPECIFIC_OVERHEAD)) {
    return EMBER_ERR_FATAL;
  }

  if (type == EMBER_OUTGOING_VIA_BINDING) {
    // If using binding, set the endpoints based on those in the binding.  The
    // cluster in the binding is not used because bindings can be used to send
    // messages with any cluster id, not just the one set in the binding.
    EmberBindingTableEntry binding;
    EmberStatus status = emberGetBinding(indexOrDestination, &binding);
    if (status != EMBER_SUCCESS) {
      return status;
    }
    apsFrame->sourceEndpoint = binding.local;
    apsFrame->destinationEndpoint = binding.remote;
  } else if (type == EMBER_OUTGOING_MULTICAST) {
    apsFrame->groupId = indexOrDestination;
  }

  if (apsFrame->sourceEndpoint == EMBER_ZDO_ENDPOINT) {
    apsFrame->profileId = EMBER_ZDO_PROFILE_ID;
  } else {
    int8u index = emberAfIndexFromEndpoint(apsFrame->sourceEndpoint);
    if (index == 0xFF) {
      return EMBER_INVALID_ENDPOINT;
    }
    apsFrame->profileId = emberAfProfileIdFromIndex(index);
  }

  // Encryption is turned on if it is required, but not turned off if it isn't.
  // This allows the that the application to send encrypted messages in special
  // cases that aren't covered by the specs.
  broadcast = (type == EMBER_OUTGOING_MULTICAST
               || type == EMBER_OUTGOING_BROADCAST);
  commandId = (message[0] & ZCL_MANUFACTURER_SPECIFIC_MASK
               ? message[4]
               : message[2]);
  if (emberAfDetermineIfLinkSecurityIsRequired(commandId,
                                               FALSE, // incoming?
                                               broadcast,
                                               apsFrame->profileId,
                                               apsFrame->clusterId)) {
    apsFrame->options |= EMBER_APS_OPTION_ENCRYPTION;
  }

  // The check for messages that are too long is done last because the caller
  // may be able to fragment the message before sending.
  if (emberAfMaximumApsPayloadLength(type, indexOrDestination, apsFrame)
      < messageLength) {
    return EMBER_MESSAGE_TOO_LONG;
  }

  return EMBER_SUCCESS;
}

boolean emberAfDetermineIfLinkSecurityIsRequired(int8u commandId,
                                                 boolean incoming,
                                                 boolean broadcast,
                                                 EmberAfProfileId profileId,
                                                 EmberAfClusterId clusterId)
{
(void)afNoSecurityForDefaultResponse; // remove warning if not used
#ifdef SE_SECURITY_PROFILE_ENABLED
  // if we have turned off all APS security (needed for testing)
  // then just always return false.
  if (afApsSecurityOff || afNoSecurityForDefaultResponse) {
    afNoSecurityForDefaultResponse = FALSE;
    return FALSE;
  }

  // NOTE:  In general if it is a unicast, and one of the SE clusters,
  // it requires APS encryption.  A few special cases exists that we
  // allow for but those must be explicitly spelled out here.

  if (!incoming && broadcast) {
    // Assume that if the local device is broadcasting, even if it is
    // using one of the SE clusters, this is okay.
    return FALSE;
  } // Else fall through.

  // Check against profile IDs that use APS security on these clusters.
  if( ! (profileId == SE_PROFILE_ID) )
    return FALSE;

  // This list comes from Section 5.4.6 of the SE spec.
  switch (clusterId) {
  case ZCL_TIME_CLUSTER_ID:
  case ZCL_COMMISSIONING_CLUSTER_ID:
  case ZCL_PRICE_CLUSTER_ID:
  case ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID:
  case ZCL_SIMPLE_METERING_CLUSTER_ID:
  case ZCL_MESSAGING_CLUSTER_ID:
  case ZCL_TUNNELING_CLUSTER_ID:
  case ZCL_GENERIC_TUNNEL_CLUSTER_ID:
  case ZCL_PREPAYMENT_CLUSTER_ID:
    return TRUE;

  case ZCL_OTA_BOOTLOAD_CLUSTER_ID:
    if (!incoming
        || (commandId != ZCL_IMAGE_NOTIFY_COMMAND_ID)) {
      return TRUE;
    }
  }

#endif //SE_SECURITY_PROFILE_ENABLED
  return FALSE;
}

int8u emberAfMaximumApsPayloadLength(EmberOutgoingMessageType type,
                                     int16u indexOrDestination,
                                     EmberApsFrame *apsFrame)
{
  EmberNodeId destination = EMBER_UNKNOWN_NODE_ID;
  int max = EMBER_AF_MAXIMUM_APS_PAYLOAD_LENGTH;

  if (apsFrame->options & EMBER_APS_OPTION_ENCRYPTION) {
    max -= EMBER_AF_APS_ENCRYPTION_OVERHEAD;
  }
  if (apsFrame->options & EMBER_APS_OPTION_SOURCE_EUI64) {
    max -= EUI64_SIZE;
  }
  if (apsFrame->options & EMBER_APS_OPTION_DESTINATION_EUI64) {
    max -= EUI64_SIZE;
  }
  if (apsFrame->options & EMBER_APS_OPTION_FRAGMENT) {
    max -= EMBER_AF_APS_FRAGMENTATION_OVERHEAD;
  }

  switch (type) {
  case EMBER_OUTGOING_DIRECT:
    destination = indexOrDestination;
    break;
  case EMBER_OUTGOING_VIA_ADDRESS_TABLE:
    destination = emberGetAddressTableRemoteNodeId(indexOrDestination);
    break;
  case EMBER_OUTGOING_VIA_BINDING:
    destination = emberGetBindingRemoteNodeId(indexOrDestination);
    break;
  case EMBER_OUTGOING_MULTICAST:
    // APS multicast messages include the two-byte group id and exclude the
    // one-byte destination endpoint, for a net loss of an extra byte.
    max--;
    break;
  case EMBER_OUTGOING_BROADCAST:
    break;
  }

#ifndef ZA_NO_SOURCE_ROUTING
  if (destination != EMBER_UNKNOWN_NODE_ID) {
    int8u index = sourceRouteFindIndex(destination);
    if (index != NULL_INDEX) {
      max -= EMBER_AF_NWK_SOURCE_ROUTE_OVERHEAD;
      while (sourceRouteTable[index].closerIndex != NULL_INDEX) {
        index = sourceRouteTable[index].closerIndex;
        max -= EMBER_AF_NWK_SOURCE_ROUTE_PER_RELAY_ADDRESS_OVERHEAD;
      }
    }
  }
#else
  (void)destination; // remove warning if not used.

#endif //ZA_NO_SOURCE_ROUTING

  return max;
}

void emberAfCopyInt16u(int8u *data, int16u index, int16u x) {
  data[index]   = (int8u) ( ((x)    ) & 0xFF);      
  data[index+1] = (int8u) ( ((x)>> 8) & 0xFF);
}

void emberAfCopyInt24u(int8u *data, int16u index, int32u x) {
  data[index]   = (int8u) ( ((x)    ) & 0xFF );
  data[index+1] = (int8u) ( ((x)>> 8) & 0xFF );
  data[index+2] = (int8u) ( ((x)>>16) & 0xFF );
}

void emberAfCopyInt32u(int8u *data, int16u index, int32u x) {
  data[index]   = (int8u) ( ((x)    ) & 0xFF );    
  data[index+1] = (int8u) ( ((x)>> 8) & 0xFF );  
  data[index+2] = (int8u) ( ((x)>>16) & 0xFF );  
  data[index+3] = (int8u) ( ((x)>>24) & 0xFF );
}

void emberAfCopyString(int8u *dest, int8u *src, int8u size)
{
  int8u length = emberAfStringLength(src);
  if (size < length) {
    length = size;
  }
  MEMCOPY(dest + 1, src + 1, length);
  dest[0] = length;
}

#if (BIGENDIAN_CPU)
  #define EM_BIG_ENDIAN TRUE
#else
  #define EM_BIG_ENDIAN FALSE
#endif

int8s emberAfCompareValues(int8u* val1, int8u* val2, int8u len) 
{
  int8u i, j, k;

  for (i = 0; i < len; i++) {
    j = (EM_BIG_ENDIAN
         ? val1[i]
         : val1[(len-1)-i]);
    k = (EM_BIG_ENDIAN
         ? val2[i]
         : val2[(len-1)-i]);

    if (j > k) {
      return 1;
    } else if (k > j) {
      return -1;
    }
  }
  return 0;
}

// DEPRECATED.
void emberAfSendReadAttribute(int16u dest, 
                              int16u cluster, 
                              int16u attribute)
{
  appResponseData[0] = ZCL_PROFILE_WIDE_COMMAND;
  appResponseData[1] = emberAfNextSequence();
  appResponseData[2] = ZCL_READ_ATTRIBUTES_COMMAND_ID;
  appResponseData[3] = LOW_BYTE(attribute);
  appResponseData[4] = HIGH_BYTE(attribute);

  appResponseLength = 5;
  emberAfResponseApsFrame.clusterId = cluster;
  emberAfResponseDestination = dest;
  emberAfSetResponseWaiting();

}


// returns the type that the attribute is, either EMBER_AF_DATA_TYPE_ANALOG,
// EMBER_AF_DATA_TYPE_DISCRETE, or EMBER_AF_DATA_TYPE_NONE. This is based on table
// 2.15 from the ZCL spec 075123r02
int8u emberAfGetAttributeAnalogOrDiscreteType(int8u dataType)
{
  int8u index = 0;
  while ( emberAfAnalogDiscreteThresholds[index] <= dataType ) {
    index += 2;
  }
  return emberAfAnalogDiscreteThresholds[index+1];
}

// Zigbee spec says types between signed 8 bit and signed 64 bit
boolean emberAfIsTypeSigned(int8u dataType) {
  return (dataType >= ZCL_INT8S_ATTRIBUTE_TYPE &&
    dataType <= ZCL_INT64S_ATTRIBUTE_TYPE);
}

int32u emberAfGetCurrentTime(void)
{
#ifdef EMBER_AF_PLUGIN_TIME_SERVER
  return emAfTimeClusterServerGetCurrentTime();
#elif defined(EMBER_AF_PLUGIN_TIME_CLIENT)
  return emAfTimeClusterClientGetCurrentTime();
#else
  return emberAfGetCurrentTimeCallback();
#endif
}


// *******************************************************
// emberAfPrintTime and emberAfSetTime are convienience methods for setting
// and displaying human readable times.

// Expects to be passed a ZigBee time which is the number of seconds
// since the year 2000
void emberAfSetTime(int32u utcTime) {
#ifdef EMBER_AF_PLUGIN_TIME_SERVER
  emAfTimeClusterServerSetCurrentTime(utcTime);
#endif //EMBER_AF_PLUGIN_TIME_SERVER
#ifdef EMBER_AF_PLUGIN_TIME_CLIENT
  emAfTimeClusterClientSetCurrentTime(utcTime);
#endif //EMBER_AF_PLUGIN_TIME_CLIENT
  emberAfSetTimeCallback(utcTime);
}

// emberAfPrintTime expects to be passed a ZigBee time which is the number
// of seconds since the year 2000, it prints out a human readable time
// from that value.
void emberAfPrintTime(int32u utcTime)
{
#ifdef EMBER_AF_PRINT_ENABLE
  int32u i;
  int32u daysSince2000 = utcTime / SECONDS_IN_DAY;
  int32u secToday = utcTime - (daysSince2000 * SECONDS_IN_DAY);
  int8u hr = (int8u)(secToday / SECONDS_IN_HOUR);
  int8u min = (int8u) ((secToday - (hr * SECONDS_IN_HOUR)) / 60);
  int8u sec = (int8u) (secToday - ((hr * SECONDS_IN_HOUR) + (min * 60)));
  int16u year = 2000;
  int8u month = 1;
  int8u day = 1;
  boolean isLeapYear = TRUE; // 2000 was a leap year
  
  // march through the calendar, counting months, days and years
  // being careful to account for leapyears.
  for (i = 0; i < daysSince2000; i++) {
    int8u daysInMonth;
    if (isLeapYear && (month == 2)) {
      daysInMonth = 29;
    } else {
      daysInMonth = emberAfDaysInMonth[month - 1];
    }
    if (daysInMonth == day) {
      month++;
      day = 1;
    } else {
      day++;
    }
    if (month == 13) {
      year++;
      month = 1;
      if (year % 4 == 0 && 
          (year % 100 != 0 || 
           (year % 400 == 0)))
        isLeapYear = TRUE;
      else
        isLeapYear = FALSE;
    }
  }
  emberAfPrintln(emberAfPrintActiveArea,
                 "UTC time: %d/%d/%d %d:%d:%d (%4x)",
                 month,
                 day,
                 year,
                 hr,
                 min,
                 sec,
                 utcTime);
#endif //EMBER_AF_PRINT_ENABLE
}

int8u emberAfAddAddressTableEntry(EmberEUI64 longId, EmberNodeId shortId)
{
  int8u i, index = EMBER_NULL_ADDRESS_TABLE_INDEX;
  for (i = 0; i < EMBER_AF_ADDRESS_TABLE_SIZE; i++) {
    if (emberGetAddressTableRemoteNodeId(i)
        != EMBER_TABLE_ENTRY_UNUSED_NODE_ID) {
      EmberEUI64 eui64;
      emberGetAddressTableRemoteEui64(i, eui64);
      if (MEMCOMPARE(longId, eui64, EUI64_SIZE) == 0) {
        index = i;
        goto kickout;
      }
    } else if (index == EMBER_NULL_ADDRESS_TABLE_INDEX) {
      index = i;
    }
  }
  if (index != EMBER_NULL_ADDRESS_TABLE_INDEX) {
    emberSetAddressTableRemoteEui64(index, longId);
kickout:
    if (shortId != EMBER_UNKNOWN_NODE_ID) {
      emberSetAddressTableRemoteNodeId(index, shortId);
    }
  }
  return index;
}

EmberStatus emberAfSetAddressTableEntry(int8u index,
                                        EmberEUI64 longId,
                                        EmberNodeId shortId)
{
  EmberStatus status = EMBER_ADDRESS_TABLE_INDEX_OUT_OF_RANGE;
  if (index < EMBER_AF_ADDRESS_TABLE_SIZE) {
    status = emberSetAddressTableRemoteEui64(index, longId);
    if (status == EMBER_SUCCESS && shortId != EMBER_UNKNOWN_NODE_ID) {
      emberSetAddressTableRemoteNodeId(index, shortId);
    }
  }
  return status;
}
