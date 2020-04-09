// *******************************************************************
// * af-security-common.c
// *
// * Security code common to both the Trust Center and the normal node.
// *
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "app/framework/include/af.h"

// to get access to the emberAfSecurityPrint macro
#include "app/framework/util/af-main.h"

#include "app/util/serial/command-interpreter2.h"
#include "app/framework/cli/security-cli.h"
#include "app/framework/util/print.h"

#include "app/framework/security/af-security.h"

//------------------------------------------------------------------------------

static PGM EmberKeyData unSetKey = DUMMY_KEY;

#if EMBER_AF_SECURITY_PROFILE == CUSTOM_SECURITY_PROFILE 
  static PGM_P customProfileText = CUSTOM_PROFILE_STRING;
  #define SECURITY_PROFILE_TEXT customProfileText
#else
  static PGM_NO_CONST PGM_P securityProfileText[] = {
    SECURITY_PROFILE_STRINGS
  };
  #define SECURITY_PROFILE_TEXT securityProfileText[EMBER_AF_SECURITY_PROFILE]  
#endif

// This routine sets the keys from values previously set on the CLI.
// If none are set via the CLI, then the default keys for the security profile
// are used.
static void getKeyFromCli(EmberKeyData* returnData, boolean linkKey)
{
  int8u* keyPtr = (linkKey
                   ? emberKeyContents(&cliPreconfiguredLinkKey)
                   : emberKeyContents(&cliNetworkKey));
  if (0 != halCommonMemPGMCompare(keyPtr, 
                                  emberKeyContents(&unSetKey), 
                                  EMBER_ENCRYPTION_KEY_SIZE)) {
    MEMCOPY(emberKeyContents(returnData), keyPtr, EMBER_ENCRYPTION_KEY_SIZE);
  }
}

void getLinkKeyFromCli(EmberKeyData* returnData)
{
  getKeyFromCli(returnData, TRUE);
}

void getNetworkKeyFromCli(EmberKeyData* returnData)
{
  getKeyFromCli(returnData, FALSE);
}

void printSecurityProfile(void)
{
  emberAfAppPrint("%p level [%x], %p Profile [%p]", 
                  "Security",
                  emberAfGetSecurityLevel(), 
                  "Security",
                  SECURITY_PROFILE_TEXT);
#ifdef ZA_USE_INSTALL_CODE
  emberAfAppPrintln(", install code");
#else
  emberAfAppPrintln("");
#endif
}
