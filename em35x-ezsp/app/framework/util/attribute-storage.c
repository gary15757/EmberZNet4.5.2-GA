// *******************************************************************
// * attribute-storage.c
// *
// * Contains the per-endpoint configuration of attribute tables.
// *
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include PLATFORM_HEADER

#ifdef EZSP_HOST
  // Includes needed for ember related functions for the EZSP host
  #include "stack/include/error.h"
  #include "stack/include/ember-types.h"
  #include "app/util/ezsp/ezsp-protocol.h"
  #include "app/util/ezsp/ezsp.h"
  #include "app/util/ezsp/serial-interface.h"
#else
  #include "stack/include/ember.h"
#endif

#include "hal/hal.h"

#include "attribute-storage.h"
#include "util.h"
#include "tokens.h"

#include "app/framework/gen/cluster-id.h"

#include "app/framework/gen/callback.h"
#include "app/framework/gen/debug-printing.h"

#include "stack/include/ember-types.h"
#include "app/framework/security/crypto-state.h"


// This is not declared CONST in order to handle dynamic endpoint information
// retrieved from tokens.
EmberAfDefinedEndpoint endpoints[MAX_ENDPOINT_COUNT];

#if ( ATTRIBUTE_MAX_SIZE == 0 )
#define ACTUAL_ATTRIBUTE_SIZE 1
#else
#define ACTUAL_ATTRIBUTE_SIZE ATTRIBUTE_MAX_SIZE
#endif

int8u attributeData[ACTUAL_ATTRIBUTE_SIZE];

#if (!defined(ATTRIBUTE_SINGLETONS_SIZE)) \
  || (ATTRIBUTE_SINGLETONS_SIZE == 0)
#define ACTUAL_SINGLETONS_SIZE 1
#else
#define ACTUAL_SINGLETONS_SIZE ATTRIBUTE_SINGLETONS_SIZE
#endif
int8u singletonAttributeData[ACTUAL_SINGLETONS_SIZE];

int8u emberEndpointCount = 0;

// If we have attributes that are more than 2 bytes, then
// we need this data block for the defaults
#ifdef GENERATED_DEFAULTS
const int8u generatedDefaults[]               = GENERATED_DEFAULTS;
#endif // GENERATED_DEFAULTS

#ifdef GENERATED_MIN_MAX_DEFAULTS
const EmberAfAttributeMinMaxValue minMaxDefaults[]          = GENERATED_MIN_MAX_DEFAULTS;
#endif //GENERATED_MIN_MAX_DEFAULTS

#ifdef GENERATED_FUNCTION_ARRAYS
GENERATED_FUNCTION_ARRAYS
#endif

const EmberAfAttributeMetadata generatedAttributes[] = GENERATED_ATTRIBUTES;
const EmberAfCluster generatedClusters[]          = GENERATED_CLUSTERS;
const EmberAfEndpointType generatedEmberAfEndpointTypes[]   = GENERATED_ENDPOINT_TYPES;

const EmberAfManufacturerCodeEntry clusterManufacturerCodes[] = GENERATED_CLUSTER_MANUFACTURER_CODES;
const int16u clusterManufacturerCodeCount = GENERATED_CLUSTER_MANUFACTURER_CODE_COUNT;
const EmberAfManufacturerCodeEntry attributeManufacturerCodes[] = GENERATED_ATTRIBUTE_MANUFACTURER_CODES;
const int16u attributeManufacturerCodeCount = GENERATED_ATTRIBUTE_MANUFACTURER_CODE_COUNT;

// Initial configuration
void emberAfEndpointConfigure(void) {
  int8u ep;
#ifdef FIXED_ENDPOINT_COUNT
  int8u fixedEndpoints[] = FIXED_ENDPOINT_ARRAY;
  int16u fixedProfileIds[] = FIXED_PROFILE_IDS;
  int16u fixedDeviceIds[] = FIXED_DEVICE_IDS;
  int8u fixedDeviceVersions[] = FIXED_DEVICE_VERSIONS;
  int8u fixedEmberAfEndpointTypes[] = FIXED_ENDPOINT_TYPES;
  emberEndpointCount = FIXED_ENDPOINT_COUNT;
  for ( ep = 0; ep < FIXED_ENDPOINT_COUNT; ep++ ) {
    endpoints[ep].endpoint      = fixedEndpoints[ep];
    endpoints[ep].profileId     = fixedProfileIds[ep];
    endpoints[ep].deviceId      = fixedDeviceIds[ep];
    endpoints[ep].deviceVersion = fixedDeviceVersions[ep];
    endpoints[ep].endpointType 
      = (EmberAfEndpointType*)&(generatedEmberAfEndpointTypes[fixedEmberAfEndpointTypes[ep]]);
  }
#else
  for ( ep = 0; ep < MAX_ENDPOINT_COUNT; ep++ ) {
    endpoints[ep].endpoint      = endpointNumber(ep);
    endpoints[ep].profileId     = endpointProfileId(ep);
    endpoints[ep].deviceId      = endpointDeviceId(ep);
    endpoints[ep].deviceVersion = endpointDeviceVersion(ep);
    endpoints[ep].endpointType  = endpointType(ep);
    if ( endpoints[ep].endpoint != 0xFF ) {
      emberEndpointCount++;
    } else {
      break;
    }
  }
#endif // FIXED_ENDPOINT_COUNT
}

int8u emberAfEndpointCount() 
{
  return emberEndpointCount;
}

// some data types (like strings) are sent OTA in human readable order
// (how they are read) instead of little endian as the data types are.
boolean emberAfIsThisDataTypeAStringType(EmberAfAttributeType dataType)
{
  if ((dataType == ZCL_OCTET_STRING_ATTRIBUTE_TYPE) ||
      (dataType == ZCL_CHAR_STRING_ATTRIBUTE_TYPE) ||
      (dataType == ZCL_LONG_OCTET_STRING_ATTRIBUTE_TYPE) ||
      (dataType == ZCL_LONG_CHAR_STRING_ATTRIBUTE_TYPE))
    {
      return TRUE;
    }
  return FALSE;
}

// This function is used to call the per-cluster default response callback
void emberAfClusterDefaultResponseCallback(int8u endpoint,
                                           EmberAfClusterId clusterId,
                                           int8u commandId,
                                           EmberAfStatus status,
                                           int8u clientServerMask)
{
  EmberAfGenericClusterFunction f;
  EmberAfCluster *cluster = emberAfFindCluster(endpoint,
                                               clusterId,
                                               clientServerMask);
  if (cluster == NULL) return;
  f = emberAfFindClusterFunction(cluster,
                                 CLUSTER_MASK_DEFAULT_RESPONSE_FUNCTION);
  if (f == NULL) return;
  ((EmberAfDefaultResponseFunction)f)(endpoint, commandId, status);
}

// This function is used to call the per-cluster message sent callback
void emberAfClusterMessageSentCallback(EmberOutgoingMessageType type,
                                       int16u indexOrDestination,
                                       EmberApsFrame *apsFrame,
                                       int16u msgLen,
                                       int8u *message,
                                       EmberStatus status)
{
  EmberAfGenericClusterFunction f;
  EmberAfCluster *cluster;
  if (apsFrame == NULL || message == NULL || msgLen == 0) return;
  cluster = emberAfFindCluster(apsFrame->sourceEndpoint,
                               apsFrame->clusterId,
                               (((message[0] & ZCL_FRAME_CONTROL_DIRECTION_MASK)
                                 == ZCL_FRAME_CONTROL_SERVER_TO_CLIENT)
                                ? CLUSTER_MASK_SERVER
                                : CLUSTER_MASK_CLIENT));
  if (cluster == NULL) return;
  f = emberAfFindClusterFunction(cluster, CLUSTER_MASK_MESSAGE_SENT_FUNCTION);
  if (f == NULL) return;
  ((EmberAfMessageSentFunction)f)(type,
                                  indexOrDestination,
                                  apsFrame,
                                  msgLen,
                                  message,
                                  status);
}

// This function is used to call the per-cluster attribute changed callback
void emAfClusterAttributeChangedCallback(int8u endpoint,
                                         EmberAfClusterId clusterId,
                                         EmberAfAttributeId attributeId,
                                         int8u clientServerMask,
                                         int16u manufacturerCode)
{
  EmberAfGenericClusterFunction f;
  EmberAfCluster *cluster = emberAfFindCluster(endpoint,
                                               clusterId,
                                               clientServerMask);
  if (cluster == NULL) return;
  if (manufacturerCode != 0) {
    f = emberAfFindClusterFunction(cluster,
      CLUSTER_MASK_MANUFACTURER_SPECIFIC_ATTRIBUTE_CHANGED_FUNCTION);
    if (f == NULL) return;
    ((EmberAfManufacturerSpecificClusterAttributeChangedCallback)f)(endpoint, 
      attributeId, manufacturerCode);
  } else {
    f = emberAfFindClusterFunction(cluster,
                                   CLUSTER_MASK_ATTRIBUTE_CHANGED_FUNCTION);
    if (f == NULL) return;
    ((EmberAfClusterAttributeChangedCallback)f)(endpoint, attributeId);
  }
}

// Calls the init functions.
void emAfCallInits() 
{
  int8u ep;
  for ( ep = 0; ep < emberAfEndpointCount(); ep ++ ) {
    int8u endpoint = endpoints[ep].endpoint;
    EmberAfEndpointType *epType = endpoints[ep].endpointType;
    int8u clusterIndex;
    for ( clusterIndex = 0; 
          clusterIndex < epType->clusterCount; 
          clusterIndex ++ ) {
      EmberAfCluster *cluster = &(epType->cluster[clusterIndex]);
      EmberAfGenericClusterFunction f;
      emberAfClusterInitCallback(endpoint, cluster->clusterId);
      f = emberAfFindClusterFunction(cluster, CLUSTER_MASK_INIT_FUNCTION);
      if ( f != NULL ) {
        ((EmberAfInitFunction)f)(endpoint);
      }
    }
  }
}

// Returns the pointer to metadata, or null if it is not found
EmberAfAttributeMetadata* emberAfLocateAttributeMetadata(int8u endpoint,
                                                         EmberAfClusterId clusterId,
                                                         EmberAfAttributeId attributeId,
                                                         int8u mask,
                                                         int16u manufacturerCode)
{
  EmberAfAttributeSearchRecord attRecord;
  EmberAfAttributeMetadata *metadata;
  MEMSET(&attRecord, 0, sizeof(EmberAfAttributeSearchRecord));
  attRecord.endpoint = endpoint;
  attRecord.clusterId = clusterId;
  attRecord.attributeId = attributeId;
  attRecord.clusterMask = mask;
  attRecord.manufacturerCode = manufacturerCode;
  return (emberAfReadOrUpdateAttribute(&attRecord,
                                       &metadata,
                                       NULL,  // buffer
                                       FALSE) // read
          ? metadata
          : NULL);
}

static int8u* singletonAttributeLocation(EmberAfAttributeMetadata *am) 
{
  EmberAfAttributeMetadata *m 
    = (EmberAfAttributeMetadata *)&(generatedAttributes[0]);
  int16u index = 0;
  while ( m < am ) {
    if ( m->mask & ATTRIBUTE_MASK_SINGLETON ) {
      index += m->size;
    }
    m++;
  }
  return (int8u *)(singletonAttributeData + index);
}


// This function does mem copy, but smartly, which means
// that if the type is a string, it will only copy as much as it needs
static boolean typeSensitiveMemCopy(int8u* dest,
                                 int8u* src,
                                 EmberAfAttributeMetadata *am)
{
  if (emberAfIsThisDataTypeAStringType(am->attributeType)) {
    if (emberAfStringLength(src) <= am->size) {
      MEMCOPY(dest, src, emberAfStringLength(src) + 1);
      return TRUE;
    } else {
      return FALSE;
    }
  } else {
    MEMCOPY(dest, src, am->size);
    return TRUE;
  }
}

boolean emberAfContainsAttribute(int8u endpoint,
                                 EmberAfClusterId clusterId,
                                 EmberAfAttributeId attributeId,
                                 int8u mask,
                                 int16u manufacturerCode) {
  EmberAfAttributeSearchRecord attRecord;
  MEMSET(&attRecord, 0, sizeof(EmberAfAttributeSearchRecord));
  attRecord.endpoint = endpoint;
  attRecord.clusterId = clusterId;
  attRecord.attributeId = attributeId;
  attRecord.clusterMask = mask;
  attRecord.manufacturerCode = manufacturerCode;
  return emberAfReadOrUpdateAttribute(&attRecord,
                                      NULL,
                                      NULL,
                                      FALSE);
}

boolean emberAfRetrieveAttribute(int8u endpoint,
                                 EmberAfClusterId clusterId,
                                 EmberAfAttributeId attributeId,
                                 int8u mask,
                                 int16u manufacturerCode,
                                 EmberAfAttributeMetadata **metadata,
                                 int8u *buffer) {
  EmberAfAttributeSearchRecord attRecord;
  MEMSET(&attRecord, 0, sizeof(EmberAfAttributeSearchRecord));
  attRecord.endpoint = endpoint;
  attRecord.clusterId = clusterId;
  attRecord.attributeId = attributeId;
  attRecord.clusterMask = mask;
  attRecord.manufacturerCode = manufacturerCode;
  return emberAfReadOrUpdateAttribute(&attRecord,
                                      metadata,
                                      buffer,
                                      FALSE);
}

boolean emberAfUpdateAttribute(int8u endpoint,
                               EmberAfClusterId clusterId,
                               EmberAfAttributeId attributeId,
                               int8u mask,
                               int16u manufacturerCode,
                               EmberAfAttributeMetadata **metadata,
                               int8u *buffer) {
  EmberAfAttributeSearchRecord attRecord;
  MEMSET(&attRecord, 0, sizeof(EmberAfAttributeSearchRecord));
  attRecord.endpoint = endpoint;
  attRecord.clusterId = clusterId;
  attRecord.attributeId = attributeId;
  attRecord.clusterMask = mask;
  attRecord.manufacturerCode = manufacturerCode;
  return emberAfReadOrUpdateAttribute(&attRecord,
                                      metadata,
                                      buffer,
                                      TRUE);
}

/** 
 * @brief Returns the manufacturer code or 0 if none could be found.
 */
static int16u emAfGetManufacturerCode(EmberAfManufacturerCodeEntry *codes,
                               int16u codeTableSize,
                               int16u tableIndex) {
  int16u i;
  for (i = 0; i < codeTableSize; i++, codes++) {
    if (codes->index == tableIndex) {
      return codes->manufacturerCode;
    }
  }
  return 0;
}

int16u emAfGetManufacturerCodeForAttribute(EmberAfAttributeMetadata *attMetaData) {
  return emAfGetManufacturerCode(
    (EmberAfManufacturerCodeEntry*) attributeManufacturerCodes,
    attributeManufacturerCodeCount,
    (attMetaData - generatedAttributes));  
}

int16u emAfGetManufacturerCodeForCluster(EmberAfCluster *cluster) {
  return emAfGetManufacturerCode(
    (EmberAfManufacturerCodeEntry*) clusterManufacturerCodes, 
    clusterManufacturerCodeCount, 
    (cluster - generatedClusters));
}

/**
 * @brief Matches a cluster based on cluster id, direction and manufacturer code.
 *   This function assumes that the passed cluster's endpoint already
 *   matches the endpoint of the EmberAfAttributeSearchRecord.
 *
 * Cluster's match if:
 *   1. Cluster ids match AND
 *   2. Cluster directions match as defined by cluster->mask 
 *        and attRecord->clusterMask AND
 *   3. If the clusters are mf specific, their mf codes match.
 */
boolean emAfMatchCluster(EmberAfCluster *cluster, 
                         EmberAfAttributeSearchRecord *attRecord) {
  if ((cluster->clusterId == attRecord->clusterId) &&
      (cluster->mask & attRecord->clusterMask) &&
      (emberAfClusterIsManufacturerSpecific(cluster) ? 
        (emAfGetManufacturerCodeForCluster(cluster) 
         == attRecord->manufacturerCode) 
       : TRUE)) {
    return TRUE;
  } 
  return FALSE;                         
}

/**
 * @brief Matches an attribute based on attribute id and manufacturer code.
 *   This function assumes that the passed cluster already matches the 
 *   clusterId, direction and mf specificity of the passed 
 *   EmberAfAttributeSearchRecord.
 * 
 * Note: If both the attribute and cluster are manufacturer specific,
 *   the cluster's mf code gets precedence.
 * 
 * Attributes match if:
 *   1. Att ids match AND
 *      a. cluster IS mf specific OR
 *      b. both stored and saught attributes are NOT mf specific OR
 *      c. stored att IS mf specific AND mfg codes match.
 */
boolean emAfMatchAttribute(EmberAfCluster *cluster,
                           EmberAfAttributeMetadata *am,
                           EmberAfAttributeSearchRecord *attRecord) {
                                      
  if (am->attributeId == attRecord->attributeId && 
       ((emberAfClusterIsManufacturerSpecific(cluster)) ||
        (!emberAfAttributeIsManufacturerSpecific(am) &&
               attRecord->manufacturerCode == 0) ||
        (emberAfAttributeIsManufacturerSpecific(am) &&
               emAfGetManufacturerCodeForAttribute(am) 
               == attRecord->manufacturerCode))) {
    return TRUE;
  }
  return FALSE; //we have a missmatch
}

// Internal function that either reads or write the attribute.
// If write is true, then buffer is data that will be written.
// If write is false, then buffer will be written over with current data.
boolean emberAfReadOrUpdateAttribute(EmberAfAttributeSearchRecord *attRecord,
                                     EmberAfAttributeMetadata **metadata,
                                     int8u *buffer,
                                     boolean write) 
{
  int8u i;
  int16u attributeOffsetIndex = 0;
    
  for (i = 0; i < emberAfEndpointCount(); i++) {
    if (endpoints[i].endpoint == attRecord->endpoint) { // Got the endpoint
      EmberAfEndpointType *endpointType = endpoints[i].endpointType;
      int8u clusterIndex;
      for (clusterIndex = 0;
           clusterIndex < endpointType->clusterCount;
           clusterIndex++) {
        EmberAfCluster *cluster = &(endpointType->cluster[clusterIndex]);
        if (emAfMatchCluster(cluster, attRecord)) { // Got the cluster
          int16u attrIndex;
          for (attrIndex = 0;
               attrIndex < cluster->attributeCount;
               attrIndex++) {
            EmberAfAttributeMetadata *am = &(cluster->attributes[attrIndex]);
            if (emAfMatchAttribute(cluster, 
                                   am, 
                                   attRecord)) { // Got the attribute

              // If passed metadata location is not null, populate
              if (metadata != NULL) {
                *metadata = am;
              }

              // If buffer is not null, then either read or write,
              // depending on the flag.
              if (buffer != NULL) {
                if (write) { 
                  // we're writing the attribute
                  if (am->mask & ATTRIBUTE_MASK_EXTERNAL_STORAGE) {
                    // update to external location
                    return emberAfExternalAttributeWriteCallback(attRecord->endpoint,
                      attRecord->clusterId,
                      am,
                      (emberAfAttributeIsManufacturerSpecific(am) ?
                        emAfGetManufacturerCodeForAttribute(am) : 0),
                      buffer);
                  } else if (am->mask & ATTRIBUTE_MASK_SINGLETON) {
                    int8u *dataPtr = singletonAttributeLocation(am);
                    return typeSensitiveMemCopy(dataPtr, buffer, am);
                  } else {
                    return typeSensitiveMemCopy((int8u *)(attributeData
                                                          + attributeOffsetIndex),
                                                buffer,
                                                am);
                  }
                } else { 
                  // we're reading the attribute
                  if (am->mask & ATTRIBUTE_MASK_EXTERNAL_STORAGE) {
                    return emberAfExternalAttributeReadCallback(attRecord->endpoint,
                            attRecord->clusterId,
                            am,
                            (emberAfAttributeIsManufacturerSpecific(am) ?
                              emAfGetManufacturerCodeForAttribute(am) : 0),
                            buffer);
                  } else if (am->mask & ATTRIBUTE_MASK_SINGLETON) {
                    int8u *dataPtr = singletonAttributeLocation(am);
                    return typeSensitiveMemCopy(buffer, dataPtr, am);
                  } else {
                    // copy from an internal array
                    return typeSensitiveMemCopy(buffer, 
                                                (int8u *)(attributeData
                                                          + attributeOffsetIndex), 
                                                am);
                  }
                }
              }
              return TRUE;
            } else { // Not the attribute we are looking for
              // Increase the index if attribute is not externally stored
              if (!(am->mask & ATTRIBUTE_MASK_EXTERNAL_STORAGE)
                   && !(am->mask & ATTRIBUTE_MASK_SINGLETON) ) {
                attributeOffsetIndex += emberAfAttributeSize(am);
              }
            }
          }
        } else { // Not the cluster we are looking for
          attributeOffsetIndex += cluster->clusterSize;
        }
      }
    } else { // Not the endpoint we are looking for
      attributeOffsetIndex += endpoints[i].endpointType->endpointSize;
    }
  }
  return FALSE; // Sorry, attribute was not found.
}

// mask = 0 -> find either client or server
// mask = CLUSTER_MASK_CLIENT -> find client
// mask = CLUSTER_MASK_SERVER -> find server
static EmberAfCluster *emberAfFindClusterInType(EmberAfEndpointType *endpointType, 
                                                EmberAfClusterId clusterId,
                                                int8u mask)
{
  int8u i;
  for (i = 0; i < endpointType->clusterCount; i++) {
    EmberAfCluster *cluster = &(endpointType->cluster[i]);
    if (cluster->clusterId == clusterId
        && (mask == 0
            || (mask == CLUSTER_MASK_CLIENT && emberAfClusterIsClient(cluster))
            || (mask == CLUSTER_MASK_SERVER && emberAfClusterIsServer(cluster)))) {
      return cluster;
    }
  }
  return NULL;
}

int8u emberAfClusterIndex(int8u endpoint, 
                          EmberAfClusterId clusterId, 
                          int8u mask)
{
  int8u ep;
  int8u index = 0xFF;
  for ( ep=0; ep < emberAfEndpointCount(); ep++ ) {
    EmberAfEndpointType *endpointType = endpoints[ep].endpointType;
    if ( emberAfFindClusterInType(endpointType, clusterId, mask) != NULL ) {
      index++;
      if ( endpoints[ep].endpoint == endpoint ) 
        return index;
    }
  }
  return 0xFF;
}

// Returns TRUE If endpoint contains passed cluster
boolean emberAfContainsCluster(int8u endpoint, EmberAfClusterId clusterId) {
  return ( emberAfFindCluster(endpoint, clusterId, 0) != NULL );
}

boolean emberAfContainsServer(int8u endpoint, EmberAfClusterId clusterId) {
  return ( emberAfFindCluster(endpoint, clusterId, CLUSTER_MASK_SERVER) != NULL );
}

boolean emberAfContainsClient(int8u endpoint, EmberAfClusterId clusterId) {
  return ( emberAfFindCluster(endpoint, clusterId, CLUSTER_MASK_CLIENT) != NULL );
}

EmberAfCluster *emberAfFindCluster(int8u endpoint, 
                                   EmberAfClusterId clusterId, 
                                   int8u mask) {
  int8u ep = emberAfIndexFromEndpoint(endpoint);
  if ( ep == 0xFF ) 
    return NULL;
  else
    return emberAfFindClusterInType(endpoints[ep].endpointType, clusterId, mask);
}

// Returns the index of a given endpoint
int8u emberAfIndexFromEndpoint(int8u endpoint) 
{
  int8u epi;
  for (epi = 0; epi < emberAfEndpointCount(); epi++) {
    if (endpoints[epi].endpoint == endpoint) {
      return epi;
    }
  }
  return 0xFF;
}

// If server == true, returns the number of server clusters,
// otherwise number of client clusters on this endpoint
int8u emberAfClusterCount(int8u endpoint, boolean server) 
{
  int8u index = emberAfIndexFromEndpoint(endpoint);
  int8u i, c=0;
  EmberAfDefinedEndpoint *de;
  EmberAfCluster *cluster;

  if ( index == 0xFF ) return 0;
  de = &(endpoints[index]);
  if ( de->endpointType == NULL) {
    return 0;
  }
  for ( i=0; i<de->endpointType->clusterCount; i++ ) {
    cluster = &(de->endpointType->cluster[i]);
    if ( server && emberAfClusterIsServer(cluster) )
      c++;
    if ( (!server) && emberAfClusterIsClient(cluster) )
      c++;
  }
  return c;
}

// Returns the clusterId of Nth server or client cluster,
// depending on server toggle.
EmberAfCluster *emberAfGetNthCluster(int8u endpoint, int8u n, boolean server) 
{
  int8u index = emberAfIndexFromEndpoint(endpoint);
  EmberAfDefinedEndpoint *de;
  int8u i,c=0;
  EmberAfCluster *cluster;

  if ( index == 0xFF ) return NULL;
  de = &(endpoints[index]);
  
  for ( i = 0; i < de->endpointType->clusterCount; i++ ) {
    cluster = &(de->endpointType->cluster[i]);
    
    if ( ( server && emberAfClusterIsServer(cluster) )
         || ( (!server) &&  emberAfClusterIsClient(cluster) ) ) {
      if ( c == n ) return cluster;
      c++;
    }
    
  }
  return NULL;
}

// Returns number of clusters put into the passed cluster list
// for the given endpoint and client/server polarity
int8u emberAfGetClustersFromEndpoint(int8u endpoint, int16u *clusterList, int8u listLen, boolean server) {
  int8u clusterCount = emberAfClusterCount(endpoint, server);
  int8u i;
  EmberAfCluster *cluster;
  if (clusterCount > listLen) {
    clusterCount = listLen;
  }
  for (i = 0; i < clusterCount; i++) {
    cluster = emberAfGetNthCluster(endpoint, i, server);
    clusterList[i] = (cluster == NULL ? 0xFFFF : cluster->clusterId);
  }
  return clusterCount;
}


void emberAfLoadAttributesFromDefaults(void) 
{
  int8u ep, clusterI;
  int16u attr;
  int8u *ptr;
  for ( ep = 0; ep < emberAfEndpointCount(); ep++ ) {
    EmberAfDefinedEndpoint *de = &(endpoints[ep]);
    for ( clusterI = 0; clusterI < de->endpointType->clusterCount; clusterI++) {
      EmberAfCluster *cluster = &(de->endpointType->cluster[clusterI]);
      for ( attr = 0; attr < cluster->attributeCount; attr++) {
        EmberAfAttributeMetadata *am = &(cluster->attributes[attr]);
        if (!(am->mask & ATTRIBUTE_MASK_EXTERNAL_STORAGE)) {
          EmberAfAttributeSearchRecord attRecord;
          MEMSET(&attRecord, 0, sizeof(EmberAfAttributeSearchRecord));
          if (am->mask & ATTRIBUTE_MASK_MIN_MAX) {
            if ( emberAfAttributeSize(am) <= 2 ) {
              ptr = (int8u*)&(am->defaultValue.ptrToMinMaxValue->defaultValue.defaultValue);
            } else {
              ptr = (int8u*)am->defaultValue.ptrToMinMaxValue->defaultValue.ptrToDefaultValue;
            }
          } else {
            if ( emberAfAttributeSize(am) <= 2 ) {
              ptr = (int8u*)&(am->defaultValue.defaultValue);
            } else {
              ptr = (int8u*)am->defaultValue.ptrToDefaultValue;
            }
          }
#if (BIGENDIAN_CPU)
          // The default value for one- and two-byte attributes is stored in an
          // int16u.  On big-endian platforms, a pointer to the default value of
          // a one-byte attribute will point to the wrong byte.  So, for those
          // cases, nudge the pointer forward so it points to the correct byte.
          if (emberAfAttributeSize(am) == 1) {
            *ptr++;
          }
#endif //BIGENDIAN
          attRecord.endpoint = de->endpoint;
          attRecord.clusterId = cluster->clusterId;
          attRecord.attributeId = am->attributeId;
          attRecord.clusterMask = (emberAfAttributeIsClient(am)
                                  ? CLUSTER_MASK_CLIENT
                                  : CLUSTER_MASK_SERVER);
          if (emberAfClusterIsManufacturerSpecific(cluster)) {            
            attRecord.manufacturerCode = 
                emAfGetManufacturerCodeForCluster(cluster);
          } else if (emberAfAttributeIsManufacturerSpecific(am)) {            
            attRecord.manufacturerCode = 
                  emAfGetManufacturerCodeForAttribute(am);
                
          }
          emberAfReadOrUpdateAttribute(&attRecord,
                                       NULL,  // metadata - not used
                                       ptr,
                                       TRUE); // write
        }
      }
    }
  }
}

void emberAfLoadAttributesFromTokens(void) 
{
// On EZSP host we currently do not support this. We need to come up with some 
// callbacks.
#ifndef EZSP_HOST
  GENERATED_TOKEN_LOADER;
#endif // EZSP_HOST
}

void emberAfSaveAttributeToToken(int8u *data,
                                 int8u endpoint, 
                                 int16u clusterId,
                                 EmberAfAttributeMetadata *metadata) 
{
  // Get out of here if this attribute doesn't have a token.
  if ( !emberAfAttributeIsTokenized(metadata)) return;

// On EZSP host we currently do not support this. We need to come up with some 
// callbacks.
#ifndef EZSP_HOST
  GENERATED_TOKEN_SAVER;
#endif // EZSP_HOST
}

// This function returns the actual function point from the array, 
// iterating over the function bits.
EmberAfGenericClusterFunction 
emberAfFindClusterFunction(EmberAfCluster *cluster,
                           EmberAfClusterMask functionMask) {
  EmberAfClusterMask mask = 0x01;
  int8u functionIndex = 0;

  if ( (cluster->mask & functionMask) == 0 )
    return NULL;
  
  while ( mask < functionMask ) {
    if ( (cluster->mask & mask) != 0 ) 
      functionIndex++;
    mask <<= 1;
  }
  return cluster->functions[functionIndex];
}

