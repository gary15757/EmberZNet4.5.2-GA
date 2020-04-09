// *******************************************************************
// * process-global-message.c
// *
// * This file contains function that processes global ZCL message.
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../include/af.h"
#include "common.h"
#include "../report/report-table.h"
#include "../plugin/smart-energy-registration/smart-energy-registration.h"
#include "../plugin/trust-center-keepalive/trust-center-keepalive.h"

// flag to keep track of the fact that we just sent a read attr for time and
// we should set our time to the result of the read attr response.
boolean emAfSyncingTime = FALSE;

#ifndef ZA_NO_REPORTING_OPTIMIZATION
/**
 * @brief Reportable change is either a specific value if it has
 * been set for a reported attribute or a default value. The
 * default is either all 0xff for unsigned values or 0x8000..
 * for signed values. This function was added as a fix for BUGZID: 11407.
 */
static void emAfPutReportableChangeInResponse(EmberAfReportEntry *entry,
                                              EmberAfAttributeType dataType)
{
  int8u bytes = emberAfGetDataSize(dataType);
  if (entry == NULL) { // default, 0xff...UL or 0x80...L
    for (; bytes > 0; bytes--) {
      int8u b = 0xff;
      if (emberAfIsTypeSigned(dataType)) {
        b = ((bytes == 1) ? 0x80 : 0x00);
      }
      emberAfPutInt8uInResp(b);
    }
  } else { // reportable change value
    int32u value = entry->reportableChange;
    for (; bytes > 0; bytes--) {
      int8u b = BYTE_0(value);
      emberAfPutInt8uInResp(b);
      value >>= 8;
    }
  }
}
#endif

boolean emAfProcessGlobalCommand(EmberAfClusterCommand *cmd)
{
  int16u attrId;
  int8u frameControl;
  // This is a little clumsy but easier to read and port
  // from earlier implementation.
  EmberAfClusterId clusterId = cmd->apsFrame->clusterId;
  int8u zclCmd = cmd->commandId;
  int8u *message = cmd->buffer;
  int16u msgLen = cmd->bufLen;
  int16u msgIndex = cmd->payloadStartIndex;
  int8u clientServerMask = (cmd->direction == ZCL_DIRECTION_CLIENT_TO_SERVER
                            ? CLUSTER_MASK_SERVER
                            : CLUSTER_MASK_CLIENT);
  int16u manufacturerCode = (cmd->mfgSpecific
                             ? cmd->mfgCode
                             : EMBER_AF_NULL_MANUFACTURER_CODE);

  // If we are disabled then we can only respond to read or write commands
  // or identify cluster (see device enabled attr of basic cluster)
  if (!emberAfIsDeviceEnabled(cmd->apsFrame->destinationEndpoint)
      && zclCmd != ZCL_READ_ATTRIBUTES_COMMAND_ID
      && zclCmd != ZCL_WRITE_ATTRIBUTES_COMMAND_ID
      && zclCmd != ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID
      && zclCmd != ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID
      && zclCmd != ZCL_DEFAULT_RESPONSE_COMMAND_ID
      && clusterId != ZCL_IDENTIFY_CLUSTER_ID) {
    emberAfCorePrintln("disabled");
    emberAfDebugPrintln("%pd, dropping global cmd:%x", "disable", zclCmd);
    emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_FAILURE);
    return TRUE;
  }

  // Clear out the response buffer by setting its length to zero
  appResponseLength = 0;

  // Make the ZCL header for the response
  // note: cmd byte is set below
  frameControl = (ZCL_PROFILE_WIDE_COMMAND
                  | (cmd->direction == ZCL_DIRECTION_CLIENT_TO_SERVER
                     ? ZCL_FRAME_CONTROL_SERVER_TO_CLIENT
                     : ZCL_FRAME_CONTROL_CLIENT_TO_SERVER));
  if (cmd->mfgSpecific) {
    frameControl |= ZCL_MANUFACTURER_SPECIFIC_MASK;
  }
  emberAfPutInt8uInResp(frameControl);
  if (cmd->mfgSpecific) {
    emberAfPutInt16uInResp(cmd->mfgCode);
  }
  emberAfPutInt8uInResp(cmd->seqNum);


  switch (zclCmd) {

  // The format of the read attributes cmd is:
  // ([attr ID:2]) * N
  // The format of the read attributes response is:
  // ([attr ID:2] [status:1] [data type:0/1] [data:0/N]) * N
  case ZCL_READ_ATTRIBUTES_COMMAND_ID:
    {
      emberAfCorePrintln("%p: clus %2x", "READ_ATTR", clusterId);
      // Set the cmd byte - this is byte 3 index 2, but since we have
      // already incremented past the 3 byte ZCL header (our index is at 3),
      // this gets written to "-1" since 3 - 1 = 2.
      emberAfPutInt8uInResp(ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID);

      // This message contains N 2-byte attr IDs after the 3 byte ZCL header,
      // for each one we need to look it up and make a response
      while (msgIndex + 2 <= msgLen) {
        // Get the attribute ID and store it in the response buffer
        // least significant byte is first OTA
        attrId = emberAfGetInt16u(message, msgIndex, msgLen);

        // This function reads the attribute and creates the correct response
        // in the response buffer
        emberAfRetrieveAttributeAndCraftResponse(cmd->apsFrame->destinationEndpoint,
                                                 clusterId,
                                                 attrId,
                                                 clientServerMask,
                                                 manufacturerCode,
                                                 (EMBER_AF_RESPONSE_BUFFER_LEN
                                                  - appResponseLength));

        // Go to next attrID
        msgIndex += 2;
      }
    }
    emberAfSendResponse();
    return TRUE;

  // Write undivided means all attributes must be written in order to write
  // any of them. So first do a check. If the check fails, send back a fail
  // response. If it works, fall through to the normal write attr code.
  // write attr responses are the same for undivided and normal writes.
  case ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID:
    {
      int8u numFailures = 0;
      int8u dataType;
      int8u dataSize;
      int8u status;

      emberAfPutInt8uInResp(ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID);

      // Go through the message until there are no more attrID/type/data
      while (msgLen > msgIndex + 3) {
        attrId = emberAfGetInt16u(message, msgIndex, msgLen);
        dataType = emberAfGetInt8u(message, msgIndex + 2, msgLen);

        // For strings, the data size is the length of the string (specified by
        // the first byte of data) plus one for the length byte itself.  For
        // everything else, the size is just the size of the data type.
        dataSize = (emberAfIsThisDataTypeAStringType(dataType)
                    ? emberAfStringLength(message + msgIndex + 3) + 1
                    : emberAfGetDataSize(dataType));

        status = emberAfVerifyAttributeWrite(cmd->apsFrame->destinationEndpoint,
                                             clusterId,
                                             attrId,
                                             clientServerMask,
                                             manufacturerCode,
                                             &(message[msgIndex + 3]),
                                             dataType);
        if (status != EMBER_ZCL_STATUS_SUCCESS) {
          numFailures++;
          // Write to the response buffer - status and then attrID
          emberAfPutInt8uInResp(status);
          emberAfPutInt16uInResp(attrId);

          emberAfCorePrint("WRITE: clus %2x attr %2x ", clusterId, attrId);
          emberAfCorePrintln("FAIL %x", status);
          emberAfCoreFlush();
        }

        // Increment past the attribute id (two bytes), the type (one byte), and
        // the data (N bytes, including the length byte for strings).
        msgIndex += 3 + dataSize;
      }
      // If there are any failures, send the response and exit
      if (numFailures > 0) {
        emberAfSendResponse();
        return TRUE;
      }
    }
    // Reset message back to start
    msgIndex = cmd->payloadStartIndex;
    appResponseLength = (cmd->mfgSpecific ? 4 : 2);
    // DO NOT BREAK from this case

  // the format of the write attributes cmd is:
  // ([attr ID:2] [data type:1] [data:N]) * N
  // the format of the write attributes response is:
  // ([status 1] [attr ID 2]) * n
  // ONLY errors are reported unless all are successful then a single success
  // is sent. write attr no response is handled by just executing the same
  // code but not setting the flag that sends the response at the end.
  case ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID:
  case ZCL_WRITE_ATTRIBUTES_COMMAND_ID:
    {
      int8u numFailures = 0;
      int8u numSuccess = 0;
      int8u dataType;
      int8u dataSize;
#if (BIGENDIAN_CPU)
      int8u writeData[ATTRIBUTE_LARGEST];
#endif //(BIGENDIAN_CPU)
      int8u status;

      // set the cmd byte - this is byte 3 index 2, but since we have
      // already incremented past the 3 byte ZCL header (our index is at 3),
      // this gets written to "-1" since 3 - 1 = 2.
      emberAfPutInt8uInResp(ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID);

      // go through the message until there are no more attrID/type/data
      while (msgLen > msgIndex + 3) {
        attrId = emberAfGetInt16u(message, msgIndex, msgLen);
        dataType = emberAfGetInt8u(message, msgIndex + 2, msgLen);

        // For strings, the data size is the length of the string (specified by
        // the first byte of data) plus one for the length byte itself.  For
        // everything else, the size is just the size of the data type.
        dataSize = (emberAfIsThisDataTypeAStringType(dataType)
                    ? emberAfStringLength(message + msgIndex + 3) + 1
                    : emberAfGetDataSize(dataType));

        // the data is sent little endian over-the-air, it needs to be
        // inserted into the table big endian for the EM250 and little
        // endian for the EZSP hosts. This means for the EM250 the data
        // needs to be reversed before sending to writeAttributes
#if (BIGENDIAN_CPU)
          // strings go over the air as length byte and then in human
          // readable format. These should not be flipped.
          if (emberAfIsThisDataTypeAStringType(dataType)) {
            MEMCOPY(writeData, message + msgIndex + 3, dataSize);
          } else {
            // the data is sent little endian over-the-air, it needs to be
            // inserted into the table big endian
            int8u i;
            for (i = 0; i < dataSize; i++) {
              writeData[i] = message[msgIndex + 3 + dataSize - i - 1];
            }
          }
#endif //(BIGENDIAN_CPU)

          status = emberAfWriteAttributeExternal(cmd->apsFrame->destinationEndpoint,
                                                 clusterId,
                                                 attrId,
                                                 clientServerMask,
                                                 manufacturerCode,
#if (BIGENDIAN_CPU)
                                                 writeData,
#else //(BIGENDIAN_CPU)
                                                 &(message[msgIndex + 3]),
#endif //(BIGENDIAN_CPU)
                                                 dataType);
          emberAfCorePrint("WRITE: clus %2x attr %2x ",
                           clusterId,
                           attrId);
          if (status == EMBER_ZCL_STATUS_SUCCESS) {
            numSuccess++;
            emberAfCorePrintln("OK");
          } else {
            numFailures++;
            // write to the response buffer - status and then attrID
            emberAfPutInt8uInResp(status);
            emberAfPutInt16uInResp(attrId);
            emberAfCorePrintln("FAIL %x",  status);
          }
          emberAfCoreFlush();

        // Increment past the attribute id (two bytes), the type (one byte), and
        // the data (N bytes, including the length byte for strings).
        msgIndex += 3 + dataSize;
      }

      if (numFailures == 0) {
        // if no failures and no success this means the packet was too short
        // print an error message but still return TRUE as we consumed the
        // message
        if (numSuccess == 0) {
          emberAfCorePrintln("WRITE: too short");
          emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_MALFORMED_COMMAND);
          return TRUE;
        }
        // if no failures and at least one success, write a success status
        // that means everything worked
        else {
          emberAfPutInt8uInResp(EMBER_ZCL_STATUS_SUCCESS);
        }
      }
      // always send a response unless the cmd requested no response
      if (zclCmd == ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID) {
        emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_SUCCESS);
        return TRUE;
      }
      emberAfSendResponse();
      return TRUE;
    }

  // the format of discover is: [start attr ID:2] [max attr IDs:1]
  // the format of the response is: [done:1] ([attrID:2] [type:1]) * N
  case ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID:
    {
      EmberAfAttributeId startingAttributeId;
      int8u numberAttributes;
      boolean *complete;

      emberAfCorePrintln("%p: clus %2x", "DISC_ATTR", clusterId);

      // set the cmd byte - this is byte 3 index 2, but since we have
      // already incremented past the 3 byte ZCL header (our index is at 3),
      // this gets written to "-1" since 3 - 1 = 2.
      emberAfPutInt8uInResp(ZCL_DISCOVER_ATTRIBUTES_RESPONSE_COMMAND_ID);

      // get the attrId to start on and the max count
      startingAttributeId = emberAfGetInt16u(message, msgIndex, msgLen);
      numberAttributes = emberAfGetInt8u(message, msgIndex + 2, msgLen);

      // The response has a one-byte field indicating whether discovery is
      // complete.  We can't populate that field until we've finished going
      // through all the attributes, so save a placeholder, write a temporary
      // value for now (so that the offset moves forward), and write the real
      // value when we're done.
      complete = &(appResponseData[appResponseLength]);
      emberAfPutInt8uInResp(FALSE);
      *complete = emberAfReadSequentialAttributesAddToResponse(cmd->apsFrame->destinationEndpoint,
                                                               clusterId,
                                                               startingAttributeId,
                                                               clientServerMask,
                                                               manufacturerCode,
                                                               numberAttributes);
      emberAfSendResponse();
      return TRUE;
    }

#ifndef ZA_NO_REPORTING_OPTIMIZATION
  // ([direction:1] [attribute id:2] [type:0/1] [min interval:0/2] ...
  // ... [max interval:0/2] [reportable change:0/V] [timeout:0/2])+
  case ZCL_CONFIGURE_REPORTING_COMMAND_ID:
    {
      boolean failures = FALSE;
      emberAfReportingPrint("%p: ", "CFG_RPT");
      emberAfReportingDebugExec(emberAfDecodeAndPrintCluster(clusterId));
      emberAfReportingPrintln("");
      emberAfReportingFlush();

      emberAfPutInt8uInResp(ZCL_CONFIGURE_REPORTING_RESPONSE_COMMAND_ID);

      // Each record in the command has a one-byte direction and a two-byte
      // attribute id.  If the direction indicates the attribute is to be
      // reported, the record will contain a one-byte type and two two-byte
      // intervals.  If the type is analog, the record will contain a reportable
      // change of the same data type.  If the direction indicates reports are
      // to be received, the record will contain a two-byte timeout.
      while (msgIndex + 3 < msgLen) {
        EmberAfReportingDirection direction;
        EmberAfStatus status;
        direction = emberAfGetInt8u(message, msgIndex, msgLen);
        msgIndex++;
        attrId = emberAfGetInt16u(message, msgIndex, msgLen);
        msgIndex += 2;
        emberAfReportingPrintln(" - direction:%x, attr:%2x", direction, attrId);
        switch (direction) {
        case EMBER_ZCL_REPORTING_DIRECTION_REPORTED:
          {
            int8u dataType;
            int16u minInterval, maxInterval;
            int32u reportableChange = 0;
            dataType = emberAfGetInt8u(message, msgIndex, msgLen);
            msgIndex++;
            minInterval = emberAfGetInt16u(message, msgIndex, msgLen);
            msgIndex += 2;
            maxInterval = emberAfGetInt16u(message, msgIndex, msgLen);
            msgIndex += 2;
            emberAfReportingPrintln("   type:%x, min:%2x, max:%2x",
                                    dataType,
                                    minInterval,
                                    maxInterval);
            if (emberAfGetAttributeAnalogOrDiscreteType(dataType)
                == EMBER_AF_DATA_TYPE_ANALOG) {
              int8u dataSize = emberAfGetDataSize(dataType);
              reportableChange = emberAfGetInt(message,
                                               msgIndex,
                                               msgLen,
                                               dataSize);
              emberAfReportingPrint("   change:");
              emberAfReportingPrintBuffer(message + msgIndex, dataSize, FALSE);
              emberAfReportingPrintln("");
              msgIndex += dataSize;
            }

            // Add a reporting entry for a reported attribute.  The reports will
            // be sent from us to the source of the Configure Reporting command.
            status = emberAfAddTxReportEntry(cmd->source,
                                             cmd->apsFrame->destinationEndpoint,
                                             cmd->apsFrame->sourceEndpoint,
                                             clusterId,
                                             attrId,
                                             clientServerMask,
                                             manufacturerCode,
                                             dataType,
                                             minInterval,
                                             maxInterval,
                                             reportableChange);
            break;
          }
        case EMBER_ZCL_REPORTING_DIRECTION_RECEIVED:
          {
            int16u timeout = emberAfGetInt16u(message, msgIndex, msgLen);
            msgIndex += 2;
            emberAfReportingPrintln("   timeout:%2x", timeout);

            // Add a reporting entry from a received attribute.  The reports
            // will be sent to us from the source of the Configure Reporting
            // command.
            status = emberAfAddRxReportEntry(cmd->source,
                                             cmd->apsFrame->sourceEndpoint,
                                             cmd->apsFrame->destinationEndpoint,
                                             clusterId,
                                             attrId,
                                             clientServerMask,
                                             manufacturerCode,
                                             timeout);
            break;
          }
        default:
          // This will abort the processing (see below).
          status = EMBER_ZCL_STATUS_INVALID_FIELD;
          break;
        }

        emberAfReportingFlush();

        // If a report cannot be configured, the status, direction, and
        // attribute are added to the response.  If the failure was due to an
        // invalid field, we have to abort after this record because we don't
        // know how to interpret the rest of the data in the request.
        if (status != EMBER_ZCL_STATUS_SUCCESS) {
          emberAfPutInt8uInResp(status);
          emberAfPutInt8uInResp(direction);
          emberAfPutInt16uInResp(attrId);
          failures = TRUE;
        }
        if (status == EMBER_ZCL_STATUS_INVALID_FIELD) {
          break;
        }
      }

      // We just respond with SUCCESS if we made it through without failures.
      if (!failures) {
        emberAfPutInt8uInResp(EMBER_ZCL_STATUS_SUCCESS);
      }
      emberAfSendResponse();
      return TRUE;
    }

  // ([direction:1] [attribute id:2])+
  case ZCL_READ_REPORTING_CONFIGURATION_COMMAND_ID:
    emberAfReportingPrint("%p: ", "READ_RPT_CFG");
    emberAfReportingDebugExec(emberAfDecodeAndPrintCluster(clusterId));
    emberAfReportingPrintln("");
    emberAfReportingFlush();

    emberAfPutInt8uInResp(ZCL_READ_REPORTING_CONFIGURATION_RESPONSE_COMMAND_ID);

    // Each record in the command has a one-byte direction and a two-byte
    // attribute id.
    while (msgIndex + 3 <= msgLen) {
      EmberAfAttributeId attrId;
      EmberAfAttributeMetadata *metadata;
      EmberAfReportEntry *entry;
      EmberAfReportingDirection direction;
      int8u sourceEndpoint, destinationEndpoint;
      direction = emberAfGetInt8u(message, msgIndex, msgLen);
      msgIndex++;
      attrId = emberAfGetInt16u(message, msgIndex, msgLen);
      msgIndex += 2;
      switch (direction) {
      case EMBER_ZCL_REPORTING_DIRECTION_REPORTED:
        metadata = emberAfLocateAttributeMetadata(cmd->apsFrame->destinationEndpoint,
                                                  clusterId,
                                                  attrId,
                                                  clientServerMask,
                                                  manufacturerCode);
        if (metadata == NULL) {
          emberAfPutInt8uInResp(EMBER_ZCL_STATUS_UNSUPPORTED_ATTRIBUTE);
          emberAfPutInt8uInResp(direction);
          emberAfPutInt16uInResp(attrId);
          continue;
        }
        sourceEndpoint = cmd->apsFrame->destinationEndpoint;
        destinationEndpoint = cmd->apsFrame->sourceEndpoint;
        break;
      case EMBER_ZCL_REPORTING_DIRECTION_RECEIVED:
        sourceEndpoint = cmd->apsFrame->sourceEndpoint;
        destinationEndpoint = cmd->apsFrame->destinationEndpoint;
        break;
      default:
        emberAfPutInt8uInResp(EMBER_ZCL_STATUS_INVALID_FIELD);
        emberAfPutInt8uInResp(direction);
        emberAfPutInt16uInResp(attrId);
        continue;
      }

      entry = emberAfFindReportEntry(direction,
                                     cmd->source,
                                     sourceEndpoint,
                                     destinationEndpoint,
                                     clusterId,
                                     attrId,
                                     clientServerMask,
                                     manufacturerCode);

      // 075123r03 seems to suggest that SUCCESS is returned even if reporting
      // isn't configured for the requested attribute.  The individual fields
      // of the response for this attribute get populated with defaults.
      emberAfPutInt8uInResp(EMBER_ZCL_STATUS_SUCCESS);
      emberAfPutInt8uInResp(direction);
      emberAfPutInt16uInResp(attrId);

      switch (direction) {
        case EMBER_ZCL_REPORTING_DIRECTION_REPORTED:
          emberAfPutInt8uInResp(metadata->attributeType);
          emberAfPutInt16uInResp(entry == NULL ? 0xFFFF : entry->minInterval);
          emberAfPutInt16uInResp(entry == NULL ? 0xFFFF : entry->maxInterval);
          if (emberAfGetAttributeAnalogOrDiscreteType(metadata->attributeType)
              == EMBER_AF_DATA_TYPE_ANALOG) {
            emAfPutReportableChangeInResponse(entry, metadata->attributeType);
          }
          break;
        case EMBER_ZCL_REPORTING_DIRECTION_RECEIVED:
          emberAfPutInt16uInResp(entry == NULL ? 0xFFFF : entry->timeout);
          break;
      }
    }
    emberAfSendResponse();
    return TRUE;
#endif //ZA_NO_REPORTING_OPTIMIZATION

  // ([attribute id:2] [status:1] [type:0/1] [value:0/V])+
  case ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID:
    // The "timesync" command in the CLI sends a Read Attributes command for the
    // Time attribute on another device and then sets a flag.  If that flag is
    // set and a Read Attributes Response command for the time comes in, we set
    // the time to the value in the message.
    if (clusterId == ZCL_TIME_CLUSTER_ID) {
      if (emAfSyncingTime
          && !cmd->mfgSpecific
          && msgLen - msgIndex == 8 // attr:2 status:1 type:1 data:4
          && (emberAfGetInt16u(message, msgIndex, msgLen)
              == ZCL_TIME_ATTRIBUTE_ID)
          && (emberAfGetInt8u(message, msgIndex + 2, msgLen)
              == EMBER_ZCL_STATUS_SUCCESS)
          && (emberAfGetInt8u(message, msgIndex + 3, msgLen)
              == ZCL_UTC_TIME_ATTRIBUTE_TYPE)) {
        emberAfSetTime(emberAfGetInt32u(message, msgIndex + 4, msgLen));
        emberAfDebugPrintln("time sync ok, time: %4x", emberAfGetCurrentTime());
        emAfSyncingTime = FALSE;
      }
#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
      emAfPluginSmartEnergyRegistrationReadAttributesResponseCallback(message + msgIndex,
                                                                      msgLen - msgIndex);
#endif //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_ESI_DISCOVERY_REQUIRED
    }

#ifdef EMBER_AF_PLUGIN_TRUST_CENTER_KEEPALIVE
    if (clusterId == ZCL_KEY_ESTABLISHMENT_CLUSTER_ID
        && !cmd->mfgSpecific
        && msgLen - msgIndex == 6 // attr:2 status:1 type:1 data:2
        && (emberAfGetInt16u(message, msgIndex, msgLen)
            == ZCL_KEY_ESTABLISHMENT_SUITE_SERVER_ATTRIBUTE_ID)) {
      emAfPluginTrustCenterKeepaliveReadAttributesResponseCallback(message + msgIndex,
                                                                   msgLen - msgIndex);
    }
#endif //EMBER_AF_PLUGIN_TRUST_CENTER_KEEPALIVE

    if (!emberAfReadAttributesResponseCallback(clusterId,
                                               message + msgIndex,
                                               msgLen - msgIndex)) {
      emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_SUCCESS);
    }
    return TRUE;

  // ([status:1] [attribute id:2])+
  case ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID:
    if (!emberAfWriteAttributesResponseCallback(clusterId,
                                                message + msgIndex,
                                                msgLen - msgIndex)) {
      emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_SUCCESS);
    }
    return TRUE;

  // ([status:1] [direction:1] [attribute id:2])+
  case ZCL_CONFIGURE_REPORTING_RESPONSE_COMMAND_ID:
    if (!emberAfConfigureReportingResponseCallback(clusterId,
                                                   message + msgIndex,
                                                   msgLen - msgIndex)) {
      emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_SUCCESS);
    }
    return TRUE;


  // ([status:1] [direction:1] [attribute id:2] [type:0/1] ...
  // ... [min interval:0/2] [max interval:0/2] [reportable change:0/V] ...
  // ... [timeout:0/2])+
  case ZCL_READ_REPORTING_CONFIGURATION_RESPONSE_COMMAND_ID:
    if (!emberAfReadReportingConfigurationResponseCallback(clusterId,
                                                           message + msgIndex,
                                                           msgLen - msgIndex)) {
      emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_SUCCESS);
    }
    return TRUE;

  // ([attribute id:2] [type:1] [data:V])+
  case ZCL_REPORT_ATTRIBUTES_COMMAND_ID:
    if (!emberAfReportAttributesCallback(clusterId,
                                         message + msgIndex,
                                         msgLen - msgIndex)) {
      emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_SUCCESS);
    }
    return TRUE;

  // [command id:1] [status:1]
  case ZCL_DEFAULT_RESPONSE_COMMAND_ID:
    {
      EmberAfStatus status;
      int8u commandId;
      commandId = emberAfGetInt8u(message, msgIndex, msgLen);
      msgIndex++;
      status = emberAfGetInt8u(message, msgIndex, msgLen);

      emberAfClusterDefaultResponseCallback(cmd->apsFrame->destinationEndpoint,
                                            clusterId,
                                            commandId,
                                            status,
                                            clientServerMask);
      emberAfDefaultResponseCallback(clusterId, commandId, status);
      return TRUE;
    }

  // [discovery complete:1] ([attribute id:2] [type:1])*
  case ZCL_DISCOVER_ATTRIBUTES_RESPONSE_COMMAND_ID:
    {
      boolean discoveryComplete = emberAfGetInt8u(message, msgIndex, msgLen);
      msgIndex++;
      if (!emberAfDiscoverAttributesResponseCallback(clusterId,
                                                     discoveryComplete,
                                                     message + msgIndex,
                                                     msgLen - msgIndex)) {
        emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_SUCCESS);
      }
      return TRUE;
    }
  }

  emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_UNSUP_GENERAL_COMMAND);
  return TRUE;
}
