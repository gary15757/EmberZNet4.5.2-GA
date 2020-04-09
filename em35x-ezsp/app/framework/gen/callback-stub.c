// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generateCallbackStubs()
//

// This c file provides stubs for all callbacks. These stubs
// will be used in the case where user defined implementations
// of the callbacks have not been provided.
#include PLATFORM_HEADER
#ifdef EZSP_HOST
// Includes needed for ember related functions for the EZSP host
#include "stack/include/error.h"
#include "stack/include/ember-types.h"
#include "app/util/ezsp/ezsp-protocol.h"
#include "app/util/ezsp/ezsp.h"
#include "app/util/ezsp/ezsp-utils.h"
#include "app/util/ezsp/serial-interface.h"
#else
// Includes needed for ember related functions for the EM250
#include "stack/include/ember.h"
#endif // EZSP_HOST

#include "app/framework/include/af.h"
#include "app/framework/util/attribute-table.h"
#include "app/framework/util/attribute-storage.h"

/** @brief Read Attributes Response
 *
 * This function is called by the application framework when a Read Attributes
 * Response command is received from an external device.  The application
 * should return TRUE if the message was processed or FALSE if it was not.
 *
 * @param clusterId The cluster identifier of this response.  Ver.: always
 * @param buffer Buffer containing the list of read attribute status records. 
 * Ver.: always
 * @param bufLen The length in bytes of the list.  Ver.: always
 */
#ifndef EMBER_CALLBACK_READ_ATTRIBUTES_RESPONSE
boolean emberAfReadAttributesResponseCallback(EmberAfClusterId clusterId, 
                                              int8u * buffer, 
                                              int16u bufLen) {
  return FALSE;
}
#endif // EMBER_CALLBACK_READ_ATTRIBUTES_RESPONSE

/** @brief Write Attributes Response
 *
 * This function is called by the application framework when a Write
 * Attributes Response command is received from an external device.  The
 * application should return TRUE if the message was processed or FALSE if it
 * was not.
 *
 * @param clusterId The cluster identifier of this response.  Ver.: always
 * @param buffer Buffer containing the list of write attribute status records.
 * Ver.: always
 * @param bufLen The length in bytes of the list.  Ver.: always
 */
#ifndef EMBER_CALLBACK_WRITE_ATTRIBUTES_RESPONSE
boolean emberAfWriteAttributesResponseCallback(EmberAfClusterId clusterId, 
                                               int8u * buffer, 
                                               int16u bufLen) {
  return FALSE;
}
#endif // EMBER_CALLBACK_WRITE_ATTRIBUTES_RESPONSE

/** @brief Configure Reporting Response
 *
 * This function is called by the application framework when a Configure
 * Reporting Response command is received from an external device.  The
 * application should return TRUE if the message was processed or FALSE if it
 * was not.
 *
 * @param clusterId The cluster identifier of this response.  Ver.: always
 * @param buffer Buffer containing the list of attribute status records. 
 * Ver.: always
 * @param bufLen The length in bytes of the list.  Ver.: always
 */
#ifndef EMBER_CALLBACK_CONFIGURE_REPORTING_RESPONSE
boolean emberAfConfigureReportingResponseCallback(EmberAfClusterId clusterId, 
                                                  int8u * buffer, 
                                                  int16u bufLen) {
  return FALSE;
}
#endif // EMBER_CALLBACK_CONFIGURE_REPORTING_RESPONSE

/** @brief Read Reporting Configuration Response
 *
 * This function is called by the application framework when a Read Reporting
 * Configuration Response command is received from an external device.  The
 * application should return TRUE if the message was processed or FALSE if it
 * was not.
 *
 * @param clusterId The cluster identifier of this response.  Ver.: always
 * @param buffer Buffer containing the list of attribute reporting
 * configuration records.  Ver.: always
 * @param bufLen The length in bytes of the list.  Ver.: always
 */
#ifndef EMBER_CALLBACK_READ_REPORTING_CONFIGURATION_RESPONSE
boolean emberAfReadReportingConfigurationResponseCallback(EmberAfClusterId clusterId, 
                                                          int8u * buffer, 
                                                          int16u bufLen) {
  return FALSE;
}
#endif // EMBER_CALLBACK_READ_REPORTING_CONFIGURATION_RESPONSE

/** @brief Report Attributes
 *
 * This function is called by the application framework when a Report
 * Attributes command is received from an external device.  The application
 * should return TRUE if the message was processed or FALSE if it was not.
 *
 * @param clusterId The cluster identifier of this command.  Ver.: always
 * @param buffer Buffer containing the list of attribute report records. 
 * Ver.: always
 * @param bufLen The length in bytes of the list.  Ver.: always
 */
#ifndef EMBER_CALLBACK_REPORT_ATTRIBUTES_RESPONSE
boolean emberAfReportAttributesCallback(EmberAfClusterId clusterId, 
                                        int8u * buffer, 
                                        int16u bufLen) {
  return FALSE;
}
#endif // EMBER_CALLBACK_REPORT_ATTRIBUTES_RESPONSE

/** @brief Default Response
 *
 * This function is called by the application framework when a Default
 * Response command is received from an external device.  The application
 * should return TRUE if the message was processed or FALSE if it was not.
 *
 * @param clusterId The cluster identifier of this response.  Ver.: always
 * @param commandId The command identifier to which this is a response.  Ver.:
 * always
 * @param status Specifies either SUCCESS or the nature of the error that was
 * detected in the received command.  Ver.: always
 */
#ifndef EMBER_CALLBACK_DEFAULT_RESPONSE
boolean emberAfDefaultResponseCallback(EmberAfClusterId clusterId, 
                                       int8u commandId, 
                                       EmberAfStatus status) {
  return FALSE;
}
#endif // EMBER_CALLBACK_DEFAULT_RESPONSE

/** @brief Discover Attributes Response
 *
 * This function is called by the application framework when a Discover
 * Attributes Response command is received from an external device.  The
 * Discover Attributes Response command contains a boolean indicating if
 * discovery is complete and a list of zero or more attribute identifier/type
 * records.  The application should return TRUE if the message was processed
 * or FALSE if it was not.
 *
 * @param clusterId The cluster identifier of this response.  Ver.: always
 * @param discoveryComplete Indicates whether there are more attributes to be
 * discovered.  TRUE if there are no more attributes to be discovered.  Ver.:
 * always
 * @param buffer Buffer containing the list of attribute identifier/type
 * records.  Ver.: always
 * @param bufLen The length in bytes of the list.  Ver.: always
 */
#ifndef EMBER_CALLBACK_DISCOVER_ATTRIBUTES_RESPONSE
boolean emberAfDiscoverAttributesResponseCallback(EmberAfClusterId clusterId, 
                                                  boolean discoveryComplete, 
                                                  int8u * buffer, 
                                                  int16u bufLen) {
  return FALSE;
}
#endif // EMBER_CALLBACK_DISCOVER_ATTRIBUTES_RESPONSE

/** @brief Allow Network Write Attribute
 *
 * This function is called by the application framework before it writes an
 * attribute in response to a write attribute request from an external device.
 * The value passed into this callback is the value to which the attribute is
 * to be set by the framework. The application framework expects one of three
 * possible values 0=Do not allow write, 1=Allow write normal (attribute must
 * be writeable), 2=Allow write for a read only attribute.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 * @param attributeId   Ver.: always
 * @param mask   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param value   Ver.: always
 * @param type   Ver.: always
 */
#ifndef EMBER_CALLBACK_NET_WRITE
EmberAfAttributeWritePermission emberAfAllowNetworkWriteAttributeCallback(int8u endpoint, 
                                                                          EmberAfClusterId clusterId, 
                                                                          EmberAfAttributeId attributeId, 
                                                                          int8u mask, 
                                                                          int16u manufacturerCode, 
                                                                          int8u* value, 
                                                                          int8u type) {
  return EMBER_ZCL_ATTRIBUTE_WRITE_PERMISSION_ALLOW_WRITE_NORMAL; // Default
}
#endif // EMBER_CALLBACK_NET_WRITE

/** @brief Pre Attribute Change
 *
 * This function is called by the application framework before it changes an
 * attribute value. The value passed into this callback is the value to which
 * the attribute is to be set by the framework.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 * @param attributeId   Ver.: always
 * @param mask   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param type   Ver.: always
 * @param size   Ver.: always
 * @param value   Ver.: always
 */
#ifndef EMBER_CALLBACK_PRE_ATTR_CH
void emberAfPreAttributeChangeCallback(int8u endpoint, 
                                       EmberAfClusterId clusterId, 
                                       EmberAfAttributeId attributeId, 
                                       int8u mask, 
                                       int16u manufacturerCode, 
                                       int8u type, 
                                       int8u size, 
                                       int8u* value) {
  
}
#endif // EMBER_CALLBACK_PRE_ATTR_CH

/** @brief Post Attribute Change
 *
 * This function is called by the application framework after it changes an
 * attribute value. The value passed into this callback is the value to which
 * the attribute was set by the framework.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 * @param attributeId   Ver.: always
 * @param mask   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param type   Ver.: always
 * @param size   Ver.: always
 * @param value   Ver.: always
 */
#ifndef EMBER_CALLBACK_POST_ATTR_CH
void emberAfPostAttributeChangeCallback(int8u endpoint, 
                                        EmberAfClusterId clusterId, 
                                        EmberAfAttributeId attributeId, 
                                        int8u mask, 
                                        int16u manufacturerCode, 
                                        int8u type, 
                                        int8u size, 
                                        int8u* value) {
  
}
#endif // EMBER_CALLBACK_POST_ATTR_CH

/** @brief Pre Message Received
 *
 * This function is called by the application framework when a raw message is
 * received but has not yet been parsed by the application framework. This
 * function should return a boolean value indicating whether the message has
 * been handled by the user application code and should be ignored by the
 * AppFramework. By default, this callback returns FALSE indicating that the
 * message has not been handled and should be handled by the AppFramework.
 * This function receives a pointer to a struct containing the super set of
 * arguments sent to the emberIncomingMessageHandler and the
 * ezspIncomingMessageHandler.
 *
 * @param incomingMessage   Ver.: always
 */
#ifndef EMBER_CALLBACK_PRE_MSG
boolean emberAfPreMessageReceivedCallback(EmberAfIncomingMessage* incomingMessage) {
  return FALSE;
}
#endif // EMBER_CALLBACK_PRE_MSG

/** @brief Pre Command Received
 *
 * This function is called by the application framework when a command is
 * received but has yet to be handled by the framework code. This function
 * should return a boolean value indicating whether the command has been
 * handled by the user application code and should be ignored by the
 * AppFramework. By default, this callback returns FALSE indicating that the
 * message has not been handled and should be handled by the
 *
 * @param cmd   Ver.: always
 */
#ifndef EMBER_CALLBACK_PRE_CMD
boolean emberAfPreCommandReceivedCallback(EmberAfClusterCommand* cmd) {
  return FALSE;
}
#endif // EMBER_CALLBACK_PRE_CMD

/** @brief Pre ZDO Message Received
 *
 * This function passes the application an incoming ZDO message and gives the
 * appictation the opportunity to handle it. By default, this callback returns
 * FALSE indicating that the incoming ZDO message has not been handled and
 * should be handled by the Application Framework.
 *
 * @param emberNodeId   Ver.: always
 * @param apsFrame   Ver.: always
 * @param message   Ver.: always
 * @param length   Ver.: always
 */
#ifndef EMBER_CALLBACK_PRE_ZDO
boolean emberAfPreZDOMessageReceivedCallback(EmberNodeId emberNodeId, 
                                             EmberApsFrame* apsFrame, 
                                             int8u* message, 
                                             int16u length) {
  return FALSE;
}
#endif // EMBER_CALLBACK_PRE_ZDO

/** @brief Message Sent
 *
 * This function is called by the application framework from the message sent
 * handler, when it is informed by the stack regarding the message sent
 * status. All of the values passed to the emberMessageSentHandler are passed
 * on to this callback. This provides an opportunity for the application to
 * verify that its message has been sent successfully and take the appropriate
 * action. This callback should return a boolean value of TRUE or FALSE. A
 * value of TRUE indicates that the message sent notification has been handled
 * and should not be handled by the application framework.
 *
 * @param type   Ver.: always
 * @param indexOrDestination   Ver.: always
 * @param apsFrame   Ver.: always
 * @param msgLen   Ver.: always
 * @param message   Ver.: always
 * @param status   Ver.: always
 */
#ifndef EMBER_CALLBACK_MSG_SENT
boolean emberAfMessageSentCallback(EmberOutgoingMessageType type, 
                                   int16u indexOrDestination, 
                                   EmberApsFrame* apsFrame, 
                                   int16u msgLen, 
                                   int8u* message, 
                                   EmberStatus status) {
  return FALSE;
}
#endif // EMBER_CALLBACK_MSG_SENT

/** @brief Stack Status
 *
 * This function is called by the application framework from the stack status
 * handler.  This callbacks provides applications an opportunity to be
 * notified of changes to the stack status and take appropriate action.  The
 * application should return TRUE if the status has been handled and should
 * not be handled by the application framework.
 *
 * @param status   Ver.: always
 */
#ifndef EMBER_CALLBACK_STACK_STATUS
boolean emberAfStackStatusCallback(EmberStatus status) {
  return FALSE;
}
#endif // EMBER_CALLBACK_STACK_STATUS

/** @brief Ncp Init
 *
 * This callback is used for initializing the network coprocessor either at
 * startup, or upon reset. It should be used to perform any kind of EZSP
 * initialization, as it will be called every time when NCP is reset. In an
 * SOC environment, this callbacks is not used.
 *
 */
#ifndef EMBER_CALLBACK_NCP_INIT
void emberAfNcpInitCallback(void) {
  
}
#endif // EMBER_CALLBACK_NCP_INIT

/** @brief Main Init
 *
 * This is the main application initialization callback. It is called prior to
 * application initialization and gives the application a chance to take care
 * of any of its own initialization procedures.
 *
 */
#ifndef EMBER_CALLBACK_MAIN_INIT
void emberAfMainInitCallback(void) {
  
}
#endif // EMBER_CALLBACK_MAIN_INIT

/** @brief Cluster Init
 *
 * This function is called when a specific cluster is initialized. It gives
 * the application an opportunity to take care of cluster initialization
 * procedures. It is called exactly once for each endpoint where cluster is
 * present.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 */
#ifndef EMBER_CALLBACK_CLUSTER_INIT
void emberAfClusterInitCallback(int8u endpoint, 
                                EmberAfClusterId clusterId) {
  
}
#endif // EMBER_CALLBACK_CLUSTER_INIT

/** @brief Pre Go To Sleep
 *
 * Called directly before a device goes to sleep. This function is passed the
 * number of milliseconds the device is attempting to go to sleep for. This
 * function returns a boolean indicating if sleep should be canceled. A
 * returned value of TRUE indicates that sleep should be canceled. A return
 * value of FALSE (default) indicates that sleep my continue as expected.
 *
 * @param sleepDurationAttempt   Ver.: always
 */
#ifndef EMBER_CALLBACK_PRE_SLEEP
boolean emberAfPreGoToSleepCallback(int32u sleepDurationAttempt) {
  return FALSE;
}
#endif // EMBER_CALLBACK_PRE_SLEEP

/** @brief Post Wake Up
 *
 * Called directly after a device wakes up from sleep. This function is passed
 * the number of milliseconds the device actually slept for.
 *
 * @param sleepDuration   Ver.: always
 */
#ifndef EMBER_CALLBACK_POST_SLEEP
void emberAfPostWakeUpCallback(int32u sleepDuration) {
  
}
#endif // EMBER_CALLBACK_POST_SLEEP

/** @brief Main Tick
 *
 * Whenever main application tick is called, this callback will be called at
 * the end of the main tick execution.
 *
 */
#ifndef EMBER_CALLBACK_MAIN_TICK
void emberAfMainTickCallback(void) {
  
}
#endif // EMBER_CALLBACK_MAIN_TICK

/** @brief External Attribute Write
 *
 * This callback is called for whenever an attribute is written, if this
 * attribute was tagged to be stored externally. Function should return true
 * if write was successful and false if not. Upon successful exit, the data
 * from the passed buffer should be stored as the current value of the
 * attribute. Important to note is, that if this method ever returns false,
 * then it is possible to break contract of the write-undivided-attributes
 * global command. That command checks for ranges and attribute existence, but
 * if this method returns false, when the attribute is finally written, then
 * the contract of writing all or no attributes will be broken.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 * @param attributeMetadata   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param buffer   Ver.: always
 */
#ifndef EMBER_CALLBACK_EXT_ATT_WRITE
boolean emberAfExternalAttributeWriteCallback(int8u endpoint, 
                                              EmberAfClusterId clusterId, 
                                              EmberAfAttributeMetadata * attributeMetadata, 
                                              int16u manufacturerCode, 
                                              int8u * buffer) {
  return FALSE;
}
#endif // EMBER_CALLBACK_EXT_ATT_WRITE

/** @brief External Attribute Read
 *
 * If an attribute is tagged to be stored externally, this function will be
 * called whenever that attribute is read. This function should return TRUE if
 * read was successful and FALSE if not. The passed buffer should be populated
 * with the associated attributes value.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 * @param attributeMetadata   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param buffer   Ver.: always
 */
#ifndef EMBER_CALLBACK_EXT_ATT_READ
boolean emberAfExternalAttributeReadCallback(int8u endpoint, 
                                             EmberAfClusterId clusterId, 
                                             EmberAfAttributeMetadata * attributeMetadata, 
                                             int16u manufacturerCode, 
                                             int8u * buffer) {
  return FALSE;
}
#endif // EMBER_CALLBACK_EXT_ATT_READ

/** @brief Report Entry Configured
 *
 * This callback is called whenever a reporting entry is configured, including
 * when entries are deleted or updated.  The application can use this callback
 * for scheduling readings or measurements based on the minimum and maximum
 * reporting interval for the entry.  The application should return
 * EMBER_ZCL_STATUS_SUCCESS if it can support the configuration or an error
 * status otherwise.  Note: attribute reporting is required for many clusters
 * and attributes, so rejecting a reporting configuration may violate ZigBee
 * specifications.
 *
 * @param entry   Ver.: always
 */
#ifndef EMBER_CALLBACK_REPORT_ENTRY_CONFIGURED
EmberAfStatus emberAfReportEntryConfiguredCallback(EmberAfReportEntry * entry) {
  return EMBER_ZCL_STATUS_SUCCESS;
}
#endif // EMBER_CALLBACK_REPORT_ENTRY_CONFIGURED

/** @brief Trust Center Join
 *
 * This callback is called from within the application framework's
 * implementation of emberTrustCenterJoinHandler or
 * ezspTrustCenterJoinHandler. This callback provides the same arguments
 * passed to the TrustCenterJoinHandler. For more information about the
 * TrustCenterJoinHandler please see documentation included in
 * stack/include/trust-center.h.
 *
 * @param newNodeId   Ver.: always
 * @param newNodeEui64   Ver.: always
 * @param parentOfNewNode   Ver.: always
 * @param status   Ver.: always
 * @param decision   Ver.: always
 */
#ifndef EMBER_CALLBACK_TRUST_CENTER_JOIN
void emberAfTrustCenterJoinCallback(EmberNodeId newNodeId, 
                                    EmberEUI64 newNodeEui64, 
                                    EmberNodeId parentOfNewNode, 
                                    EmberDeviceUpdate status, 
                                    EmberJoinDecision decision) {
  
}
#endif // EMBER_CALLBACK_TRUST_CENTER_JOIN

/** @brief Get Current Time
 *
 * This callback is called when device attempts to get current time from the
 * hardware. If this device has means to retrieve exact time, then this method
 * should implement it. If the callback can't provide the exact time it should
 * return 0 to indicate failure. Default action is to return 0, which
 * indicates that device does not have access to real time.
 *
 */
#ifndef EMBER_CALLBACK_GET_CURRENT_TIME
int32u emberAfGetCurrentTimeCallback(void) {
  return 0;
}
#endif // EMBER_CALLBACK_GET_CURRENT_TIME

/** @brief Set Time
 *
 * This callback should be implemented, if the device has access to real time
 * clock, and has an ability to update that clock. The application framework
 * expects to be passed the utcTime which is the number of seconds since the
 * year 2000. Default implementation does nothing. Note: This function used to
 * take time in year, month, day, hour, min, sec. We have changed this to
 * utcTime in order to conserve code space.
 *
 * @param utcTime   Ver.: always
 */
#ifndef EMBER_CALLBACK_SET_TIME
void emberAfSetTimeCallback(int32u utcTime) {
  
}
#endif // EMBER_CALLBACK_SET_TIME

/** @brief Convert Volts To Celsius
 *
 * Function that converts volts on the ADC line into celsius.
 *
 * @param voltage Voltage from ADC  Ver.: always
 */
#ifndef EMBER_CALLBACK_TEMP_MEASUREMENT_CLUSTER_TEMP_VOLTS_TO_CELSIUS
int32s emberAfTempMeasurementClusterConvertVoltsToCelsiusCallback(int16u voltage) {
  // LM20 temp sensor implementation
        return 1591887L - (171 * (int32s)voltage);
}
#endif // EMBER_CALLBACK_TEMP_MEASUREMENT_CLUSTER_TEMP_VOLTS_TO_CELSIUS

/** @brief Initiate Key Establishment
 *
 * This function is called by the framework to initiate key establishment with
 * a remote device.  The application should return EMBER_SUCCESS if key
 * establishment was initiated successfully.  The application should call
 * ::emberAfKeyEstablishmentCallback as events occur.
 *
 * @param nodeId The node id of the remote device.  Ver.: always
 * @param endpoint The endpoint on the remote device.  Ver.: always
 */
#ifndef EMBER_CALLBACK_INITIATE_KEY_ESTABLISHMENT
EmberStatus emberAfInitiateKeyEstablishmentCallback(EmberNodeId nodeId, 
                                                    int8u endpoint) {
  return EMBER_LIBRARY_NOT_PRESENT;
}
#endif // EMBER_CALLBACK_INITIATE_KEY_ESTABLISHMENT

/** @brief Initiate Inter Pan Key Establishment
 *
 * This function is called by the framework to initiate key establishment with
 * a remote device on a different PAN.  The application should return
 * EMBER_SUCCESS if key establishment was initiated successfully.  The
 * application should call ::emberAfInterPanKeyEstablishmentCallback as events
 * occur.
 *
 * @param panId The PAN id of the remote device.  Ver.: always
 * @param eui64 The EUI64 of the remote device.  Ver.: always
 */
#ifndef EMBER_CALLBACK_INITIATE_INTER_PAN_KEY_ESTABLISHMENT
EmberStatus emberAfInitiateInterPanKeyEstablishmentCallback(EmberPanId panId, 
                                                            const EmberEUI64 eui64) {
  return EMBER_LIBRARY_NOT_PRESENT;
}
#endif // EMBER_CALLBACK_INITIATE_INTER_PAN_KEY_ESTABLISHMENT

/** @brief Key Establishment
 *
 * A callback by the key-establishment code to indicate an event has occurred.
 * For error codes this is purely a notification.  For non-error status codes
 * (besides LINK_KEY_ESTABLISHED), it is the application's chance to allow or
 * disallow the operation.  If the application returns TRUE then the key
 * establishment is allowed to proceed.  If it returns FALSE, then key
 * establishment is aborted.  LINK_KEY_ESTABLISHED is a notification of
 * success.
 *
 * @param status   Ver.: always
 * @param amInitiator   Ver.: always
 * @param partnerShortId   Ver.: always
 * @param delayInSeconds   Ver.: always
 */
#ifndef EMBER_CALLBACK_KEY_ESTABLISHMENT
boolean emberAfKeyEstablishmentCallback(EmberAfKeyEstablishmentNotifyMessage status, 
                                        boolean amInitiator, 
                                        EmberNodeId partnerShortId, 
                                        int8u delayInSeconds) {
  return TRUE;
}
#endif // EMBER_CALLBACK_KEY_ESTABLISHMENT

/** @brief Inter Pan Key Establishment
 *
 * A callback by the key-establishment code to indicate an event has occurred.
 * For error codes this is purely a notification.  For non-error status codes
 * (besides LINK_KEY_ESTABLISHED), it is the application's chance to allow or
 * disallow the operation.  If the application returns TRUE then the key
 * establishment is allowed to proceed.  If it returns FALSE, then key
 * establishment is aborted.  LINK_KEY_ESTABLISHED is a notification of
 * success.
 *
 * @param status   Ver.: always
 * @param amInitiator   Ver.: always
 * @param panId   Ver.: always
 * @param eui64   Ver.: always
 * @param delayInSeconds   Ver.: always
 */
#ifndef EMBER_CALLBACK_INTER_PAN_KEY_ESTABLISHMENT
boolean emberAfInterPanKeyEstablishmentCallback(EmberAfKeyEstablishmentNotifyMessage status, 
                                                boolean amInitiator, 
                                                EmberPanId panId, 
                                                const EmberEUI64 eui64, 
                                                int8u delayInSeconds) {
  return TRUE;
}
#endif // EMBER_CALLBACK_INTER_PAN_KEY_ESTABLISHMENT

/** @brief Performing Key Establishment
 *
 * This function is called by the framework to determine if the device is
 * performing key establishment.  The application should return TRUE if key
 * establishment is in progress.
 *
 */
#ifndef EMBER_CALLBACK_PERFORMING_KEY_ESTABLISHMENT
boolean emberAfPerformingKeyEstablishmentCallback(void) {
  return FALSE;
}
#endif // EMBER_CALLBACK_PERFORMING_KEY_ESTABLISHMENT

/** @brief Initiate Partner Link Key Exchange
 *
 * This function is called by the framework to initiate a partner link key
 * exchange with a remote device.  The application should return EMBER_SUCCESS
 * if the partner link key exchange was initiated successfully.  When the
 * partner link key exchange completes, the application should call the given
 * callback.
 *
 * @param target The node id of the remote device.  Ver.: always
 * @param endpoint The key establishment endpoint of the remote device.  Ver.:
 * always
 * @param callback The callback that should be called when the partner link
 * key exchange completse.  Ver.: always
 */
#ifndef EMBER_CALLBACK_INITIATE_PARTNER_LINK_KEY_EXCHANGE
EmberStatus emberAfInitiatePartnerLinkKeyExchangeCallback(EmberNodeId target, 
                                                          int8u endpoint, 
                                                          EmberAfPartnerLinkKeyExchangeCallback * callback) {
  return EMBER_LIBRARY_NOT_PRESENT;
}
#endif // EMBER_CALLBACK_INITIATE_PARTNER_LINK_KEY_EXCHANGE

/** @brief Partner Link Key Exchange Request
 *
 * This function is called by the framework on SOC platforms when a remote
 * node requests a partner link key exchange.  The application should return
 * EMBER_SUCCESS to accept the request or any other status to reject it.  On
 * network coprocessor platforms, this function will not be called because the
 * NCP handles partner link key exchange requests based on the binding policy.
 *
 * @param partner The EUI of the remote node.  Ver.: always
 */
#ifndef EMBER_CALLBACK_PARTNER_LINK_KEY_EXCHANGE_REQUEST
EmberStatus emberAfPartnerLinkKeyExchangeRequestCallback(EmberEUI64 partner) {
  return EMBER_LIBRARY_NOT_PRESENT;
}
#endif // EMBER_CALLBACK_PARTNER_LINK_KEY_EXCHANGE_REQUEST

/** @brief Partner Link Key Exchange Response
 *
 * This function is called by the framework when a remote node requests a
 * partner link key exchange.  The application should return TRUE to accept
 * the request or FALSE to reject it.  On network coprocessor platforms, this
 * function will not be called because the NCP handles partner link key
 * exchange requests based on the binding policy.
 *
 * @param sender The EUI of the remote node.  Ver.: always
 * @param status The ZDO response status.  Ver.: always
 */
#ifndef EMBER_CALLBACK_PARTNER_LINK_KEY_EXCHANGE_RESPONSE
void emberAfPartnerLinkKeyExchangeResponseCallback(EmberNodeId sender, 
                                                   EmberZdoStatus status) {
  
}
#endif // EMBER_CALLBACK_PARTNER_LINK_KEY_EXCHANGE_RESPONSE

/** @brief Registration Start
 *
 * This callback is called when the device joins a network and the
 * registration process should begin.  The application should return
 * EMBER_SUCCESS if the registration process started successfully.  When
 * registration is complete, the application should call
 * emberAfRegistrationCallback with an indication of success or failure.
 *
 */
#ifndef EMBER_CALLBACK_REGISTRATION_START
EmberStatus emberAfRegistrationStartCallback(void) {
  return EMBER_LIBRARY_NOT_PRESENT;
}
#endif // EMBER_CALLBACK_REGISTRATION_START

/** @brief Registration Abort
 *
 * This callback is called when the device should abort the registration
 * process.
 *
 */
#ifndef EMBER_CALLBACK_REGISTRATION_ABORT
void emberAfRegistrationAbortCallback(void) {
  
}
#endif // EMBER_CALLBACK_REGISTRATION_ABORT

/** @brief Registration
 *
 * This callback is called when the device joins a network and the process of
 * registration is complete. This callback provides a success value of TRUE if
 * the registration process was successful and a value of FALSE if
 * registration failed.
 *
 * @param success TRUE if registration succeeded, FALSE otherwise.  Ver.:
 * always
 */
#ifndef EMBER_CALLBACK_REGISTRATION
void emberAfRegistrationCallback(boolean success) {
  
}
#endif // EMBER_CALLBACK_REGISTRATION

/** @brief Trust Center Keepalive Update
 *
 * This callback is called when the device finishes registration (successfully
 * or otherwise) and the trust center keepalive process must be updated.  If
 * the keepalive process has not been started, then it is started.  Otherwise
 * if the keepalive is in the process of searching for the TC, it will process
 * the result of that Trust Center search operation.
 *
 * @param registrationComplete   Ver.: always
 */
#ifndef EMBER_CALLBACK_TRUST_CENTER_KEEPALIVE_UPDATE
void emberAfTrustCenterKeepaliveUpdateCallback(boolean registrationComplete) {
  
}
#endif // EMBER_CALLBACK_TRUST_CENTER_KEEPALIVE_UPDATE

/** @brief Trust Center Keepalive Abort
 *
 * This callback is called when the device should abort the trust center
 * keepalive process.
 *
 */
#ifndef EMBER_CALLBACK_TRUST_CENTER_KEEPALIVE_ABORT
void emberAfTrustCenterKeepaliveAbortCallback(void) {
  
}
#endif // EMBER_CALLBACK_TRUST_CENTER_KEEPALIVE_ABORT

/** @brief Custom Command Line
 *
 * If you enable this callback, then it will be called when 'custom' CLI
 * command is executed. It is responsible for reading it's own arguments.
 *
 */
#ifndef EMBER_CALLBACK_CUSTOM_CLI_COMMAND
void emberAfCustomCommandLineCallback(void) {
  
}
#endif // EMBER_CALLBACK_CUSTOM_CLI_COMMAND

/** @brief Ota Server Incoming Message Raw
 *
 * This callback is for processing incoming messages for the Over-the-air
 * bootload cluster server.  ZCL will not process the message and instead hand
 * the raw over the air data to the callback for its own processing.
 *
 * @param message A pointer to the structure containing the message buffer and
 * other information about it.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_SERVER_INCOMING_MESSAGE_RAW
boolean emberAfOtaServerIncomingMessageRawCallback(EmberAfClusterCommand * message) {
  return FALSE;
}
#endif // EMBER_CALLBACK_OTA_SERVER_INCOMING_MESSAGE_RAW

/** @brief Ota Server Send Image Notify
 *
 * This callback is an indication to the OTA server that it should send out
 * notification about an OTA file that is available for download.
 *
 * @param dest The destination of the image notify message.  May be a
 * broadcast address.  Ver.: always
 * @param endpoint The destination endpoint of the image notify message.  May
 * be a broadcast endpoint.  Ver.: always
 * @param payloadType The type of data the image notify message will contain. 
 * 0 = no data.  1 = Manufacturer ID.  2 = Manufacturer ID and the image type
 * ID.  3 = Manufacturer ID, image type ID, and firmware version.  Ver.:
 * always
 * @param queryJitter The percentage of nodes that should respond to this
 * message, from 1-100.  On receipt of this message, each recipient will
 * randomly choose a percentage and only query the server if their percentage
 * is below this value.  Ver.: always
 * @param id The image information that will be put in the message.  The data
 * within this struct that will be appended to the message is determined by
 * the previous 'payloadType' argument.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_SERVER_SEND_IMAGE_NOTIFY
boolean emberAfOtaServerSendImageNotifyCallback(EmberNodeId dest, 
                                                int8u endpoint, 
                                                int8u payloadType, 
                                                int8u queryJitter, 
                                                const EmberAfOtaImageId* id) {
  return FALSE;
}
#endif // EMBER_CALLBACK_OTA_SERVER_SEND_IMAGE_NOTIFY

/** @brief Ota Storage Driver Init
 *
 * The initialization code for the OTA storage driver.
 *
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_DRIVER_INIT
boolean emberAfOtaStorageDriverInitCallback(void) {
  // The storage driver and the rest of the OTA bootload code will not function correctly unless it is implemnted.
  // Please implement me.
  assert(FALSE);
  return FALSE;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_DRIVER_INIT

/** @brief Ota Storage Driver Read
 *
 * This callback defines the low-level means by which a device reads from the
 * OTA storage device.
 *
 * @param offset The address offset from the start of the storage device where
 * data is to be read.  Ver.: always
 * @param length   Ver.: always
 * @param returnData A pointer where the data read from the device should be
 * written to.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_DRIVER_READ
boolean emberAfOtaStorageDriverReadCallback(int32u offset, 
                                            int32u length, 
                                            int8u* returnData) {
  // The storage driver and the rest of the OTA bootload code will not function correctly unless it is implemnted.
  // Please implement me.
  assert(FALSE);
  return FALSE;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_DRIVER_READ

/** @brief Ota Storage Driver Write
 *
 * This callback defines the low-level means by which a device reads from the
 * OTA storage device.
 *
 * @param dataToWrite A pointer to the data that will be written to the
 * storage device.  Ver.: always
 * @param offset The address offset from the start of the storage device where
 * data will be written.  Ver.: always
 * @param length The length of the data to be written to the storage device. 
 * Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_DRIVER_WRITE
boolean emberAfOtaStorageDriverWriteCallback(const int8u* dataToWrite, 
                                             int32u offset, 
                                             int32u length) {
  // The storage driver and the rest of the OTA bootload code will not function correctly unless it is implemnted.
  // Please implement me.
  assert(FALSE);
  return FALSE;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_DRIVER_WRITE

/** @brief Ota Bootload
 *
 * The platform specific routine to bootload the device from a ZigBee
 * over-the-air upgrade file.
 *
 * @param id A pointer to the structure that contains the information about
 * what OTA image to bootload.  Ver.: always
 * @param ncpUpgradeTagId The tag ID of the upgrade data that will be used to
 * bootload the device.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_BOOTLOAD
int8u emberAfOtaBootloadCallback(const EmberAfOtaImageId* id, 
                                 int16u ncpUpgradeTagId) {
  // Please implement me
  emberAfCorePrintln("Not supported.");
  return 1;
}
#endif // EMBER_CALLBACK_OTA_BOOTLOAD

/** @brief Ota Storage Init
 *
 * This callback initializes the ZigBee Over-the-air storage module.
 *
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_INIT
EmberAfOtaStorageStatus emberAfOtaStorageInitCallback(void) {
  return EMBER_AF_OTA_STORAGE_SUCCESS;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_INIT

/** @brief Ota Storage Close
 *
 * This callback shuts down the ZigBee Over-the-air storage module.
 *
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_CLOSE
void emberAfOtaStorageCloseCallback(void) {
  // Please implement me.
  assert(FALSE);
}
#endif // EMBER_CALLBACK_OTA_STORAGE_CLOSE

/** @brief Ota Storage Get Count
 *
 * This callback returns the total number of ZigBee Over-the-air upgrade
 * images stored in the storage module.
 *
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_GET_COUNT
int8u emberAfOtaStorageGetCountCallback(void) {
  return 0;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_GET_COUNT

/** @brief Ota Storage Search
 *
 * This callback searches through the list of all images for one that matches
 * the passed parameters.  On success an image identifier is returned with a
 * matching image.  On failure emberAfInvalidImageId is returned.
 *
 * @param manufacturerId The ZigBee assigned identifier of the manufacturer
 * contained in the OTA image being searched for.  Ver.: always
 * @param imageTypeId The image type identifier contained in the OTA image
 * being searched for.  Ver.: always
 * @param hardwareVersion This is a pointer to the hardware version that will
 * be used in the search.  If the pointer is NULL, hardware version will not
 * be considered when searching for matching images.  If it points to a value,
 * the search will only consider images where that value falls between the
 * minimum and maxmimum hardware version specified in the OTA file.  If no
 * hardware version is present in an OTA file but the other parameters match,
 * the file will be considered a match  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_SEARCH
EmberAfOtaImageId emberAfOtaStorageSearchCallback(int16u manufacturerId, 
                                                  int16u imageTypeId, 
                                                  const int16u* hardwareVersion) {
  // If no image is found that matches the search criteria, this function should return the invalid image id.
  return emberAfInvalidImageId;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_SEARCH

/** @brief Ota Storage Get Total Image Size
 *
 * This function returns the total size of the ZigBee Over-the-air file with
 * the passed parameters.  If no file is found with those parameters, 0 is
 * returned.
 *
 * @param id A pointer to the image identifier for the OTA file to retrieve
 * information for.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_GET_TOTAL_IMAGE_SIZE
int32u emberAfOtaStorageGetTotalImageSizeCallback(const EmberAfOtaImageId* id) {
  // On failure this should return an image size of zero.
  return 0;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_GET_TOTAL_IMAGE_SIZE

/** @brief Ota Storage Iterator First
 *
 * This callback lets you walk through the list of all OTA files by jumping to
 * the first file in the list maintained by the storage module.  If there is
 * no file then emberAfOtaInvalidImageId is returned.
 *
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_ITERATOR_FIRST
EmberAfOtaImageId emberAfOtaStorageIteratorFirstCallback(void) {
  // It is expected that the storage module maintain its own internal iterator that the 'first' and 'next' functions will manipulate.

  // If there are no images at all, this function should return the invalid image id.
  return emberAfInvalidImageId;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_ITERATOR_FIRST

/** @brief Ota Storage Iterator Next
 *
 * This callback lets you walk through the list of all OTA files by jumping to
 * the next file in the list maintained by the storage module.  If there is no
 * next file then emberAfOtaInvalidImageId is returned.
 *
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_ITERATOR_NEXT
EmberAfOtaImageId emberAfOtaStorageIteratorNextCallback(void) {
  // It is expected that the storage module maintain its own internal iterator that the 'first' and 'next' functions will manipulate.

  // If there are no more images, this function should return the invalid image id.
  return emberAfInvalidImageId;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_ITERATOR_NEXT

/** @brief Ota Storage Get Full Header
 *
 * This callback populates the EmberAfOtaHeader structure pointed to by the
 * returnData with data about the OTA file stored in the storage module.
 *
 * @param id This is a pointer to the image id for the OTA file to retrieve
 * information about.  Ver.: always
 * @param returnData This is a pointer to the location of the structure that
 * will be populated with data.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_GET_FULL_HEADER
EmberAfOtaStorageStatus emberAfOtaStorageGetFullHeaderCallback(const EmberAfOtaImageId* id, 
                                                               EmberAfOtaHeader* returnData) {
  // If the requested image cannot be found, then an error shouldb e returned.
  return EMBER_AF_OTA_STORAGE_ERROR;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_GET_FULL_HEADER

/** @brief Ota Storage Read Image Data
 *
 * This callback reads data from the specified OTA file and returns that data
 * to the caller.
 *
 * @param id This is a pointer to the image id for the OTA file to retrieve
 * data from.  Ver.: always
 * @param offset This is the offset relative to the start of the image where
 * the data should be read from.  Ver.: always
 * @param length This is the length of data that will be read.  Ver.: always
 * @param returnData This is a pointer to where the data read out of the file
 * will be written to  Ver.: always
 * @param returnedLength This is a pointer to a variable where the actual
 * length of data read will be written to.  A short read may occur if the end
 * of file was reached.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_READ_IMAGE_DATA
EmberAfOtaStorageStatus emberAfOtaStorageReadImageDataCallback(const EmberAfOtaImageId* id, 
                                                               int32u offset, 
                                                               int32u length, 
                                                               int8u* returnData, 
                                                               int32u* returnedLength) {
  // If the requested image cannot be found, then an error should be returned.
  return EMBER_AF_OTA_STORAGE_ERROR;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_READ_IMAGE_DATA

/** @brief Ota Storage Clear Temp Data
 *
 * This function clears any existing temp data that was downloaed.  It is used
 * immediately prior to downloading a raw image over the air.
 *
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_CLEAR_TEMP_DATA
EmberAfOtaStorageStatus emberAfOtaStorageClearTempDataCallback(void) {
  // If the image data cannot be stored, an error should be returned.
  return EMBER_AF_OTA_STORAGE_ERROR;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_CLEAR_TEMP_DATA

/** @brief Ota Storage Write Temp Data
 *
 * This function writes to the temporary data in the storage device at the
 * specified offset.  It is used when downloading a raw image over the air.
 *
 * @param offset The location within the download image file where to write
 * the data.  Ver.: always
 * @param length The length of data to write.  Ver.: always
 * @param data A pointer to the temporary data that will be written to the
 * storage device.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_WRITE_TEMP_DATA
EmberAfOtaStorageStatus emberAfOtaStorageWriteTempDataCallback(int32u offset, 
                                                               int32u length, 
                                                               const int8u* data) {
  // If the image data cannot be stored, an error should be returned.
  return EMBER_AF_OTA_STORAGE_ERROR;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_WRITE_TEMP_DATA

/** @brief Ota Storage Check Temp Data
 *
 * This callback will validate temporary data in the storage device to
 * determine whether it is a complete file, a partially downloaded file, or
 * there is no file present.  When a complete or partial file is found it will
 * return EMBER_AF_OTA_STORAGE_SUCCESS or
 * EMBER_AF_OTA_STORAGE_PARTIAL_FILE_FOUND, respectively.  In that case, the
 * currentOffset, totalImageSize, and newFileInfo will be populated with data.
 * When EMBER_AF_OTA_STORAGE_ERROR is returned, no temporary data is present.
 *
 * @param currentOffset A pointer to a value that will be written with the
 * offset within the total file size that has been successfully stored in the
 * storage device.  This will indicate how much data has been currently
 * dowloaded.  Ver.: always
 * @param totalImageSize A pointer to a value that will be written with the
 * total image size of the OTA file when a download has completed.  This does
 * not indicate how much data has actually been downloaded currently.  Ver.:
 * always
 * @param newFileInfo This is the image id of the temporary file data stored
 * in the storage device.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_CHECK_TEMP_DATA
EmberAfOtaStorageStatus emberAfOtaStorageCheckTempDataCallback(int32u* currentOffset, 
                                                               int32u* totalImageSize, 
                                                               EmberAfOtaImageId* newFileInfo) {
  // If the image data cannot be successfully verified, an error should be returned.
  return EMBER_AF_OTA_STORAGE_ERROR;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_CHECK_TEMP_DATA

/** @brief Ota Storage Finish Download
 *
 * This function indicates to the storage module that the download has
 * finished.
 *
 * @param offset The final offset of the downloaded file (i.e. the total size)
 * Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_STORAGE_FINISH_DOWNLOAD
EmberAfOtaStorageStatus emberAfOtaStorageFinishDownloadCallback(int32u offset) {
  return EMBER_AF_OTA_STORAGE_SUCCESS;
}
#endif // EMBER_CALLBACK_OTA_STORAGE_FINISH_DOWNLOAD

/** @brief Ota Client Incoming Message Raw
 *
 * This callback is for processing incoming messages for the Over-the-air
 * bootload cluster client.  ZCL will not process the message and instead hand
 * the raw over the air data to the callback for its own processing.
 *
 * @param message A pointer to the structure containing the message buffer and
 * other information about it.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_CLIENT_INCOMING_MESSAGE_RAW
boolean emberAfOtaClientIncomingMessageRawCallback(EmberAfClusterCommand * message) {
  return FALSE;
}
#endif // EMBER_CALLBACK_OTA_CLIENT_INCOMING_MESSAGE_RAW

/** @brief Ota Client Start
 *
 * This callback should be called when the profile specific registration has
 * completed successfully.  It will start the client's state machine that will
 * find the OTA server, query it for the next image, download the image, wait
 * for the bootload message, and kick off the bootload.
 *
 */
#ifndef EMBER_CALLBACK_OTA_CLIENT_START
void emberAfOtaClientStartCallback(void) {
  
}
#endif // EMBER_CALLBACK_OTA_CLIENT_START

/** @brief Ota Client Version Info
 *
 * This function is called by the OTA client when a new query will occur to
 * the server asking what the next version of firmware is.  The client can
 * inform the cluster software as to what information to use in the query (and
 * subsequent download).
 *
 * @param currentImageInfo This is the information to use in the next query by
 * the client cluster code.  It contains the manufacturer ID, image type ID,
 * and the firmware version to be specified in the query message sent to the
 * server.  Ver.: always
 * @param hardwareVersion This is a pointer to the hardware version to use in
 * the query.  If no hardware version should be used, then
 * EMBER_AF_INVALID_HARDWARE_VERSION should be used.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_CLIENT_VERSION_INFO
void emberAfOtaClientVersionInfoCallback(EmberAfOtaImageId* currentImageInfo, 
                                         int16u* hardwareVersion) {
  // Customer will fill in the image info with their manufacturer ID,
  // image type ID, and current software version number.
  // The deviceSpecificFileEui64 can be ignored.

  // It may be necessary to dynamically determine this by talking to
  // another device, as is the case with a host talking to an NCP device.

  // However, this routine will be called repeatedly so it may be wise
  // to cache the data!

/* This is commented out since the #defines below are not defined.

  if (currentImageInfo != NULL) {
    MEMSET(currentImageInfo, 0, sizeof(EmberAfOtaImageId));
    currentImageInfo->manufacturerId  = EMBER_AF_MANUFACTURER_CODE;
    currentImageInfo->imageTypeId     = EMBER_AF_IMAGE_TYPE_ID;
    currentImageInfo->firmwareVersion = EMBER_AF_CUSTOM_FIRMWARE_VERSION;
  }

  if (hardwareVersion != NULL) {
    *hardwareVersion = EMBER_AF_INVALID_HARDWARE_VERSION;
  }

  assert(FALSE);
*/
}
#endif // EMBER_CALLBACK_OTA_CLIENT_VERSION_INFO

/** @brief Ota Client Custom Verify
 *
 * This callback is executed by the OTA client after the signature
 * verification has successfully completed.  It allows the device to do its
 * own custom verification of the image (such as verifying that the EBL is
 * intact).
 *
 * @param newVerification This indicates if a new verification should be
 * started.  Ver.: always
 * @param id This is ID of the image to be verified.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_CLIENT_CUSTOM_VERIFY_CALLBACK
EmberAfImageVerifyStatus emberAfOtaClientCustomVerifyCallback(boolean newVerification, 
                                                              const EmberAfOtaImageId* id) {
  // Manufacturing specific checks can be made to the image in this function to
  // determine if it is valid.  This function is called AFTER cryptographic 
  // checks have passed.  If the cryptographic checks failed, this function will
  // never be called.
  
  // The function shall return one of the following based on its own 
  // verification process.
  // 1) EMBER_AF_IMAGE_GOOD - the image has passed all checks
  // 2) EMBER_AF_IMAGE_BAD  - the image is not valid 
  // 3) EMBER_AF_IMAGE_VERIFY_IN_PROGRESS - the image is valid so far, but more
  //      checks are needed.  This callback shall be re-executed later to 
  //      continue verification.  This allows other code in the framework to run.
  return EMBER_AF_IMAGE_GOOD;
}
#endif // EMBER_CALLBACK_OTA_CLIENT_CUSTOM_VERIFY_CALLBACK

/** @brief Ota Client Download Complete
 *
 * This callback indicates that the OTA client has completed the download of a
 * file.  If the file has been completely downloaded and cryptographic checks
 * have been turned on, then those will be performed prior to this callback
 * and that outcome included in the 'success' result.  On failure, this
 * callback is merely informative, and the return type is ignored.  On
 * succesful download, this callback allows the client to perform any
 * additional verification of the downloaded image and return that result to
 * the OTA server.
 *
 * @param success This indicates the success or failure of the download and
 * cryptographic verification process (if applicable).  Ver.: always
 * @param id This is the image identifier information that corresponds to the
 * download result.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_CLIENT_DOWNLOAD_COMPLETE
boolean emberAfOtaClientDownloadCompleteCallback(boolean success, 
                                                 const EmberAfOtaImageId* id) {
  // At this point the image has been completely downloaded and cryptographic 
  // checks (if applicable) have been performed.

  if (!success) {
    emberAfOtaBootloadClusterPrintln("Download failed.");
    return TRUE;   // return value is ignored
  }
  
  // This is for any additional validation that needs to be performed
  // on the image by the application.
  
  // The results of checks here will be returned back to the OTA server
  // in the Upgrade End request.
  return TRUE;
}
#endif // EMBER_CALLBACK_OTA_CLIENT_DOWNLOAD_COMPLETE

/** @brief Ota Client Bootload
 *
 * This callback is fired when the OTA Client recevies a command to bootload
 * the newly downloaded OTA image.  This callback will perform the platform
 * specific to bootload their device.
 *
 * @param id This is the identifier relating to the image that has been
 * downloaded and is ready for bootload.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_CLIENT_BOOTLOAD
void emberAfOtaClientBootloadCallback(const EmberAfOtaImageId* id) {
  // Any final preperation prior to the bootload should be done here.
  // It is assumed that the device will reset in most all cases.
  // Please implement me.
}
#endif // EMBER_CALLBACK_OTA_CLIENT_BOOTLOAD

/** @brief Ota Server Query
 *
 * This callback is fired when the OTA server receives a query request by the
 * client.  The callback lets the server application indicate to the client
 * what the 'next' version of software is for the device, or if there is not
 * one available.
 *
 * @param currentImageId This is the current software image that the client
 * hase.  Ver.: always
 * @param hardwareVersion If this value is non-NULL, it indicates the hardware
 * version of the client device.  If NULL, the client did not specify a
 * hardware version.  Ver.: always
 * @param nextUpgradeImageId This is a pointer to a data structure containing
 * the 'next' software version for the client to download.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_SERVER_QUERY
int8u emberAfOtaServerQueryCallback(const EmberAfOtaImageId* currentImageId, 
                                    int16u* hardwareVersion, 
                                    EmberAfOtaImageId* nextUpgradeImageId) {
  // If a new software image is available, this function should return EMBER_ZCL_STATUS_SUCCESS
  // and populate the 'nextUpgradeImageId' structure with the appropriate values.
  // If no new software image is available (i.e. the client should not download a firmware image)
  // then the server should return EMBER_ZCL_STATUS_NO_IMAGE_AVAILABLE.
  return EMBER_ZCL_STATUS_NO_IMAGE_AVAILABLE;
}
#endif // EMBER_CALLBACK_OTA_SERVER_QUERY

/** @brief Ota Server Block Size
 *
 * This function provides a way for the server to adjust the block size of its
 * response to an Image block request by a client.
 *
 * @param clientNodeId The node Id of OTA client making an image block
 * request.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_SERVER_BLOCK_SIZE
int8u emberAfOtaServerBlockSizeCallback(EmberNodeId clientNodeId) {
  // This function provides a way for the server to potentially
  // adjust the block size based on the client who is requesting.
  // In other words if we are using source routing we will limit
  // data returned by enough to put a source route into the message.

  // Image Block Response Message Format
  // Status Code: 1-byte
  // Manuf Code:  2-bytes
  // Image Type:  2-bytes
  // File Ver:    4-bytes
  // File Offset: 4-bytes
  // Data Size:   1-byte
  // Data:        variable
  const int8u IMAGE_BLOCK_RESPONSE_OVERHEAD = (EMBER_AF_ZCL_OVERHEAD + 14);

  EmberApsFrame apsFrame;
  int8u maxSize;
  apsFrame.options = EMBER_APS_OPTION_NONE;

#if defined(SE_SECURITY_PROFILE_ENABLED)
  apsFrame.options |= EMBER_APS_OPTION_ENCRYPTION;
#endif

  maxSize = emberAfMaximumApsPayloadLength(EMBER_OUTGOING_DIRECT,
                                           clientNodeId,
                                           &apsFrame);
  maxSize -= IMAGE_BLOCK_RESPONSE_OVERHEAD;
  return maxSize;
}
#endif // EMBER_CALLBACK_OTA_SERVER_BLOCK_SIZE

/** @brief Ota Server Image Block Request
 *
 * This function is called when the server application receives an image block
 * request by a client.
 *
 * @param id This structure contains the image Id that the client is
 * requesting a block from.  Ver.: always
 * @param offset This is the offset within the OTA file that the client is
 * requesting.  Ver.: always
 * @param maxDataSize This is the maximum size that the client has requested
 * for the data block sent in the response.  Ver.: always
 * @param waitTimeMinutes If the function returns
 * EMBER_ZCL_STATUS_WAIT_FOR_DATA, then this is a pointer to the delay time in
 * minutes that will be sent back to the client.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_SERVER_IMAGE_BLOCK_REQUEST
int8u emberAfOtaServerImageBlockRequestCallback(const EmberAfOtaImageId* id, 
                                                int32u offset, 
                                                int8u maxDataSize, 
                                                int32u* waitTimeMinutes) {
  // This function should return one of the following:
  //   EMBER_ZCL_STATUS_SUCCESS - This indicates that the OTA server code should
  //     respond to the image block request normally.
  //   EMBER_ZCL_STATUS_ABORT - This indicates to the OTA server that it should
  //     tell the client to abort the download and make no more image block requests.
  //   EMBER_ZCL_STATUS_WAIT_FOR_DATA - This indicates to the OTA server to tell
  //     the client it should delay before asking for that data block again.
  //     The 'waitTimeInMinutes' value should be filled in with the delay value.
  return EMBER_ZCL_STATUS_SUCCESS;
}
#endif // EMBER_CALLBACK_OTA_SERVER_IMAGE_BLOCK_REQUEST

/** @brief Ota Server Upgrade End Request
 *
 * This function is called when the OTA server receives a request an upgrade
 * end request.  If the request indicated a successful download by the client,
 * the server must tell the client when and if to upgrade to the downloaded
 * image.
 *
 * @param source The node ID of the device that sent the upgrade end request. 
 * Ver.: always
 * @param status This is the ZCL status sent by the client indicating the
 * result of its attempt to download the new upgrade image.  If the status is
 * not EMBER_ZCL_STATUS_SUCCESS then this callback is merely informative and
 * no response mesasge will be generated by the server.  Ver.: always
 * @param returnValue If the server returns TRUE indicating that the client
 * should apply the upgrade, this time value indicates when in the future the
 * client should apply the upgrade.  Ver.: always
 * @param imageId This variable indicates the software version that the client
 * successfully downloaded and is asking to upgrade to.  Ver.: always
 */
#ifndef EMBER_CALLBACK_OTA_SERVER_UPGRADE_END_REQUEST
boolean emberAfOtaServerUpgradeEndRequestCallback(EmberNodeId source, 
                                                  int8u status, 
                                                  int32u* returnValue, 
                                                  const EmberAfOtaImageId* imageId) {
  // If the status value is not EMBER_ZCL_STATUS_SUCCESS, then this callback is
  // merely informative and no response message will be generated by the server.
  // If the server wants the client to NOT apply the upgrade, then it should
  // return FALSE.
  // If the server wants the client to apply the upgrade, it should return TRUE
  // and set the 'returnValue' parameter to when it wants the client to
  // apply the upgrade.  There are three possible values:
  //   0               =  Apply the upgrade now
  //   0xFFFFFFFF      =  Don't apply yet, ask again later.
  //   (anything-else) =  Apply the upgrade X minutes from now.
  *returnValue = 0;
  return TRUE;
}
#endif // EMBER_CALLBACK_OTA_SERVER_UPGRADE_END_REQUEST

/** @brief Ota Page Request Server Policy
 *
 * This callback is called by the OTA server page request code when it wants
 * to determine if it is allowed for an OTA client to make a page request.  It
 * is only called if page request support has been enabled on the server.  It
 * should return EMBER_ZCL_STATUS_SUCCESS if it allows the page request, and
 * EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND if it does not want to allow it.
 *
 */
#ifndef EMBER_CALLBACK_OTA_PAGE_REQUEST_SERVER_POLICY
int8u emberAfOtaPageRequestServerPolicyCallback(void) {
  return EMBER_ZCL_STATUS_SUCCESS;
}
#endif // EMBER_CALLBACK_OTA_PAGE_REQUEST_SERVER_POLICY

/** @brief Endpoint In Group
 *
 * This function is called by the framework when it needs to determine if an
 * endpoint is a member of a group.  The application should return TRUE if the
 * endpoint is a member of the group and FALSE otherwise.
 *
 * @param endpoint The endpoint.  Ver.: always
 * @param groupId The group identifier.  Ver.: always
 */
#ifndef EMBER_CALLBACK_GROUPS_CLUSTER_ENDPOINT_IN_GROUP
boolean emberAfGroupsClusterEndpointInGroupCallback(int8u endpoint, 
                                                    int16u groupId) {
  return FALSE;
}
#endif // EMBER_CALLBACK_GROUPS_CLUSTER_ENDPOINT_IN_GROUP

/** @brief Clear Group Table
 *
 * This function is called by the framework when the application should clear
 * the group table.
 *
 */
#ifndef EMBER_CALLBACK_GROUPS_CLUSTER_CLEAR_GROUP_TABLE
void emberAfGroupsClusterClearGroupTableCallback(void) {
  
}
#endif // EMBER_CALLBACK_GROUPS_CLUSTER_CLEAR_GROUP_TABLE

/** @brief Store Current Scene
 *
 * This function is called by the framework when the application should store
 * the current scene.  If an entry already exists in the scene table with the
 * same scene and group ids, the application should update the entry with the
 * current scene.  Otherwise, a new entry should be adde to the scene table,
 * if possible.
 *
 * @param endpoint The endpoint.  Ver.: always
 * @param groupId The group identifier.  Ver.: always
 * @param sceneId The scene identifier.  Ver.: always
 */
#ifndef EMBER_CALLBACK_SCENES_CLUSTER_STORE_CURRENT_SCENE
EmberAfStatus emberAfScenesClusterStoreCurrentSceneCallback(int8u endpoint, 
                                                            int16u groupId, 
                                                            int8u sceneId) {
  return EMBER_ZCL_STATUS_FAILURE;
}
#endif // EMBER_CALLBACK_SCENES_CLUSTER_STORE_CURRENT_SCENE

/** @brief Recall Saved Scene
 *
 * This function is called by the framework when the application should recall
 * a saved scene.
 *
 * @param endpoint The endpoint.  Ver.: always
 * @param groupId The group identifier.  Ver.: always
 * @param sceneId The scene identifier.  Ver.: always
 */
#ifndef EMBER_CALLBACK_SCENES_CLUSTER_RECALL_SAVED_SCENE
EmberAfStatus emberAfScenesClusterRecallSavedSceneCallback(int8u endpoint, 
                                                           int16u groupId, 
                                                           int8u sceneId) {
  return EMBER_ZCL_STATUS_FAILURE;
}
#endif // EMBER_CALLBACK_SCENES_CLUSTER_RECALL_SAVED_SCENE

/** @brief ClearSceneTable
 *
 * This function is called by the framework when the application should clear
 * the scene table.
 *
 */
#ifndef EMBER_CALLBACK_SCENES_CLUSTER_CLEAR_SCENE_TABLE
void emberAfScenesClusterClearSceneTableCallback(void) {
  
}
#endif // EMBER_CALLBACK_SCENES_CLUSTER_CLEAR_SCENE_TABLE

/** @brief Interpan Send Message
 *
 * This function will send a raw MAC message with interpan frame format using
 * the passed parameters.
 *
 * @param header Interpan header info  Ver.: always
 * @param messageLength The length of the message received or to send  Ver.:
 * always
 * @param message The message data received or to send.  Ver.: always
 */
#ifndef EMBER_CALLBACK_INTERPAN_SEND_MESSAGE
EmberStatus emberAfInterpanSendMessageCallback(EmberAfInterpanHeader* header, 
                                               int16u messageLength, 
                                               int8u* message) {
  return EMBER_LIBRARY_NOT_PRESENT;
}
#endif // EMBER_CALLBACK_INTERPAN_SEND_MESSAGE

/** @brief Interpan Init
 *
 * Initializes the interpan functionality.
 *
 */
#ifndef EMBER_CALLBACK_INTERPAN_INIT
void emberAfInterpanInitCallback(void) {
  
}
#endif // EMBER_CALLBACK_INTERPAN_INIT

/** @brief Unused Pan Id Found
 *
 * This is called by the framework on behalf of the form-and-join library to
 * notify the application of the PAN id and channel found following a call to
 * ::emberScanForUnusedPanId().  See form-and-join documentation for more
 * information.
 *
 * @param panId   Ver.: always
 * @param channel   Ver.: always
 */
#ifndef EMBER_CALLBACK_UNUSED_PAN_ID_FOUND
void emberAfUnusedPanIdFoundCallback(EmberPanId panId, 
                                     int8u channel) {
  
}
#endif // EMBER_CALLBACK_UNUSED_PAN_ID_FOUND

/** @brief Joinable Network Found
 *
 * This is called by the framework on behalf of the form-and-join library to
 * notify the application of the network found after a call to
 * ::emberScanForJoinableNetwork() or ::emberScanForNextJoinableNetwork(). 
 * See form-and-join documentation for more information.
 *
 * @param networkFound   Ver.: always
 * @param lqi   Ver.: always
 * @param rssi   Ver.: always
 */
#ifndef EMBER_CALLBACK_JOINABLE_NETWORK_FOUND
void emberAfJoinableNetworkFoundCallback(EmberZigbeeNetwork * networkFound, 
                                         int8u lqi, 
                                         int8s rssi) {
  
}
#endif // EMBER_CALLBACK_JOINABLE_NETWORK_FOUND

/** @brief Scan Error
 *
 * This is called by the framework on behalf of the form-and-join library to
 * notify the application if an error occurs while scanning.  See
 * form-and-join documentation for more information.
 *
 * @param status The status of the scan.  Ver.: always
 */
#ifndef EMBER_CALLBACK_SCAN_ERROR
void emberAfScanErrorCallback(EmberStatus status) {
  
}
#endif // EMBER_CALLBACK_SCAN_ERROR

/** @brief Find Unused Pan Id And Form
 *
 * This function is called by the framework to search for an unused PAN id and
 * form a new network.  The application should return EMBER_SUCCESS if the
 * operation was initiated successfully.
 *
 */
#ifndef EMBER_CALLBACK_FIND_UNUSED_PAN_ID_AND_FORM
EmberStatus emberAfFindUnusedPanIdAndFormCallback(void) {
  return EMBER_LIBRARY_NOT_PRESENT;
}
#endif // EMBER_CALLBACK_FIND_UNUSED_PAN_ID_AND_FORM

/** @brief Start Search For Joinable Network
 *
 * This function is called by the framework to search for joinable networks
 * and join a network.  The application should return EMBER_SUCCESS if the
 * operation was initiated successfully.
 *
 */
#ifndef EMBER_CALLBACK_START_SEARCH_FOR_JOINABLE_NETWORK
EmberStatus emberAfStartSearchForJoinableNetworkCallback(void) {
  return EMBER_LIBRARY_NOT_PRESENT;
}
#endif // EMBER_CALLBACK_START_SEARCH_FOR_JOINABLE_NETWORK

/** @brief Continue Joinable Network Search
 *
 * This is called by the framework to instruct the application to continue its
 * joinable network search.
 *
 */
#ifndef EMBER_CALLBACK_CONTINUE_JOINABLE_NETWORK_SEARCH
void emberAfContinueJoinableNetworkSearchCallback(void) {
  
}
#endif // EMBER_CALLBACK_CONTINUE_JOINABLE_NETWORK_SEARCH

/** @brief Network Find Operation Complete
 *
 * This is called by the framework when the network find operation is
 * complete.
 *
 */
#ifndef EMBER_CALLBACK_NETWORK_FIND_OPERATION_COMPLETE
void emberAfNetworkFindOperationCompleteCallback(void) {
  
}
#endif // EMBER_CALLBACK_NETWORK_FIND_OPERATION_COMPLETE

/** @brief Client Command Received
 *
 * This function is called by the application framework when a
 * server-to-client key establishment command is received but has yet to be
 * handled by the framework code.  This function should return a boolean value
 * indicating whether the command has been handled by the application code and
 * should not be further processed by the framework.
 *
 * @param cmd   Ver.: always
 */
#ifndef EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_CLIENT_COMMAND_RECEIVED
boolean emberAfKeyEstablishmentClusterClientCommandReceivedCallback(EmberAfClusterCommand * cmd) {
  return FALSE;
}
#endif // EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_CLIENT_COMMAND_RECEIVED

/** @brief Server Command Received
 *
 * This function is called by the application framework when a
 * client-to-server key establishment command is received but has yet to be
 * handled by the framework code.  This function should return a boolean value
 * indicating whether the command has been handled by the application code and
 * should not be further processed by the framework.
 *
 * @param cmd   Ver.: always
 */
#ifndef EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_SERVER_COMMAND_RECEIVED
boolean emberAfKeyEstablishmentClusterServerCommandReceivedCallback(EmberAfClusterCommand * cmd) {
  return FALSE;
}
#endif // EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_SERVER_COMMAND_RECEIVED
