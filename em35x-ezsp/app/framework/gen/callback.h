// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generateCallbackPrototypes()
//

// Enclosing macro to prevent multiple inclusion
#ifndef __EMBER_AF_CALLBACK_PROTOTYPES__
#define __EMBER_AF_CALLBACK_PROTOTYPES__


/**
 * @addtogroup callback Application Framework V2 callback interface Reference
 * This header provides callback function prototypes to interface the developer's
 * application code with the Ember Application Framework.
 * @{
 */


#include "app/framework/include/af-types.h"


/** @name Non-Cluster Related Callbacks */
// @{
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
boolean emberAfReadAttributesResponseCallback(EmberAfClusterId clusterId, 
                                              int8u * buffer, 
                                              int16u bufLen);
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
boolean emberAfWriteAttributesResponseCallback(EmberAfClusterId clusterId, 
                                               int8u * buffer, 
                                               int16u bufLen);
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
boolean emberAfConfigureReportingResponseCallback(EmberAfClusterId clusterId, 
                                                  int8u * buffer, 
                                                  int16u bufLen);
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
boolean emberAfReadReportingConfigurationResponseCallback(EmberAfClusterId clusterId, 
                                                          int8u * buffer, 
                                                          int16u bufLen);
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
boolean emberAfReportAttributesCallback(EmberAfClusterId clusterId, 
                                        int8u * buffer, 
                                        int16u bufLen);
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
boolean emberAfDefaultResponseCallback(EmberAfClusterId clusterId, 
                                       int8u commandId, 
                                       EmberAfStatus status);
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
boolean emberAfDiscoverAttributesResponseCallback(EmberAfClusterId clusterId, 
                                                  boolean discoveryComplete, 
                                                  int8u * buffer, 
                                                  int16u bufLen);
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
EmberAfAttributeWritePermission emberAfAllowNetworkWriteAttributeCallback(int8u endpoint, 
                                                                          EmberAfClusterId clusterId, 
                                                                          EmberAfAttributeId attributeId, 
                                                                          int8u mask, 
                                                                          int16u manufacturerCode, 
                                                                          int8u* value, 
                                                                          int8u type);
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
void emberAfPreAttributeChangeCallback(int8u endpoint, 
                                       EmberAfClusterId clusterId, 
                                       EmberAfAttributeId attributeId, 
                                       int8u mask, 
                                       int16u manufacturerCode, 
                                       int8u type, 
                                       int8u size, 
                                       int8u* value);
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
void emberAfPostAttributeChangeCallback(int8u endpoint, 
                                        EmberAfClusterId clusterId, 
                                        EmberAfAttributeId attributeId, 
                                        int8u mask, 
                                        int16u manufacturerCode, 
                                        int8u type, 
                                        int8u size, 
                                        int8u* value);
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
boolean emberAfPreMessageReceivedCallback(EmberAfIncomingMessage* incomingMessage);
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
boolean emberAfPreCommandReceivedCallback(EmberAfClusterCommand* cmd);
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
boolean emberAfPreZDOMessageReceivedCallback(EmberNodeId emberNodeId, 
                                             EmberApsFrame* apsFrame, 
                                             int8u* message, 
                                             int16u length);
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
boolean emberAfMessageSentCallback(EmberOutgoingMessageType type, 
                                   int16u indexOrDestination, 
                                   EmberApsFrame* apsFrame, 
                                   int16u msgLen, 
                                   int8u* message, 
                                   EmberStatus status);
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
boolean emberAfStackStatusCallback(EmberStatus status);
/** @brief Ncp Init
 *
 * This callback is used for initializing the network coprocessor either at
 * startup, or upon reset. It should be used to perform any kind of EZSP
 * initialization, as it will be called every time when NCP is reset. In an
 * SOC environment, this callbacks is not used.
 *
 */
void emberAfNcpInitCallback(void);
/** @brief Main Init
 *
 * This is the main application initialization callback. It is called prior to
 * application initialization and gives the application a chance to take care
 * of any of its own initialization procedures.
 *
 */
void emberAfMainInitCallback(void);
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
void emberAfClusterInitCallback(int8u endpoint, 
                                EmberAfClusterId clusterId);
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
boolean emberAfPreGoToSleepCallback(int32u sleepDurationAttempt);
/** @brief Post Wake Up
 *
 * Called directly after a device wakes up from sleep. This function is passed
 * the number of milliseconds the device actually slept for.
 *
 * @param sleepDuration   Ver.: always
 */
void emberAfPostWakeUpCallback(int32u sleepDuration);
/** @brief Main Tick
 *
 * Whenever main application tick is called, this callback will be called at
 * the end of the main tick execution.
 *
 */
void emberAfMainTickCallback(void);
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
boolean emberAfExternalAttributeWriteCallback(int8u endpoint, 
                                              EmberAfClusterId clusterId, 
                                              EmberAfAttributeMetadata * attributeMetadata, 
                                              int16u manufacturerCode, 
                                              int8u * buffer);
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
boolean emberAfExternalAttributeReadCallback(int8u endpoint, 
                                             EmberAfClusterId clusterId, 
                                             EmberAfAttributeMetadata * attributeMetadata, 
                                             int16u manufacturerCode, 
                                             int8u * buffer);
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
EmberAfStatus emberAfReportEntryConfiguredCallback(EmberAfReportEntry * entry);
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
void emberAfTrustCenterJoinCallback(EmberNodeId newNodeId, 
                                    EmberEUI64 newNodeEui64, 
                                    EmberNodeId parentOfNewNode, 
                                    EmberDeviceUpdate status, 
                                    EmberJoinDecision decision);
/** @brief Get Current Time
 *
 * This callback is called when device attempts to get current time from the
 * hardware. If this device has means to retrieve exact time, then this method
 * should implement it. If the callback can't provide the exact time it should
 * return 0 to indicate failure. Default action is to return 0, which
 * indicates that device does not have access to real time.
 *
 */
int32u emberAfGetCurrentTimeCallback(void);
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
void emberAfSetTimeCallback(int32u utcTime);
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
EmberStatus emberAfInitiateKeyEstablishmentCallback(EmberNodeId nodeId, 
                                                    int8u endpoint);
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
EmberStatus emberAfInitiateInterPanKeyEstablishmentCallback(EmberPanId panId, 
                                                            const EmberEUI64 eui64);
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
boolean emberAfKeyEstablishmentCallback(EmberAfKeyEstablishmentNotifyMessage status, 
                                        boolean amInitiator, 
                                        EmberNodeId partnerShortId, 
                                        int8u delayInSeconds);
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
boolean emberAfInterPanKeyEstablishmentCallback(EmberAfKeyEstablishmentNotifyMessage status, 
                                                boolean amInitiator, 
                                                EmberPanId panId, 
                                                const EmberEUI64 eui64, 
                                                int8u delayInSeconds);
/** @brief Performing Key Establishment
 *
 * This function is called by the framework to determine if the device is
 * performing key establishment.  The application should return TRUE if key
 * establishment is in progress.
 *
 */
boolean emberAfPerformingKeyEstablishmentCallback(void);
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
EmberStatus emberAfInitiatePartnerLinkKeyExchangeCallback(EmberNodeId target, 
                                                          int8u endpoint, 
                                                          EmberAfPartnerLinkKeyExchangeCallback * callback);
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
EmberStatus emberAfPartnerLinkKeyExchangeRequestCallback(EmberEUI64 partner);
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
void emberAfPartnerLinkKeyExchangeResponseCallback(EmberNodeId sender, 
                                                   EmberZdoStatus status);
/** @brief Registration Start
 *
 * This callback is called when the device joins a network and the
 * registration process should begin.  The application should return
 * EMBER_SUCCESS if the registration process started successfully.  When
 * registration is complete, the application should call
 * emberAfRegistrationCallback with an indication of success or failure.
 *
 */
EmberStatus emberAfRegistrationStartCallback(void);
/** @brief Registration Abort
 *
 * This callback is called when the device should abort the registration
 * process.
 *
 */
void emberAfRegistrationAbortCallback(void);
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
void emberAfRegistrationCallback(boolean success);
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
void emberAfTrustCenterKeepaliveUpdateCallback(boolean registrationComplete);
/** @brief Trust Center Keepalive Abort
 *
 * This callback is called when the device should abort the trust center
 * keepalive process.
 *
 */
void emberAfTrustCenterKeepaliveAbortCallback(void);
/** @brief Custom Command Line
 *
 * If you enable this callback, then it will be called when 'custom' CLI
 * command is executed. It is responsible for reading it's own arguments.
 *
 */
void emberAfCustomCommandLineCallback(void);
/** @brief Ota Server Incoming Message Raw
 *
 * This callback is for processing incoming messages for the Over-the-air
 * bootload cluster server.  ZCL will not process the message and instead hand
 * the raw over the air data to the callback for its own processing.
 *
 * @param message A pointer to the structure containing the message buffer and
 * other information about it.  Ver.: always
 */
boolean emberAfOtaServerIncomingMessageRawCallback(EmberAfClusterCommand * message);
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
boolean emberAfOtaServerSendImageNotifyCallback(EmberNodeId dest, 
                                                int8u endpoint, 
                                                int8u payloadType, 
                                                int8u queryJitter, 
                                                const EmberAfOtaImageId* id);
/** @brief Ota Storage Driver Init
 *
 * The initialization code for the OTA storage driver.
 *
 */
boolean emberAfOtaStorageDriverInitCallback(void);
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
boolean emberAfOtaStorageDriverReadCallback(int32u offset, 
                                            int32u length, 
                                            int8u* returnData);
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
boolean emberAfOtaStorageDriverWriteCallback(const int8u* dataToWrite, 
                                             int32u offset, 
                                             int32u length);
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
int8u emberAfOtaBootloadCallback(const EmberAfOtaImageId* id, 
                                 int16u ncpUpgradeTagId);
/** @brief Ota Storage Init
 *
 * This callback initializes the ZigBee Over-the-air storage module.
 *
 */
EmberAfOtaStorageStatus emberAfOtaStorageInitCallback(void);
/** @brief Ota Storage Close
 *
 * This callback shuts down the ZigBee Over-the-air storage module.
 *
 */
void emberAfOtaStorageCloseCallback(void);
/** @brief Ota Storage Get Count
 *
 * This callback returns the total number of ZigBee Over-the-air upgrade
 * images stored in the storage module.
 *
 */
int8u emberAfOtaStorageGetCountCallback(void);
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
EmberAfOtaImageId emberAfOtaStorageSearchCallback(int16u manufacturerId, 
                                                  int16u imageTypeId, 
                                                  const int16u* hardwareVersion);
/** @brief Ota Storage Get Total Image Size
 *
 * This function returns the total size of the ZigBee Over-the-air file with
 * the passed parameters.  If no file is found with those parameters, 0 is
 * returned.
 *
 * @param id A pointer to the image identifier for the OTA file to retrieve
 * information for.  Ver.: always
 */
int32u emberAfOtaStorageGetTotalImageSizeCallback(const EmberAfOtaImageId* id);
/** @brief Ota Storage Iterator First
 *
 * This callback lets you walk through the list of all OTA files by jumping to
 * the first file in the list maintained by the storage module.  If there is
 * no file then emberAfOtaInvalidImageId is returned.
 *
 */
EmberAfOtaImageId emberAfOtaStorageIteratorFirstCallback(void);
/** @brief Ota Storage Iterator Next
 *
 * This callback lets you walk through the list of all OTA files by jumping to
 * the next file in the list maintained by the storage module.  If there is no
 * next file then emberAfOtaInvalidImageId is returned.
 *
 */
EmberAfOtaImageId emberAfOtaStorageIteratorNextCallback(void);
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
EmberAfOtaStorageStatus emberAfOtaStorageGetFullHeaderCallback(const EmberAfOtaImageId* id, 
                                                               EmberAfOtaHeader* returnData);
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
EmberAfOtaStorageStatus emberAfOtaStorageReadImageDataCallback(const EmberAfOtaImageId* id, 
                                                               int32u offset, 
                                                               int32u length, 
                                                               int8u* returnData, 
                                                               int32u* returnedLength);
/** @brief Ota Storage Clear Temp Data
 *
 * This function clears any existing temp data that was downloaed.  It is used
 * immediately prior to downloading a raw image over the air.
 *
 */
EmberAfOtaStorageStatus emberAfOtaStorageClearTempDataCallback(void);
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
EmberAfOtaStorageStatus emberAfOtaStorageWriteTempDataCallback(int32u offset, 
                                                               int32u length, 
                                                               const int8u* data);
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
EmberAfOtaStorageStatus emberAfOtaStorageCheckTempDataCallback(int32u* currentOffset, 
                                                               int32u* totalImageSize, 
                                                               EmberAfOtaImageId* newFileInfo);
/** @brief Ota Storage Finish Download
 *
 * This function indicates to the storage module that the download has
 * finished.
 *
 * @param offset The final offset of the downloaded file (i.e. the total size)
 * Ver.: always
 */
EmberAfOtaStorageStatus emberAfOtaStorageFinishDownloadCallback(int32u offset);
/** @brief Ota Client Incoming Message Raw
 *
 * This callback is for processing incoming messages for the Over-the-air
 * bootload cluster client.  ZCL will not process the message and instead hand
 * the raw over the air data to the callback for its own processing.
 *
 * @param message A pointer to the structure containing the message buffer and
 * other information about it.  Ver.: always
 */
boolean emberAfOtaClientIncomingMessageRawCallback(EmberAfClusterCommand * message);
/** @brief Ota Client Start
 *
 * This callback should be called when the profile specific registration has
 * completed successfully.  It will start the client's state machine that will
 * find the OTA server, query it for the next image, download the image, wait
 * for the bootload message, and kick off the bootload.
 *
 */
void emberAfOtaClientStartCallback(void);
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
void emberAfOtaClientVersionInfoCallback(EmberAfOtaImageId* currentImageInfo, 
                                         int16u* hardwareVersion);
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
EmberAfImageVerifyStatus emberAfOtaClientCustomVerifyCallback(boolean newVerification, 
                                                              const EmberAfOtaImageId* id);
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
boolean emberAfOtaClientDownloadCompleteCallback(boolean success, 
                                                 const EmberAfOtaImageId* id);
/** @brief Ota Client Bootload
 *
 * This callback is fired when the OTA Client recevies a command to bootload
 * the newly downloaded OTA image.  This callback will perform the platform
 * specific to bootload their device.
 *
 * @param id This is the identifier relating to the image that has been
 * downloaded and is ready for bootload.  Ver.: always
 */
void emberAfOtaClientBootloadCallback(const EmberAfOtaImageId* id);
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
int8u emberAfOtaServerQueryCallback(const EmberAfOtaImageId* currentImageId, 
                                    int16u* hardwareVersion, 
                                    EmberAfOtaImageId* nextUpgradeImageId);
/** @brief Ota Server Block Size
 *
 * This function provides a way for the server to adjust the block size of its
 * response to an Image block request by a client.
 *
 * @param clientNodeId The node Id of OTA client making an image block
 * request.  Ver.: always
 */
int8u emberAfOtaServerBlockSizeCallback(EmberNodeId clientNodeId);
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
int8u emberAfOtaServerImageBlockRequestCallback(const EmberAfOtaImageId* id, 
                                                int32u offset, 
                                                int8u maxDataSize, 
                                                int32u* waitTimeMinutes);
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
boolean emberAfOtaServerUpgradeEndRequestCallback(EmberNodeId source, 
                                                  int8u status, 
                                                  int32u* returnValue, 
                                                  const EmberAfOtaImageId* imageId);
/** @brief Ota Page Request Server Policy
 *
 * This callback is called by the OTA server page request code when it wants
 * to determine if it is allowed for an OTA client to make a page request.  It
 * is only called if page request support has been enabled on the server.  It
 * should return EMBER_ZCL_STATUS_SUCCESS if it allows the page request, and
 * EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND if it does not want to allow it.
 *
 */
int8u emberAfOtaPageRequestServerPolicyCallback(void);
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
EmberStatus emberAfInterpanSendMessageCallback(EmberAfInterpanHeader* header, 
                                               int16u messageLength, 
                                               int8u* message);
/** @brief Interpan Init
 *
 * Initializes the interpan functionality.
 *
 */
void emberAfInterpanInitCallback(void);
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
void emberAfUnusedPanIdFoundCallback(EmberPanId panId, 
                                     int8u channel);
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
void emberAfJoinableNetworkFoundCallback(EmberZigbeeNetwork * networkFound, 
                                         int8u lqi, 
                                         int8s rssi);
/** @brief Scan Error
 *
 * This is called by the framework on behalf of the form-and-join library to
 * notify the application if an error occurs while scanning.  See
 * form-and-join documentation for more information.
 *
 * @param status The status of the scan.  Ver.: always
 */
void emberAfScanErrorCallback(EmberStatus status);
/** @brief Find Unused Pan Id And Form
 *
 * This function is called by the framework to search for an unused PAN id and
 * form a new network.  The application should return EMBER_SUCCESS if the
 * operation was initiated successfully.
 *
 */
EmberStatus emberAfFindUnusedPanIdAndFormCallback(void);
/** @brief Start Search For Joinable Network
 *
 * This function is called by the framework to search for joinable networks
 * and join a network.  The application should return EMBER_SUCCESS if the
 * operation was initiated successfully.
 *
 */
EmberStatus emberAfStartSearchForJoinableNetworkCallback(void);
/** @brief Continue Joinable Network Search
 *
 * This is called by the framework to instruct the application to continue its
 * joinable network search.
 *
 */
void emberAfContinueJoinableNetworkSearchCallback(void);
/** @brief Network Find Operation Complete
 *
 * This is called by the framework when the network find operation is
 * complete.
 *
 */
void emberAfNetworkFindOperationCompleteCallback(void);
/** @} END Non-Cluster Related Callbacks */

/** @name Basic Cluster Callbacks */
// @{

/** @brief Reset To Factory Defaults
 *
 *
 */
boolean emberAfBasicClusterResetToFactoryDefaultsCallback(void);
/** @brief Server Init
 *
 * Basic cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfBasicClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Basic cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfBasicClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Basic cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfBasicClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Basic cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfBasicClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Basic cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfBasicClusterServerAttributeChangedCallback(int8u endpoint, 
                                                       EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Basic cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfBasicClusterClientAttributeChangedCallback(int8u endpoint, 
                                                       EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Basic cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfBasicClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                           EmberAfAttributeId attributeId, 
                                                                           int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Basic cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfBasicClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                           EmberAfAttributeId attributeId, 
                                                                           int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Basic cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfBasicClusterServerDefaultResponseCallback(int8u endpoint, 
                                                      int8u commandId, 
                                                      EmberAfStatus status);
/** @brief Client Default Response
 *
 * Basic cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfBasicClusterClientDefaultResponseCallback(int8u endpoint, 
                                                      int8u commandId, 
                                                      EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Basic cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfBasicClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                  int16u indexOrDestination, 
                                                  EmberApsFrame * apsFrame, 
                                                  int16u msgLen, 
                                                  int8u * message, 
                                                  EmberStatus status);
/** @brief Client Message Sent
 *
 * Basic cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfBasicClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                  int16u indexOrDestination, 
                                                  EmberApsFrame * apsFrame, 
                                                  int16u msgLen, 
                                                  int8u * message, 
                                                  EmberStatus status);

/** @} END Basic Cluster Callbacks */

/** @name Power Configuration Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Power Configuration cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPowerConfigClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Power Configuration cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPowerConfigClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Power Configuration cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfPowerConfigClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Power Configuration cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfPowerConfigClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Power Configuration cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfPowerConfigClusterServerAttributeChangedCallback(int8u endpoint, 
                                                             EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Power Configuration cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfPowerConfigClusterClientAttributeChangedCallback(int8u endpoint, 
                                                             EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Power Configuration cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfPowerConfigClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                 EmberAfAttributeId attributeId, 
                                                                                 int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Power Configuration cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfPowerConfigClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                 EmberAfAttributeId attributeId, 
                                                                                 int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Power Configuration cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfPowerConfigClusterServerDefaultResponseCallback(int8u endpoint, 
                                                            int8u commandId, 
                                                            EmberAfStatus status);
/** @brief Client Default Response
 *
 * Power Configuration cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfPowerConfigClusterClientDefaultResponseCallback(int8u endpoint, 
                                                            int8u commandId, 
                                                            EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Power Configuration cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfPowerConfigClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                        int16u indexOrDestination, 
                                                        EmberApsFrame * apsFrame, 
                                                        int16u msgLen, 
                                                        int8u * message, 
                                                        EmberStatus status);
/** @brief Client Message Sent
 *
 * Power Configuration cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfPowerConfigClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                        int16u indexOrDestination, 
                                                        EmberApsFrame * apsFrame, 
                                                        int16u msgLen, 
                                                        int8u * message, 
                                                        EmberStatus status);

/** @} END Power Configuration Cluster Callbacks */

/** @name Device Temperature Configuration Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Device Temperature Configuration cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfDeviceTempClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Device Temperature Configuration cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfDeviceTempClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Device Temperature Configuration cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfDeviceTempClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Device Temperature Configuration cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfDeviceTempClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Device Temperature Configuration cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfDeviceTempClusterServerAttributeChangedCallback(int8u endpoint, 
                                                            EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Device Temperature Configuration cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfDeviceTempClusterClientAttributeChangedCallback(int8u endpoint, 
                                                            EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Device Temperature Configuration cluster, Server Manufacturer Specific
 * Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfDeviceTempClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                EmberAfAttributeId attributeId, 
                                                                                int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Device Temperature Configuration cluster, Client Manufacturer Specific
 * Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfDeviceTempClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                EmberAfAttributeId attributeId, 
                                                                                int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Device Temperature Configuration cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfDeviceTempClusterServerDefaultResponseCallback(int8u endpoint, 
                                                           int8u commandId, 
                                                           EmberAfStatus status);
/** @brief Client Default Response
 *
 * Device Temperature Configuration cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfDeviceTempClusterClientDefaultResponseCallback(int8u endpoint, 
                                                           int8u commandId, 
                                                           EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Device Temperature Configuration cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfDeviceTempClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                       int16u indexOrDestination, 
                                                       EmberApsFrame * apsFrame, 
                                                       int16u msgLen, 
                                                       int8u * message, 
                                                       EmberStatus status);
/** @brief Client Message Sent
 *
 * Device Temperature Configuration cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfDeviceTempClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                       int16u indexOrDestination, 
                                                       EmberApsFrame * apsFrame, 
                                                       int16u msgLen, 
                                                       int8u * message, 
                                                       EmberStatus status);

/** @} END Device Temperature Configuration Cluster Callbacks */

/** @name Identify Cluster Callbacks */
// @{

/** @brief Identify
 *
 *
 * @param identifyTime   Ver.: always
 */
boolean emberAfIdentifyClusterIdentifyCallback(int16u identifyTime);
/** @brief Identify Query
 *
 *
 */
boolean emberAfIdentifyClusterIdentifyQueryCallback(void);
/** @brief Identify Query Response
 *
 *
 * @param timeout   Ver.: always
 */
boolean emberAfIdentifyClusterIdentifyQueryResponseCallback(int16u timeout);
/** @brief Server Init
 *
 * Identify cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIdentifyClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Identify cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIdentifyClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Identify cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIdentifyClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Identify cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIdentifyClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Identify cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIdentifyClusterServerAttributeChangedCallback(int8u endpoint, 
                                                          EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Identify cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIdentifyClusterClientAttributeChangedCallback(int8u endpoint, 
                                                          EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Identify cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfIdentifyClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                              EmberAfAttributeId attributeId, 
                                                                              int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Identify cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfIdentifyClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                              EmberAfAttributeId attributeId, 
                                                                              int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Identify cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfIdentifyClusterServerDefaultResponseCallback(int8u endpoint, 
                                                         int8u commandId, 
                                                         EmberAfStatus status);
/** @brief Client Default Response
 *
 * Identify cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfIdentifyClusterClientDefaultResponseCallback(int8u endpoint, 
                                                         int8u commandId, 
                                                         EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Identify cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfIdentifyClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                     int16u indexOrDestination, 
                                                     EmberApsFrame * apsFrame, 
                                                     int16u msgLen, 
                                                     int8u * message, 
                                                     EmberStatus status);
/** @brief Client Message Sent
 *
 * Identify cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfIdentifyClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                     int16u indexOrDestination, 
                                                     EmberApsFrame * apsFrame, 
                                                     int16u msgLen, 
                                                     int8u * message, 
                                                     EmberStatus status);

/** @} END Identify Cluster Callbacks */

/** @name Groups Cluster Callbacks */
// @{

/** @brief Endpoint In Group
 *
 * This function is called by the framework when it needs to determine if an
 * endpoint is a member of a group.  The application should return TRUE if the
 * endpoint is a member of the group and FALSE otherwise.
 *
 * @param endpoint The endpoint.  Ver.: always
 * @param groupId The group identifier.  Ver.: always
 */
boolean emberAfGroupsClusterEndpointInGroupCallback(int8u endpoint, 
                                                    int16u groupId);
/** @brief Clear Group Table
 *
 * This function is called by the framework when the application should clear
 * the group table.
 *
 */
void emberAfGroupsClusterClearGroupTableCallback(void);
/** @brief Add Group
 *
 *
 * @param groupId   Ver.: always
 * @param groupName   Ver.: always
 */
boolean emberAfGroupsClusterAddGroupCallback(int16u groupId, 
                                             int8u* groupName);
/** @brief View Group
 *
 *
 * @param groupId   Ver.: always
 */
boolean emberAfGroupsClusterViewGroupCallback(int16u groupId);
/** @brief Get Group Membership
 *
 *
 * @param groupCount   Ver.: always
 * @param groupList   Ver.: always
 */
boolean emberAfGroupsClusterGetGroupMembershipCallback(int8u groupCount, 
                                                       int8u* groupList);
/** @brief Remove Group
 *
 *
 * @param groupId   Ver.: always
 */
boolean emberAfGroupsClusterRemoveGroupCallback(int16u groupId);
/** @brief Remove All Groups
 *
 *
 */
boolean emberAfGroupsClusterRemoveAllGroupsCallback(void);
/** @brief Add Group If Identifying
 *
 *
 * @param groupId   Ver.: always
 * @param groupName   Ver.: always
 */
boolean emberAfGroupsClusterAddGroupIfIdentifyingCallback(int16u groupId, 
                                                          int8u* groupName);
/** @brief Add Group Response
 *
 *
 * @param status   Ver.: always
 * @param groupId   Ver.: always
 */
boolean emberAfGroupsClusterAddGroupResponseCallback(int8u status, 
                                                     int16u groupId);
/** @brief View Group Response
 *
 *
 * @param status   Ver.: always
 * @param groupId   Ver.: always
 * @param groupName   Ver.: always
 */
boolean emberAfGroupsClusterViewGroupResponseCallback(int8u status, 
                                                      int16u groupId, 
                                                      int8u* groupName);
/** @brief Get Group Membership Response
 *
 *
 * @param capacity   Ver.: always
 * @param groupCount   Ver.: always
 * @param groupList   Ver.: always
 */
boolean emberAfGroupsClusterGetGroupMembershipResponseCallback(int8u capacity, 
                                                               int8u groupCount, 
                                                               int8u* groupList);
/** @brief Remove Group Response
 *
 *
 * @param status   Ver.: always
 * @param groupId   Ver.: always
 */
boolean emberAfGroupsClusterRemoveGroupResponseCallback(int8u status, 
                                                        int16u groupId);
/** @brief Server Init
 *
 * Groups cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfGroupsClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Groups cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfGroupsClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Groups cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfGroupsClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Groups cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfGroupsClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Groups cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfGroupsClusterServerAttributeChangedCallback(int8u endpoint, 
                                                        EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Groups cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfGroupsClusterClientAttributeChangedCallback(int8u endpoint, 
                                                        EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Groups cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfGroupsClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                            EmberAfAttributeId attributeId, 
                                                                            int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Groups cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfGroupsClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                            EmberAfAttributeId attributeId, 
                                                                            int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Groups cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfGroupsClusterServerDefaultResponseCallback(int8u endpoint, 
                                                       int8u commandId, 
                                                       EmberAfStatus status);
/** @brief Client Default Response
 *
 * Groups cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfGroupsClusterClientDefaultResponseCallback(int8u endpoint, 
                                                       int8u commandId, 
                                                       EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Groups cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfGroupsClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                   int16u indexOrDestination, 
                                                   EmberApsFrame * apsFrame, 
                                                   int16u msgLen, 
                                                   int8u * message, 
                                                   EmberStatus status);
/** @brief Client Message Sent
 *
 * Groups cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfGroupsClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                   int16u indexOrDestination, 
                                                   EmberApsFrame * apsFrame, 
                                                   int16u msgLen, 
                                                   int8u * message, 
                                                   EmberStatus status);

/** @} END Groups Cluster Callbacks */

/** @name Scenes Cluster Callbacks */
// @{

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
EmberAfStatus emberAfScenesClusterStoreCurrentSceneCallback(int8u endpoint, 
                                                            int16u groupId, 
                                                            int8u sceneId);
/** @brief Recall Saved Scene
 *
 * This function is called by the framework when the application should recall
 * a saved scene.
 *
 * @param endpoint The endpoint.  Ver.: always
 * @param groupId The group identifier.  Ver.: always
 * @param sceneId The scene identifier.  Ver.: always
 */
EmberAfStatus emberAfScenesClusterRecallSavedSceneCallback(int8u endpoint, 
                                                           int16u groupId, 
                                                           int8u sceneId);
/** @brief ClearSceneTable
 *
 * This function is called by the framework when the application should clear
 * the scene table.
 *
 */
void emberAfScenesClusterClearSceneTableCallback(void);
/** @brief Add Scene
 *
 *
 * @param groupId   Ver.: always
 * @param sceneId   Ver.: always
 * @param transitionTime   Ver.: always
 * @param sceneName   Ver.: always
 * @param extensionFieldSets   Ver.: always
 */
boolean emberAfScenesClusterAddSceneCallback(int16u groupId, 
                                             int8u sceneId, 
                                             int16u transitionTime, 
                                             int8u* sceneName, 
                                             int8u* extensionFieldSets);
/** @brief View Scene
 *
 *
 * @param groupId   Ver.: always
 * @param sceneId   Ver.: always
 */
boolean emberAfScenesClusterViewSceneCallback(int16u groupId, 
                                              int8u sceneId);
/** @brief Remove Scene
 *
 *
 * @param groupId   Ver.: always
 * @param sceneId   Ver.: always
 */
boolean emberAfScenesClusterRemoveSceneCallback(int16u groupId, 
                                                int8u sceneId);
/** @brief Remove All Scenes
 *
 *
 * @param groupId   Ver.: always
 */
boolean emberAfScenesClusterRemoveAllScenesCallback(int16u groupId);
/** @brief Store Scene
 *
 *
 * @param groupId   Ver.: always
 * @param sceneId   Ver.: always
 */
boolean emberAfScenesClusterStoreSceneCallback(int16u groupId, 
                                               int8u sceneId);
/** @brief Recall Scene
 *
 *
 * @param groupId   Ver.: always
 * @param sceneId   Ver.: always
 */
boolean emberAfScenesClusterRecallSceneCallback(int16u groupId, 
                                                int8u sceneId);
/** @brief Get Scene Membership
 *
 *
 * @param groupId   Ver.: always
 */
boolean emberAfScenesClusterGetSceneMembershipCallback(int16u groupId);
/** @brief Add Scene Response
 *
 *
 * @param status   Ver.: always
 * @param groupId   Ver.: always
 * @param sceneId   Ver.: always
 */
boolean emberAfScenesClusterAddSceneResponseCallback(int8u status, 
                                                     int16u groupId, 
                                                     int8u sceneId);
/** @brief View Scene Response
 *
 *
 * @param status   Ver.: always
 * @param groupId   Ver.: always
 * @param sceneId   Ver.: always
 * @param transitionTime   Ver.: always
 * @param sceneName   Ver.: always
 * @param extensionFieldSets   Ver.: always
 */
boolean emberAfScenesClusterViewSceneResponseCallback(int8u status, 
                                                      int16u groupId, 
                                                      int8u sceneId, 
                                                      int16u transitionTime, 
                                                      int8u* sceneName, 
                                                      int8u* extensionFieldSets);
/** @brief Remove Scene Response
 *
 *
 * @param status   Ver.: always
 * @param groupId   Ver.: always
 * @param sceneId   Ver.: always
 */
boolean emberAfScenesClusterRemoveSceneResponseCallback(int8u status, 
                                                        int16u groupId, 
                                                        int8u sceneId);
/** @brief Remove All Scenes Response
 *
 *
 * @param status   Ver.: always
 * @param groupId   Ver.: always
 */
boolean emberAfScenesClusterRemoveAllScenesResponseCallback(int8u status, 
                                                            int16u groupId);
/** @brief Store Scene Response
 *
 *
 * @param status   Ver.: always
 * @param groupId   Ver.: always
 * @param sceneId   Ver.: always
 */
boolean emberAfScenesClusterStoreSceneResponseCallback(int8u status, 
                                                       int16u groupId, 
                                                       int8u sceneId);
/** @brief Get Scene Membership Response
 *
 *
 * @param status   Ver.: always
 * @param capacity   Ver.: always
 * @param groupId   Ver.: always
 * @param sceneCount   Ver.: always
 * @param sceneList   Ver.: always
 */
boolean emberAfScenesClusterGetSceneMembershipResponseCallback(int8u status, 
                                                               int8u capacity, 
                                                               int16u groupId, 
                                                               int8u sceneCount, 
                                                               int8u* sceneList);
/** @brief Server Init
 *
 * Scenes cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfScenesClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Scenes cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfScenesClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Scenes cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfScenesClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Scenes cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfScenesClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Scenes cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfScenesClusterServerAttributeChangedCallback(int8u endpoint, 
                                                        EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Scenes cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfScenesClusterClientAttributeChangedCallback(int8u endpoint, 
                                                        EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Scenes cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfScenesClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                            EmberAfAttributeId attributeId, 
                                                                            int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Scenes cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfScenesClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                            EmberAfAttributeId attributeId, 
                                                                            int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Scenes cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfScenesClusterServerDefaultResponseCallback(int8u endpoint, 
                                                       int8u commandId, 
                                                       EmberAfStatus status);
/** @brief Client Default Response
 *
 * Scenes cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfScenesClusterClientDefaultResponseCallback(int8u endpoint, 
                                                       int8u commandId, 
                                                       EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Scenes cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfScenesClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                   int16u indexOrDestination, 
                                                   EmberApsFrame * apsFrame, 
                                                   int16u msgLen, 
                                                   int8u * message, 
                                                   EmberStatus status);
/** @brief Client Message Sent
 *
 * Scenes cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfScenesClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                   int16u indexOrDestination, 
                                                   EmberApsFrame * apsFrame, 
                                                   int16u msgLen, 
                                                   int8u * message, 
                                                   EmberStatus status);

/** @} END Scenes Cluster Callbacks */

/** @name On/off Cluster Callbacks */
// @{

/** @brief Off
 *
 *
 */
boolean emberAfOnOffClusterOffCallback(void);
/** @brief On
 *
 *
 */
boolean emberAfOnOffClusterOnCallback(void);
/** @brief Toggle
 *
 *
 */
boolean emberAfOnOffClusterToggleCallback(void);
/** @brief Server Init
 *
 * On/off cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfOnOffClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * On/off cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfOnOffClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * On/off cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfOnOffClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * On/off cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfOnOffClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * On/off cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfOnOffClusterServerAttributeChangedCallback(int8u endpoint, 
                                                       EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * On/off cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfOnOffClusterClientAttributeChangedCallback(int8u endpoint, 
                                                       EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * On/off cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfOnOffClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                           EmberAfAttributeId attributeId, 
                                                                           int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * On/off cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfOnOffClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                           EmberAfAttributeId attributeId, 
                                                                           int16u manufacturerCode);
/** @brief Server Default Response
 *
 * On/off cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfOnOffClusterServerDefaultResponseCallback(int8u endpoint, 
                                                      int8u commandId, 
                                                      EmberAfStatus status);
/** @brief Client Default Response
 *
 * On/off cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfOnOffClusterClientDefaultResponseCallback(int8u endpoint, 
                                                      int8u commandId, 
                                                      EmberAfStatus status);
/** @brief Server Message Sent
 *
 * On/off cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfOnOffClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                  int16u indexOrDestination, 
                                                  EmberApsFrame * apsFrame, 
                                                  int16u msgLen, 
                                                  int8u * message, 
                                                  EmberStatus status);
/** @brief Client Message Sent
 *
 * On/off cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfOnOffClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                  int16u indexOrDestination, 
                                                  EmberApsFrame * apsFrame, 
                                                  int16u msgLen, 
                                                  int8u * message, 
                                                  EmberStatus status);
/** @brief Sample Mfg Specific Off With Transition
 *
 *
 */
boolean emberAfOnOffClusterSampleMfgSpecificOffWithTransitionCallback(void);
/** @brief Sample Mfg Specific On With Transition
 *
 *
 */
boolean emberAfOnOffClusterSampleMfgSpecificOnWithTransitionCallback(void);
/** @brief Sample Mfg Specific Toggle With Transition
 *
 *
 */
boolean emberAfOnOffClusterSampleMfgSpecificToggleWithTransitionCallback(void);

/** @} END On/off Cluster Callbacks */

/** @name On/off Switch Configuration Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * On/off Switch Configuration cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfOnOffSwitchConfigClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * On/off Switch Configuration cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfOnOffSwitchConfigClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * On/off Switch Configuration cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfOnOffSwitchConfigClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * On/off Switch Configuration cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfOnOffSwitchConfigClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * On/off Switch Configuration cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfOnOffSwitchConfigClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                   EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * On/off Switch Configuration cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfOnOffSwitchConfigClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                   EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * On/off Switch Configuration cluster, Server Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfOnOffSwitchConfigClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                       EmberAfAttributeId attributeId, 
                                                                                       int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * On/off Switch Configuration cluster, Client Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfOnOffSwitchConfigClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                       EmberAfAttributeId attributeId, 
                                                                                       int16u manufacturerCode);
/** @brief Server Default Response
 *
 * On/off Switch Configuration cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfOnOffSwitchConfigClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                  int8u commandId, 
                                                                  EmberAfStatus status);
/** @brief Client Default Response
 *
 * On/off Switch Configuration cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfOnOffSwitchConfigClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                  int8u commandId, 
                                                                  EmberAfStatus status);
/** @brief Server Message Sent
 *
 * On/off Switch Configuration cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfOnOffSwitchConfigClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                              int16u indexOrDestination, 
                                                              EmberApsFrame * apsFrame, 
                                                              int16u msgLen, 
                                                              int8u * message, 
                                                              EmberStatus status);
/** @brief Client Message Sent
 *
 * On/off Switch Configuration cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfOnOffSwitchConfigClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                              int16u indexOrDestination, 
                                                              EmberApsFrame * apsFrame, 
                                                              int16u msgLen, 
                                                              int8u * message, 
                                                              EmberStatus status);

/** @} END On/off Switch Configuration Cluster Callbacks */

/** @name Level Control Cluster Callbacks */
// @{

/** @brief Move To Level
 *
 *
 * @param level   Ver.: always
 * @param transitionTime   Ver.: always
 */
boolean emberAfLevelControlClusterMoveToLevelCallback(int8u level, 
                                                      int16u transitionTime);
/** @brief Move
 *
 *
 * @param moveMode   Ver.: always
 * @param rate   Ver.: always
 */
boolean emberAfLevelControlClusterMoveCallback(int8u moveMode, 
                                               int8u rate);
/** @brief Step
 *
 *
 * @param stepMode   Ver.: always
 * @param stepSize   Ver.: always
 * @param transitionTime   Ver.: always
 */
boolean emberAfLevelControlClusterStepCallback(int8u stepMode, 
                                               int8u stepSize, 
                                               int16u transitionTime);
/** @brief Stop
 *
 *
 */
boolean emberAfLevelControlClusterStopCallback(void);
/** @brief Move To Level With On Off
 *
 *
 * @param level   Ver.: always
 * @param transitionTime   Ver.: always
 */
boolean emberAfLevelControlClusterMoveToLevelWithOnOffCallback(int8u level, 
                                                               int16u transitionTime);
/** @brief Move With On Off
 *
 *
 * @param moveMode   Ver.: always
 * @param rate   Ver.: always
 */
boolean emberAfLevelControlClusterMoveWithOnOffCallback(int8u moveMode, 
                                                        int8u rate);
/** @brief Step With On Off
 *
 *
 * @param stepMode   Ver.: always
 * @param stepSize   Ver.: always
 * @param transitionTime   Ver.: always
 */
boolean emberAfLevelControlClusterStepWithOnOffCallback(int8u stepMode, 
                                                        int8u stepSize, 
                                                        int16u transitionTime);
/** @brief Stop With On Off
 *
 *
 */
boolean emberAfLevelControlClusterStopWithOnOffCallback(void);
/** @brief Server Init
 *
 * Level Control cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfLevelControlClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Level Control cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfLevelControlClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Level Control cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfLevelControlClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Level Control cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfLevelControlClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Level Control cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfLevelControlClusterServerAttributeChangedCallback(int8u endpoint, 
                                                              EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Level Control cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfLevelControlClusterClientAttributeChangedCallback(int8u endpoint, 
                                                              EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Level Control cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfLevelControlClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                  EmberAfAttributeId attributeId, 
                                                                                  int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Level Control cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfLevelControlClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                  EmberAfAttributeId attributeId, 
                                                                                  int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Level Control cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfLevelControlClusterServerDefaultResponseCallback(int8u endpoint, 
                                                             int8u commandId, 
                                                             EmberAfStatus status);
/** @brief Client Default Response
 *
 * Level Control cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfLevelControlClusterClientDefaultResponseCallback(int8u endpoint, 
                                                             int8u commandId, 
                                                             EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Level Control cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfLevelControlClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                         int16u indexOrDestination, 
                                                         EmberApsFrame * apsFrame, 
                                                         int16u msgLen, 
                                                         int8u * message, 
                                                         EmberStatus status);
/** @brief Client Message Sent
 *
 * Level Control cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfLevelControlClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                         int16u indexOrDestination, 
                                                         EmberApsFrame * apsFrame, 
                                                         int16u msgLen, 
                                                         int8u * message, 
                                                         EmberStatus status);

/** @} END Level Control Cluster Callbacks */

/** @name Alarms Cluster Callbacks */
// @{

/** @brief Reset Alarm
 *
 *
 * @param alarmCode   Ver.: always
 * @param clusterId   Ver.: always
 */
boolean emberAfAlarmClusterResetAlarmCallback(int8u alarmCode, 
                                              int16u clusterId);
/** @brief Reset All Alarms
 *
 *
 */
boolean emberAfAlarmClusterResetAllAlarmsCallback(void);
/** @brief Get Alarm
 *
 *
 */
boolean emberAfAlarmClusterGetAlarmCallback(void);
/** @brief Reset Alarm Log
 *
 *
 */
boolean emberAfAlarmClusterResetAlarmLogCallback(void);
/** @brief Alarm
 *
 *
 * @param alarmCode   Ver.: always
 * @param clusterId   Ver.: always
 */
boolean emberAfAlarmClusterAlarmCallback(int8u alarmCode, 
                                         int16u clusterId);
/** @brief Get Alarm Response
 *
 *
 * @param status   Ver.: always
 * @param alarmCode   Ver.: always
 * @param clusterId   Ver.: always
 * @param timeStamp   Ver.: always
 */
boolean emberAfAlarmClusterGetAlarmResponseCallback(int8u status, 
                                                    int8u alarmCode, 
                                                    int16u clusterId, 
                                                    int32u timeStamp);
/** @brief Server Init
 *
 * Alarms cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfAlarmClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Alarms cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfAlarmClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Alarms cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfAlarmClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Alarms cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfAlarmClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Alarms cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfAlarmClusterServerAttributeChangedCallback(int8u endpoint, 
                                                       EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Alarms cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfAlarmClusterClientAttributeChangedCallback(int8u endpoint, 
                                                       EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Alarms cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfAlarmClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                           EmberAfAttributeId attributeId, 
                                                                           int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Alarms cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfAlarmClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                           EmberAfAttributeId attributeId, 
                                                                           int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Alarms cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfAlarmClusterServerDefaultResponseCallback(int8u endpoint, 
                                                      int8u commandId, 
                                                      EmberAfStatus status);
/** @brief Client Default Response
 *
 * Alarms cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfAlarmClusterClientDefaultResponseCallback(int8u endpoint, 
                                                      int8u commandId, 
                                                      EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Alarms cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfAlarmClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                  int16u indexOrDestination, 
                                                  EmberApsFrame * apsFrame, 
                                                  int16u msgLen, 
                                                  int8u * message, 
                                                  EmberStatus status);
/** @brief Client Message Sent
 *
 * Alarms cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfAlarmClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                  int16u indexOrDestination, 
                                                  EmberApsFrame * apsFrame, 
                                                  int16u msgLen, 
                                                  int8u * message, 
                                                  EmberStatus status);

/** @} END Alarms Cluster Callbacks */

/** @name Time Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Time cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfTimeClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Time cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfTimeClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Time cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfTimeClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Time cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfTimeClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Time cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfTimeClusterServerAttributeChangedCallback(int8u endpoint, 
                                                      EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Time cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfTimeClusterClientAttributeChangedCallback(int8u endpoint, 
                                                      EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Time cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfTimeClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                          EmberAfAttributeId attributeId, 
                                                                          int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Time cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfTimeClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                          EmberAfAttributeId attributeId, 
                                                                          int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Time cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfTimeClusterServerDefaultResponseCallback(int8u endpoint, 
                                                     int8u commandId, 
                                                     EmberAfStatus status);
/** @brief Client Default Response
 *
 * Time cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfTimeClusterClientDefaultResponseCallback(int8u endpoint, 
                                                     int8u commandId, 
                                                     EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Time cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfTimeClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                 int16u indexOrDestination, 
                                                 EmberApsFrame * apsFrame, 
                                                 int16u msgLen, 
                                                 int8u * message, 
                                                 EmberStatus status);
/** @brief Client Message Sent
 *
 * Time cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfTimeClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                 int16u indexOrDestination, 
                                                 EmberApsFrame * apsFrame, 
                                                 int16u msgLen, 
                                                 int8u * message, 
                                                 EmberStatus status);

/** @} END Time Cluster Callbacks */

/** @name RSSI Location Cluster Callbacks */
// @{

/** @brief Set Absolute Location
 *
 *
 * @param coordinate1   Ver.: always
 * @param coordinate2   Ver.: always
 * @param coordinate3   Ver.: always
 * @param power   Ver.: always
 * @param pathLossExponent   Ver.: always
 */
boolean emberAfRssiLocationClusterSetAbsoluteLocationCallback(int16s coordinate1, 
                                                              int16s coordinate2, 
                                                              int16s coordinate3, 
                                                              int16s power, 
                                                              int16u pathLossExponent);
/** @brief Set Device Configuration
 *
 *
 * @param power   Ver.: always
 * @param pathLossExponent   Ver.: always
 * @param calculationPeriod   Ver.: always
 * @param numberRssiMeasurements   Ver.: always
 * @param reportingPeriod   Ver.: always
 */
boolean emberAfRssiLocationClusterSetDeviceConfigurationCallback(int16s power, 
                                                                 int16u pathLossExponent, 
                                                                 int16u calculationPeriod, 
                                                                 int8u numberRssiMeasurements, 
                                                                 int16u reportingPeriod);
/** @brief Get Device Configuration
 *
 *
 * @param targetAddress   Ver.: always
 */
boolean emberAfRssiLocationClusterGetDeviceConfigurationCallback(int8u* targetAddress);
/** @brief Get Location Data
 *
 *
 * @param flags   Ver.: always
 * @param numberResponses   Ver.: always
 * @param targetAddress   Ver.: always
 */
boolean emberAfRssiLocationClusterGetLocationDataCallback(int8u flags, 
                                                          int8u numberResponses, 
                                                          int8u* targetAddress);
/** @brief Rssi Response
 *
 *
 * @param replyingDevice   Ver.: always
 * @param coordinate1   Ver.: always
 * @param coordinate2   Ver.: always
 * @param coordinate3   Ver.: always
 * @param rssi   Ver.: always
 * @param numberRssiMeasurements   Ver.: always
 */
boolean emberAfRssiLocationClusterRssiResponseCallback(int8u* replyingDevice, 
                                                       int16s coordinate1, 
                                                       int16s coordinate2, 
                                                       int16s coordinate3, 
                                                       int8s rssi, 
                                                       int8u numberRssiMeasurements);
/** @brief Send Pings
 *
 *
 * @param targetAddress   Ver.: always
 * @param numberRssiMeasurements   Ver.: always
 * @param calculationPeriod   Ver.: always
 */
boolean emberAfRssiLocationClusterSendPingsCallback(int8u* targetAddress, 
                                                    int8u numberRssiMeasurements, 
                                                    int16u calculationPeriod);
/** @brief Anchor Node Announce
 *
 *
 * @param anchorNodeIeeeAddress   Ver.: always
 * @param coordinate1   Ver.: always
 * @param coordinate2   Ver.: always
 * @param coordinate3   Ver.: always
 */
boolean emberAfRssiLocationClusterAnchorNodeAnnounceCallback(int8u* anchorNodeIeeeAddress, 
                                                             int16s coordinate1, 
                                                             int16s coordinate2, 
                                                             int16s coordinate3);
/** @brief Device Configuration Response
 *
 *
 * @param status   Ver.: always
 * @param power   Ver.: always
 * @param pathLossExponent   Ver.: always
 * @param calculationPeriod   Ver.: always
 * @param numberRssiMeasurements   Ver.: always
 * @param reportingPeriod   Ver.: always
 */
boolean emberAfRssiLocationClusterDeviceConfigurationResponseCallback(int8u status, 
                                                                      int16s power, 
                                                                      int16u pathLossExponent, 
                                                                      int16u calculationPeriod, 
                                                                      int8u numberRssiMeasurements, 
                                                                      int16u reportingPeriod);
/** @brief Location Data Response
 *
 *
 * @param status   Ver.: always
 * @param locationType   Ver.: always
 * @param coordinate1   Ver.: always
 * @param coordinate2   Ver.: always
 * @param coordinate3   Ver.: always
 * @param power   Ver.: always
 * @param pathLossExponent   Ver.: always
 * @param locationMethod   Ver.: always
 * @param qualityMeasure   Ver.: always
 * @param locationAge   Ver.: always
 */
boolean emberAfRssiLocationClusterLocationDataResponseCallback(int8u status, 
                                                               int8u locationType, 
                                                               int16s coordinate1, 
                                                               int16s coordinate2, 
                                                               int16s coordinate3, 
                                                               int16s power, 
                                                               int16u pathLossExponent, 
                                                               int8u locationMethod, 
                                                               int8u qualityMeasure, 
                                                               int16u locationAge);
/** @brief Location Data Notification
 *
 *
 * @param locationType   Ver.: always
 * @param coordinate1   Ver.: always
 * @param coordinate2   Ver.: always
 * @param coordinate3   Ver.: always
 * @param power   Ver.: always
 * @param pathLossExponent   Ver.: always
 * @param locationMethod   Ver.: always
 * @param qualityMeasure   Ver.: always
 * @param locationAge   Ver.: always
 */
boolean emberAfRssiLocationClusterLocationDataNotificationCallback(int8u locationType, 
                                                                   int16s coordinate1, 
                                                                   int16s coordinate2, 
                                                                   int16s coordinate3, 
                                                                   int16s power, 
                                                                   int16u pathLossExponent, 
                                                                   int8u locationMethod, 
                                                                   int8u qualityMeasure, 
                                                                   int16u locationAge);
/** @brief Compact Location Data Notification
 *
 *
 * @param locationType   Ver.: always
 * @param coordinate1   Ver.: always
 * @param coordinate2   Ver.: always
 * @param coordinate3   Ver.: always
 * @param qualityMeasure   Ver.: always
 * @param locationAge   Ver.: always
 */
boolean emberAfRssiLocationClusterCompactLocationDataNotificationCallback(int8u locationType, 
                                                                          int16s coordinate1, 
                                                                          int16s coordinate2, 
                                                                          int16s coordinate3, 
                                                                          int8u qualityMeasure, 
                                                                          int16u locationAge);
/** @brief Rssi Ping
 *
 *
 * @param locationType   Ver.: always
 */
boolean emberAfRssiLocationClusterRssiPingCallback(int8u locationType);
/** @brief Rssi Request
 *
 *
 */
boolean emberAfRssiLocationClusterRssiRequestCallback(void);
/** @brief Report Rssi Measurements
 *
 *
 * @param measuringDevice   Ver.: always
 * @param neighbors   Ver.: always
 * @param neighborsInfo   Ver.: always
 */
boolean emberAfRssiLocationClusterReportRssiMeasurementsCallback(int8u* measuringDevice, 
                                                                 int8u neighbors, 
                                                                 int8u* neighborsInfo);
/** @brief Request Own Location
 *
 *
 * @param blindNode   Ver.: always
 */
boolean emberAfRssiLocationClusterRequestOwnLocationCallback(int8u* blindNode);
/** @brief Server Init
 *
 * RSSI Location cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfRssiLocationClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * RSSI Location cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfRssiLocationClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * RSSI Location cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfRssiLocationClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * RSSI Location cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfRssiLocationClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * RSSI Location cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfRssiLocationClusterServerAttributeChangedCallback(int8u endpoint, 
                                                              EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * RSSI Location cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfRssiLocationClusterClientAttributeChangedCallback(int8u endpoint, 
                                                              EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * RSSI Location cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfRssiLocationClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                  EmberAfAttributeId attributeId, 
                                                                                  int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * RSSI Location cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfRssiLocationClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                  EmberAfAttributeId attributeId, 
                                                                                  int16u manufacturerCode);
/** @brief Server Default Response
 *
 * RSSI Location cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfRssiLocationClusterServerDefaultResponseCallback(int8u endpoint, 
                                                             int8u commandId, 
                                                             EmberAfStatus status);
/** @brief Client Default Response
 *
 * RSSI Location cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfRssiLocationClusterClientDefaultResponseCallback(int8u endpoint, 
                                                             int8u commandId, 
                                                             EmberAfStatus status);
/** @brief Server Message Sent
 *
 * RSSI Location cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfRssiLocationClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                         int16u indexOrDestination, 
                                                         EmberApsFrame * apsFrame, 
                                                         int16u msgLen, 
                                                         int8u * message, 
                                                         EmberStatus status);
/** @brief Client Message Sent
 *
 * RSSI Location cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfRssiLocationClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                         int16u indexOrDestination, 
                                                         EmberApsFrame * apsFrame, 
                                                         int16u msgLen, 
                                                         int8u * message, 
                                                         EmberStatus status);

/** @} END RSSI Location Cluster Callbacks */

/** @name Binary Input (Basic) Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Binary Input (Basic) cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfBinaryInputBasicClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Binary Input (Basic) cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfBinaryInputBasicClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Binary Input (Basic) cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfBinaryInputBasicClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Binary Input (Basic) cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfBinaryInputBasicClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Binary Input (Basic) cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfBinaryInputBasicClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                  EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Binary Input (Basic) cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfBinaryInputBasicClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                  EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Binary Input (Basic) cluster, Server Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfBinaryInputBasicClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                      EmberAfAttributeId attributeId, 
                                                                                      int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Binary Input (Basic) cluster, Client Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfBinaryInputBasicClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                      EmberAfAttributeId attributeId, 
                                                                                      int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Binary Input (Basic) cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfBinaryInputBasicClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                 int8u commandId, 
                                                                 EmberAfStatus status);
/** @brief Client Default Response
 *
 * Binary Input (Basic) cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfBinaryInputBasicClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                 int8u commandId, 
                                                                 EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Binary Input (Basic) cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfBinaryInputBasicClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                             int16u indexOrDestination, 
                                                             EmberApsFrame * apsFrame, 
                                                             int16u msgLen, 
                                                             int8u * message, 
                                                             EmberStatus status);
/** @brief Client Message Sent
 *
 * Binary Input (Basic) cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfBinaryInputBasicClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                             int16u indexOrDestination, 
                                                             EmberApsFrame * apsFrame, 
                                                             int16u msgLen, 
                                                             int8u * message, 
                                                             EmberStatus status);

/** @} END Binary Input (Basic) Cluster Callbacks */

/** @name Commissioning Cluster Callbacks */
// @{

/** @brief Restart Device
 *
 *
 * @param options   Ver.: always
 * @param delay   Ver.: always
 * @param jitter   Ver.: always
 */
boolean emberAfCommissioningClusterRestartDeviceCallback(int8u options, 
                                                         int8u delay, 
                                                         int8u jitter);
/** @brief Save Startup Parameters
 *
 *
 * @param options   Ver.: always
 * @param index   Ver.: always
 */
boolean emberAfCommissioningClusterSaveStartupParametersCallback(int8u options, 
                                                                 int8u index);
/** @brief Restore Startup Parameters
 *
 *
 * @param options   Ver.: always
 * @param index   Ver.: always
 */
boolean emberAfCommissioningClusterRestoreStartupParametersCallback(int8u options, 
                                                                    int8u index);
/** @brief Reset Startup Parameters
 *
 *
 * @param options   Ver.: always
 * @param index   Ver.: always
 */
boolean emberAfCommissioningClusterResetStartupParametersCallback(int8u options, 
                                                                  int8u index);
/** @brief Restart Device Response
 *
 *
 * @param status   Ver.: always
 */
boolean emberAfCommissioningClusterRestartDeviceResponseCallback(int8u status);
/** @brief Save Startup Parameters Response
 *
 *
 * @param status   Ver.: always
 */
boolean emberAfCommissioningClusterSaveStartupParametersResponseCallback(int8u status);
/** @brief Restore Startup Parameters Response
 *
 *
 * @param status   Ver.: always
 */
boolean emberAfCommissioningClusterRestoreStartupParametersResponseCallback(int8u status);
/** @brief Reset Startup Parameters Response
 *
 *
 * @param status   Ver.: always
 */
boolean emberAfCommissioningClusterResetStartupParametersResponseCallback(int8u status);
/** @brief Server Init
 *
 * Commissioning cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfCommissioningClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Commissioning cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfCommissioningClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Commissioning cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfCommissioningClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Commissioning cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfCommissioningClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Commissioning cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfCommissioningClusterServerAttributeChangedCallback(int8u endpoint, 
                                                               EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Commissioning cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfCommissioningClusterClientAttributeChangedCallback(int8u endpoint, 
                                                               EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Commissioning cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfCommissioningClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                   EmberAfAttributeId attributeId, 
                                                                                   int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Commissioning cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfCommissioningClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                   EmberAfAttributeId attributeId, 
                                                                                   int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Commissioning cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfCommissioningClusterServerDefaultResponseCallback(int8u endpoint, 
                                                              int8u commandId, 
                                                              EmberAfStatus status);
/** @brief Client Default Response
 *
 * Commissioning cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfCommissioningClusterClientDefaultResponseCallback(int8u endpoint, 
                                                              int8u commandId, 
                                                              EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Commissioning cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfCommissioningClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                          int16u indexOrDestination, 
                                                          EmberApsFrame * apsFrame, 
                                                          int16u msgLen, 
                                                          int8u * message, 
                                                          EmberStatus status);
/** @brief Client Message Sent
 *
 * Commissioning cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfCommissioningClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                          int16u indexOrDestination, 
                                                          EmberApsFrame * apsFrame, 
                                                          int16u msgLen, 
                                                          int8u * message, 
                                                          EmberStatus status);

/** @} END Commissioning Cluster Callbacks */

/** @name Shade Configuration Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Shade Configuration cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfShadeConfigClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Shade Configuration cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfShadeConfigClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Shade Configuration cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfShadeConfigClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Shade Configuration cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfShadeConfigClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Shade Configuration cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfShadeConfigClusterServerAttributeChangedCallback(int8u endpoint, 
                                                             EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Shade Configuration cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfShadeConfigClusterClientAttributeChangedCallback(int8u endpoint, 
                                                             EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Shade Configuration cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfShadeConfigClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                 EmberAfAttributeId attributeId, 
                                                                                 int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Shade Configuration cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfShadeConfigClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                 EmberAfAttributeId attributeId, 
                                                                                 int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Shade Configuration cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfShadeConfigClusterServerDefaultResponseCallback(int8u endpoint, 
                                                            int8u commandId, 
                                                            EmberAfStatus status);
/** @brief Client Default Response
 *
 * Shade Configuration cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfShadeConfigClusterClientDefaultResponseCallback(int8u endpoint, 
                                                            int8u commandId, 
                                                            EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Shade Configuration cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfShadeConfigClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                        int16u indexOrDestination, 
                                                        EmberApsFrame * apsFrame, 
                                                        int16u msgLen, 
                                                        int8u * message, 
                                                        EmberStatus status);
/** @brief Client Message Sent
 *
 * Shade Configuration cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfShadeConfigClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                        int16u indexOrDestination, 
                                                        EmberApsFrame * apsFrame, 
                                                        int16u msgLen, 
                                                        int8u * message, 
                                                        EmberStatus status);

/** @} END Shade Configuration Cluster Callbacks */

/** @name Pump Configuration and Control Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Pump Configuration and Control cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPumpConfigControlClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Pump Configuration and Control cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPumpConfigControlClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Pump Configuration and Control cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfPumpConfigControlClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Pump Configuration and Control cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfPumpConfigControlClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Pump Configuration and Control cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfPumpConfigControlClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                   EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Pump Configuration and Control cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfPumpConfigControlClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                   EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Pump Configuration and Control cluster, Server Manufacturer Specific
 * Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfPumpConfigControlClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                       EmberAfAttributeId attributeId, 
                                                                                       int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Pump Configuration and Control cluster, Client Manufacturer Specific
 * Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfPumpConfigControlClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                       EmberAfAttributeId attributeId, 
                                                                                       int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Pump Configuration and Control cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfPumpConfigControlClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                  int8u commandId, 
                                                                  EmberAfStatus status);
/** @brief Client Default Response
 *
 * Pump Configuration and Control cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfPumpConfigControlClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                  int8u commandId, 
                                                                  EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Pump Configuration and Control cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfPumpConfigControlClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                              int16u indexOrDestination, 
                                                              EmberApsFrame * apsFrame, 
                                                              int16u msgLen, 
                                                              int8u * message, 
                                                              EmberStatus status);
/** @brief Client Message Sent
 *
 * Pump Configuration and Control cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfPumpConfigControlClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                              int16u indexOrDestination, 
                                                              EmberApsFrame * apsFrame, 
                                                              int16u msgLen, 
                                                              int8u * message, 
                                                              EmberStatus status);

/** @} END Pump Configuration and Control Cluster Callbacks */

/** @name Thermostat Cluster Callbacks */
// @{

/** @brief Setpoint Raise Lower
 *
 *
 * @param mode   Ver.: always
 * @param amount   Ver.: always
 */
boolean emberAfThermostatClusterSetpointRaiseLowerCallback(int8u mode, 
                                                           int8s amount);
/** @brief Server Init
 *
 * Thermostat cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfThermostatClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Thermostat cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfThermostatClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Thermostat cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfThermostatClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Thermostat cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfThermostatClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Thermostat cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfThermostatClusterServerAttributeChangedCallback(int8u endpoint, 
                                                            EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Thermostat cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfThermostatClusterClientAttributeChangedCallback(int8u endpoint, 
                                                            EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Thermostat cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfThermostatClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                EmberAfAttributeId attributeId, 
                                                                                int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Thermostat cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfThermostatClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                EmberAfAttributeId attributeId, 
                                                                                int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Thermostat cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfThermostatClusterServerDefaultResponseCallback(int8u endpoint, 
                                                           int8u commandId, 
                                                           EmberAfStatus status);
/** @brief Client Default Response
 *
 * Thermostat cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfThermostatClusterClientDefaultResponseCallback(int8u endpoint, 
                                                           int8u commandId, 
                                                           EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Thermostat cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfThermostatClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                       int16u indexOrDestination, 
                                                       EmberApsFrame * apsFrame, 
                                                       int16u msgLen, 
                                                       int8u * message, 
                                                       EmberStatus status);
/** @brief Client Message Sent
 *
 * Thermostat cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfThermostatClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                       int16u indexOrDestination, 
                                                       EmberApsFrame * apsFrame, 
                                                       int16u msgLen, 
                                                       int8u * message, 
                                                       EmberStatus status);

/** @} END Thermostat Cluster Callbacks */

/** @name Fan Control Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Fan Control cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfFanControlClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Fan Control cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfFanControlClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Fan Control cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfFanControlClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Fan Control cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfFanControlClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Fan Control cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfFanControlClusterServerAttributeChangedCallback(int8u endpoint, 
                                                            EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Fan Control cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfFanControlClusterClientAttributeChangedCallback(int8u endpoint, 
                                                            EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Fan Control cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfFanControlClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                EmberAfAttributeId attributeId, 
                                                                                int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Fan Control cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfFanControlClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                EmberAfAttributeId attributeId, 
                                                                                int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Fan Control cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfFanControlClusterServerDefaultResponseCallback(int8u endpoint, 
                                                           int8u commandId, 
                                                           EmberAfStatus status);
/** @brief Client Default Response
 *
 * Fan Control cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfFanControlClusterClientDefaultResponseCallback(int8u endpoint, 
                                                           int8u commandId, 
                                                           EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Fan Control cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfFanControlClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                       int16u indexOrDestination, 
                                                       EmberApsFrame * apsFrame, 
                                                       int16u msgLen, 
                                                       int8u * message, 
                                                       EmberStatus status);
/** @brief Client Message Sent
 *
 * Fan Control cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfFanControlClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                       int16u indexOrDestination, 
                                                       EmberApsFrame * apsFrame, 
                                                       int16u msgLen, 
                                                       int8u * message, 
                                                       EmberStatus status);

/** @} END Fan Control Cluster Callbacks */

/** @name Dehumidification Control Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Dehumidification Control cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfDehumidControlClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Dehumidification Control cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfDehumidControlClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Dehumidification Control cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfDehumidControlClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Dehumidification Control cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfDehumidControlClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Dehumidification Control cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfDehumidControlClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Dehumidification Control cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfDehumidControlClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Dehumidification Control cluster, Server Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfDehumidControlClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                    EmberAfAttributeId attributeId, 
                                                                                    int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Dehumidification Control cluster, Client Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfDehumidControlClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                    EmberAfAttributeId attributeId, 
                                                                                    int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Dehumidification Control cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfDehumidControlClusterServerDefaultResponseCallback(int8u endpoint, 
                                                               int8u commandId, 
                                                               EmberAfStatus status);
/** @brief Client Default Response
 *
 * Dehumidification Control cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfDehumidControlClusterClientDefaultResponseCallback(int8u endpoint, 
                                                               int8u commandId, 
                                                               EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Dehumidification Control cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfDehumidControlClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                           int16u indexOrDestination, 
                                                           EmberApsFrame * apsFrame, 
                                                           int16u msgLen, 
                                                           int8u * message, 
                                                           EmberStatus status);
/** @brief Client Message Sent
 *
 * Dehumidification Control cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfDehumidControlClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                           int16u indexOrDestination, 
                                                           EmberApsFrame * apsFrame, 
                                                           int16u msgLen, 
                                                           int8u * message, 
                                                           EmberStatus status);

/** @} END Dehumidification Control Cluster Callbacks */

/** @name Thermostat User Interface Configuration Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Thermostat User Interface Configuration cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfThermostatUiConfigClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Thermostat User Interface Configuration cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfThermostatUiConfigClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Thermostat User Interface Configuration cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfThermostatUiConfigClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Thermostat User Interface Configuration cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfThermostatUiConfigClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Thermostat User Interface Configuration cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfThermostatUiConfigClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                    EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Thermostat User Interface Configuration cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfThermostatUiConfigClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                    EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Thermostat User Interface Configuration cluster, Server Manufacturer
 * Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfThermostatUiConfigClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                        EmberAfAttributeId attributeId, 
                                                                                        int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Thermostat User Interface Configuration cluster, Client Manufacturer
 * Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfThermostatUiConfigClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                        EmberAfAttributeId attributeId, 
                                                                                        int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Thermostat User Interface Configuration cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfThermostatUiConfigClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                   int8u commandId, 
                                                                   EmberAfStatus status);
/** @brief Client Default Response
 *
 * Thermostat User Interface Configuration cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfThermostatUiConfigClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                   int8u commandId, 
                                                                   EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Thermostat User Interface Configuration cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfThermostatUiConfigClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                               int16u indexOrDestination, 
                                                               EmberApsFrame * apsFrame, 
                                                               int16u msgLen, 
                                                               int8u * message, 
                                                               EmberStatus status);
/** @brief Client Message Sent
 *
 * Thermostat User Interface Configuration cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfThermostatUiConfigClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                               int16u indexOrDestination, 
                                                               EmberApsFrame * apsFrame, 
                                                               int16u msgLen, 
                                                               int8u * message, 
                                                               EmberStatus status);

/** @} END Thermostat User Interface Configuration Cluster Callbacks */

/** @name Color Control Cluster Callbacks */
// @{

/** @brief Move To Hue
 *
 *
 * @param hue   Ver.: always
 * @param direction   Ver.: always
 * @param transitionTime   Ver.: always
 */
boolean emberAfColorControlClusterMoveToHueCallback(int8u hue, 
                                                    int8u direction, 
                                                    int16u transitionTime);
/** @brief Move Hue
 *
 *
 * @param moveMode   Ver.: always
 * @param rate   Ver.: always
 */
boolean emberAfColorControlClusterMoveHueCallback(int8u moveMode, 
                                                  int8u rate);
/** @brief Step Hue
 *
 *
 * @param stepMode   Ver.: always
 * @param stepSize   Ver.: always
 * @param transitionTime   Ver.: always
 */
boolean emberAfColorControlClusterStepHueCallback(int8u stepMode, 
                                                  int8u stepSize, 
                                                  int8u transitionTime);
/** @brief Move To Saturation
 *
 *
 * @param saturation   Ver.: always
 * @param transitionTime   Ver.: always
 */
boolean emberAfColorControlClusterMoveToSaturationCallback(int8u saturation, 
                                                           int16u transitionTime);
/** @brief Move Saturation
 *
 *
 * @param moveMode   Ver.: always
 * @param rate   Ver.: always
 */
boolean emberAfColorControlClusterMoveSaturationCallback(int8u moveMode, 
                                                         int8u rate);
/** @brief Step Saturation
 *
 *
 * @param stepMode   Ver.: always
 * @param stepSize   Ver.: always
 * @param transitionTime   Ver.: always
 */
boolean emberAfColorControlClusterStepSaturationCallback(int8u stepMode, 
                                                         int8u stepSize, 
                                                         int8u transitionTime);
/** @brief Move To Hue And Saturation
 *
 *
 * @param hue   Ver.: always
 * @param saturation   Ver.: always
 * @param transitionTime   Ver.: always
 */
boolean emberAfColorControlClusterMoveToHueAndSaturationCallback(int8u hue, 
                                                                 int8u saturation, 
                                                                 int16u transitionTime);
/** @brief Move To Color
 *
 *
 * @param colorX   Ver.: always
 * @param colorY   Ver.: always
 * @param transitionTime   Ver.: always
 */
boolean emberAfColorControlClusterMoveToColorCallback(int16u colorX, 
                                                      int16u colorY, 
                                                      int16u transitionTime);
/** @brief Move Color
 *
 *
 * @param rateX   Ver.: always
 * @param rateY   Ver.: always
 */
boolean emberAfColorControlClusterMoveColorCallback(int16s rateX, 
                                                    int16s rateY);
/** @brief Step Color
 *
 *
 * @param stepX   Ver.: always
 * @param stepY   Ver.: always
 * @param transitionTime   Ver.: always
 */
boolean emberAfColorControlClusterStepColorCallback(int16s stepX, 
                                                    int16s stepY, 
                                                    int16u transitionTime);
/** @brief Move To Color Temperature
 *
 *
 * @param colorTemperature   Ver.: always
 * @param transitionTime   Ver.: always
 */
boolean emberAfColorControlClusterMoveToColorTemperatureCallback(int16u colorTemperature, 
                                                                 int16u transitionTime);
/** @brief Server Init
 *
 * Color Control cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfColorControlClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Color Control cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfColorControlClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Color Control cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfColorControlClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Color Control cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfColorControlClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Color Control cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfColorControlClusterServerAttributeChangedCallback(int8u endpoint, 
                                                              EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Color Control cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfColorControlClusterClientAttributeChangedCallback(int8u endpoint, 
                                                              EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Color Control cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfColorControlClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                  EmberAfAttributeId attributeId, 
                                                                                  int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Color Control cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfColorControlClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                  EmberAfAttributeId attributeId, 
                                                                                  int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Color Control cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfColorControlClusterServerDefaultResponseCallback(int8u endpoint, 
                                                             int8u commandId, 
                                                             EmberAfStatus status);
/** @brief Client Default Response
 *
 * Color Control cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfColorControlClusterClientDefaultResponseCallback(int8u endpoint, 
                                                             int8u commandId, 
                                                             EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Color Control cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfColorControlClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                         int16u indexOrDestination, 
                                                         EmberApsFrame * apsFrame, 
                                                         int16u msgLen, 
                                                         int8u * message, 
                                                         EmberStatus status);
/** @brief Client Message Sent
 *
 * Color Control cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfColorControlClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                         int16u indexOrDestination, 
                                                         EmberApsFrame * apsFrame, 
                                                         int16u msgLen, 
                                                         int8u * message, 
                                                         EmberStatus status);

/** @} END Color Control Cluster Callbacks */

/** @name Ballast Configuration Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Ballast Configuration cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfBallastConfigurationClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Ballast Configuration cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfBallastConfigurationClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Ballast Configuration cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfBallastConfigurationClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Ballast Configuration cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfBallastConfigurationClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Ballast Configuration cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfBallastConfigurationClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                      EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Ballast Configuration cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfBallastConfigurationClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                      EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Ballast Configuration cluster, Server Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfBallastConfigurationClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                          EmberAfAttributeId attributeId, 
                                                                                          int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Ballast Configuration cluster, Client Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfBallastConfigurationClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                          EmberAfAttributeId attributeId, 
                                                                                          int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Ballast Configuration cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfBallastConfigurationClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                     int8u commandId, 
                                                                     EmberAfStatus status);
/** @brief Client Default Response
 *
 * Ballast Configuration cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfBallastConfigurationClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                     int8u commandId, 
                                                                     EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Ballast Configuration cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfBallastConfigurationClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                                 int16u indexOrDestination, 
                                                                 EmberApsFrame * apsFrame, 
                                                                 int16u msgLen, 
                                                                 int8u * message, 
                                                                 EmberStatus status);
/** @brief Client Message Sent
 *
 * Ballast Configuration cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfBallastConfigurationClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                                 int16u indexOrDestination, 
                                                                 EmberApsFrame * apsFrame, 
                                                                 int16u msgLen, 
                                                                 int8u * message, 
                                                                 EmberStatus status);

/** @} END Ballast Configuration Cluster Callbacks */

/** @name Illuminance Measurement Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Illuminance Measurement cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIllumMeasurementClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Illuminance Measurement cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIllumMeasurementClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Illuminance Measurement cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIllumMeasurementClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Illuminance Measurement cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIllumMeasurementClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Illuminance Measurement cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIllumMeasurementClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                  EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Illuminance Measurement cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIllumMeasurementClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                  EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Illuminance Measurement cluster, Server Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfIllumMeasurementClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                      EmberAfAttributeId attributeId, 
                                                                                      int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Illuminance Measurement cluster, Client Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfIllumMeasurementClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                      EmberAfAttributeId attributeId, 
                                                                                      int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Illuminance Measurement cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfIllumMeasurementClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                 int8u commandId, 
                                                                 EmberAfStatus status);
/** @brief Client Default Response
 *
 * Illuminance Measurement cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfIllumMeasurementClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                 int8u commandId, 
                                                                 EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Illuminance Measurement cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfIllumMeasurementClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                             int16u indexOrDestination, 
                                                             EmberApsFrame * apsFrame, 
                                                             int16u msgLen, 
                                                             int8u * message, 
                                                             EmberStatus status);
/** @brief Client Message Sent
 *
 * Illuminance Measurement cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfIllumMeasurementClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                             int16u indexOrDestination, 
                                                             EmberApsFrame * apsFrame, 
                                                             int16u msgLen, 
                                                             int8u * message, 
                                                             EmberStatus status);

/** @} END Illuminance Measurement Cluster Callbacks */

/** @name Illuminance Level Sensing Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Illuminance Level Sensing cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIllumLevelSensingClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Illuminance Level Sensing cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIllumLevelSensingClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Illuminance Level Sensing cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIllumLevelSensingClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Illuminance Level Sensing cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIllumLevelSensingClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Illuminance Level Sensing cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIllumLevelSensingClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                   EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Illuminance Level Sensing cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIllumLevelSensingClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                   EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Illuminance Level Sensing cluster, Server Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfIllumLevelSensingClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                       EmberAfAttributeId attributeId, 
                                                                                       int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Illuminance Level Sensing cluster, Client Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfIllumLevelSensingClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                       EmberAfAttributeId attributeId, 
                                                                                       int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Illuminance Level Sensing cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfIllumLevelSensingClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                  int8u commandId, 
                                                                  EmberAfStatus status);
/** @brief Client Default Response
 *
 * Illuminance Level Sensing cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfIllumLevelSensingClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                  int8u commandId, 
                                                                  EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Illuminance Level Sensing cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfIllumLevelSensingClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                              int16u indexOrDestination, 
                                                              EmberApsFrame * apsFrame, 
                                                              int16u msgLen, 
                                                              int8u * message, 
                                                              EmberStatus status);
/** @brief Client Message Sent
 *
 * Illuminance Level Sensing cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfIllumLevelSensingClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                              int16u indexOrDestination, 
                                                              EmberApsFrame * apsFrame, 
                                                              int16u msgLen, 
                                                              int8u * message, 
                                                              EmberStatus status);

/** @} END Illuminance Level Sensing Cluster Callbacks */

/** @name Temperature Measurement Cluster Callbacks */
// @{

/** @brief Convert Volts To Celsius
 *
 * Function that converts volts on the ADC line into celsius.
 *
 * @param voltage Voltage from ADC  Ver.: always
 */
int32s emberAfTempMeasurementClusterConvertVoltsToCelsiusCallback(int16u voltage);
/** @brief Server Init
 *
 * Temperature Measurement cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfTempMeasurementClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Temperature Measurement cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfTempMeasurementClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Temperature Measurement cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfTempMeasurementClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Temperature Measurement cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfTempMeasurementClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Temperature Measurement cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfTempMeasurementClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                 EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Temperature Measurement cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfTempMeasurementClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                 EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Temperature Measurement cluster, Server Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfTempMeasurementClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                     EmberAfAttributeId attributeId, 
                                                                                     int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Temperature Measurement cluster, Client Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfTempMeasurementClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                     EmberAfAttributeId attributeId, 
                                                                                     int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Temperature Measurement cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfTempMeasurementClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                int8u commandId, 
                                                                EmberAfStatus status);
/** @brief Client Default Response
 *
 * Temperature Measurement cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfTempMeasurementClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                int8u commandId, 
                                                                EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Temperature Measurement cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfTempMeasurementClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                            int16u indexOrDestination, 
                                                            EmberApsFrame * apsFrame, 
                                                            int16u msgLen, 
                                                            int8u * message, 
                                                            EmberStatus status);
/** @brief Client Message Sent
 *
 * Temperature Measurement cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfTempMeasurementClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                            int16u indexOrDestination, 
                                                            EmberApsFrame * apsFrame, 
                                                            int16u msgLen, 
                                                            int8u * message, 
                                                            EmberStatus status);

/** @} END Temperature Measurement Cluster Callbacks */

/** @name Pressure Measurement Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Pressure Measurement cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPressureMeasurementClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Pressure Measurement cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPressureMeasurementClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Pressure Measurement cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfPressureMeasurementClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Pressure Measurement cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfPressureMeasurementClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Pressure Measurement cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfPressureMeasurementClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                     EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Pressure Measurement cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfPressureMeasurementClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                     EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Pressure Measurement cluster, Server Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfPressureMeasurementClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                         EmberAfAttributeId attributeId, 
                                                                                         int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Pressure Measurement cluster, Client Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfPressureMeasurementClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                         EmberAfAttributeId attributeId, 
                                                                                         int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Pressure Measurement cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfPressureMeasurementClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                    int8u commandId, 
                                                                    EmberAfStatus status);
/** @brief Client Default Response
 *
 * Pressure Measurement cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfPressureMeasurementClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                    int8u commandId, 
                                                                    EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Pressure Measurement cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfPressureMeasurementClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                                int16u indexOrDestination, 
                                                                EmberApsFrame * apsFrame, 
                                                                int16u msgLen, 
                                                                int8u * message, 
                                                                EmberStatus status);
/** @brief Client Message Sent
 *
 * Pressure Measurement cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfPressureMeasurementClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                                int16u indexOrDestination, 
                                                                EmberApsFrame * apsFrame, 
                                                                int16u msgLen, 
                                                                int8u * message, 
                                                                EmberStatus status);

/** @} END Pressure Measurement Cluster Callbacks */

/** @name Flow Measurement Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Flow Measurement cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfFlowMeasurementClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Flow Measurement cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfFlowMeasurementClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Flow Measurement cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfFlowMeasurementClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Flow Measurement cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfFlowMeasurementClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Flow Measurement cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfFlowMeasurementClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                 EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Flow Measurement cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfFlowMeasurementClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                 EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Flow Measurement cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfFlowMeasurementClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                     EmberAfAttributeId attributeId, 
                                                                                     int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Flow Measurement cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfFlowMeasurementClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                     EmberAfAttributeId attributeId, 
                                                                                     int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Flow Measurement cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfFlowMeasurementClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                int8u commandId, 
                                                                EmberAfStatus status);
/** @brief Client Default Response
 *
 * Flow Measurement cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfFlowMeasurementClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                int8u commandId, 
                                                                EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Flow Measurement cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfFlowMeasurementClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                            int16u indexOrDestination, 
                                                            EmberApsFrame * apsFrame, 
                                                            int16u msgLen, 
                                                            int8u * message, 
                                                            EmberStatus status);
/** @brief Client Message Sent
 *
 * Flow Measurement cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfFlowMeasurementClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                            int16u indexOrDestination, 
                                                            EmberApsFrame * apsFrame, 
                                                            int16u msgLen, 
                                                            int8u * message, 
                                                            EmberStatus status);

/** @} END Flow Measurement Cluster Callbacks */

/** @name Relative Humidity Measurement Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Relative Humidity Measurement cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfRelativeHumidityMeasurementClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Relative Humidity Measurement cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfRelativeHumidityMeasurementClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Relative Humidity Measurement cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfRelativeHumidityMeasurementClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Relative Humidity Measurement cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfRelativeHumidityMeasurementClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Relative Humidity Measurement cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfRelativeHumidityMeasurementClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                             EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Relative Humidity Measurement cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfRelativeHumidityMeasurementClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                             EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Relative Humidity Measurement cluster, Server Manufacturer Specific
 * Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfRelativeHumidityMeasurementClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                                 EmberAfAttributeId attributeId, 
                                                                                                 int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Relative Humidity Measurement cluster, Client Manufacturer Specific
 * Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfRelativeHumidityMeasurementClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                                 EmberAfAttributeId attributeId, 
                                                                                                 int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Relative Humidity Measurement cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfRelativeHumidityMeasurementClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                            int8u commandId, 
                                                                            EmberAfStatus status);
/** @brief Client Default Response
 *
 * Relative Humidity Measurement cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfRelativeHumidityMeasurementClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                            int8u commandId, 
                                                                            EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Relative Humidity Measurement cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfRelativeHumidityMeasurementClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                                        int16u indexOrDestination, 
                                                                        EmberApsFrame * apsFrame, 
                                                                        int16u msgLen, 
                                                                        int8u * message, 
                                                                        EmberStatus status);
/** @brief Client Message Sent
 *
 * Relative Humidity Measurement cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfRelativeHumidityMeasurementClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                                        int16u indexOrDestination, 
                                                                        EmberApsFrame * apsFrame, 
                                                                        int16u msgLen, 
                                                                        int8u * message, 
                                                                        EmberStatus status);

/** @} END Relative Humidity Measurement Cluster Callbacks */

/** @name Occupancy Sensing Cluster Callbacks */
// @{

/** @brief Server Init
 *
 * Occupancy Sensing cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfOccupancySensingClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Occupancy Sensing cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfOccupancySensingClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Occupancy Sensing cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfOccupancySensingClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Occupancy Sensing cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfOccupancySensingClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Occupancy Sensing cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfOccupancySensingClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                  EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Occupancy Sensing cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfOccupancySensingClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                  EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Occupancy Sensing cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfOccupancySensingClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                      EmberAfAttributeId attributeId, 
                                                                                      int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Occupancy Sensing cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfOccupancySensingClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                      EmberAfAttributeId attributeId, 
                                                                                      int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Occupancy Sensing cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfOccupancySensingClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                 int8u commandId, 
                                                                 EmberAfStatus status);
/** @brief Client Default Response
 *
 * Occupancy Sensing cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfOccupancySensingClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                 int8u commandId, 
                                                                 EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Occupancy Sensing cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfOccupancySensingClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                             int16u indexOrDestination, 
                                                             EmberApsFrame * apsFrame, 
                                                             int16u msgLen, 
                                                             int8u * message, 
                                                             EmberStatus status);
/** @brief Client Message Sent
 *
 * Occupancy Sensing cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfOccupancySensingClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                             int16u indexOrDestination, 
                                                             EmberApsFrame * apsFrame, 
                                                             int16u msgLen, 
                                                             int8u * message, 
                                                             EmberStatus status);

/** @} END Occupancy Sensing Cluster Callbacks */

/** @name IAS Zone Cluster Callbacks */
// @{

/** @brief Zone Enroll Response
 *
 *
 * @param enrollResponseCode   Ver.: always
 * @param zoneId   Ver.: always
 */
boolean emberAfIasZoneClusterZoneEnrollResponseCallback(int8u enrollResponseCode, 
                                                        int8u zoneId);
/** @brief Zone Status Change Notification
 *
 *
 * @param zoneStatus   Ver.: always
 * @param extendedStatus   Ver.: always
 */
boolean emberAfIasZoneClusterZoneStatusChangeNotificationCallback(int16u zoneStatus, 
                                                                  int8u extendedStatus);
/** @brief Zone Enroll Request
 *
 *
 * @param zoneType   Ver.: always
 * @param manufacturerCode   Ver.: always
 */
boolean emberAfIasZoneClusterZoneEnrollRequestCallback(int16u zoneType, 
                                                       int16u manufacturerCode);
/** @brief Server Init
 *
 * IAS Zone cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIasZoneClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * IAS Zone cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIasZoneClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * IAS Zone cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIasZoneClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * IAS Zone cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIasZoneClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * IAS Zone cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIasZoneClusterServerAttributeChangedCallback(int8u endpoint, 
                                                         EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * IAS Zone cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIasZoneClusterClientAttributeChangedCallback(int8u endpoint, 
                                                         EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * IAS Zone cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfIasZoneClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                             EmberAfAttributeId attributeId, 
                                                                             int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * IAS Zone cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfIasZoneClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                             EmberAfAttributeId attributeId, 
                                                                             int16u manufacturerCode);
/** @brief Server Default Response
 *
 * IAS Zone cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfIasZoneClusterServerDefaultResponseCallback(int8u endpoint, 
                                                        int8u commandId, 
                                                        EmberAfStatus status);
/** @brief Client Default Response
 *
 * IAS Zone cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfIasZoneClusterClientDefaultResponseCallback(int8u endpoint, 
                                                        int8u commandId, 
                                                        EmberAfStatus status);
/** @brief Server Message Sent
 *
 * IAS Zone cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfIasZoneClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                    int16u indexOrDestination, 
                                                    EmberApsFrame * apsFrame, 
                                                    int16u msgLen, 
                                                    int8u * message, 
                                                    EmberStatus status);
/** @brief Client Message Sent
 *
 * IAS Zone cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfIasZoneClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                    int16u indexOrDestination, 
                                                    EmberApsFrame * apsFrame, 
                                                    int16u msgLen, 
                                                    int8u * message, 
                                                    EmberStatus status);

/** @} END IAS Zone Cluster Callbacks */

/** @name IAS ACE Cluster Callbacks */
// @{

/** @brief Arm
 *
 *
 * @param armMode   Ver.: always
 */
boolean emberAfIasAceClusterArmCallback(int8u armMode);
/** @brief Bypass
 *
 *
 * @param numberOfZones   Ver.: always
 * @param zoneIds   Ver.: always
 */
boolean emberAfIasAceClusterBypassCallback(int8u numberOfZones, 
                                           int8u* zoneIds);
/** @brief Emergency
 *
 *
 */
boolean emberAfIasAceClusterEmergencyCallback(void);
/** @brief Fire
 *
 *
 */
boolean emberAfIasAceClusterFireCallback(void);
/** @brief Panic
 *
 *
 */
boolean emberAfIasAceClusterPanicCallback(void);
/** @brief Get Zone Id Map
 *
 *
 */
boolean emberAfIasAceClusterGetZoneIdMapCallback(void);
/** @brief Get Zone Information
 *
 *
 * @param zoneId   Ver.: always
 */
boolean emberAfIasAceClusterGetZoneInformationCallback(int8u zoneId);
/** @brief Arm Response
 *
 *
 * @param armNotification   Ver.: always
 */
boolean emberAfIasAceClusterArmResponseCallback(int8u armNotification);
/** @brief Get Zone Id Map Response
 *
 *
 * @param section0   Ver.: always
 * @param section1   Ver.: always
 * @param section2   Ver.: always
 * @param section3   Ver.: always
 * @param section4   Ver.: always
 * @param section5   Ver.: always
 * @param section6   Ver.: always
 * @param section7   Ver.: always
 * @param section8   Ver.: always
 * @param section9   Ver.: always
 * @param section10   Ver.: always
 * @param section11   Ver.: always
 * @param section12   Ver.: always
 * @param section13   Ver.: always
 * @param section14   Ver.: always
 * @param section15   Ver.: always
 */
boolean emberAfIasAceClusterGetZoneIdMapResponseCallback(int16u section0, 
                                                         int16u section1, 
                                                         int16u section2, 
                                                         int16u section3, 
                                                         int16u section4, 
                                                         int16u section5, 
                                                         int16u section6, 
                                                         int16u section7, 
                                                         int16u section8, 
                                                         int16u section9, 
                                                         int16u section10, 
                                                         int16u section11, 
                                                         int16u section12, 
                                                         int16u section13, 
                                                         int16u section14, 
                                                         int16u section15);
/** @brief Get Zone Information Response
 *
 *
 * @param zoneId   Ver.: always
 * @param zoneType   Ver.: always
 * @param ieeeAddress   Ver.: always
 */
boolean emberAfIasAceClusterGetZoneInformationResponseCallback(int8u zoneId, 
                                                               int16u zoneType, 
                                                               int8u* ieeeAddress);
/** @brief Server Init
 *
 * IAS ACE cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIasAceClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * IAS ACE cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIasAceClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * IAS ACE cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIasAceClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * IAS ACE cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIasAceClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * IAS ACE cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIasAceClusterServerAttributeChangedCallback(int8u endpoint, 
                                                        EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * IAS ACE cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIasAceClusterClientAttributeChangedCallback(int8u endpoint, 
                                                        EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * IAS ACE cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfIasAceClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                            EmberAfAttributeId attributeId, 
                                                                            int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * IAS ACE cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfIasAceClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                            EmberAfAttributeId attributeId, 
                                                                            int16u manufacturerCode);
/** @brief Server Default Response
 *
 * IAS ACE cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfIasAceClusterServerDefaultResponseCallback(int8u endpoint, 
                                                       int8u commandId, 
                                                       EmberAfStatus status);
/** @brief Client Default Response
 *
 * IAS ACE cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfIasAceClusterClientDefaultResponseCallback(int8u endpoint, 
                                                       int8u commandId, 
                                                       EmberAfStatus status);
/** @brief Server Message Sent
 *
 * IAS ACE cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfIasAceClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                   int16u indexOrDestination, 
                                                   EmberApsFrame * apsFrame, 
                                                   int16u msgLen, 
                                                   int8u * message, 
                                                   EmberStatus status);
/** @brief Client Message Sent
 *
 * IAS ACE cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfIasAceClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                   int16u indexOrDestination, 
                                                   EmberApsFrame * apsFrame, 
                                                   int16u msgLen, 
                                                   int8u * message, 
                                                   EmberStatus status);

/** @} END IAS ACE Cluster Callbacks */

/** @name IAS WD Cluster Callbacks */
// @{

/** @brief Start Warning
 *
 *
 * @param warningInfo   Ver.: always
 * @param warningDuration   Ver.: always
 */
boolean emberAfIasWdClusterStartWarningCallback(int8u warningInfo, 
                                                int16u warningDuration);
/** @brief Squawk
 *
 *
 * @param squawkInfo   Ver.: always
 */
boolean emberAfIasWdClusterSquawkCallback(int8u squawkInfo);
/** @brief Server Init
 *
 * IAS WD cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIasWdClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * IAS WD cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIasWdClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * IAS WD cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIasWdClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * IAS WD cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIasWdClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * IAS WD cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIasWdClusterServerAttributeChangedCallback(int8u endpoint, 
                                                       EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * IAS WD cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIasWdClusterClientAttributeChangedCallback(int8u endpoint, 
                                                       EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * IAS WD cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfIasWdClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                           EmberAfAttributeId attributeId, 
                                                                           int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * IAS WD cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfIasWdClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                           EmberAfAttributeId attributeId, 
                                                                           int16u manufacturerCode);
/** @brief Server Default Response
 *
 * IAS WD cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfIasWdClusterServerDefaultResponseCallback(int8u endpoint, 
                                                      int8u commandId, 
                                                      EmberAfStatus status);
/** @brief Client Default Response
 *
 * IAS WD cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfIasWdClusterClientDefaultResponseCallback(int8u endpoint, 
                                                      int8u commandId, 
                                                      EmberAfStatus status);
/** @brief Server Message Sent
 *
 * IAS WD cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfIasWdClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                  int16u indexOrDestination, 
                                                  EmberApsFrame * apsFrame, 
                                                  int16u msgLen, 
                                                  int8u * message, 
                                                  EmberStatus status);
/** @brief Client Message Sent
 *
 * IAS WD cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfIasWdClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                  int16u indexOrDestination, 
                                                  EmberApsFrame * apsFrame, 
                                                  int16u msgLen, 
                                                  int8u * message, 
                                                  EmberStatus status);

/** @} END IAS WD Cluster Callbacks */

/** @name Door Lock Cluster Callbacks */
// @{

/** @brief Lock Door
 *
 *
 */
boolean emberAfDoorLockClusterLockDoorCallback(void);
/** @brief Unlock Door
 *
 *
 */
boolean emberAfDoorLockClusterUnlockDoorCallback(void);
/** @brief Lock Door Response
 *
 *
 * @param status   Ver.: always
 */
boolean emberAfDoorLockClusterLockDoorResponseCallback(int8u status);
/** @brief Unlock Door Response
 *
 *
 * @param status   Ver.: always
 */
boolean emberAfDoorLockClusterUnlockDoorResponseCallback(int8u status);
/** @brief Server Init
 *
 * Door Lock cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfDoorLockClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Door Lock cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfDoorLockClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Door Lock cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfDoorLockClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Door Lock cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfDoorLockClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Door Lock cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfDoorLockClusterServerAttributeChangedCallback(int8u endpoint, 
                                                          EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Door Lock cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfDoorLockClusterClientAttributeChangedCallback(int8u endpoint, 
                                                          EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Door Lock cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfDoorLockClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                              EmberAfAttributeId attributeId, 
                                                                              int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Door Lock cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfDoorLockClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                              EmberAfAttributeId attributeId, 
                                                                              int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Door Lock cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfDoorLockClusterServerDefaultResponseCallback(int8u endpoint, 
                                                         int8u commandId, 
                                                         EmberAfStatus status);
/** @brief Client Default Response
 *
 * Door Lock cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfDoorLockClusterClientDefaultResponseCallback(int8u endpoint, 
                                                         int8u commandId, 
                                                         EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Door Lock cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfDoorLockClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                     int16u indexOrDestination, 
                                                     EmberApsFrame * apsFrame, 
                                                     int16u msgLen, 
                                                     int8u * message, 
                                                     EmberStatus status);
/** @brief Client Message Sent
 *
 * Door Lock cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfDoorLockClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                     int16u indexOrDestination, 
                                                     EmberApsFrame * apsFrame, 
                                                     int16u msgLen, 
                                                     int8u * message, 
                                                     EmberStatus status);

/** @} END Door Lock Cluster Callbacks */

/** @name Window Covering Cluster Callbacks */
// @{

/** @brief Window Covering Up Open
 *
 *
 */
boolean emberAfWindowCoveringClusterWindowCoveringUpOpenCallback(void);
/** @brief Window Covering Down Close
 *
 *
 */
boolean emberAfWindowCoveringClusterWindowCoveringDownCloseCallback(void);
/** @brief Window Covering Stop
 *
 *
 */
boolean emberAfWindowCoveringClusterWindowCoveringStopCallback(void);
/** @brief Window Covering Go To Lift Setpoint
 *
 *
 * @param indexOfLiftSetpoint   Ver.: always
 */
boolean emberAfWindowCoveringClusterWindowCoveringGoToLiftSetpointCallback(int8u indexOfLiftSetpoint);
/** @brief Window Covering Go To Lift Value
 *
 *
 * @param liftValue   Ver.: always
 */
boolean emberAfWindowCoveringClusterWindowCoveringGoToLiftValueCallback(int16u liftValue);
/** @brief Window Covering Go To Lift Percentage
 *
 *
 * @param percentageLiftValue   Ver.: always
 */
boolean emberAfWindowCoveringClusterWindowCoveringGoToLiftPercentageCallback(int8u percentageLiftValue);
/** @brief Window Covering Go To Tilt Setpoint
 *
 *
 * @param indexOfTiltSetpoint   Ver.: always
 */
boolean emberAfWindowCoveringClusterWindowCoveringGoToTiltSetpointCallback(int8u indexOfTiltSetpoint);
/** @brief Window Covering Go To Tilt Value
 *
 *
 * @param tiltValue   Ver.: always
 */
boolean emberAfWindowCoveringClusterWindowCoveringGoToTiltValueCallback(int16u tiltValue);
/** @brief Window Covering Go To Tilt Percentage
 *
 *
 * @param percentageTiltValue   Ver.: always
 */
boolean emberAfWindowCoveringClusterWindowCoveringGoToTiltPercentageCallback(int8u percentageTiltValue);
/** @brief Window Covering Go To Program Setpoint
 *
 *
 * @param setpointType   Ver.: always
 * @param setpointIndex   Ver.: always
 * @param setpointValue   Ver.: always
 */
boolean emberAfWindowCoveringClusterWindowCoveringGoToProgramSetpointCallback(int8u setpointType, 
                                                                              int8u setpointIndex, 
                                                                              int16u setpointValue);
/** @brief Server Init
 *
 * Window Covering cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfWindowCoveringClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Window Covering cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfWindowCoveringClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Window Covering cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfWindowCoveringClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Window Covering cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfWindowCoveringClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Window Covering cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfWindowCoveringClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Window Covering cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfWindowCoveringClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Window Covering cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfWindowCoveringClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                    EmberAfAttributeId attributeId, 
                                                                                    int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Window Covering cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfWindowCoveringClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                    EmberAfAttributeId attributeId, 
                                                                                    int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Window Covering cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfWindowCoveringClusterServerDefaultResponseCallback(int8u endpoint, 
                                                               int8u commandId, 
                                                               EmberAfStatus status);
/** @brief Client Default Response
 *
 * Window Covering cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfWindowCoveringClusterClientDefaultResponseCallback(int8u endpoint, 
                                                               int8u commandId, 
                                                               EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Window Covering cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfWindowCoveringClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                           int16u indexOrDestination, 
                                                           EmberApsFrame * apsFrame, 
                                                           int16u msgLen, 
                                                           int8u * message, 
                                                           EmberStatus status);
/** @brief Client Message Sent
 *
 * Window Covering cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfWindowCoveringClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                           int16u indexOrDestination, 
                                                           EmberApsFrame * apsFrame, 
                                                           int16u msgLen, 
                                                           int8u * message, 
                                                           EmberStatus status);

/** @} END Window Covering Cluster Callbacks */

/** @name Generic Tunnel Cluster Callbacks */
// @{

/** @brief Match Protocol Address
 *
 *
 * @param protocolAddress   Ver.: always
 */
boolean emberAfGenericTunnelClusterMatchProtocolAddressCallback(int8u* protocolAddress);
/** @brief Match Protocol Address Response
 *
 *
 */
boolean emberAfGenericTunnelClusterMatchProtocolAddressResponseCallback(void);
/** @brief Advertise Protocol Address
 *
 *
 * @param protocolAddress   Ver.: always
 */
boolean emberAfGenericTunnelClusterAdvertiseProtocolAddressCallback(int8u* protocolAddress);
/** @brief Server Init
 *
 * Generic Tunnel cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfGenericTunnelClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Generic Tunnel cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfGenericTunnelClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Generic Tunnel cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfGenericTunnelClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Generic Tunnel cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfGenericTunnelClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Generic Tunnel cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfGenericTunnelClusterServerAttributeChangedCallback(int8u endpoint, 
                                                               EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Generic Tunnel cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfGenericTunnelClusterClientAttributeChangedCallback(int8u endpoint, 
                                                               EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Generic Tunnel cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfGenericTunnelClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                   EmberAfAttributeId attributeId, 
                                                                                   int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Generic Tunnel cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfGenericTunnelClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                   EmberAfAttributeId attributeId, 
                                                                                   int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Generic Tunnel cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfGenericTunnelClusterServerDefaultResponseCallback(int8u endpoint, 
                                                              int8u commandId, 
                                                              EmberAfStatus status);
/** @brief Client Default Response
 *
 * Generic Tunnel cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfGenericTunnelClusterClientDefaultResponseCallback(int8u endpoint, 
                                                              int8u commandId, 
                                                              EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Generic Tunnel cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfGenericTunnelClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                          int16u indexOrDestination, 
                                                          EmberApsFrame * apsFrame, 
                                                          int16u msgLen, 
                                                          int8u * message, 
                                                          EmberStatus status);
/** @brief Client Message Sent
 *
 * Generic Tunnel cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfGenericTunnelClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                          int16u indexOrDestination, 
                                                          EmberApsFrame * apsFrame, 
                                                          int16u msgLen, 
                                                          int8u * message, 
                                                          EmberStatus status);

/** @} END Generic Tunnel Cluster Callbacks */

/** @name BACnet Protocol Tunnel Cluster Callbacks */
// @{

/** @brief Transfer Npdu
 *
 *
 * @param NPDU   Ver.: always
 */
boolean emberAfBacnetProtocolTunnelClusterTransferNpduCallback(int8u* NPDU);
/** @brief Server Init
 *
 * BACnet Protocol Tunnel cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfBacnetProtocolTunnelClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * BACnet Protocol Tunnel cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfBacnetProtocolTunnelClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * BACnet Protocol Tunnel cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfBacnetProtocolTunnelClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * BACnet Protocol Tunnel cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfBacnetProtocolTunnelClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * BACnet Protocol Tunnel cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfBacnetProtocolTunnelClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                      EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * BACnet Protocol Tunnel cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfBacnetProtocolTunnelClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                      EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * BACnet Protocol Tunnel cluster, Server Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfBacnetProtocolTunnelClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                          EmberAfAttributeId attributeId, 
                                                                                          int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * BACnet Protocol Tunnel cluster, Client Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfBacnetProtocolTunnelClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                          EmberAfAttributeId attributeId, 
                                                                                          int16u manufacturerCode);
/** @brief Server Default Response
 *
 * BACnet Protocol Tunnel cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfBacnetProtocolTunnelClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                     int8u commandId, 
                                                                     EmberAfStatus status);
/** @brief Client Default Response
 *
 * BACnet Protocol Tunnel cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfBacnetProtocolTunnelClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                     int8u commandId, 
                                                                     EmberAfStatus status);
/** @brief Server Message Sent
 *
 * BACnet Protocol Tunnel cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfBacnetProtocolTunnelClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                                 int16u indexOrDestination, 
                                                                 EmberApsFrame * apsFrame, 
                                                                 int16u msgLen, 
                                                                 int8u * message, 
                                                                 EmberStatus status);
/** @brief Client Message Sent
 *
 * BACnet Protocol Tunnel cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfBacnetProtocolTunnelClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                                 int16u indexOrDestination, 
                                                                 EmberApsFrame * apsFrame, 
                                                                 int16u msgLen, 
                                                                 int8u * message, 
                                                                 EmberStatus status);

/** @} END BACnet Protocol Tunnel Cluster Callbacks */

/** @name Over the Air Bootloading Cluster Cluster Callbacks */
// @{

/** @brief Image Notify
 *
 *
 * @param payloadType   Ver.: always
 * @param queryJitter   Ver.: always
 * @param manufacturerId   Ver.: always
 * @param imageType   Ver.: always
 * @param newFileVersion   Ver.: always
 */
boolean emberAfOtaBootloadClusterImageNotifyCallback(int8u payloadType, 
                                                     int8u queryJitter, 
                                                     int16u manufacturerId, 
                                                     int16u imageType, 
                                                     int32u newFileVersion);
/** @brief Query Next Image Request
 *
 *
 * @param fieldControl   Ver.: always
 * @param manufacturerId   Ver.: always
 * @param imageType   Ver.: always
 * @param currentFileVersion   Ver.: always
 * @param hardwareVersion   Ver.: always
 */
boolean emberAfOtaBootloadClusterQueryNextImageRequestCallback(int8u fieldControl, 
                                                               int16u manufacturerId, 
                                                               int16u imageType, 
                                                               int32u currentFileVersion, 
                                                               int16u hardwareVersion);
/** @brief Query Next Image Response
 *
 *
 * @param status   Ver.: always
 * @param manufacturerId   Ver.: always
 * @param imageType   Ver.: always
 * @param fileVersion   Ver.: always
 * @param imageSize   Ver.: always
 */
boolean emberAfOtaBootloadClusterQueryNextImageResponseCallback(int8u status, 
                                                                int16u manufacturerId, 
                                                                int16u imageType, 
                                                                int32u fileVersion, 
                                                                int32u imageSize);
/** @brief Image Block Request
 *
 *
 * @param fieldControl   Ver.: always
 * @param manufacturerId   Ver.: always
 * @param imageType   Ver.: always
 * @param fileVersion   Ver.: always
 * @param fileOffset   Ver.: always
 * @param maxDataSize   Ver.: always
 * @param requestNodeAddress   Ver.: always
 */
boolean emberAfOtaBootloadClusterImageBlockRequestCallback(int8u fieldControl, 
                                                           int16u manufacturerId, 
                                                           int16u imageType, 
                                                           int32u fileVersion, 
                                                           int32u fileOffset, 
                                                           int8u maxDataSize, 
                                                           int8u* requestNodeAddress);
/** @brief Image Page Request
 *
 *
 * @param fieldControl   Ver.: always
 * @param manufacturerId   Ver.: always
 * @param imageType   Ver.: always
 * @param fileVersion   Ver.: always
 * @param fileOffset   Ver.: always
 * @param maxDataSize   Ver.: always
 * @param pageSize   Ver.: always
 * @param responseSpacing   Ver.: always
 * @param requestNodeAddress   Ver.: always
 */
boolean emberAfOtaBootloadClusterImagePageRequestCallback(int8u fieldControl, 
                                                          int16u manufacturerId, 
                                                          int16u imageType, 
                                                          int32u fileVersion, 
                                                          int32u fileOffset, 
                                                          int8u maxDataSize, 
                                                          int16u pageSize, 
                                                          int16u responseSpacing, 
                                                          int8u* requestNodeAddress);
/** @brief Image Block Response
 *
 *
 * @param status   Ver.: always
 * @param manufacturerId   Ver.: always
 * @param imageType   Ver.: always
 * @param fileVersion   Ver.: always
 * @param fileOffset   Ver.: always
 * @param dataSize   Ver.: always
 * @param imageData   Ver.: always
 */
boolean emberAfOtaBootloadClusterImageBlockResponseCallback(int8u status, 
                                                            int16u manufacturerId, 
                                                            int16u imageType, 
                                                            int32u fileVersion, 
                                                            int32u fileOffset, 
                                                            int8u dataSize, 
                                                            int8u* imageData);
/** @brief Upgrade End Request
 *
 *
 * @param status   Ver.: always
 * @param manufacturerId   Ver.: always
 * @param imageType   Ver.: always
 * @param fileVersion   Ver.: always
 */
boolean emberAfOtaBootloadClusterUpgradeEndRequestCallback(int8u status, 
                                                           int16u manufacturerId, 
                                                           int16u imageType, 
                                                           int32u fileVersion);
/** @brief Upgrade End Response
 *
 *
 * @param manufacturerId   Ver.: always
 * @param imageType   Ver.: always
 * @param fileVersion   Ver.: always
 * @param currentTime   Ver.: always
 * @param upgradeTime   Ver.: always
 */
boolean emberAfOtaBootloadClusterUpgradeEndResponseCallback(int16u manufacturerId, 
                                                            int16u imageType, 
                                                            int32u fileVersion, 
                                                            int32u currentTime, 
                                                            int32u upgradeTime);
/** @brief Query Specific File Request
 *
 *
 * @param requestNodeAddress   Ver.: always
 * @param manufacturerId   Ver.: always
 * @param imageType   Ver.: always
 * @param fileVersion   Ver.: always
 * @param currentZigbeeStackVersion   Ver.: always
 */
boolean emberAfOtaBootloadClusterQuerySpecificFileRequestCallback(int8u* requestNodeAddress, 
                                                                  int16u manufacturerId, 
                                                                  int16u imageType, 
                                                                  int32u fileVersion, 
                                                                  int16u currentZigbeeStackVersion);
/** @brief Query Specific File Response
 *
 *
 * @param status   Ver.: always
 * @param manufacturerId   Ver.: always
 * @param imageType   Ver.: always
 * @param fileVersion   Ver.: always
 * @param imageSize   Ver.: always
 */
boolean emberAfOtaBootloadClusterQuerySpecificFileResponseCallback(int8u status, 
                                                                   int16u manufacturerId, 
                                                                   int16u imageType, 
                                                                   int32u fileVersion, 
                                                                   int32u imageSize);
/** @brief Server Init
 *
 * Over the Air Bootloading Cluster cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfOtaBootloadClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Over the Air Bootloading Cluster cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfOtaBootloadClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Over the Air Bootloading Cluster cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfOtaBootloadClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Over the Air Bootloading Cluster cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfOtaBootloadClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Over the Air Bootloading Cluster cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfOtaBootloadClusterServerAttributeChangedCallback(int8u endpoint, 
                                                             EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Over the Air Bootloading Cluster cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfOtaBootloadClusterClientAttributeChangedCallback(int8u endpoint, 
                                                             EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Over the Air Bootloading Cluster cluster, Server Manufacturer Specific
 * Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfOtaBootloadClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                 EmberAfAttributeId attributeId, 
                                                                                 int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Over the Air Bootloading Cluster cluster, Client Manufacturer Specific
 * Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfOtaBootloadClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                 EmberAfAttributeId attributeId, 
                                                                                 int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Over the Air Bootloading Cluster cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfOtaBootloadClusterServerDefaultResponseCallback(int8u endpoint, 
                                                            int8u commandId, 
                                                            EmberAfStatus status);
/** @brief Client Default Response
 *
 * Over the Air Bootloading Cluster cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfOtaBootloadClusterClientDefaultResponseCallback(int8u endpoint, 
                                                            int8u commandId, 
                                                            EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Over the Air Bootloading Cluster cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfOtaBootloadClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                        int16u indexOrDestination, 
                                                        EmberApsFrame * apsFrame, 
                                                        int16u msgLen, 
                                                        int8u * message, 
                                                        EmberStatus status);
/** @brief Client Message Sent
 *
 * Over the Air Bootloading Cluster cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfOtaBootloadClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                        int16u indexOrDestination, 
                                                        EmberApsFrame * apsFrame, 
                                                        int16u msgLen, 
                                                        int8u * message, 
                                                        EmberStatus status);

/** @} END Over the Air Bootloading Cluster Cluster Callbacks */

/** @name Demand Response and Load Control Cluster Callbacks */
// @{

/** @brief Load Control Event
 *
 *
 * @param issuerEventId   Ver.: always
 * @param deviceClass   Ver.: always
 * @param utilityEnrollmentGroup   Ver.: always
 * @param startTime   Ver.: always
 * @param durationInMinutes   Ver.: always
 * @param criticalityLevel   Ver.: always
 * @param coolingTemperatureOffset   Ver.: always
 * @param heatingTemperatureOffset   Ver.: always
 * @param coolingTemperatureSetPoint   Ver.: always
 * @param heatingTemperatureSetPoint   Ver.: always
 * @param averageLoadAdjustmentPercentage   Ver.: always
 * @param dutyCycle   Ver.: always
 * @param eventControl   Ver.: always
 */
boolean emberAfDemandResponseLoadControlClusterLoadControlEventCallback(int32u issuerEventId, 
                                                                        int16u deviceClass, 
                                                                        int8u utilityEnrollmentGroup, 
                                                                        int32u startTime, 
                                                                        int16u durationInMinutes, 
                                                                        int8u criticalityLevel, 
                                                                        int8u coolingTemperatureOffset, 
                                                                        int8u heatingTemperatureOffset, 
                                                                        int16s coolingTemperatureSetPoint, 
                                                                        int16s heatingTemperatureSetPoint, 
                                                                        int8s averageLoadAdjustmentPercentage, 
                                                                        int8u dutyCycle, 
                                                                        int8u eventControl);
/** @brief Cancel Load Control Event
 *
 *
 * @param issuerEventId   Ver.: always
 * @param deviceClass   Ver.: always
 * @param utilityEnrollmentGroup   Ver.: always
 * @param cancelControl   Ver.: always
 * @param effectiveTime   Ver.: always
 */
boolean emberAfDemandResponseLoadControlClusterCancelLoadControlEventCallback(int32u issuerEventId, 
                                                                              int16u deviceClass, 
                                                                              int8u utilityEnrollmentGroup, 
                                                                              int8u cancelControl, 
                                                                              int32u effectiveTime);
/** @brief Cancel All Load Control Events
 *
 *
 * @param cancelControl   Ver.: always
 */
boolean emberAfDemandResponseLoadControlClusterCancelAllLoadControlEventsCallback(int8u cancelControl);
/** @brief Report Event Status
 *
 *
 * @param issuerEventId   Ver.: always
 * @param eventStatus   Ver.: always
 * @param eventStatusTime   Ver.: always
 * @param criticalityLevelApplied   Ver.: always
 * @param coolingTemperatureSetPointApplied   Ver.: always
 * @param heatingTemperatureSetPointApplied   Ver.: always
 * @param averageLoadAdjustmentPercentageApplied   Ver.: always
 * @param dutyCycleApplied   Ver.: always
 * @param eventControl   Ver.: always
 * @param signatureType   Ver.: always
 * @param signature   Ver.: until SE_1.1, 105638r08
 */
boolean emberAfDemandResponseLoadControlClusterReportEventStatusCallback(int32u issuerEventId, 
                                                                         int8u eventStatus, 
                                                                         int32u eventStatusTime, 
                                                                         int8u criticalityLevelApplied, 
                                                                         int16s coolingTemperatureSetPointApplied, 
                                                                         int16s heatingTemperatureSetPointApplied, 
                                                                         int8s averageLoadAdjustmentPercentageApplied, 
                                                                         int8u dutyCycleApplied, 
                                                                         int8u eventControl, 
                                                                         int8u signatureType, 
                                                                         int8u* signature);
/** @brief Get Scheduled Events
 *
 *
 * @param startTime   Ver.: always
 * @param numberOfEvents   Ver.: always
 */
boolean emberAfDemandResponseLoadControlClusterGetScheduledEventsCallback(int32u startTime, 
                                                                          int8u numberOfEvents);
/** @brief Server Init
 *
 * Demand Response and Load Control cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfDemandResponseLoadControlClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Demand Response and Load Control cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfDemandResponseLoadControlClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Demand Response and Load Control cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfDemandResponseLoadControlClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Demand Response and Load Control cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfDemandResponseLoadControlClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Demand Response and Load Control cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfDemandResponseLoadControlClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                           EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Demand Response and Load Control cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfDemandResponseLoadControlClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                           EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Demand Response and Load Control cluster, Server Manufacturer Specific
 * Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfDemandResponseLoadControlClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                               EmberAfAttributeId attributeId, 
                                                                                               int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Demand Response and Load Control cluster, Client Manufacturer Specific
 * Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfDemandResponseLoadControlClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                               EmberAfAttributeId attributeId, 
                                                                                               int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Demand Response and Load Control cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfDemandResponseLoadControlClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                          int8u commandId, 
                                                                          EmberAfStatus status);
/** @brief Client Default Response
 *
 * Demand Response and Load Control cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfDemandResponseLoadControlClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                          int8u commandId, 
                                                                          EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Demand Response and Load Control cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfDemandResponseLoadControlClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                                      int16u indexOrDestination, 
                                                                      EmberApsFrame * apsFrame, 
                                                                      int16u msgLen, 
                                                                      int8u * message, 
                                                                      EmberStatus status);
/** @brief Client Message Sent
 *
 * Demand Response and Load Control cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfDemandResponseLoadControlClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                                      int16u indexOrDestination, 
                                                                      EmberApsFrame * apsFrame, 
                                                                      int16u msgLen, 
                                                                      int8u * message, 
                                                                      EmberStatus status);

/** @} END Demand Response and Load Control Cluster Callbacks */

/** @name Simple Metering Cluster Callbacks */
// @{

/** @brief Get Profile Response
 *
 *
 * @param endTime   Ver.: always
 * @param status   Ver.: always
 * @param profileIntervalPeriod   Ver.: always
 * @param numberOfPeriodsDelivered   Ver.: always
 * @param intervals   Ver.: always
 */
boolean emberAfSimpleMeteringClusterGetProfileResponseCallback(int32u endTime, 
                                                               int8u status, 
                                                               int8u profileIntervalPeriod, 
                                                               int8u numberOfPeriodsDelivered, 
                                                               int8u* intervals);
/** @brief Request Mirror
 *
 *
 */
boolean emberAfSimpleMeteringClusterRequestMirrorCallback(void);
/** @brief Remove Mirror
 *
 *
 */
boolean emberAfSimpleMeteringClusterRemoveMirrorCallback(void);
/** @brief Request Fast Poll Mode Response
 *
 *
 * @param appliedUpdatePeriod   Ver.: always
 * @param fastPollModeEndtime   Ver.: always
 */
boolean emberAfSimpleMeteringClusterRequestFastPollModeResponseCallback(int8u appliedUpdatePeriod, 
                                                                        int32u fastPollModeEndtime);
/** @brief Get Profile
 *
 *
 * @param intervalChannel   Ver.: always
 * @param endTime   Ver.: always
 * @param numberOfPeriods   Ver.: always
 */
boolean emberAfSimpleMeteringClusterGetProfileCallback(int8u intervalChannel, 
                                                       int32u endTime, 
                                                       int8u numberOfPeriods);
/** @brief Request Mirror Response
 *
 *
 * @param endpointId   Ver.: always
 */
boolean emberAfSimpleMeteringClusterRequestMirrorResponseCallback(int16u endpointId);
/** @brief Mirror Removed
 *
 *
 * @param endpointId   Ver.: always
 */
boolean emberAfSimpleMeteringClusterMirrorRemovedCallback(int16u endpointId);
/** @brief Request Fast Poll Mode
 *
 *
 * @param fastPollUpdatePeriod   Ver.: always
 * @param duration   Ver.: always
 */
boolean emberAfSimpleMeteringClusterRequestFastPollModeCallback(int8u fastPollUpdatePeriod, 
                                                                int8u duration);
/** @brief Server Init
 *
 * Simple Metering cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfSimpleMeteringClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Simple Metering cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfSimpleMeteringClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Simple Metering cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfSimpleMeteringClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Simple Metering cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfSimpleMeteringClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Simple Metering cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfSimpleMeteringClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Simple Metering cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfSimpleMeteringClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Simple Metering cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfSimpleMeteringClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                    EmberAfAttributeId attributeId, 
                                                                                    int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Simple Metering cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfSimpleMeteringClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                    EmberAfAttributeId attributeId, 
                                                                                    int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Simple Metering cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfSimpleMeteringClusterServerDefaultResponseCallback(int8u endpoint, 
                                                               int8u commandId, 
                                                               EmberAfStatus status);
/** @brief Client Default Response
 *
 * Simple Metering cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfSimpleMeteringClusterClientDefaultResponseCallback(int8u endpoint, 
                                                               int8u commandId, 
                                                               EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Simple Metering cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfSimpleMeteringClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                           int16u indexOrDestination, 
                                                           EmberApsFrame * apsFrame, 
                                                           int16u msgLen, 
                                                           int8u * message, 
                                                           EmberStatus status);
/** @brief Client Message Sent
 *
 * Simple Metering cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfSimpleMeteringClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                           int16u indexOrDestination, 
                                                           EmberApsFrame * apsFrame, 
                                                           int16u msgLen, 
                                                           int8u * message, 
                                                           EmberStatus status);

/** @} END Simple Metering Cluster Callbacks */

/** @name Price Cluster Callbacks */
// @{

/** @brief Publish Price
 *
 *
 * @param providerId   Ver.: always
 * @param rateLabel   Ver.: always
 * @param issuerEventId   Ver.: always
 * @param currentTime   Ver.: always
 * @param unitOfMeasure   Ver.: always
 * @param currency   Ver.: always
 * @param priceTrailingDigitAndPriceTier   Ver.: always
 * @param numberOfPriceTiersAndRegisterTier   Ver.: always
 * @param startTime   Ver.: always
 * @param durationInMinutes   Ver.: always
 * @param price   Ver.: always
 * @param priceRatio   Ver.: always
 * @param generationPrice   Ver.: always
 * @param generationPriceRatio   Ver.: always
 * @param alternateCostDelivered   Ver.: since SE_1.0, 075356r15
 * @param alternateCostUnit   Ver.: since SE_1.0, 075356r15
 * @param alternateCostTrailingDigit   Ver.: since SE_1.0, 075356r15
 * @param numberOfBlockThresholds   Ver.: since SE_1.1, 105638r09
 * @param priceControl   Ver.: since SE_1.1, 105638r09
 */
boolean emberAfPriceClusterPublishPriceCallback(int32u providerId, 
                                                int8u* rateLabel, 
                                                int32u issuerEventId, 
                                                int32u currentTime, 
                                                int8u unitOfMeasure, 
                                                int16u currency, 
                                                int8u priceTrailingDigitAndPriceTier, 
                                                int8u numberOfPriceTiersAndRegisterTier, 
                                                int32u startTime, 
                                                int16u durationInMinutes, 
                                                int32u price, 
                                                int8u priceRatio, 
                                                int32u generationPrice, 
                                                int8u generationPriceRatio, 
                                                int32u alternateCostDelivered, 
                                                int8u alternateCostUnit, 
                                                int8u alternateCostTrailingDigit, 
                                                int8u numberOfBlockThresholds, 
                                                int8u priceControl);
/** @brief Publish Block Period
 *
 *
 * @param providerId   Ver.: always
 * @param issuerEventId   Ver.: always
 * @param blockPeriodStartTime   Ver.: always
 * @param blockPeriodDurationInMinutes   Ver.: always
 * @param numberOfPriceTiersAndNumberOfBlockThresholds   Ver.: always
 * @param blockPeriodControl   Ver.: always
 */
boolean emberAfPriceClusterPublishBlockPeriodCallback(int32u providerId, 
                                                      int32u issuerEventId, 
                                                      int32u blockPeriodStartTime, 
                                                      int32u blockPeriodDurationInMinutes, 
                                                      int8u numberOfPriceTiersAndNumberOfBlockThresholds, 
                                                      int8u blockPeriodControl);
/** @brief Get Current Price
 *
 *
 * @param commandOptions   Ver.: always
 */
boolean emberAfPriceClusterGetCurrentPriceCallback(int8u commandOptions);
/** @brief Get Scheduled Prices
 *
 *
 * @param startTime   Ver.: always
 * @param numberOfEvents   Ver.: always
 */
boolean emberAfPriceClusterGetScheduledPricesCallback(int32u startTime, 
                                                      int8u numberOfEvents);
/** @brief Price Acknowledgement
 *
 *
 * @param providerId   Ver.: always
 * @param issuerEventId   Ver.: always
 * @param priceAckTime   Ver.: always
 * @param control   Ver.: always
 */
boolean emberAfPriceClusterPriceAcknowledgementCallback(int32u providerId, 
                                                        int32u issuerEventId, 
                                                        int32u priceAckTime, 
                                                        int8u control);
/** @brief Get Block Periods
 *
 *
 * @param startTime   Ver.: always
 * @param numberOfEvents   Ver.: always
 */
boolean emberAfPriceClusterGetBlockPeriodsCallback(int32u startTime, 
                                                   int8u numberOfEvents);
/** @brief Server Init
 *
 * Price cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPriceClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Price cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPriceClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Price cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfPriceClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Price cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfPriceClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Price cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfPriceClusterServerAttributeChangedCallback(int8u endpoint, 
                                                       EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Price cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfPriceClusterClientAttributeChangedCallback(int8u endpoint, 
                                                       EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Price cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfPriceClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                           EmberAfAttributeId attributeId, 
                                                                           int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Price cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfPriceClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                           EmberAfAttributeId attributeId, 
                                                                           int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Price cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfPriceClusterServerDefaultResponseCallback(int8u endpoint, 
                                                      int8u commandId, 
                                                      EmberAfStatus status);
/** @brief Client Default Response
 *
 * Price cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfPriceClusterClientDefaultResponseCallback(int8u endpoint, 
                                                      int8u commandId, 
                                                      EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Price cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfPriceClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                  int16u indexOrDestination, 
                                                  EmberApsFrame * apsFrame, 
                                                  int16u msgLen, 
                                                  int8u * message, 
                                                  EmberStatus status);
/** @brief Client Message Sent
 *
 * Price cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfPriceClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                  int16u indexOrDestination, 
                                                  EmberApsFrame * apsFrame, 
                                                  int16u msgLen, 
                                                  int8u * message, 
                                                  EmberStatus status);

/** @} END Price Cluster Callbacks */

/** @name Messaging Cluster Callbacks */
// @{

/** @brief Display Message
 *
 *
 * @param messageId   Ver.: always
 * @param messageControl   Ver.: always
 * @param startTime   Ver.: always
 * @param durationInMinutes   Ver.: always
 * @param message   Ver.: always
 */
boolean emberAfMessagingClusterDisplayMessageCallback(int32u messageId, 
                                                      int8u messageControl, 
                                                      int32u startTime, 
                                                      int16u durationInMinutes, 
                                                      int8u* message);
/** @brief Cancel Message
 *
 *
 * @param messageId   Ver.: always
 * @param messageControl   Ver.: always
 */
boolean emberAfMessagingClusterCancelMessageCallback(int32u messageId, 
                                                     int8u messageControl);
/** @brief Get Last Message
 *
 *
 */
boolean emberAfMessagingClusterGetLastMessageCallback(void);
/** @brief Message Confirmation
 *
 *
 * @param messageId   Ver.: always
 * @param confirmationTime   Ver.: always
 */
boolean emberAfMessagingClusterMessageConfirmationCallback(int32u messageId, 
                                                           int32u confirmationTime);
/** @brief Server Init
 *
 * Messaging cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfMessagingClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Messaging cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfMessagingClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Messaging cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfMessagingClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Messaging cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfMessagingClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Messaging cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfMessagingClusterServerAttributeChangedCallback(int8u endpoint, 
                                                           EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Messaging cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfMessagingClusterClientAttributeChangedCallback(int8u endpoint, 
                                                           EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Messaging cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfMessagingClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                               EmberAfAttributeId attributeId, 
                                                                               int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Messaging cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfMessagingClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                               EmberAfAttributeId attributeId, 
                                                                               int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Messaging cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfMessagingClusterServerDefaultResponseCallback(int8u endpoint, 
                                                          int8u commandId, 
                                                          EmberAfStatus status);
/** @brief Client Default Response
 *
 * Messaging cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfMessagingClusterClientDefaultResponseCallback(int8u endpoint, 
                                                          int8u commandId, 
                                                          EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Messaging cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfMessagingClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                      int16u indexOrDestination, 
                                                      EmberApsFrame * apsFrame, 
                                                      int16u msgLen, 
                                                      int8u * message, 
                                                      EmberStatus status);
/** @brief Client Message Sent
 *
 * Messaging cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfMessagingClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                      int16u indexOrDestination, 
                                                      EmberApsFrame * apsFrame, 
                                                      int16u msgLen, 
                                                      int8u * message, 
                                                      EmberStatus status);

/** @} END Messaging Cluster Callbacks */

/** @name Tunneling Cluster Callbacks */
// @{

/** @brief Request Tunnel
 *
 *
 * @param protocolId   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param flowControlSupport   Ver.: always
 */
boolean emberAfTunnelingClusterRequestTunnelCallback(int8u protocolId, 
                                                     int16u manufacturerCode, 
                                                     int8u flowControlSupport);
/** @brief Close Tunnel
 *
 *
 * @param tunnelId   Ver.: always
 */
boolean emberAfTunnelingClusterCloseTunnelCallback(int16u tunnelId);
/** @brief Transfer Data Client To Server
 *
 *
 * @param tunnelId   Ver.: always
 * @param data   Ver.: always
 */
boolean emberAfTunnelingClusterTransferDataClientToServerCallback(int16u tunnelId, 
                                                                  int8u* data);
/** @brief Transfer Data Error Client To Server
 *
 *
 * @param tunnelId   Ver.: always
 * @param transferDataStatus   Ver.: always
 */
boolean emberAfTunnelingClusterTransferDataErrorClientToServerCallback(int16u tunnelId, 
                                                                       int8u transferDataStatus);
/** @brief Ack Transfer Data Client To Server
 *
 *
 * @param tunnelId   Ver.: always
 * @param numberOfBytesLeft   Ver.: always
 */
boolean emberAfTunnelingClusterAckTransferDataClientToServerCallback(int16u tunnelId, 
                                                                     int16u numberOfBytesLeft);
/** @brief Ready Data Client To Server
 *
 *
 * @param tunnelId   Ver.: always
 * @param numberOfOctetsLeft   Ver.: always
 */
boolean emberAfTunnelingClusterReadyDataClientToServerCallback(int16u tunnelId, 
                                                               int16u numberOfOctetsLeft);
/** @brief Request Tunnel Response
 *
 *
 * @param tunnelId   Ver.: always
 * @param tunnelStatus   Ver.: always
 */
boolean emberAfTunnelingClusterRequestTunnelResponseCallback(int16u tunnelId, 
                                                             int8u tunnelStatus);
/** @brief Transfer Data Server To Client
 *
 *
 * @param tunnelId   Ver.: always
 * @param data   Ver.: always
 */
boolean emberAfTunnelingClusterTransferDataServerToClientCallback(int16u tunnelId, 
                                                                  int8u* data);
/** @brief Transfer Data Error Server To Client
 *
 *
 * @param tunnelId   Ver.: always
 * @param transferDataStatus   Ver.: always
 */
boolean emberAfTunnelingClusterTransferDataErrorServerToClientCallback(int16u tunnelId, 
                                                                       int8u transferDataStatus);
/** @brief Ack Transfer Data Server To Client
 *
 *
 * @param tunnelId   Ver.: always
 * @param numberOfBytesLeft   Ver.: always
 */
boolean emberAfTunnelingClusterAckTransferDataServerToClientCallback(int16u tunnelId, 
                                                                     int16u numberOfBytesLeft);
/** @brief Ready Data Server To Client
 *
 *
 * @param tunnelId   Ver.: always
 * @param numberOfOctetsLeft   Ver.: always
 */
boolean emberAfTunnelingClusterReadyDataServerToClientCallback(int16u tunnelId, 
                                                               int16u numberOfOctetsLeft);
/** @brief Server Init
 *
 * Tunneling cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfTunnelingClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Tunneling cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfTunnelingClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Tunneling cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfTunnelingClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Tunneling cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfTunnelingClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Tunneling cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfTunnelingClusterServerAttributeChangedCallback(int8u endpoint, 
                                                           EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Tunneling cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfTunnelingClusterClientAttributeChangedCallback(int8u endpoint, 
                                                           EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Tunneling cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfTunnelingClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                               EmberAfAttributeId attributeId, 
                                                                               int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Tunneling cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfTunnelingClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                               EmberAfAttributeId attributeId, 
                                                                               int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Tunneling cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfTunnelingClusterServerDefaultResponseCallback(int8u endpoint, 
                                                          int8u commandId, 
                                                          EmberAfStatus status);
/** @brief Client Default Response
 *
 * Tunneling cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfTunnelingClusterClientDefaultResponseCallback(int8u endpoint, 
                                                          int8u commandId, 
                                                          EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Tunneling cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfTunnelingClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                      int16u indexOrDestination, 
                                                      EmberApsFrame * apsFrame, 
                                                      int16u msgLen, 
                                                      int8u * message, 
                                                      EmberStatus status);
/** @brief Client Message Sent
 *
 * Tunneling cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfTunnelingClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                      int16u indexOrDestination, 
                                                      EmberApsFrame * apsFrame, 
                                                      int16u msgLen, 
                                                      int8u * message, 
                                                      EmberStatus status);

/** @} END Tunneling Cluster Callbacks */

/** @name Prepayment Cluster Callbacks */
// @{

/** @brief Select Available Emergency Credit
 *
 *
 * @param commandDateTime   Ver.: always
 * @param originatingDevice   Ver.: always
 * @param siteId   Ver.: always
 * @param meterSerialNumber   Ver.: always
 */
boolean emberAfPrepaymentClusterSelectAvailableEmergencyCreditCallback(int32u commandDateTime, 
                                                                       int8u originatingDevice, 
                                                                       int8u* siteId, 
                                                                       int8u* meterSerialNumber);
/** @brief Change Supply
 *
 *
 * @param providerId   Ver.: always
 * @param requestDateTime   Ver.: always
 * @param siteId   Ver.: always
 * @param meterSerialNumber   Ver.: always
 * @param implementationDateTime   Ver.: always
 * @param proposedSupplyStatus   Ver.: always
 * @param originatorIdSupplyControlBits   Ver.: always
 */
boolean emberAfPrepaymentClusterChangeSupplyCallback(int32u providerId, 
                                                     int32u requestDateTime, 
                                                     int8u* siteId, 
                                                     int8u* meterSerialNumber, 
                                                     int32u implementationDateTime, 
                                                     int8u proposedSupplyStatus, 
                                                     int8u originatorIdSupplyControlBits);
/** @brief Supply Status Response
 *
 *
 * @param providerId   Ver.: always
 * @param implementationtDateTime   Ver.: always
 * @param supplyStatus   Ver.: always
 */
boolean emberAfPrepaymentClusterSupplyStatusResponseCallback(int32u providerId, 
                                                             int32u implementationtDateTime, 
                                                             int8u supplyStatus);
/** @brief Server Init
 *
 * Prepayment cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPrepaymentClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Prepayment cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPrepaymentClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Prepayment cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfPrepaymentClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Prepayment cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfPrepaymentClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Prepayment cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfPrepaymentClusterServerAttributeChangedCallback(int8u endpoint, 
                                                            EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Prepayment cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfPrepaymentClusterClientAttributeChangedCallback(int8u endpoint, 
                                                            EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Prepayment cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfPrepaymentClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                EmberAfAttributeId attributeId, 
                                                                                int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Prepayment cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfPrepaymentClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                EmberAfAttributeId attributeId, 
                                                                                int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Prepayment cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfPrepaymentClusterServerDefaultResponseCallback(int8u endpoint, 
                                                           int8u commandId, 
                                                           EmberAfStatus status);
/** @brief Client Default Response
 *
 * Prepayment cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfPrepaymentClusterClientDefaultResponseCallback(int8u endpoint, 
                                                           int8u commandId, 
                                                           EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Prepayment cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfPrepaymentClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                       int16u indexOrDestination, 
                                                       EmberApsFrame * apsFrame, 
                                                       int16u msgLen, 
                                                       int8u * message, 
                                                       EmberStatus status);
/** @brief Client Message Sent
 *
 * Prepayment cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfPrepaymentClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                       int16u indexOrDestination, 
                                                       EmberApsFrame * apsFrame, 
                                                       int16u msgLen, 
                                                       int8u * message, 
                                                       EmberStatus status);

/** @} END Prepayment Cluster Callbacks */

/** @name Key establishment Cluster Callbacks */
// @{

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
boolean emberAfKeyEstablishmentClusterClientCommandReceivedCallback(EmberAfClusterCommand * cmd);
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
boolean emberAfKeyEstablishmentClusterServerCommandReceivedCallback(EmberAfClusterCommand * cmd);
/** @brief Initiate Key Establishment Request
 *
 *
 * @param keyEstablishmentSuite   Ver.: always
 * @param ephemeralDataGenerateTime   Ver.: always
 * @param confirmKeyGenerateTime   Ver.: always
 * @param identity   Ver.: always
 */
boolean emberAfKeyEstablishmentClusterInitiateKeyEstablishmentRequestCallback(int16u keyEstablishmentSuite, 
                                                                              int8u ephemeralDataGenerateTime, 
                                                                              int8u confirmKeyGenerateTime, 
                                                                              int8u* identity);
/** @brief Ephemeral Data Request
 *
 *
 * @param ephemeralData   Ver.: always
 */
boolean emberAfKeyEstablishmentClusterEphemeralDataRequestCallback(int8u* ephemeralData);
/** @brief Confirm Key Data Request
 *
 *
 * @param secureMessageAuthenticationCode   Ver.: always
 */
boolean emberAfKeyEstablishmentClusterConfirmKeyDataRequestCallback(int8u* secureMessageAuthenticationCode);
/** @brief Terminate Key Establishment
 *
 *
 * @param statusCode   Ver.: always
 * @param waitTime   Ver.: always
 * @param keyEstablishmentSuite   Ver.: always
 */
boolean emberAfKeyEstablishmentClusterTerminateKeyEstablishmentCallback(int8u statusCode, 
                                                                        int8u waitTime, 
                                                                        int16u keyEstablishmentSuite);
/** @brief Initiate Key Establishment Response
 *
 *
 * @param requestedKeyEstablishmentSuite   Ver.: always
 * @param ephemeralDataGenerateTime   Ver.: always
 * @param confirmKeyGenerateTime   Ver.: always
 * @param identity   Ver.: always
 */
boolean emberAfKeyEstablishmentClusterInitiateKeyEstablishmentResponseCallback(int16u requestedKeyEstablishmentSuite, 
                                                                               int8u ephemeralDataGenerateTime, 
                                                                               int8u confirmKeyGenerateTime, 
                                                                               int8u* identity);
/** @brief Ephemeral Data Response
 *
 *
 * @param ephemeralData   Ver.: always
 */
boolean emberAfKeyEstablishmentClusterEphemeralDataResponseCallback(int8u* ephemeralData);
/** @brief Confirm Key Data Response
 *
 *
 * @param secureMessageAuthenticationCode   Ver.: always
 */
boolean emberAfKeyEstablishmentClusterConfirmKeyDataResponseCallback(int8u* secureMessageAuthenticationCode);
/** @brief Server Init
 *
 * Key establishment cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfKeyEstablishmentClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Key establishment cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfKeyEstablishmentClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Key establishment cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfKeyEstablishmentClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Key establishment cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfKeyEstablishmentClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Key establishment cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfKeyEstablishmentClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                  EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Key establishment cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfKeyEstablishmentClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                  EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Key establishment cluster, Server Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfKeyEstablishmentClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                      EmberAfAttributeId attributeId, 
                                                                                      int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Key establishment cluster, Client Manufacturer Specific Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfKeyEstablishmentClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                      EmberAfAttributeId attributeId, 
                                                                                      int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Key establishment cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfKeyEstablishmentClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                 int8u commandId, 
                                                                 EmberAfStatus status);
/** @brief Client Default Response
 *
 * Key establishment cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfKeyEstablishmentClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                 int8u commandId, 
                                                                 EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Key establishment cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfKeyEstablishmentClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                             int16u indexOrDestination, 
                                                             EmberApsFrame * apsFrame, 
                                                             int16u msgLen, 
                                                             int8u * message, 
                                                             EmberStatus status);
/** @brief Client Message Sent
 *
 * Key establishment cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfKeyEstablishmentClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                             int16u indexOrDestination, 
                                                             EmberApsFrame * apsFrame, 
                                                             int16u msgLen, 
                                                             int8u * message, 
                                                             EmberStatus status);

/** @} END Key establishment Cluster Callbacks */

/** @name Sample Mfg Specific Cluster Cluster Callbacks */
// @{

/** @brief Command One
 *
 *
 * @param argOne   Ver.: always
 */
boolean emberAfSampleMfgSpecificClusterCommandOneCallback(int8u argOne);
/** @brief Server Init
 *
 * Sample Mfg Specific Cluster cluster, Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfSampleMfgSpecificClusterServerInitCallback(int8u endpoint);
/** @brief Client Init
 *
 * Sample Mfg Specific Cluster cluster, Client Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfSampleMfgSpecificClusterClientInitCallback(int8u endpoint);
/** @brief Server Tick
 *
 * Sample Mfg Specific Cluster cluster, Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfSampleMfgSpecificClusterServerTickCallback(int8u endpoint);
/** @brief Client Tick
 *
 * Sample Mfg Specific Cluster cluster, Client Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfSampleMfgSpecificClusterClientTickCallback(int8u endpoint);
/** @brief Server Attribute Changed
 *
 * Sample Mfg Specific Cluster cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfSampleMfgSpecificClusterServerAttributeChangedCallback(int8u endpoint, 
                                                                   EmberAfAttributeId attributeId);
/** @brief Client Attribute Changed
 *
 * Sample Mfg Specific Cluster cluster, Client Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfSampleMfgSpecificClusterClientAttributeChangedCallback(int8u endpoint, 
                                                                   EmberAfAttributeId attributeId);
/** @brief Server Manufacturer Specific Attribute Changed
 *
 * Sample Mfg Specific Cluster cluster, Server Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfSampleMfgSpecificClusterServerManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                       EmberAfAttributeId attributeId, 
                                                                                       int16u manufacturerCode);
/** @brief Client Manufacturer Specific Attribute Changed
 *
 * Sample Mfg Specific Cluster cluster, Client Manufacturer Specific Attribute
 * Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 * @param manufacturerCode Manufacturer Code of the attribute that changed 
 * Ver.: always
 */
void emberAfSampleMfgSpecificClusterClientManufacturerSpecificAttributeChangedCallback(int8u endpoint, 
                                                                                       EmberAfAttributeId attributeId, 
                                                                                       int16u manufacturerCode);
/** @brief Server Default Response
 *
 * Sample Mfg Specific Cluster cluster, Server Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfSampleMfgSpecificClusterServerDefaultResponseCallback(int8u endpoint, 
                                                                  int8u commandId, 
                                                                  EmberAfStatus status);
/** @brief Client Default Response
 *
 * Sample Mfg Specific Cluster cluster, Client Default Response
 *
 * @param endpoint Destination endpoint  Ver.: always
 * @param commandId Command id  Ver.: always
 * @param status Status in default response  Ver.: always
 */
void emberAfSampleMfgSpecificClusterClientDefaultResponseCallback(int8u endpoint, 
                                                                  int8u commandId, 
                                                                  EmberAfStatus status);
/** @brief Server Message Sent
 *
 * Sample Mfg Specific Cluster cluster, Server Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfSampleMfgSpecificClusterServerMessageSentCallback(EmberOutgoingMessageType type, 
                                                              int16u indexOrDestination, 
                                                              EmberApsFrame * apsFrame, 
                                                              int16u msgLen, 
                                                              int8u * message, 
                                                              EmberStatus status);
/** @brief Client Message Sent
 *
 * Sample Mfg Specific Cluster cluster, Client Message Sent
 *
 * @param type The type of message sent  Ver.: always
 * @param indexOrDestination The destination or address to which the message
 * was sent  Ver.: always
 * @param apsFrame The APS frame for the message  Ver.: always
 * @param msgLen The length of the message  Ver.: always
 * @param message The message that was sent  Ver.: always
 * @param status The status of the sent message  Ver.: always
 */
void emberAfSampleMfgSpecificClusterClientMessageSentCallback(EmberOutgoingMessageType type, 
                                                              int16u indexOrDestination, 
                                                              EmberApsFrame * apsFrame, 
                                                              int16u msgLen, 
                                                              int8u * message, 
                                                              EmberStatus status);

/** @} END Sample Mfg Specific Cluster Cluster Callbacks */


/** @} END addtogroup */
#endif // __EMBER_AF_CALLBACK_PROTOTYPES__
