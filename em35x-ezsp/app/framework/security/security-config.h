// *******************************************************************
// * security-config.h
// *
// * This file defines various security parameters based on the security
// * profile setup via App. Builder.
// *
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// This will be defined in the application's configuration from App. Builder.
//#define EMBER_AF_SECURITY_PROFILE               <from-app-builder>

#define NONE_SECURITY_PROFILE    0x00
#define HA_SECURITY_PROFILE      0x01
#define SE_SECURITY_PROFILE_TEST 0x02
#define SE_SECURITY_PROFILE_FULL 0x03
#define CUSTOM_SECURITY_PROFILE  0xFF

#define SECURITY_PROFILE_STRINGS                \
  "No Security",                                \
  "HA",                                         \
  "SE Test",                                    \
  "SE Full",                                    \

#define CUSTOM_PROFILE_STRING  "Custom"

#if EMBER_AF_SECURITY_PROFILE == SE_SECURITY_PROFILE_TEST || EMBER_AF_SECURITY_PROFILE == SE_SECURITY_PROFILE_FULL
  #define SE_SECURITY_PROFILE_ENABLED
#endif

#define ALLOW TRUE
#define DENY  FALSE

// HA Security
// Uses link keys with a global preconfigured key on the trust center.
// All devices use that key to join.
#define HA_SECURITY_BITMASK ( EMBER_STANDARD_SECURITY_MODE    \
                              | EMBER_HAVE_PRECONFIGURED_KEY  \
                              | EMBER_GLOBAL_LINK_KEY         \
                              | EMBER_REQUIRE_ENCRYPTED_KEY)
#define HA_TC_LINK_KEY_REQUEST_POLICY  DENY
#define HA_APP_LINK_KEY_REQUEST_POLICY ALLOW
// This needs to be updated with the new profile interopability link key.
#define ZIGBEE_PROFILE_INTEROPERABILITY_LINK_KEY          \
  /* This key is "ZigBeeAlliance09" */                    \
  { 0x5A, 0x69, 0x67, 0x42, 0x65, 0x65, 0x41, 0x6C,       \
    0x6C, 0x69, 0x61, 0x6E, 0x63, 0x65, 0x30, 0x39 }

// SE Security Test
// Uses a global preconfigured link key so that devices can join
// without install codes.  This may be used with or without real ECC.
#define SE_SECURITY_TEST_BITMASK ( EMBER_STANDARD_SECURITY_MODE   \
                                   | EMBER_HAVE_PRECONFIGURED_KEY \
                                   | EMBER_GLOBAL_LINK_KEY        \
                                   | EMBER_REQUIRE_ENCRYPTED_KEY)
#define SE_TC_LINK_KEY_REQUEST_POLICY  DENY
#define SE_APP_LINK_KEY_REQUEST_POLICY ALLOW
#define SE_SECURITY_TEST_LINK_KEY                         \
  { 0x56, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,       \
    0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77 }

// SE Security Full
// There is no global preconfigured link key defined.  Devices must
// join with their install code already setup in the tokens.
// TC will have to individually add the install code keys for each joining
// device at runtime.
#define SE_SECURITY_FULL_BITMASK  ( EMBER_STANDARD_SECURITY_MODE                     \
                                    | EMBER_GET_PRECONFIGURED_KEY_FROM_INSTALL_CODE  \
                                    | EMBER_REQUIRE_ENCRYPTED_KEY)
// Key request policies are the same for the SE Test and SE Full Profiles.
// #define SE_TC_LINK_KEY_REQUEST_POLICY  DENY
// #define SE_APP_LINK_KEY_REQUEST_POLICY ALLOW


#define DUMMY_KEY { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   \
                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }


// For all the security profiles but "Custom", the TC_SECURITY_BITMASK and
// NODE_SECURITY_BITMASK can be set to the same values.  This is just a 
// coincidence and not by design.

#if EMBER_AF_SECURITY_PROFILE == NONE_SECURITY_PROFILE
  #define TC_SECURITY_BITMASK           0x0
  #define NODE_SECURITY_BITMASK         0x0
  #define TC_LINK_KEY_REQUEST_POLICY    DENY
  #define APP_LINK_KEY_REQUEST_POLICY   DENY
  #define PRECONFIGURED_KEY             DUMMY_KEY

#elif EMBER_AF_SECURITY_PROFILE == HA_SECURITY_PROFILE
  #define TC_SECURITY_BITMASK           HA_SECURITY_BITMASK
  #define NODE_SECURITY_BITMASK         HA_SECURITY_BITMASK
  #define TC_LINK_KEY_REQUEST_POLICY    HA_TC_LINK_KEY_REQUEST_POLICY
  #define APP_LINK_KEY_REQUEST_POLICY   HA_APP_LINK_KEY_REQUEST_POLICY
  #define PRECONFIGURED_KEY             ZIGBEE_PROFILE_INTEROPERABILITY_LINK_KEY

#elif EMBER_AF_SECURITY_PROFILE == SE_SECURITY_PROFILE_TEST
  #define TC_SECURITY_BITMASK           SE_SECURITY_TEST_BITMASK
  #define NODE_SECURITY_BITMASK         SE_SECURITY_TEST_BITMASK
  #define TC_LINK_KEY_REQUEST_POLICY    SE_TC_LINK_KEY_REQUEST_POLICY
  #define APP_LINK_KEY_REQUEST_POLICY   SE_APP_LINK_KEY_REQUEST_POLICY
  #define PRECONFIGURED_KEY             SE_SECURITY_TEST_LINK_KEY

#elif EMBER_AF_SECURITY_PROFILE == SE_SECURITY_PROFILE_FULL
  #define TC_SECURITY_BITMASK           SE_SECURITY_FULL_BITMASK
  #define NODE_SECURITY_BITMASK         SE_SECURITY_FULL_BITMASK
  #define TC_LINK_KEY_REQUEST_POLICY    SE_TC_LINK_KEY_REQUEST_POLICY
  #define APP_LINK_KEY_REQUEST_POLICY   SE_APP_LINK_KEY_REQUEST_POLICY
  // SE does not use a global preconfigured key as all devices get their
  // key from their install code.  The dummy key will not be used
  // because the EMBER_GLOBAL_LINK_KEY bit is not set.  
  #define PRECONFIGURED_KEY             DUMMY_KEY

#elif EMBER_AF_SECURITY_PROFILE != CUSTOM_SECURITY_PROFILE 
  #error "No security profile is set.  Must set #define EMBER_AF_SECURITY_PROFILE."
#endif

// We enable tweaking the security bitmask options via these two #defines.
#if !defined (ADDITIONAL_BITMASK_OPTIONS)
  #define ADDITIONAL_BITMASK_OPTIONS 0
#endif
#if !defined (CLEARED_BITMASK_OPTIONS)
  #define CLEARED_BITMASK_OPTIONS    0
#endif


#if !defined(ZA_KEY_SWITCH_INTERVAL)
  #define ZA_KEY_SWITCH_INTERVAL 172800UL // in seconds (2 days)
#endif


// Custom Security Profile as defined by App. Builder

#if EMBER_AF_SECURITY_PROFILE == CUSTOM_SECURITY_PROFILE

  // Trust Center (Coordinator)
  #if defined ZA_TC_GLOBAL_LINK_KEY  
    #define GLOBAL_LINK_KEY EMBER_GLOBAL_LINK_KEY
  #else
    #define GLOBAL_LINK_KEY 0
  #endif

  #define TC_SECURITY_BITMASK (EMBER_STANDARD_SECURITY_MODE    \
                               | GLOBAL_LINK_KEY               \
                               | EMBER_HAVE_PRECONFIGURED_KEY)
  #define TC_LINK_KEY_REQUEST_POLICY ALLOW
  #define APP_LINK_KEY_REQUEST_POLICY DENY


  // Normal Node
  #if defined ZA_SECURITY_PRECONFIGURED_KEY
    #define OPTION_PRECONFIGURED_KEY EMBER_HAVE_PRECONFIGURED_KEY
    #define PRECONFIGURED_KEY        ZA_SECURITY_PRECONFIGURED_KEY
  #else
    #define OPTION_PRECONFIGURED_KEY EMBER_GET_LINK_KEY_WHEN_JOINING
  #endif
  #if defined ZA_USE_INSTALL_CODE
    #define OPTION_INSTALL_CODE     EMBER_GET_PRECONFIGURED_KEY_FROM_INSTALL_CODE
  #else
    #define OPTION_INSTALL_CODE     0
  #endif

  #define NODE_SECURITY_BITMASK (EMBER_STANDARD_SECURITY_MODE \
                                 | OPTION_PRECONFIGURED_KEY   \
                                 | OPTION_INSTALL_CODE)

#endif // CUSTOM_SECURITY_PROFILE

#if !defined(PRECONFIGURED_KEY)
  #define PRECONFIGURED_KEY DUMMY_KEY
#endif
