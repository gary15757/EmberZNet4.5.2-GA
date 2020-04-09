// *****************************************************************************
// * fragmentation.c
// *
// * Splits long messages into smaller fragments for transmission and
// * reassembles received fragments into full messages.
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include "app/framework/include/af.h"
#ifdef EZSP_HOST
#include "app/util/source-route-host.h"
#endif //EZSP_HOST
#include "fragmentation.h"

#ifdef EMBER_AF_ENABLE_FRAGMENTATION
EmberEventControl emAfFragmentationEventControl;

#ifdef EZSP_HOST
static int16u emberApsAckTimeoutMs    = 0;
static int8u  emberFragmentWindowSize = 0;
#else //EZSP_HOST
extern int8u  emberFragmentWindowSize;
#endif //EZSP_HOST

void emAfFragmentationInit(void)
{
#ifdef EZSP_HOST
  int16u value;
  ezspGetConfigurationValue(EZSP_CONFIG_APS_ACK_TIMEOUT,      &emberApsAckTimeoutMs);
  ezspGetConfigurationValue(EZSP_CONFIG_FRAGMENT_WINDOW_SIZE, &value);
  emberFragmentWindowSize = (int8u)value;
#endif //EZSP_HOST
}

//------------------------------------------------------------------------------
// Sending

static EmberStatus sendNextFragments(void);
static void abortTransmission(EmberStatus status);

static EmberOutgoingMessageType  txMessageType = 0xFF;
static int16u                    txIndexOrDestination;
static EmberApsFrame             txApsFrame;
#ifdef EZSP_APPLICATION_HAS_ROUTE_RECORD_HANDLER
static boolean                   txSourceRoute;
static int8u                     txRelayCount;
static int16u                    txRelayList[ZA_MAX_HOPS];
#endif //EZSP_APPLICATION_HAS_ROUTE_RECORD_HANDLER
static int8u                    *txBuffer;
static int16u                    txBufLen;
static int8u                     txFragmentLen;
static int8u                     txFragmentCount;
static int8u                     txFragmentBase;
static int8u                     txFragmentsInTransit;

EmberStatus emAfFragmentationSendUnicast(EmberOutgoingMessageType type,
                                         int16u indexOrDestination,
                                         EmberApsFrame *apsFrame,
                                         int8u *buffer,
                                         int16u bufLen)
{
  EmberStatus status;
  int16u fragments;

  if (emberFragmentWindowSize == 0) {
    return EMBER_INVALID_CALL;
  }

  // Only one fragmented message can be transmitted at a time.
  if (txMessageType != 0xFF) {
    return EMBER_MAX_MESSAGE_LIMIT_REACHED;
  }

  txMessageType = type;
  txIndexOrDestination = indexOrDestination;
  MEMCOPY(&txApsFrame, apsFrame, sizeof(EmberApsFrame));
  txApsFrame.options |= (EMBER_APS_OPTION_FRAGMENT | EMBER_APS_OPTION_RETRY);
#ifdef EZSP_APPLICATION_HAS_ROUTE_RECORD_HANDLER
  txSourceRoute = emberFindSourceRoute(indexOrDestination,
                                       &txRelayCount,
                                       txRelayList);
#endif //EZSP_APPLICATION_HAS_ROUTE_RECORD_HANDLER
  txBuffer = buffer;
  txBufLen = bufLen;
  txFragmentLen = emberAfMaximumApsPayloadLength(type,
                                                 indexOrDestination,
                                                 &txApsFrame);
  fragments = ((bufLen + txFragmentLen - 1) / txFragmentLen);
  if (fragments > MAX_INT8U_VALUE) {
    return EMBER_MESSAGE_TOO_LONG;
  }
  txFragmentCount = (int8u)fragments;
  txFragmentBase = 0;
  txFragmentsInTransit = 0;

  status = sendNextFragments();
  if (status != EMBER_SUCCESS) {
    txMessageType = 0xFF;
  }
  return status;
}

boolean emAfFragmentationMessageSent(EmberApsFrame *apsFrame,
                                     EmberStatus status)
{
  if (apsFrame->options & EMBER_APS_OPTION_FRAGMENT) {
    if (status == EMBER_SUCCESS) {
      txFragmentsInTransit--;
      if (txFragmentsInTransit == 0) {
        txFragmentBase += emberFragmentWindowSize;
        abortTransmission(sendNextFragments());
      }
    } else {
      abortTransmission(status);
    }
    return TRUE;
  } else {
    return FALSE;
  }
}

static EmberStatus sendNextFragments(void)
{
  int16u offset = txFragmentBase * txFragmentLen;
  int8u i;

  // Send fragments until the window is full.
  for (i = txFragmentBase;
       i < txFragmentBase + emberFragmentWindowSize && i < txFragmentCount;
       i++) {
    EmberStatus status;

    // For a message requiring n fragments, the length of each of the first
    // n - 1 fragments is the maximum fragment size.  The length of the last
    // fragment is whatever is leftover.
    int8u fragmentLen = (offset + txFragmentLen < txBufLen
                         ? txFragmentLen
                         : txBufLen - offset);

    txApsFrame.groupId = HIGH_LOW_TO_INT(txFragmentCount, i);

#ifdef EZSP_HOST
#ifdef EZSP_APPLICATION_HAS_ROUTE_RECORD_HANDLER
    if (txSourceRoute) {
      status = ezspSetSourceRoute(txIndexOrDestination,
                                  txRelayCount,
                                  txRelayList);
      if (status != EMBER_SUCCESS) {
        return status;
      }
    }
#endif //EZSP_APPLICATION_HAS_ROUTE_RECORD_HANDLER
    status = ezspSendUnicast(txMessageType,
                             txIndexOrDestination,
                             &txApsFrame,
                             i,
                             fragmentLen,
                             txBuffer + offset,
                             &txApsFrame.sequence);
#else //EZSP_HOST
    {
      EmberMessageBuffer message;
      message = emberFillLinkedBuffers(txBuffer + offset, fragmentLen);
      if (message == EMBER_NULL_MESSAGE_BUFFER) {
        return EMBER_NO_BUFFERS;
      }
      status = emberSendUnicast(txMessageType,
                                txIndexOrDestination,
                                &txApsFrame,
                                message);
      emberReleaseMessageBuffer(message);
    }
#endif //EZSP_HOST

    if (status != EMBER_SUCCESS) {
      return status;
    }

    txFragmentsInTransit++;
    offset += fragmentLen;
  }

  if (txFragmentsInTransit == 0) {
    txMessageType = 0xFF;
    emAfFragmentationMessageSentHandler(txMessageType,
                                        txIndexOrDestination,
                                        &txApsFrame,
                                        txBuffer,
                                        txBufLen,
                                        EMBER_SUCCESS);
  }

  return EMBER_SUCCESS;
}

static void abortTransmission(EmberStatus status)
{
  if (status != EMBER_SUCCESS && txMessageType != 0xFF) {
    emAfFragmentationMessageSentHandler(txMessageType,
                                        txIndexOrDestination,
                                        &txApsFrame,
                                        txBuffer,
                                        txBufLen,
                                        status);
    txMessageType = 0xFF;
  }
}

//------------------------------------------------------------------------------
// Receiving.

#define lowBitMask(n) ((1 << (n)) - 1)
static void setFragmentMask(void);
static boolean storeRxFragment(int8u fragment, int8u *buffer, int16u bufLen);

static int8u       rxBuffer[EMBER_AF_FRAGMENT_BUFFER_SIZE];
static EmberNodeId rxFragmentSource = EMBER_NULL_NODE_ID;
static int8u       rxFragmentSequenceNumber;
static int8u       rxFragmentBase;
static int8u       rxFragmentsExpected;
static int8u       rxFragmentsReceived;

static int8u       rxFragmentMask;
static int8u       rxFragmentLens[EMBER_AF_FRAGMENTATION_MAXIMUM_RECEIVED_FRAGMENTS];

boolean emAfFragmentationIncomingMessage(EmberApsFrame *apsFrame,
                                         EmberNodeId sender,
                                         int8u **buffer,
                                         int16u *bufLen)
{
  boolean newFragment;
  int8u fragment;
  int8u mask;

  if (!(apsFrame->options & EMBER_APS_OPTION_FRAGMENT)) {
    return FALSE;
  }

  fragment = LOW_BYTE(apsFrame->groupId);

  if (rxFragmentSource == EMBER_NULL_NODE_ID
      && fragment < emberFragmentWindowSize) {
    rxFragmentSource = sender;
    rxFragmentSequenceNumber = apsFrame->sequence;
    rxFragmentBase = 0;
    rxFragmentsReceived = 0;
    rxFragmentsExpected = 0xFF;
    setFragmentMask();
    MEMSET(rxFragmentLens, 0, EMBER_AF_FRAGMENTATION_MAXIMUM_RECEIVED_FRAGMENTS);
    emberEventControlSetDelayMS(emAfFragmentationEventControl,
                                (emberApsAckTimeoutMs
                                 * ZIGBEE_APSC_MAX_TRANSMIT_RETRIES));
  }

  if (rxFragmentSource != sender
      || rxFragmentSequenceNumber != apsFrame->sequence) {
    return TRUE;
  }

  if (rxFragmentMask == 0xFF
      && rxFragmentBase + emberFragmentWindowSize <= fragment) {
    rxFragmentBase += emberFragmentWindowSize;
    setFragmentMask();
    emberEventControlSetDelayMS(emAfFragmentationEventControl,
                                (emberApsAckTimeoutMs
                                 * ZIGBEE_APSC_MAX_TRANSMIT_RETRIES));
  }

  if (rxFragmentBase + emberFragmentWindowSize <= fragment) {
    return TRUE;
  }

  mask = 1 << (fragment % emberFragmentWindowSize);
  newFragment = !(mask & rxFragmentMask);

  if (fragment == 0) {
    rxFragmentsExpected = HIGH_BYTE(apsFrame->groupId);
    if (rxFragmentsExpected < emberFragmentWindowSize) {
      setFragmentMask();
    }
    if (rxFragmentsExpected > EMBER_AF_FRAGMENTATION_MAXIMUM_RECEIVED_FRAGMENTS) {
      goto kickout;
    }
  }

  rxFragmentMask |= mask;
  if (newFragment) {
    rxFragmentsReceived++;
    if (!storeRxFragment(fragment, *buffer, *bufLen)) {
      goto kickout;
    }
  }

  if (fragment == rxFragmentsExpected - 1
      || (rxFragmentMask | lowBitMask(fragment % emberFragmentWindowSize)) == 0xFF) {
#ifdef EZSP_HOST
    apsFrame->groupId = HIGH_LOW_TO_INT(rxFragmentMask, rxFragmentBase);
    ezspSendReply(sender, apsFrame, 0, NULL);
#else //EZSP_HOST
    emberSetReplyFragmentData(HIGH_LOW_TO_INT(rxFragmentMask, rxFragmentBase));
    emberSendReply(apsFrame->clusterId, EMBER_NULL_MESSAGE_BUFFER);
#endif //EZSP_HOST
  }

  if (rxFragmentsReceived == rxFragmentsExpected) {
    int16u length = 0;
    int8u i;
    for (i = 0; i < rxFragmentsExpected; i++) {
      length += rxFragmentLens[i];
    }
    rxFragmentSource = EMBER_NULL_NODE_ID;

    // This library sends replies for all fragments, so, before passing on the
    // reassembled message, clear the retry bit to prevent the application from
    // sending a duplicate reply.
    apsFrame->options &= ~EMBER_APS_OPTION_RETRY;

    *bufLen = length;
    *buffer = rxBuffer;
    return FALSE;
  }
  return TRUE;

kickout:
  emAfFragmentationAbortReception();
  return TRUE;
}

void emAfFragmentationAbortReception(void)
{
  emberEventControlSetInactive(emAfFragmentationEventControl);
  if (rxFragmentSource != EMBER_NULL_NODE_ID) {
    rxFragmentSource = EMBER_NULL_NODE_ID;
  }
}

static void setFragmentMask(void)
{
  // Unused bits must be 1.
  int8u highestZeroBit = emberFragmentWindowSize;
  // If we are in the final window, there may be additional unused bits.
  if (rxFragmentsExpected < rxFragmentBase + emberFragmentWindowSize) {
    highestZeroBit = (rxFragmentsExpected % emberFragmentWindowSize);
  }
  rxFragmentMask = ~ lowBitMask(highestZeroBit);
}

static boolean storeRxFragment(int8u fragment, int8u *buffer, int16u bufLen)
{
  int16u index = 0;
  int8u i;
  for (i = 0; i < fragment; i++) {
    index += rxFragmentLens[i];
  }
  if (index + bufLen > EMBER_AF_FRAGMENT_BUFFER_SIZE) {
    return FALSE;
  }
  MEMCOPY(rxBuffer + index + bufLen,
          rxBuffer + index,
          EMBER_AF_FRAGMENT_BUFFER_SIZE - (index + bufLen));
  MEMCOPY(rxBuffer + index, buffer, bufLen);
  rxFragmentLens[fragment] = bufLen;
  return TRUE;
}
#endif //EMBER_AF_ENABLE_FRAGMENTATION
