// *******************************************************************
// * af-main.h
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include CONFIGURATION_HEADER
#include PLATFORM_HEADER     // Micro and compiler specific typedefs and macros
#include "stack/include/ember-types.h"

#ifndef EMBER_AF_REJOIN_ATTEMPTS_MAX
  #define EMBER_AF_REJOIN_ATTEMPTS_MAX 0xff //always attempt rejoin
#endif

#ifndef EMBER_AF_NUM_MISSED_POLLS_TO_TRIGGER_MOVE
  #define EMBER_AF_NUM_MISSED_POLLS_TO_TRIGGER_MOVE 10
#endif

#ifdef EMBER_AF_ENABLE_STATISTICS
  extern int32u haNumPktsRxAll;
  extern int32u haNumPktsRxGivenToZCL;
  extern int32u haNumPktsRxLengthError;
  extern int32u haNumPktsRxWrongProfile;
  extern int32u haNumPktsRxWrongEndpoint;

  // macros for incrementing the counters
  #define INCR_haNumPktsRxAll           haNumPktsRxAll++
  #define INCR_haNumPktsRxGivenToZCL    haNumPktsRxGivenToZCL++
  #define INCR_haNumPktsRxLengthError   haNumPktsRxLengthError++
  #define INCR_haNumPktsRxWrongProfile  haNumPktsRxWrongProfile++
  #define INCR_haNumPktsRxWrongEndpoint haNumPktsRxWrongEndpoint++
#else // EMBER_AF_ENABLE_STATISTICS
  #define INCR_haNumPktsRxAll
  #define INCR_haNumPktsRxGivenToZCL
  #define INCR_haNumPktsRxLengthError
  #define INCR_haNumPktsRxWrongProfile
  #define INCR_haNumPktsRxWrongEndpoint
#endif // EMBER_AF_ENABLE_STATISTICS

#define MFG_STRING_MAX_LENGTH 16

// returnData must be MFG_STRING_MAX_LENGTH in length and 
// is NOT expected to be NULL terminated (could be though)
void emberAfGetMfgString(int8u* returnData);

#ifdef EMBER_AF_HEARTBEAT_ENABLE
#define emAfBlinkHeartbeat() halToggleLed(EMBER_AF_HEARTBEAT_LED)
#else
#define emAfBlinkHeartbeat()
#endif // EMBER_AF_HEARTBEAT_ENABLE

// Functions common to both SOC and Host versions of the application.
boolean emberAfIsFullSmartEnergySecurityPresent(void);
void emberAfPrintIncomingZclMessage(int8u endpoint,
                                    int16u clusterId,
                                    int8u* message,
                                    int16u len);

#if defined(EZSP_HOST)
  EmberStatus generateRandomKey(EmberKeyData* result);
  void afHostRefreshNodeId(void);
#else
  #define generateRandomKey(result) emberGenerateRandomKey(result)

  int8u emAfCopyMessageIntoRamBuffer(EmberMessageBuffer message,
                                     int8u *buffer,
                                     int16u bufLen);

#endif

#if defined EZSP_HOST
// Normally this is provided by the stack code, but on the host
// it is provided by the application code.
void emberReverseMemCopy(int8u* dest, const int8u* src, int16u length);

// utility for setting an EZSP config value and printing the result
EzspStatus emberAfSetEzspConfigValue(EzspConfigId configId,
                                     int16u value,
                                     PGM_P configIdName);

// utility for setting an EZSP policy and printing the result
EzspStatus emberAfSetEzspPolicy(EzspPolicyId policyId,
                                EzspDecisionId decisionId,
                                PGM_P policyName,
                                PGM_P decisionName);

// utility for setting an EZSP value and printing the result
EzspStatus emberAfSetEzspValue(EzspValueId valueId,
                               int8u valueLength,
                               int8u *value,
                               PGM_P valueName);

#endif // EZSP_HOST

void emAfPrintStatus(PGM_P task,
                     EmberStatus status);

extern boolean emberAfFirstButtonPressed;
extern boolean emberAfSecondButtonPressed;

void emberAfGetNetworkParameters(EmberNodeType* nodeType, 
                          EmberNetworkParameters* parameters);
int8u emberAfGetSecurityLevel(void);
int8u emberAfGetKeyTableSize(void);
void emAfCopyCounterValues(int16u* counters);
int8u emAfGetPacketBufferFreeCount(void);
int8u emAfGetPacketBufferTotalCount(void);


void emAfCliVersionCommand(void);

void emAfPermitJoin(int8u duration);
void emAfStopSmartEnergyStartup(void);

boolean emAfProcessZdo(EmberNodeId sender,
                       EmberApsFrame* apsFrame,
                       int8u* message, 
                       int16u length);

extern int8u emAfExtendedPanId[];

void emAfIncomingMessageHandler(EmberIncomingMessageType type,
                                EmberApsFrame *apsFrame,
                                int8u lastHopLqi,
                                int8s lastHopRssi,
                                EmberNodeId sender,
                                int8u bindingIndex,
                                int8u addressIndex,
                                int16u messageLength,
                                int8u *messageContents);
void emAfMessageSentHandler(EmberOutgoingMessageType type,
                            int16u indexOrDestination,
                            EmberApsFrame *apsFrame,
                            EmberStatus status,
                            int16u messageLength,
                            int8u *messageContents);
void emAfProcessSendStatus(EmberOutgoingMessageType type,
                           int16u indexOrDestination,
                           EmberApsFrame *apsFrame,
                           EmberStatus status,
                           int16u messageLength,
                           int8u *messageContents);

void emAfStackStatusHandler(EmberStatus status);
EmberStatus emAfNetworkInit(void);

// For Test purposes only
extern EmberStatus emAfNetworkInitReturnCodeStatus;

int8u emberAfCopyBigEndianEui64Argument(int8s index, EmberEUI64 destination);
void emAfScheduleFindAndRejoinEvent(void);
