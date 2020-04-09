/**
 * @file af-types.h
 * @brief The include file for all the types for Ember ApplicationFramework
 *
 * <!-- Author(s):  Timotej Ecimovic, timotej@ember.com -->
 *
 * <!--Copyright 2004-2010 by Ember Corporation. All rights reserved.    *80*-->
 */

/** @addtogroup aftypes Application Framework V2 Types Reference
 * This documentation describes the types used by the Ember 
 * Application Framework V2.
 * @{
 */ 


#ifndef __AF_API_TYPES__
#define __AF_API_TYPES__

#include "app/framework/gen/enums.h"

/**
 * @brief Type for refering to ZigBee application profile id
 */
typedef int16u EmberAfProfileId;

/**
 * @brief Type for refering to ZCL attribute id
 */
typedef int16u EmberAfAttributeId;

/**
 * @brief Type for refering to ZCL cluster id
 */
typedef int16u EmberAfClusterId;

/**
 * @brief Type for refering to ZCL attribute type
 */
typedef int8u EmberAfAttributeType;

/**
 * @brief Type for the cluster mask
 */
typedef int8u EmberAfClusterMask;

/**
 * @brief Type for the attribute mask
 */
typedef int8u EmberAfAttributeMask;

/**
 * @brief Generic function type, used for either of the cluster function.
 *
 * This type is used for the array of the cluster functions, and should
 * always be cast into one of the specific functions before being called.
 */
typedef void (*EmberAfGenericClusterFunction)(void);

/**
 * @brief A distinguished manufacturer code that is used to indicate the
 * absence of a manufacturer-specific profile, cluster, command, or attribute.
 */
#define EMBER_AF_NULL_MANUFACTURER_CODE 0x0000

/**
 * @brief Type for default values.
 *
 * Default value is either a value itself, if it is 2 bytes or less,
 * or a pointer to the value itself, if attribute type is longer than
 * 2 bytes.
 */
typedef union {
  /** 
   * Points to data if size is more than 2 bytes.
   * If size is more than 2 bytes, and this value is NULL,
   * then the default value is all zeroes.
   */
  int8u *ptrToDefaultValue; 
  /**
   * Actual default value if the attribute size is 2 bytes or less.
   */
  int16u defaultValue;
} EmberAfDefaultAttributeValue;

/**
 * @brief Type describing the attribute default, min and max values.
 *
 * This struct is required if the attribute mask specifies that this
 * attribute has a known min and max values.
 */
typedef struct {
  /** 
   * Default value of the attribute.
   */
  EmberAfDefaultAttributeValue defaultValue;
  /**
   * Minimum allowed value 
   */
  EmberAfDefaultAttributeValue minValue;
  /**
   * Maximum allowed value.
   */
  EmberAfDefaultAttributeValue maxValue;
} EmberAfAttributeMinMaxValue;

/**
 * @brief Union describing the attribute default/min/max values.
 */
typedef union {
  /** 
   * Points to data if size is more than 2 bytes.
   * If size is more than 2 bytes, and this value is NULL,
   * then the default value is all zeroes.
   */
  int8u *ptrToDefaultValue; 
  /**
   * Actual default value if the attribute size is 2 bytes or less.
   */
  int16u defaultValue;
  /**
   * Points to the min max attribute value structure, if min/max is
   * supported for this attribute.
   */
  EmberAfAttributeMinMaxValue *ptrToMinMaxValue;
} EmberAfDefaultOrMinMaxAttributeValue;


/**
 * @brief Each attribute has it's metadata stored in such struct.
 *
 * There is only one of these per attribute across all endpoints.
 */
typedef struct {
  /** 
   * Attribute ID, according to ZCL specs.
   */
  EmberAfAttributeId attributeId;
  /**
   * Attribute type, according to ZCL specs.
   */
  EmberAfAttributeType attributeType;
  /**
   * Size of this attribute in bytes.
   */
  int8u size;
  /**
   * Attribute mask, tagging attribute with specific 
   * functionality. See ATTRIBUTE_MASK_ macros defined
   * in app/framework/gen/attribute-storage.h.
   */
  EmberAfAttributeMask mask;
  /**
   * Pointer to the default value union. Actual value stored
   * depends on the mask.
   */
  EmberAfDefaultOrMinMaxAttributeValue  defaultValue;
} EmberAfAttributeMetadata;

/**
 * @brief Struct describing cluster
 */
typedef struct {
  /**
   *  ID of cluster according to ZCL spec
   */
  EmberAfClusterId clusterId;
  /**
   * Pointer to attribute metadata array for this cluster.
   */
  EmberAfAttributeMetadata *attributes;
  /**
   * Total number of attributes
   */
  int16u attributeCount;
  /**
   * Total size of non-external, non-singleton attribute for this cluster.
   */
  int16u clusterSize;
  /**
   * Mask with additional functionality for cluster. See CLUSTER_MASK
   * macros.
   */
  EmberAfClusterMask mask;

  /**
   * An array into the cluster functions. The length of the array
   * is determined by the function bits in mask. This may be null
   * if this cluster has no functions.
   */
  const EmberAfGenericClusterFunction *functions;

} EmberAfCluster;

/**
 * @brief Struct used to find an attribute in storage. Together the elements
 * in this search record constitute the "primary key" used to identify a unique
 * attribute value in attribute storage.
 */
typedef struct {
   
  /**
  * Endpoint that the attribute is located on
  */
  int8u endpoint;
   
  /**
  * Cluster that the attribute is located on. If the cluster
  * id is inside the manufacturer specific range, 0xfc00 - 0xffff,
  * The manufacturer code should also be set to the code associated
  * with the manufacturer specific cluster.
  */
  EmberAfClusterId clusterId;
   
  /**
  * Cluster mask for the cluster, used to determine if it is
  * the server or client version of the cluster. See CLUSTER_MASK_
  * macros defined in app/framework/gen/attribute-storage.h
  */
  EmberAfClusterMask clusterMask;
   
  /**
  * The two byte identifier for the attribute. If the cluster id is 
  * inside the manufacturer specific range 0xfc00 - 0xffff, or the manufacturer
  * code is NOT 0, the attribute is assumed to be manufacturer specific.
  */   
  EmberAfAttributeId attributeId;
      
  /**
   * Manufacturer Code associated with the cluster and or attribute. 
   * If the cluster id is inside the manufacturer specific
   * range, this value should indicate the manufacturer code for the 
   * manufacturer specific cluster. Otherwise if this value is non zero, 
   * and the cluster id is a standard ZCL cluster, 
   * it is assumed that the attribute being sought is a manufacturer specific
   * extension to the standard ZCL cluster indicated by the cluster id. 
   */ 
  int16u manufacturerCode;
} EmberAfAttributeSearchRecord;

/**
 * A struct used to construct a table of manufacturer codes for 
 * manufacturer specfic attributes and clusters.
 */
typedef struct {
  int16u index;
  int16u manufacturerCode;
} EmberAfManufacturerCodeEntry;

/**
 * @brief a struct containing the superset of values
 * passed to both emberIncomingMessageHandler on the SOC and 
 * ezspIncomingMessageHandler on the host.
 */
typedef struct {
  /**
   * The type of the incoming message
   */
  EmberIncomingMessageType type;
  /**
   * Aps frame for the incoming message
   */
  EmberApsFrame* apsFrame;
  /**
   * The message copied into a flat buffer
   */
  int8u* message;
  /**
   * Length of the incoming message
   */
  int16u msgLen;
  /**
   * Two byte node id of the sending node.
   */
  int16u source;
  /**
   * Link quality from the node that last relayed
   * the message.
   */
  int8u lastHopLqi;
  /**
   * The energy level (in units of dBm) observed during the reception.
   */
  int8s lastHopRssi;
  /**
   * The index of a binding that matches the message 
   * or 0xFF if there is no matching binding.
   */
  int8u bindingTableIndex;
  /**
   * The index of the entry in the address table 
   * that matches the sender of the message or 0xFF 
   * if there is no matching entry.
   */
  int8u addressTableIndex;
} EmberAfIncomingMessage;


/**
 * @brief Interpan Message type: unicast, broadcast, or multicast.
 */
typedef int8u EmberAfInterpanMessageType;
#define EMBER_AF_INTER_PAN_UNICAST   0x00
#define EMBER_AF_INTER_PAN_BROADCAST 0x08
#define EMBER_AF_INTER_PAN_MULTICAST 0x0C

// Legacy names
#define INTER_PAN_UNICAST   EMBER_AF_INTER_PAN_UNICAST
#define INTER_PAN_BROADCAST EMBER_AF_INTER_PAN_BROADCAST
#define INTER_PAN_MULTICAST EMBER_AF_INTER_PAN_MULTICAST


#define EMBER_AF_INTERPAN_OPTION_NONE                 0x0000
#define EMBER_AF_INTERPAN_OPTION_APS_ENCRYPT          0x0001
#define EMBER_AF_INTERPAN_OPTION_MAC_HAS_LONG_ADDRESS 0x0002

/**
 * @brief The options for sending/receiving interpan messages.
 */
typedef int16u EmberAfInterpanOptions;

/**
 * @brief Interpan header used for sending and receiving interpan
 *   messages.
 */
typedef struct {
  EmberAfInterpanMessageType messageType;

  /**
   * MAC addressing
   * For outgoing messages this is the destination.  For incoming messages
   * it is the source, which always has a long address.
   */
  EmberEUI64 longAddress;
  EmberNodeId shortAddress;
  EmberPanId panId;

  /** 
   * APS data
   */
  EmberAfProfileId profileId;
  EmberAfClusterId clusterId;
  /**
   * The groupId is only used for 
   * EMBER_AF_INTERPAN_MULTICAST
   */
  EmberMulticastId groupId;
  EmberAfInterpanOptions options;
} EmberAfInterpanHeader;

// Legacy Name
#define InterPanHeader EmberAfInterpanHeader

/**
 * @brief The options for what interpan messages are allowed.
 */
typedef int8u EmberAfAllowedInterpanOptions;

#define EMBER_AF_INTERPAN_DIRECTION_CLIENT_TO_SERVER 0x01
#define EMBER_AF_INTERPAN_DIRECTION_SERVER_TO_CLIENT 0x02
#define EMBER_AF_INTERPAN_DIRECTION_BOTH             0x03
#define EMBER_AF_INTERPAN_GLOBAL_COMMAND             0x04
#define EMBER_AF_INTERPAN_MANUFACTURER_SPECIFIC      0x08

/**
 * @brief This structure is used define an interpan message that
 *   will be accepted by the interpan filters. 
 */
typedef struct {
  EmberAfProfileId profileId;
  EmberAfClusterId clusterId;
  int8u commandId;
  EmberAfAllowedInterpanOptions options;
} EmberAfAllowedInterPanMessage;


/**
 * @brief The EmberAFClusterCommand is a struct wrapper
 *   for all the data pertaining to a command which comes
 *   in over the air. This enables struct is used to 
 *   encapsulate a command in a single place on the stack
 *   and pass a pointer to that location around during
 *   command processing
 */
typedef struct {
  /**
   * Aps frame for the incoming message
   */
  EmberApsFrame            *apsFrame;
  EmberIncomingMessageType  type;
  EmberNodeId               source;
  int8u                    *buffer;
  int16u                    bufLen;
  boolean                   clusterSpecific;
  boolean                   mfgSpecific;
  int16u                    mfgCode;
  int8u                     seqNum;
  int8u                     commandId;
  int8u                     payloadStartIndex;
  int8u                     direction;
  EmberAfInterpanHeader    *interPanHeader;
} EmberAfClusterCommand;

/**
 * @brief Endpoint type struct describes clusters that are on the endpoint.
 */
typedef struct {
  /**
   * Pointer to the cluster structs, describing clusters on this
   * endpoint type.
   */
  EmberAfCluster *cluster;
  /**
   * Number of clusters in this endpoint type.
   */
  int8u  clusterCount;
  /**
   * Size of all non-external, non-singlet attribute in this endpoint type.
   */
  int16u endpointSize;
} EmberAfEndpointType;

/**
 * @brief Struct that maps actual endpoint type, onto a specific endpoint.
 */
typedef struct {
  /**
   * Actual ZigBee endpoint number.
   */
  int8u endpoint;
  /**
   * Profile ID of the device on this endpoint.
   */
  EmberAfProfileId profileId;
  /**
   * Device ID of the device on this endpoint.
   */
  int16u deviceId;
  /**
   * Version of the device.
   */
  int8u deviceVersion;
  /**
   * Endpoint type for this endpoint.
   */
  EmberAfEndpointType *endpointType;
} EmberAfDefinedEndpoint;


// Cluster specific types

/**
 * @brief Struct that describes a load control event.
 *
 * This is used in the load control event callback and
 * within the demand response load control cluster code.
 */
typedef struct {
  int32u     eventId;
  EmberEUI64 source;
  int8u      sourceEndpoint;
  int8u      destinationEndpoint;
  int16u     deviceClass;
  int8u      utilityEnrollmentGroup;
  /**
   * Start time in seconds
   */
  int32u     startTime;
  /**
   * Duration in minutes
   */
  int16u     duration;
  int8u      criticalityLevel;
  int8u      coolingTempOffset;
  int8u      heatingTempOffset;
  int16s     coolingTempSetPoint;
  int16s     heatingTempSetPoint;
  int8s      avgLoadPercentage;
  int8u      dutyCycle;
  int8u      eventControl;
  int16u     startRand;
  int16u     endRand;
  int8u      optionControl;
} EmberAfLoadControlEvent;

/** @} END addtogroup */

/** @addtogroup servicediscovery */


/**
 * @brief This is an enum used to indicate the result of the
 *   service discovery.  Unicast discoveries are completed
 *   as soon as a response is received.  Broadcast discoveries
 *   wait a period of time for multiple responses to be received.
 */
typedef enum {
  EMBER_AF_BROADCAST_SERVICE_DISCOVERY_COMPLETE             = 0x00,
  EMBER_AF_BROADCAST_SERVICE_DISCOVERY_RESPONSE_RECEIVED    = 0x01,
  EMBER_AF_UNICAST_SERVICE_DISCOVERY_TIMEOUT                = 0x02,
  EMBER_AF_UNICAST_SERVICE_DISCOVERY_COMPLETE_WITH_RESPONSE = 0x03,
} EmberAfServiceDiscoveryStatus;

#define EM_AF_DISCOVERY_RESPONSE_MASK (0x01)

/**
 * @brief A simple way to determine if the service discovery callback
 *   has a response.
 */
#define emberAfHaveDiscoveryResponseStatus(status)  ((status) & EM_AF_DISCOVERY_RESPONSE_MASK)

/**
 * @brief A structure containing general information about the service discovery.
 */
typedef struct {
  /**
   * The status indicates both the type of request (broadcast or unicast)
   * and whether a response has been received.
   */
  EmberAfServiceDiscoveryStatus status;

  /**
   * This indicates what ZDO request cluster was associated with the request.
   * It is helpful for a callback that may be used for multiple ZDO request types
   * to determine the type of data returned.  This will be based on the
   * ZDO cluster values defined in ember-types.h.
   */
  int16u zdoRequestClusterId;

  /**
   * This is the address of the device that matched the request, which may
   * be different than the device that *actually* is responding.  This occurs
   * when parents respond on behalf of their children.
   */
  EmberNodeId matchAddress;

  /**
   * Only if the status code indicates a response will this data be non-NULL.
   * When there is data, the type is according to the ZDO cluster ID sent out.
   * For NETWORK_ADDRESS_REQUEST or IEEE_ADDRESS_REQUEST, the long ID will
   * be contained in the responseData,  so it will be a value of type ::EmberEUI64.
   * The short ID will be in the matchAddress parameter field.  
   * For the MATCH_DESCRIPTORS_REQUEST the responseData will point
   * to an ::EmberAfEndpointList structure.
   */
  const void* responseData;
} EmberAfServiceDiscoveryResult;

/**
 * @brief A list of endpoints received during a service discovery attempt.
 *   This will be returned for a match descriptor request and a 
 *   active endpoint request.
 */
typedef struct {
  int8u count;
  const int8u* list;
} EmberAfEndpointList;

/**
 * @brief This defines a callback where a code element or cluster can be informed
 * as to the result of a service discovery they have requested.
 * For each match, the callback is fired with all the resulting matches from
 * that source.  If the discovery was unicast to a specific device, then
 * the callback will only be fired once with either MATCH_FOUND or COMPLETE
 * (no matches found).  If the discovery is broadcast then multiple callbacks
 * may be fired with ::EMBER_AF_SERVICE_DISCOVERY_RESPONSE_RECEIVED.  
 * After a couple seconds the callback will then be fired with 
 * ::EMBER_AF_SERVICE_DISCOVERY_COMPLETE as the result.  
 */
typedef void (EmberAfServiceDiscoveryCallback)(const EmberAfServiceDiscoveryResult* result);

/**
 * @brief This defines a callback where a code element or cluster can be
 * informed as to the result of a request to initiate a partner link key
 * exchange.  The callback will be triggered with success equal to TRUE if the
 * exchange completed successfully.
 */
typedef void (EmberAfPartnerLinkKeyExchangeCallback)(boolean success);

/**
 * @brief This is an enum used to control how the device
 *        will sleep for a given active cluster related event.
 *        When the event is scheduled, the scheduling code can
 *        pass a sleep control value which will be stored along
 *        with the event. The processor is only allowed to sleep
 *        according to the most restrictive sleep control value
 *        for any active event. For instance, if two events
 *        are active, one with EMBER_AF_OK_TO_HIBERNATE and the
 *        other with EMBER_AF_OK_TO_NAP, then the processor
 *        will only be allowed to nap until the second event
 *        is deactivated.
 */
typedef enum {
  EMBER_AF_OK_TO_HIBERNATE,
  EMBER_AF_OK_TO_NAP,
  EMBER_AF_STAY_AWAKE
} EmberAfEventSleepControl;

/**
 * @brief a structure used to keep track of cluster related events and
 * their sleep control values. The cluster code will not know at
 * runtime all of the events that it has access to in the event table
 * This structure is stored by the application framework in an event
 * context table which allong with helper functions allows the cluster
 * code to schedule and deactivate its associated events.
 */
typedef struct {
  /**
   * The endpoint of the associated cluster event.
   */
  int8u endpoint;
  /**
   * The cluster id of the associated cluster event.
   */
  int16u clusterId;
  /**
   * The server/client identity of the associated cluster event.
   */
  boolean isClient;
  /**
   * A sleep control value used to control the processor's sleep
   * behavior while the event is active..
   */
  EmberAfEventSleepControl sleepControl;
  /**
   * A pointer to the event control value which is stored in the event table
   * and is used to actually schedule the event.
   */
  EmberEventControl *eventControl;
} EmberAfEventContext;

/**
 * @brief A structure used to reporting configurations.
 */
typedef struct {
  /**
   * TRUE if the entry is in use; otherwise, FALSE.
   */
  boolean inUse;
  /**
   * EMBER_ZCL_REPORTING_DIRECTION_REPORTED for reports sent from the local
   * device or EMBER_ZCL_REPORTING_DIRECTION_RECEIVED for reports received from
   * a remote device.
   */
  EmberAfReportingDirection direction;
  /**
   * The node id of the remote device.  For reported attributes, this is the
   * node that will receive the report from us.  For received attributes, this
   * is the node that will send the report to us.
   */
  EmberNodeId nodeId;
  /**
   * The endpoint on which the reported attribute is located.  For reported
   * attributes, this is the endpoint on the local device.  For received
   * attributes, it is the endpoint on the remote device.
   */
  int8u sourceEndpoint;
  /**
   * The endpoint to which the report attribute is sent.  For reported
   * attributes, this is the endpoint on the remote device.  For received
   * attributes, it is the endpoint on the local device.
   */
  int8u destinationEndpoint;
  /**
   * The cluster where the attribute is located.
   */
  EmberAfClusterId clusterId;
  /**
   * The id of the attribute being reported or received.
   */
  EmberAfAttributeId attributeId;
  /**
   * CLUSTER_MASK_SERVER for server-side attributes or CLUSTER_MASK_CLIENT for
   * client-side attributes.
   */
  int8u mask;
  /**
   * Manufacturer code associated with the cluster and/or attribute.  If the
   * cluster id is inside the manufacturer-specific range, this value indicates
   * the manufacturer code for the cluster.  Otherwise, if this value is non-
   * zero and the cluster id is a standard ZCL cluster, it indicates the
   * manufacturer code for attribute. 
   */
  int16u manufacturerCode;
  /**
   * The minimum reporting interval, measured in seconds.  This field is ignored
   * for received reports.
   */
  int16u minInterval;
  /**
   * The maximum reporting interval, measured in seconds.  This field is ignored
   * for received reports.
   */
  int16u maxInterval;
  /**
   * The elapsed interval in seconds since the last report.  This field is
   * ignored for received reports.
   */
  int16u currentInterval;
  /**
   * The minimum change to the attribute that will result in a report being
   * sent.  This field is ignored for received reports and for discrete data
   * types.
   */
  int32u reportableChange;
  /**
   * The value of the attribute that was sent in the last report.  This field is
   * ignored for received reports.
   */
  int32u lastReportValue;
  /**
   * The maximum expected time between reports.  This field is ignored for
   * reported reports.
   */
  int16u timeout;
  /**
   * The number of times that reporting this attribute has failed.  This field
   * is ignored for received reports.
   */
  int8u failCount;
} EmberAfReportEntry;

#ifdef EMBER_AF_PLUGIN_GROUPS_SERVER
/**
 * @brief Indicates the absence of a Group table entry.
 */
#define EMBER_AF_GROUP_TABLE_NULL_INDEX 0xFF
/**
 * @brief Value used when setting or getting the endpoint in a Group table
 * entry.  It indicates that the entry is not in use.
 */
#define EMBER_AF_GROUP_TABLE_UNUSED_ENDPOINT_ID 0x00
/**
 * @brief Maximum length of Group names, not including the length byte.
 */
#define ZCL_GROUPS_CLUSTER_MAXIMUM_NAME_LENGTH 16
/**
 * @brief A structure used to store group table entries in RAM or in tokens,
 * depending on the the platform.  If the endpoint field is
 * ::EMBER_AF_GROUP_TABLE_UNUSED_ENDPOINT_ID, the entry is unused.
 */
typedef struct {
  int8u  endpoint; // 0x00 when not in use
  int16u groupId;
  int8u  bindingIndex;
#ifdef EMBER_AF_PLUGIN_GROUPS_SERVER_NAME_SUPPORT
  int8u  name[ZCL_GROUPS_CLUSTER_MAXIMUM_NAME_LENGTH + 1];
#endif
} EmberAfGroupTableEntry;
#endif //EMBER_AF_PLUGIN_GROUPS_SERVER

/**
 * @brief Indicates the absence of a Scene table entry.
 */
#define EMBER_AF_SCENE_TABLE_NULL_INDEX 0xFF
/**
 * @brief Value used when setting or getting the endpoint in a Scene table
 * entry.  It indicates that the entry is not in use.
 */
#define EMBER_AF_SCENE_TABLE_UNUSED_ENDPOINT_ID 0x00
/**
 * @brief Maximum length of Scene names, not including the length byte.
 */
#define ZCL_SCENES_CLUSTER_MAXIMUM_NAME_LENGTH 16
/**
 * @brief The group identifier for the global scene.
 */
#define ZCL_SCENES_GLOBAL_SCENE_GROUP_ID 0x0000
/**
 * @brief A structure used to store scene table entries in RAM or in tokens,
 * depending on a plugin setting.  If endpoint field is
 * ::EMBER_AF_SCENE_TABLE_UNUSED_ENDPOINT_ID, the entry is unused.
 */
typedef struct {
  int8u   endpoint;                // 0x00 when this record is not in use
  int16u  groupId;                 // 0x0000 if not associated with a group
  int8u   sceneId;
#ifdef EMBER_AF_PLUGIN_SCENES_NAME_SUPPORT
  int8u   name[ZCL_SCENES_CLUSTER_MAXIMUM_NAME_LENGTH + 1];
#endif
  int16u  transitionTime;          // in seconds
#ifdef ZCL_USING_ON_OFF_CLUSTER_SERVER
  boolean hasOnOffValue;
  boolean onOffValue;
#endif
#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
  boolean hasCurrentLevelValue;
  int8u   currentLevelValue;
#endif
#ifdef ZCL_USING_THERMOSTAT_CLUSTER_SERVER
  boolean hasOccupiedCoolingSetpointValue;
  int16s  occupiedCoolingSetpointValue;
  boolean hasOccupiedHeatingSetpointValue;
  int16s  occupiedHeatingSetpointValue;
  boolean hasSystemModeValue;
  int8u   systemModeValue;
#endif
#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER
  boolean hasCurrentXValue;
  int16u  currentXValue;
  boolean hasCurrentYValue;
  int16u  currentYValue;
#endif
#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_SERVER
  boolean hasLockStateValue;
  int8u   lockStateValue;
#endif
#ifdef ZCL_USING_WINDOW_COVERING_CLUSTER_SERVER
  boolean hasCurrentPositionLiftPercentageValue;
  int8u   currentPositionLiftPercentageValue;
  boolean hasCurrentPositionTiltPercentageValue;
  int8u   currentPositionTiltPercentageValue;
#endif
} EmberAfSceneTableEntry;

#ifdef EMBER_AF_PLUGIN_MESSAGING_CLIENT
typedef struct {
  boolean    valid;
  boolean    active;
  EmberEUI64 server;
  int8u      serverEndpoint;
  int8u      clientEndpoint;
  int32u     messageId;
  int8u      messageControl;
  int32u     startTime;
  int32u     endTime;
  int16u     durationInMinutes;
  int8u      message[EMBER_AF_PLUGIN_MESSAGING_CLIENT_MESSAGE_SIZE + 1];
} EmberAfPluginMessagingClientMessage;
#endif //EMBER_AF_PLUGIN_MESSAGING_CLIENT

#define ZCL_PRICE_CLUSTER_MAXIMUM_RATE_LABEL_LENGTH 11
#ifdef EMBER_AF_PLUGIN_PRICE_CLIENT
typedef struct {
  boolean valid;
  boolean active;
  int32u  providerId;
  int8u   rateLabel[ZCL_PRICE_CLUSTER_MAXIMUM_RATE_LABEL_LENGTH + 1];
  int32u  issuerEventId;
  int32u  currentTime;
  int8u   unitOfMeasure;
  int16u  currency;
  int8u   priceTrailingDigitAndPriceTier;
  int8u   numberOfPriceTiersAndRegisterTier;
  int32u  startTime;
  int32u  endTime;
  int16u  durationInMinutes;
  int32u  price;
  int8u   priceRatio;
  int32u  generationPrice;
  int8u   generationPriceRatio;
  int32u  alternateCostDelivered;
  int8u   alternateCostUnit;
  int8u   alternateCostTrailingDigit;
  int8u   numberOfBlockThresholds;
  int8u   priceControl;
} EmberAfPluginPriceClientPrice;
#endif //EMBER_AF_PLUGIN_PRICE_CLIENT

#ifdef EMBER_AF_PLUGIN_PSL_COMMISSIONING
typedef struct {
  EmberMulticastId groupId;
  int8u            groupType;
} EmberAfPluginPslCommissioningGroupInformationRecord;

typedef struct {
  EmberNodeId networkAddress;
  int8u       endpointId;
  int16u      profileId;
  int16u      deviceId;
  int8u       version;
} EmberAfPluginPslCommissioningEndpointInformationRecord;
#endif

/**
 * @brief This is a unique identifier for referencing ZigBee Over-the-air upgrade
 *   images.  It is used by the OTA plugins when passing around information about
 *   an upgrade file.
 */
typedef struct {
  int16u manufacturerId;
  int16u imageTypeId;
  int32u firmwareVersion;

  /**
   * This is only used for device specific files.
   * It will be set to all 0's when the image does not
   * have an upgrade destination field in it.
   * Little endian format.
   */
  int8u deviceSpecificFileEui64[EUI64_SIZE];         
} EmberAfOtaImageId;

/**
 * @brief This status contains the success or error code of an OTA storage
 *   device operation.
 */
typedef enum {
  EMBER_AF_OTA_STORAGE_SUCCESS              = 0,
  EMBER_AF_OTA_STORAGE_ERROR                = 1,
  EMBER_AF_OTA_STORAGE_RETURN_DATA_TOO_LONG = 2,
  EMBER_AF_OTA_STORAGE_PARTIAL_FILE_FOUND   = 3,
} EmberAfOtaStorageStatus;

/**
 * @brief The maximum size of the string that is present in the header
 *   of the ZigBee Over-the-air file format.
 */
#define EMBER_AF_OTA_MAX_HEADER_STRING_LENGTH 32

/**
 * @brief This structure is an in-memory representation of
 *   the Over-the-air header data that resides on disk.
 *   It is not a byte-for-byte copy.
 */
typedef struct {
  // Magic Number omitted since it is always the same.
  int16u headerVersion;
  int16u headerLength;
  int16u fieldControl;
  int16u manufacturerId;
  int16u imageTypeId;           // a.k.a. Device ID
  int32u firmwareVersion;
  int16u zigbeeStackVersion;

  /**
   * @brief The spec. does NOT require that the string be NULL terminated in the 
   *   header stored on disk.  Therefore we make sure we can support a 
   *   32-character string without a NULL terminator by adding +1 in the data
   *   structure.
   */
  int8u headerString[EMBER_AF_OTA_MAX_HEADER_STRING_LENGTH + 1];  

  /** 
   * @brief When reading the header this will be the complete length of 
   *  the file. When writing the header, this must be set to 
   *  the length of the MFG image data portion including all tags.
   */
  int32u imageSize;

  /** 
   * @brief The remaining four fields are optional. The field control should be checked
   *   to determine if their values are valid.
   */
  int8u securityCredentials;
  int8u upgradeFileDestination[EUI64_SIZE];
  int16u minimumHardwareVersion;
  int16u maximumHardwareVersion;
} EmberAfOtaHeader;

/**
 * @brief This structure contains information about a tag that resides
 *   within an Over-the-air bootload file.
 */
typedef struct {
  int16u id;
  int32u length;
} EmberAfTagData;

typedef enum {
  NO_APP_MESSAGE               = 0,
  RECEIVED_PARTNER_CERTIFICATE = 1,
  GENERATING_EPHEMERAL_KEYS    = 2,
  GENERATING_SHARED_SECRET     = 3,
  KEY_GENERATION_DONE          = 4,
  GENERATE_SHARED_SECRET_DONE  = 5,
  /**
   * LINK_KEY_ESTABLISHED indicates Success,
   * key establishment done.
   */
  LINK_KEY_ESTABLISHED         = 6,  


  /**
   * Error codes:
   * Transient failures where Key Establishment could be retried
   */
  NO_LOCAL_RESOURCES          = 7,
  PARTNER_NO_RESOURCES        = 8,
  TIMEOUT_OCCURRED            = 9,
  INVALID_APP_COMMAND         = 10,
  MESSAGE_SEND_FAILURE        = 11, 
  PARTNER_SENT_TERMINATE      = 12,
  INVALID_PARTNER_MESSAGE     = 13,
  PARTNER_SENT_DEFAULT_RESPONSE_ERROR = 14,

  /** 
   * Fatal Errors:
   * These results are not worh retrying because the outcome
   * will not change
   */
  BAD_CERTIFICATE_ISSUER      = 15,
  KEY_CONFIRM_FAILURE         = 16,
  BAD_KEY_ESTABLISHMENT_SUITE = 17,

  KEY_TABLE_FULL              = 18,

  /**
   * Neither initiator nor responder is an
   * ESP/TC so the key establishment is not
   * allowed per the spec.
   */
  NO_ESTABLISHMENT_ALLOWED    = 19, 
} EmberAfKeyEstablishmentNotifyMessage;

#define APP_NOTIFY_ERROR_CODE_START NO_LOCAL_RESOURCES
#define APP_NOTIFY_MESSAGE_TEXT { \
  "None",                         \
  "Received Cert",                \
  "Generate keys",                \
  "Generate secret",              \
  "Key generate done",            \
  "Generate secret done",         \
  "Link key verified",            \
                                  \
  /* Transient Error codes */     \
  "No local resources",           \
  "Partner no resources",         \
  "Timeout",                      \
  "Invalid app. command",         \
  "Message send failure",         \
  "Partner sent terminate",       \
  "Bad message",                  \
  "Partner sent Default Rsp",     \
                                  \
  /* Fatal errors */              \
  "Bad cert issuer",              \
  "Key confirm failure",          \
  "Bad key est. suite",           \
  "Key table full",               \
  "Not allowed",                  \
}

/**
 * @brief This enumeration is used to indicate the state of an OTA bootload
 *   image undergoing verification.  This is used both for cryptographic
 *   verification and manufacturer specific verification.
 */
typedef enum {
  EMBER_AF_IMAGE_GOOD                 = 0,
  EMBER_AF_IMAGE_BAD                  = 1,
  EMBER_AF_IMAGE_VERIFY_IN_PROGRESS   = 2,

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  // Internal use only.
  EMBER_AF_IMAGE_VERIFY_WAIT          = 3,
  EMBER_AF_IMAGE_VERIFY_ERROR         = 4,
  EMBER_AF_IMAGE_UNKNOWN              = 5,
  EMBER_AF_NO_IMAGE_VERIFY_SUPPORT    = 6,
#endif
} EmberAfImageVerifyStatus;

/**
 * @brief Type for refering to the tick callback for cluster.
 *
 * Tick function will be called once for each tick for each endpoint in
 * the cluster. The rate of tick is determined by the metadata of the
 * cluster.
 */
typedef void (*EmberAfTickFunction)(int8u endpoint);


/**
 * @brief Type for refering to the init callback for cluster.
 *
 * Init function is called when the application starts up, once for
 * each cluster/endpoint combination.
 */
typedef void (*EmberAfInitFunction)(int8u endpoint);

/**
 * @brief Type for refering to the attribute changed callback function.
 *
 * This function is called just after an attribute changes.
 */
typedef void (*EmberAfClusterAttributeChangedCallback)(int8u endpoint,
                                                       EmberAfAttributeId attributeId);

/**
 * @brief Type for refering to the manufacturer specific 
 *        attribute changed callback function.
 *
 * This function is called just after a manufacturer specific attribute changes.
 */
typedef void (*EmberAfManufacturerSpecificClusterAttributeChangedCallback)(int8u endpoint,
                                                       EmberAfAttributeId attributeId,
                                                       int16u manufacturerCode);


/**
 * @brief Type for refering to the default response callback function.
 *
 * This function is called when default response is received, before
 * the global callback. Global callback is called immediatelly afterwards.
 */
typedef void (*EmberAfDefaultResponseFunction)(int8u endpoint,
                                               int8u commandId,
                                               EmberAfStatus status);

/**
 * @brief Type for refering to the message sent callback function.
 *
 * This function is called when a message is sent.
 */
typedef void (*EmberAfMessageSentFunction)(EmberOutgoingMessageType type,
                                           int16u indexOrDestination,
                                           EmberApsFrame *apsFrame,
                                           int16u msgLen,
                                           int8u *message,
                                           EmberStatus status);

#endif // __AF_API_TYPES__
