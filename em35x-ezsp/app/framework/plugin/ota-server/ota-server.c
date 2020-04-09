// *******************************************************************
// * ota-server.c
// *
// * Zigbee Over-the-air bootload cluster for upgrading firmware and 
// * downloading specific file.
// * 
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "app/framework/include/af.h"
#include "app/framework/gen/callback.h"
#include "app/framework/plugin/ota-common/ota.h"
#include "app/framework/plugin/ota-storage-common/ota-storage.h"
#include "ota-server.h"
#include "app/framework/util/util.h"
#include "app/framework/util/common.h"
#include "app/framework/plugin/ota-server-policy/ota-server-policy.h"

// -----------------------------------------------------------------------------
// Globals
// -----------------------------------------------------------------------------

extern int8u appDefaultResponseStatus;

#define LAST_MESSAGE_ID ZCL_QUERY_SPECIFIC_FILE_RESPONSE_COMMAND_ID



static int8u serverEndpoint = 0;  // invalid endpoint

#define QUERY_NEXT_IMAGE_HW_VER_PRESENT_MASK  0x01

// this mask is the same for both Image block request and image page request
#define IMAGE_REQUEST_IEEE_PRESENT_MASK       0x01  

// NOTE:  This value cannot be set above 50 in Smart Energy due to 
//        APS encryption
#define MAX_POSSIBLE_SERVER_BLOCK_SIZE 50

// -----------------------------------------------------------------------------
// Forward Declarations
// -----------------------------------------------------------------------------

static boolean commandParse(EmberAfClusterCommand* command);
static void prepareResponse(boolean useDefaultResponse,
                            int8u commandId,
                            int8u status,
                            int8u defaultResponsePayloadCommandId);
#define prepareClusterResponse(commandId, status)                 \
  prepareResponse(FALSE,                                          \
                  commandId,                                      \
                  status,                                         \
                  0)          // defaultResponsePayloadCommandId

#define prepareDefaultResponse(status, commandId)   \
  prepareResponse(TRUE,                             \
                  ZCL_DEFAULT_RESPONSE_COMMAND_ID,  \
                  (status),                         \
                  (commandId))

static void addEmberAfOtaImageIdIntoResponse(const EmberAfOtaImageId* id);

// -------------------------------------------------------
// OTA Server Init and Tick functions
// -------------------------------------------------------

void emberAfOtaBootloadClusterServerInitCallback(int8u endpoint)
{
  emberAfOtaStorageInitCallback();
  serverEndpoint = endpoint;
}

void emberAfOtaBootloadClusterServerTickCallback(int8u endpoint)
{
  emAfOtaPageRequestTick(endpoint);
}

// -------------------------------------------------------
// OTA Server Handler functions
// -------------------------------------------------------
boolean emberAfOtaServerIncomingMessageRawCallback(EmberAfClusterCommand* command)
{
  if(!commandParse(command)) {
    emberAfOtaBootloadClusterPrintln("ClusterError: failed parsing cmd 0x%x", 
                                     command->commandId);
    emberAfOtaBootloadClusterFlush();
    emberAfSendDefaultResponse(command, EMBER_ZCL_STATUS_INVALID_FIELD);
  } else {
    emberAfSendResponse();
  }

  // Always return true to indicate we processed the message.
  return TRUE;
}

static int8u queryNextImageRequestHandler(const EmberAfOtaImageId* currentImageId,
                                          int16u* hardwareVersion)
{
  int8u status;
  EmberAfOtaImageId upgradeImageId;
  
  status = emberAfOtaServerQueryCallback(currentImageId,
                                         hardwareVersion,
                                         &upgradeImageId);

  prepareClusterResponse(ZCL_QUERY_NEXT_IMAGE_RESPONSE_COMMAND_ID,
                         status);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    return status;
  }

  addEmberAfOtaImageIdIntoResponse(&upgradeImageId);
  emberAfPutInt32uInResp(emberAfOtaStorageGetTotalImageSizeCallback(&upgradeImageId));
  return status;
}

boolean emberAfOtaServerSendImageNotifyCallback(EmberNodeId dest,
                                                int8u endpoint,
                                                int8u payloadType,
                                                int8u queryJitter,
                                                const EmberAfOtaImageId* id)
{
  emberAfResponseDestination = dest;
  emberAfResponseApsFrame.destinationEndpoint = endpoint;
  prepareClusterResponse(ZCL_IMAGE_NOTIFY_COMMAND_ID,
                         payloadType);

  emberAfPutInt8uInResp(queryJitter);

  if (payloadType >= 1) {
    emberAfPutInt16uInResp(id->manufacturerId);
  }
  if (payloadType >= 2) {
    emberAfPutInt16uInResp(id->imageTypeId);
  }
  if (payloadType >= 3) {
    emberAfPutInt32uInResp(id->firmwareVersion);
  }
  emberAfSendResponse();
  return TRUE;
}

static void printBlockRequestInfo(const EmberAfOtaImageId* id,
                                  int8u maxDataSize,
                                  int32u offset)
{
  // To reduce the redundant data printed by the server, it will only print
  // a request for a different image than the last one.  To change this
  // behavior update the boolean below.
  const boolean printAllRequests = FALSE;

  static EmberAfOtaImageId lastImageId = INVALID_OTA_IMAGE_ID;

  if (!printAllRequests
      && (0 == MEMCOMPARE(id, &lastImageId, sizeof(EmberAfOtaImageId)))) {
    return;
  }
  MEMCOPY(&lastImageId, id, sizeof(EmberAfOtaImageId));
  
  emberAfOtaBootloadClusterPrintln("NEW ImageBlockReq mfgId:%2x imageTypeId:%2x, file:%4x, maxDataSize:%d, offset:0x%4x",
                              id->manufacturerId, 
                              id->imageTypeId, 
                              id->firmwareVersion, 
                              maxDataSize, 
                              offset);
}

// This function is made non-static for the Page request code
// It returns 0 on error, or the number of bytes sent on success.
int8u emAfOtaImageBlockRequestHandler(EmberNodeId source,
                                      const EmberAfOtaImageId* id,
                                      int32u offset,
                                      int8u maxDataSize)
{
  int8u data[MAX_POSSIBLE_SERVER_BLOCK_SIZE];
  int32u actualLength;
  int8u status = EMBER_ZCL_STATUS_SUCCESS;
  int8u serverBlockSize = emberAfOtaServerBlockSizeCallback(source);
  int32u waitTime;

  if (serverBlockSize > MAX_POSSIBLE_SERVER_BLOCK_SIZE) {
    serverBlockSize = MAX_POSSIBLE_SERVER_BLOCK_SIZE;
  }

  status = emberAfOtaServerImageBlockRequestCallback(id,
                                                     offset,
                                                     maxDataSize,
                                                     &waitTime);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    prepareClusterResponse(ZCL_IMAGE_BLOCK_RESPONSE_COMMAND_ID,
                           status);
    if (status == EMBER_ZCL_STATUS_WAIT_FOR_DATA) {
      // Current time (0 = use relative time, not UTC)
      emberAfPutInt32uInResp(0);
      emberAfPutInt32uInResp(waitTime);
    }
    return 0;
  }

  MEMSET(data, 0, MAX_POSSIBLE_SERVER_BLOCK_SIZE);
  printBlockRequestInfo(id, maxDataSize, offset);

  maxDataSize = (maxDataSize < serverBlockSize
                 ? maxDataSize
                 : serverBlockSize);
  if (EMBER_AF_OTA_STORAGE_SUCCESS 
      != emberAfOtaStorageReadImageDataCallback(id,
                                                offset,
                                                maxDataSize,
                                                data,
                                                &actualLength)
      || actualLength == 0) {
    status = EMBER_ZCL_STATUS_NO_IMAGE_AVAILABLE;
  }

  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    if (!emAfOtaPageRequestErrorHandler()) {
      // If the page request code didn't handle the error (because this code 
      // wasn't called due to a page request) then we send a normal
      // response.  We don't generate an error message because in that case
      // we were sending an unsolicited image block response.
      prepareDefaultResponse(status, ZCL_IMAGE_BLOCK_REQUEST_COMMAND_ID);
    }
    return 0;
  }

  prepareClusterResponse(ZCL_IMAGE_BLOCK_RESPONSE_COMMAND_ID, status);
  addEmberAfOtaImageIdIntoResponse(id);
  emberAfPutInt32uInResp(offset);
  emberAfPutInt8uInResp((int8u)actualLength);
  emberAfPutBlockInResp(data, actualLength);

  // We can't send more than 128 bytes in a packet so we can safely cast this
  // to a 1-byte number.
  return (int8u)actualLength;
}

static void constructUpgradeEndResponse(const EmberAfOtaImageId* imageId,
                                        int32u upgradeTime)
{
  prepareClusterResponse(ZCL_UPGRADE_END_RESPONSE_COMMAND_ID,
                         0);      // status code (will ignore)
  
  appResponseLength--;  // The above function wrote an extra byte which we 
                        // don't want because there is no status code for this
                        // message

  addEmberAfOtaImageIdIntoResponse(imageId);

  // We always use relative time.  There is no benefit in using
  // UTC time since the client has to support both.
  emberAfPutInt32uInResp(0);                   // current time
  emberAfPutInt32uInResp(upgradeTime);
}

static void upgradeEndRequestHandler(EmberNodeId source,
                                     int8u status, 
                                     const EmberAfOtaImageId* imageId)
{
  int32u upgradeTime;
  boolean goAhead;
  emberAfOtaBootloadClusterPrintln("RX UpgradeEndReq status:%x", 
                                   status);

  // This callback is considered only informative when the status
  // is a failure.
  goAhead = emberAfOtaServerUpgradeEndRequestCallback(source,
                                                      status,
                                                      &upgradeTime,
                                                      imageId);

  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    if (goAhead) {
      constructUpgradeEndResponse(imageId, upgradeTime);
    } else {
      prepareDefaultResponse(EMBER_ZCL_STATUS_ABORT,
                             ZCL_UPGRADE_END_REQUEST_COMMAND_ID);
    }
  } // Else 
    // Non-zero status.  Nothing to do.
}

static void querySpecificFileRequestHandler(int8u* requestNodeAddress,
                                            const EmberAfOtaImageId* imageId,
                                            int16u currentStackVersion)
{
  // Not supported yet.
  prepareDefaultResponse(EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND,
                         ZCL_QUERY_SPECIFIC_FILE_REQUEST_COMMAND_ID);
}

static void prepareResponse(boolean useDefaultResponse,
                            int8u commandId,
                            int8u status,
                            int8u defaultResponsePayloadCommandId)
{
  emberAfResponseApsFrame.sourceEndpoint = serverEndpoint;
  appResponseLength = 0;
  emberAfResponseApsFrame.clusterId = ZCL_OTA_BOOTLOAD_CLUSTER_ID;

  emberAfResponseApsFrame.options =
    ((emAfOtaServerHandlingPageRequest()
      && commandId == ZCL_IMAGE_BLOCK_RESPONSE_COMMAND_ID)
     ? EMBER_APS_OPTION_NONE
     : EMBER_APS_OPTION_RETRY );

  // Assume emberAfResponseApsFrame.destinationEndpoint has already
  // been set based on the framework.  In most cases it is as simple
  // as swapping source and dest endpoints.

  emberAfPutInt8uInResp((useDefaultResponse
                         ? ZCL_PROFILE_WIDE_COMMAND
                         : (ZCL_CLUSTER_SPECIFIC_COMMAND
                            | ZCL_DISABLE_DEFAULT_RESPONSE_MASK))
                        | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT);
  emberAfPutInt8uInResp(commandId == ZCL_IMAGE_NOTIFY_COMMAND_ID
                        ? emberAfNextSequence()
                        : emberAfIncomingZclSequenceNumber);

  emberAfPutInt8uInResp(commandId);
  if (useDefaultResponse) {
    emberAfPutInt8uInResp(defaultResponsePayloadCommandId);
  }
  emberAfPutInt8uInResp(status);

  // Assume the emberAfAppResponseDestination is already set.
}

static void addEmberAfOtaImageIdIntoResponse(const EmberAfOtaImageId* id)
{
  emberAfPutInt16uInResp(id->manufacturerId);
  emberAfPutInt16uInResp(id->imageTypeId);
  emberAfPutInt32uInResp(id->firmwareVersion);
}

static boolean commandParse(EmberAfClusterCommand* command)
{
  int8u commandId = command->commandId;
  int8u* buffer = command->buffer;
  int8u length = command->bufLen;
  int8u index = EMBER_AF_ZCL_OVERHEAD;
  EmberAfOtaImageId imageId = INVALID_OTA_IMAGE_ID;

  if (commandId > LAST_MESSAGE_ID
      || (length < 
          (EMBER_AF_ZCL_OVERHEAD + emAfOtaMinMessageLengths[commandId]))) {
    return FALSE;
  }
  switch(commandId) {
    case ZCL_QUERY_NEXT_IMAGE_REQUEST_COMMAND_ID:
    case ZCL_IMAGE_BLOCK_REQUEST_COMMAND_ID:
    case ZCL_IMAGE_PAGE_REQUEST_COMMAND_ID: {
      int8u fieldControl; 
      int32u offset;
      int8u maxDataSize;
      int16u hardwareVersion;
      boolean hardwareVersionPresent = FALSE;
      
      fieldControl = emberAfGetInt8u(buffer, index, length);      
      index++;
      index += emAfOtaParseImageIdFromMessage(&imageId,
                                              &(buffer[index]),
                                              length);
      
      if (commandId == ZCL_QUERY_NEXT_IMAGE_REQUEST_COMMAND_ID) {
        if (fieldControl & QUERY_NEXT_IMAGE_HW_VER_PRESENT_MASK) {
          hardwareVersionPresent = TRUE;
          hardwareVersion = emberAfGetInt16u(buffer, index, length);
          index += 2;
        }

        queryNextImageRequestHandler(&imageId,
                                     (hardwareVersionPresent
                                      ? &hardwareVersion
                                      : NULL));
        return TRUE;

      } // else // ZCL_IMAGE_BLOCK_REQUEST_COMMAND_ID
                //   or ZCL_IMAGE_PAGE_REQUEST_COMMAND_ID

      offset = emberAfGetInt32u(buffer, index, length);
      index += 4;
      maxDataSize = emberAfGetInt8u(buffer, index, length);
      index++;
      
      if (commandId == ZCL_IMAGE_BLOCK_REQUEST_COMMAND_ID) {
        emAfOtaImageBlockRequestHandler(command->source,
                                        &imageId,
                                        offset,
                                        maxDataSize);

      } else { // ZCL_IMAGE_PAGE_REQUEST_COMMAND_ID
        int16u pageSize;
        int16u responseSpacing;
        int8u status;

        pageSize = emberAfGetInt16u(buffer, index, length);
        index += 2;

        responseSpacing = emberAfGetInt16u(buffer, index, length);
        index += 2;
        
        status = emAfOtaPageRequestHandler(serverEndpoint,
                                           &imageId,
                                           offset,
                                           maxDataSize,
                                           pageSize,
                                           responseSpacing);
                                       
        if (status != EMBER_ZCL_STATUS_SUCCESS) {
          prepareDefaultResponse(status,
                                 ZCL_IMAGE_PAGE_REQUEST_COMMAND_ID);
        }
      }
      return TRUE;
    }
    case ZCL_UPGRADE_END_REQUEST_COMMAND_ID: {
      int8u status = emberAfGetInt8u(buffer, index, length);
      index++;
      if (status == EMBER_ZCL_STATUS_SUCCESS) {
        index += emAfOtaParseImageIdFromMessage(&imageId,
                                                &(buffer[index]),
                                                length);
      }
      upgradeEndRequestHandler(command->source, status, &imageId);
      return TRUE;
    }
    case ZCL_QUERY_SPECIFIC_FILE_REQUEST_COMMAND_ID: {
      int8u* requestNodeAddress = &(buffer[index]);
      int16u currentStackVersion;
      index += 8;  // add 8 to jump over the requestNodeAddress 
      index += emAfOtaParseImageIdFromMessage(&imageId,
                                              &(buffer[index]),
                                              length);
      currentStackVersion = emberAfGetInt16u(buffer, index, length);
      index += 2;
      querySpecificFileRequestHandler(requestNodeAddress,
                                      &imageId,
                                      currentStackVersion);
      return TRUE;
    }
  }
  return FALSE;
}

void emberAfOtaServerSendUpgradeCommandCallback(EmberNodeId dest,
                                                int8u endpoint,
                                                const EmberAfOtaImageId* id)
{
  emberAfResponseDestination = dest;
  emberAfResponseApsFrame.destinationEndpoint = endpoint;
  constructUpgradeEndResponse(id,
                              0);  // upgrade time (0 = now)
  emberAfSendResponse();
}
