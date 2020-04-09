// *******************************************************************
// * messaging-server.h
// *
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// ----------------------------------------------------------------------------
// Message Control byte
// ----------------------------------------------------------------------------

#define ZCL_MESSAGING_CLUSTER_TRANSMISSION_MASK (BIT(1) | BIT(0))
#define ZCL_MESSAGING_CLUSTER_IMPORTANCE_MASK   (BIT(3) | BIT(2))
#define ZCL_MESSAGING_CLUSTER_CONFIRMATION_MASK BIT(7)

#define ZCL_MESSAGING_CLUSTER_START_TIME_NOW         0x00000000UL
#define ZCL_MESSAGING_CLUSTER_END_TIME_NEVER         0xFFFFFFFFUL
#define ZCL_MESSAGING_CLUSTER_DURATION_UNTIL_CHANGED 0xFFFF

typedef struct {
  boolean valid;
  int32u  messageId;
  int8u   messageControl;
  int32u  startTime;
  int16u  durationInMinutes;
  int8u   message[EMBER_AF_PLUGIN_MESSAGING_SERVER_MESSAGE_SIZE + 1];
} EmberAfMessagingServerMessage;

void emAfPluginMessagingServerPrintInfo(void);
EmberAfMessagingServerMessage *emAfPluginMessagingServerGetMessageStruct(void);
