// *******************************************************************
// * drlc-server.h
// *
// * This is an implementation of a drlc server which is intended to 
// * be used for testing only. Generally it is expected that the drlc
// * server will act as a passthrough for drlc events and will not maintain
// * a list of scheduled events of its own. However for testing purposes
// * it is highly useful to have the server store scheduled events so that
// * - minus a backend - the ESP can respond to get scheduled events
// * commands.
// * 
// * There are a couple things about
// * this code that make it incomplete as an actual drlc server table
// *
// * 1. Scheduled events are not stored in persistent memory, which they
// *    would have to be if this were intended for an ESP which for some
// *    reason were storing events.
// *
// * 2. It is possible to schedule an event with time 0x0000, which when
// *    retrieved means start this event now. If this is active for all
// *    time then the event will always start now, whatever now might be.
// *
// * Note: The EmberAfLoadControlEvent source field is used to activate 
// * / deactivate an event. If the field is set to 0xffff, then 
// * the event is considered inactive, If it is set to 0x0000 then the 
// * event is considered active.
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af-types.h"

#ifndef EMBER_AF_PLUGIN_DRLC_SERVER_SCHEDULED_EVENT_TABLE_SIZE
  #define  EMBER_AF_PLUGIN_DRLC_SERVER_SCHEDULED_EVENT_TABLE_SIZE 2
#endif //EMBER_AF_PLUGIN_DRLC_SERVER_SCHEDULED_EVENT_TABLE_SIZE

// used by the cli to clear all scheduled events in the drlc server
void emAfClearScheduledLoadControlEvents(void);

// returns a pointer to the next free scheduled load control event table entry
// or NULL if none exists. 
EmberAfLoadControlEvent *emAfGetScheduledLoadControlEvent(int8u index);

void emAfPluginDrlcServerPrintInfo(void);
