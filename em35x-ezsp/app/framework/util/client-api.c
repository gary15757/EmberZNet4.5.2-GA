// Copyright 2009 by Ember Corporation. All rights reserved.
//
// This file contains the C portion of the client api.
//

#include PLATFORM_HEADER
#include "common.h"
#include "util.h"
#include "client-api.h"

extern int8u emberAfSequenceNumber;

static int8u *zclBuffer = NULL;
static int16u zclBufferLen = 0;

// Pointer to where this API should put the length
static int16u *responseLengthPtr = NULL;

// Pointer to where the API should put the cluster ID
static EmberApsFrame *commandApsFrame = NULL;

/////////////////

// Method that fills in the buffer.
// It returns number of bytes filled
// and 0 on error.
static int16u emAfVFillBuffer(int8u *buffer,
                              int16u bufferLen,
                              int8u frameControl,
                              int16u manufacturerCode,
                              int8u commandId,
                              PGM_P format,
                              va_list argPointer)
{
  int16u len = 0, word;
  int8u i = 0, c, *contents;
  int32u wword;

  if (bufferLen < EMBER_AF_ZCL_OVERHEAD
      || (manufacturerCode != EMBER_AF_NULL_MANUFACTURER_CODE
          && bufferLen < EMBER_AF_ZCL_MANUFACTURER_SPECIFIC_OVERHEAD)) {
    return 0;
  }

  if (manufacturerCode != EMBER_AF_NULL_MANUFACTURER_CODE) {
    frameControl |= ZCL_MANUFACTURER_SPECIFIC_MASK;
  }
  buffer[len++] = frameControl;
  if (manufacturerCode != EMBER_AF_NULL_MANUFACTURER_CODE) {
    for (c = 0; c < 2; c++) {
       buffer[len++] = LOW_BYTE(manufacturerCode);
       manufacturerCode = manufacturerCode >> 8;
    }
  }
  buffer[len++] = emberAfNextSequence();
  buffer[len++] = commandId;

  while(format[i] != 0) {
    char cmd = format[i];
    if (cmd >= '0' && cmd <= '9') {
      c = (cmd - '0');
      if (bufferLen < len + c) return 0;
      contents = (int8u *)va_arg(argPointer, int8u *);
      MEMCOPY(buffer + len, contents, c);
      len += c;
    } else if (cmd >= 'A' && cmd <= 'G') {
      c = (cmd - 'A') + 10;
      if (bufferLen < len + c) return 0;
      contents = (int8u *)va_arg(argPointer, int8u *);
      MEMCOPY(buffer + len, contents, c);
      len += c;
    } else {
      switch(cmd) {

      case 'u': // int8u
        if (bufferLen < len + 1) return 0;
        buffer[len++] = (int8u)va_arg(argPointer, int);
        break;

      case 'v': // int16u
        if (bufferLen < len + 2) return 0;
        word = (int16u)va_arg(argPointer, int);
        // The direct assignment of the low and high bytes does not work on the
        // EM250 because of a compiler bug.  As a workaround, use the same
        // looping mechanism as for int32u.
        //buffer[len++] = LOW_BYTE(word);
        //buffer[len++] = HIGH_BYTE(word);
        for (c = 0; c < 2; c++) {
          buffer[len++] = LOW_BYTE(word);
          word = word >> 8;
        }
        break;

      case 'w': // int32u
        if (bufferLen < len + 4) return 0;
        wword = (int32u)va_arg(argPointer, int32u);
        for (c = 0; c < 4; c++) {
          buffer[len++] = LOW_BYTE(wword);
          wword = wword >> 8;
        }
        break;

      case 's': // One parameter, which is int8u*, containing length first.
        contents = (int8u *)va_arg(argPointer, int8u *);
        c = emberAfStringLength(contents);
        if (bufferLen < len + c + 1) {
          emberAfDebugPrintln("String[%d] does not fit into buffer.", c);
          return 0;
        }
        MEMCOPY(buffer + len, contents, c + 1);
        len += (c + 1);
        break;

      case 'S':
        // One parameter is int8u*, next parameter is length
        // length is added as a first byte, rest is the buffer
        contents = (int8u *)va_arg(argPointer, int8u *);
        c = (int8u)va_arg(argPointer, int);
        if (bufferLen < len + c + 1) return 0;
        buffer[len++] = c;
        MEMCOPY(buffer + len, contents, c);
        len += c;
        break;

      case 'b':
        // One parameter is int8u*, next parameter is length
        // length is used, but not put in the outgoing buffer
        contents = (int8u *)va_arg(argPointer, int8u *);
        c = (int8u)va_arg(argPointer, int);
        if (bufferLen < len + c) return 0;
        MEMCOPY(buffer + len, contents, c);
        len += c;
        break;
      }
    }
    i++;
  }

  return len;
}

////////////////////// Public API ////////////////////////

void emberAfSetExternalBuffer(int8u *buffer,
                              int16u bufferLen,
                              int16u *lenPtr,
                              EmberApsFrame *apsFrame)
{
  zclBuffer = buffer;
  zclBufferLen = bufferLen;
  responseLengthPtr = lenPtr;
  commandApsFrame = apsFrame;
}

int16u emberAfFillExternalManufacturerSpecificBuffer(int8u frameControl,
                                                     EmberAfClusterId clusterId,
                                                     int16u manufacturerCode,
                                                     int8u commandId,
                                                     PGM_P format,
                                                     ...)
{
  int16u returnValue;
  va_list argPointer;

  va_start(argPointer, format);
  returnValue = emAfVFillBuffer(zclBuffer,
                                zclBufferLen,
                                frameControl,
                                manufacturerCode,
                                commandId,
                                format,
                                argPointer);
  va_end(argPointer);
  *responseLengthPtr = (int8u)returnValue;
  commandApsFrame->clusterId = clusterId;
  return returnValue;
}

int16u emberAfFillExternalBuffer(int8u frameControl,
                                 EmberAfClusterId clusterId,
                                 int8u commandId,
                                 PGM_P format,
                                 ...)
{
  int16u returnValue;
  va_list argPointer;

  va_start(argPointer, format);
  returnValue = emAfVFillBuffer(zclBuffer,
                                zclBufferLen,
                                frameControl,
                                EMBER_AF_NULL_MANUFACTURER_CODE,
                                commandId,
                                format,
                                argPointer);
  va_end(argPointer);
  *responseLengthPtr = (int8u)returnValue;
  commandApsFrame->clusterId = clusterId;
  return returnValue;
}

int16u emberAfFillBuffer(int8u *buffer,
                         int16u bufferLen,
                         int8u frameControl,
                         int8u commandId,
                         PGM_P format,
                         ...)
{
  int16u returnValue;
  va_list argPointer;

  va_start(argPointer, format);
  returnValue = emAfVFillBuffer(buffer,
                                bufferLen,
                                frameControl,
                                EMBER_AF_NULL_MANUFACTURER_CODE,
                                commandId,
                                format,
                                argPointer);
  va_end(argPointer);
  return returnValue;
}

EmberStatus emberAfSendCommandMulticast(EmberMulticastId multicastId)
{
  emberAfAddToCurrentAppTasks(EMBER_AF_WAITING_FOR_ZCL_RESPONSE);
  return emberAfSendMulticast(multicastId,
                              commandApsFrame,
                              *responseLengthPtr,
                              zclBuffer);
}

EmberStatus emberAfSendCommandUnicast(EmberOutgoingMessageType type,
                                      int16u indexOrDestination)
{
  emberAfAddToCurrentAppTasks(EMBER_AF_WAITING_FOR_ZCL_RESPONSE);
  return emberAfSendUnicast(type,
                            indexOrDestination,
                            commandApsFrame,
                            *responseLengthPtr,
                            zclBuffer);
}

EmberStatus emberAfSendCommandBroadcast(EmberNodeId destination)
{
  emberAfAddToCurrentAppTasks(EMBER_AF_WAITING_FOR_ZCL_RESPONSE);
  return emberAfSendBroadcast(destination,
                              commandApsFrame,
                              *responseLengthPtr,
                              zclBuffer);
}

EmberStatus emberAfSendCommandInterPan(EmberPanId panId,
                                       const EmberEUI64 destinationLongId,
                                       EmberNodeId destinationShortId,
                                       EmberMulticastId multicastId,
                                       EmberAfProfileId profileId)
{
  return emberAfSendInterPan(panId,
                             destinationLongId,
                             destinationShortId,
                             multicastId,
                             commandApsFrame->clusterId,
                             profileId,
                             *responseLengthPtr,
                             zclBuffer);
}

EmberApsFrame *emberAfGetCommandApsFrame()
{
  return commandApsFrame;
}
