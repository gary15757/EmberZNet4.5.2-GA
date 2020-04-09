/**
 * @file af.h
 * @brief The master include file for the Ember ApplicationFramework  API.
 *
 * <!-- Author(s): Ezra Hale, ezra@ember.com,        -->
 * <!--            Timotej Ecimovic, timotej@ember.com -->
 *
 * <!--Copyright 2004-2010 by Ember Corporation. All rights reserved.    *80*-->
 */

/**
 * @addtogroup af Application Framework V2 API Reference
 * This documentation describes the application programming interface (API)
 * for the Ember Application Framework V2.
 * The file af.h is the master include file for the Application Framework V2 modules.
 * @{
 */


#ifndef __AF_API__
#define __AF_API__

#ifndef CONFIGURATION_HEADER
  #define CONFIGURATION_HEADER "app/framework/util/config.h"
#endif
#include CONFIGURATION_HEADER

// Micro and compiler specific typedefs and macros
#include PLATFORM_HEADER

#ifdef EZSP_HOST
  // Includes needed for ember related functions for the EZSP host
  #include "stack/include/error.h"
  #include "stack/include/ember-types.h"
  #include "app/util/ezsp/ezsp-protocol.h"
  #include "app/util/ezsp/ezsp.h"
  #include "app/util/ezsp/ezsp-utils.h"
  #include "app/util/ezsp/serial-interface.h"
#else
  // Includes needed for ember related functions for the EM250
  #include "stack/include/ember.h"
#endif // EZSP_HOST

// HAL - hardware abstraction layer
#include "hal/hal.h" 
#include "app/util/serial/serial.h"  // Serial utility APIs

#include "stack/include/event.h"
#include "stack/include/error.h"
#include "af-types.h"
#include "app/framework/util/print.h"
#include "app/framework/gen/af-structs.h"
#include "app/framework/gen/attribute-id.h"
#include "app/framework/gen/attribute-storage.h"
#include "app/framework/gen/attribute-type.h"
#include "app/framework/gen/call-command-handler.h"
#include "app/framework/gen/callback.h"
#include "app/framework/gen/client-command-macro.h"
#include "app/framework/gen/cluster-id.h"
#include "app/framework/gen/command-id.h"
#include "app/framework/gen/debug-printing.h"
#include "app/framework/gen/enums.h"
#include "app/framework/gen/print-cluster.h"
#include "app/framework/gen/stack-handlers.h"
#include "app/framework/util/client-api.h"


/** @name Attribute Storage */
// @{

/**
 * @brief locate attribute metadata
 *
 * Function returns pointer to the attribute metadata structure,
 * or NULL if attribute was not found.
 *
 * @param endpoint Zigbee endpoint number.
 * @param cluster Cluster ID of the sought cluster.
 * @param attribute Attribute ID of the sought attribute.
 * @param mask CLUSTER_MASK_SERVER or CLUSTER_MASK_CLIENT
 *
 * @return Returns pointer to the attribute metadata location.
 */
EmberAfAttributeMetadata *emberAfLocateAttributeMetadata(int8u endpoint,
                                                         EmberAfClusterId cluster,
                                                         EmberAfAttributeId attribute,
                                                         int8u mask,
                                                         int16u manufacturerCode);

/**
 * @brief Returns TRUE If endpoint contains cluster.
 *
 * This function returns true regardless of whether
 * the endpoint contains server, client or both.
 */
boolean emberAfContainsCluster(int8u endpoint, EmberAfClusterId clusterId);

/**
 * @brief Returns TRUE If endpoint contains cluster server.
 *
 * This function returns true if
 * the endpoint contains server of a given cluster.
 */
boolean emberAfContainsServer(int8u endpoint, EmberAfClusterId clusterId);

/**
 * @brief Returns TRUE If endpoint contains cluster client.
 *
 * This function returns true if
 * the endpoint contains client of a given cluster.
 */
boolean emberAfContainsClient(int8u endpoint, EmberAfClusterId clusterId);


/**
 * @brief Main function for manipulating attributes.
 *
 * This function locates the attribute and returns true upon succes
 * and false if attribute was not found.
 * if metadata is non-NULL, then it is populated.
 * if buffer is non-NULL, then it is populated with attribute data.
 *
 * Note, that this function DOES NOT perform any read-only or type
 * checking. This is just a low-level interface to the attribute table,
 * and it is up to the called to ensure permissions and type checking.
 *
 * Use other attribute functions for higher-level access to attribute
 * table.
 *
 * @param *attRecord Pointer to an instance of EmberAfAttributeSearchRecord
 *   which contains everything needed to find the unique attribute requested
 *   in memory.
 * @param metadata Location where the attribute metadata pointer will
 *   be copied into. It can be NULL, in which case metadata pointer
 *   is not retrieved.
 * @param buffer Location where attribute will be written into or
 *   read from, depending if this is read or write operation. If it is
 *   NULL, then it will not be used, and data can't be read or written.
 * @param write If it is TRUE, then this is write operation, otherwise
 *   it is a read operation.
 *
 * @return TRUE if operation was succesfull, FALSE otherwise.
 */
boolean emberAfReadOrUpdateAttribute(EmberAfAttributeSearchRecord *attRecord,
                                     EmberAfAttributeMetadata **metadata,
                                     int8u *buffer,
                                     boolean write);



/**
 * @brief write an attribute, performing all the checks.
 *
 * This function will attempt to write the attribute value from
 * the provided pointer. This function will only check that the
 * attribute exists. If it does it will write the value into
 * the attribute table for the given attribute.
 *
 * This funciton will not check to see if the attribute is
 * writable since the read only / writable characteristic
 * of an attribute only pertains to external devices writing
 * over the air. Because this function is being called locally
 * it assumes that the device knows what it is doing and has permission
 * to perform the given operation.
 *
 * @see emberAfWriteClientAttribute, emberAfWriteServerAttribute, 
 *      emberAfWriteManufacturerSpecificClientAttribute, 
 *      emberAfWriteManufacturerSpecificServerAttribute
 */
EmberAfStatus emberAfWriteAttribute(int8u endpoint,
                                    EmberAfClusterId cluster,
                                    EmberAfAttributeId attributeID,
                                    int8u mask,
                                    int8u* dataPtr,
                                    int8u dataType);

/**
 * @brief write a cluster server attribute.
 *
 * This function is the same as emberAfWriteAttribute
 * except that it saves having to pass the cluster mask.
 * this is useful for code savings since write attribute
 * is used frequently throughout the framework
 *
 * @see emberAfWriteClientAttribute, 
 *      emberAfWriteManufacturerSpecificClientAttribute, 
 *      emberAfWriteManufacturerSpecificServerAttribute
 */
EmberAfStatus emberAfWriteServerAttribute(int8u endpoint,
                                          EmberAfClusterId cluster,
                                          EmberAfAttributeId attributeID,
                                          int8u* dataPtr,
                                          int8u dataType);

/**
 * @brief write an cluster client attribute.
 *
 * This function is the same as emberAfWriteAttribute
 * except that it saves having to pass the cluster mask.
 * this is useful for code savings since write attribute
 * is used frequently throughout the framework
 *
 * @see emberAfWriteServerAttribute, 
 *      emberAfWriteManufacturerSpecificClientAttribute, 
 *      emberAfWriteManufacturerSpecificServerAttribute
 */
EmberAfStatus emberAfWriteClientAttribute(int8u endpoint,
                                          EmberAfClusterId cluster,
                                          EmberAfAttributeId attributeID,
                                          int8u* dataPtr,
                                          int8u dataType);

/**
 * @brief write an manufacturer specific server attribute.
 *
 * This function is the same as emberAfWriteAttribute
 * except that it saves having to pass the cluster mask.
 * this is useful for code savings since write attribute
 * is used frequently throughout the framework
 *
 * @see emberAfWriteClientAttribute, emberAfWriteServerAttribute, 
 *      emberAfWriteManufacturerSpecificClientAttribute 
 */
EmberAfStatus emberAfWriteManufacturerSpecificServerAttribute(int8u endpoint,
                                                              EmberAfClusterId cluster,
                                                              EmberAfAttributeId attributeID,
                                                              int16u manufacturerCode,
                                                              int8u* dataPtr,
                                                              int8u dataType);

/**
 * @brief write an manufacturer specific client attribute.
 *
 * This function is the same as emberAfWriteAttribute
 * except that it saves having to pass the cluster mask.
 * this is useful for code savings since write attribute
 * is used frequently throughout the framework
 *
 * @see emberAfWriteClientAttribute, emberAfWriteServerAttribute, 
 *      emberAfWriteManufacturerSpecificServerAttribute
 */
EmberAfStatus emberAfWriteManufacturerSpecificClientAttribute(int8u endpoint,
                                                              EmberAfClusterId cluster,
                                                              EmberAfAttributeId attributeID,
                                                              int16u manufacturerCode,
                                                              int8u* dataPtr,
                                                              int8u dataType);


/**
 * @brief Function that test the success of attribute write.
 *
 * This function returns success if attribute write would be succesfull.
 * It does not actuall write anything, just validates for read-only and
 * data-type.
 *
 * @param endpoint Zigbee endpoint number
 * @param cluster Cluster ID of the sought cluster.
 * @param attribute Attribute ID of the sought attribute.
 * @param mask CLUSTER_MASK_SERVER or CLUSTER_MASK_CLIENT
 * @param buffer Location where attribute will be written from.
 * @param dataType ZCL attribute type.
 */
EmberAfStatus emberAfVerifyAttributeWrite(int8u endpoint,
                                          EmberAfClusterId cluster,
                                          EmberAfAttributeId attributeID,
                                          int8u mask,
                                          int16u manufacturerCode,
                                          int8u* buffer,
                                          int8u dataType);

/**
 * @brief Read the attribute value, performing all the checks.
 *
 * This function will attempt to read the attribute and store
 * it into the pointer. It will also read the data type.
 * Both dataPtr and dataType may be NULL, signifying that either
 * value or type is not desired.
 *
 * @see emberAfReadClientAttribute, emberAfReadServerAttribute, 
 *      emberAfReadManufacturerSpecificClientAttribute, 
 *      emberAfReadManufacturerSpecificServerAttribute
 */
EmberAfStatus emberAfReadAttribute(int8u endpoint,
                                   EmberAfClusterId cluster,
                                   EmberAfAttributeId attributeID,
                                   int8u mask,
                                   int8u* dataPtr,
                                   int8u maxLength,
                                   int8u* dataType);

/**
 * @brief Read the server attribute value, performing all the checks.
 *
 * This function will attempt to read the attribute and store
 * it into the pointer. It will also read the data type.
 * Both dataPtr and dataType may be NULL, signifying that either
 * value or type is not desired.
 *
 * @see emberAfReadClientAttribute, 
 *      emberAfReadManufacturerSpecificClientAttribute, 
 *      emberAfReadManufacturerSpecificServerAttribute
 */
EmberAfStatus emberAfReadServerAttribute(int8u endpoint,
                                         EmberAfClusterId cluster,
                                         EmberAfAttributeId attributeID,
                                         int8u* dataPtr,
                                         int8u maxLength);

/**
 * @brief Read the attribute value, performing all the checks.
 *
 * This function will attempt to read the attribute and store
 * it into the pointer. It will also read the data type.
 * Both dataPtr and dataType may be NULL, signifying that either
 * value or type is not desired.
 *
 * @see emberAfReadServerAttribute, 
 *      emberAfReadManufacturerSpecificClientAttribute, 
 *      emberAfReadManufacturerSpecificServerAttribute
 */
EmberAfStatus emberAfReadClientAttribute(int8u endpoint,
                                         EmberAfClusterId cluster,
                                         EmberAfAttributeId attributeID,
                                         int8u* dataPtr,
                                         int8u maxLength);

/**
 * @brief Read the server attribute value, performing all the checks.
 *
 * This function will attempt to read the attribute and store
 * it into the pointer. It will also read the data type.
 * Both dataPtr and dataType may be NULL, signifying that either
 * value or type is not desired.
 *
 * @see emberAfReadClientAttribute, emberAfReadServerAttribute, 
 *      emberAfReadManufacturerSpecificClientAttribute
 */
EmberAfStatus emberAfReadManufacturerSpecificServerAttribute(int8u endpoint,
                                                             EmberAfClusterId cluster,
                                                             EmberAfAttributeId attributeID,
                                                             int16u manufacturerCode,
                                                             int8u* dataPtr,
                                                             int8u maxLength);

/**
 * @brief Read the attribute value, performing all the checks.
 *
 * This function will attempt to read the attribute and store
 * it into the pointer. It will also read the data type.
 * Both dataPtr and dataType may be NULL, signifying that either
 * value or type is not desired.
 *
 * @see emberAfReadClientAttribute, emberAfReadServerAttribute, 
 *      emberAfReadManufacturerSpecificServerAttribute
 */
EmberAfStatus emberAfReadManufacturerSpecificClientAttribute(int8u endpoint,
                                                             EmberAfClusterId cluster,
                                                             EmberAfAttributeId attributeID,
                                                             int16u manufacturerCode,
                                                             int8u* dataPtr,
                                                             int8u maxLength);


/**
 * @brief this function returns the size of the ZCL data in bytes.
 *
 * @param dataType Zcl data type
 * @return size in bytes or 0 if invalid data type
 */
int8u emberAfGetDataSize(int8u dataType);

/**
 * @brief macro that returns true if the cluster is in the manufacturer specific range
 *
 * @param cluster EmberAfCluster* to consider
 */
#define emberAfClusterIsManufacturerSpecific(cluster) ((cluster)->clusterId >= 0xFC00)


/**
 * @brief macro that returns true if attribute is read only.
 *
 * @param metadata EmberAfAttributeMetadata* to consider.
 */
#define emberAfAttributeIsReadOnly(metadata) (((metadata)->mask & ATTRIBUTE_MASK_WRITABLE) == 0)

/**
 * @brief macro that returns true if this is a client attribute, and false if it is server
 *
 * @param metadata EmberAfAttributeMetadata* to consider.
 */
#define emberAfAttributeIsClient(metadata) (((metadata)->mask & ATTRIBUTE_MASK_CLIENT) != 0)

/**
 * @brief macro that returns true if attribute is saved to token.
 *
 * @param metadata EmberAfAttributeMetadata* to consider.
 */
#define emberAfAttributeIsTokenized(metadata) (((metadata)->mask & ATTRIBUTE_MASK_TOKENIZE) != 0)

/**
 * @brief macro that returns true if attribute is a singleton
 *
 * @param metadata EmberAfAttributeMetadata* to consider.
 */
#define emberAfAttributeIsSingleton(metadata) (((metadata)->mask & ATTRIBUTE_MASK_SINGLETON) != 0)

/**
 * @brief macro that returns true if attribute is manufacturer specific
 *
 * @param metadata EmberAfAttributeMetadata* to consider.
 */
#define emberAfAttributeIsManufacturerSpecific(metadata) (((metadata)->mask & ATTRIBUTE_MASK_MANUFACTURER_SPECIFIC) != 0)


/**
 * @brief macro that returns size of attribute in bytes.
 *
 * @param metadata EmberAfAttributeMetadata* to consider.
 */
#define emberAfAttributeSize(metadata) ((metadata)->size)

// master array of all defined endpoints
extern EmberAfDefinedEndpoint endpoints[];

/**
 * @brief Macro that takes index of endpoint, and returns Zigbee endpoint
 */
#define emberAfEndpointFromIndex(index) (endpoints[(index)].endpoint)

/**
 * Returns the index of a given endpoint
 */
int8u emberAfIndexFromEndpoint(int8u endpoint);

/**
 * @brief Macro that takes index of endpoint, and returns profile Id for it
 */
#define emberAfProfileIdFromIndex(index) (endpoints[(index)].profileId)

/**
 * @brief Macro that takes index of endpoint, and returns device Id for it
 */
#define emberAfDeviceIdFromIndex(index) (endpoints[(index)].deviceId)

/**
 * @brief Macro that takes index of endpoint, and returns device version for it
 */
#define emberAfDeviceVersionFromIndex(index) (endpoints[(index)].deviceVersion)

/**
 * @brief Macro that returns primary profile ID.
 *
 * Primary profile is the profile of a primary endpoint as defined
 * in the appbuilder.
 */
#define emberAfPrimaryProfileId()       emberAfProfileIdFromIndex(0)

/**
 * @brief Macro that returns the primary endpoint.
 */
#define emberAfPrimaryEndpoint() (endpoints[0].endpoint)


/**
 * @brief Returns the number of endpoints.
 */
int8u emberAfEndpointCount(void);

/**
 * Data types are either analog or discrete. This makes a difference for
 * some of the ZCL global commands
 */
enum {
  EMBER_AF_DATA_TYPE_ANALOG     = 0,
  EMBER_AF_DATA_TYPE_DISCRETE   = 1,
  EMBER_AF_DATA_TYPE_NONE       = 2
};
/**
 * @brief Returns the type of the attribute, either ANALOG, DISCRETE or NONE
 */
int8u emberAfGetAttributeAnalogOrDiscreteType(int8u dataType);

/**
 *@brief Returns true if type is signed, false otherwise.
 */
boolean emberAfIsTypeSigned(int8u dataType);

/**
 * @brief Function that extracts a 32-bit integer from the message buffer
 */
int32u emberAfGetInt32u(const int8u* message, int16u currentIndex, int16u msgLen);

/**
 * @brief Function that extracts a 24-bit integer from the message buffer
 */
int32u emberAfGetInt24u(const int8u* message, int16u currentIndex, int16u msgLen);

/**
 * @brief Function that extracts a 16-bit integer from the message buffer
 */
int16u emberAfGetInt16u(const int8u* message, int16u currentIndex, int16u msgLen);
/**
 * @brief Function that extracts a ZCL string from the message buffer
 */
int8u* emberAfGetString(int8u* message, int16u currentIndex, int16u msgLen);

/**
 * @brief Macro for consistency, that extracts single byte out of the message
 */
#define emberAfGetInt8u(message, currentIndex, msgLen) message[currentIndex]

/**
 * @brief Macro for consistency that copies an int8u from variable into buffer.
 */
#define emberAfCopyInt8u(data,index,x) (data[index] = (x))
/**
 * @brief function that copies an in16u value into a buffer
 */
void emberAfCopyInt16u(int8u *data, int16u index, int16u x);
/**
 * @brief function that copies an in24u value into a buffer
 */
void emberAfCopyInt24u(int8u *data, int16u index, int32u x);
/**
 * @brief function that copies an in32u value into a buffer
 */
void emberAfCopyInt32u(int8u *data, int16u index, int32u x);
/*
 * @brief Function that copies a ZigBee string into a buffer.  The size
 * parameter should indicate the maximum number of characters to copy to the
 * destination buffer not including the length byte.
 */
void emberAfCopyString(int8u *dest, int8u *src, int8u size);
/*
 * @brief Function that determines the length of a ZigBee string.
 */
int8u emberAfStringLength(const int8u *buffer);

/** @} END Attribute Storage */

/** @name Device Control */
// @{

/**
 * @brief Function that checks if endpoint is enabled.
 *
 * This function returns true if device at a given endpoint is
 * enabled. At startup all endpoints are enabled.
 *
 * @param endpoint Zigbee endpoint number
 */
boolean emberAfIsDeviceEnabled(int8u endpoint);

/**
 * @brief Function that enables or disables an endpoint.
 *
 * By calling this function, you turn off all processing of incoming traffic
 * for a given endpoint.
 *
 * @param endpoint Zigbee endpoint number
 */
void emberAfSetDeviceEnabled(int8u endpoint, boolean enabled);

/** @} END Device Control */

/** @name Miscellaneous */
// @{


/**
 * @brief This indicates a new image verification is taking place.
 */
#define EMBER_AF_NEW_IMAGE_VERIFICATION TRUE

/**
 * @brief This indicates the continuation of an image verification already 
 * in progress.
 */
#define EMBER_AF_CONTINUE_IMAGE_VERIFY  FALSE


/**
 * @brief This variable defines an invalid image id.  It is used
 *   to determine if a returned EmberAfOtaImageId is valid or not.
 *   This is done by passing the data to the function
 *   emberAfIsOtaImageIdValid().
 */
extern PGM EmberAfOtaImageId emberAfInvalidImageId;


/**
 * @brief Returns true if a given ZCL data type is a string type.
 *
 * You should use this function if you need to perform a different
 * memory operation on a certain attribute because it is a string type.
 * Since ZCL strings carry length as the first byte, it is often required
 * to treat them differently than regular data types.
 *
 * @return true if data type is a string.
 */
boolean emberAfIsThisDataTypeAStringType(int8u dataType);

/**
 * @brief Returns a next sequence number for the outgoing ZCL message.
 *
 * Whenever sending ZCL messages you need a sequence. This function gives one.
 *
 * @return Next usable sequence number.
 */
int8u emberAfNextSequence(void);

/**
 * @brief Simple integer comparison function.
 * Compares two values of a known length as integers.
 * The integers are in native endianess.
 *
 * @return -1 if val1 is smaller, 0 if they are the same or 1 if val2 is smaller.
 */
int8s emberAfCompareValues(int8u* val1, int8u* val2, int8u len);

/**
 * @brief populates the eui64 with the local eui64.
 */
void emberAfGetEui64(EmberEUI64 returnEui64);

/**
 * @brief Returns the node ID of the local node.
 */
EmberNodeId emberAfGetNodeId(void);

/** @} END Miscellaneous */

/** @name Printing */
// @{

// Guaranteed print
/**
 * @brief Print that can't be turned off.
 *
 */
#define emberAfGuaranteedPrint(...)   emberAfPrint(0xFFFF, __VA_ARGS__)

/**
 * @brief Println that can't be turned off.
 */
#define emberAfGuaranteedPrintln(...) emberAfPrintln(0xFFFF, __VA_ARGS__)

/**
 * @brief Buffer print that can't be turned off.
 */
#define emberAfGuaranteedPrintBuffer(buffer,len,withSpace) emberAfPrintBuffer(0xFFFF,(buffer),(len),(withSpace))

/**
 * @brief String print that can't be turned off.
 */
#define emberAfGuaranteedPrintString(buffer) emberAfPrintString(0xFFFF,(buffer))

/**
 * @brief Buffer flush for emberAfGuaranteedPrint(), emberAfGuaranteedPrintln(),
 * emberAfGuaranteedPrintBuffer(), and emberAfGuaranteedPrintString().
 */
#define emberAfGuaranteedFlush()      emberAfFlush(0xFFFF)

/**
 * @brief returns true if certain debug area is enabled.
 */
boolean emberAfPrintEnabled(int16u functionality);

/**
 * @brief Useful function to print a buffer
 */
void emberAfPrintBuffer(int16u area, const int8u *buffer, int16u bufferLen, boolean withSpaces);

/**
 * @brief Useful function to print characters strings.  The first byte of the
 * buffer specifies the length of the string.
 */
void emberAfPrintString(int16u area, const int8u *buffer);

/**
 * @brief prints the specified text if certain debug are is enabled
 * @param functionality: one of the EMBER_AF_PRINT_xxx macros as defined by appbuilder
 * @param formatString: formatString for varargs
 */
void emberAfPrint(int16u functionality, PGM_P formatString, ...);

/**
 * @brief prints the specified text if certain debug are is enabled.
 * Print-out will include the newline character at the end.
 * @param functionality: one of the EMBER_AF_PRINT_xxx macros as defined by appbuilder
 * @param formatString: formatString for varargs
 */
void emberAfPrintln(int16u functionality, PGM_P formatString, ...);

/**
 * @brief buffer flush
 */
void emberAfFlush(int16u functionality);

/**
 * @brief turns on debugging for certain functional area
 */
void emberAfPrintOn(int16u functionality);

/**
 * @brief turns off debugging for certain functional area
 */
void emberAfPrintOff(int16u functionality);

/** @brief turns on debugging for all functional areas
 */
void emberAfPrintAllOn(void);

/**
 * @brief turns off debugging for all functional areas
 */
void emberAfPrintAllOff(void);

/**
 * @brief prints current status of functional areas
 */
void emberAfPrintStatus(void);

/**
 * @brief prints eui64 stored in little endian format
 */
void emberAfPrintLittleEndianEui64(const EmberEUI64 eui64);


/**
 * @brief prints eui64 stored in big endian format
 */
void emberAfPrintBigEndianEui64(const EmberEUI64 eui64);

/**
 * @brief prints all message data in message format
 */
void emberAfPrintMessageData(int8u* data, int16u length);


/** @} END Printing */



/** @name Hibernation */
//@{
#define MILLISECOND_TICKS_PER_QUARTERSECOND (MILLISECOND_TICKS_PER_SECOND >> 2)
#define MILLISECOND_TICKS_PER_MINUTE (60L * MILLISECOND_TICKS_PER_SECOND)
#define MILLISECOND_TICKS_PER_HOUR   (60L * MILLISECOND_TICKS_PER_MINUTE)

extern int32u emberAfHibernateDuration;

/**
 * @brief Macro for setting hibernate duration at run time
 *
 * @param newValue The value to which the hibernate duration
 *    should be set
 */
#define EMBER_AF_SET_HIBERNATE_DURATION(newValue)       \
  emberAfHibernateDuration = newValue

/**
 * @brief Macro for setting nap duration at run time
 *
 * @param newValue The value to which the hibernate duration
 *    should be set
 */
#define EMBER_AF_SET_NAP_DURATION(newValue)     \
  emberAfNapDuration = newValue

/**
 * @brief An enum used to track the tasks that the Application
 * framework cares about. These are inteneded to be tasks
 * that should keep the device out of hibernation like an
 * application level request / response. If the response does
 * not come in as a data ack, then the application will need
 * to stay out of hibernation to wait and poll for it.
 *
 * Of coures some tasks do not necessarily have a response. For
 * instance, a ZDO request may or may not have a response. In this
 * case, the application framework cannot rely on the fact that
 * a response will come in to end the wake cycle, so the Application
 * framework must timeout the wake cycle if no expected
 * response is received or no other event can be relied upon to
 * end the wake cycle.
 *
 * Tasks of this type should be added to the EMBER_AF_WAKE_TIMEOUT_MASK
 * so that they can be governed by a timeout instead of a request
 * / response
 *
 * the register emAfCurrentAppTasks is an int32u bitmask used to
 * track which tasks are active at any given time. The bottom 16 bits,
 * values 0x01 - 0x8000 are reserved for Ember's use. The top
 * 16 bits are reserved for the customer, values 0x8000 -
 * 0x80000000
 */
enum {
  // we may be able to remove these top two since they are
  // handled by the stack on the SOC.
  EMBER_AF_WAITING_FOR_DATA_ACK                  = 0x01, //not needed?
  EMBER_AF_LAST_POLL_GOT_DATA                    = 0x02, //not needed?
  EMBER_AF_WAITING_FOR_SERVICE_DISCOVERY         = 0x04,
  EMBER_AF_WAITING_FOR_ZDO_RESPONSE              = 0x08,
  EMBER_AF_WAITING_FOR_ZCL_RESPONSE              = 0x10,
  EMBER_AF_WAITING_FOR_REGISTRATION              = 0x20,
  EMBER_AF_WAITING_FOR_PARTNER_LINK_KEY_EXCHANGE = 0x40,
};

/**
 * @brief The amount of time in quarter seconds
 * that a task which has an optional response can keep the
 * device awake for. Curently defaults to 3 seconds.
 */
#ifndef EMBER_AF_WAKE_TIMEOUT
#define EMBER_AF_WAKE_TIMEOUT 4 // 1 second
#endif

/**
 * @brief A mask of all app tasks that currently can be
 * governed by a timeout. Any task which does not necessarily
 * have a deterministic response which can trigger an end to the wake
 * cycle must be included in this mask so that it can be timed
 * out.
 */
#ifndef EMBER_AF_WAKE_TIMEOUT_MASK
#define EMBER_AF_WAKE_TIMEOUT_MASK (EMBER_AF_WAITING_FOR_ZDO_RESPONSE \
                                    | EMBER_AF_WAITING_FOR_ZCL_RESPONSE)
#endif

/**
 * @brief externed value used in task functions and macros
 * which is declared inside app/framework/util/util.c
 */
extern int32u emAfCurrentAppTasks;

/**
 * @brief A function used to add a task to the task register.
 */
void emberAfAddToCurrentAppTasks(int32u mask);

/**
 * @brief A function used to remove a task from the task register.
 */
void emberAfRemoveFromCurrentAppTasks(int32u mask);

/**
 * @brief A function used to check if it is ok to hibernate. It
 * is not ok to hibernate if any app tasks are currently in
 * progress, so this macro just checks that there are no current
 * app tasks registered. If a task is in progress but has
 * timedout it will be removed before a determination concerning
 * hibernation is made. This function also checks the current
 * active events to see if any are holding the device out of
 * hibernation.
 */
boolean emberAfOkToHibernate(void);

/**
 * @brief A macro used to check if it is ok for the application
 * to nap. It is not ok for the applicaton to nap if any processes
 * are going on that require the device to stay awake. This macro
 * only checks that current active events are not holding the device
 * out of nap.
 */
#define emberAfOkToNap() (emberAfGetCurrentSleepControl() < EMBER_AF_STAY_AWAKE)

/**
 * @brief A macro used to retrieve the bitmask of all application
 * frameowrk tasks currently in progress. This can be useful for debugging if
 * some task is holding the device out of hibernation.
 */
#ifdef ZA_DEVICE_IS_SLEEPY
#define emberAfCurrentAppTasks() (emAfCurrentAppTasks)
#else
#define emberAfCurrentAppTasks()
#endif //ZA_DEVICE_IS_SLEEPY

/**
 * @brief a function used to run the applcation framework's
 *        event mechanism. This function passes the application
 *        framework's event tables to the ember stack's event
 *        processing code.
 */
void emberAfRunEvents(void);

/**
 * @brief This function schedules an event to call emberFindAndRejoinNetwork.
 * the first call to emberFindAndRejoinNetwork will happen on the current channel
 * with security enabled. After that, the event will be rescheduled every 10 seconds
 * across all 15.4 channels. This event will be rescheduled until 
 * EMBER_AF_REJOIN_ATTEMPTS_MAX is reached or a suitable network is joined. 
 * If EMBER_AF_REJOIN_ATTEMPTS_MAX is set to 0xff, the event will be
 * rescheduled indefinitely until a suitable network is found and joined.
 *
 * @return Returns true if the device is able to start a move, false if a
 * a move event is already scheduled.
 */
boolean emberAfStartMove(void);

/**
 * @brief Friendly define for use in the scheduling or canceling client events
 * with emberAfScheduleClusterTick() and emberAfDeactivateClusterTick().
 */
#define EMBER_AF_CLIENT_CLUSTER_TICK TRUE

/**
* @brief Friendly define for use in the scheduling or canceling server events
* with emberAfScheduleClusterTick() and emberAfDeactivateClusterTick().
 */
#define EMBER_AF_SERVER_CLUSTER_TICK FALSE

/**
 * @brief This function is used to schedule a cluster related
 * event inside the application framework's event mechanism.
 * This function provides a wrapper for the ember stack
 * event mechanism which allows the cluster code
 * to access its events by their endpoint, cluster id and client/server
 * identity. The passed sleepControl value provides the same functionality
 * as adding an event to the current app tasks. By passing this value, the
 * cluster is able to indicate the priority of the event that is scheduled
 * and what type of sleeping the processor should be able to do while
 * the event being scheduled is active. The sleepControl value for each
 * active event is checked inside the emberAfOkToHibernate and emberAfOkToNap
 * functions.
 *
 * @param endpoint the endpoint of the event to be scheduled
 * @param clusterId the clusterId of the event to be scheduled
 * @param isClient TRUE if the event to be scheduled is associated with a
 *        client cluster, FALSE otherwise.
 * @param time the number of milliseconds till the event should be called.
 * @param sleepControl the priority of the event, what the processor should
 *        be allowed to do in terms of sleeping while the event is active.
 *
 * @return If the event in question was found in the event
 *         table and scheduled, this function will return EMBER_SUCCESS,
 *         If the event could not be found it will return EMBER_BAD_ARGUMENT
 *
 */
EmberStatus emberAfScheduleClusterTick(int8u endpoint,
                                       int16u clusterId,
                                       boolean isClient,
                                       int32u timeMs,
                                       EmberAfEventSleepControl sleepControl);

/**
 * @brief A function used to deactivate a cluster related event.
 * This function provides a wrapper for the ember stack's event mechanism
 * which allows an event to be accessed by its endpoint, cluster id and
 * client/server identity.
 *
 * @param endpoint the endpoint of the event to be deactivated.
 * @param clusterId the clusterId of the event to be deactivated.
 * @param isClient TRUE if the event to be deactivate is a client
 *        cluster, FALSE otherwise.
 *
 * @return If the event in question was found in the event table
 *         and scheduled, this function will return EMBER_SUCCESS,
 *         If the event could not be found it will return
 *         EMBER_BAD_ARGUMENT
 *
 */
EmberStatus emberAfDeactivateClusterTick(int8u endpoint,
                                         int16u clusterId,
                                         boolean isClient);

/**
 * @brief A convenience function used to schedule an event in
 * the Ember Event Control API depending on how large the passed
 * timeMs value is. The Ember Event Control API uses three functions
 * for the scheduling of events which indicate the time increment in
 * milliseconds, quarter seconds, or seconds. This function wraps that
 * API and provides a single function for the scheduling of all events
 * based on a passed int32u value indicating the number of milliseconds
 * until the next event. This function is used by both the cluster scheduling
 * as well as the application framework's own internal event scheduling
 *
 * @param eventControl A pointer to the ember event control value which
 *                     is referred to in the event table.
 * @param timeMs the number of milliseconds until the next event.
 *
 * @return If the passed milliseconds can be transformed into a proper
 *         event control time increment: milliseconds, quarter seconds or
 *         minutes, that can be represented in a int16u, this function will
 *         schedule the event and return EMBER_SUCCESS. Otherwise it will
 *         return EMBER_BAD_ARGUMENT.
 *
 */
EmberStatus emberAfEventControlSetDelay(EmberEventControl *eventControl, int32u timeMs);


/**
 * @brief A function used to retrieve the number of milliseconds until
 * the next event scheduled in the application framework's event
 * mechanism.
 * @param maxMs, the maximum number of milliseconds until the next
 *        event.
 * @return The number of milliseconds until the next event or
 * maxMs if no event is scheduled before then.
 */
int32u emberAfMsToNextEvent(int32u maxMs);

/**
 * @brief A function used to retrieve the number of quarter seconds until
 * the next event scheduled in the application framework's event
 * mechanism. This function will round down and will return 0 if the
 * next event must fire within a quarter second.
 * @param maxQS, the maximum number of quarter seconds until the next
 *        event.
 * @return The number of quarter seconds until the next event or
 * maxQS if no event is scheduled before then.
 */
#define emberAfQSToNextEvent(maxQS) (emberAfMsToNextEvent(maxQS * \
				     (MILLISECOND_TICKS_PER_QUARTERSECOND)) \
				     / (MILLISECOND_TICKS_PER_QUARTERSECOND))

/**
 * @brief A function for retrieving the most restrictive sleep
 * control value for all scheduled events. This function is
 * used by emberAfOkToNap and emberAfOkToHibernate to makes sure
 * that there are no events scheduled which will keep the device
 * from hibernating or napping.
 * @return The most restrictive sleep control value for all
 *         scheduled events or the value returned by 
 *         emberAfGetDefaultSleepControl()
 *         if no events are currently scheduled. The default
 *         sleep control value is initialized to 
 *         EMBER_AF_OK_TO_HIBERNATE but can be changed at any
 *         time using the emberAfSetDefaultSleepControl() function.
 */
EmberAfEventSleepControl emberAfGetCurrentSleepControl(void);

/**
 * @brief A function for setting the default sleep control
 *        value against which all scheduled event sleep control
 *        values will be evaluated. This can be used to keep
 *        a device awake for an extended period of time by setting
 *        the default to EMBER_AF_STAY_AWAKE and then resetting
 *        the value to EMBER_AF_OK_TO_HIBERNATE once the wake
 *        period is complete.
 */
void  emberAfSetDefaultSleepControl(EmberAfEventSleepControl control);

/**
 * @brief A function used to retrive the default sleep control against
 *        which all event sleep control values are evaluated. The
 *        default sleep control value is initialized to 
 *        EMBER_AF_OK_TO_HIBERNATE but can be changed by the application
 *        at any time using the emberAfSetDefaultSleepControl() function.
 * @return The current default sleep control value.
 */
 extern EmberAfEventSleepControl emAfDefaultSleepControl;
 #define emberAfGetDefaultSleepControl() (emAfDefaultSleepControl)

/** @} END Hibernation */


/** @name Time */
// @{

/**
 * @brief Retrieves current time.
 *
 * Convienience function for retrieving the current time.
 * If the time server cluster is implemented, then the time
 * is retrieved from that cluster's time attribute. Otherwise,
 * the emberAfGetCurrentTimeCallback is called. In the case of the
 * stub, the current hal time is returned.
 *
 * A real time is expected to in the ZigBee time format, the number
 * of seconds since the year 2000.
 */
int32u emberAfGetCurrentTime(void);

/**
 * @brief Sets current time.
 * Convenience function for setting the time to a value.
 * If the time server cluster is implemented on this device,
 * then this call will be passed along to the time cluster server
 * which will update the time. Otherwise the emberAfSetTimeCallback
 * is called, which in the case of the stub does nothing.
 *
 * @param utcTime: A ZigBee time, the number of seconds since the
 *                 year 2000.
 */
void emberAfSetTime(int32u utcTime);


/**
 * @brief Prints time.
 *
 * Convenience function for all clusters to print time.
 * This function expects to be passed a ZigBee time which
 * is the number of seconds since the year 2000. If
 * EMBER_AF_PRINT_CORE is defined, this function will print
 * a human readable time from the passed value. If not, this
 * function will print nothing.
 *
 * @param utcTime: A ZigBee time, the number of seconds since the
 *                 year 2000.
 */
void emberAfPrintTime(int32u utcTime);

/** @} END Time */


/** @name Messaging */
// @{

/**
 * @brief DEPRECATED: Use emberAfSendResponse to send the response immediately
 * or any of the emberAfSend or emberAfSendCommand functions to send delayed
 * responses.
 *
 * This macro prepares the response to be sent
 * once the application exits the context of the 
 * incomingMessageHandler. This ensures that the 
 * message response will be sent back after
 * the APS Ack is sent for the incoming message.
 */
extern boolean emberAfResponseWaitingFlag;

/**
 * @brief DEPRECATED: Use emberAfSendResponse to send the response immediately
 * or any of the emberAfSend or emberAfSendCommand functions to send delayed
 * responses.
 */
#define emberAfSetResponseWaiting() emberAfResponseWaitingFlag = TRUE

/**
 * @brief This function sends a ZCL response, based on the information
 * that is currently in the outgoing buffer. It is expected that a complete
 * ZCL message is present, including header.  The application may use
 * this method directly from within the message handling function
 * and associated callbacks.  However this will result in the 
 * response being sent before the APS Ack is sent which is not
 * ideal.
 * 
 * NOTE:  This will overwrite the ZCL sequence number of the message
 * to use the LAST received sequence number.
 */
EmberStatus emberAfSendResponse(void);

/**
 * @brief DEPRECATED: Use emberAfSendCommandUnicast instead to unicast the
 * message to a specific node or binding or address table index.  If using the
 * emberAfFillCommand macros to construct the outgoing message, the sequence
 * number will be set automatically.  Otherwise, emberAfNextSequence can be
 * used to retrieve a new sequence number for the message.
 *
 * This function sends a ZCL request, based on the information that is currently
 * in the outgoing buffer.  It is expected that a complete ZCL mesasge is
 * present, including header.
 * 
 * NOTE:  This will overwrite the ZCL sequence number of the message to use the
 * NEXT sequence number of the local device.
 */
EmberStatus emberAfSendRequest(void);

/**
 * @brief Sends multicast.
 */
EmberStatus emberAfSendMulticast(EmberMulticastId multicastId,
                                 EmberApsFrame *apsFrame,
                                 int16u messageLength,
                                 int8u* message);

/**
 * @brief Sends broadcast.
 */
EmberStatus emberAfSendBroadcast(EmberNodeId destination,
                                 EmberApsFrame *apsFrame,
                                 int16u messageLength,
                                 int8u* message);

/**
 * @brief Sends unicast.
 */
EmberStatus emberAfSendUnicast(EmberOutgoingMessageType type,
                               int16u indexOrDestination,
                               EmberApsFrame *apsFrame,
                               int16u messageLength,
                               int8u* message);

/**
 * @brief Sends interpan message.
 */
EmberStatus emberAfSendInterPan(EmberPanId panId,
                                const EmberEUI64 destinationLongId,
                                EmberNodeId destinationShortId,
                                EmberMulticastId multicastId,
                                EmberAfClusterId clusterId,
                                EmberAfProfileId profileId,
                                int16u messageLength,
                                int8u* messageBytes);

// DEPRECATED.
#define emberAfSendInterpanUnicast(destinationShortAddress,  \
                                   destinationPanId,         \
                                   destinationAppProfileId,  \
                                   destinationClusterId,     \
                                   multicastIdOrZero,        \
                                   longAddressOrNull,        \
                                   messageLength,            \
                                   messageBytes)             \
  emberAfSendInterPan(destinationPanId,                      \
                      longAddressOrNull,                     \
                      destinationShortAddress,               \
                      multicastIdOrZero,                     \
                      destinationClusterId,                  \
                      destinationAppProfileId,               \
                      messageLength,                         \
                      messageBytes)

/**
 * @brief Sends end device binding request.
 */
EmberStatus emberAfSendEndDeviceBind(int8u endpoint);

/**
 * @brief Sends the command prepared with emberAfFill.... macro.
 *
 * This function is used to send a command that was previously prepared
 * using the emberAfFill... macros from the client command API. It
 * will be sent as multicast.
 */
EmberStatus emberAfSendCommandMulticast(EmberMulticastId multicastId);

/**
 * @brief Sends the command prepared with emberAfFill.... macro.
 *
 * This function is used to send a command that was previously prepared
 * using the emberAfFill... macros from the client command API.
 * It will be sent as unicast.
 */
EmberStatus emberAfSendCommandUnicast(EmberOutgoingMessageType type,
                                      int16u indexOrDestination);

/**
 * @brief Sends the command prepared with emberAfFill.... macro.
 *
 * This function is used to send a command that was previously prepared
 * using the emberAfFill... macros from the client command API.
 */
EmberStatus emberAfSendCommandBroadcast(EmberNodeId destination);

/**
 * @brief Sends the command prepared with emberAfFill.... macro.
 *
 * This function is used to send a command that was previously prepared
 * using the emberAfFill... macros from the client command API.
 * It will be sent via inter-PAN.  If destinationLongId is not NULL, the message
 * will be sent to that long address using long addressing mode; otherwise, the
 * message will be sent to destinationShortId using short address mode.  IF
 * multicastId is not zero, the message will be sent using multicast mode.
 */
EmberStatus emberAfSendCommandInterPan(EmberPanId panId,
                                       const EmberEUI64 destinationLongId,
                                       EmberNodeId destinationShortId,
                                       EmberMulticastId multicastId,
                                       EmberAfProfileId profileId);

// DEPRECATED.
#define emberAfSendCommandInterpanUnicast(eui64,       \
                                          nodeId,      \
                                          panId,       \
                                          multicastId, \
                                          profileId)   \
  emberAfSendCommandInterPan(panId,                    \
                             eui64,                    \
                             nodeId,                   \
                             multicastId,              \
                             profileId)

/**
 * @brief Sends a default response to a cluster command.
 *
 * This function is used to prepare and send a default response to a cluster
 * command.
 *
 * @param cmd The cluster command to which to respond.
 * @param status Status code for the default response command.
 * @return An ::EmberStatus value that indicates the success or failure of
 * sending the response.
 */
EmberStatus emberAfSendDefaultResponse(const EmberAfClusterCommand *cmd,
                                       EmberAfStatus status);

/**
 * @brief Returns the maximum size of the payload that the Application
 * Support sub-layer will accept for the given message type, destination, and
 * APS frame.
 *
 * The size depends on multiple factors, including the security level in use
 * and additional information added to the message to support the various
 * options.
 *
 * @param type The outgoing message type.
 * @param indexOrDestination Depending on the message type, this is either the
 *  EmberNodeId of the destination, an index into the address table, an index
 *  into the binding table, the multicast identifier, or a broadcast address.
 * @param apsFrame The APS frame for the message.
 * @return The maximum APS payload length for the given message.
 */
int8u emberAfMaximumApsPayloadLength(EmberOutgoingMessageType type,
                                     int16u indexOrDestination,
                                     EmberApsFrame *apsFrame);

/**
 * @brief Access to client API aps frame.
 */
EmberApsFrame *emberAfGetCommandApsFrame(void);

/**
 * @brief Friendly define for use in discovering client clusters with
 * ::emberAfFindDevicesSupportingCluster() or 
 * ::emberAfFindDevicesByProfileAndCluster().
 */
#define EMBER_AF_CLIENT_CLUSTER_DISCOVERY FALSE

/**
 * @brief Friendly define for use in discovering server clusters with
 * ::emberAfFindDevicesSupportingCluster() or 
 * ::emberAfFindDevicesByProfileAndCluster().
 */
#define EMBER_AF_SERVER_CLUSTER_DISCOVERY TRUE

#ifdef DOXYGEN_SHOULD_SKIP_THIS
/**
 * @brief Find devices in the network that support a given cluster.  This 
 *   function assumes that the application profile for the cluster being 
 *   discovered is that of the primary endpoint configuration on the local
 *   device.  If you have multiple endpoints with different profiles, this
 *   may not be a valid assumption.  For a more flexible interface that supports
 *   specifying a profile ID, see ::emberAfFindDevicesByProfileAndCluster().
 *   may either be a specific device, or the broadcast
 *
 * With this function a service discovery is initiated and received
 * responses are returned by executing the callback function passed in.
 * For unicast discoveries, the callback will be executed only once.
 * Either the target will return a result or a timeout will occur.
 * For broadcast discoveries, the callback may be called multiple times
 * and after a period of time the discovery will be finished with a final
 * call to the callback.
 * 
 * This API has been superseded by ::emberAfFindDevicesByProfileAndCluster() 
 * but remains as a macro for convenience and backwards compatibility.  It may
 * also be useful in cases where the calling function can't easily determine the
 * application profile (by looking at the description of a relevant endpoint).
 *
 * @param target The destination node ID for the discovery; either a specific
 *  node's ID or EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS.
 * @param clusterId The cluster being discovered. (Assumed to be from Primary 
 *  endpoint's application profile.)
 * @param serverCluster EMBER_AF_SERVER_CLUSTER_DISCOVERY (TRUE) if discovering
 *  servers for the target cluster; EMBER_AF_CLIENT_CLUSTER_DISCOVERY (FALSE)
 *  if discovering clients for that cluster.
 * @param callback Function pointer for the callback function triggered when
 *  a match is discovered.  (For broadcast discoveries, this is called once per
 *  matching node, even if a node has multiple matching endpoints.)
 */
EmberStatus emberAfFindDevicesSupportingCluster(EmberNodeId target,
                                                EmberAfClusterId clusterId,
                                                boolean serverCluster,
                                                EmberAfServiceDiscoveryCallback *callback);
#else // doxygen
#define emberAfFindDevicesSupportingCluster( target, clusterId, serverCluster, callback) \
 ( emberAfFindDevicesByProfileAndCluster( target, \
     emberAfPrimaryProfileId(), 	\
     clusterId, \
     serverCluster, \
     callback) )
#endif // doxygen 


/**
 * @brief Use this function to find devices in the network with endpoints
 *   matching a given profile ID and cluster ID in their descriptors.
 *   Target may either be a specific device, or the broadcast
 *   address EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS.
 *
 * With this function a service discovery is initiated and received
 * responses are returned by executing the callback function passed in.
 * For unicast discoveries, the callback will be executed only once.
 * Either the target will return a result or a timeout will occur.
 * For broadcast discoveries, the callback may be called multiple times
 * and after a period of time the discovery will be finished with a final
 * call to the callback.
 * 
 * @param target The destination node ID for the discovery; either a specific
 *  node's ID or EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS.
 * @param profileId The application profile for the cluster being discovered.
 * @param clusterId The cluster being discovered.
 * @param serverCluster EMBER_AF_SERVER_CLUSTER_DISCOVERY (TRUE) if discovering
 *  servers for the target cluster; EMBER_AF_CLIENT_CLUSTER_DISCOVERY (FALSE)
 *  if discovering clients for that cluster.
 * @param callback Function pointer for the callback function triggered when
 *  a match is discovered.  (For broadcast discoveries, this is called once per
 *  matching node, even if a node has multiple matching endpoints.)
 */
EmberStatus emberAfFindDevicesByProfileAndCluster(EmberNodeId target,
                                                  EmberAfProfileId profileId,
                                                  EmberAfClusterId clusterId,
                                                  boolean serverCluster,
                                                  EmberAfServiceDiscoveryCallback *callback);


/** 
 * @brief Use this function to initiate a discovery for the IEEE address
 *   of the specified node id.  This will send a unicast sent to the target
 *   node ID.
 */
EmberStatus emberAfFindIeeeAddress(EmberNodeId shortAddress,
                                   EmberAfServiceDiscoveryCallback *callback);

/**
 * @brief Use this function to initiate a discovery for the short ID of the
 *   specified long address.  This will send a broadcast to all
 *   rx-on-when-idle devices (non-sleepies).
 */
EmberStatus emberAfFindNodeId(EmberEUI64 longAddress,
                              EmberAfServiceDiscoveryCallback *callback);

/**
 * @brief Use this function to add an entry for a remote device to the address
 * table.
 *
 * @param longId The EUI64 of the remote device.
 * @param shortId The node id of the remote device or ::EMBER_UNKNOWN_NODE_ID
 * if the node id is currently unknown.
 * @return The index of the address table entry for this remove device or
 * ::EMBER_NULL_ADDRESS_TABLE_INDEX if an error occurred (e.g., the address
 * table is full).
 */
int8u emberAfAddAddressTableEntry(EmberEUI64 longId, EmberNodeId shortId);

/**
 * @brief Use this function to add an entry for a remote device to the address
 * table at a specific location.
 *
 * @param index The index of the address table entry.
 * @param longId The EUI64 of the remote device.
 * @param shortId The node id of the remote device or ::EMBER_UNKNOWN_NODE_ID
 * if the node id is currently unknown.
 * @return ::EMBER_SUCCESS if the address table entry was successfully set,
 * ::EMBER_ADDRESS_TABLE_ENTRY_IS_ACTIVE if any messages are being sent using
 * the existing entry at that index, or ::EMBER_ADDRESS_TABLE_INDEX_OUT_OF_RANGE
 * if the index is out of range.
 */
EmberStatus emberAfSetAddressTableEntry(int8u index,
                                        EmberEUI64 longId,
                                        EmberNodeId shortId);

/**
 * @brief Use this macro to retrive the current command. This
 * macro may only be used within the command parsing context. For instance
 * Any of the command handling callbacks may use this macro. If this macro
 * is used outside the command context, the returned EmberAfClusterCommand pointer
 * will be null.
 */
#define emberAfCurrentCommand() (emAfCurrentCommand)
extern EmberAfClusterCommand *emAfCurrentCommand;

/**
 * @brief returns the current endpoint that is being served.
 *
 * The purpose of this macro is mostly to access endpoint that
 * is being served in the command callbacks.
 */
#define emberAfCurrentEndpoint() (emberAfCurrentCommand()->apsFrame->destinationEndpoint)

#ifdef DOXYGEN_SHOULD_SKIP_THIS
/** @brief Use this function to initiate key establishment with a remote node.
 * ::emberAfKeyEstablishmentCallback will be called as events occur and when
 * key establishment completes.
 *
 * @param nodeId The node id of the remote device.
 * @param endpoint The endpoint on the remote device.
 * @return ::EMBER_SUCCESS if key establishment was initiated successfully
 */
EmberStatus emberAfInitiateKeyEstablishment(EmberNodeId nodeId, int8u endpoint);

/** @brief Use this function to initiate key establishment wih a remote node on
 * a different PAN.  ::emberAfInterPanKeyEstablishmentCallback will be called
 * as events occur and when key establishment completes.
 *
 * @param panId The PAN id of the remote device.
 * @param eui64 The EUI64 of the remote device.
 * @return ::EMBER_SUCCESS if key establishment was initiated successfully
 */
EmberStatus emberAfInitiateInterPanKeyEstablishment(EmberPanId panId,
                                                    const EmberEUI64 eui64);

/** @brief Use this function to tell if the device is in the process of
 * performing key establishment.
 *
 * @return ::TRUE if key establishment is in progress.
 */
boolean emberAfPerformingKeyEstablishment(void);

/** @brief Use this function to initiate partner link key exchange with a
 * remote node.
 *
 * @param target The node id of the remote device.
 * @param endpoint The key establishment endpoint of the remote device.
 * @param callback The callback that should be called when the partner link
 * key exchange completes.
 * @return ::EMBER_SUCCESS if the partner link key exchange was initiated
 * successfully.
 */
EmberStatus emberAfInitiatePartnerLinkKeyExchange(EmberNodeId target,
                                                  int8u endpoint,
                                                  EmberAfPartnerLinkKeyExchangeCallback *callback);
#else
  #define emberAfInitiateKeyEstablishment(nodeId, endpoint) \
    emberAfInitiateKeyEstablishmentCallback(nodeId, endpoint)
  #define emberAfInitiateInterPanKeyEstablishment(panId, eui64) \
    emberAfInitiateInterPanKeyEstablishmentCallback(panId, eui64)
  #define emberAfPerformingKeyEstablishment() \
    emberAfPerformingKeyEstablishmentCallback()
  #define emberAfInitiatePartnerLinkKeyExchange(target, endpoint, callback) \
    emberAfInitiatePartnerLinkKeyExchangeCallback(target, endpoint, callback)
#endif

/** @} END Messaging */


/** @name ZCL macros */
// @{
// Frame control fields (8 bits total)
// Bits 0 and 1 are Frame Type Sub-field
#define ZCL_FRAME_CONTROL_FRAME_TYPE_MASK     (BIT(0)|BIT(1))
#define ZCL_CLUSTER_SPECIFIC_COMMAND          BIT(0)
#define ZCL_PROFILE_WIDE_COMMAND              0
// Bit 2 is Manufacturer Specific Sub-field
#define ZCL_MANUFACTURER_SPECIFIC_MASK        BIT(2)
// Bit 3 is Direction Sub-field
#define ZCL_FRAME_CONTROL_DIRECTION_MASK      BIT(3)
#define ZCL_FRAME_CONTROL_SERVER_TO_CLIENT    BIT(3)
#define ZCL_FRAME_CONTROL_CLIENT_TO_SERVER    0
// Bit 4 is Disable Default Response Sub-field
#define ZCL_DISABLE_DEFAULT_RESPONSE_MASK     BIT(4)
// Bits 5 to 7 are reserved

// Packet must be at least 3 bytes for ZCL overhead.
//   Frame Control (1-byte)
//   Sequence Number (1-byte)
//   Command Id (1-byte)
#define EMBER_AF_ZCL_OVERHEAD                       3
#define EMBER_AF_ZCL_MANUFACTURER_SPECIFIC_OVERHEAD 5

/** @} END ZCL macros */


/** @name Stack handler utility functions */
// ${
/**
 * @brief that function contains the functionality that app framework
 * should execute during the poll complete handler. If you implement
 * your own callback, you should call this function within.
 */
void emberAfPollCompleteHandler(EmberStatus status);


/**
 * @brief that function contains the functionality that app framework
 * should execute during the EZSP poll complete handler. If you implement
 * your own callback, you should call this function within.
 */
void emberAfEzspPollCompleteHandler(EmberStatus status);
/** @} End stack handlers */

/** @name Network utility functions */
// ${

/** @brief Use this function to form a new network using the specified network
 * parameters.
 *
 * @param parameters Specification of the new network.
 * @return An ::EmberStatus value that indicates either the successful formation
 * of the new network or the reason that the network formation failed.
 */
EmberStatus emberAfFormNetwork(EmberNetworkParameters *parameters);

/** @brief Use this function to associate with the network using the specified
 * network parameters.
 *
 * @param parameters Specification of the network with which the node should
 * associate.
 * @return An ::EmberStatus value that indicates either that the association
 * process began successfully or the reason for failure.
 */
EmberStatus emberAfJoinNetwork(EmberNetworkParameters *parameters);

#ifdef DOXYGEN_SHOULD_SKIP_THIS
/** @brief Use this function to find an unused PAN id and form a new network.
 *
 * @return An ::EmberStatus value that indicates either the process begin
 * successfully or the reason for failure.
 */
EmberStatus emberAfFindUnusedPanIdAndForm(void);
/** @brief Use this function to find a joinable network and join it.
 *
 * @return An ::EmberStatus value that indicates either the process begin
 * successfully or the reason for failure.
 */
EmberStatus emberAfStartSearchForJoinableNetwork(void);
#else
  #define emberAfFindUnusedPanIdAndForm()        emberAfFindUnusedPanIdAndFormCallback()
  #define emberAfStartSearchForJoinableNetwork() emberAfStartSearchForJoinableNetworkCallback()
#endif

/** @} End network utility functions */

/** @} END addtogroup */

#endif // __AF_API__
