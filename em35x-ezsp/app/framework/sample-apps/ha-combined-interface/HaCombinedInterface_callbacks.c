// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
//

// This callback file is created for your convenience. You may add application code
// to this file. If you regenerate this file over a previous version, the previous
// version will be overwritten and any code you have added will be lost.

#include "app/framework/include/af.h"
#include "app/framework/util/util.h"

#define HA_PROFILE_ID 0x0104

static boolean foundLight = FALSE;
static boolean lookingForLight = FALSE;
static EmberNodeId lightId = EMBER_NULL_NODE_ID;

  
static void lightDiscoveryCallback(const EmberAfServiceDiscoveryResult* result) 
{
  int8u i;
  
  if (emberAfHaveDiscoveryResponseStatus(result->status)) {
    const EmberAfEndpointList* epList
      = (const EmberAfEndpointList*)result->responseData;
    emberAfCorePrintln("found light: 0x%2x", result->matchAddress);
    for (i = 0; i < epList->count; i++) {
      emberAfCorePrintln("  ept: 0x%x", epList->list[i]);
    }
    // store information of the first light we found
    if (!foundLight) {
      lightId = result->matchAddress;
      foundLight = TRUE;
    }
  } else if (result->status == EMBER_AF_BROADCAST_SERVICE_DISCOVERY_COMPLETE) {
    emberAfCorePrintln("This is all the lights found.");
    lookingForLight = FALSE;
  }
}

/** @brief Main Tick
 *
 * Whenever main application tick is called, this callback will be called at
 * the end of the main tick execution.
 *
 */
void emberAfMainTickCallback(void)
{
  EmberStatus status;
  
  // if we are not part of the network, clear the light id; if not 
  // already done so.
  if(emberNetworkState() != EMBER_JOINED_NETWORK) {
    if(lightId != EMBER_NULL_NODE_ID) {
      lightId = EMBER_NULL_NODE_ID;
      foundLight = FALSE;
    }
  } else {
    // if we are on the network, discover the light if we have not done it
    // already.
    if (lightId == EMBER_NULL_NODE_ID && !foundLight && !lookingForLight) {
      emberAfCorePrintln("Find a light");
      status
        = emberAfFindDevicesByProfileAndCluster(
            EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS,
            HA_PROFILE_ID,
            ZCL_ON_OFF_CLUSTER_ID,
            EMBER_AF_SERVER_CLUSTER_DISCOVERY,
            lightDiscoveryCallback);
      if (status != EMBER_SUCCESS) { // server cluster
        emberAfDebugPrintln("Cannot find light, error 0x%x", status);
      } else {
        // the boolean is used so we do not keep sending match descriptor
        // request everytime mainTick is call while waiting for match
        // descriptor response.
        lookingForLight = TRUE;
      }
    } // check lightId value
  }
}

/** @brief Configure Reporting Response
 *
 * This function is called by the application framework when a Configure
 * Reporting Response command is received from an external device.  The
 * application should return TRUE if the message was processed or FALSE if it
 * was not.
 *
 * @param clusterId The cluster identifier of this response.
 * @param buffer Buffer containing the list of attribute status records.
 * @param bufLen The length in bytes of the list.
 */
boolean emberAfConfigureReportingResponseCallback(EmberAfClusterId clusterId, 
                                                  int8u *buffer, 
                                                  int16u bufLen)
{
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_REPORTING)
  int16u bufIndex = 0;
  emberAfReportingPrint("%p_RESP: ", "CFG_RPT");
  emberAfReportingDebugExec(emberAfDecodeAndPrintCluster(clusterId));
  emberAfReportingPrintln("");
  emberAfReportingFlush();

  // Each record in the response has a one-byte status.  If the status is not
  // SUCCESS, the record will also contain a one-byte direction and a two-byte
  // attribute id.
  while (bufIndex + 1 <= bufLen) {
    EmberAfStatus status = (EmberAfStatus)emberAfGetInt8u(buffer,
                                                          bufIndex,
                                                          bufLen);
    bufIndex++;
    emberAfReportingPrintln(" - status:%x", status);
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      EmberAfReportingDirection direction;
      EmberAfAttributeId attributeId;
      direction =  (EmberAfReportingDirection)emberAfGetInt8u(buffer,
                                                              bufIndex,
                                                              bufLen);
      bufIndex++;
      attributeId = (EmberAfAttributeId)emberAfGetInt16u(buffer,
                                                         bufIndex,
                                                         bufLen);
      bufIndex += 2;
      emberAfReportingPrintln("   direction:%x, attr:%2x",
                              direction,
                              attributeId);
    }
    emberAfReportingFlush();
  }
#endif //EMBER_AF_PRINT_ENABLE && EMBER_AF_PRINT_REPORTING
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

/** @brief Read Reporting Configuration Response
 *
 * This function is called by the application framework when a Read Reporting
 * Configuration Response command is received from an external device.  The
 * application should return TRUE if the message was processed or FALSE if it
 * was not.
 *
 * @param clusterId The cluster identifier of this response.
 * @param buffer Buffer containing the list of attribute reporting configuration records.
 * @param bufLen The length in bytes of the list.
 */
boolean emberAfReadReportingConfigurationResponseCallback(EmberAfClusterId clusterId, 
                                                          int8u *buffer, 
                                                          int16u bufLen)
{
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_REPORTING)
  int16u bufIndex = 0;
  emberAfReportingPrint("%p_RESP: ", "READ_RPT_CFG");
  emberAfReportingDebugExec(emberAfDecodeAndPrintCluster(clusterId));
  emberAfReportingPrintln("");
  emberAfReportingFlush();

  // Each record in the response has a one-byte status, a one-byte direction,
  // and a two-byte attribute id.  If the status is SUCCESS, the record will
  // contain additional fields.
  while (bufIndex + 4 <= bufLen) {
    EmberAfAttributeId attributeId;
    EmberAfStatus status;
    EmberAfReportingDirection direction;
    status = (EmberAfStatus)emberAfGetInt8u(buffer, bufIndex, bufLen);
    bufIndex++;
    direction = (EmberAfReportingDirection)emberAfGetInt8u(buffer,
                                                           bufIndex,
                                                           bufLen);
    bufIndex++;
    attributeId = (EmberAfAttributeId)emberAfGetInt16u(buffer,
                                                       bufIndex,
                                                       bufLen);
    bufIndex += 2;
    emberAfReportingPrintln(" - status:%x, direction:%x, attr:%2x",
                            status,
                            direction,
                            attributeId);
    if (status == EMBER_ZCL_STATUS_SUCCESS) {
      // If the direction indicates the attribute is reported, the record will
      // contain a one-byte type and two two-byte intervals.  If the type is
      // analog, the record will contain a reportable change of the same data
      // type.  If the direction indicates reports of the attribute are
      // received, the record will contain a two-byte timeout.
      switch (direction) {
      case EMBER_ZCL_REPORTING_DIRECTION_REPORTED:
        {
          int16u minInterval, maxInterval;
          int8u dataType;
          dataType = emberAfGetInt8u(buffer, bufIndex, bufLen);
          bufIndex++;
          minInterval = emberAfGetInt16u(buffer, bufIndex, bufLen);
          bufIndex += 2;
          maxInterval = emberAfGetInt16u(buffer, bufIndex, bufLen);
          bufIndex += 2;
          emberAfReportingPrintln("   type:%x, min:%2x, max:%2x",
                                  dataType,
                                  minInterval,
                                  maxInterval);
          if (emberAfGetAttributeAnalogOrDiscreteType(dataType)
              == EMBER_AF_DATA_TYPE_ANALOG) {
            int8u dataSize = emberAfGetDataSize(dataType);
            emberAfReportingPrint("   change:");
            emberAfReportingPrintBuffer(buffer + bufIndex, dataSize, FALSE);
            emberAfReportingPrintln("");
            bufIndex += dataSize;
          }
          break;
        }
      case EMBER_ZCL_REPORTING_DIRECTION_RECEIVED:
        {
          int16u timeout = emberAfGetInt16u(buffer, bufIndex, bufLen);
          bufIndex += 2;
          emberAfReportingPrintln("   timeout:%2x", timeout);
          break;
        }
      default:
        emberAfReportingPrintln("ERR: unknown direction %x", direction);
        emberAfSendDefaultResponse(emberAfCurrentCommand(),
                                   EMBER_ZCL_STATUS_INVALID_FIELD);
        return TRUE;
      }
    }
    emberAfReportingFlush();
  }
#endif //EMBER_AF_PRINT_ENABLE && EMBER_AF_PRINT_REPORTING
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

/** @brief Report Attributes
 *
 * This function is called by the application framework when a Report
 * Attributes command is received from an external device.  The application
 * should return TRUE if the message was processed or FALSE if it was not.
 *
 * @param clusterId The cluster identifier of this command.
 * @param buffer Buffer containing the list of attribute report records.
 * @param bufLen The length in bytes of the list.
 */
boolean emberAfReportAttributesCallback(EmberAfClusterId clusterId, 
                                        int8u *buffer, 
                                        int16u bufLen)
{
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_REPORTING)
  int16u bufIndex = 0;
  emberAfReportingPrint("RPT_ATTR: ");
  emberAfReportingDebugExec(emberAfDecodeAndPrintCluster(clusterId));
  emberAfReportingPrintln("");

  // Each record in the response has a two-byte attribute id, a one-byte
  // type, and variable-length data.
  while (bufIndex + 3 < bufLen) {
    EmberAfAttributeId attributeId;
    int8u dataType, dataSize;
    attributeId = (EmberAfAttributeId)emberAfGetInt16u(buffer,
                                                       bufIndex,
                                                       bufLen);
    bufIndex += 2;
    dataType = emberAfGetInt8u(buffer, bufIndex, bufLen);
    bufIndex++;

    // For strings, the data size is the length of the string (specified by
    // the first byte of data) plus one for the length byte itself.  For
    // everything else, the size is just the size of the data type.
    dataSize = (emberAfIsThisDataTypeAStringType(dataType)
                ? emberAfStringLength(buffer + bufIndex) + 1
                : emberAfGetDataSize(dataType));

    emberAfReportingPrintln(" - attr:%2x", attributeId);
    emberAfReportingPrint("   type:%x, val:", dataType);
    if (emberAfIsThisDataTypeAStringType(dataType)) {
      emberAfReportingPrintString(buffer + bufIndex);
    } else {
      emberAfReportingPrintBuffer(buffer + bufIndex, dataSize, FALSE);
    }
    emberAfReportingPrintln("");
    // display specific message for on/off cluster report
    if((clusterId == ZCL_ON_OFF_CLUSTER_ID) 
      && (attributeId == ZCL_ON_OFF_ATTRIBUTE_ID)) {
      int8u lightValue = emberAfGetInt8u(buffer, bufIndex, bufLen);
      emberAfReportingPrintln("************************");
      emberAfReportingPrintln(" Light is now %p", (lightValue > 0 ? "ON" : "OFF"));
      emberAfReportingPrintln("************************");
    }
    emberAfReportingFlush();
    bufIndex += dataSize;
  }
#endif //EMBER_AF_PRINT_ENABLE && EMBER_AF_PRINT_REPORTING
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

/** @brief Finished
 *
 * This callback is fired when the network-find plugin is finished with the
 * forming or joining process.  The result of the operation will be returned
 * in the status parameter.
 *
 * @param status   Ver.: always
 */
void emberAfPluginNetworkFindFinishedCallback(EmberStatus status) {
  
}
