// *******************************************************************
// * af-main-soc.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "app/framework/include/af.h"

#include "stack/include/event.h"         // Event related api

// Attribute storage info
#include "app/framework/util/attribute-storage.h"

#include "app/util/serial/serial.h"  // Serial utility APIs

// ZDO
#include "app/util/zigbee-framework/zigbee-device-common.h"
#include "app/util/zigbee-framework/zigbee-device-library.h"

// Counters - Stack counters library
#include "app/util/counters/counters.h"

// Network Utilities (form, join and associated scan code)
#include "app/util/common/form-and-join.h"

// service discovery
#include "app/framework/util/service-discovery.h"

// fragmentation
#include "app/framework/util/fragmentation.h"

// Security Address Cache
#include "app/util/security/security.h"

#include "app/framework/plugin/partner-link-key-exchange/partner-link-key-exchange.h"

// determines the number of in-clusters and out-clusters based on defines
// in config.h
#include "app/framework/util/af-main.h"

// CLI - command line interface
#include "app/util/serial/command-interpreter2.h"

#include "app/framework/cli/core-cli.h"
#include "app/framework/cli/custom-cli.h"
#include "app/framework/cli/network-cli.h"
#include "app/framework/cli/plugin-cli.h"
#include "app/framework/cli/security-cli.h"
#include "app/framework/cli/zcl-cli.h"
#include "app/framework/cli/zdo-cli.h"

// Needed for zaTrustCenterSecurityInit() and zaNodeSecurityInit()
#include "app/framework/security/af-security.h"

#include "app/framework/util/util.h"

// Information about stack libraries
#include "app/util/common/library.h"

#include "app/framework/util/af-eeprom.h"

#include "app/framework/plugin/test-harness/test-harness-cli.h"

// A global used to schedule the polling event
int32u emAfPollIntervalTime = 0;

// Set the default hibernate duration defined by the application header
// provided as a global here so that it can be modified at runtime.
int32u emberAfHibernateDuration = EMBER_AF_LONG_POLL_INTERVAL;

// Set the default nap duration defined by the application header
// provided as a global here so that it can be modified at runtime.
int32u emberAfNapDuration = EMBER_AF_SHORT_POLL_INTERVAL;

// **************************************************
// defines that can be turned off to save space

// APP_SERIAL is set in the project files

int8u serialPort = APP_SERIAL;

// ******************************************************************
// Forward declarations.
static void appTick(void);

// for very basic commands only
void tinySerialInputTick(void);

// fwd declare
void emAfSchedulePollEvent(void);
void emAfCheckForSleep(void);
void emAfFullSleep(int32u sleepDurationMS);

#include "app/util/concentrator/concentrator.h"

#if defined(ZA_DEVICE_IS_SLEEPY) || defined(ZA_DEVICE_IS_NONSLEEPY_END_DEVICE)
EmberEventControl emAfPollEventControl;
void emAfPollEvent(void);
#endif

// Endpoint index that will be sent next time button0 is pressed.
int8u afEndDevEndpointNextSend = 0;

#if (EMBER_AF_BAUD_RATE == 9600)
  #define BAUD_RATE BAUD_9600
#elif (EMBER_AF_BAUD_RATE == 19200)
  #define BAUD_RATE BAUD_19200
#elif (EMBER_AF_BAUD_RATE == 38400)
  #define BAUD_RATE BAUD_38400
#elif (EMBER_AF_BAUD_RATE == 115200) 
  #define BAUD_RATE BAUD_115200
#elif (EMBER_AF_BAUD_RATE == 230400)
  #define BAUD_RATE BAUD_230400
#elif (EMBER_AF_BAUD_RATE == 460800)
  #define BAUD_RATE BAUD_460800
#else
  #error EMBER_AF_BAUD_RATE not set
#endif

// *******************************************************************
// *******************************************************************
// The main() loop and the application's contribution.

void main(void)
{
  EmberStatus status;
  int8u reset;

  // Determine the cause of the reset (powerup, etc).
  reset = halGetResetInfo();

  //Initialize the hal
  halInit();
  INTERRUPTS_ON();  // Safe to enable interrupts at this point

  // Initialize the Ember Stack.
  status = emberInit();

#ifdef DEBUG
  emberDebugInit(0);  // Use serial port 0 for debug output
#endif

  emberSerialInit(APP_SERIAL, BAUD_RATE, PARITY_NONE, 1);

  emberAfCorePrintln("Reset info: 0x%x", reset);

  if (status != EMBER_SUCCESS) {
    emberAfCorePrintln("%pemberInit 0x%x", "ERROR: ", status);

    // The app can choose what to do here.  If the app is running
    // another device then it could stay running and report the
    // error visually for example. This app asserts.
    assert(FALSE);
  } else {
    emberAfDebugPrintln("init pass");
  }

  emberAfEndpointConfigure();
  emberAfMainInitCallback();

  emberAfInit();

  emberAfInterpanInitCallback();

  // The address cache needs to be initialized and used with the source routing
  // code for the trust center to operate properly.
  securityAddressCacheInit(EMBER_AF_ADDRESS_TABLE_SIZE,               // offset
                           EMBER_AF_TRUST_CENTER_ADDRESS_CACHE_SIZE); // size

#if ZA_DEVICE_TYPE == ZA_COORDINATOR
  // Always do this on boot to assure that the correct security policies
  // are in place.
  zaTrustCenterSecurityPolicyInit();
#endif

  // network init if possible - the node type this device was previously
  // needs to match or the device can be a ZC and joined a network as a ZR.
  {
    EmberNodeType nodeType;
    if (((emberGetNodeType(&nodeType)) == EMBER_SUCCESS)
        && ((nodeType == ZA_DEVICE_TYPE) 
            || ((nodeType == EMBER_ROUTER) 
                && (ZA_DEVICE_TYPE == ZA_COORDINATOR))
            )
        ) {
      emAfNetworkInit();
    }
  }

#if defined(ZA_CLI_MINIMAL) || defined(ZA_CLI_FULL)
  emberCommandReaderInit();
#endif //defined(ZA_CLI_MINIMAL) || defined(ZA_CLI_FULL)

  // Set the manufacturing code. This is defined by ZigBee document 053874r10
  // Ember's ID is 0x1002
  emberSetManufacturerCode(EMBER_AF_MANUFACTURER_CODE);

  emberSetMaximumIncomingTransferSize(EMBER_AF_INCOMING_BUFFER_LENGTH);
  emberSetMaximumOutgoingTransferSize(EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH);

  while(TRUE) {
    halResetWatchdog();   // Periodically reset the watchdog.
    emberTick();          // Allow the stack to run.

    // Allow the ZCL clusters to run. This should go immediately after emberTick
    emberAfTick();            

    // Give the app a chance to service events, timers, etc.
    appTick();            

    emberFormAndJoinTick();

#ifdef ZA_TINY_SERIAL_INPUT
    tinySerialInputTick();
#endif //ZA_TINY_SERIAL_INPUT

    emberAfRunEvents();

#if defined(ZA_CLI_MINIMAL) || defined(ZA_CLI_FULL)
    if (emberProcessCommandInput(APP_SERIAL)) {
      emberAfGuaranteedPrint("%p>", ZA_PROMPT);
    }
#endif //defined(ZA_CLI_MINIMAL) || defined(ZA_CLI_FULL)

    #ifdef DEBUG
    emberSerialBufferTick();   // Needed for buffered serial, which debug uses
    #endif
  }
}

void emberAfGetMfgString(int8u* returnData)
{
  halCommonGetMfgToken(returnData, TOKEN_MFG_STRING);
}

EmberNodeId emberAfGetNodeId(void)
{
  return emberGetNodeId();
}

void emberConcentratorRouteDiscoverySentHandler(void)
{
  emberAfDebugPrintln("send MTORR");
}

#ifdef EMBER_AF_CONCENTRATOR
void emberIncomingRouteErrorHandler(EmberStatus status, EmberNodeId target)
{
  emberConcentratorNoteRouteError(status);
}
#endif

// ***********************************************
// appTick
//
// service regular operations of the application
// ***********************************************
static void appTick(void)
{
  static int16u lastBlinkTime = 0;
  int16u time;

#if defined(ZA_DEVICE_IS_SLEEPY) || defined(ZA_DEVICE_IS_NONSLEEPY_END_DEVICE)
    emAfSchedulePollEvent();
#ifdef ZA_DEVICE_IS_SLEEPY
    emAfCheckForSleep();
#endif //ZA_DEVICE_IS_SLEEPY
#endif

  time = halCommonGetInt16uMillisecondTick();

  if ( elapsedTimeInt16u(lastBlinkTime, time) > 200 /*ms*/) {
    // blink the LED
    emAfBlinkHeartbeat();
    lastBlinkTime = time;
     
#ifdef EMBER_AF_USE_BUTTONS
    // **************************************
    // check the buttons for activity
    // button 0: if not joined: FORM if the device is capable of forming
    //           if joined: BIND (send ZDO end dev bind req) 
    // button 1: if not joined: JOIN 
    //           if joined: PERMIT JOINING
    // **************************************
    if (emberAfFirstButtonPressed) {
      emberAfFirstButtonPressed = FALSE;

      if (emberNetworkState() == EMBER_JOINED_NETWORK) {
        // bind
        emberAfZdoPrintln("End device binding:%x", afEndDevEndpointNextSend);
        emberAfSendEndDeviceBind(emberAfEndpointFromIndex(afEndDevEndpointNextSend++));
        if (afEndDevEndpointNextSend >= emberAfEndpointCount()) {
          afEndDevEndpointNextSend = 0;
        }
      } else if (emberNetworkState() == EMBER_NO_NETWORK) {
#if (ZA_DEVICE_TYPE == ZA_COORDINATOR)
        // form
        zaTrustCenterSecurityInit();
        emberAfCorePrintln("%p: nwk down: do form", "button0");
        emberAfFindUnusedPanIdAndForm();
#else
        emberAfCorePrintln("%p: only coordinator can form", "button0");
#endif
      }
    }
    if (emberAfSecondButtonPressed) {
      emberAfSecondButtonPressed = FALSE;

      if (emberNetworkState() == EMBER_JOINED_NETWORK) {
        // permit join
        emberAfCorePrint("%p: ", "button1");
        emAfPermitJoin(60);
      } else if (emberNetworkState() == EMBER_NO_NETWORK) {
        zaNodeSecurityInit();
        emberAfStartSearchForJoinableNetwork();
        emberAfCorePrintln("%p: join", "button1");
      }
    }
#endif //EMBER_AF_USE_BUTTONS
  } // end time check

  // **************************************
  // This sends Many-to-One Route Requests if this device
  // is setup to do that using app/util/concentrator library.  The library
  // handles its own time check, hence, this is done outside the time-check
  // if-statement.
  // **************************************
  #ifdef EMBER_AF_CONCENTRATOR
    emberConcentratorTick();
  #endif //EMBER_AF_CONCENTRATOR

}

// **************************************
// The Polling init and event 
// **************************************
#if defined(ZA_DEVICE_IS_SLEEPY) || defined(ZA_DEVICE_IS_NONSLEEPY_END_DEVICE)

// Schedules the polling event according to what the application and the stack
// currently require. The logic here is pretty simple, if the poll 
// interval has changed or the poll event has been deactivated (because it ran),
// we schedule it.
void emAfSchedulePollEvent(void) {
  boolean changeState = FALSE;
  EmberNetworkStatus state = emberNetworkState();

  // If we are not on a network there is no sense in polling, however
  // if we are joined with no parent we want to keep polling to allow
  // the stack to repair the connection, if this fails we will schedule
  // a move.

  if (state != EMBER_JOINED_NETWORK &&
      state != EMBER_JOINED_NETWORK_NO_PARENT)
    return;

  // Sleepys check hibernate vs. nap, non-sleepys always
  // poll on the long poll interval
#ifdef ZA_DEVICE_IS_SLEEPY
  if (emberOkToHibernate() && 
      emberAfOkToHibernate())
  {
#endif
    if (emAfPollIntervalTime != emberAfHibernateDuration) {
      emAfPollIntervalTime = emberAfHibernateDuration;
      changeState = TRUE;
    }
#ifdef ZA_DEVICE_IS_SLEEPY
  } else {
    if (emAfPollIntervalTime != emberAfNapDuration) {
      emAfPollIntervalTime = emberAfNapDuration;
      changeState = TRUE;
    }
  }
#endif
  if (changeState || !emberEventControlGetActive(emAfPollEventControl)) {
	emberAfEventControlSetDelay(&emAfPollEventControl,
	    (emAfPollIntervalTime * MILLISECOND_TICKS_PER_QUARTERSECOND));	
  }
}


// The poll event, simply deactivates the current event and
// runs the poll.
void emAfPollEvent(void) {
  EmberStatus status;
  EmberNetworkStatus state = emberNetworkState();
  
  emberEventControlSetInactive(emAfPollEventControl);
  
  status = emberPollForData();
  if (status != EMBER_SUCCESS) {
    emberAfCorePrintln("poll: 0x%x", status);
    emberAfCoreFlush();
  }
}

// ***********************************************************************
// emberAfPollCompleteHandler
//
// This function is called when a poll completes. The status explains what
// happened with the poll. This function can tell if the parent responded
// with data, with no data, or didnt respond at all. This function keeps
// track of the failures to communicate to the parent (polls that the 
// parent doesnt ack) and attempts to find a new parent when a threshold
// has been reached. The threshold depends on the type of end device, see
// the comment for pollFailTimeToTriggerMove below for a complete description.
// 
// A regular stack poll complete handler should call this function.
// ***********************************************************************
void emberAfPollCompleteHandler(EmberStatus status)
{  
  static int8u numPollsFailing = 0;  
	
  switch (status) {
  case EMBER_SUCCESS:
    emberAfAddToCurrentAppTasks(EMBER_AF_LAST_POLL_GOT_DATA);
    emberAfDebugPrintln("poll: got data");
    numPollsFailing = 0;
    break;
  case EMBER_MAC_NO_DATA:
    emberAfRemoveFromCurrentAppTasks(EMBER_AF_LAST_POLL_GOT_DATA);
    emberAfDebugPrintln("poll: no data");
    numPollsFailing = 0;
    break;
  case EMBER_DELIVERY_FAILED:
    // this means the air was busy - don't count as a failure
    emberAfRemoveFromCurrentAppTasks(EMBER_AF_LAST_POLL_GOT_DATA);
    emberAfDebugPrintln("poll: delivery failed");
    break;
  case EMBER_MAC_NO_ACK_RECEIVED:
    // If we are performing key establishment, we can ignore this
    // since the parent could go away for long periods of time while
    // doing ecc processes.
    if (emberAfPerformingKeyEstablishment())
      break;
    // Count failures until we hit EMBER_AF_NUM_MISSED_POLLS_TO_TRIGGER_MOVE 
    // then we try a rejoin. If rejoin fails it will trigger a move
    numPollsFailing++;
    if (numPollsFailing >= EMBER_AF_NUM_MISSED_POLLS_TO_TRIGGER_MOVE) {
      emberAfStartMove();
    }
    emberAfRemoveFromCurrentAppTasks(EMBER_AF_LAST_POLL_GOT_DATA);
    break;
  }
  emberAfDebugFlush();
}

#else //(ZA_DEVICE_IS_SLEEPY) || defined(ZA_DEVICE_IS_NONSLEEPY_END_DEVICE)

void emberAfPollCompleteHandler(EmberStatus status)
{}

#endif //(ZA_DEVICE_IS_SLEEPY) || defined(ZA_DEVICE_IS_NONSLEEPY_END_DEVICE)


// **************************************
// This checks if the device can go to sleep and then sleeps for either the
// nap duration or the hibernate duration. It polls on wakeup
// **************************************

// To fix a warning:
int32u emMsToNextStackEvent(void);


#ifdef ZA_DEVICE_IS_SLEEPY
void emAfCheckForSleep(void)
{
  int32u sleepDurationMS = 0;

#ifdef EMBER_AF_STAY_AWAKE_WHEN_NOT_JOINED
  if (emberNetworkState() != EMBER_JOINED_NETWORK)
    return;
#endif //EMBER_AF_STAY_AWAKE_WHEN_NOT_JOINED

  if (emberOkToNap() && emberAfOkToNap()) {
    int32u timeToNextEventMax = MAX_INT32U_VALUE;
    if (emberNetworkState() == EMBER_JOINING_NETWORK) {
      timeToNextEventMax = emMsToNextStackEvent();
    }
    sleepDurationMS = emberAfMsToNextEvent(timeToNextEventMax);
  } else {
    return;
  }

  if (sleepDurationMS > 0) {
    emAfFullSleep(sleepDurationMS);
  }

}

// **************************************
// this puts the device to deep sleep
// **************************************
void emAfFullSleep(int32u sleepDurationMS)
{
  int32u sleepDurationAttemptedMS = sleepDurationMS;

  if (emberAfPreGoToSleepCallback(sleepDurationMS)) {
    return; //User app says don't go to sleep
  }

  // print a message
  emberAfDebugPrintln("sleep %l ms", sleepDurationMS);
  emberAfDebugFlush();

  // turn off the radio
  emberStackPowerDown();
  // this disables interrupts and reenables them once it completes
  ATOMIC(
    // turn off board and peripherals
    halPowerDown();
    // turn micro to power save mode - wakes on external interrupt
    // or when the time specified expires
    halSleepForMilliseconds(&sleepDurationMS);
    // power up board and peripherals
    halPowerUp();
  );
  // power up radio
  emberStackPowerUp();

  emAfNoteEepromInitializedState(FALSE);

  // Allow the stack to time out any of its events and check on its
  // own network state.
  emberTick();

  // Inform the application how long we have slept, sleepDuration has
  // been decremented by the call to halSleepForMilliseconds() by the amount
  // of time that we slept.  To get the actual sleep time we must determine
  // the delta between the amount we asked for and the amount of sleep time
  // LEFT in our request value.
  emberAfPostWakeUpCallback(sleepDurationAttemptedMS - sleepDurationMS);

  // message to know we are awake
  emberAfDebugPrintln("wakeup %l ms", 
		    (sleepDurationAttemptedMS - sleepDurationMS));
  emberAfDebugFlush();
}
#endif //ZA_DEVICE_IS_SLEEPY


// ******************************************************************
// binding
// ******************************************************************
EmberStatus emberAfSendEndDeviceBind(int8u endpoint)
{
  EmberStatus status;
  EmberApsOption options = ((EMBER_AF_DEFAULT_APS_OPTIONS
                             | EMBER_APS_OPTION_SOURCE_EUI64)
                            & ~EMBER_APS_OPTION_RETRY);

  emberAfZdoPrintln("send %x %2x", endpoint, options);
  status = emberEndDeviceBindRequest(endpoint, options);
  emberAfZdoPrintln("done: %x.", status);
  emberAfZdoFlush();
  return status;
}

EmberStatus emberRemoteSetBindingHandler(EmberBindingTableEntry *entry)
{
  EmberStatus status;
  EmberBindingTableEntry candidate;
  int8u i;

  // If we receive a bind request for the Key Establishment cluster and we are
  // not the trust center, then we are doing partner link key exchange.  We
  // don't actually have to create a binding.
  if (emberGetNodeId() != EMBER_TRUST_CENTER_NODE_ID
      && entry->clusterId == ZCL_KEY_ESTABLISHMENT_CLUSTER_ID) {
    return emberAfPartnerLinkKeyExchangeRequestCallback(entry->identifier);
  }

  // first look for a duplicate binding, we should not add duplicates
  for (i = 0; i < EMBER_BINDING_TABLE_SIZE; i++) {
    emberAfZdoPrintln("check bind %x", i);
    if (emberGetBinding(i, &candidate) == EMBER_SUCCESS
        && candidate.type == EMBER_UNICAST_BINDING
        && candidate.local == entry->local
        && candidate.clusterId == entry->clusterId
        && candidate.remote == entry->remote
        && MEMCOMPARE(candidate.identifier,
                      entry->identifier,
                      EUI64_SIZE) == 0) {
      // the binding already exists - this is success
      emberAfZdoPrintln("found dup bind at %x", i);
      return EMBER_SUCCESS;
    }
    emberAfZdoFlush();
  }

  for (i = 0; i < EMBER_BINDING_TABLE_SIZE; i++) {
      // see if the binding is empty
    if (emberGetBinding(i, &candidate) == EMBER_SUCCESS
        && candidate.type == EMBER_UNUSED_BINDING) {
      status = emberSetBinding(i, entry);
      return status;
    }
  }
  // if we make it here we didnt find a free slot
  return EMBER_TABLE_FULL;
}

EmberStatus emberRemoteDeleteBindingHandler(int8u index)
{
  EmberStatus status = emberDeleteBinding(index);
  emberAfZdoPrintln("delete binding: %x %x", index, status);
  return status;
}

// ******************************************************************
// setup endpoints and clusters for responding to ZDO requests
// ******************************************************************
int8u emberGetEndpoint(int8u index)
{
  return emberAfEndpointFromIndex(index);
}

// must return the endpoint desc of the endpoint specified 
boolean emberGetEndpointDescription(int8u endpoint,
                                    EmberEndpointDescription *result)
{
  int8u endpointIndex = emberAfIndexFromEndpoint(endpoint);
  if (endpointIndex == 0xFF) {
    return FALSE;
  }

  result->profileId          = emberAfProfileIdFromIndex(endpointIndex);
  result->deviceId           = emberAfDeviceIdFromIndex(endpointIndex);
  result->deviceVersion      = emberAfDeviceVersionFromIndex(endpointIndex);
  result->inputClusterCount  = emberAfClusterCount(endpoint, TRUE);
  result->outputClusterCount = emberAfClusterCount(endpoint, FALSE);

  return TRUE;
}

// must return the clusterId at listIndex in the list specified for the 
// endpoint specified
int16u emberGetEndpointCluster(int8u endpoint,
                               EmberClusterListId listId,
                               int8u listIndex)
{
  EmberAfCluster *cluster = NULL;
  // no error checking as the error checking happens before the call
  // to this function
  if (listId == EMBER_INPUT_CLUSTER_LIST) {
    cluster = emberAfGetNthCluster(endpoint, listIndex, TRUE);
  } else if (listId == EMBER_OUTPUT_CLUSTER_LIST) {
    cluster = emberAfGetNthCluster(endpoint, listIndex, FALSE);
  } 
  if ( cluster == NULL ) 
    return 0xFFFF;

  return cluster->clusterId;
}


// *******************************************************************
// Handlers required to use the Ember Stack.

// Called when the stack status changes, usually as a result of an
// attempt to form, join, or leave a network.
void emberStackStatusHandler(EmberStatus status)
{
  emAfStackStatusHandler(status);
}

// Copy the message buffer into a RAM buffer.
//   If message is too large, 0 is returned and no copying is done.
//   Otherwise data is copied, and length of copied data is returned.
int8u emAfCopyMessageIntoRamBuffer(EmberMessageBuffer message,
                                   int8u *buffer,
                                   int16u bufLen)
{
  int8u length = emberMessageBufferLength(message);
  if (bufLen < length) {
    emberAfAppPrintln("%pmsg too big (%d > %d)", 
                      "ERROR: ", 
                      length, 
                      bufLen);
    return 0;
  }
  emberCopyFromLinkedBuffers(message, 0, buffer, length); // no offset
  return length;
}

void emberIncomingMessageHandler(EmberIncomingMessageType type,
                                 EmberApsFrame *apsFrame,
                                 EmberMessageBuffer message)
{
  int8u lastHopLqi;
  int8s lastHopRssi;
  EmberNodeId sender;
  int8u i, addressIndex;
  int16u messageLength;
  int8u messageContents[EMBER_AF_MAXIMUM_APS_PAYLOAD_LENGTH];

  messageLength = emAfCopyMessageIntoRamBuffer(message,
                                               messageContents,
                                               EMBER_AF_MAXIMUM_APS_PAYLOAD_LENGTH);
  if (messageLength == 0) {
    INCR_haNumPktsRxLengthError;
    return;
  }

  emberGetLastHopLqi(&lastHopLqi);
  emberGetLastHopRssi(&lastHopRssi);
  sender = emberGetSender();
  addressIndex = EMBER_NULL_ADDRESS_TABLE_INDEX;
  for (i = 0; i < EMBER_AF_ADDRESS_TABLE_SIZE; i++) {
    if (emberGetAddressTableRemoteNodeId(i) == sender) {
      addressIndex = i;
      break;
    }
  }

  emAfIncomingMessageHandler(type,
                             apsFrame,
                             lastHopLqi,
                             lastHopRssi,
                             sender,
                             emberGetBindingIndex(),
                             addressIndex,
                             messageLength,
                             messageContents);
}


// Called when a message we sent is acked by the destination or when an
// ack fails to arrive after several retransmissions.
void emberMessageSentHandler(EmberOutgoingMessageType type,
                             int16u indexOrDestination,
                             EmberApsFrame *apsFrame,
                             EmberMessageBuffer message,
                             EmberStatus status)
{
  int8u messageContents[EMBER_AF_MAXIMUM_APS_PAYLOAD_LENGTH];
  int8u messageLength;

#ifdef EMBER_AF_ENABLE_FRAGMENTATION
  if (emAfFragmentationMessageSent(apsFrame, status)) {
    return;
  }
#endif //EMBER_AF_ENABLE_FRAGMENTATION
  
#ifdef EMBER_AF_CONCENTRATOR
  emberConcentratorNoteDeliveryFailure(type, status);
#endif

  messageLength = emAfCopyMessageIntoRamBuffer(message,
                                               messageContents,
                                               EMBER_AF_MAXIMUM_APS_PAYLOAD_LENGTH);
  if (messageLength == 0) {
    // Message too long.  Error printed by above function.
    return;
  }

  emAfMessageSentHandler(type,
                         indexOrDestination,
                         apsFrame,
                         status,
                         messageLength,
                         messageContents);
}

// ******************************************************************
// the application implements the send functions for the CLI and the
// ZCL utils. The sending is different for different platforms so 
// this needs to be done in the application and not the libraries.
// ******************************************************************

// function for sending a multicast
EmberStatus emberAfSendMulticast(EmberMulticastId multicastId,
                                 EmberApsFrame *apsFrame,
                                 int16u messageLength,
                                 int8u *message)
{
  EmberStatus status = emAfProcessOutgoingMessage(EMBER_OUTGOING_MULTICAST,
                                                  multicastId,
                                                  apsFrame,
                                                  messageLength,
                                                  message);
  if (status == EMBER_SUCCESS) {
    EmberMessageBuffer payload = emberFillLinkedBuffers(message,
                                                        (int8u)messageLength);
    if (payload == EMBER_NULL_MESSAGE_BUFFER) {
      status = EMBER_NO_BUFFERS;
    } else {
      status = emberSendMulticast(apsFrame,
                                  ZA_MAX_HOPS, // radius
                                  ZA_MAX_HOPS, // nonmemberRadius
                                  payload);
      emberReleaseMessageBuffer(payload);
    }
  }
  emAfProcessSendStatus(EMBER_OUTGOING_MULTICAST,
                        multicastId,
                        apsFrame,
                        status,
                        messageLength,
                        message);
  return status;
}

// function for sending a broadcast
EmberStatus emberAfSendBroadcast(EmberNodeId destination,
                                 EmberApsFrame *apsFrame,
                                 int16u messageLength,
                                 int8u *message)
{
  EmberStatus status = emAfProcessOutgoingMessage(EMBER_OUTGOING_BROADCAST,
                                                  destination,
                                                  apsFrame,
                                                  messageLength,
                                                  message);
  if (status == EMBER_SUCCESS) {
    EmberMessageBuffer payload = emberFillLinkedBuffers(message,
                                                        (int8u)messageLength);
    if (payload == EMBER_NULL_MESSAGE_BUFFER) {
      status = EMBER_NO_BUFFERS;
    } else {
      status = emberSendBroadcast(destination,
                                  apsFrame,
                                  ZA_MAX_HOPS, // radius
                                  payload);
      emberReleaseMessageBuffer(payload);
    }
  }
  emAfProcessSendStatus(EMBER_OUTGOING_BROADCAST,
                        destination,
                        apsFrame,
                        status,
                        messageLength,
                        message);
  return status;
}

// function for sending a unicast
EmberStatus emberAfSendUnicast(EmberOutgoingMessageType type,
                               int16u indexOrDestination,
                               EmberApsFrame *apsFrame,
                               int16u messageLength,
                               int8u *message)
{
  EmberStatus status = emAfProcessOutgoingMessage(type,
                                                  indexOrDestination,
                                                  apsFrame,
                                                  messageLength,
                                                  message);
  if (status == EMBER_SUCCESS) {
    EmberMessageBuffer payload = emberFillLinkedBuffers(message,
                                                        (int8u)messageLength);
    if (payload == EMBER_NULL_MESSAGE_BUFFER) {
      status = EMBER_NO_BUFFERS;
    } else {
      status = emberSendUnicast(type, indexOrDestination, apsFrame, payload);
      emberReleaseMessageBuffer(payload);
    }
#ifdef EMBER_AF_ENABLE_FRAGMENTATION
  } else if (status == EMBER_MESSAGE_TOO_LONG) {
    status = emAfFragmentationSendUnicast(type,
                                          indexOrDestination,
                                          apsFrame,
                                          message,
                                          messageLength);
    emberAfDebugPrintln("%pstart:len=%d.", "Fragmentation:", messageLength);
#endif
  }
  emAfProcessSendStatus(type,
                        indexOrDestination,
                        apsFrame,
                        status,
                        messageLength,
                        message);
  return status;
}

void emberAfGetEui64(EmberEUI64 returnEui64)
{
  MEMCOPY(returnEui64, emberGetEui64(), EUI64_SIZE);
}

void emberAfGetNetworkParameters(EmberNodeType* nodeType, 
                                 EmberNetworkParameters* parameters)
{
  emberGetNodeType(nodeType);
  emberGetNetworkParameters(parameters);
}

int8u emberAfGetSecurityLevel(void)
{
  return EMBER_SECURITY_LEVEL;
}

int8u emberAfGetKeyTableSize(void)
{
  return EMBER_KEY_TABLE_SIZE;
}

void emAfCopyCounterValues(int16u* counters)
{
  MEMCOPY(counters, emberCounters, sizeof(emberCounters));

  // To maintain parity between the SOC and the Host code,
  // we clear the counters after reading them because that is
  // what happens with the host.
  emberClearCounters();
}

int8u emAfGetPacketBufferFreeCount(void)
{
  return emberPacketBufferFreeCount();
}

int8u emAfGetPacketBufferTotalCount(void)
{
  return EMBER_PACKET_BUFFER_COUNT;
}


// ******************************************************************
// Functions called by the Serial Command Line Interface (CLI)
// ******************************************************************

void emAfCliVersionCommand(void)
{
  emberAfAppPrintln("stack ver. [0x%2x]", SOFTWARE_VERSION);
  emberAfAppFlush();
}

// *************************************************************
// code added to print the routing table. The print is executed from
// the option callback: "option route"
// *************************************************************
#ifdef DEBUG_PRINT_FOR_ROUTING_TABLE
typedef struct {
  int16u destination;
  int16u nextHop;
  int8u  status;
  int8u  age;
} RouteTableEntry;

extern int8u* emRouteData;

PGM_NO_CONST PGM_P zigbeeRouteStatusNames[] =
  {
    "active",
    "discov",
    "",
    "unused",
  };

void printRouteTable()
{
  RouteTableEntry* rte; 
  int8u i;

  emberAfAppPrintln("agg 10=low ram, 20=high ram");
  emberAfAppPrintln("rrec 0=clear 4=sent 8=needed\r\n");
  emberAfAppPrintln("route table:\r\n---------------");
  for (i = 0; i < EMBER_ROUTE_TABLE_SIZE; i++) {
    rte = (RouteTableEntry*) (emRouteData + (sizeof(RouteTableEntry) * i));
    
    emberAfAppPrintln("%x: <%2x>id:%2X next:%2X status:%x (%p) rrec:%x agg:%x age:%d",
                   i,
                   rte,
                   rte->destination,
                   rte->nextHop,
                   rte->status,
                   zigbeeRouteStatusNames[rte->status & 3],
                   rte->status & 12,
                   rte->status & 48,
                   rte->age);
    emberAfAppFlush();
  }
  

}

#endif //DEBUG_PRINT_FOR_ROUTING_TABLE


#ifdef DEBUG_PRINT_FOR_ROUTING_TABLE
void optionPrintRouteCommand(void)
{
  printRouteTable();
}
#endif


#if defined(ZA_CLI_MINIMAL) || defined(ZA_CLI_FULL)

// *****************************
// required setup for command line interface (CLI)
// see app/util/serial/command-interpreter2.h for more information
// *****************************

//******************************************************************
// The top-level command table

EmberCommandEntry emberCommandTable[] = {
#ifdef ZA_CLI_FULL
#ifndef ZA_NO_REPORTING_OPTIMIZATION
  {"add-report-entry", emAfCliAddReportEntryCommand,     "vuuvvuuvvb"},
#endif //ZA_NO_REPORTING_OPTIMIZATION
#if (defined(ZCL_USING_KEY_ESTABLISHMENT_CLUSTER_CLIENT) \
     && defined(ZCL_USING_KEY_ESTABLISHMENT_CLUSTER_SERVER))
  {"cbke",             NULL,                             (PGM_P)cbkeCommands},
#endif
  {"cha",              NULL,                             (PGM_P)changeKeyCommands},
#ifdef EMBER_AF_PLUGIN_DRLC
  {"clear_events",     emAfCliClearEventsCommand,        ""},
#endif //EMBER_AF_PLUGIN_DRLC
#ifdef EMBER_CALLBACK_CUSTOM_CLI_COMMAND
  {"custom",           emberAfCustomCommandLineCallback, "?"},
#endif //EMBER_CALLBACK_CUSTOM_CLI_COMMAND
  {"interpan",         NULL,                             (PGM_P)interpanCommands},
  {"option",           NULL,                             (PGM_P)optionCommands},
  {"read",             emAfCliReadCommand,               "uvvu"},
  {"time",             emAfCliTimesyncCommand,           "vuu"},
  {"write",            emAfCliWriteCommand,              "uvvuub"},
  {"zcl",              NULL,                             (PGM_P)zclCommands}, // from zcl-cli.c
  EMBER_AF_PLUGIN_COMMANDS
#endif //ZA_CLI_FULL
  {"bsend",            emAfCliBsendCommand,              "u"},
#ifdef EMBER_AF_PRINT_ENABLE
  {"debugprint",       NULL,                             (PGM_P)debugPrintCommands},
#endif //EMBER_AF_PRINT_ENABLE
  {"keys",             NULL,                             (PGM_P)keysCommands},
  {"network",          NULL,                             (PGM_P)networkCommands}, // from network-cli.c
#ifdef EMBER_AF_PRINT_ENABLE
  {"print",            NULL,                             (PGM_P)printCommands},
#endif //EMBER_AF_PRINT_ENABLE
  {"raw",              emAfCliRawCommand,                "vb"},
  {"send",             emAfCliSendCommand,               "vuu"},
  {"send_multicast",   emAfCliSendCommand,               "vuu"},
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
  {"version",          emAfCliVersionCommand,            ""},
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
  EMBER_AF_CORE_COMMANDS
#ifndef EMBER_AF_CLI_DISABLE_INFO
  EMBER_AF_INFO_COMMAND
#endif
  KEY_UPDATE_COMMANDS
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
  LIBRARY_COMMANDS // Defined in app/util/common/library.h
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
  ZDO_COMMANDS
  CUSTOM_COMMANDS

  TEST_HARNESS_CLI_COMMANDS

  {NULL,               NULL,                             NULL}, // terminator
};

#else //defined(ZA_CLI_MINIMAL) || defined(ZA_CLI_FULL)
// when using no CLI, need to set these externs
EmberCommandEntry emberCommandTable[] = { { NULL } };
#endif //defined(ZA_CLI_MINIMAL) || defined(ZA_CLI_FULL)

#ifdef ZA_TINY_SERIAL_INPUT

// i = info
// f = form
// j = join
// p = permit join
// l = leave
// t = read time from ZC
// b = read basic from ZC
// k = print keys
// c = clear keys
// m = send match desc to start Key Est. cluster looked for is controlled by +
// + = change which cluster is looked for during Key Est
// a = establish pArtner link key with the following hardcoded EUI and dest EP
EmberEUI64 partnerLinkKeyEui = { 
  // Little endian format.
  0x79, 0x6c, 0x06, 0x00, 0x00, 0x6f, 0x0d, 0x00
};
#define partnerLinkKeyDestEp KEY_ESTABLISHMENT_ENDPOINT

#define TINY_SERIAL_CHANNEL 11
#define TINY_SERIAL_PANID   0x00AB

void tinySerialInputTick(void) {
  int8u cmd;
  EmberNetworkParameters networkParams;
  EmberStatus status;
  static int16u matchDescClusterId = ZCL_KEY_ESTABLISHMENT_CLUSTER_ID;
  MEMSET(&networkParams, 0, sizeof(EmberNetworkParameters));

  if(emberSerialReadByte(APP_SERIAL, &cmd) == 0) {
    if (cmd != '\n') emberAfAppPrintln("");
                                
    switch(cmd) {
     // info
    case 'i':
      emAfCliInfoCommand();
      break;

      // form
    case 'f':
#if (ZA_DEVICE_TYPE == ZA_COORDINATOR)
      zaTrustCenterSecurityInit();

      MEMCOPY(networkParams.extendedPanId, 
              emAfExtendedPanId,
              EXTENDED_PAN_ID_SIZE);
      networkParams.radioChannel = TINY_SERIAL_CHANNEL;
      networkParams.radioTxPower = 2;
      networkParams.panId = TINY_SERIAL_PANID;
      status = emberFormNetwork(&networkParams);
      //emberAfGuaranteedPrintln("form 0x%x\r\n", status);
#else  // (ZA_DEVICE_TYPE == ZA_COORDINATOR)
      emberAfGuaranteedPrintln("only coordinators can form networks");
#endif  // (ZA_DEVICE_TYPE == ZA_COORDINATOR)
      break;

      // join
    case 'j':
      zaNodeSecurityInit();

      MEMCOPY(networkParams.extendedPanId, 
              emAfExtendedPanId,
              EXTENDED_PAN_ID_SIZE);
      networkParams.radioChannel = TINY_SERIAL_CHANNEL;
      networkParams.radioTxPower = 2;
      networkParams.panId = TINY_SERIAL_PANID;
      // ZCs can't join, but if our type is meant to be a coordinator 
      // we can join as a router. 
      if (ZA_DEVICE_TYPE == EMBER_COORDINATOR) {
        status = emberJoinNetwork(EMBER_ROUTER, &networkParams);
      } else {
        status = emberJoinNetwork(ZA_DEVICE_TYPE, &networkParams);
      }

      emberAfGuaranteedPrintln("join 0x%x", status);
      break;
      // pjoin
    case 'p':
      status = emberPermitJoining(20);
      emberAfGuaranteedPrintln("pJoin for %x sec: 0x%x", 20, status);
      break;

      // pjoin
    case 'l':
      status = emberLeaveNetwork();
      emberAfGuaranteedPrintln("leave 0x%x", status);
      break;

    case 's':
      emAfCliCountersCommand();
      break;
   
      // send read time to coord
    case 't':
      emberAfSendReadAttribute(EMBER_ZIGBEE_COORDINATOR_ADDRESS,
                               ZCL_TIME_CLUSTER_ID, 
                               ZCL_TIME_ATTRIBUTE_ID);
      break;
    
      // send read basic to coord
    case 'b':
      emberAfSendReadAttribute(EMBER_ZIGBEE_COORDINATOR_ADDRESS, 
                               ZCL_BASIC_CLUSTER_ID, 
                               ZCL_VERSION_ATTRIBUTE_ID);
      break;
      
      // print keys
    case 'k':
      printKeyInfo();
      break;

      // clear keys
    case 'c':
      {
        int8u i;
        for (i = 0; i < EMBER_KEY_TABLE_SIZE; i++) {
          emberEraseKeyTableEntry(i);
        }
      }
      break;

    case '+':
      switch (matchDescClusterId) {
      case ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID:
        matchDescClusterId = ZCL_TIME_CLUSTER_ID;
        emberAfGuaranteedPrintln("using time");
        break;
      case ZCL_TIME_CLUSTER_ID:
        matchDescClusterId = ZCL_BASIC_CLUSTER_ID;
        emberAfGuaranteedPrintln("using basic");
        break;
      case ZCL_BASIC_CLUSTER_ID:
        matchDescClusterId = ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID;
        emberAfGuaranteedPrintln("using DRLC");
        break;
      }
      break;
    
    case 'a': {
      EmberNodeId partner = emberLookupNodeIdByEui64(partnerLinkKeyEui);
      if (partner == EMBER_NULL_NODE_ID) {
        emberAfGuaranteedPrint("Could not determine short ID of ");
        emberAfPrintIeeeLine(partnerLinkKeyEui);
      } else {
        EmberStatus status = emberAfInitiatePartnerLinkKeyExchange(partner,
                                                                   partnerLinkKeyDestEp,
                                                                   NULL); // callback
        if (status == EMBER_SUCCESS) {
          emberAfGuaranteedPrintln("Initiated Partner Link Key");
        } else {
          emberAfGuaranteedPrintln("Failed partner link key request: 0x%x",
                                   status);
        }
      }
    }
      break;

    case '\n':
    case '\r':
      break;

    default:
      emberAfGuaranteedPrintln("ukwn cmd");
      break;
     }

    if (cmd != '\n') {
      emberAfGuaranteedPrint("\r\n%p>", ZA_PROMPT);
    }
  }

}
#endif //ZA_TINY_SERIAL_INPUT
