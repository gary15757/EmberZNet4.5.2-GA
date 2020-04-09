// *****************************************************************************
// * fragmentation.h
// *
// * Splits long messages into smaller blocks for transmission and reassembles
// * received blocks.
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#ifndef EMBER_AF_FRAGMENTATION_MAXIMUM_RECEIVED_FRAGMENTS
#define EMBER_AF_FRAGMENTATION_MAXIMUM_RECEIVED_FRAGMENTS 30
#endif //EMBER_AF_FRAGMENTATION_MAXIMUM_RECEIVED_FRAGMENTS

#ifndef ZIGBEE_APSC_MAX_TRANSMIT_RETRIES
#define ZIGBEE_APSC_MAX_TRANSMIT_RETRIES 3
#endif //ZIGBEE_APSC_MAX_TRANSMIT_RETRIES

extern EmberEventControl emAfFragmentationEventControl;

void emAfFragmentationInit(void);

//------------------------------------------------------------------------------
// Sending

EmberStatus emAfFragmentationSendUnicast(EmberOutgoingMessageType type,
                                         int16u indexOrDestination,
                                         EmberApsFrame *apsFrame,
                                         int8u *buffer,
                                         int16u bufLen);

boolean emAfFragmentationMessageSent(EmberApsFrame *apsFrame,
                                     EmberStatus status);

void emAfFragmentationMessageSentHandler(EmberOutgoingMessageType type,
                                         int16u indexOrDestination,
                                         EmberApsFrame *apsFrame,
                                         int8u *buffer,
                                         int16u bufLen,
                                         EmberStatus status);

//------------------------------------------------------------------------------
// Receiving.

boolean emAfFragmentationIncomingMessage(EmberApsFrame *apsFrame,
                                         EmberNodeId sender,
                                         int8u **buffer,
                                         int16u *bufLen);

void emAfFragmentationAbortReception(void);
