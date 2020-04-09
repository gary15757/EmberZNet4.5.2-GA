// *******************************************************************
// * messaging-server.c
// *
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "messaging-server.h"

static EmberAfMessagingServerMessage message;

void emberAfMessagingClusterServerInitCallback(int8u endpoint)
{
  message.valid             = FALSE;
  message.messageId         = 0x00000000;
  message.messageControl    = 0x00;
  message.startTime         = 0x00000000;
  message.durationInMinutes = 0x0000;
  message.message[0]        = 0;
}

boolean emberAfMessagingClusterGetLastMessageCallback(void)
{
  emberAfMessagingClusterPrintln("RX: GetLastMessage");

  if (message.valid) {
    emberAfFillCommandMessagingClusterDisplayMessage(message.messageId,
                                                     message.messageControl,
                                                     message.startTime,
                                                     message.durationInMinutes,
                                                     message.message);
    emberAfGetCommandApsFrame()->options |= EMBER_APS_OPTION_SOURCE_EUI64;
    emberAfSendResponse();
  } else {
    emberAfSendDefaultResponse(emberAfCurrentCommand(),
                               EMBER_ZCL_STATUS_NOT_FOUND);
  }
  return TRUE;
}

boolean emberAfMessagingClusterMessageConfirmationCallback(int32u messageId,
                                                           int32u confirmationTime)
{
  emberAfMessagingClusterPrintln("RX: MessageConfirmation 0x%4x, 0x%4x",
                                 messageId,
                                 confirmationTime);
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

void emAfPluginMessagingServerPrintInfo(void)
{
  emberAfMessagingClusterPrintln("= Server Message =");
  emberAfMessagingClusterFlush();

  emberAfMessagingClusterPrintln(" vld: %p",   (message.valid 
                                                ? "YES" 
                                                : "NO"));
  emberAfMessagingClusterPrintln("  id: 0x%4x", message.messageId);
  emberAfMessagingClusterPrintln("  mc: 0x%x",  message.messageControl);
  emberAfMessagingClusterPrintln("  st: 0x%4x", message.startTime);
  emberAfMessagingClusterPrintln("time: 0x%4x", emberAfGetCurrentTime());
  emberAfMessagingClusterPrintln(" dur: 0x%2x", message.durationInMinutes);
  emberAfMessagingClusterFlush();
  emberAfMessagingClusterPrint(  " mes: \"");
  emberAfMessagingClusterPrintString(message.message);
  emberAfMessagingClusterPrintln("\"");
  emberAfMessagingClusterFlush();
}

EmberAfMessagingServerMessage *emAfPluginMessagingServerGetMessageStruct(void)
{
  return &message;
}
