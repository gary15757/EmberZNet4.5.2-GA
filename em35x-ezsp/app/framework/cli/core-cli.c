// *****************************************************************************
// * core-cli.c
// *
// * Core CLI commands used by all applications regardless of profile.
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

// common include file
#include "app/framework/util/common.h"
#include "app/framework/util/af-main.h"

#include "app/util/serial/command-interpreter2.h"
#include "stack/include/library.h"
#include "app/framework/security/af-security.h"

#if !defined(EZSP_HOST)
  #include "stack/include/cbke-crypto-engine.h"  // emberGetCertificate()
#endif

//------------------------------------------------------------------------------
// Forward declarations

static void printOnCommand(void);
static void printOffCommand(void);

//------------------------------------------------------------------------------
// Globals 

#ifdef EMBER_TEST
static PGM_NO_CONST PGM_P counterStrings[] = {
  EMBER_COUNTER_STRINGS
};
#endif //EMBER_TEST


/**
 * @addtogroup cli
 * @{
 */
/**
 * @brief 
 *        <b>debugprint status</b>
 *        - <i>Displays the current status of debug printing on the 
 *          application.</i>
 *        
 *        <b>debugprint all_on</b> 
 *        - <i>Turns on all debug printing 
 *        for printing options which are compiled into the application.</i>
 *   
 *        <b>debugprint all_off</b>
 *        - <i>Turns off all debug printing for printing options which are compiled
 *        into the application.</i>
 *
 *        <b>debugprint on &lt;area&gt;</b>
 *        - <i>Turns on debug printing for a specific area
 *           - area - two byte value indicating the area to turn on</i>
 *
 *        <b>debugprint off &lt;area&gt;</b>
 *        - <i>Turns off debug printing for a specific area
 *           - area - two byte value indicating the area to turn off</i>
 */
#define EMBER_AF_DOXYGEN_CLI__DEBUG_PRINT_COMMANDS
/** @} END addtogroup */
EmberCommandEntry debugPrintCommands[] = {
  {"status", emberAfPrintStatus, ""},
  {"all_on", emberAfPrintAllOn, ""},
  {"all_off", emberAfPrintAllOff, ""},
  {"on", printOnCommand, "v"},
  {"off", printOffCommand, "v"},
  { NULL }
};

//------------------------------------------------------------------------------

static void printPacketBuffers(void)
{
  emberAfAppPrintln("Buffs: %d / %d",
                    emAfGetPacketBufferFreeCount(),
                    emAfGetPacketBufferTotalCount());
}

void emAfCliCountersCommand(void)
{
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
  int8u i;
  int16u counters[EMBER_COUNTER_TYPE_COUNT];
  
  emAfCopyCounterValues(counters);
  for (i=0; i < EMBER_COUNTER_TYPE_COUNT; i++) {
#ifdef EMBER_TEST
    emberAfAppPrintln("%d: %p = %d",
                      i,
                      counterStrings[i],
                      counters[i]);
#else //EMBER_TEST
    emberAfAppPrintln("%d: %d",
                      i,
                      counters[i]);
#endif //EMBER_TEST
    emberAfAppFlush();
  }

  emberAfAppPrintln("");
  printPacketBuffers();
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
}

static void printOnCommand(void)
{
  int16u area = (int16u)emberUnsignedCommandArgument(0);
  emberAfPrintOn(area);
}

static void printOffCommand(void)
{
  int16u area = (int16u)emberUnsignedCommandArgument(0);
  emberAfPrintOff(area);
}

void emAfCliResetCommand(void)
{
  halReboot();
}
                              
void emAfCliHelpCommand(void)
{

#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
  EmberCommandEntry *commandFinger = emberCommandTable;
  for (; commandFinger->name != NULL; commandFinger++) {
    emberAfAppPrintln("%p", commandFinger->name);
    emberAfAppFlush();
  }
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
}


static void printMfgString(void)
{
  int8u i;
  int8u mfgString[MFG_STRING_MAX_LENGTH + 1];
  emberAfGetMfgString(mfgString);

  for (i = 0; i < MFG_STRING_MAX_LENGTH; i++) {
    // The MFG string is not necessarily NULL terminated.
    // Uninitialized bytes are left at 0xFF so we make sure
    // it is NULL terminated.
    if (mfgString[i] == 0xFF) {
      mfgString[i] = '\0';
    }
  }
  mfgString[MFG_STRING_MAX_LENGTH] = '\0';
  
  // Note:  We use '%s' here because this is a RAM string.  Normally
  // most strings are literals or constants in flash and use '%p'.
  emberAfAppPrintln("MFG String: %s", mfgString);
}

static boolean printSmartEnergySecurityInfo(void)
{
#if EMBER_AF_SECURITY_PROFILE == SE_SECURITY_PROFILE_FULL || EMBER_AF_SECURITY_PROFILE == SE_SECURITY_PROFILE_TEST
  boolean securityGood = TRUE;
  emberAfAppPrint("SE Security Info [");
  {
    // for SE security, print the state of ECC, CBKE, and the programmed Cert
    EmberCertificateData cert;
    EmberStatus status = emberGetCertificate(&cert);

    // check the status of the ECC library
    if (emberGetLibraryStatus(EMBER_ECC_LIBRARY_ID)
        & EMBER_LIBRARY_PRESENT_MASK) {
      emberAfAppPrint("RealEcc ");
    } else {
      emberAfAppPrint("NoEcc ");
      securityGood = FALSE;
    }

    // status of EMBER_LIBRARY_NOT_PRESENT means the CBKE is not present
    // in the image.  We don't know anything about the certificate.
    if (status == EMBER_LIBRARY_NOT_PRESENT) {
      emberAfAppPrint("NoCbke UnknownCert");
      securityGood = FALSE;
    } else {
      emberAfAppPrint("RealCbke ");

      // status of EMBER_SUCCESS means the cert is ok
      if (status == EMBER_SUCCESS) {
        emberAfAppPrint("GoodCert");
      }
      // status of EMBER_ERR_FATAL means the cert failed
      else if (status == EMBER_ERR_FATAL) {
        emberAfAppPrint("BadCert");
        securityGood = FALSE;
      }
    }
    emberAfAppPrintln("]");
  }
  emberAfAppFlush();
  return securityGood;
#else
  return FALSE;
#endif
}

// *****************************
// infoCommand
//
// info <no arguments>
// *****************************

void emAfCliInfoCommand(void)
{
  EmberNodeType nodeTypeResult = 0xFF;
  int8u commandLength;
  EmberEUI64 myEui64;
  EmberNetworkParameters networkParams;
  emberStringCommandArgument(-1, &commandLength);
  printMfgString();
  emberAfGetEui64(myEui64);
  emberAfGetNetworkParameters(&nodeTypeResult, &networkParams);
  emberAfAppPrint("node [");
  emberAfAppDebugExec(emberAfPrintBigEndianEui64(myEui64));
  emberAfAppFlush();
  emberAfAppPrintln("] chan [%d] pwr [%d]",
                    networkParams.radioChannel,
                    networkParams.radioTxPower);
  emberAfAppPrint("panID [0x%2x] nodeID [0x%2x] ",
                 networkParams.panId,
                 emberGetNodeId());
  emberAfAppFlush();
  emberAfAppPrint("xpan [0x");
  emberAfAppDebugExec(emberAfPrintBigEndianEui64(networkParams.extendedPanId));
  emberAfAppPrintln("]");
  emberAfAppFlush();

  emAfCliVersionCommand();
  emberAfAppFlush();

  emberAfAppPrint("nodeType [");
  if (nodeTypeResult != 0xFF) {
    emberAfAppPrint("0x%x", nodeTypeResult);
  } else {
    emberAfAppPrint("unknown");
  }
  emberAfAppPrintln("]");
  emberAfAppFlush();

  printSecurityProfile();

  printSmartEnergySecurityInfo();

  emberAfAppPrint("network state [%x] ", emberNetworkState());
  printPacketBuffers();
  emberAfAppFlush();

  // print the endpoint information
  {
    int8u i, j;
    emberAfAppPrintln("Ep cnt: %d", emberAfEndpointCount());
    // loop for each endpoint
    for (i = 0; i < emberAfEndpointCount(); i++) {
      EmberAfEndpointType *et = endpoints[i].endpointType;
      emberAfAppPrint("ep %d [%p] ",
                 emberAfEndpointFromIndex(i),
                 emberAfIsDeviceEnabled(emberAfEndpointFromIndex(i))
                 ? "enabled" 
                 : "disabled");
      emberAfAppPrintln("profile [0x%2x] devId [0x%2x] ver [0x%x]",
                        emberAfProfileIdFromIndex(i),
                        emberAfDeviceIdFromIndex(i),
                        emberAfDeviceVersionFromIndex(i));    
      // loop for the clusters within the endpoint
      for (j = 0; j < et->clusterCount; j++) {
        EmberAfCluster *zc = &(et->cluster[j]);
        emberAfAppPrint("    %p cluster: 0x%2x ", 
                       (emberAfClusterIsClient(zc)
                        ? "out(client)"
                        : "in (server)" ),
                       zc->clusterId);
        emberAfAppDebugExec(emberAfDecodeAndPrintCluster(zc->clusterId));
        emberAfAppPrintln("");
        emberAfAppFlush();
      }
      emberAfAppFlush();
    }
  }
}

void emAfCliEchoCommand(void)
{
  int8u echoOn = (int8u)emberUnsignedCommandArgument(0);
  if ( echoOn ) {
    emberCommandInterpreterEchoOn();
  } else {
    emberCommandInterpreterEchoOff();
  }
}
