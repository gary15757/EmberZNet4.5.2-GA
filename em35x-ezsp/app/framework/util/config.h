// *******************************************************************
// * config.h
// *
// * This file is the main configuration settings for the Zigbee app.
// * The zigbee app can become a Home Automation (HA) device, a Smart
// * Energy (SE) device, or a Custom Zigbee device. 
// *
// * This application can be configured using AppBuilder. AppBuilder
// * generates a file containing defines that setup what pieces of the
// * code is used (which clusters, security settings, zigbee device type,
// * serial port, etc). These defines are added to a new file and included
// * by setting ZA_GENERATED_HEADER to the new filename so these defines are
// * sourced first.
// *
// * This file also contains default values for the defines so some can
// * be set by the user but defaults are always available.
// *******************************************************************

#ifndef __EMBER_AF_CONFIG_H__
#define __EMBER_AF_CONFIG_H__

// include generated configuration information from AppBuilder. 
// ZA_GENERATED_HEADER is defined in the project file
#ifdef ZA_GENERATED_HEADER
  #include ZA_GENERATED_HEADER
#endif


// *******************************************************************
// pre-defined Devices
// 
// use these to determine which type of device the current application is.
// do not use the EMBER_* versions from ember-types.h as these are in an
// enum and are not available at preprocessor time. These need to be set 
// before the devices are loaded from ha-devices.h and se-devices.h
#define ZA_COORDINATOR 1
#define ZA_ROUTER 2
#define ZA_END_DEVICE 3
#define ZA_SLEEPY_END_DEVICE 4
#define ZA_MOBILE_END_DEVICE 5

#define SE_PROFILE_ID (0x0109)
#define CBA_PROFILE_ID (0x0105)

#define EM_AF_MANUFACTURER_CODE 0x1002

// This file determines the security profile used, and from that various
// other security parameters.
#include "app/framework/security/security-config.h"

// *******************************************************************
// Application configuration of RAM for cluster usage
// 
// This section defines constants that size the tables used by the cluster
// code. 

// report entries are used to keep track of which device to send reports
// to once a device has been configured for reports. These are sized at 
// 28 bytes each.
#ifndef EMBER_AF_REPORT_TABLE_SIZE
  #define EMBER_AF_REPORT_TABLE_SIZE 3
#endif

#if (EMBER_AF_REPORT_TABLE_SIZE == 0)
  #define ZA_NO_REPORTING_OPTIMIZATION
#endif

// Set the default manufacturer code for the application
#ifndef EMBER_AF_MANUFACTURER_CODE
  #define EMBER_AF_MANUFACTURER_CODE EM_AF_MANUFACTURER_CODE
#endif

// This is the max hops that the network can support - used to determine
// the max source route overhead and broadcast radius
// if we havent defined MAX_HOPS then define based on profile ID
#ifndef ZA_MAX_HOPS
  #ifdef ZA_PROFILE_ID
    // if we are a Smart Energy device
    #if (ZA_PROFILE_ID == SE_PROFILE_ID)
      #define ZA_MAX_HOPS 6
    // all other profiles
    #else 
      #define ZA_MAX_HOPS 12
    #endif 
  // if we dont have an application profile defined
  #else  
    // default profile is Smart Energy so use that value
    #define ZA_MAX_HOPS 6            
  #endif // ifdef ZA_PROFILE_ID
#endif //ifndef ZA_MAX_HOPS


// device that collect reports need to be concentrators
#ifdef ZA_REPORT_COLLECTION_ENABLED
  #ifndef EMBER_AF_CONCENTRATOR
    #define EMBER_AF_CONCENTRATOR
  #endif
  #ifndef EMBER_CONCENTRATOR_TYPE
    #define EMBER_CONCENTRATOR_TYPE EMBER_LOW_RAM_CONCENTRATOR
  #endif
  #define EMBER_CONCENTRATOR_RADIUS 6
  #define EMBER_CONCENTRATOR_MAX_SECONDS_BETWEEN_DISCOVERIES 20
#endif

// The maximum APS payload, not including any APS options.  This value is also
// available from emberMaximumApsPayloadLength() or ezspMaximumPayloadLength().
// See http://portal.ember.com/faq/payload for more information.
#if EMBER_AF_SECURITY_PROFILE == NONE_SECURITY_PROFILE
  #define EMBER_AF_MAXIMUM_APS_PAYLOAD_LENGTH 100
#else
  #define EMBER_AF_MAXIMUM_APS_PAYLOAD_LENGTH 82
#endif

// Max PHY size = 128
//   -1 byte for PHY length
//   -2 bytes for MAC CRC
#define EMBER_AF_MAXIMUM_INTERPAN_LENGTH 125

// The additional overhead required for APS encryption (security = 5, MIC = 4).
#define EMBER_AF_APS_ENCRYPTION_OVERHEAD 9

// The additional overhead required for APS fragmentation.
#define EMBER_AF_APS_FRAGMENTATION_OVERHEAD 2

// The additional overhead required for network source routing (relay count = 1,
// relay index = 1).  This does not include the size of the relay list itself.
#define EMBER_AF_NWK_SOURCE_ROUTE_OVERHEAD 2

// The additional overhead required per relay address for network source
// routing.  This is in addition to the overhead defined above.
#define EMBER_AF_NWK_SOURCE_ROUTE_PER_RELAY_ADDRESS_OVERHEAD 2

// defines the largest size payload allowed to send and receive. This 
// affects the payloads generated from the CLI and the payloads generated 
// as responses.
// Maximum payload length.
// If fragmenation is enabled, and fragmentation length is bigger than default, then use that
#if defined(EMBER_AF_ENABLE_FRAGMENTATION) \
    && (EMBER_AF_FRAGMENT_BUFFER_SIZE > EMBER_AF_MAXIMUM_APS_PAYLOAD_LENGTH)
  #define EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH EMBER_AF_FRAGMENT_BUFFER_SIZE
  #define EMBER_AF_INCOMING_BUFFER_LENGTH      EMBER_AF_FRAGMENT_BUFFER_SIZE
#else
  #define EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH EMBER_AF_MAXIMUM_APS_PAYLOAD_LENGTH
  #define EMBER_AF_INCOMING_BUFFER_LENGTH      EMBER_AF_MAXIMUM_APS_PAYLOAD_LENGTH
#endif


// *******************************************************************
// Application configuration of Flash
//
// This section gives the application options for turning on or off
// features that affect the amount of flash used.

#ifndef EMBER_PACKET_BUFFER_COUNT
// This applies only to the SOC.
  #if defined (CORTEXM3)
    // Much of the memory we use in App. framework is global and not
    // in packet buffers.  We size this to a large enough size to
    // insure the stack has enough to process messages, but leave
    // most of the memory for the application.
    #define EMBER_PACKET_BUFFER_COUNT 75
  #else // Assume XAP
    // Empirically, 24 is the minimum amount needed for key establishment 
    // operations during joining.
    #define EMBER_PACKET_BUFFER_COUNT 24
  #endif
#endif //EMBER_PACKET_BUFFER_COUNT

// *******************************************************************
// Defines needed for enabling security
//

// Unless we are not using security, our stack profile is 2 (ZigBee Pro).  The
// stack will set up other configuration values based on profile.
#if EMBER_AF_SECURITY_PROFILE != NONE_SECURITY_PROFILE
  #define EMBER_STACK_PROFILE 2
#else // SECURITY_PROFILE == NONE_SECURITY_PROFILE
  #ifndef EMBER_STACK_PROFILE
    #define EMBER_STACK_PROFILE 0
  #endif //EMBER_STACK_PROFILE
  #ifndef EMBER_SECURITY_LEVEL
    #define EMBER_SECURITY_LEVEL 0 
  #endif //EMBER_SECURITY_LEVEL
#endif


// *******************************************************************
// Application Handlers
//
// By default, a number of stub handlers are automatically provided
// that have no effect.  If the application would like to implement any
// of these handlers itself, it needs to define the appropriate macro

#include "app/framework/gen/stack-handlers.h"

#define EMBER_APPLICATION_HAS_REMOTE_BINDING_HANDLER
#define EMBER_APPLICATION_HAS_ENERGY_SCAN_RESULT_HANDLER
#define EMBER_APPLICATION_HAS_GET_ENDPOINT
#define EMBER_APPLICATION_HAS_TRUST_CENTER_JOIN_HANDLER

#define EZSP_APPLICATION_HAS_ENERGY_SCAN_RESULT_HANDLER
#define EZSP_APPLICATION_HAS_INCOMING_SENDER_EUI64_HANDLER
#define EZSP_APPLICATION_HAS_TRUST_CENTER_JOIN_HANDLER

#if defined(EMBER_AF_PLUGIN_OTA_CLIENT_SIGNATURE_VERIFICATION_SUPPORT)
  #define EZSP_APPLICATION_HAS_DSA_VERIFY_HANDLER
#endif

#define EMBER_APPLICATION_HAS_COUNTER_HANDLER

// For storing route records
#if defined(EMBER_APPLICATION_HAS_SOURCE_ROUTING) || defined(EZSP_APPLICATION_HAS_ROUTE_RECORD_HANDLER)
  #ifndef EMBER_SOURCE_ROUTE_TABLE_SIZE
    #define EMBER_SOURCE_ROUTE_TABLE_SIZE 7
  #endif
#else
  #define ZA_NO_SOURCE_ROUTING
#endif


#ifdef EMBER_AF_CONCENTRATOR
#define EMBER_APPLICATION_HAS_INCOMING_ROUTE_ERROR_HANDLER
#endif

// *******************************************************************
// Default values for required defines
//

// Extended PAN ID is used in choosing the correct network when joining
#ifndef ZA_EXTENDED_PANID
  #define ZA_EXTENDED_PANID {0,0,0,0,0,0,0,0}
#endif

// The channel mask controls which channels are used for joining when
// scanning and finding a channel.
//
// channels 11-26:
// 111111111111111100000000000 = 0x7FFF800
//
// channels 11, 14, 15, 19, 20, 24, 25 [HA req 5.5]
// 011000110001100100000000000 = 0x318C800
#ifndef EMBER_AF_CHANNEL_MASK
  #define EMBER_AF_CHANNEL_MASK 0x318C800UL
#endif

// radio power. Maximum value for EM250 is 3.
#ifndef EMBER_AF_RADIO_POWER
  #define EMBER_AF_RADIO_POWER 3
#endif

// This is how long a device waits between polls when it is otherwise
// unoccupied
#ifndef EMBER_AF_LONG_POLL_INTERVAL
  #define EMBER_AF_LONG_POLL_INTERVAL 12 // 3 seconds
#endif

// This is how long a device waits between polls when expecting data
#ifndef EMBER_AF_SHORT_POLL_INTERVAL
  #define EMBER_AF_SHORT_POLL_INTERVAL 2 // 0.5 second
#endif

// the baud rate to use for the serial port
#ifndef EMBER_AF_BAUD_RATE
  #ifdef EZSP_HOST
    #define EMBER_AF_BAUD_RATE 19200
  #else //EZSP_HOST
    #define EMBER_AF_BAUD_RATE 115200
  #endif //EZSP_HOST
#endif //ifndef EMBER_AF_BAUD_RATE

// The value of the prompt for the serial CLI (command-line-interface)
#ifndef ZA_PROMPT
  #define ZA_PROMPT "Default"
#endif //ZA_PROMPT

// zigbee device type
#ifndef ZA_DEVICE_TYPE
  #define ZA_DEVICE_TYPE ZA_COORDINATOR
#endif //ZA_DEVICE_TYPE

// create a define if the device type is sleepy or mobile so we can
// use a simpler ifdef in the code
#if (ZA_DEVICE_TYPE == ZA_SLEEPY_END_DEVICE) || (ZA_DEVICE_TYPE == ZA_MOBILE_END_DEVICE)
  #define ZA_DEVICE_IS_SLEEPY
#endif 

// create a define to use for nonsleepy end devices. These devices still need
// to poll their parents in order to stay in the child table but they do not
// need to sleep
#if (ZA_DEVICE_TYPE == ZA_END_DEVICE)
  #define ZA_DEVICE_IS_NONSLEEPY_END_DEVICE
#endif

// define the serial port that the application uses to be 1 if this is not set
#ifndef APP_SERIAL
  #define APP_SERIAL 1
#endif

#ifndef EMBER_AF_ADDRESS_TABLE_SIZE
#define EMBER_AF_ADDRESS_TABLE_SIZE 2
#endif

#ifndef EMBER_AF_TRUST_CENTER_ADDRESS_CACHE_SIZE
  #ifdef EMBER_AF_CONCENTRATOR
    #define EMBER_AF_TRUST_CENTER_ADDRESS_CACHE_SIZE 2
  #else
    #define EMBER_AF_TRUST_CENTER_ADDRESS_CACHE_SIZE 0
  #endif
#endif

// The total size of the address table is the size of the section used by the
// application plus the size of section used for the trust center address cache.
// The NCP allows each section to be sized independently, but the SOC requires
// a single configuration for the whole table.
#ifndef EMBER_ADDRESS_TABLE_SIZE
#define EMBER_ADDRESS_TABLE_SIZE (EMBER_AF_ADDRESS_TABLE_SIZE + EMBER_AF_TRUST_CENTER_ADDRESS_CACHE_SIZE)
#endif

#ifndef EMBER_AF_DEFAULT_APS_OPTIONS
  // BUGZID 12261: Concentrators use MTORRs for route discovery and should not
  // enable route discovery in the APS options.
  #ifdef EMBER_AF_CONCENTRATOR
    #define EMBER_AF_DEFAULT_APS_OPTIONS            \
      (EMBER_APS_OPTION_RETRY                       \
       | EMBER_APS_OPTION_ENABLE_ADDRESS_DISCOVERY)
  #else
    #define EMBER_AF_DEFAULT_APS_OPTIONS            \
      (EMBER_APS_OPTION_RETRY                       \
       | EMBER_APS_OPTION_ENABLE_ROUTE_DISCOVERY    \
       | EMBER_APS_OPTION_ENABLE_ADDRESS_DISCOVERY)
  #endif //EMBER_AF_CONCENTRATOR
#endif

#endif // __EMBER_AF_CONFIG_H__
