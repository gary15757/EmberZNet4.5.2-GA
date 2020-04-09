// *******************************************************************
// * report-table.h
// *
// * This reporting code is an implementation of the ZCL reporting mechanism as
// * described in the ZCL spec.
// *
// * This table is used to schedule both the sending (REPORTED) and receiving
// * (RECEIVED) of reported attributes.
// *
// * ATTRIBUTE REPORTING:
// * Attributes which the application will report are entered with the
// * EMBER_ZCL_REPORTING_DIRECTION_REPORTED flag in the entries direction field.
// * This signifies that, for this attribute, the device is acting as a
// * reporting SERVER and is responsible for reporting the attribute to the
// * reporting CLIENT.
// *
// * ATTRIBUTE RECEIVING:
// * Attributes which are going to be reported to this device are entered with
// * EMBER_ZCL_REPORTING_DIRECTION_RECEIVED flag in the entries direction field.
// * This signifies that, for this attribute, the device is acting as the
// * reporting CLIENT and is responsible for receiving the reported attribute
// * and taking the appropriate action when the associated server fails to
// * report the attribute in a timely fashion.
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// Report tick interval in seconds
#ifndef EMBER_AF_REPORT_TICK_INTERVAL
  #define EMBER_AF_REPORT_TICK_INTERVAL 1
#endif

// Maximum number of failures allowed before cleaning up a reported report.
#ifndef EMBER_AF_REPORT_FAILURE_LIMIT
  #define EMBER_AF_REPORT_FAILURE_LIMIT 3
#endif

/**
 * Prints out the entire report table
 */
void emberAfPrintReportTable(void);

/**
 * Checks report entries to see if any need
 * to be sent, or are expected and have not
 * been reported
 */
void emberAfReportTableTick(void);

/**
 * Add an entry for an attribute for which we expect to receive reports.  The
 * node id and source endpoint refer to the remote node from which will we will
 * receive the report on the local destination endpoint.
 */
EmberAfStatus emberAfAddRxReportEntry(EmberNodeId nodeId,
                                      int8u sourceEndpoint,
                                      int8u destinationEndpoint,
                                      EmberAfClusterId clusterId,
                                      EmberAfAttributeId attributeId,
                                      int8u mask,
                                      int16u manufacturerCode,
                                      int16u timeout);

/**
 * Add an entry for an attribute for which we will send reports.  The node id
 * and destination endpoint refer to the remote node to which we will send the
 * report from the local source endpoint.
 */
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
                                      int32u reportableChange);

/**
 * Find an entry in the table.  The node id always refers to the remote node
 * while the meaning of the source and destination endpoints depends on the
 * direction of the report.
 */
EmberAfReportEntry *emberAfFindReportEntry(EmberAfReportingDirection direction,
                                           EmberNodeId nodeId,
                                           int8u sourceEndpoint,
                                           int8u destinationEndpoint,
                                           EmberAfClusterId clusterId,
                                           EmberAfAttributeId attributeId,
                                           int8u mask,
                                           int16u manufacturerCode);

/**
 * Find an empty slot in the table.
 */
EmberAfReportEntry *emberAfFindAvailableReportEntry(void);

/**
 * Clear the report table.
 */
void emberAfReportTableClear(void);

/**
 * Update the status of a report entry based on report ACK.
 */
void emberAfUpdateReportEntryStatus(EmberNodeId nodeId,
                                    int8u sourceEndpoint,
                                    int8u destinationEndpoint,
                                    EmberAfClusterId clusterId,
                                    int8u mask,
                                    int16u manufacturerCode,
                                    EmberStatus messageSentStatus);
