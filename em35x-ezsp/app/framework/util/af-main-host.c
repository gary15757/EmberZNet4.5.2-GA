// *******************************************************************
// * af-main-host.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "app/framework/include/af.h"

#include "app/util/serial/serial.h"  // Serial utility APIs

// CLI - command line interface
#include "app/util/serial/command-interpreter2.h"
#include "app/framework/cli/core-cli.h"
#include "app/framework/cli/custom-cli.h"
#include "app/framework/cli/network-cli.h"
#include "app/framework/cli/plugin-cli.h"
#include "app/framework/cli/security-cli.h"
#include "app/framework/cli/zcl-cli.h"
#include "app/framework/cli/zdo-cli.h"
#include "app/framework/plugin/test-harness/test-harness-cli.h"

// ZCL - ZigBee Cluster Library
#include "app/framework/util/attribute-storage.h"
#include "app/framework/util/util.h"
#include "app/framework/util/af-event.h"

// ZDO - ZigBee Device Object
#include "app/util/zigbee-framework/zigbee-device-common.h"
#include "app/util/zigbee-framework/zigbee-device-host.h"

// Service discovery library
#include "service-discovery.h"

// Fragmentation
#include "app/framework/util/fragmentation.h"
#include "app/util/source-route-host.h"

// determines the number of in-clusters and out-clusters based on defines
// in config.h
#include "app/framework/util/af-main.h"

// Needed for zaTrustCenterSecurityInit() and zaNodeSecurityInit()
#include "app/framework/security/af-security.h"


#ifdef GATEWAY_APP
  #define COMMAND_INTERPRETER_SUPPORT
  #include "app/util/gateway/gateway.h"
#endif

#include "app/util/security/security.h"  // Trust Center Address Cache

#include "app/framework/plugin/partner-link-key-exchange/partner-link-key-exchange.h"
#include "app/util/common/library.h"
#include "app/framework/security/crypto-state.h"

#include "app/util/concentrator/concentrator.h"

// This is used to store the local EUI of the NCP when using
// fake certificates.
// Fake certificates are constructed by setting the data to all F's
// but using the device's real IEEE in the cert.  The Key establishment
// code requires access to the local IEEE to do this.
EmberEUI64 emLocalEui64;

// Endpoint index that will be sent next time button0 is pressed.
int8u afEndDevEndpointNextSend = 0;

// APP_SERIAL is set in the project files
int8u serialPort = APP_SERIAL;

static EmberNodeId localId = EMBER_NULL_NODE_ID;

// the stack version that the NCP is running
static int16u ncpStackVer;

// ******************************************************************

// Is the NCP awake?
boolean emNCPIsAwake = FALSE;

// A global used to schedule the polling event
int32u emAfPollIntervalTime = 0;

// Set the default hibernate duration defined by the application header
// provided as a global here so that it can be modified at runtime.
int32u emberAfHibernateDuration = EMBER_AF_LONG_POLL_INTERVAL;

// Set the default nap duration defined by the application header
// provided as a global here so that it can be modified at runtime.
int32u emberAfNapDuration = EMBER_AF_SHORT_POLL_INTERVAL;

// when this is set to TRUE it means the NCP has reported a serious error
// and the host needs to reset and re-init the NCP
boolean ncpNeedsResetAndInit = FALSE;

#if EMBER_AF_SECURITY_PROFILE == NONE_SECURITY_PROFILE
  #define SECURITY_LEVEL 0
#else
  #define SECURITY_LEVEL 5
#endif

#if defined (GATEWAY_APP)
  // Baud rate on the gateway application is meaningless, but we must
  // define it satisfy compilation.
  #define BAUD_RATE BAUD_115200

  // Port 1 on the gateway application is used for CLI, while port 0
  // is used for "raw" binary.  We ignore what was set via App. Builder
  // since only port 1 is used by the application.
  #undef APP_SERIAL
  #define APP_SERIAL 1

#elif (EMBER_AF_BAUD_RATE == 9600)
  #define BAUD_RATE BAUD_9600
#elif (EMBER_AF_BAUD_RATE == 19200)
  #define BAUD_RATE BAUD_19200
#elif (EMBER_AF_BAUD_RATE == 38400)
  #define BAUD_RATE BAUD_38400
#else
  #error EMBER_AF_BAUD_RATE not set
#endif

#define MAX_CLUSTER 58

// We only get the sender EUI callback when the sender EUI is in the incoming
// message. This keeps track of if the value in the variable is valid or not.
// This is set to VALID (TRUE) when the callback happens and set to INVALID
// (FALSE) at the end of IncomingMessageHandler.
static boolean currentSenderEui64IsValid;
static EmberEUI64 currentSenderEui64;
static EmberNodeId currentSender = EMBER_NULL_NODE_ID;

// Forward declarations for sleep functions
void emAfSchedulePollEvent(void);
void emAfCheckForSleep(void);
void emAfFullSleep(int32u sleepDuration);

//------------------------------------------------------------------------------
// Forward declarations

static void platformTick(void);

static EzspStatus createEndpoint(int8u endpoint);

static void storeLowHighInt16u(int8u* contents, int16u value)
{
  contents[0] = LOW_BYTE(value);
  contents[1] = HIGH_BYTE(value);
}

// Because an EZSP call can be expensive in terms of bandwidth,
// we cache the node ID so it can be quickly retrieved by the host.
EmberNodeId emberAfGetNodeId(void)
{
  if (localId == EMBER_NULL_NODE_ID) {
    localId = emberGetNodeId();
  }
  return localId;
}

void emberAfGetMfgString(int8u* returnData)
{
  static int8u mfgString[MFG_STRING_MAX_LENGTH];  // +1 for '\0'
  static boolean mfgStringRetrieved = FALSE;

  if (mfgStringRetrieved == FALSE) {
    ezspGetMfgToken(EZSP_MFG_STRING, mfgString);
    mfgStringRetrieved = TRUE;
  }
  // NOTE:  The MFG string is not NULL terminated.
  MEMCOPY(returnData, mfgString, MFG_STRING_MAX_LENGTH);
}

void afHostRefreshNodeId(void)
{
  localId = EMBER_NULL_NODE_ID;
}

// This is an ineffecient way to generate a random key for the host.
// If there is a pseudo random number generator available on the host,
// that may be a better mechanism. 

EmberStatus generateRandomKey(EmberKeyData* result)
{
  int16u data;
  int8u* keyPtr = emberKeyContents(result);
  int8u i;

  // Since our EZSP command only generates a random 16-bit number,
  // we must call it repeatedly to get a 128-bit random number.

  for ( i = 0; i < 8; i++ ) {
    EmberStatus status = ezspGetRandomNumber(&data);

    if ( status != EMBER_SUCCESS ) {
      return status;
    }

    storeLowHighInt16u(keyPtr, data);
    keyPtr+=2;
  }

  return EMBER_SUCCESS;
}

// Slowly ratchet up the number of available buffers until we no longer can.
static void setPacketBufferCount(void)
{
  int16u value;
  EzspStatus ezspStatus = EZSP_SUCCESS;

  // We start from the default used by the NCP and increase up from there
  // rather than use a hard coded default in the code.
  // This is more portable to different NCP hardware (i.e. 357 vs. 260).
  ezspStatus = ezspGetConfigurationValue(EZSP_CONFIG_PACKET_BUFFER_COUNT,
                                         &value);

  while (ezspStatus == EZSP_SUCCESS) {
    ezspStatus = ezspSetConfigurationValue(EZSP_CONFIG_PACKET_BUFFER_COUNT,
                                           value);
    value++;
  }
  emberAfAppPrintln("Ezsp Config: set packet buffers to %d",
                    value - 1);
  emberAfAppFlush();
}

// initialize the network co-processor (NCP)
void emAfResetAndInitNCP(void)
{
  int8u ep;
  EmberStatus status;
  EzspStatus ezspStatus;

  // Reset the poll interval so the NCP will be
  // instructed to poll if necessary
  emAfPollIntervalTime = 0;

  // ezspInit resets the NCP by calling halNcpHardReset on a SPI host or
  // ashResetNcp on a UART host
  ezspStatus = ezspInit();

  if (ezspStatus != EZSP_SUCCESS) {
    emberAfCorePrintln("ERROR: ezspForceReset 0x%x", ezspStatus);
    emberAfCoreFlush();
    assert(FALSE);
  }

  // send the version command before any other commands
  emAfCliVersionCommand();

  // set the binding table size
  emberAfSetEzspConfigValue(EZSP_CONFIG_BINDING_TABLE_SIZE,
                            EMBER_BINDING_TABLE_SIZE,
                            "binding table size");

  // set the source route table size
  emberAfSetEzspConfigValue(EZSP_CONFIG_SOURCE_ROUTE_TABLE_SIZE,
                            EMBER_SOURCE_ROUTE_TABLE_SIZE,
                            "source route table size");

  emberAfSetEzspConfigValue(EZSP_CONFIG_SECURITY_LEVEL,
                            SECURITY_LEVEL,
                            "security level");

  // set the address table size
  emberAfSetEzspConfigValue(EZSP_CONFIG_ADDRESS_TABLE_SIZE,
                            EMBER_AF_ADDRESS_TABLE_SIZE,
                            "address table size");

  // set the trust center address cache size
  emberAfSetEzspConfigValue(EZSP_CONFIG_TRUST_CENTER_ADDRESS_CACHE_SIZE,
                            EMBER_AF_TRUST_CENTER_ADDRESS_CACHE_SIZE,
                            "TC addr cache");

  // the stack profile is defined in the config file
  emberAfSetEzspConfigValue(EZSP_CONFIG_STACK_PROFILE,
                            EMBER_STACK_PROFILE,
                            "stack profile");

  emberAfSetEzspConfigValue(EZSP_CONFIG_KEY_TABLE_SIZE,
                            EMBER_KEY_TABLE_SIZE,
                            "key table size");

  // allow other devices to modify the binding table
  emberAfSetEzspPolicy(EZSP_BINDING_MODIFICATION_POLICY,
                       EZSP_ALLOW_BINDING_MODIFICATION,
                       "binding modify",
                       "allow");

  // return message tag and message contents in ezspMessageSentHandler()
  emberAfSetEzspPolicy(EZSP_MESSAGE_CONTENTS_IN_CALLBACK_POLICY,
                       EZSP_MESSAGE_TAG_AND_CONTENTS_IN_CALLBACK,
                       "message content in msgSent",
                       "return");

  {
    int8u value[2];
    value[0] = LOW_BYTE(EMBER_AF_INCOMING_BUFFER_LENGTH);
    value[1] = HIGH_BYTE(EMBER_AF_INCOMING_BUFFER_LENGTH);
    emberAfSetEzspValue(EZSP_VALUE_MAXIMUM_INCOMING_TRANSFER_SIZE,
                        2,     // value length
                        value,
                        "maximum incoming transfer size");
    value[0] = LOW_BYTE(EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH);
    value[1] = HIGH_BYTE(EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH);
    emberAfSetEzspValue(EZSP_VALUE_MAXIMUM_OUTGOING_TRANSFER_SIZE,
                        2,     // value length
                        value,
                        "maximum outgoing transfer size");
  }

  emberSetManufacturerCode(EMBER_AF_MANUFACTURER_CODE);

  // Call the Ncp init callback if there is some user-specific stuff to do.
  // BUGZID: 12473, moved above setPacketBufferCount -WEH
  emberAfNcpInitCallback();

  setPacketBufferCount();

#ifdef EMBER_AF_ENABLE_FRAGMENTATION
  emAfFragmentationInit();
#endif //EMBER_AF_ENABLE_FRAGMENTATION

  // create endpoints
  for ( ep = 0; ep < emberAfEndpointCount(); ep++ ) {
    createEndpoint(emberAfEndpointFromIndex(ep));
  }

  // network init if possible - the node type this device was previously
  // needs to match or the device can be a ZC and joined a network as a ZR.
  {
    EmberNodeType nodeType;
    EmberNetworkParameters networkParams;
    status = ezspGetNetworkParameters(&nodeType, &networkParams);
    // if retrieving the network parameters was successful AND either
    // - the node type matches, or
    // - the node wants to be a ZC and was a ZR (this is ok)
    if ((status == EMBER_SUCCESS)
        && ((nodeType == ZA_DEVICE_TYPE)
            || ((nodeType == EMBER_ROUTER)
                && (ZA_DEVICE_TYPE == ZA_COORDINATOR)))) {
      emAfNetworkInit();
    }
  }

  emberAfGetEui64(emLocalEui64);
}

// *******************************************************************
// *******************************************************************
// The main() loop and the application's contribution.

int main( MAIN_FUNCTION_PARAMETERS )
{
  //Initialize the hal
  halInit();
  INTERRUPTS_ON();  // Safe to enable interrupts at this point

  // for Gateway apps init the Gateway CLI
#if defined(GATEWAY_APP)
  if (EMBER_SUCCESS == gatewayInit( MAIN_FUNCTION_ARGUMENTS )) {
    gatewayCommandInterpreterInit(ZA_PROMPT, emberCommandTable);
  } else {
    return 1;
  }
#endif

  emberSerialInit(APP_SERIAL, BAUD_RATE, PARITY_NONE, 1);

  // We must initialize the endpoint information first so
  // that they are correctly added by emAfResetAndInitNCP()
  emberAfEndpointConfigure();

  // initialize the network co-processor (NCP)
  emAfResetAndInitNCP();

  // Main init callback
  emberAfMainInitCallback();

  // initialize the ZCL Utilities
  emberAfInit();

#if ZA_DEVICE_TYPE == ZA_COORDINATOR
  // Always do this on boot to assure that the correct security policies
  // are in place.
  zaTrustCenterSecurityPolicyInit();
#endif

  emberAfInterpanInitCallback();

  emberCommandReaderInit();

  // main loop
  while(TRUE) {
    halResetWatchdog();   // Periodically reset the watchdog.

    // see if the NCP has anything waiting to send us
    ezspTick();

    while (ezspCallbackPending()) {
      ezspSleepMode = EZSP_FRAME_CONTROL_IDLE;
      ezspCallback();
      // BUGZID: 12692 callback may generate response need to send if one waiting 
      if (emberAfResponseWaitingFlag) {
        emberAfSendResponse();
      }
    }

    // check if we have hit an EZSP Error and need to reset and init the NCP
    if (ncpNeedsResetAndInit) {
      ncpNeedsResetAndInit = FALSE;
      // re-initialize the NCP
      emAfResetAndInitNCP();
    }

    // Wait until ECC operations are done.  Don't allow any of the clusters
    // to send messages as the NCP is busy doing ECC
    if (emAfIsCryptoOperationInProgress()) {
      continue;
    }

    // let the ZCL Utils run - this should go after ezspTick
    emberAfTick();

    // Give the platform code a chance to service its events
    platformTick();

    emberAfRunEvents();

    if (emberProcessCommandInput(APP_SERIAL)) {
#if !defined GATEWAY_APP      
      // Gateway app. has its own way of handling the command-line prompt.
      emberAfGuaranteedPrint("%p>", ZA_PROMPT);
#endif
    }

#ifdef DEBUG
    // Needed for buffered serial, which debug uses
    emberSerialBufferTick();
#endif //DEBUG
  }
  return 0;
}

void emberConcentratorRouteDiscoverySentHandler(void) {}

static void platformTick(void)
{
  static int16u lastBlinkTime = 0;
  int16u time;

#if defined(ZA_DEVICE_IS_SLEEPY) || defined(ZA_DEVICE_IS_NONSLEEPY_END_DEVICE)
    emAfSchedulePollEvent();
#ifdef ZA_DEVICE_IS_SLEEPY
    emAfCheckForSleep();
#endif //ZA_DEVICE_IS_SLEEPY
#endif

  time = halCommonGetInt16uMillisecondTick();

  // The casting is necessary here to prevent an overflow.
  if ( elapsedTimeInt16u(lastBlinkTime, time) > 200 /*ms*/) {
    // blink the LED
    emAfBlinkHeartbeat();
    lastBlinkTime = time;

#ifdef EMBER_AF_CONCENTRATOR
    emberConcentratorTick();
#endif //EMBER_AF_CONCENTRATOR

#ifdef EMBER_AF_USE_BUTTONS
    // **************************************
    // check the buttons for activity
    // button 0: if not joined: FORM if the device is capable of forming
    //           if joined: BIND (send ZDO end dev bind req)
    // button 1: if not joined: JOIN
    //           if joined: PERMIT JOINING
    // **************************************
    if (emberAfFirstButtonPressed) {
      emberAfFirstButtonPressed = FALSE;

      if (emberNetworkState() == EMBER_JOINED_NETWORK) {
        // bind
        emberAfZdoPrintln("End device binding:%x", afEndDevEndpointNextSend);
        emberAfSendEndDeviceBind(emberAfEndpointFromIndex(afEndDevEndpointNextSend++));
        if (afEndDevEndpointNextSend >= emberAfEndpointCount()) {
          afEndDevEndpointNextSend = 0;
        }
      } else if (emberNetworkState() == EMBER_NO_NETWORK) {
#if (ZA_DEVICE_TYPE == ZA_COORDINATOR)
        // form
        zaTrustCenterSecurityInit();
        emberAfCorePrintln("%p: nwk down: do form", "button0");
        emberAfFindUnusedPanIdAndForm();
#else
        emberAfCorePrintln("%p: only coordinator can form", "button0");
#endif
      }
    }
    if (emberAfSecondButtonPressed) {
      emberAfSecondButtonPressed = FALSE;

      if (emberNetworkState() == EMBER_JOINED_NETWORK) {
        // permit join
        emberAfCorePrint("%p: ", "button1");
        emAfPermitJoin(60);
      } else if (emberNetworkState() == EMBER_NO_NETWORK) {
        zaNodeSecurityInit();
        emberAfStartSearchForJoinableNetwork();
        emberAfCorePrintln("%p: join", "button1");
      }
    }
#endif //EMBER_AF_USE_BUTTONS
  }
}

#ifdef ZA_DEVICE_IS_SLEEPY
void emAfCheckForSleep(void)
{
  // after sleeping, sleepDuration is how long the device actually slept
  int32u sleepDurationMS = 0;

#ifdef EMBER_AF_STAY_AWAKE_WHEN_NOT_JOINED
  if (emberNetworkState() != EMBER_JOINED_NETWORK)
    return;
#endif //EMBER_AF_STAY_AWAKE_WHEN_NOT_JOINED

  // If all subsystems used events to fire their actions, 
  // we wouldn't have to limit our sleep when !ok to hibernate.
  // Unfortunately Key Establishment
  // still needs to be serviced like a tick when holding 
  // us out of hibernation so during KE we have to make sure
  // that we wake on the short poll interval event though the host
  // is not responsible for polling. 
  if (emberAfOkToHibernate())
    sleepDurationMS = emberAfMsToNextEvent(MAX_TIMER_MILLISECONDS_HOST);
  else if (emberAfOkToNap())
    sleepDurationMS = emberAfMsToNextEvent(emberAfNapDuration * 
      MILLISECOND_TICKS_PER_QUARTERSECOND);
  else
    return;
  
  if (sleepDurationMS > 0)
    emAfFullSleep(sleepDurationMS);
}

void emAfFullSleep(int32u sleepDurationMS)
{
  EmberStatus status;
  int32u time = halCommonGetInt32uMillisecondTick();
  int32u elapsedSleepTimeMS;
  int8u timerUnit;
  int16u timerDuration;
  int32u timerDurationMS;

  // Get the proper timer duration and units we will use to set our
  // wake timer on the NCP. We are basically converting MS to 
  // MS, QS or minutes.
  emAfGetTimerDurationAndUnitFromMS(sleepDurationMS, &timerDuration, &timerUnit);
  
  // Translate back to MS so that we call the PreGoToSleepCallback
  // with the accurate MS (corrected for rounding due to units)
  timerDurationMS = emAfGetMSFromTimerDurationAndUnit(timerDuration, timerUnit);

  // a final check with the app if we can go to sleep
  if (emberAfPreGoToSleepCallback(timerDurationMS)) {
    return; // User app says don't go to sleep.
  }

  emberAfDebugPrintln("EVENT: atmpt sleep for 0x%4x MS...",
		     timerDurationMS);
  emberAfDebugFlush();
  
  // If we have anything waiting in the queue send it
  // before we sleep
  emberSerialWaitSend(EMBER_AF_PRINT_OUTPUT);

  // set the variable that will instruct the stack to sleep after
  // processing the next EZSP command
  ezspSleepMode = EZSP_FRAME_CONTROL_DEEP_SLEEP;

  // Set timer on NCP so we get woken up, this call will
  // also put the NCP to sleep due to sleep mode setting above.
  status = ezspSetTimer(0, timerDuration, timerUnit, FALSE);

  // check that we were able to set the timer and that an
  // ezsp error was not received in the call.
  if (status == EMBER_SUCCESS && !ncpNeedsResetAndInit) {
  
    // setting awake flag to false since NCP is sleeping.
    emNCPIsAwake = FALSE;
    // this disables interrupts and reenables them once it completes
    ATOMIC(
      halPowerDown();  // turn off board and peripherals
      // Use maintain timer so that we can accurately
      // measure how long we have actually slept and don't
      // have to manage the system time.
      halSleep(SLEEPMODE_MAINTAINTIMER);
      halPowerUp();   // power up board and peripherals
    );
  } else {
    emberAfDebugPrintln("setTimer fail: 0x%x", status);
    emberAfDebugFlush();
  }

  // Make sure the NCP is awake since the host could have been waken up via
  // other external interrupt like button press.  If it's not then wake it.
  if (emNCPIsAwake == FALSE) {
    ezspWakeUp();
    do { } while (emNCPIsAwake == FALSE);
  }

  ezspSleepMode = EZSP_FRAME_CONTROL_IDLE;

  // Get the amount of time that has actually ellapsed since we went to sleep
  elapsedSleepTimeMS = elapsedTimeInt32u(time, halCommonGetInt32uMillisecondTick());

  // Inform the application how long we slept
  emberAfPostWakeUpCallback(elapsedSleepTimeMS);

  emberAfDebugPrintln("wakeup");
  emberAfDebugFlush();
}
#endif //ZA_DEVICE_IS_SLEEPY


// ******************************************************************
// binding
// ******************************************************************
EmberStatus emberAfSendEndDeviceBind(int8u endpoint)
{
  EmberStatus status;
  EmberEUI64 eui;
  int8u inClusterCount, outClusterCount;
  EmberAfClusterId clusterList[MAX_CLUSTER];
  EmberAfClusterId *inClusterList;
  EmberAfClusterId *outClusterList;
  EmberAfProfileId profileId;
  EmberApsOption options = ((EMBER_AF_DEFAULT_APS_OPTIONS
                             | EMBER_APS_OPTION_SOURCE_EUI64)
                            & ~EMBER_APS_OPTION_RETRY);
  int8u index = emberAfIndexFromEndpoint(endpoint);
  if (index == 0xFF) {
    return EMBER_INVALID_ENDPOINT;
  }

  emberAfGetEui64(eui);

  emberAfZdoPrintln("send %x %2x ", endpoint, options);
  inClusterList = clusterList;
  inClusterCount = emberAfGetClustersFromEndpoint(endpoint, inClusterList, MAX_CLUSTER, TRUE);
  outClusterList = clusterList + inClusterCount;
  outClusterCount = emberAfGetClustersFromEndpoint(endpoint, outClusterList, (MAX_CLUSTER - inClusterCount), FALSE);
  profileId = emberAfProfileIdFromIndex(index);

  status = ezspEndDeviceBindRequest(emberGetNodeId(),
                                    eui, 
                                    endpoint,
                                    profileId,
                                    inClusterCount,              // cluster in count
                                    outClusterCount,              // cluster out count
                                    inClusterList,     // list of input clusters
                                    outClusterList,    // list of output clusters
                                    options); 
  emberAfZdoPrintln("done: %x.", status);
  return status;
}

// **********************************************************************
// this function sets an EZSP config value and prints out the results to
// the serial output
// **********************************************************************
EzspStatus emberAfSetEzspConfigValue(EzspConfigId configId,
                                     int16u value,
                                     PGM_P configIdName)
{

  EzspStatus ezspStatus = ezspSetConfigurationValue(configId, value);
  emberAfAppPrint("Ezsp Config: set %p to 0x%2x:", configIdName, value);
  emberAfAppFlush();

  emberAfAppDebugExec(emAfPrintStatus("set", ezspStatus));
  emberAfAppPrintln("");
  emberAfAppFlush();
  return ezspStatus;
}


// **********************************************************************
// this function sets an EZSP policy and prints out the results to
// the serial output
// **********************************************************************
EzspStatus emberAfSetEzspPolicy(EzspPolicyId policyId,
                                EzspDecisionId decisionId,
                                PGM_P policyName,
                                PGM_P decisionName)
{
  EzspStatus ezspStatus = ezspSetPolicy(policyId,
                                        decisionId);
  emberAfAppPrint("Ezsp Policy: set %p to \"%p\":",
                 policyName, 
                 decisionName);
  emberAfAppDebugExec(emAfPrintStatus("set",
                                      ezspStatus));
  emberAfAppPrintln("");
  emberAfAppFlush();
  return ezspStatus;
}

// **********************************************************************
// this function sets an EZSP value and prints out the results to
// the serial output
// **********************************************************************
EzspStatus emberAfSetEzspValue(EzspValueId valueId,
                               int8u valueLength,
                               int8u *value,
                               PGM_P valueName)

{
  EzspStatus ezspStatus = ezspSetValue(valueId, valueLength, value);
  int32u promotedValue;
  if (valueLength <= 4) {
    promotedValue = (int32u)(*value);
  }
  emberAfAppPrint("Ezsp Value : set %p to ", valueName);

  // print the value based on the length of the value
  switch (valueLength){
  case 1:
  case 2:
  case 4:
    emberAfAppPrint("0x%4x:", promotedValue);
    break;
  default:
    emberAfAppPrint("{val of len %x}:", valueLength);
  }

  emberAfAppDebugExec(emAfPrintStatus("set", ezspStatus));
  emberAfAppPrintln("");
  emberAfAppFlush();
  return ezspStatus;
}

// ******************************************************************
// setup endpoints and clusters for responding to ZDO requests
// ******************************************************************

//
// Creates the endpoint for 260 by calling ezspAddEndpoint()
//
static EzspStatus createEndpoint(int8u endpoint) {
  EzspStatus status;
  EmberAfCluster *cluster;

  int16u clusterList[MAX_CLUSTER];
  int16u *inClusterList;
  int16u *outClusterList;

  int8u inClusterCount;
  int8u outClusterCount;

  int8u i, endpointIndex;

  // Lay out clusters in the arrays.
  inClusterList = clusterList;
  inClusterCount = emberAfGetClustersFromEndpoint(endpoint, inClusterList, MAX_CLUSTER, TRUE);

  outClusterList = clusterList + inClusterCount;
  outClusterCount = emberAfGetClustersFromEndpoint(endpoint, outClusterList, (MAX_CLUSTER - inClusterCount), FALSE); 
  endpointIndex = emberAfIndexFromEndpoint(endpoint);

  // Call EZSP function with data.
  status = ezspAddEndpoint(endpoint,
                           emberAfProfileIdFromIndex(endpointIndex),
                           emberAfDeviceIdFromIndex(endpointIndex),
                           emberAfDeviceVersionFromIndex(endpointIndex),
                           inClusterCount,
                           outClusterCount,
                           (int16u *)inClusterList,
                           (int16u *)outClusterList);

  if (status != EZSP_SUCCESS) {
    emberAfAppPrintln("Error in creating endpoint %d: 0x%x", endpoint, status);
  } else {
    emberAfAppPrintln("Ezsp Endpoint %d added, profile 0x%2x, in clusters: %d, out clusters %d",
                      endpoint,
                      emberAfProfileIdFromIndex(endpointIndex),
                      inClusterCount,
                      outClusterCount);
  }
  return status;
}


// *******************************************************************
// Handlers required to use the Ember Stack.

// Called when the stack status changes, usually as a result of an
// attempt to form, join, or leave a network.
void ezspStackStatusHandler(EmberStatus status)
{
  emAfStackStatusHandler(status);
}

EmberNodeId emberGetSender(void)
{
  return currentSender;
}

// This is not called if the incoming message did not contain the EUI64 of
// the sender.
void ezspIncomingSenderEui64Handler(EmberEUI64 senderEui64)
{
  // current sender is now valid
  MEMCOPY(currentSenderEui64, senderEui64, EUI64_SIZE);
  currentSenderEui64IsValid = TRUE;
}

EmberStatus emberGetSenderEui64(EmberEUI64 senderEui64)
{
  // if the current sender EUI is valid then copy it in and send it back
  if (currentSenderEui64IsValid) {
    MEMCOPY(senderEui64, currentSenderEui64, EUI64_SIZE);
    return EMBER_SUCCESS;
  }
  // in the not valid case just return error
  return EMBER_ERR_FATAL;
}

//
// ******************************************************************

void ezspIncomingMessageHandler(EmberIncomingMessageType type,
                                EmberApsFrame *apsFrame,
                                int8u lastHopLqi,
                                int8s lastHopRssi,
                                EmberNodeId sender,
                                int8u bindingIndex,
                                int8u addressIndex,
                                int8u messageLength,
                                int8u *messageContents)
{
  currentSender = sender;
  emAfIncomingMessageHandler(type,
                             apsFrame,
                             lastHopLqi,
                             lastHopRssi,
                             sender,
                             bindingIndex,
                             addressIndex,
                             messageLength,
                             messageContents);
  currentSenderEui64IsValid = FALSE;
  currentSender = EMBER_NULL_NODE_ID;
}

// Called when a message we sent is acked by the destination or when an
// ack fails to arrive after several retransmissions.
void ezspMessageSentHandler(EmberOutgoingMessageType type,
                            int16u indexOrDestination,
                            EmberApsFrame *apsFrame,
                            int8u messageTag,
                            EmberStatus status,
                            int8u messageLength,
                            int8u *messageContents)
{
#ifdef EMBER_AF_ENABLE_FRAGMENTATION
  if (emAfFragmentationMessageSent(apsFrame, status)) {
    return;
  }
#endif //EMBER_AF_ENABLE_FRAGMENTATION

  emAfMessageSentHandler(type,
                         indexOrDestination,
                         apsFrame,
                         status,
                         messageLength,
                         messageContents);
}

#if defined(ZA_DEVICE_IS_NONSLEEPY_END_DEVICE) || defined(ZA_DEVICE_IS_SLEEPY)
void emAfSchedulePollEvent(void) {
  int32u pollTime = 0;
  EmberStatus status;

#ifdef ZA_DEVICE_IS_SLEEPY
  if (emberAfOkToHibernate())
    pollTime = emberAfHibernateDuration;
  else
    pollTime = emberAfNapDuration;
#else
  pollTime = emberAfHibernateDuration;
#endif //ZA_DEVICE_IS_SLEEPY

  if (emAfPollIntervalTime != pollTime)
  {
    emberAfCorePrintln("ezspPollForData: %4x QS", pollTime);
    emberAfCoreFlush();

    status = ezspPollForData(pollTime,
                             EMBER_EVENT_QS_TIME,
                             EMBER_AF_NUM_MISSED_POLLS_TO_TRIGGER_MOVE);
    if (status != EMBER_SUCCESS) {
      emberAfCorePrintln("poll: 0x%x", status);
      emberAfCoreFlush();
    }
    emAfPollIntervalTime = pollTime;  
  }
}

void emberAfEzspPollCompleteHandler(EmberStatus status)
{
#ifdef ZA_DEVICE_IS_SLEEPY
  switch (status) {
  case EMBER_SUCCESS:
    emberAfDebugPrintln("poll: got data");
    break;
    // this status won't normally be called, see comment for case EMBER_SUCCESS
  case EMBER_MAC_NO_DATA:
    emberAfDebugPrintln("poll: no data");
    break;
  case EMBER_DELIVERY_FAILED:
    emberAfDebugPrintln("poll: failed to send");
    break;
  case EMBER_MAC_NO_ACK_RECEIVED:
    {
      // If we are performing key establishment, we can ignore this
      // since the parent could go away for long periods of time while
      // doing ecc processes.
      if (emberAfPerformingKeyEstablishment())
        break;
      emberAfStartMove();
    }
    break;
  default:
    emberAfDebugPrintln("unknown status: 0x%x", status);
  }
#endif //ZA_DEVICE_IS_SLEEPY
}
#else 
void emberAfEzspPollCompleteHandler(EmberStatus status) {}
#endif//defined(ZA_DEVICE_IS_NONSLEEPY_END_DEVICE) || defined(ZA_DEVICE_IS_SLEEPY)

void emberChildJoinHandler(int8u index, boolean joining)
{}

void scanError(EmberStatus status)
{
  emberAfAppPrintln("Scan error 0x%x", status);
}


void halNcpIsAwakeIsr(boolean isAwake)
{
  emNCPIsAwake = isAwake;
}

// This is called when an EZSP error is reported
void ezspErrorHandler(EzspStatus status)
{
  emberAfCorePrintln("ERROR: ezspErrorHandler 0x%x", status);
  emberAfCoreFlush();

  // Rather than detect whether or not we can recover from the error,
  // we just flag the NCP for reboot.
  ncpNeedsResetAndInit = TRUE;
}

// ******************************************************************
// the application implements the send functions for the CLI and the
// ZCL utils. The sending is different for different platforms so
// this needs to be done in the application and not the libraries.
// ******************************************************************

// function for sending a multicast
EmberStatus emberAfSendMulticast(EmberMulticastId multicastId,
                                 EmberApsFrame *apsFrame,
                                 int16u messageLength,
                                 int8u *message)
{
  EmberStatus status = emAfProcessOutgoingMessage(EMBER_OUTGOING_MULTICAST,
                                                  multicastId,
                                                  apsFrame,
                                                  messageLength,
                                                  message);
  if (status == EMBER_SUCCESS) {
    status = ezspSendMulticast(apsFrame,
                               ZA_MAX_HOPS, // radius
                               ZA_MAX_HOPS, // nonmemberRadius
                               0,           // message tag - not used
                               (int8u)messageLength,
                               message,
                               &apsFrame->sequence);
  }
  emAfProcessSendStatus(EMBER_OUTGOING_MULTICAST,
                        multicastId,
                        apsFrame,
                        status,
                        messageLength,
                        message);
  return status;
}

// function for sending a broadcast
EmberStatus emberAfSendBroadcast(EmberNodeId destination,
                                 EmberApsFrame *apsFrame,
                                 int16u messageLength,
                                 int8u *message)
{
  EmberStatus status = emAfProcessOutgoingMessage(EMBER_OUTGOING_BROADCAST,
                                                  destination,
                                                  apsFrame,
                                                  messageLength,
                                                  message);
  if (status == EMBER_SUCCESS) {
    status = ezspSendBroadcast(destination,
                               apsFrame,
                               ZA_MAX_HOPS, // radius
                               0,           // message tag - not used
                               (int8u)messageLength,
                               message,
                               &apsFrame->sequence);
  }
  emAfProcessSendStatus(EMBER_OUTGOING_BROADCAST,
                        destination,
                        apsFrame,
                        status,
                        messageLength,
                        message);
  return status;
}

// function for sending a unicast
EmberStatus emberAfSendUnicast(EmberOutgoingMessageType type,
                               int16u indexOrDestination,
                               EmberApsFrame *apsFrame,
                               int16u messageLength,
                               int8u *message)
{
  EmberStatus status = emAfProcessOutgoingMessage(type,
                                                  indexOrDestination,
                                                  apsFrame,
                                                  messageLength,
                                                  message);
  if (status == EMBER_SUCCESS) {
#ifdef EZSP_APPLICATION_HAS_ROUTE_RECORD_HANDLER
    int16u relayList[ZA_MAX_HOPS];
    int8u relayCount;
    if (emberFindSourceRoute(indexOrDestination, &relayCount, relayList)) {
      status = ezspSetSourceRoute(indexOrDestination, relayCount, relayList);
      if (status != EMBER_SUCCESS) {
        status = EMBER_SOURCE_ROUTE_FAILURE;
        goto kickout;
      }
    }
#endif
    status = ezspSendUnicast(type,
                             indexOrDestination,
                             apsFrame,
                             0, // message tag - not used
                             (int8u)messageLength,
                             message,
                             &apsFrame->sequence);
#ifdef EMBER_AF_ENABLE_FRAGMENTATION
  } else if (status == EMBER_MESSAGE_TOO_LONG) {
    status = emAfFragmentationSendUnicast(type,
                                          indexOrDestination,
                                          apsFrame,
                                          message,
                                          messageLength);
    emberAfDebugPrintln("%pstart:len=%d.", "Fragmentation:", messageLength);
#endif
  }
  goto kickout; // silence a warning when not using source routing
kickout:
  emAfProcessSendStatus(type,
                        indexOrDestination,
                        apsFrame,
                        status,
                        messageLength,
                        message);
  return status;
}

// Platform dependent interface to get various stack parameters. 
void emberAfGetEui64(EmberEUI64 returnEui64)
{
  // We cache the EUI64 of the NCP since it never changes.
  static boolean validEui64 = FALSE;
  static EmberEUI64 myEui64;

  if (validEui64 == FALSE) {
    ezspGetEui64(myEui64);
    validEui64 = TRUE;
  }
  MEMCOPY(returnEui64, myEui64, EUI64_SIZE);
}

void emberAfGetNetworkParameters(EmberNodeType* nodeType, 
                                 EmberNetworkParameters* parameters)
{
  ezspGetNetworkParameters(nodeType, parameters);
}

int8u emberAfGetSecurityLevel(void)
{
  int16u level = 0xFFFF;
  // Assume that if this function fails the "level" will not be written.
  ezspGetConfigurationValue(EZSP_CONFIG_SECURITY_LEVEL, &level);
  return (int8u)level;
}

int8u emberAfGetKeyTableSize(void)
{
  static int16u size = 0xFFFF;
  // We cache the value of the key table size to reduce EZSP calls.
  if (size == 0xFFFF
      && EZSP_SUCCESS != ezspGetConfigurationValue(EZSP_CONFIG_KEY_TABLE_SIZE,
                                                   &size)) {
    // We return a 0 size on error to prevent code from using the invalid
    // value of 0xFFFF.  This is particularly necessary for loops that
    // iterate over all indexes.
    return 0;
  }
  return (int8u)size;
}

// On the System-on-a-chip this function is provided by the stack.
// Here is a copy for the host based applications.
void emberReverseMemCopy(int8u* dest, const int8u* src, int16u length)
{
  int16u i;
  int16u j = (length - 1);
  
  for( i = 0; i < length; i++) {
    dest[i] = src[j];
    j--;
  }
}

// ******************************************************************
// Functions called by the Serial Command Line Interface (CLI)
// ******************************************************************

// *****************************
// emAfCliVersionCommand
//
// version <no arguments>
// *****************************
void emAfCliVersionCommand(void)
{
  // Note that NCP == Network Co-Processor

  // the EZSP protocol version that the NCP is using
  int8u ncpEzspProtocolVer;

  // the stackType that the NCP is running 
  int8u ncpStackType;

  // the EZSP protocol version that the Host is running
  // we are the host so we set this value
  int8u hostEzspProtocolVer = EZSP_PROTOCOL_VERSION;

  // send the Host version number to the NCP. The NCP returns the EZSP
  // version that the NCP is running along with the stackType and stackVersion
  ncpEzspProtocolVer = ezspVersion(hostEzspProtocolVer, 
                                   &ncpStackType, 
                                   &ncpStackVer);  
  
  // verify that the stack type is what is expected
  if (ncpStackType != EZSP_STACK_TYPE_MESH) {
    emberAfAppPrint("ERROR: stack type 0x%x is not expected!", 
                   ncpStackType);
    assert(FALSE);
  }

  // verify that the NCP EZSP Protocol version is what is expected
  if (ncpEzspProtocolVer != EZSP_PROTOCOL_VERSION) {
    emberAfAppPrint("ERROR: NCP EZSP protocol version of 0x%x does not match Host version 0x%x\r\n", 
                   ncpEzspProtocolVer, 
                   hostEzspProtocolVer);
    assert(FALSE);
  }

  emberAfAppPrint("ezsp ver 0x%x stack type 0x%x stack ver 0x%2x\r\n", 
                 ncpEzspProtocolVer, ncpStackType, ncpStackVer);
  emberAfAppFlush();
}

void emAfCopyCounterValues(int16u* counters)
{
  ezspReadAndClearCounters(counters); 
}

int8u emAfGetPacketBufferFreeCount(void)
{
  int8u freeCount;
  int8u valueLength;
  ezspGetValue(EZSP_VALUE_FREE_BUFFERS,
               &valueLength,
               &freeCount);
  return freeCount;
}

int8u emAfGetPacketBufferTotalCount(void)
{
  int16u value;
  ezspGetConfigurationValue(EZSP_CONFIG_PACKET_BUFFER_COUNT, 
                            &value);
  return (int8u)value;
}

EmberCommandEntry emberCommandTable[] = {
#ifndef ZA_NO_REPORTING_OPTIMIZATION
  {"add-report-entry", emAfCliAddReportEntryCommand,     "vuuvvuuvvb"},
#endif //ZA_NO_REPORTING_OPTIMIZATION
  {"bsend",            emAfCliBsendCommand,              "u"},
#if (defined(ZCL_USING_KEY_ESTABLISHMENT_CLUSTER_CLIENT) \
     && defined(ZCL_USING_KEY_ESTABLISHMENT_CLUSTER_SERVER))
  {"cbke",             NULL,                             (PGM_P)cbkeCommands},
#endif
  {"cha",              NULL,                             (PGM_P)changeKeyCommands},
#ifdef EMBER_AF_PLUGIN_DRLC
  {"clear_events",     emAfCliClearEventsCommand,        ""},
#endif //EMBER_AF_PLUGIN_DRLC
#ifdef EMBER_CALLBACK_CUSTOM_CLI_COMMAND
  {"custom",           emberAfCustomCommandLineCallback, "?"},
#endif //EMBER_CALLBACK_CUSTOM_CLI_COMMAND
#ifdef EMBER_AF_PRINT_ENABLE
  {"debugprint",       NULL,                             (PGM_P)debugPrintCommands},
#endif //EMBER_AF_PRINT_ENABLE
  {"interpan",         NULL,                             (PGM_P)interpanCommands},
  {"keys",             NULL,                             (PGM_P)keysCommands},
  {"network",          NULL,                             (PGM_P)networkCommands}, // from network-cli.c
  {"option",           NULL,                             (PGM_P)optionCommands},
#ifdef EMBER_AF_PRINT_ENABLE
  {"print",            NULL,                             (PGM_P)printCommands},
#endif //EMBER_AF_PRINT_ENABLE
  {"raw",              emAfCliRawCommand,                "vb"},
  {"read",             emAfCliReadCommand,               "uvvu"},
  {"send",             emAfCliSendCommand,               "vuu"},
  {"send_multicast",   emAfCliSendCommand,               "vuu"},
  {"time",             emAfCliTimesyncCommand,           "vuu"},
  {"write",            emAfCliWriteCommand,              "uvvuub"},
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
  {"version",          emAfCliVersionCommand,            ""},
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
  {"zcl",              NULL,                             (PGM_P)zclCommands}, // from zcl-cli.c
  EMBER_AF_PLUGIN_COMMANDS
  EMBER_AF_CORE_COMMANDS
#ifndef EMBER_AF_CLI_DISABLE_INFO
  EMBER_AF_INFO_COMMAND
#endif
  KEY_UPDATE_COMMANDS
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
  LIBRARY_COMMANDS // Defined in app/util/common/library.h
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
  ZDO_COMMANDS
  CUSTOM_COMMANDS

  TEST_HARNESS_CLI_COMMANDS

  {NULL,               NULL,                             NULL}, // terminator
};
