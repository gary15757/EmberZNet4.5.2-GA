// *******************************************************************
// * messaging-client.c
// *
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "../../util/common.h"
#include "messaging-client.h"
#include "gen/messaging-client-callback.h"

static EmberAfPluginMessagingClientMessage message;

void emberAfMessagingClusterClientInitCallback(int8u endpoint)
{
  message.valid             = FALSE;
  message.active            = FALSE;
  message.messageId         = 0x00000000UL;
  message.messageControl    = 0x00;
  message.startTime         = 0x00000000UL;
  message.endTime           = 0x00000000UL;
  message.durationInMinutes = 0x0000;
  message.message[0]        = 0;
}

void emberAfMessagingClusterClientTickCallback(int8u endpoint)
{
  // The tick is used to deactivate messages that are active or to activate
  // messages that are inactive.  So, first, just flip the active state and
  // notify the application of the change.
  message.active = !message.active;
  if (message.active) {
    emberAfPluginMessagingClientDisplayMessageCallback(&message);
  } else {
    emberAfPluginMessagingClientCancelMessageCallback(&message);
  }

  // If the new state is active and the duration is not "until changed," then we
  // have to schedule a tick to deactivate the message after the duration has
  // elapsed.  Otherwise, cancel the tick because no further processing is
  // required as either the message is no longer active or it will live until
  // changed.
  if (message.active
      && (message.durationInMinutes
          != ZCL_MESSAGING_CLUSTER_DURATION_UNTIL_CHANGED)) {
    emberAfScheduleClusterTick(endpoint,
                               ZCL_MESSAGING_CLUSTER_ID,
                               EMBER_AF_CLIENT_CLUSTER_TICK,
                               ((message.endTime - message.startTime)
                                * MILLISECOND_TICKS_PER_SECOND),
                               EMBER_AF_OK_TO_HIBERNATE);
  }
}

boolean emberAfMessagingClusterDisplayMessageCallback(int32u messageId,
                                                      int8u messageControl,
                                                      int32u startTime,
                                                      int16u durationInMinutes,
                                                      int8u* msg)
{
  int32u now = emberAfGetCurrentTime();

  emberAfMessagingClusterPrint("RX: DisplayMessage"
                               " 0x%4x, 0x%x, 0x%4x, 0x%2x, \"",
                               messageId,
                               messageControl,
                               startTime,
                               durationInMinutes);
  emberAfMessagingClusterPrintString(msg);
  emberAfMessagingClusterPrintln("\"");

  // If we already have a message, notify the application that it should no
  // longer display it.
  if (message.active) {
    message.active = FALSE;
    emberAfPluginMessagingClientCancelMessageCallback(&message);
    emberAfDeactivateClusterTick(emberAfCurrentEndpoint(),
                                 ZCL_MESSAGING_CLUSTER_ID,
                                 EMBER_AF_CLIENT_CLUSTER_TICK);
  }

  // The source and destination are stored so that Message Confirmation commands
  // can be sent asynchronously.
  emberLookupEui64ByNodeId(emberAfCurrentCommand()->source, message.server);
  message.serverEndpoint = emberAfCurrentCommand()->apsFrame->sourceEndpoint;
  message.clientEndpoint = emberAfCurrentCommand()->apsFrame->destinationEndpoint;

  message.messageId         = messageId;
  message.messageControl    = messageControl;
  message.startTime         = (startTime == ZCL_MESSAGING_CLUSTER_START_TIME_NOW
                               ? now
                               : startTime);
  message.endTime           = (durationInMinutes == ZCL_MESSAGING_CLUSTER_DURATION_UNTIL_CHANGED
                               ? ZCL_MESSAGING_CLUSTER_END_TIME_NEVER
                               : message.startTime + durationInMinutes * 60);
  message.durationInMinutes = durationInMinutes;
  emberAfCopyString(message.message, msg, EMBER_AF_PLUGIN_MESSAGING_CLIENT_MESSAGE_SIZE);

  if (message.startTime <= now) {
    if (message.durationInMinutes
        == ZCL_MESSAGING_CLUSTER_DURATION_UNTIL_CHANGED) {
      // If a message starts in the past and the duration is "until changed," it
      // gets marked as active and no tick is scheduled becaues the message will
      // live until we receive a new message or a cancel command.
      message.active = TRUE;
      emberAfPluginMessagingClientDisplayMessageCallback(&message);
    } else if (message.endTime > now) {
      // If a message starts in the past and the duration has not elapsed, it
      // gets marked as active and a tick is scheduled for the time remaining in
      // the duration to wake us up and mark the message as inactive.
      message.active = TRUE;
      emberAfPluginMessagingClientDisplayMessageCallback(&message);
      emberAfScheduleClusterTick(emberAfCurrentEndpoint(),
                                 ZCL_MESSAGING_CLUSTER_ID,
                                 EMBER_AF_CLIENT_CLUSTER_TICK,
                                 ((message.endTime - now)
                                  * MILLISECOND_TICKS_PER_SECOND),
                                 EMBER_AF_OK_TO_HIBERNATE);
    } else {
      // Finally, if a message starts in the past and the duration has elapsed,
      // it gets marked as inactive and no tick is scheduled because no further
      // processing is needed.
      message.active = FALSE;
    }
  } else {
    // If a message starts in the future, it gets marked as inactive and a tick
    // is scheduled to wake us up at startTime to mark the message as active.
    message.active = FALSE;
    emberAfScheduleClusterTick(emberAfCurrentEndpoint(),
                               ZCL_MESSAGING_CLUSTER_ID,
                               EMBER_AF_CLIENT_CLUSTER_TICK,
                               ((message.startTime - now)
                                * MILLISECOND_TICKS_PER_SECOND),
                               EMBER_AF_OK_TO_HIBERNATE);
  }

  // Once we receive a message, the data in the structure becomes valid and
  // remains valid forever.  When the message expires or is canceled, it gets
  // marked as inactive, but stays valid.  This allows the application to
  // display or confirm old messages.
  message.valid = TRUE;

  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

boolean emberAfMessagingClusterCancelMessageCallback(int32u messageId,
                                                     int8u messageControl)
{
  EmberAfStatus status;

  emberAfMessagingClusterPrintln("RX: CancelMessage 0x%4x, 0x%x",
                                 messageId,
                                 messageControl);

  if (message.active && message.messageId == messageId) {
    message.active = FALSE;
    message.messageControl = messageControl;
    emberAfPluginMessagingClientCancelMessageCallback(&message);
    emberAfDeactivateClusterTick(emberAfCurrentEndpoint(),
                                 ZCL_MESSAGING_CLUSTER_ID,
                                 EMBER_AF_CLIENT_CLUSTER_TICK);
    status = EMBER_ZCL_STATUS_SUCCESS;
  } else {
    status = EMBER_ZCL_STATUS_NOT_FOUND;
  }

  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}

void emAfPluginMessagingClientPrintInfo(void)
{
  emberAfMessagingClusterPrintln("= Client Message =");
  emberAfMessagingClusterFlush();

  emberAfMessagingClusterPrintln(" vld: %p", (message.valid ? "YES" : "NO"));
  emberAfMessagingClusterPrintln(" act: %p", (message.active ? "YES" : "NO"));
  emberAfMessagingClusterPrintln("  id: 0x%4x", message.messageId);
  emberAfMessagingClusterPrintln("  mc: 0x%x",  message.messageControl);
  emberAfMessagingClusterPrintln("  st: 0x%4x", message.startTime);
  emberAfMessagingClusterPrintln("  et: 0x%4x", message.endTime);
  emberAfMessagingClusterPrintln("time: 0x%4x", emberAfGetCurrentTime());
  emberAfMessagingClusterPrintln(" dur: 0x%2x", message.durationInMinutes);
  emberAfMessagingClusterFlush();
  emberAfMessagingClusterPrint(  " mes: \"");
  emberAfMessagingClusterPrintString(message.message);
  emberAfMessagingClusterPrintln("\"");
  emberAfMessagingClusterFlush();
}

EmberAfStatus emberAfPluginMessagingClientConfirmMessage(void)
{
  EmberAfStatus status = EMBER_ZCL_STATUS_NOT_FOUND;
  if (message.valid) {
    EmberNodeId nodeId = emberLookupNodeIdByEui64(message.server);
    emberAfFillCommandMessagingClusterMessageConfirmation(message.messageId,
                                                          emberAfGetCurrentTime());
    // The source and destination are reversed for the confirmation.
    emberAfGetCommandApsFrame()->sourceEndpoint      = message.clientEndpoint;
    emberAfGetCommandApsFrame()->destinationEndpoint = message.serverEndpoint;
    status = ((emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, nodeId)
               == EMBER_SUCCESS)
              ? EMBER_ZCL_STATUS_SUCCESS
              : EMBER_ZCL_STATUS_FAILURE);
  }
  return status;
}
