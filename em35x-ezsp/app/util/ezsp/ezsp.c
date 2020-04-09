// File: ezsp.c
// 
// Description: Host EZSP layer. Provides functions that allow the Host
// application to send every EZSP command to the EM260. The command and response
// parameters are defined in the datasheet.
// 
// Copyright 2006-2010 by Ember Corporation. All rights reserved.           *80*

#include PLATFORM_HEADER

#include "stack/include/ember-types.h"
#include "stack/include/error.h"

#include "hal/hal.h"

#include "app/util/ezsp/ezsp-protocol.h"
#include "app/util/ezsp/ezsp.h"
#include "app/util/ezsp/serial-interface.h"
#include "app/util/ezsp/ezsp-frame-utilities.h"

#ifdef EZSP_UART
  #include "app/ezsp-uart-host/ash-host-priv.h"
  #define EZSP_UART_TRACE(...) ashTraceEzspVerbose(__VA_ARGS__)
#else
  #define EZSP_UART_TRACE(...)
#endif

//----------------------------------------------------------------
// Forward Declarations

static void startCommand(int8u command);
static void sendCommand(void);
static void callbackDispatch(void);
static void callbackPointerInit(void);
static int8u *fetchInt8uPointer(int8u length);

//----------------------------------------------------------------
// Global Variables

int8u ezspSleepMode = EZSP_FRAME_CONTROL_IDLE;

static boolean sendingCommand = FALSE;
static int8u ezspSequence = 0;

// Some callbacks from EZSP to the application include a pointer parameter. For
// example, messageContents in ezspIncomingMessageHandler(). Copying the
// callback and then giving the application a pointer to this copy means it is
// safe for the application to call EZSP functions inside the callback. To save
// RAM, the application can define EZSP_DISABLE_CALLBACK_COPY. The application
// must then not read from the pointer after calling an EZSP function inside the
// callback.
#ifndef EZSP_DISABLE_CALLBACK_COPY
static int8u ezspCallbackStorage[EZSP_MAX_FRAME_LENGTH];
#endif

boolean ncpHasCallbacks;

//----------------------------------------------------------------
// Special Handling for AES functions.

// This is a copy of the function available on the SOC.  It would be a waste
// to have this be an actual EZSP call.
void emberAesMmoHashInit(EmberAesMmoHashContext *context)
{
  MEMSET(context, 0, sizeof(EmberAesMmoHashContext));
}

// Here we convert the normal Ember AES hash call to the specialized EZSP call.
// This came about because we cannot pass a block of data that is
// both input and output into EZSP.  The block must be broken up into two
// elements.  We unify the two pieces here to make it invisible to
// the users.

static EmberStatus aesMmoHash(EmberAesMmoHashContext *context,
                              boolean finalize,
                              int32u length,
                              int8u *data)
{
  EmberAesMmoHashContext returnData;
  EmberStatus status;
  if (length > 255) {
    return EMBER_INVALID_CALL;
  }
  // In theory we could use 'context' structure as the 'returnData',
  // however that could be risky if the EZSP function tries to memset() the 
  // 'returnData' prior to storing data in it.
  status = ezspAesMmoHash(context,
                          finalize,
                          (int8u)length,
                          data,
                          &returnData);
  MEMCOPY(context, &returnData, sizeof(EmberAesMmoHashContext));
  return status;
}

EmberStatus emberAesMmoHashUpdate(EmberAesMmoHashContext *context,
                                  int32u length,
                                  int8u *data)
{
  return aesMmoHash(context,
                    FALSE,   // finalize?
                    length,
                    data);
}

EmberStatus emberAesMmoHashFinal(EmberAesMmoHashContext *context,
                                 int32u length,
                                 int8u *data)
{
  return aesMmoHash(context,
                    TRUE,    // finalize?
                    length,
                    data);
}

//------------------------------------------------------------------------------
// SOC function names that are available on the host in a different
// form to save code space.

EmberStatus emberStartWritingStackTokens(void)
{
  int8u i = 1;
  return ezspSetValue(EZSP_VALUE_STACK_TOKEN_WRITING, 1, &i);
}

EmberStatus emberStopWritingStackTokens(void)
{
  int8u i = 0;
  return ezspSetValue(EZSP_VALUE_STACK_TOKEN_WRITING, 1, &i);
}

boolean emberWritingStackTokensEnabled(void)
{
  int8u value;
  int8u valueLength = 1;
  ezspGetValue(EZSP_VALUE_STACK_TOKEN_WRITING, &valueLength, &value);
  return value;
}

boolean emberStackIsPerformingRejoin(void)
{
  int8u value = 0;
  int8u valueLength;
  ezspGetValue(EZSP_VALUE_STACK_IS_PERFORMING_REJOIN,
               &valueLength,
               &value);
  return value;
}

EmberStatus emberSendRemoveDevice(EmberNodeId destShort,
                                  EmberEUI64 destLong,
                                  EmberEUI64 deviceToRemoveLong)
{
  int8u data[16];
  // We don't care about the value of the extra 8-bytes in the array.
  // The NCP will not actually use that data.  But this EZSP message must
  // be the same size as the ezspUnicastNwkKeyUpdate() message.
  MEMCOPY(data, deviceToRemoveLong, EUI64_SIZE);
  return ezspRemoveDevice(destShort, destLong, (int8u*)deviceToRemoveLong);
}

EmberStatus emberSendUnicastNetworkKeyUpdate(EmberNodeId targetShort,
                                             EmberEUI64  targetLong,
                                             EmberKeyData* newKey)
{
  return ezspUnicastNwkKeyUpdate(targetShort,
                                 targetLong,
                                 newKey);
}

//------------------------------------------------------------------------------

#include "command-functions.h"

//----------------------------------------------------------------
// EZSP Utilities

static void startCommand(int8u command)
{
  ezspWritePointer = ezspFrameContents + EZSP_PARAMETERS_INDEX;
  serialSetCommandByte(EZSP_FRAME_ID_INDEX, command);
}

enum {
  RESPONSE_SUCCESS,
  RESPONSE_WAITING,
  RESPONSE_ERROR
};

static int8u responseReceived(void)
{
  EzspStatus status;
  int8u responseFrameControl;

  status = serialResponseReceived();

  if (status == EZSP_SPI_WAITING_FOR_RESPONSE
      || status == EZSP_ASH_NO_RX_DATA) {
    return RESPONSE_WAITING;
  }

  ezspReadPointer = ezspFrameContents + EZSP_PARAMETERS_INDEX;

  if (status == EZSP_SUCCESS) {
    responseFrameControl = serialGetResponseByte(EZSP_FRAME_CONTROL_INDEX);
    if (serialGetResponseByte(EZSP_FRAME_ID_INDEX) == EZSP_INVALID_COMMAND)
      status = serialGetResponseByte(EZSP_PARAMETERS_INDEX);
    if ((responseFrameControl & EZSP_FRAME_CONTROL_DIRECTION_MASK)
        != EZSP_FRAME_CONTROL_RESPONSE)
      status = EZSP_ERROR_WRONG_DIRECTION;
    if ((responseFrameControl & EZSP_FRAME_CONTROL_TRUNCATED_MASK)
        == EZSP_FRAME_CONTROL_TRUNCATED)
      status = EZSP_ERROR_TRUNCATED;
    if ((responseFrameControl & EZSP_FRAME_CONTROL_OVERFLOW_MASK)
        == EZSP_FRAME_CONTROL_OVERFLOW_MASK)
      status = EZSP_ERROR_OVERFLOW;
    if ((responseFrameControl & EZSP_FRAME_CONTROL_PENDING_CB_MASK)
        == EZSP_FRAME_CONTROL_PENDING_CB) {
      ncpHasCallbacks = TRUE;
    } else {
      ncpHasCallbacks = FALSE;
    }
  }
  if (status != EZSP_SUCCESS) {
    EZSP_UART_TRACE("responseReceived(): ezspErrorHandler(): 0x%x", status);
    ezspErrorHandler(status);
    return RESPONSE_ERROR;
  } else {
    return RESPONSE_SUCCESS;
  }
}

static void sendCommand(void)
{
  EzspStatus status;
  int16u length = ezspWritePointer - ezspFrameContents;
  serialSetCommandByte(EZSP_SEQUENCE_INDEX, ezspSequence);
  ezspSequence++;
  serialSetCommandByte(EZSP_FRAME_CONTROL_INDEX,
                       (EZSP_FRAME_CONTROL_COMMAND | ezspSleepMode));
  if (length > EZSP_MAX_FRAME_LENGTH) {
    EZSP_UART_TRACE("sendCommand(): ezspErrorHandler(): EZSP_ERROR_COMMAND_TOO_LONG");
    ezspErrorHandler(EZSP_ERROR_COMMAND_TOO_LONG);
    return;
  }
  serialSetCommandLength(length);
  // Ensure that a second command is not sent before the response to the first
  // command has been processed.
  assert(!sendingCommand);
  sendingCommand = TRUE;
  status = serialSendCommand();
  if (status == EZSP_SUCCESS) {
    while (responseReceived() == RESPONSE_WAITING) {
      ezspWaitingForResponse();
    }
  } else {
    EZSP_UART_TRACE("sendCommand(): ezspErrorHandler(): 0x%x", status);
    ezspErrorHandler(status);
  }
  sendingCommand = FALSE;
}

static void callbackPointerInit(void)
{
#ifndef EZSP_DISABLE_CALLBACK_COPY
  MEMCOPY(ezspCallbackStorage, ezspFrameContents, EZSP_MAX_FRAME_LENGTH);
  ezspReadPointer = ezspCallbackStorage + EZSP_PARAMETERS_INDEX;
#endif
}

static int8u *fetchInt8uPointer(int8u length)
{
  int8u *result = ezspReadPointer;
  ezspReadPointer += length;
  return result;
}

void ezspTick(void)
{
  int8u count = serialPendingResponseCount() + 1;
  // Ensure that we are not being called from within a command.
  assert(!sendingCommand);
  while (count > 0 && responseReceived() == RESPONSE_SUCCESS) {
    callbackDispatch();
    count--;
  }
  simulatedTimePasses();
}
