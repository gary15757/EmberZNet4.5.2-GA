// *******************************************************************
// * SeMeterMirror_callbacks.c
// *
// * This file contains all application specific code for the
// * meter mirror sample application. The code is implemented in
// * a series of callbacks which are called from within the
// * application framework. Each callback below includes a
// * comment explaining what it does for the application.
// *
// * This application is inteded to be used along with the
// * gas meter sample application SeMeterGas
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "app/framework/util/common.h"
#include "app/framework/util/attribute-table.h"

#define ESP_ENDPOINT            0x01
#define METER_MIRROR_ENDPOINT   0x03
#define INVALID_MIRROR_ENDPOINT 0xffff
#define MIRROR_CAPACITY 0x01

// Used for tracking whether physicalEnvironment attribute returns 0x01 (has mirror capacity)
// or return 0x00 (mirror has no capacity available)
// mirrorCapacity var is decremented for each new mirror add, incremented for each removed mirror
int8u mirrorCapacity = MIRROR_CAPACITY;

//Forward declaration
static int16u getMirrorEndpoint(EmberEUI64 sendingDeviceIeeeAddress);
static void updatePhysicalEnvironment(void);
static void initMirrors(void);

// *******************************************************************
// * clusterInitCallback
// *
// * This callback is called for each cluster on each endpoint it
// * provides an opportunity for the application to do any
// * initialization of the cluster.
// *
// * In the case of the simple metering cluster,
// * cluster initialization is very important since the
// * simple metering device type is defined by an attribute
// * within the cluster. This means that, when the device starts
// * the application needs to make sure that the device type
// * is set to the appropriate type for the device implemented
// * on each endpoint.
// *
// * This application has 2 endpoints,
// *   1: ESP
// *   3: Meter Mirror
// *
// * The code implemented in this callback checks that
// * each endpoint which implements simple metering (they all do)
// * has the right device type value for that endpoint.
// * In the case of an unallocated mirror, there is (at the time
// * that I am writing this) no value defined in the spec so
// * I created one, out of a reserved value
// * EMBER_ZCL_METER_DEVICE_TYPE_UNDEFINED_MIRROR_METER (0xfe).
// *
// *******************************************************************
void emberAfClusterInitCallback(int8u endpoint, int16u clusterId) {
  int8u deviceType = EMBER_ZCL_METER_DEVICE_TYPE_UNDEFINED_MIRROR_METER;

  // Make sure that our meter endpoint's device type attributes
  // are set properly. The device type attributes default is 0x00
  // which happens to be Electric meter so we only have to check
  // our mirror endpoints to make sure that they are not set to default.
  if (endpoint == METER_MIRROR_ENDPOINT
      && clusterId == ZCL_SIMPLE_METERING_CLUSTER_ID) {
    // We don't check to see if this attribute exists prior to writing
    // it because if device type doesn't exist we'll get an error
    // and we want to know if our confiuration is missing deviceType
    // because that would be a bug.
    emberAfWriteAttribute(endpoint,
                          ZCL_SIMPLE_METERING_CLUSTER_ID,
                          ZCL_METERING_DEVICE_TYPE_ATTRIBUTE_ID,
                          CLUSTER_MASK_SERVER,
                          (int8u *)&deviceType,
                          ZCL_INT8U_ATTRIBUTE_TYPE);
  } else if (endpoint == ESP_ENDPOINT && clusterId == ZCL_BASIC_CLUSTER_ID) {
    initMirrors();
  }
}

/** @brief Stack Status
 *
 * This function is called by the application framework from the stack status
 * handler.  This callbacks provides applications an opportunity to be
 * notified of changes to the stack status and take appropriate action.  The
 * application should return TRUE if the status has been handled and should
 * not be handled by the application framework.
 *
 * If the mirroring device leaves the network, we should wipe our mirror state.
 *
 * @param status   Ver.: always
 */
boolean emberAfStackStatusCallback(EmberStatus status) {
  EmberNetworkStatus state = emberNetworkState();
  if (state == EMBER_NO_NETWORK) {
    
    // clear our mirrors.
    emberAfCorePrintln("STACK STATUS NO NETWORK. INIT MIRRORS!!!");
    emberAfCoreFlush();
    
    initMirrors();
  }
  return FALSE;
}


// *******************************************************************
// * reportAttributesCallback
// *
// * Mirrored devices update their mirrors by sending unsolicited report
// * attributes commands.  If a report is received from the mirrored device for
// * simple metering attributes, this function will copy the reported values to
// * the local attribute table.
// *
// *******************************************************************
boolean emberAfReportAttributesCallback(EmberAfClusterId clusterId,
                                        int8u *buffer,
                                        int16u bufLen)
{
  EmberEUI64 sendersEui;
  int16u bufIndex = 0;
  int16u endpointId = INVALID_MIRROR_ENDPOINT;
  int8u mask = ((emberAfCurrentCommand()->direction
                 == ZCL_DIRECTION_CLIENT_TO_SERVER)
                ? CLUSTER_MASK_CLIENT
                : CLUSTER_MASK_SERVER);

  // Ignore reports not received by the mirror, not for the simple metering
  // cluster, or if the EUI of the report sender does not match the mirrored
  // device.
  if (emberLookupEui64ByNodeId(emberAfCurrentCommand()->source, sendersEui)
        != EMBER_SUCCESS) {
        return FALSE;
  }
  
  endpointId = getMirrorEndpoint(sendersEui);
  if (endpointId == INVALID_MIRROR_ENDPOINT) {
    return FALSE;
  }

  // Each record in the report has a two-byte attribute id, a one-byte type, and
  // variable-length data.
  while (bufIndex + 3 < bufLen) {
    EmberAfStatus status;
    EmberAfAttributeId attributeId;
    EmberAfAttributeType dataType;
    int8u dataSize;

    attributeId = (EmberAfAttributeId)emberAfGetInt16u(buffer,
                                                       bufIndex,
                                                       bufLen);
    bufIndex += 2;
    dataType = (EmberAfAttributeType)emberAfGetInt8u(buffer, bufIndex, bufLen);
    bufIndex++;

    // For strings, the data size is the length of the string (specified by the
    // first byte of data) plus one for the length byte itself.  For everything
    // else, the size is just the size of the data type.
    dataSize = (emberAfIsThisDataTypeAStringType(dataType)
                ? buffer[bufIndex] + 1
                : emberAfGetDataSize(dataType));

    {
#if (BIGENDIAN_CPU)
      int8u data[ATTRIBUTE_LARGEST];
      if (isThisDataTypeSentLittleEndianOTA(dataType)) {
        emberReverseMemCopy(data, buffer + bufIndex, dataSize);
      } else {
        MEMCOPY(data, buffer + bufIndex, dataSize);
      }
#else
      int8u *data = buffer + bufIndex;
#endif
      status = emberAfWriteAttribute((int8u)endpointId,
                                     ZCL_SIMPLE_METERING_CLUSTER_ID,
                                     attributeId,
                                     mask,
                                     data,
                                     dataType);
    }

    emberAfCorePrintln("Mirror attribute 0x%2x: 0x%x", attributeId, status);
    bufIndex += dataSize;
  }

  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

// *******************************************************************
// * simpleMeteringClusterRequestMirrorCallback
// *
// * This callback checks the mirror endpoints to see if there
// * is a mirror available. If there is one, it sets the mirror
// * based on the Ieee Address of the requesting device and
// * returns the endpoint of the allocated mirror.
// *
// * If no mirror is available, the callback returns 0xFFFF
// * indicating that a mirror could not be allocated.
// *
// * The ZCL spec (as of this writing) expects that the mirror
// * will begin reading attributes off the mirrored device once
// * the mirror has been allocated. This does not make sense since
// * the mirrored device is by definition sleepy so most attribute
// * reads will likely fail. I have not implemented any mechanism
// * for syncing the mirrored device with the mirror. My expectation
// * is that the mirrored device will update the mirror using
// * global writes for the simple metering attributes on the mirror
// * endpoint. This is the reason that I have implemented the
// * preExternalWriteAttributeCallback above.
// *
// * If you want your mirror to be compliant with the current ZCL
// * spec, you will have to implement some sort of syncing by reading
// * mechanism. I did not to this here since it seemed like a lot
// * of excess code for a feature which is likely to be removed
// * from the spec. A proper mirrored device should instead keep
// * track of its own attribute changes and write them to the mirror
// * as needed during its awake period.
// *
// *******************************************************************
int16u emberAfPluginSimpleMeteringClientRequestMirrorCallback(EmberEUI64 requestingDeviceIeeeAddress)
{
  boolean exists;
  int8u i;
  int8u att;
  int16u endpointId = INVALID_MIRROR_ENDPOINT; // Invalid endpoint, default return;
  int8u mirrorEui[EUI64_SIZE];
  EmberEUI64 clearEui = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

  // Go over our endpoints and find an unallocated meter mirror
  for (i = 0; i < emberAfEndpointCount(); i++) {
    exists = emberAfRetrieveAttribute(emberAfEndpointFromIndex(i),
                               ZCL_SIMPLE_METERING_CLUSTER_ID,
                               ZCL_METERING_DEVICE_TYPE_ATTRIBUTE_ID,
                               CLUSTER_MASK_SERVER,
                               0,
                               NULL,
                               &att);
    if ( !exists ) continue;
    exists = emberAfRetrieveAttribute(emberAfEndpointFromIndex(i),
                               ZCL_SIMPLE_METERING_CLUSTER_ID,
                               ZCL_MIRROR_IEEE_ADDRESS_ATTRIBUTE_ID,
                               CLUSTER_MASK_SERVER,
                               EM_AF_MANUFACTURER_CODE,
                               NULL,
                               mirrorEui);
    if ( !exists ) continue;

    // If endpoint is unallocated OR is allocated to the
    // requesting device send back the endpoint
    // This handles duplicate requests for mirrors from the same device.
    if ( ( (att == EMBER_ZCL_METER_DEVICE_TYPE_UNDEFINED_MIRROR_METER)
         && (0 == MEMCOMPARE(clearEui, mirrorEui, EUI64_SIZE)) )
         || ( 0 == MEMCOMPARE(requestingDeviceIeeeAddress,
                              mirrorEui,
                              EUI64_SIZE))) {
      endpointId = emberAfEndpointFromIndex(i);
      break;
    }
  }

  if (endpointId != INVALID_MIRROR_ENDPOINT) {
    emberAfWriteManufacturerSpecificServerAttribute(endpointId,
                          ZCL_SIMPLE_METERING_CLUSTER_ID,
                          ZCL_MIRROR_IEEE_ADDRESS_ATTRIBUTE_ID,
                          EM_AF_MANUFACTURER_CODE,
                          requestingDeviceIeeeAddress,
                          ZCL_IEEE_ADDRESS_ATTRIBUTE_TYPE
                          );
      // Check if duplicate request, if not then
    // decrement the mirrorCapacity value, if depleted set physical environment attrib 0x00
    if ( 0 != MEMCOMPARE(requestingDeviceIeeeAddress, mirrorEui, EUI64_SIZE)) {
      mirrorCapacity--;
      updatePhysicalEnvironment();
    }
  }
  return endpointId;
}

// *******************************************************************
// * simpleMeteringClusterRequestMirrorCallback
// *
// * This callback checks the that the device requesting to remove
// * the mirror is in fact the mirrored device by comparing the
// * device's ieee address with that of the mirror. If they are the
// * same, the mirror is removed and the endpoint from which it was
// * removed is returned.
// *
// * 
// * 02/17/2011 - Updated to accept mirror removal on any
// * endpoint instead of requiring that request come in on mirror's 
// * endpoint.
// * 
// * If the ieee addresses don't match this callback returns
// * 0xFFFF indicating that the mirror could not be removed.
// *
// *******************************************************************
int16u emberAfPluginSimpleMeteringClientRemoveMirrorCallback(EmberEUI64 requestingDeviceIeeeAddress)
{
  int16u endpointId = INVALID_MIRROR_ENDPOINT; // Invalid endpoint, default return
  boolean exists;
  EmberEUI64 mirrorEui;
  int8u deviceType = EMBER_ZCL_METER_DEVICE_TYPE_UNDEFINED_MIRROR_METER;
  EmberEUI64 clearEui = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  int8u i;
  
  endpointId = getMirrorEndpoint(requestingDeviceIeeeAddress);
  
  // If we were unable to find the mirror, fail
  if (endpointId != INVALID_MIRROR_ENDPOINT) {
    // Remove the mirror and send back the endpoint from which it was
    // removed
    emberAfWriteAttribute((int8u)endpointId,
                          ZCL_SIMPLE_METERING_CLUSTER_ID, 
                          ZCL_METERING_DEVICE_TYPE_ATTRIBUTE_ID,
                          CLUSTER_MASK_SERVER,
                          (int8u*) &deviceType,
                          ZCL_INT8U_ATTRIBUTE_TYPE
                          );
    emberAfWriteManufacturerSpecificServerAttribute((int8u)endpointId,
                          ZCL_SIMPLE_METERING_CLUSTER_ID, 
                          ZCL_MIRROR_IEEE_ADDRESS_ATTRIBUTE_ID,
                          EM_AF_MANUFACTURER_CODE,
                          clearEui,
                          ZCL_IEEE_ADDRESS_ATTRIBUTE_TYPE
                          );
    mirrorCapacity++;
    updatePhysicalEnvironment();
  }  
  return endpointId;
}

// A utility function for matching an incoming ieee address with 
// an mirror's endpoint, basically we are finding the requesting device's
// mirror or returning a failure.
static int16u getMirrorEndpoint(EmberEUI64 requestingDeviceIeeeAddress) {
  int16u endpointId = INVALID_MIRROR_ENDPOINT;
  EmberEUI64 mirrorEui;
  int8u i;
  boolean exists;
  
  // Find the endpoint on which the requesting device has a mirror.
  for (i = 0; i < emberAfEndpointCount(); i++) {
    exists = emberAfRetrieveAttribute(emberAfEndpointFromIndex(i), 
                               ZCL_SIMPLE_METERING_CLUSTER_ID,
                               ZCL_MIRROR_IEEE_ADDRESS_ATTRIBUTE_ID,
                               CLUSTER_MASK_SERVER,
                               EM_AF_MANUFACTURER_CODE,
                               NULL,
                               mirrorEui);
    if ( !exists ) continue;
  
    if (0 == MEMCOMPARE(requestingDeviceIeeeAddress, 
                        mirrorEui, 
                        EUI64_SIZE)) {
      endpointId = emberAfEndpointFromIndex(i);
      break;
    }
  }
  return endpointId;
}

static void updatePhysicalEnvironment() {
  int8u physEnv = 0;
  if (mirrorCapacity) {
    physEnv = 1;
  }
  emberAfWriteAttribute(ESP_ENDPOINT,
                        ZCL_BASIC_CLUSTER_ID,
                        ZCL_PHYSICAL_ENVIRONMENT_ATTRIBUTE_ID,
                        CLUSTER_MASK_SERVER,
                        (int8u *)&physEnv,
                        ZCL_INT8U_ATTRIBUTE_TYPE);
}

static void initMirrors() {
  int8u deviceType = EMBER_ZCL_METER_DEVICE_TYPE_UNDEFINED_MIRROR_METER;
  emberAfWriteAttribute(METER_MIRROR_ENDPOINT,
                        ZCL_SIMPLE_METERING_CLUSTER_ID,
                        ZCL_METERING_DEVICE_TYPE_ATTRIBUTE_ID,
                        CLUSTER_MASK_SERVER,
                        (int8u *)&deviceType,
                        ZCL_INT8U_ATTRIBUTE_TYPE);
  mirrorCapacity = MIRROR_CAPACITY;
  updatePhysicalEnvironment();
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
