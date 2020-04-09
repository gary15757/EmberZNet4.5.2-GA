// *****************************************************************************
// * service-discovery-common.c
// *
// * Service discovery code that is common to different types of service
// * discovery, e.g. match descriptor, NWK address lookup, and IEEE address
// * lookup.
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include PLATFORM_HEADER     // Micro and compiler specific typedefs and macros

#if defined EZSP_HOST
  #include "stack/include/ember-types.h"
  #include "stack/include/error.h"
  #include "stack/include/library.h"
  #include "app/util/ezsp/ezsp-protocol.h"
  #include "app/util/ezsp/ezsp.h"
  #include "app/util/zigbee-framework/zigbee-device-host.h"
#else
  // Ember stack and related utilities
  #include "stack/include/ember.h"         // Main stack definitions
#endif

#include "hal/hal.h"
#include "service-discovery.h"
#include "print.h"
#include "app/framework/include/af.h" // for wake register management

//==============================================================================
// Service discovery state machine
//
//   This code handles initiating a limited set of ZDO, receiving
//   the response and sending it back to the cluster or code element that
//   requested it.  Unfortunately the ZDO message does not have any distinct
//   identifiers that would allow us to determine what cluster/endpoint on our
//   local device initiated the request.  Therefore we can only allow one
//    outstanding request at a time.


static EmberAfServiceDiscoveryCallback *serviceDiscoveryCallback = NULL;

EmberEventControl emAfServiceDiscoveryEventControl;

#define DISCOVERY_TIMEOUT_QS 8

static boolean unicastQuery = FALSE;

// This will contain the target type: broadcast or unicast (high bit)
// and the ZDO cluster ID of the request.  Since ZDO requests
// clear the high bit (only repsonses use it), we can use that leftover bit
// for something else.
static int16u requestData;

#define UNICAST_QUERY_BIT (0x8000)
#define isUnicastQuery() (UNICAST_QUERY_BIT == (requestData & UNICAST_QUERY_BIT))
#define setUnicastQuery() (requestData |= UNICAST_QUERY_BIT)

#define getRequestCluster() (requestData & ~UNICAST_QUERY_BIT)

// seq. number (1), status (1), address (2), length (1)
#define MATCH_DESCRIPTOR_OVERHEAD               5
#define MINIMUM_MATCH_DESCRIPTOR_SUCCESS_LENGTH MATCH_DESCRIPTOR_OVERHEAD

// seq. number (1), status (1)
#define ZDO_OVERHEAD 2
// EUI64 (8), node ID (2),
#define MINIMUM_ADDRESS_REQEUST_SUCCESS (ZDO_OVERHEAD + 10)
#define ADDRESS_RESPONSE_NODE_ID_OFFSET (ZDO_OVERHEAD + EUI64_SIZE)

#define serviceDiscoveryInProgress() (NULL != serviceDiscoveryCallback)

static PGM_P prefix = "Svc Disc: ";

//==============================================================================
// Forward Declarations

static void setupDiscoveryData(EmberNodeId messageDest,
                               EmberAfServiceDiscoveryCallback *callback,
                               int16u zdoClusterId);

//==============================================================================

EmberStatus emberAfFindDevicesByProfileAndCluster(EmberNodeId target,
                                                  EmberAfProfileId profileId,
                                                  EmberAfClusterId clusterId,
                                                  boolean serverCluster,
                                                  EmberAfServiceDiscoveryCallback *callback)
{
  EmberStatus status;
  (void)prefix; //remove warning if not used

  if (serviceDiscoveryInProgress()) {
    return EMBER_INVALID_CALL;
  }

  unicastQuery = (target < EMBER_BROADCAST_ADDRESS);
  if (!unicastQuery && target != EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS) {
    // Note:  The core spec. only allows a Match Descriptor broadcast to
    // the 'rx on when idle' address.  No other broadcast addresses are allowed.
    // The Ember stack will silently discard broadcast match descriptors
    // to invalid broadcast addresses.
    emberAfServiceDiscoveryPrintln("%pIllegal broadcast address, remapping to valid one.",
                                   prefix);
    target = EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS;
  }

  status = emAfSendMatchDescriptor(target, profileId, clusterId, serverCluster);
  if (status != EMBER_SUCCESS) {
    emberAfServiceDiscoveryPrintln("%pFailed to send match discovery: 0x%x",
                                   prefix,
                                   status);
    return status;
  }


  emberAfServiceDiscoveryPrintln("%pStarting discovery for cluster 0x%2x",
                                 prefix,
                                 clusterId);

  setupDiscoveryData(target, callback, MATCH_DESCRIPTORS_REQUEST);

  return EMBER_SUCCESS;
}

EmberStatus emberAfFindIeeeAddress(EmberNodeId shortAddress,
                                   EmberAfServiceDiscoveryCallback *callback)
{
  EmberStatus status;

  if (serviceDiscoveryInProgress()) {
    return EMBER_INVALID_CALL;
  }

  status = emberIeeeAddressRequest(shortAddress,
                                   FALSE,         // report kids?
                                   0,             // child start index
                                   EMBER_APS_OPTION_RETRY);

  if (status != EMBER_SUCCESS) {
    emberAfServiceDiscoveryPrintln("%pFailed to send IEEE address request: 0x%x",
                                   prefix,
                                   status);
    return status;
  }

  setupDiscoveryData(shortAddress, callback, IEEE_ADDRESS_REQUEST);

  return status;
}

EmberStatus emberAfFindNodeId(EmberEUI64 longAddress,
                              EmberAfServiceDiscoveryCallback *callback)
{
  EmberStatus status;

  if (serviceDiscoveryInProgress()) {
    return EMBER_INVALID_CALL;
  }

  status = emberNetworkAddressRequest(longAddress,
                                      FALSE,         // report kids?
                                      0);            // child start index

  if (status != EMBER_SUCCESS) {
    emberAfServiceDiscoveryPrintln("%pFailed to send NWK address request: 0x%x",
                                   prefix,
                                   status);
    return status;
  }

  setupDiscoveryData(EMBER_BROADCAST_ADDRESS, callback, NETWORK_ADDRESS_REQUEST);

  return status;
}

static void setupDiscoveryData(EmberNodeId messageDest,
                               EmberAfServiceDiscoveryCallback *callback,
                               int16u zdoClusterRequest)
{
  requestData = zdoClusterRequest;
  if (messageDest < EMBER_BROADCAST_ADDRESS) {
    setUnicastQuery();
  }
  serviceDiscoveryCallback = callback;
  emberEventControlSetDelayQS(emAfServiceDiscoveryEventControl,
                              DISCOVERY_TIMEOUT_QS);

  // keep sleepy end devices out of hibernation until
  // service discovery is complete
  emberAfAddToCurrentAppTasks(EMBER_AF_WAITING_FOR_SERVICE_DISCOVERY);
}

void emAfServiceDiscoveryComplete(void)
{
  EmberAfServiceDiscoveryCallback *callback = serviceDiscoveryCallback;

  serviceDiscoveryCallback = NULL;
  emberAfServiceDiscoveryPrintln("%pcomplete.", prefix);
  emberEventControlSetInactive(emAfServiceDiscoveryEventControl);

  // allow sleepy end devices to go into hibernation now.
  emberAfRemoveFromCurrentAppTasks(EMBER_AF_WAITING_FOR_SERVICE_DISCOVERY);

  if (callback) {
    EmberAfServiceDiscoveryResult result;
    result.status = (isUnicastQuery()
                     ? EMBER_AF_UNICAST_SERVICE_DISCOVERY_TIMEOUT
                     : EMBER_AF_BROADCAST_SERVICE_DISCOVERY_COMPLETE);
    result.zdoRequestClusterId = getRequestCluster();
    result.matchAddress = EMBER_NULL_NODE_ID;
    result.responseData = NULL;
    (*callback)(&result);
  }
}

static void executeCallback(const EmberAfServiceDiscoveryResult *result)
{
  (*serviceDiscoveryCallback)(result);
  if (isUnicastQuery()) {
    // If the request was unicast and we received a response then we are done.
    // No need to wait for the timer to expire.

    // We NULL the callback as a way of indicating we already fired it.
    // For timeouts, the callback will not be NULL and still fire.
    serviceDiscoveryCallback = NULL;
    emAfServiceDiscoveryComplete();
  }
}

static boolean processMatchDescriptorResponse(const int8u *message,
                                              int16u length)
{
  EmberNodeId matchId;
  int8u listLength;

  if (length < MINIMUM_MATCH_DESCRIPTOR_SUCCESS_LENGTH) {
    emberAfServiceDiscoveryPrintln("%pMessage too short", prefix);
    return TRUE;
  }

  // This will now be used as the length of the match list.
  length -= MATCH_DESCRIPTOR_OVERHEAD;

  // If the parent of a sleepy device supports caching its descriptor
  // information then the sender of the response may not be the device
  // that actually matches the request.  The device id that matches
  // is included in the message.
  matchId = message[2] + (message[3] << 8);
  listLength = message[4];

  if (listLength != length) {
    emberAfServiceDiscoveryPrintln("%pMessage too short for num. endpoints",
                                   prefix);
    return TRUE;
  }

  emberAfServiceDiscoveryPrintln("%pMatch%p found from 0x%2x.",
                                 prefix,
                                 (listLength > 0
                                  ? ""
                                  : " NOT"),
                                 matchId);

  // If we got an active response with an empty list then ignore it.
  if (listLength != 0) {
    EmberAfServiceDiscoveryResult result;
    EmberAfEndpointList endpointList;
    endpointList.count = length;
    endpointList.list = &(message[MATCH_DESCRIPTOR_OVERHEAD]);
    result.status = (isUnicastQuery()
                     ? EMBER_AF_UNICAST_SERVICE_DISCOVERY_COMPLETE_WITH_RESPONSE
                     : EMBER_AF_BROADCAST_SERVICE_DISCOVERY_RESPONSE_RECEIVED);
    result.zdoRequestClusterId = getRequestCluster();
    result.matchAddress = matchId;
    result.responseData = &endpointList;
    executeCallback(&result);
  }
  return TRUE;
}

// Both NWK and IEEE responses have the same exact format.
static boolean processAddressResponse(const int8u *message, int16u length)
{
  EmberAfServiceDiscoveryResult result;
  EmberEUI64 eui64LittleEndian;

  if (length < MINIMUM_ADDRESS_REQEUST_SUCCESS) {
    emberAfServiceDiscoveryPrintln("%pMessage too short", prefix);
    return TRUE;
  }
  MEMCOPY(eui64LittleEndian, message + ZDO_OVERHEAD, EUI64_SIZE);
  result.status = (isUnicastQuery()
                   ? EMBER_AF_UNICAST_SERVICE_DISCOVERY_COMPLETE_WITH_RESPONSE
                   : EMBER_AF_BROADCAST_SERVICE_DISCOVERY_RESPONSE_RECEIVED);
  result.matchAddress = (message[ADDRESS_RESPONSE_NODE_ID_OFFSET]
                         + (message[ADDRESS_RESPONSE_NODE_ID_OFFSET+1] << 8));
  result.zdoRequestClusterId = getRequestCluster();
  result.responseData = eui64LittleEndian;

  executeCallback(&result);
  return TRUE;
}

boolean emAfServiceDiscoveryIncoming(EmberNodeId sender,
                                     EmberApsFrame *apsFrame,
                                     const int8u *message,
                                     int16u length)
{
  if (!(serviceDiscoveryInProgress()
        && (apsFrame->profileId == EMBER_ZDO_PROFILE_ID
            // ZDO Responses set the high bit on the request cluster ID
            && (apsFrame->clusterId == (CLUSTER_ID_RESPONSE_MINIMUM
                                        | getRequestCluster()))))) {
    return FALSE;
  }

  // If we hear our own request and respond we ignore it.
  if (sender == emberGetNodeId()) {
    return TRUE;
  }

  // The second byte is the status code
  if (message[1] != EMBER_ZDP_SUCCESS) {
    return TRUE;
  }

  switch (apsFrame->clusterId) {
  case MATCH_DESCRIPTORS_RESPONSE:
    return processMatchDescriptorResponse(message, length);

  case NETWORK_ADDRESS_RESPONSE:
  case IEEE_ADDRESS_RESPONSE:
    return processAddressResponse(message, length);

  default:
    // Some ZDO request we don't care about.
    break;
  }

  return FALSE;
}
