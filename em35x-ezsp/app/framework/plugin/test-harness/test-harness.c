// *****************************************************************************
// * key-establishment-test-harness.c
// *
// *  Test harness code for validating the behavior of the key establishment
// *  cluster and modifying the normal behavior of App. Framework.
// *
// * Copyright 2011 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

// this file contains all the common includes for clusters in the zcl-util
#include "app/framework/include/af.h"
#include "app/framework/util/common.h"
#include "app/framework/util/util.h"
#include "app/util/serial/command-interpreter2.h"

#include "app/framework/plugin/key-establishment/key-establishment.h"
#include "test-harness.h"
#include "test-harness-cli.h"

#if !defined(EZSP_HOST)
  #include "stack/include/cbke-crypto-engine.h"
#endif

//------------------------------------------------------------------------------
// Globals

typedef int8u TestHarnessMode;

#define MODE_NORMAL           0
#define MODE_CERT_MANGLE      1
#define MODE_OUT_OF_SEQUENCE  2
#define MODE_NO_RESOURCES     3
#define MODE_TIMEOUT          4
#define MODE_DELAY_CBKE       5
#define MODE_DEFAULT_RESPONSE 6

static PGM_P modeText[] = {
  "Normal",
  "Cert Mangle",
  "Out of Sequence",
  "No Resources",
  "Cause Timeout",
  "Delay CBKE operation",
  "Default Response",
};

static TestHarnessMode testHarnessMode = MODE_NORMAL;
static int8u respondToCommandWithOutOfSequence = ZCL_INITIATE_KEY_ESTABLISHMENT_REQUEST_COMMAND_ID;
static int8s certLengthMod = 0;

#define CERT_MANGLE_NONE    0
#define CERT_MANGLE_LENGTH  1
#define CERT_MANGLE_ISSUER  2
#define CERT_MANGLE_CORRUPT 3

static PGM_P certMangleText[] = {
  "None",
  "Mangle Length",
  "Rewrite Issuer",
  "Corrupt Cert",
};

typedef int8u CertMangleType;

static CertMangleType certMangleType = CERT_MANGLE_NONE;

// Offset from start of ZCL header
//   - ZCL overhead (3 bytes)
//   - KE suite (2 bytes)
//   - Ephemeral Data Generate Time (1 byte)
//   - Confirm Key Generate Time (1 byte)
#define CERT_OFFSET_IN_INITIATE_KEY_ESTABLISHMENT_MESSAGE (3 + 2 + 1 + 1)

// Public Key Reconstruction Data (22 bytes)
// Subject (8 bytes)
#define ISSUER_OFFSET_IN_CERT (22 + 8)

// The test spec says to mangle the issuer to be 0102030405060708
static int8u invalidIssuer[] = {
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
};


// Command List
//
//   test-harness status 
//     Prints the current mode of the test harness.

//   test-harness aps-sec-for-clust on <clusterID>
//   test-harness aps-sec-for-clust off
//     This turns on/off that the specified cluster
//     requires APS security. This does not override the normal
//     rules by the SE profile for security.  It simply supplements
//     the rules with one additional cluster that requires APS security.

//   test-harness registration <on|off>
//     Turns on/off automatic Smart Energy Registration after joining or 
//     reboot.  Default is on.

//   test-harness ke normal-mode
//     Sets normal mode for key establishment on the test harness, which 
//     suppresses any bad behavior and allows normal KE operation.

//   test-harness ke no-resources
//     The device will send a "Terminate Key Estabilshment Message (No resources)"
//     in response to any attempt to initiate KE with it.  As a client, it will send
//     a Terminate message after receiving the Initiate Key establishment response.

//   test-harness ke default-resp
//     The device will send a "Default Response (Failure)" in response to any attempt
//     to initiate KE with it.  As a client, it will send
//     a Default Response after receiving the Initiate Key establishment response.

//   test-harness out-of-sequence <id>
//     This command will send an out-of-sequence message during key establishment.
//     It will look for the local device to send the command with the passed 'ID'
//     and will send a different command ID.  So if the outgoing command is 
//     Initiate KE (ID 0) and the passed ID = 0, then it will send an Ephemeral
//     Data Command (ID 1) instead.

//   test-harness ke timeout
//     This command will induce a timeout by dropping the outgoing message
//     instead of sending it.  This will occur for every command, except
//     when the device is a KE client sending the first message.  In that case
//     it will induce a timeout on the second message (ephemeral data request).

//   test-harness ke delay-cbke <delay-time-seconds>   <advertised-delay-seconds>
//     This command causes the test harness to introduce artificial delays
//     to the ephemeral key and confirm key generation time.  It will delay
//     generation by 'delay-time-seconds' so it takes longer than normal.
//     Thus the ephemeral data request/response message will be delayed.
//     The 'advertised-delay-seconds' is the amount of time that the local
//     device tells the partner it will take them (in the Initiate KE message).  
//     If the delay-time-seconds <= advertised-delay-seconds, then key 
//     establishment should complete successfully but just be delayed.  If 
//     delay-time-seconds > advertised-delay-seconds then the partner device
//     should timeout the operation as the local device will take longer than
//     expected.  However the local device will still send the ephemeral data 
//     message in an attempt to continue key establishment.  It is expected 
//     that the partner will reject this attempt and send back a Terminate 
//     message.

//   test-harness ke cert-mangle length <signed-length>
//     This will modify the initiate key establishment message length by +/-
//     'signed-length' bytes.

//   test-harness ke cert-mangle issuer <new-issuer-value>
//     This will rewrite the issuer field of the certificate with the 
//     'new-issuer-value' when the initiate key establishment message
//     is sent out.

//   test-harness ke cert-mangle corrupt <index>
//     This will rewrite the 'index' byte of the certificate field of the
//     initiate key establishment message to corrupt the certificate.
//     It will bit-flip the 'index' byte to change its value.

static void setMode(void);
static void setCertMangleType(void);
static void delayEphemeral(void);
static void printStatus(void);
static void setRegistration(void);
static void setApsSecurityForCluster(void);

static EmberCommandEntry certMangleCommands[] = {
  { "length",  setCertMangleType,   "s" },
  { "issuer",  setCertMangleType,   "b" },
  { "corrupt", setCertMangleType,   "u" },
  { NULL },
};

static EmberCommandEntry registrationCommands[] = {
  { "on",  setRegistration, "" },
  { "off", setRegistration, "" },
  { NULL },
};

static EmberCommandEntry apsSecurityForClusterCommands[] = {
  { "on",  setApsSecurityForCluster, "v" },
  { "off", setApsSecurityForCluster, ""  },
  { NULL }, 
};

static EmberCommandEntry keyEstablishmentCommands[] = {
  { "normal-mode",     setMode, ""                        },
  { "no-resources",    setMode, ""                        },
  { "out-of-sequence", setMode, "u"                       },
  { "timeout",         setMode, ""                        },
  { "delay-cbke",      setMode, "vv"                      },
  { "cert-mangle",     NULL,    (PGM_P)certMangleCommands },
  { "default-resp",    setMode, ""                        },
  { NULL },
};

EmberCommandEntry emAfTestHarnessCommands[] = {
  { "status",            printStatus, ""                                   },
  { "aps-sec-for-clust", NULL,        (PGM_P)apsSecurityForClusterCommands },
  { "registration",      NULL,        (PGM_P)registrationCommands          },
  { "ke",                NULL,        (PGM_P)keyEstablishmentCommands      },
  { NULL },
};

static int8u certIndexToCorrupt = 0;
#define TEST_HARNESS_BACK_OFF_TIME_SECONDS 30

#define CBKE_KEY_ESTABLISHMENT_SUITE         0x0001   // per the spec

#define TEST_HARNESS_PRINT_PREFIX "TEST HARNESS: "

// Holds either the ephemeral public key or the 2 SMAC values.
// The SMAC values are the biggest piece of data.
static int8u* delayedData[EMBER_SMAC_SIZE * 2];
static boolean stopRecursion = FALSE;
static int16u cbkeDelaySeconds = 0;
static int8u delayedCbkeOperation = CBKE_OPERATION_GENERATE_KEYS;

EmberEventControl emAfKeyEstablishmentTestHarnessEventControl;

// This is what is reported to the partner of key establishment.
int16u emAfKeyEstablishmentTestHarnessGenerateKeyTime = DEFAULT_EPHEMERAL_DATA_GENERATE_TIME_SECONDS;
int16u emAfKeyEstablishmentTestHarnessConfirmKeyTime = DEFAULT_GENERATE_SHARED_SECRET_TIME_SECONDS;
int16u emAfKeyEstablishmentTestHarnessAdvertisedGenerateKeyTime = DEFAULT_EPHEMERAL_DATA_GENERATE_TIME_SECONDS;

#define NULL_CLUSTER_ID 0xFFFF
static EmberAfClusterId clusterIdRequiringApsSecurity = NULL_CLUSTER_ID;

// Packet must be at least 3 bytes for ZCL overhead.
//   Frame Control (1-byte)
//   Sequence Number (1-byte)
//   Command Id (1-byte)
#define ZCL_OVERHEAD 3

#if defined(EMBER_AF_PLUGIN_TEST_HARNESS_AUTO_REGISTRATION_START)
  #define AUTO_REG_START TRUE
#else
  #define AUTO_REG_START FALSE
#endif

boolean emAfTestHarnessAllowRegistration = AUTO_REG_START;

//------------------------------------------------------------------------------
// External Declarations

#if defined(EZSP_HOST)
void emberGenerateCbkeKeysHandler(EmberStatus status,
                                  EmberPublicKeyData* ephemeralPublicKey);
#endif

void emberCalculateSmacsHandler(EmberStatus status,
                                EmberSmacData* initiatorSmacReturn,
                                EmberSmacData* responderSmacReturn);

//------------------------------------------------------------------------------


static void testHarnessPrintVarArgs(PGM_P format,
                                   va_list vargs)
{
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_KEY_ESTABLISHMENT_CLUSTER)
  emberAfKeyEstablishmentClusterFlush();
  emberAfKeyEstablishmentClusterPrint(TEST_HARNESS_PRINT_PREFIX);
  emberSerialPrintfVarArg(EMBER_AF_PRINT_OUTPUT, format, vargs);
  emberAfKeyEstablishmentClusterFlush();
#endif
}

static void testHarnessPrint(PGM_P format,
                               ...)
{
  va_list vargs;
  va_start(vargs, format);
  testHarnessPrintVarArgs(format, vargs);
  va_end(vargs);
}


static void testHarnessPrintln(PGM_P format,
                               ...)
{
  va_list vargs;
  va_start(vargs, format);
  testHarnessPrintVarArgs(format, vargs);
  va_end(vargs);
  emberSerialPrintCarriageReturn(EMBER_AF_PRINT_OUTPUT);
}

static void resetTimeouts(void)
{
  emAfKeyEstablishmentTestHarnessGenerateKeyTime = DEFAULT_EPHEMERAL_DATA_GENERATE_TIME_SECONDS;
  emAfKeyEstablishmentTestHarnessConfirmKeyTime = DEFAULT_GENERATE_SHARED_SECRET_TIME_SECONDS;
  emAfKeyEstablishmentTestHarnessAdvertisedGenerateKeyTime = DEFAULT_EPHEMERAL_DATA_GENERATE_TIME_SECONDS;
}

static void setCertMangleType(void)
{
  int8u commandChar = emberCurrentCommand->name[0];

  testHarnessMode = MODE_CERT_MANGLE;

  if (commandChar == 'l') {
    certMangleType = CERT_MANGLE_LENGTH;
    certLengthMod = (int8s)emberSignedCommandArgument(0);
  } else if (commandChar == 'i') {
    certMangleType = CERT_MANGLE_ISSUER;
    emberCopyEui64Argument(0, invalidIssuer);
  } else if (commandChar == 'c' ) {
    certMangleType = CERT_MANGLE_CORRUPT;
    certIndexToCorrupt = (int8u)emberUnsignedCommandArgument(0);
  } else {
    testHarnessPrintln("Unknown command");
    return;
  }

  // Reset this value back to its normal value in case 
  // it was set.
  resetTimeouts();
}

static void setMode(void)
{
  int8u commandChar0 = emberCurrentCommand->name[0];
  int8u commandChar2 = emberCurrentCommand->name[2];

  if (commandChar0 == 'o') {
    testHarnessMode = MODE_OUT_OF_SEQUENCE;
    respondToCommandWithOutOfSequence = (int8u)emberUnsignedCommandArgument(0);

  } else if (commandChar0 == 'n') {
    if (commandChar2 == '-') {
      testHarnessMode = MODE_NO_RESOURCES;
    } else if (commandChar2 == 'r') {
      testHarnessMode = MODE_NORMAL;
    }

  } else if (commandChar0 == 't') {
    testHarnessMode = MODE_TIMEOUT;

  } else if (commandChar2 == 'l' ) {  // delay-cbke
    int16u delay = (int16u)emberUnsignedCommandArgument(0);
    int16u advertisedDelay = (int16u)emberUnsignedCommandArgument(1);
    testHarnessMode = MODE_DELAY_CBKE;
    cbkeDelaySeconds = delay;
    emAfKeyEstablishmentTestHarnessGenerateKeyTime = delay;
    emAfKeyEstablishmentTestHarnessConfirmKeyTime  = advertisedDelay;
    emAfKeyEstablishmentTestHarnessAdvertisedGenerateKeyTime = advertisedDelay;
    return;

  } else if (commandChar2 == 'f') { // default-resp
    testHarnessMode = MODE_DEFAULT_RESPONSE;
    return;

  } else {
    testHarnessPrintln("Unknown command");
    return;
  }

  resetTimeouts();
}

static void setRegistration(void)
{
  int8u commandChar1 = emberCurrentCommand->name[1];
  if (commandChar1 == 'n') {
    emAfTestHarnessAllowRegistration = TRUE;
  } else if (commandChar1 == 'f') {
    emAfTestHarnessAllowRegistration = FALSE;
  } else {
    testHarnessPrintln("Unknown command");
  }
}

static void setApsSecurityForCluster(void)
{
  int8u commandChar1 = emberCurrentCommand->name[1];
  if (commandChar1 == 'n') {
    clusterIdRequiringApsSecurity = (int16u)emberUnsignedCommandArgument(0);
  } else if (commandChar1 == 'f') {
    clusterIdRequiringApsSecurity = NULL_CLUSTER_ID;
  } else {
    testHarnessPrintln("Unknown command");
  }

}


boolean emAfKeyEstablishmentTestHarnessMessageSendCallback(int8u message)
{
  int8u i;
  int8u* ptr = (appResponseData
                + CERT_OFFSET_IN_INITIATE_KEY_ESTABLISHMENT_MESSAGE);
  int8u direction = (*appResponseData & ZCL_FRAME_CONTROL_DIRECTION_MASK);

  if (MODE_NORMAL == testHarnessMode) {
    return TRUE;
  }

  if (testHarnessMode == MODE_CERT_MANGLE) {
    if (message == ZCL_INITIATE_KEY_ESTABLISHMENT_REQUEST_COMMAND_ID) {
      if (certMangleType == CERT_MANGLE_LENGTH) {
        if (certLengthMod > 0) {
          ptr = appResponseData + appResponseLength;
          for (i = 0; i < certLengthMod; i++) {
            *ptr = i;
            ptr++;
          }
        }
        appResponseLength += certLengthMod;

        testHarnessPrintln("Mangling certificate length by %p%d bytes",
                           (certLengthMod > 0
                            ? "+"
                            : ""),
                           certLengthMod);

      } else if (certMangleType == CERT_MANGLE_ISSUER) {
        ptr += ISSUER_OFFSET_IN_CERT;

        MEMCOPY(ptr, invalidIssuer, EUI64_SIZE);
        testHarnessPrintln("Mangling certificate issuer to be (>)%X%X%X%X%X%X%X%X",
                           invalidIssuer[0],
                           invalidIssuer[1],
                           invalidIssuer[2],
                           invalidIssuer[3],
                           invalidIssuer[4],
                           invalidIssuer[5],
                           invalidIssuer[6],
                           invalidIssuer[7]);
      
      } else if (certMangleType == CERT_MANGLE_CORRUPT) {
        // We bit flip the byte to make sure it is different than 
        // its real value.
        ptr += certIndexToCorrupt;
        *ptr = ~ (*ptr);
        testHarnessPrintln("Mangling byte at index %d in certificate.", 
                           certIndexToCorrupt);
      }
    } else if (message == ZCL_TERMINATE_KEY_ESTABLISHMENT_COMMAND_ID) {
      if (certMangleType == CERT_MANGLE_CORRUPT) {
        // To simulate that the test harness has NOT cancelled
        // key establishment due to a problem with calculating
        // or comparing the SMAC (acting as KE server), we
        // send a confirm key message instead.  The local server
        // has really cancelled KE but we want to test that the other
        // side will cancel it and send its own terminate message.
        ptr = appResponseData + 2; // jump over frame control and sequence num
        *ptr++ = ZCL_CONFIRM_KEY_DATA_RESPONSE_COMMAND_ID;
        for (i = 0; i < EMBER_SMAC_SIZE; i++) {
          *ptr++ = i;
        }
        appResponseLength = (ZCL_OVERHEAD
                             + EMBER_SMAC_SIZE);
        testHarnessPrintln("Rewriting Terminate Message as Confirm Key Message");
      }
    }

  } else if (testHarnessMode == MODE_OUT_OF_SEQUENCE) {
    if (message == respondToCommandWithOutOfSequence) {
      int8u *ptr = appResponseData + 2;  // ZCL Frame control and sequence number

      testHarnessPrintln("Sending out-of-sequence message");

      ptr[0] = (message == ZCL_CONFIRM_KEY_DATA_REQUEST_COMMAND_ID
                ? ZCL_INITIATE_KEY_ESTABLISHMENT_REQUEST_COMMAND_ID
                : (message + 1));

      // Setting the outgoing message to the right length without really
      // filling the message with valid data means there would
      // probably be garbage or bad data.  However the receiving device should
      // check for an invalid command ID first before parsing the specific
      // fields in the message.
      appResponseLength = ZCL_OVERHEAD + emAfKeyEstablishMessageToDataSize[message];
    }

  } else if (testHarnessMode == MODE_NO_RESOURCES) {

    // If we are the client then we have to wait until after the first
    // message to send the 'no resources' message.
    if (!(direction == ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
          && message == ZCL_INITIATE_KEY_ESTABLISHMENT_REQUEST_COMMAND_ID)) {
      int8u *ptr = appResponseData + 2;  // ZCL Frame control and sequence number
      *ptr++ = ZCL_TERMINATE_KEY_ESTABLISHMENT_COMMAND_ID;
      *ptr++ = EMBER_ZCL_AMI_KEY_ESTABLISHMENT_STATUS_NO_RESOURCES;
      *ptr++ = TEST_HARNESS_BACK_OFF_TIME_SECONDS;
      *ptr++ = LOW_BYTE(CBKE_KEY_ESTABLISHMENT_SUITE);
      *ptr++ = HIGH_BYTE(CBKE_KEY_ESTABLISHMENT_SUITE);

      appResponseLength = ptr - appResponseData;
      
      testHarnessPrintln("Sending Terminate: NO_RESOURCES");
    }
    
  } else if (testHarnessMode == MODE_DEFAULT_RESPONSE) {

    // If we are the client then we have to wait until after the first
    // message to send the Default Response message.
    if (!(direction == ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
          && message == ZCL_INITIATE_KEY_ESTABLISHMENT_REQUEST_COMMAND_ID)) {
      int8u *ptr = appResponseData;  
      int8u oldCommandId;
      *ptr++ = direction;
      ptr++; // skip sequence number, it was already written correctly.

      oldCommandId = *ptr;
      *ptr++ = ZCL_DEFAULT_RESPONSE_COMMAND_ID;

      // If we are the client, we send a response to the previous command ID.
      // If we are the server, we send a response to the current command ID.
      // This works because the client -> server and server -> client commands
      // are identical.  The client code will be sending the NEXT command ID,
      // which we are rewriting into a default response.  The server is sending
      // a command ID for the previous client command (a response ID to the
      // request), which has the same command ID as we are rewriting.
      *ptr++ = (direction == ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                ? oldCommandId - 1
                : oldCommandId);
      *ptr++ = EMBER_ZCL_STATUS_FAILURE;
      
      appResponseLength = ptr - appResponseData;
      
      testHarnessPrintln("Sending Default Response: FAILURE");
    }
    
  } else if (testHarnessMode == MODE_TIMEOUT) {

    // If we are the client then we have to wait until after the first
    // message to induce a timeout.
    if (!(direction == ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
          && message == ZCL_INITIATE_KEY_ESTABLISHMENT_REQUEST_COMMAND_ID)) {
      testHarnessPrintln("Suppressing message to induce timeout.");
      return FALSE;
    }
  }

  // Send the message
  return TRUE;
}

void emAfKeyEstablishementTestHarnessEventHandler(void)
{
  emberEventControlSetInactive(emAfKeyEstablishmentTestHarnessEventControl);
  testHarnessPrintln("Test Harness Event Handler fired, Tick: 0x%4X",
                     halCommonGetInt32uMillisecondTick());

  stopRecursion = TRUE;
  testHarnessPrintln("Generating %p callback.",
                     ((delayedCbkeOperation
                       == CBKE_OPERATION_GENERATE_KEYS)
                      ? "emberGenerateCbkeKeysHandler()"
                      : "emberCalculateSmacsHandler()"));
  
  if (delayedCbkeOperation == CBKE_OPERATION_GENERATE_KEYS) {
    emAfPluginKeyEstablishmentGenerateCbkeKeysHandler(EMBER_SUCCESS,
                                                      (EmberPublicKeyData*)delayedData);
  } else {
    emAfPluginKeyEstablishmentCalculateSmacsHandler(EMBER_SUCCESS,
                                                    (EmberSmacData*)delayedData,
                                                    (EmberSmacData*)(delayedData + EMBER_SMAC_SIZE));
  }
  
  stopRecursion = FALSE;
}

boolean emAfKeyEstablishmentTestHarnessCbkeCallback(int8u cbkeOperation,
                                                    int8u* data1,
                                                    int8u* data2)
{
  if (testHarnessMode != MODE_DELAY_CBKE) {
    return FALSE;
  }

  if (stopRecursion) {
    return FALSE;
  }

  testHarnessPrintln("Delaying %p key callback for %d seconds", 
                     (cbkeOperation == CBKE_OPERATION_GENERATE_KEYS
                      ? "ephemeral"
                      : "confirm"),
                     cbkeDelaySeconds);

  MEMCOPY(delayedData,
          data1, 
          (cbkeOperation == CBKE_OPERATION_GENERATE_KEYS
           ? sizeof(EmberPublicKeyData)
           : sizeof(EmberSmacData)));

  if (data2 != NULL) {
    MEMCOPY(delayedData + sizeof(EmberSmacData),
            data2,
            sizeof(EmberSmacData));
  }

  delayedCbkeOperation = cbkeOperation;
  
  testHarnessPrintln("Test Harness Tick: 0x%4X",
                     halCommonGetInt32uMillisecondTick());
  emberAfEventControlSetDelay(&emAfKeyEstablishmentTestHarnessEventControl, 
                              (((int32u)(cbkeDelaySeconds)) 
                               * MILLISECOND_TICKS_PER_SECOND));  // convert to MS
  return TRUE;
}

static void printStatus(void)
{
  emberAfKeyEstablishmentClusterPrint("Test Harness Mode: %p", modeText[testHarnessMode]);  
  if (testHarnessMode == MODE_CERT_MANGLE) {
    emberAfKeyEstablishmentClusterPrintln("");
    emberAfKeyEstablishmentClusterPrint("Cert Mangling Type: %p", certMangleText[certMangleType]);
    if (certMangleType == CERT_MANGLE_LENGTH) {
      emberAfKeyEstablishmentClusterPrint(" (%p%d bytes)",
                                          ((certLengthMod > 0)
                                           ? "+"
                                           : ""),
                                          certLengthMod);
    } else if (certMangleType == CERT_MANGLE_CORRUPT) {
      emberAfKeyEstablishmentClusterPrint(" (index: %d)",
                                          certIndexToCorrupt);
    }
  } else if (testHarnessMode == MODE_DELAY_CBKE) {
    emberAfKeyEstablishmentClusterPrint(" (by %d seconds",
                                        cbkeDelaySeconds);
  }
  emberAfKeyEstablishmentClusterPrintln("");

  emberAfKeyEstablishmentClusterPrintln("Auto SE Registration: %p",
                                        (emAfTestHarnessAllowRegistration
                                         ? "On"
                                         : "Off"));
  emberAfKeyEstablishmentClusterPrint("Additional Cluster Security: ");
  if (clusterIdRequiringApsSecurity == NULL_CLUSTER_ID) {
    emberAfKeyEstablishmentClusterPrintln("off");
  } else {
    emberAfKeyEstablishmentClusterPrintln("0x%2X", 
                                          clusterIdRequiringApsSecurity);
  }
  emberAfKeyEstablishmentClusterFlush();
}

boolean emberAfClusterSecurityCustomCallback(EmberAfClusterId clusterId, 
                                             boolean incoming, 
                                             int8u commandId)
{
  return (clusterIdRequiringApsSecurity != NULL_CLUSTER_ID
          && clusterId == clusterIdRequiringApsSecurity);
}

//------------------------------------------------------------------------------

