// *******************************************************************
// * report-table.c
// *
// * This reporting code is an implementation of the ZCL reporting
// * mechanism as described in the ZCL spec.
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "app/framework/include/af.h"
#include "app/framework/util/common.h"
#include "app/framework/report/report-table.h"

#ifndef ZA_NO_REPORTING_OPTIMIZATION
EmberEventControl emAfReportTableEventControl;

// storage for the report entries.
// EMBER_AF_REPORT_TABLE_SIZE is set in config.h
static EmberAfReportEntry emAfReportTable[EMBER_AF_REPORT_TABLE_SIZE];

#define READ_DATA_SIZE 8 // max size for reported data.

// forward declaration
static void emAfScheduleNextOrDeactivateReportTick(void);

// Currently, this function only checks on entries to be reported (i.e., those
// that need to be sent).
void emberAfReportTableTick(void)
{
  static int32u lastTime = 0;
  EmberNodeId nodeId;
  EmberApsFrame *apsFrame = emberAfGetCommandApsFrame();
  boolean clientToServer;
  int16u manufacturerCode;
  EmberAfStatus status;
  EmberAfAttributeType dataType;
  int32u currentTime = halCommonGetInt32uMillisecondTick();
  int8u i, dataSize;
  boolean madeHeader = FALSE;
  int8u readData[READ_DATA_SIZE];
  int32u elapsed;

  // Check to see how many seconds have elapsed.  This will be used later to
  // increase currentInterval.
  elapsed = (elapsedTimeInt32u(lastTime, currentTime)
             / MILLISECOND_TICKS_PER_SECOND);
  lastTime = currentTime;

  // Go through the table looking for TX entries ready to send.
  for (i = 0; i < EMBER_AF_REPORT_TABLE_SIZE; i++) {
    EmberAfReportEntry *entry = &emAfReportTable[i];

    // Check to see if an entry needs to be cleaned up.
    if (entry->failCount >= EMBER_AF_REPORT_FAILURE_LIMIT) {
      entry->inUse = FALSE;
      emberAfReportEntryConfiguredCallback(entry);
      continue;
    }

    // We only handle TX reporting.
    if (!entry->inUse
        || entry->direction != EMBER_ZCL_REPORTING_DIRECTION_REPORTED) {
      continue;
    }

    // Increase current second count.
    entry->currentInterval += elapsed;

    // If the minimum interval has not yet elapsed, we will not report.
    if (entry->currentInterval < entry->minInterval) {
      continue;
    }

    // Read the current value so we can check the difference.
    status = emAfReadAttribute(entry->sourceEndpoint,
                               entry->clusterId,
                               entry->attributeId,
                               entry->mask,
                               entry->manufacturerCode,
                               (int8u *)&readData,
                               READ_DATA_SIZE,
                               &dataType);
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      emberAfReportingPrintln("ERR: reading cluster 0x%2x attribute 0x%2x: 0x%x",
                              entry->clusterId,
                              entry->attributeId,
                              status);
      continue;
    }

    // If periodic reporting is disabled (i.e., the maximum interval is set to
    // zero) or the current interval is less than the maximum interval, we will
    // only send a report if there has been a reportable change.
    if (entry->maxInterval == 0x0000
        || entry->currentInterval < entry->maxInterval) {
      int32u difference = emberAfGetDifference(readData,
                                               entry->lastReportValue,
                                               emberAfGetDataSize(dataType));
      if (emberAfGetAttributeAnalogOrDiscreteType(dataType)
          == EMBER_AF_DATA_TYPE_ANALOG) {
        if (difference < entry->reportableChange) {
          continue;
        }
      } else if (difference == 0) {
        continue;
      }
    }

    // If we have already started a report for a different attribute or
    // destination, send it and create a new one.
    if (madeHeader &&
        !(entry->nodeId == nodeId
          && entry->sourceEndpoint == apsFrame->sourceEndpoint
          && entry->destinationEndpoint == apsFrame->destinationEndpoint
          && entry->clusterId == apsFrame->clusterId
          && emberAfClusterIsClient(entry) == clientToServer
          && entry->manufacturerCode == manufacturerCode)) {
      emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, nodeId);
      madeHeader = FALSE;
    }

    // If we haven't made the message header, make it.
    if (!madeHeader) {
      madeHeader = TRUE;
      clientToServer = emberAfClusterIsClient(entry);
      // The manufacturer-specfic version of the fill API only creates a
      // manufacturer-specfic command if the manufacturer code is set.  For
      // non-manufacturer-specfic reports, the manufacturer code is unset, so
      // we can get away with using this API for both cases.
      emberAfFillExternalManufacturerSpecificBuffer((ZCL_PROFILE_WIDE_COMMAND
                                                     | (clientToServer
                                                        ? ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                                                        : ZCL_FRAME_CONTROL_SERVER_TO_CLIENT)),
                                                    entry->clusterId,
                                                    entry->manufacturerCode,
                                                    ZCL_REPORT_ATTRIBUTES_COMMAND_ID,
                                                    "");
      nodeId = entry->nodeId;
      apsFrame->sourceEndpoint = entry->sourceEndpoint;
      apsFrame->destinationEndpoint = entry->destinationEndpoint;
      apsFrame->options = EMBER_AF_DEFAULT_APS_OPTIONS;
      manufacturerCode = entry->manufacturerCode;
    }

    // Payload is [attribute id:2] [type:1] [data:N].
    emberAfPutInt16uInResp(entry->attributeId);
    emberAfPutInt8uInResp(dataType);

    dataSize = emberAfGetDataSize(dataType);

#if (BIGENDIAN_CPU)
    if (isThisDataTypeSentLittleEndianOTA(dataType)) {
      int8u i;
      for (i = 0; i < dataSize; i++) {
        emberAfPutInt8uInResp(readData[dataSize - i - 1]);
      }
    } else {
      emberAfPutBlockInResp(readData, dataSize);
    }
#else
    emberAfPutBlockInResp(readData, dataSize);
#endif

    // clear out the curr interval and set the last reported value
    entry->currentInterval = 0;
    // Store the last value reported so that we can track changes.  We only do
    // this for data types that are small enough for us to compare.
    if (dataSize <= sizeof(entry->lastReportValue)) {
      entry->lastReportValue = 0;
#if (BIGENDIAN_CPU)
      MEMCOPY(((int8u *)&entry->lastReportValue
               + sizeof(entry->lastReportValue)
               - dataSize),
              readData,
              dataSize);
#else
      MEMCOPY(&entry->lastReportValue, readData, dataSize);
#endif
    }
  }

  if (madeHeader) {
    emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, nodeId);
  }
  emAfScheduleNextOrDeactivateReportTick();
}

EmberAfStatus emberAfAddRxReportEntry(EmberNodeId nodeId,
                                      int8u sourceEndpoint,
                                      int8u destinationEndpoint,
                                      EmberAfClusterId clusterId,
                                      EmberAfAttributeId attributeId,
                                      int8u mask,
                                      int16u manufacturerCode,
                                      int16u timeout)
{
  EmberAfReportEntry *entry;
  EmberAfStatus status;

  // Check the table for an entry that matches this request.  If one exists, it
  // will be overwritten with the new configuration.
  entry = emberAfFindReportEntry(EMBER_ZCL_REPORTING_DIRECTION_RECEIVED,
                                 nodeId,
                                 sourceEndpoint,
                                 destinationEndpoint,
                                 clusterId,
                                 attributeId,
                                 mask,
                                 manufacturerCode);

  // If we didn't find a match, look for an open slot in the table.  Abort if
  // there are no slots for this request.
  if (entry == NULL) {
    entry = emberAfFindAvailableReportEntry();
    if (entry == NULL) {
      return EMBER_ZCL_STATUS_INSUFFICIENT_SPACE;
    }
  }

  // Write the report configuration.
  entry->inUse = TRUE;
  entry->direction = EMBER_ZCL_REPORTING_DIRECTION_RECEIVED;
  entry->nodeId = nodeId;
  entry->sourceEndpoint = sourceEndpoint;
  entry->destinationEndpoint = destinationEndpoint;
  entry->clusterId = clusterId;
  entry->attributeId = attributeId;
  entry->mask = mask;
  entry->manufacturerCode = manufacturerCode;
  entry->minInterval = 0;      // not used for received reports
  entry->maxInterval = 0;      // not used for received reports
  entry->currentInterval = 0;  // not used for received reports
  entry->reportableChange = 0; // not used for received reports
  entry->lastReportValue = 0;  // not used for received reports
  entry->timeout = timeout;
  entry->failCount = 0;        // not used for received reports

  // The application may reject the configuration.
  status = emberAfReportEntryConfiguredCallback(entry);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    entry->inUse = FALSE;
  }
  return status;
}

EmberAfStatus emberAfAddTxReportEntry(EmberNodeId nodeId,
                                      int8u sourceEndpoint,
                                      int8u destinationEndpoint,
                                      EmberAfClusterId clusterId,
                                      EmberAfAttributeId attributeId,
                                      int8u mask,
                                      int16u manufacturerCode,
                                      EmberAfAttributeType dataType,
                                      int16u minInterval,
                                      int16u maxInterval,
                                      int32u reportableChange)
{
  EmberAfReportEntry *entry;
  EmberAfStatus status;
  EmberAfAttributeType realDataType;

  // Verify that we support the attribute and that the data type matches.
  status = emAfReadAttribute(sourceEndpoint,
                             clusterId,
                             attributeId,
                             mask,
                             manufacturerCode,
                             NULL, // data
                             0,    // max length
                             &realDataType);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    return status;
  } else if (dataType != realDataType) {
    return EMBER_ZCL_STATUS_INVALID_DATA_TYPE;
  }

  // Verify the minimum and maximum intervals make sense.
  if (maxInterval != 0 && maxInterval < minInterval) {
    return EMBER_ZCL_STATUS_INVALID_VALUE;
  }

  // Check the table for an entry that matches this request.  If one exists, it
  // will be overwritten with the new configuration.
  entry = emberAfFindReportEntry(EMBER_ZCL_REPORTING_DIRECTION_REPORTED,
                                 nodeId,
                                 sourceEndpoint,
                                 destinationEndpoint,
                                 clusterId,
                                 attributeId,
                                 mask,
                                 manufacturerCode);

  // If the maximum reporting interval is 0xFFFF, the device shall not issue
  // reports for the attribute and the configuration information for that
  // attribute need not be maintained.
  if (maxInterval == 0xFFFF) {
    if (entry != NULL) {
      entry->inUse = FALSE;
      emberAfReportEntryConfiguredCallback(entry);
      emAfScheduleNextOrDeactivateReportTick();
    }
    return EMBER_ZCL_STATUS_SUCCESS;
  }

  // If we didn't find a match, look for an open slot in the table.  Abort if
  // there are no slots for this request.
  if (entry == NULL) {
    entry = emberAfFindAvailableReportEntry();
    if (entry == NULL) {
      return EMBER_ZCL_STATUS_INSUFFICIENT_SPACE;
    }
  }

  // Write the report configuration.
  entry->inUse = TRUE;
  entry->direction = EMBER_ZCL_REPORTING_DIRECTION_REPORTED;
  entry->nodeId = nodeId;
  entry->sourceEndpoint = sourceEndpoint;
  entry->destinationEndpoint = destinationEndpoint;
  entry->clusterId = clusterId;
  entry->attributeId = attributeId;
  entry->mask = mask;
  entry->manufacturerCode = manufacturerCode;
  entry->minInterval = minInterval;
  entry->maxInterval = maxInterval;
  entry->currentInterval = 0;
  entry->reportableChange = reportableChange;
  entry->lastReportValue = 0;
  entry->timeout = 0; // not used for reported reports
  entry->failCount = 0;

  // The application may reject the configuration.
  status = emberAfReportEntryConfiguredCallback(entry);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    entry->inUse = FALSE;
  }
  emAfScheduleNextOrDeactivateReportTick();
  return status;
}

EmberAfReportEntry *emberAfFindReportEntry(EmberAfReportingDirection direction,
                                           EmberNodeId nodeId,
                                           int8u sourceEndpoint,
                                           int8u destinationEndpoint,
                                           EmberAfClusterId clusterId,
                                           EmberAfAttributeId attributeId,
                                           int8u mask,
                                           int16u manufacturerCode)
{
  EmberAfReportEntry *entry;
  int8u i;

  for (i = 0; i < EMBER_AF_REPORT_TABLE_SIZE; i++) {
    entry = &emAfReportTable[i];
    if (entry->inUse
        && entry->direction == direction
        && entry->nodeId == nodeId
        && entry->sourceEndpoint == sourceEndpoint
        && entry->destinationEndpoint == destinationEndpoint
        && entry->clusterId == clusterId
        && entry->attributeId == attributeId
        && entry->mask == mask
        && entry->manufacturerCode == manufacturerCode) {
      return entry;
    }
  }
  return NULL;
}

EmberAfReportEntry *emberAfFindAvailableReportEntry(void)
{
  EmberAfReportEntry *entry;
  int8u i;
  
  for (i = 0; i < EMBER_AF_REPORT_TABLE_SIZE; i++) {
    entry = &emAfReportTable[i];
    if (!entry->inUse) {
      return entry;
    }
  }
  return NULL;
}

void emberAfPrintReportTable(void)
{
  int8u i;
  EmberAfReportEntry* entry;

  for (i = 0; i < EMBER_AF_REPORT_TABLE_SIZE; i++) {
    entry = &emAfReportTable[i];
    emberAfReportingPrint("%x:", i);
    if (entry->inUse) {
      emberAfReportingPrint("clus %2x attr %2x ",
                            entry->clusterId,
                            entry->attributeId);
      if (entry->direction == EMBER_ZCL_REPORTING_DIRECTION_REPORTED) {
        emberAfReportingPrint("report-to ep %x on %2x from ep %x "
                              "min %2x max %2x curr %2x "
                              "rpt-chg %4x last-rpt-val %4x",
                              entry->destinationEndpoint,
                              entry->nodeId,
                              entry->sourceEndpoint,
                              entry->minInterval,
                              entry->maxInterval,
                              entry->currentInterval,
                              entry->reportableChange,
                              entry->lastReportValue);
      } else {
        emberAfReportingPrint("report-from ep %x on %2x to ep %x timeout %2x",
                              entry->sourceEndpoint,
                              entry->nodeId,
                              entry->destinationEndpoint,
                              entry->timeout);
      }
    }
    emberAfReportingPrintln("");
    emberAfReportingFlush();
  }
}

void emberAfReportTableClear(void)
{
  int8u i;
  for (i = 0; i < EMBER_AF_REPORT_TABLE_SIZE; i++) {
    emAfReportTable[i].inUse = FALSE;
  }
  emAfScheduleNextOrDeactivateReportTick();
}

void emberAfUpdateReportEntryStatus(EmberNodeId nodeId,
                                    int8u sourceEndpoint,
                                    int8u destinationEndpoint,
                                    EmberAfClusterId clusterId,
                                    int8u mask,
                                    int16u manufacturerCode,
                                    EmberStatus messageSentStatus)
{
  // All reports for a given node, source, destination, and cluster should go
  // out in a single message, so mark update all the matching reporting entries
  // regardless of attribute id.
  int8u i;
  for (i = 0; i < EMBER_AF_REPORT_TABLE_SIZE; i++) {
    EmberAfReportEntry *entry = &emAfReportTable[i];
    if (entry->inUse
        && entry->direction == EMBER_ZCL_REPORTING_DIRECTION_REPORTED
        && entry->nodeId == nodeId
        && entry->sourceEndpoint == sourceEndpoint
        && entry->destinationEndpoint == destinationEndpoint
        && entry->clusterId == clusterId
        && entry->mask == mask
        && entry->manufacturerCode == manufacturerCode) {
      if (messageSentStatus == EMBER_SUCCESS) {
        entry->failCount = 0;
      } else {
        entry->failCount++;
      }
    }
  }
}

void emAfScheduleNextOrDeactivateReportTick(void) {
  int16u reportIntervalSeconds = MAX_INT16U_VALUE;
  int8u i;
  boolean foundLiveEntry = FALSE;
  for (i = 0; i < EMBER_AF_REPORT_TABLE_SIZE; i++) {
    // Only schedule ticks for entries that are active and transmitting reports.
    EmberAfReportEntry *entry = &emAfReportTable[i];
    if (entry->inUse
        && entry->direction == EMBER_ZCL_REPORTING_DIRECTION_REPORTED) {
      // For a given report entry, a tick is not required until the minimum
      // reporting interval has elapsed.  Once it has, we have to tick often so
      // that we can watch for a reportable change to occur or for the maximum
      // interval to elapse.  As we look at each entry, keep track of the
      // smallest delay for all entries.  This will be how long we sleep.
      int16u remainingSeconds = (entry->currentInterval < entry->minInterval
                                 ? entry->minInterval - entry->currentInterval
                                 : EMBER_AF_REPORT_TICK_INTERVAL);
      if (remainingSeconds < reportIntervalSeconds) {
        reportIntervalSeconds = remainingSeconds;
      }
      foundLiveEntry = TRUE;
    }
  }
  if (foundLiveEntry) {
    emberAfDebugPrintln("sched report event for: %d", reportIntervalSeconds);
    emberAfEventControlSetDelay(&emAfReportTableEventControl,
                                (reportIntervalSeconds
                                 * MILLISECOND_TICKS_PER_SECOND));
  } else {
    emberAfDebugPrintln("deactivate report event.");
    emberEventControlSetInactive(emAfReportTableEventControl);
  }
}
#endif
