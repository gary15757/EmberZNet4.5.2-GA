// *******************************************************************
// * af-node.c
// *
// * Security code for a normal (non-Trust Center) node.
// *
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include PLATFORM_HEADER //compiler/micro specifics, types

#if defined EZSP_HOST
  #include "stack/include/ember-types.h"
  #include "stack/include/error.h"

  #include "app/util/ezsp/ezsp-protocol.h"
  #include "app/util/ezsp/ezsp.h"
  #include "app/util/ezsp/ezsp-utils.h"
  #include "app/util/ezsp/serial-interface.h"

#else // Stack App
  #include "stack/include/ember.h"
#endif

// This is needed when security-config.h is included so that the functions below
// are correctly defined and not stubbed.  Only needed by this file.
#define USE_REAL_SECURITY_PROTOTYPES

// to get access to the emberAfSecurityPrint macro
#include "app/framework/util/af-main.h"

// HAL - hardware abstraction layer
#include "hal/hal.h"
#include "app/util/serial/serial.h"


#include "app/framework/security/af-security.h"
#include "app/framework/util/print.h"

// PRECONFIGURED_KEY is defined by the security configuration based on the
// security profile.  ZA_SECURITY_NETWORK_KEY is unneeded by the normal node.
static PGM EmberKeyData preconfiguredKey = PRECONFIGURED_KEY;

//------------------------------------------------------------------------------

EmberStatus zaNodeSecurityInit(void)
{
  EmberInitialSecurityState state;
  EmberStatus status;
  MEMSET(&state, 0, sizeof(EmberInitialSecurityState));

  // NOTE:  We must use the PGM version of memcopy() for those
  // platforms where the program and data space are segregrated.
  halCommonMemPGMCopy(emberKeyContents(&(state.preconfiguredKey)), 
                      emberKeyContents(&preconfiguredKey),
                      EMBER_ENCRYPTION_KEY_SIZE);

  state.bitmask = ((NODE_SECURITY_BITMASK 
                    | ADDITIONAL_BITMASK_OPTIONS)
                   & ~CLEARED_BITMASK_OPTIONS);

#if defined ZA_CLI_FULL
  // This function will only be used if the full CLI is enabled,
  // and a value has been previously set via the "changekey" command.
  getLinkKeyFromCli(&(state.preconfiguredKey));
#endif
  
  emberAfSecurityPrintln("set state to: 0x%2x", state.bitmask);
  status = emberSetInitialSecurityState(&state);
  emberAfSecurityPrintln("security init node: 0x%x", status);
  return status;
}


