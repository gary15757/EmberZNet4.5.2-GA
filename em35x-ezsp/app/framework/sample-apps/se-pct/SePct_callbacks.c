// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
//
//

// This callback file is created for your convenience. You may add application code
// to this file. If you regenerate this file over a previous version, the previous
// version will be overwritten and any code you have added will be lost.

#include "app/framework/include/af.h"


/** @brief Event Action
 *
 * This function is called by the demand response and load control client
 * plugin whenever an event status changes within the DRLC event table.  The
 * list of possible event status values is defined by the ZCL spec and is
 * listed in the Application Framework's generated enums located at
 * app/framework/gen/enums.h.  For example, an event status may be:
 * AMI_EVENT_STATUS_LOAD_CONTROL_EVENT_COMMAND_RX indicating that a properly
 * formatted event was received; AMI_EVENT_STATUS_EVENT_STARTED indicating
 * that an event has started; AMI_EVENT_STATUS_THE_EVENT_HAS_BEEN_CANCELED,
 * indicating that the event was canceled.  This callback is intended to give
 * the device an opportunity to take action on the event in question.  For
 * instance if an event starts, the device should take the appropriate event
 * action on the hardware.  This callback returns a boolean, if returned value
 * is true, then a notification will be send over the air automatically to the
 * originator of the event.  If it is false, then nothing will be sent back to
 * the originator of the event.  Please note that in order for your
 * application to be ZigBee compliant, a notification must be sent over the
 * air to the originator of the event, so a value of FALSE should only be
 * returned if your application code takes care of sending this message or
 * there is some other reason a message does not need to be sent by the
 * framework.
 *
 * @param loadControlEvent Actual event  Ver.: always
 * @param eventStatus Status of event  Ver.: always
 * @param sequenceNumber Sequence number  Ver.: always
 */
boolean emberAfPluginDrlcEventActionCallback(EmberAfLoadControlEvent * loadControlEvent,
                                             EmberAfAmiEventStatus eventStatus,
                                             int8u sequenceNumber)
{
  return TRUE;
}

/** @brief Finished
 *
 * This callback is fired when the network-find plugin is finished with the
 * forming or joining process.  The result of the operation will be returned
 * in the status parameter.
 *
 * @param status   Ver.: always
 */
void emberAfPluginNetworkFindFinishedCallback(EmberStatus status) {
  
}
