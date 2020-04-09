// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generateClientAPI()
//

// Enclosing macro to prevent multiple inclusion
#ifndef CLUSTER_CLIENT_API
#define CLUSTER_CLIENT_API


// This is generated client API



/**
 * @addtogroup command Application Framework V2 command interface Reference
 * This document describes the ZCL command interface used by the Ember Application
 * Framework for filling ZCL command buffers.
 * @{
 */
/** @name Global Commands */
// @{
/** @brief Command description for ReadAttributes
 *
 * Command: ReadAttributes
 * @param clusterId EmberAfClusterId
 * @param attributeIds int8u*
 * @param attributeIdsLen int8u
 */
#define emberAfFillCommandGlobalServerToClientReadAttributes(clusterId,attributeIds,attributeIdsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_READ_ATTRIBUTES_COMMAND_ID,\
                            "b",\
                            attributeIds,\
                            attributeIdsLen\
                            );


/** @brief Command description for ReadAttributes
 *
 * Command: ReadAttributes
 * @param clusterId EmberAfClusterId
 * @param attributeIds int8u*
 * @param attributeIdsLen int8u
 */
#define emberAfFillCommandGlobalClientToServerReadAttributes(clusterId,attributeIds,attributeIdsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_READ_ATTRIBUTES_COMMAND_ID,\
                            "b",\
                            attributeIds,\
                            attributeIdsLen\
                            );


/** @brief Command description for ReadAttributesResponse
 *
 * Command: ReadAttributesResponse
 * @param clusterId EmberAfClusterId
 * @param readAttributeStatusRecords int8u*
 * @param readAttributeStatusRecordsLen int8u
 */
#define emberAfFillCommandGlobalServerToClientReadAttributesResponse(clusterId,readAttributeStatusRecords,readAttributeStatusRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID,\
                            "b",\
                            readAttributeStatusRecords,\
                            readAttributeStatusRecordsLen\
                            );


/** @brief Command description for ReadAttributesResponse
 *
 * Command: ReadAttributesResponse
 * @param clusterId EmberAfClusterId
 * @param readAttributeStatusRecords int8u*
 * @param readAttributeStatusRecordsLen int8u
 */
#define emberAfFillCommandGlobalClientToServerReadAttributesResponse(clusterId,readAttributeStatusRecords,readAttributeStatusRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID,\
                            "b",\
                            readAttributeStatusRecords,\
                            readAttributeStatusRecordsLen\
                            );


/** @brief Command description for WriteAttributes
 *
 * Command: WriteAttributes
 * @param clusterId EmberAfClusterId
 * @param writeAttributeRecords int8u*
 * @param writeAttributeRecordsLen int8u
 */
#define emberAfFillCommandGlobalServerToClientWriteAttributes(clusterId,writeAttributeRecords,writeAttributeRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_WRITE_ATTRIBUTES_COMMAND_ID,\
                            "b",\
                            writeAttributeRecords,\
                            writeAttributeRecordsLen\
                            );


/** @brief Command description for WriteAttributes
 *
 * Command: WriteAttributes
 * @param clusterId EmberAfClusterId
 * @param writeAttributeRecords int8u*
 * @param writeAttributeRecordsLen int8u
 */
#define emberAfFillCommandGlobalClientToServerWriteAttributes(clusterId,writeAttributeRecords,writeAttributeRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_WRITE_ATTRIBUTES_COMMAND_ID,\
                            "b",\
                            writeAttributeRecords,\
                            writeAttributeRecordsLen\
                            );


/** @brief Command description for WriteAttributesUndivided
 *
 * Command: WriteAttributesUndivided
 * @param clusterId EmberAfClusterId
 * @param writeAttributeRecords int8u*
 * @param writeAttributeRecordsLen int8u
 */
#define emberAfFillCommandGlobalServerToClientWriteAttributesUndivided(clusterId,writeAttributeRecords,writeAttributeRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID,\
                            "b",\
                            writeAttributeRecords,\
                            writeAttributeRecordsLen\
                            );


/** @brief Command description for WriteAttributesUndivided
 *
 * Command: WriteAttributesUndivided
 * @param clusterId EmberAfClusterId
 * @param writeAttributeRecords int8u*
 * @param writeAttributeRecordsLen int8u
 */
#define emberAfFillCommandGlobalClientToServerWriteAttributesUndivided(clusterId,writeAttributeRecords,writeAttributeRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID,\
                            "b",\
                            writeAttributeRecords,\
                            writeAttributeRecordsLen\
                            );


/** @brief Command description for WriteAttributesResponse
 *
 * Command: WriteAttributesResponse
 * @param clusterId EmberAfClusterId
 * @param writeAttributeStatusRecords int8u*
 * @param writeAttributeStatusRecordsLen int8u
 */
#define emberAfFillCommandGlobalServerToClientWriteAttributesResponse(clusterId,writeAttributeStatusRecords,writeAttributeStatusRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID,\
                            "b",\
                            writeAttributeStatusRecords,\
                            writeAttributeStatusRecordsLen\
                            );


/** @brief Command description for WriteAttributesResponse
 *
 * Command: WriteAttributesResponse
 * @param clusterId EmberAfClusterId
 * @param writeAttributeStatusRecords int8u*
 * @param writeAttributeStatusRecordsLen int8u
 */
#define emberAfFillCommandGlobalClientToServerWriteAttributesResponse(clusterId,writeAttributeStatusRecords,writeAttributeStatusRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID,\
                            "b",\
                            writeAttributeStatusRecords,\
                            writeAttributeStatusRecordsLen\
                            );


/** @brief Command description for WriteAttributesNoResponse
 *
 * Command: WriteAttributesNoResponse
 * @param clusterId EmberAfClusterId
 * @param writeAttributeRecords int8u*
 * @param writeAttributeRecordsLen int8u
 */
#define emberAfFillCommandGlobalServerToClientWriteAttributesNoResponse(clusterId,writeAttributeRecords,writeAttributeRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID,\
                            "b",\
                            writeAttributeRecords,\
                            writeAttributeRecordsLen\
                            );


/** @brief Command description for WriteAttributesNoResponse
 *
 * Command: WriteAttributesNoResponse
 * @param clusterId EmberAfClusterId
 * @param writeAttributeRecords int8u*
 * @param writeAttributeRecordsLen int8u
 */
#define emberAfFillCommandGlobalClientToServerWriteAttributesNoResponse(clusterId,writeAttributeRecords,writeAttributeRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID,\
                            "b",\
                            writeAttributeRecords,\
                            writeAttributeRecordsLen\
                            );


/** @brief Command description for ConfigureReporting
 *
 * Command: ConfigureReporting
 * @param clusterId EmberAfClusterId
 * @param configureReportingRecords int8u*
 * @param configureReportingRecordsLen int8u
 */
#define emberAfFillCommandGlobalServerToClientConfigureReporting(clusterId,configureReportingRecords,configureReportingRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_CONFIGURE_REPORTING_COMMAND_ID,\
                            "b",\
                            configureReportingRecords,\
                            configureReportingRecordsLen\
                            );


/** @brief Command description for ConfigureReporting
 *
 * Command: ConfigureReporting
 * @param clusterId EmberAfClusterId
 * @param configureReportingRecords int8u*
 * @param configureReportingRecordsLen int8u
 */
#define emberAfFillCommandGlobalClientToServerConfigureReporting(clusterId,configureReportingRecords,configureReportingRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_CONFIGURE_REPORTING_COMMAND_ID,\
                            "b",\
                            configureReportingRecords,\
                            configureReportingRecordsLen\
                            );


/** @brief Command description for ConfigureReportingResponse
 *
 * Command: ConfigureReportingResponse
 * @param clusterId EmberAfClusterId
 * @param configureReportingStatusRecords int8u*
 * @param configureReportingStatusRecordsLen int8u
 */
#define emberAfFillCommandGlobalServerToClientConfigureReportingResponse(clusterId,configureReportingStatusRecords,configureReportingStatusRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_CONFIGURE_REPORTING_RESPONSE_COMMAND_ID,\
                            "b",\
                            configureReportingStatusRecords,\
                            configureReportingStatusRecordsLen\
                            );


/** @brief Command description for ConfigureReportingResponse
 *
 * Command: ConfigureReportingResponse
 * @param clusterId EmberAfClusterId
 * @param configureReportingStatusRecords int8u*
 * @param configureReportingStatusRecordsLen int8u
 */
#define emberAfFillCommandGlobalClientToServerConfigureReportingResponse(clusterId,configureReportingStatusRecords,configureReportingStatusRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_CONFIGURE_REPORTING_RESPONSE_COMMAND_ID,\
                            "b",\
                            configureReportingStatusRecords,\
                            configureReportingStatusRecordsLen\
                            );


/** @brief Command description for ReadReportingConfiguration
 *
 * Command: ReadReportingConfiguration
 * @param clusterId EmberAfClusterId
 * @param readReportingConfigurationAttributeRecords int8u*
 * @param readReportingConfigurationAttributeRecordsLen int8u
 */
#define emberAfFillCommandGlobalServerToClientReadReportingConfiguration(clusterId,readReportingConfigurationAttributeRecords,readReportingConfigurationAttributeRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_READ_REPORTING_CONFIGURATION_COMMAND_ID,\
                            "b",\
                            readReportingConfigurationAttributeRecords,\
                            readReportingConfigurationAttributeRecordsLen\
                            );


/** @brief Command description for ReadReportingConfiguration
 *
 * Command: ReadReportingConfiguration
 * @param clusterId EmberAfClusterId
 * @param readReportingConfigurationAttributeRecords int8u*
 * @param readReportingConfigurationAttributeRecordsLen int8u
 */
#define emberAfFillCommandGlobalClientToServerReadReportingConfiguration(clusterId,readReportingConfigurationAttributeRecords,readReportingConfigurationAttributeRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_READ_REPORTING_CONFIGURATION_COMMAND_ID,\
                            "b",\
                            readReportingConfigurationAttributeRecords,\
                            readReportingConfigurationAttributeRecordsLen\
                            );


/** @brief Command description for ReadReportingConfigurationResponse
 *
 * Command: ReadReportingConfigurationResponse
 * @param clusterId EmberAfClusterId
 * @param readReportingConfigurationRecords int8u*
 * @param readReportingConfigurationRecordsLen int8u
 */
#define emberAfFillCommandGlobalServerToClientReadReportingConfigurationResponse(clusterId,readReportingConfigurationRecords,readReportingConfigurationRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_READ_REPORTING_CONFIGURATION_RESPONSE_COMMAND_ID,\
                            "b",\
                            readReportingConfigurationRecords,\
                            readReportingConfigurationRecordsLen\
                            );


/** @brief Command description for ReadReportingConfigurationResponse
 *
 * Command: ReadReportingConfigurationResponse
 * @param clusterId EmberAfClusterId
 * @param readReportingConfigurationRecords int8u*
 * @param readReportingConfigurationRecordsLen int8u
 */
#define emberAfFillCommandGlobalClientToServerReadReportingConfigurationResponse(clusterId,readReportingConfigurationRecords,readReportingConfigurationRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_READ_REPORTING_CONFIGURATION_RESPONSE_COMMAND_ID,\
                            "b",\
                            readReportingConfigurationRecords,\
                            readReportingConfigurationRecordsLen\
                            );


/** @brief Command description for ReportAttributes
 *
 * Command: ReportAttributes
 * @param clusterId EmberAfClusterId
 * @param reportAttributeRecords int8u*
 * @param reportAttributeRecordsLen int8u
 */
#define emberAfFillCommandGlobalServerToClientReportAttributes(clusterId,reportAttributeRecords,reportAttributeRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_REPORT_ATTRIBUTES_COMMAND_ID,\
                            "b",\
                            reportAttributeRecords,\
                            reportAttributeRecordsLen\
                            );


/** @brief Command description for ReportAttributes
 *
 * Command: ReportAttributes
 * @param clusterId EmberAfClusterId
 * @param reportAttributeRecords int8u*
 * @param reportAttributeRecordsLen int8u
 */
#define emberAfFillCommandGlobalClientToServerReportAttributes(clusterId,reportAttributeRecords,reportAttributeRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_REPORT_ATTRIBUTES_COMMAND_ID,\
                            "b",\
                            reportAttributeRecords,\
                            reportAttributeRecordsLen\
                            );


/** @brief Command description for DefaultResponse
 *
 * Command: DefaultResponse
 * @param clusterId EmberAfClusterId
 * @param commandId int8u
 * @param status int8u
 */
#define emberAfFillCommandGlobalServerToClientDefaultResponse(clusterId,commandId,status) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_DEFAULT_RESPONSE_COMMAND_ID,\
                            "uu",\
                            commandId,\
                            status\
                            );


/** @brief Command description for DefaultResponse
 *
 * Command: DefaultResponse
 * @param clusterId EmberAfClusterId
 * @param commandId int8u
 * @param status int8u
 */
#define emberAfFillCommandGlobalClientToServerDefaultResponse(clusterId,commandId,status) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_DEFAULT_RESPONSE_COMMAND_ID,\
                            "uu",\
                            commandId,\
                            status\
                            );


/** @brief Command description for DiscoverAttributes
 *
 * Command: DiscoverAttributes
 * @param clusterId EmberAfClusterId
 * @param startId int16u
 * @param maxAttributeIds int8u
 */
#define emberAfFillCommandGlobalServerToClientDiscoverAttributes(clusterId,startId,maxAttributeIds) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID,\
                            "vu",\
                            startId,\
                            maxAttributeIds\
                            );


/** @brief Command description for DiscoverAttributes
 *
 * Command: DiscoverAttributes
 * @param clusterId EmberAfClusterId
 * @param startId int16u
 * @param maxAttributeIds int8u
 */
#define emberAfFillCommandGlobalClientToServerDiscoverAttributes(clusterId,startId,maxAttributeIds) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID,\
                            "vu",\
                            startId,\
                            maxAttributeIds\
                            );


/** @brief Command description for DiscoverAttributesResponse
 *
 * Command: DiscoverAttributesResponse
 * @param clusterId EmberAfClusterId
 * @param discoveryComplete int8u
 * @param discoverAttributesInfoRecords int8u*
 * @param discoverAttributesInfoRecordsLen int8u
 */
#define emberAfFillCommandGlobalServerToClientDiscoverAttributesResponse(clusterId,discoveryComplete,discoverAttributesInfoRecords,discoverAttributesInfoRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            clusterId,\
                            ZCL_DISCOVER_ATTRIBUTES_RESPONSE_COMMAND_ID,\
                            "ub",\
                            discoveryComplete,\
                            discoverAttributesInfoRecords,\
                            discoverAttributesInfoRecordsLen\
                            );


/** @brief Command description for DiscoverAttributesResponse
 *
 * Command: DiscoverAttributesResponse
 * @param clusterId EmberAfClusterId
 * @param discoveryComplete int8u
 * @param discoverAttributesInfoRecords int8u*
 * @param discoverAttributesInfoRecordsLen int8u
 */
#define emberAfFillCommandGlobalClientToServerDiscoverAttributesResponse(clusterId,discoveryComplete,discoverAttributesInfoRecords,discoverAttributesInfoRecordsLen) \
  emberAfFillExternalBuffer(ZCL_PROFILE_WIDE_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            clusterId,\
                            ZCL_DISCOVER_ATTRIBUTES_RESPONSE_COMMAND_ID,\
                            "ub",\
                            discoveryComplete,\
                            discoverAttributesInfoRecords,\
                            discoverAttributesInfoRecordsLen\
                            );


/** @} END Global Commands */



/** @name Basic Commands */
// @{
/** @brief Command that resets all attribute values to factory default.
 *
 * Cluster: Basic, Attributes for determining basic information about a device, setting user device information such as location, and enabling a device.
 * Command: ResetToFactoryDefaults
 */
#define emberAfFillCommandBasicClusterResetToFactoryDefaults() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_BASIC_CLUSTER_ID,\
                            ZCL_RESET_TO_FACTORY_DEFAULTS_COMMAND_ID,\
                            ""\
                            );


/** @} END Basic Commands */


/** @name Power Configuration Commands */
// @{
/** @} END Power Configuration Commands */


/** @name Device Temperature Configuration Commands */
// @{
/** @} END Device Temperature Configuration Commands */


/** @name Identify Commands */
// @{
/** @brief Command description for Identify
 *
 * Cluster: Identify, Attributes and commands for putting a device into Identification mode (e.g. flashing a light).
 * Command: Identify
 * @param identifyTime int16u
 */
#define emberAfFillCommandIdentifyClusterIdentify(identifyTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_IDENTIFY_CLUSTER_ID,\
                            ZCL_IDENTIFY_COMMAND_ID,\
                            "v",\
                            identifyTime\
                            );


/** @brief Command description for IdentifyQuery
 *
 * Cluster: Identify, Attributes and commands for putting a device into Identification mode (e.g. flashing a light).
 * Command: IdentifyQuery
 */
#define emberAfFillCommandIdentifyClusterIdentifyQuery() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_IDENTIFY_CLUSTER_ID,\
                            ZCL_IDENTIFY_QUERY_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for IdentifyQueryResponse
 *
 * Cluster: Identify, Attributes and commands for putting a device into Identification mode (e.g. flashing a light).
 * Command: IdentifyQueryResponse
 * @param timeout int16u
 */
#define emberAfFillCommandIdentifyClusterIdentifyQueryResponse(timeout) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_IDENTIFY_CLUSTER_ID,\
                            ZCL_IDENTIFY_QUERY_RESPONSE_COMMAND_ID,\
                            "v",\
                            timeout\
                            );


/** @} END Identify Commands */


/** @name Groups Commands */
// @{
/** @brief Command description for AddGroup
 *
 * Cluster: Groups, Attributes and commands for group configuration and manipulation.
 * Command: AddGroup
 * @param groupId int16u
 * @param groupName int8u*
 */
#define emberAfFillCommandGroupsClusterAddGroup(groupId,groupName) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_GROUPS_CLUSTER_ID,\
                            ZCL_ADD_GROUP_COMMAND_ID,\
                            "vs",\
                            groupId,\
                            groupName\
                            );


/** @brief Command description for ViewGroup
 *
 * Cluster: Groups, Attributes and commands for group configuration and manipulation.
 * Command: ViewGroup
 * @param groupId int16u
 */
#define emberAfFillCommandGroupsClusterViewGroup(groupId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_GROUPS_CLUSTER_ID,\
                            ZCL_VIEW_GROUP_COMMAND_ID,\
                            "v",\
                            groupId\
                            );


/** @brief Command description for GetGroupMembership
 *
 * Cluster: Groups, Attributes and commands for group configuration and manipulation.
 * Command: GetGroupMembership
 * @param groupCount int8u
 * @param groupList int8u*
 * @param groupListLen int8u
 */
#define emberAfFillCommandGroupsClusterGetGroupMembership(groupCount,groupList,groupListLen) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_GROUPS_CLUSTER_ID,\
                            ZCL_GET_GROUP_MEMBERSHIP_COMMAND_ID,\
                            "ub",\
                            groupCount,\
                            groupList,\
                            groupListLen\
                            );


/** @brief Command description for RemoveGroup
 *
 * Cluster: Groups, Attributes and commands for group configuration and manipulation.
 * Command: RemoveGroup
 * @param groupId int16u
 */
#define emberAfFillCommandGroupsClusterRemoveGroup(groupId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_GROUPS_CLUSTER_ID,\
                            ZCL_REMOVE_GROUP_COMMAND_ID,\
                            "v",\
                            groupId\
                            );


/** @brief Command description for RemoveAllGroups
 *
 * Cluster: Groups, Attributes and commands for group configuration and manipulation.
 * Command: RemoveAllGroups
 */
#define emberAfFillCommandGroupsClusterRemoveAllGroups() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_GROUPS_CLUSTER_ID,\
                            ZCL_REMOVE_ALL_GROUPS_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for AddGroupIfIdentifying
 *
 * Cluster: Groups, Attributes and commands for group configuration and manipulation.
 * Command: AddGroupIfIdentifying
 * @param groupId int16u
 * @param groupName int8u*
 */
#define emberAfFillCommandGroupsClusterAddGroupIfIdentifying(groupId,groupName) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_GROUPS_CLUSTER_ID,\
                            ZCL_ADD_GROUP_IF_IDENTIFYING_COMMAND_ID,\
                            "vs",\
                            groupId,\
                            groupName\
                            );


/** @brief Command description for AddGroupResponse
 *
 * Cluster: Groups, Attributes and commands for group configuration and manipulation.
 * Command: AddGroupResponse
 * @param status int8u
 * @param groupId int16u
 */
#define emberAfFillCommandGroupsClusterAddGroupResponse(status,groupId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_GROUPS_CLUSTER_ID,\
                            ZCL_ADD_GROUP_RESPONSE_COMMAND_ID,\
                            "uv",\
                            status,\
                            groupId\
                            );


/** @brief Command description for ViewGroupResponse
 *
 * Cluster: Groups, Attributes and commands for group configuration and manipulation.
 * Command: ViewGroupResponse
 * @param status int8u
 * @param groupId int16u
 * @param groupName int8u*
 */
#define emberAfFillCommandGroupsClusterViewGroupResponse(status,groupId,groupName) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_GROUPS_CLUSTER_ID,\
                            ZCL_VIEW_GROUP_RESPONSE_COMMAND_ID,\
                            "uvs",\
                            status,\
                            groupId,\
                            groupName\
                            );


/** @brief Command description for GetGroupMembershipResponse
 *
 * Cluster: Groups, Attributes and commands for group configuration and manipulation.
 * Command: GetGroupMembershipResponse
 * @param capacity int8u
 * @param groupCount int8u
 * @param groupList int8u*
 * @param groupListLen int8u
 */
#define emberAfFillCommandGroupsClusterGetGroupMembershipResponse(capacity,groupCount,groupList,groupListLen) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_GROUPS_CLUSTER_ID,\
                            ZCL_GET_GROUP_MEMBERSHIP_RESPONSE_COMMAND_ID,\
                            "uub",\
                            capacity,\
                            groupCount,\
                            groupList,\
                            groupListLen\
                            );


/** @brief Command description for RemoveGroupResponse
 *
 * Cluster: Groups, Attributes and commands for group configuration and manipulation.
 * Command: RemoveGroupResponse
 * @param status int8u
 * @param groupId int16u
 */
#define emberAfFillCommandGroupsClusterRemoveGroupResponse(status,groupId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_GROUPS_CLUSTER_ID,\
                            ZCL_REMOVE_GROUP_RESPONSE_COMMAND_ID,\
                            "uv",\
                            status,\
                            groupId\
                            );


/** @} END Groups Commands */


/** @name Scenes Commands */
// @{
/** @brief Command description for AddScene
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: AddScene
 * @param groupId int16u
 * @param sceneId int8u
 * @param transitionTime int16u
 * @param sceneName int8u*
 * @param extensionFieldSets int8u*
 * @param extensionFieldSetsLen int8u
 */
#define emberAfFillCommandScenesClusterAddScene(groupId,sceneId,transitionTime,sceneName,extensionFieldSets,extensionFieldSetsLen) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_ADD_SCENE_COMMAND_ID,\
                            "vuvsb",\
                            groupId,\
                            sceneId,\
                            transitionTime,\
                            sceneName,\
                            extensionFieldSets,\
                            extensionFieldSetsLen\
                            );


/** @brief Command description for ViewScene
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: ViewScene
 * @param groupId int16u
 * @param sceneId int8u
 */
#define emberAfFillCommandScenesClusterViewScene(groupId,sceneId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_VIEW_SCENE_COMMAND_ID,\
                            "vu",\
                            groupId,\
                            sceneId\
                            );


/** @brief Command description for RemoveScene
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: RemoveScene
 * @param groupId int16u
 * @param sceneId int8u
 */
#define emberAfFillCommandScenesClusterRemoveScene(groupId,sceneId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_REMOVE_SCENE_COMMAND_ID,\
                            "vu",\
                            groupId,\
                            sceneId\
                            );


/** @brief Command description for RemoveAllScenes
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: RemoveAllScenes
 * @param groupId int16u
 */
#define emberAfFillCommandScenesClusterRemoveAllScenes(groupId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_REMOVE_ALL_SCENES_COMMAND_ID,\
                            "v",\
                            groupId\
                            );


/** @brief Command description for StoreScene
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: StoreScene
 * @param groupId int16u
 * @param sceneId int8u
 */
#define emberAfFillCommandScenesClusterStoreScene(groupId,sceneId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_STORE_SCENE_COMMAND_ID,\
                            "vu",\
                            groupId,\
                            sceneId\
                            );


/** @brief Command description for RecallScene
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: RecallScene
 * @param groupId int16u
 * @param sceneId int8u
 */
#define emberAfFillCommandScenesClusterRecallScene(groupId,sceneId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_RECALL_SCENE_COMMAND_ID,\
                            "vu",\
                            groupId,\
                            sceneId\
                            );


/** @brief Command description for GetSceneMembership
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: GetSceneMembership
 * @param groupId int16u
 */
#define emberAfFillCommandScenesClusterGetSceneMembership(groupId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_GET_SCENE_MEMBERSHIP_COMMAND_ID,\
                            "v",\
                            groupId\
                            );


/** @brief Command description for AddSceneResponse
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: AddSceneResponse
 * @param status int8u
 * @param groupId int16u
 * @param sceneId int8u
 */
#define emberAfFillCommandScenesClusterAddSceneResponse(status,groupId,sceneId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_ADD_SCENE_RESPONSE_COMMAND_ID,\
                            "uvu",\
                            status,\
                            groupId,\
                            sceneId\
                            );


/** @brief Command description for ViewSceneResponse
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: ViewSceneResponse
 * @param status int8u
 * @param groupId int16u
 * @param sceneId int8u
 * @param transitionTime int16u
 * @param sceneName int8u*
 * @param extensionFieldSets int8u*
 * @param extensionFieldSetsLen int8u
 */
#define emberAfFillCommandScenesClusterViewSceneResponse(status,groupId,sceneId,transitionTime,sceneName,extensionFieldSets,extensionFieldSetsLen) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_VIEW_SCENE_RESPONSE_COMMAND_ID,\
                            "uvuvsb",\
                            status,\
                            groupId,\
                            sceneId,\
                            transitionTime,\
                            sceneName,\
                            extensionFieldSets,\
                            extensionFieldSetsLen\
                            );


/** @brief Command description for RemoveSceneResponse
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: RemoveSceneResponse
 * @param status int8u
 * @param groupId int16u
 * @param sceneId int8u
 */
#define emberAfFillCommandScenesClusterRemoveSceneResponse(status,groupId,sceneId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_REMOVE_SCENE_RESPONSE_COMMAND_ID,\
                            "uvu",\
                            status,\
                            groupId,\
                            sceneId\
                            );


/** @brief Command description for RemoveAllScenesResponse
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: RemoveAllScenesResponse
 * @param status int8u
 * @param groupId int16u
 */
#define emberAfFillCommandScenesClusterRemoveAllScenesResponse(status,groupId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_REMOVE_ALL_SCENES_RESPONSE_COMMAND_ID,\
                            "uv",\
                            status,\
                            groupId\
                            );


/** @brief Command description for StoreSceneResponse
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: StoreSceneResponse
 * @param status int8u
 * @param groupId int16u
 * @param sceneId int8u
 */
#define emberAfFillCommandScenesClusterStoreSceneResponse(status,groupId,sceneId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_STORE_SCENE_RESPONSE_COMMAND_ID,\
                            "uvu",\
                            status,\
                            groupId,\
                            sceneId\
                            );


/** @brief Command description for GetSceneMembershipResponse
 *
 * Cluster: Scenes, Attributes and commands for scene configuration and manipulation.
 * Command: GetSceneMembershipResponse
 * @param status int8u
 * @param capacity int8u
 * @param groupId int16u
 * @param sceneCount int8u
 * @param sceneList int8u*
 * @param sceneListLen int8u
 */
#define emberAfFillCommandScenesClusterGetSceneMembershipResponse(status,capacity,groupId,sceneCount,sceneList,sceneListLen) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_SCENES_CLUSTER_ID,\
                            ZCL_GET_SCENE_MEMBERSHIP_RESPONSE_COMMAND_ID,\
                            "uuvub",\
                            status,\
                            capacity,\
                            groupId,\
                            sceneCount,\
                            sceneList,\
                            sceneListLen\
                            );


/** @} END Scenes Commands */


/** @name On/off Commands */
// @{
/** @brief Command description for Off
 *
 * Cluster: On/off, Attributes and commands for switching devices between 'On' and 'Off' states.
 * Command: Off
 */
#define emberAfFillCommandOnOffClusterOff() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_ON_OFF_CLUSTER_ID,\
                            ZCL_OFF_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for On
 *
 * Cluster: On/off, Attributes and commands for switching devices between 'On' and 'Off' states.
 * Command: On
 */
#define emberAfFillCommandOnOffClusterOn() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_ON_OFF_CLUSTER_ID,\
                            ZCL_ON_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for Toggle
 *
 * Cluster: On/off, Attributes and commands for switching devices between 'On' and 'Off' states.
 * Command: Toggle
 */
#define emberAfFillCommandOnOffClusterToggle() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_ON_OFF_CLUSTER_ID,\
                            ZCL_TOGGLE_COMMAND_ID,\
                            ""\
                            );


/** @brief Client command that turns the device off with a transition given
        by the transition time in the Ember Sample transition time attribute.
 *
 * Cluster: On/off, Attributes and commands for switching devices between 'On' and 'Off' states.
 * Command: SampleMfgSpecificOffWithTransition
 */
#define emberAfFillCommandOnOffClusterSampleMfgSpecificOffWithTransition() \
  emberAfFillExternalManufacturerSpecificBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_ON_OFF_CLUSTER_ID,\
                            0x1002,\
                            ZCL_SAMPLE_MFG_SPECIFIC_OFF_WITH_TRANSITION_COMMAND_ID,\
                            ""\
                            );


/** @brief Client command that turns the device on with a transition given
        by the transition time in the Ember Sample transition time attribute.
 *
 * Cluster: On/off, Attributes and commands for switching devices between 'On' and 'Off' states.
 * Command: SampleMfgSpecificOnWithTransition
 */
#define emberAfFillCommandOnOffClusterSampleMfgSpecificOnWithTransition() \
  emberAfFillExternalManufacturerSpecificBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_ON_OFF_CLUSTER_ID,\
                            0x1002,\
                            ZCL_SAMPLE_MFG_SPECIFIC_ON_WITH_TRANSITION_COMMAND_ID,\
                            ""\
                            );


/** @brief Client command that toggles the device with a transition given
        by the transition time in the Ember Sample transition time attribute.
 *
 * Cluster: On/off, Attributes and commands for switching devices between 'On' and 'Off' states.
 * Command: SampleMfgSpecificToggleWithTransition
 */
#define emberAfFillCommandOnOffClusterSampleMfgSpecificToggleWithTransition() \
  emberAfFillExternalManufacturerSpecificBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_ON_OFF_CLUSTER_ID,\
                            0x1002,\
                            ZCL_SAMPLE_MFG_SPECIFIC_TOGGLE_WITH_TRANSITION_COMMAND_ID,\
                            ""\
                            );


/** @} END On/off Commands */


/** @name On/off Switch Configuration Commands */
// @{
/** @} END On/off Switch Configuration Commands */


/** @name Level Control Commands */
// @{
/** @brief Command description for MoveToLevel
 *
 * Cluster: Level Control, Attributes and commands for controlling devices that can be set to a level between fully 'On' and fully 'Off.'
 * Command: MoveToLevel
 * @param level int8u
 * @param transitionTime int16u
 */
#define emberAfFillCommandLevelControlClusterMoveToLevel(level,transitionTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_LEVEL_CONTROL_CLUSTER_ID,\
                            ZCL_MOVE_TO_LEVEL_COMMAND_ID,\
                            "uv",\
                            level,\
                            transitionTime\
                            );


/** @brief Command description for Move
 *
 * Cluster: Level Control, Attributes and commands for controlling devices that can be set to a level between fully 'On' and fully 'Off.'
 * Command: Move
 * @param moveMode int8u
 * @param rate int8u
 */
#define emberAfFillCommandLevelControlClusterMove(moveMode,rate) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_LEVEL_CONTROL_CLUSTER_ID,\
                            ZCL_MOVE_COMMAND_ID,\
                            "uu",\
                            moveMode,\
                            rate\
                            );


/** @brief Command description for Step
 *
 * Cluster: Level Control, Attributes and commands for controlling devices that can be set to a level between fully 'On' and fully 'Off.'
 * Command: Step
 * @param stepMode int8u
 * @param stepSize int8u
 * @param transitionTime int16u
 */
#define emberAfFillCommandLevelControlClusterStep(stepMode,stepSize,transitionTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_LEVEL_CONTROL_CLUSTER_ID,\
                            ZCL_STEP_COMMAND_ID,\
                            "uuv",\
                            stepMode,\
                            stepSize,\
                            transitionTime\
                            );


/** @brief Command description for Stop
 *
 * Cluster: Level Control, Attributes and commands for controlling devices that can be set to a level between fully 'On' and fully 'Off.'
 * Command: Stop
 */
#define emberAfFillCommandLevelControlClusterStop() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_LEVEL_CONTROL_CLUSTER_ID,\
                            ZCL_STOP_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for MoveToLevelWithOnOff
 *
 * Cluster: Level Control, Attributes and commands for controlling devices that can be set to a level between fully 'On' and fully 'Off.'
 * Command: MoveToLevelWithOnOff
 * @param level int8u
 * @param transitionTime int16u
 */
#define emberAfFillCommandLevelControlClusterMoveToLevelWithOnOff(level,transitionTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_LEVEL_CONTROL_CLUSTER_ID,\
                            ZCL_MOVE_TO_LEVEL_WITH_ON_OFF_COMMAND_ID,\
                            "uv",\
                            level,\
                            transitionTime\
                            );


/** @brief Command description for MoveWithOnOff
 *
 * Cluster: Level Control, Attributes and commands for controlling devices that can be set to a level between fully 'On' and fully 'Off.'
 * Command: MoveWithOnOff
 * @param moveMode int8u
 * @param rate int8u
 */
#define emberAfFillCommandLevelControlClusterMoveWithOnOff(moveMode,rate) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_LEVEL_CONTROL_CLUSTER_ID,\
                            ZCL_MOVE_WITH_ON_OFF_COMMAND_ID,\
                            "uu",\
                            moveMode,\
                            rate\
                            );


/** @brief Command description for StepWithOnOff
 *
 * Cluster: Level Control, Attributes and commands for controlling devices that can be set to a level between fully 'On' and fully 'Off.'
 * Command: StepWithOnOff
 * @param stepMode int8u
 * @param stepSize int8u
 * @param transitionTime int16u
 */
#define emberAfFillCommandLevelControlClusterStepWithOnOff(stepMode,stepSize,transitionTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_LEVEL_CONTROL_CLUSTER_ID,\
                            ZCL_STEP_WITH_ON_OFF_COMMAND_ID,\
                            "uuv",\
                            stepMode,\
                            stepSize,\
                            transitionTime\
                            );


/** @brief Command description for StopWithOnOff
 *
 * Cluster: Level Control, Attributes and commands for controlling devices that can be set to a level between fully 'On' and fully 'Off.'
 * Command: StopWithOnOff
 */
#define emberAfFillCommandLevelControlClusterStopWithOnOff() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_LEVEL_CONTROL_CLUSTER_ID,\
                            ZCL_STOP_WITH_ON_OFF_COMMAND_ID,\
                            ""\
                            );


/** @} END Level Control Commands */


/** @name Alarms Commands */
// @{
/** @brief Command description for ResetAlarm
 *
 * Cluster: Alarms, Attributes and commands for sending notifications and configuring alarm functionality.
 * Command: ResetAlarm
 * @param alarmCode int8u
 * @param clusterId int16u
 */
#define emberAfFillCommandAlarmClusterResetAlarm(alarmCode,clusterId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_ALARM_CLUSTER_ID,\
                            ZCL_RESET_ALARM_COMMAND_ID,\
                            "uv",\
                            alarmCode,\
                            clusterId\
                            );


/** @brief Command description for ResetAllAlarms
 *
 * Cluster: Alarms, Attributes and commands for sending notifications and configuring alarm functionality.
 * Command: ResetAllAlarms
 */
#define emberAfFillCommandAlarmClusterResetAllAlarms() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_ALARM_CLUSTER_ID,\
                            ZCL_RESET_ALL_ALARMS_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for GetAlarm
 *
 * Cluster: Alarms, Attributes and commands for sending notifications and configuring alarm functionality.
 * Command: GetAlarm
 */
#define emberAfFillCommandAlarmClusterGetAlarm() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_ALARM_CLUSTER_ID,\
                            ZCL_GET_ALARM_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for ResetAlarmLog
 *
 * Cluster: Alarms, Attributes and commands for sending notifications and configuring alarm functionality.
 * Command: ResetAlarmLog
 */
#define emberAfFillCommandAlarmClusterResetAlarmLog() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_ALARM_CLUSTER_ID,\
                            ZCL_RESET_ALARM_LOG_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for Alarm
 *
 * Cluster: Alarms, Attributes and commands for sending notifications and configuring alarm functionality.
 * Command: Alarm
 * @param alarmCode int8u
 * @param clusterId int16u
 */
#define emberAfFillCommandAlarmClusterAlarm(alarmCode,clusterId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_ALARM_CLUSTER_ID,\
                            ZCL_ALARM_COMMAND_ID,\
                            "uv",\
                            alarmCode,\
                            clusterId\
                            );


/** @brief Command description for GetAlarmResponse
 *
 * Cluster: Alarms, Attributes and commands for sending notifications and configuring alarm functionality.
 * Command: GetAlarmResponse
 * @param status int8u
 * @param alarmCode int8u
 * @param clusterId int16u
 * @param timeStamp int32u
 */
#define emberAfFillCommandAlarmClusterGetAlarmResponse(status,alarmCode,clusterId,timeStamp) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_ALARM_CLUSTER_ID,\
                            ZCL_GET_ALARM_RESPONSE_COMMAND_ID,\
                            "uuvw",\
                            status,\
                            alarmCode,\
                            clusterId,\
                            timeStamp\
                            );


/** @} END Alarms Commands */


/** @name Time Commands */
// @{
/** @} END Time Commands */


/** @name RSSI Location Commands */
// @{
/** @brief Command description for SetAbsoluteLocation
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: SetAbsoluteLocation
 * @param coordinate1 int16s
 * @param coordinate2 int16s
 * @param coordinate3 int16s
 * @param power int16s
 * @param pathLossExponent int16u
 */
#define emberAfFillCommandRssiLocationClusterSetAbsoluteLocation(coordinate1,coordinate2,coordinate3,power,pathLossExponent) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_SET_ABSOLUTE_LOCATION_COMMAND_ID,\
                            "vvvvv",\
                            coordinate1,\
                            coordinate2,\
                            coordinate3,\
                            power,\
                            pathLossExponent\
                            );


/** @brief Command description for SetDeviceConfiguration
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: SetDeviceConfiguration
 * @param power int16s
 * @param pathLossExponent int16u
 * @param calculationPeriod int16u
 * @param numberRssiMeasurements int8u
 * @param reportingPeriod int16u
 */
#define emberAfFillCommandRssiLocationClusterSetDeviceConfiguration(power,pathLossExponent,calculationPeriod,numberRssiMeasurements,reportingPeriod) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_SET_DEVICE_CONFIGURATION_COMMAND_ID,\
                            "vvvuv",\
                            power,\
                            pathLossExponent,\
                            calculationPeriod,\
                            numberRssiMeasurements,\
                            reportingPeriod\
                            );


/** @brief Command description for GetDeviceConfiguration
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: GetDeviceConfiguration
 * @param targetAddress int8u*
 */
#define emberAfFillCommandRssiLocationClusterGetDeviceConfiguration(targetAddress) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_GET_DEVICE_CONFIGURATION_COMMAND_ID,\
                            "8",\
                            targetAddress\
                            );


/** @brief Command description for GetLocationData
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: GetLocationData
 * @param flags int8u
 * @param numberResponses int8u
 * @param targetAddress int8u*
 */
#define emberAfFillCommandRssiLocationClusterGetLocationData(flags,numberResponses,targetAddress) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_GET_LOCATION_DATA_COMMAND_ID,\
                            "uu8",\
                            flags,\
                            numberResponses,\
                            targetAddress\
                            );


/** @brief 
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: RssiResponse
 * @param replyingDevice int8u*
 * @param coordinate1 int16s
 * @param coordinate2 int16s
 * @param coordinate3 int16s
 * @param rssi int8s
 * @param numberRssiMeasurements int8u
 */
#define emberAfFillCommandRssiLocationClusterRssiResponse(replyingDevice,coordinate1,coordinate2,coordinate3,rssi,numberRssiMeasurements) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_RSSI_RESPONSE_COMMAND_ID,\
                            "8vvvuu",\
                            replyingDevice,\
                            coordinate1,\
                            coordinate2,\
                            coordinate3,\
                            rssi,\
                            numberRssiMeasurements\
                            );


/** @brief Command description for SendPings
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: SendPings
 * @param targetAddress int8u*
 * @param numberRssiMeasurements int8u
 * @param calculationPeriod int16u
 */
#define emberAfFillCommandRssiLocationClusterSendPings(targetAddress,numberRssiMeasurements,calculationPeriod) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_SEND_PINGS_COMMAND_ID,\
                            "8uv",\
                            targetAddress,\
                            numberRssiMeasurements,\
                            calculationPeriod\
                            );


/** @brief Command description for AnchorNodeAnnounce
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: AnchorNodeAnnounce
 * @param anchorNodeIeeeAddress int8u*
 * @param coordinate1 int16s
 * @param coordinate2 int16s
 * @param coordinate3 int16s
 */
#define emberAfFillCommandRssiLocationClusterAnchorNodeAnnounce(anchorNodeIeeeAddress,coordinate1,coordinate2,coordinate3) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_ANCHOR_NODE_ANNOUNCE_COMMAND_ID,\
                            "8vvv",\
                            anchorNodeIeeeAddress,\
                            coordinate1,\
                            coordinate2,\
                            coordinate3\
                            );


/** @brief Command description for DeviceConfigurationResponse
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: DeviceConfigurationResponse
 * @param status int8u
 * @param power int16s
 * @param pathLossExponent int16u
 * @param calculationPeriod int16u
 * @param numberRssiMeasurements int8u
 * @param reportingPeriod int16u
 */
#define emberAfFillCommandRssiLocationClusterDeviceConfigurationResponse(status,power,pathLossExponent,calculationPeriod,numberRssiMeasurements,reportingPeriod) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_DEVICE_CONFIGURATION_RESPONSE_COMMAND_ID,\
                            "uvvvuv",\
                            status,\
                            power,\
                            pathLossExponent,\
                            calculationPeriod,\
                            numberRssiMeasurements,\
                            reportingPeriod\
                            );


/** @brief Command description for LocationDataResponse
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: LocationDataResponse
 * @param status int8u
 * @param locationType int8u
 * @param coordinate1 int16s
 * @param coordinate2 int16s
 * @param coordinate3 int16s
 * @param power int16s
 * @param pathLossExponent int16u
 * @param locationMethod int8u
 * @param qualityMeasure int8u
 * @param locationAge int16u
 */
#define emberAfFillCommandRssiLocationClusterLocationDataResponse(status,locationType,coordinate1,coordinate2,coordinate3,power,pathLossExponent,locationMethod,qualityMeasure,locationAge) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_LOCATION_DATA_RESPONSE_COMMAND_ID,\
                            "uuvvvvvuuv",\
                            status,\
                            locationType,\
                            coordinate1,\
                            coordinate2,\
                            coordinate3,\
                            power,\
                            pathLossExponent,\
                            locationMethod,\
                            qualityMeasure,\
                            locationAge\
                            );


/** @brief Command description for LocationDataNotification
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: LocationDataNotification
 * @param locationType int8u
 * @param coordinate1 int16s
 * @param coordinate2 int16s
 * @param coordinate3 int16s
 * @param power int16s
 * @param pathLossExponent int16u
 * @param locationMethod int8u
 * @param qualityMeasure int8u
 * @param locationAge int16u
 */
#define emberAfFillCommandRssiLocationClusterLocationDataNotification(locationType,coordinate1,coordinate2,coordinate3,power,pathLossExponent,locationMethod,qualityMeasure,locationAge) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_LOCATION_DATA_NOTIFICATION_COMMAND_ID,\
                            "uvvvvvuuv",\
                            locationType,\
                            coordinate1,\
                            coordinate2,\
                            coordinate3,\
                            power,\
                            pathLossExponent,\
                            locationMethod,\
                            qualityMeasure,\
                            locationAge\
                            );


/** @brief Command description for CompactLocationDataNotification
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: CompactLocationDataNotification
 * @param locationType int8u
 * @param coordinate1 int16s
 * @param coordinate2 int16s
 * @param coordinate3 int16s
 * @param qualityMeasure int8u
 * @param locationAge int16u
 */
#define emberAfFillCommandRssiLocationClusterCompactLocationDataNotification(locationType,coordinate1,coordinate2,coordinate3,qualityMeasure,locationAge) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_COMPACT_LOCATION_DATA_NOTIFICATION_COMMAND_ID,\
                            "uvvvuv",\
                            locationType,\
                            coordinate1,\
                            coordinate2,\
                            coordinate3,\
                            qualityMeasure,\
                            locationAge\
                            );


/** @brief Command description for RssiPing
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: RssiPing
 * @param locationType int8u
 */
#define emberAfFillCommandRssiLocationClusterRssiPing(locationType) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_RSSI_PING_COMMAND_ID,\
                            "u",\
                            locationType\
                            );


/** @brief Command description for RssiRequest
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: RssiRequest
 */
#define emberAfFillCommandRssiLocationClusterRssiRequest() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_RSSI_REQUEST_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for ReportRssiMeasurements
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: ReportRssiMeasurements
 * @param measuringDevice int8u*
 * @param neighbors int8u
 * @param neighborsInfo int8u*
 * @param neighborsInfoLen int8u
 */
#define emberAfFillCommandRssiLocationClusterReportRssiMeasurements(measuringDevice,neighbors,neighborsInfo,neighborsInfoLen) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_REPORT_RSSI_MEASUREMENTS_COMMAND_ID,\
                            "8ub",\
                            measuringDevice,\
                            neighbors,\
                            neighborsInfo,\
                            neighborsInfoLen\
                            );


/** @brief Command description for RequestOwnLocation
 *
 * Cluster: RSSI Location, Attributes and commands that provide a means for exchanging location information and channel parameters among devices.
 * Command: RequestOwnLocation
 * @param blindNode int8u*
 */
#define emberAfFillCommandRssiLocationClusterRequestOwnLocation(blindNode) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_RSSI_LOCATION_CLUSTER_ID,\
                            ZCL_REQUEST_OWN_LOCATION_COMMAND_ID,\
                            "8",\
                            blindNode\
                            );


/** @} END RSSI Location Commands */


/** @name Binary Input (Basic) Commands */
// @{
/** @} END Binary Input (Basic) Commands */


/** @name Commissioning Commands */
// @{
/** @brief Command description for RestartDevice
 *
 * Cluster: Commissioning, Attributes and commands for commissioning and managing a ZigBee device.
 * Command: RestartDevice
 * @param options int8u
 * @param delay int8u
 * @param jitter int8u
 */
#define emberAfFillCommandCommissioningClusterRestartDevice(options,delay,jitter) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COMMISSIONING_CLUSTER_ID,\
                            ZCL_RESTART_DEVICE_COMMAND_ID,\
                            "uuu",\
                            options,\
                            delay,\
                            jitter\
                            );


/** @brief Command description for SaveStartupParameters
 *
 * Cluster: Commissioning, Attributes and commands for commissioning and managing a ZigBee device.
 * Command: SaveStartupParameters
 * @param options int8u
 * @param index int8u
 */
#define emberAfFillCommandCommissioningClusterSaveStartupParameters(options,index) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COMMISSIONING_CLUSTER_ID,\
                            ZCL_SAVE_STARTUP_PARAMETERS_COMMAND_ID,\
                            "uu",\
                            options,\
                            index\
                            );


/** @brief Command description for RestoreStartupParameters
 *
 * Cluster: Commissioning, Attributes and commands for commissioning and managing a ZigBee device.
 * Command: RestoreStartupParameters
 * @param options int8u
 * @param index int8u
 */
#define emberAfFillCommandCommissioningClusterRestoreStartupParameters(options,index) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COMMISSIONING_CLUSTER_ID,\
                            ZCL_RESTORE_STARTUP_PARAMETERS_COMMAND_ID,\
                            "uu",\
                            options,\
                            index\
                            );


/** @brief Command description for ResetStartupParameters
 *
 * Cluster: Commissioning, Attributes and commands for commissioning and managing a ZigBee device.
 * Command: ResetStartupParameters
 * @param options int8u
 * @param index int8u
 */
#define emberAfFillCommandCommissioningClusterResetStartupParameters(options,index) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COMMISSIONING_CLUSTER_ID,\
                            ZCL_RESET_STARTUP_PARAMETERS_COMMAND_ID,\
                            "uu",\
                            options,\
                            index\
                            );


/** @brief Command description for RestartDeviceResponse
 *
 * Cluster: Commissioning, Attributes and commands for commissioning and managing a ZigBee device.
 * Command: RestartDeviceResponse
 * @param status int8u
 */
#define emberAfFillCommandCommissioningClusterRestartDeviceResponse(status) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_COMMISSIONING_CLUSTER_ID,\
                            ZCL_RESTART_DEVICE_RESPONSE_COMMAND_ID,\
                            "u",\
                            status\
                            );


/** @brief Command description for SaveStartupParametersResponse
 *
 * Cluster: Commissioning, Attributes and commands for commissioning and managing a ZigBee device.
 * Command: SaveStartupParametersResponse
 * @param status int8u
 */
#define emberAfFillCommandCommissioningClusterSaveStartupParametersResponse(status) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_COMMISSIONING_CLUSTER_ID,\
                            ZCL_SAVE_STARTUP_PARAMETERS_RESPONSE_COMMAND_ID,\
                            "u",\
                            status\
                            );


/** @brief Command description for RestoreStartupParametersResponse
 *
 * Cluster: Commissioning, Attributes and commands for commissioning and managing a ZigBee device.
 * Command: RestoreStartupParametersResponse
 * @param status int8u
 */
#define emberAfFillCommandCommissioningClusterRestoreStartupParametersResponse(status) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_COMMISSIONING_CLUSTER_ID,\
                            ZCL_RESTORE_STARTUP_PARAMETERS_RESPONSE_COMMAND_ID,\
                            "u",\
                            status\
                            );


/** @brief Command description for ResetStartupParametersResponse
 *
 * Cluster: Commissioning, Attributes and commands for commissioning and managing a ZigBee device.
 * Command: ResetStartupParametersResponse
 * @param status int8u
 */
#define emberAfFillCommandCommissioningClusterResetStartupParametersResponse(status) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_COMMISSIONING_CLUSTER_ID,\
                            ZCL_RESET_STARTUP_PARAMETERS_RESPONSE_COMMAND_ID,\
                            "u",\
                            status\
                            );


/** @} END Commissioning Commands */


/** @name Shade Configuration Commands */
// @{
/** @} END Shade Configuration Commands */


/** @name Pump Configuration and Control Commands */
// @{
/** @} END Pump Configuration and Control Commands */


/** @name Thermostat Commands */
// @{
/** @brief Command description for SetpointRaiseLower
 *
 * Cluster: Thermostat, An interface for configuring and controlling the functionality of a thermostat.
 * Command: SetpointRaiseLower
 * @param mode int8u
 * @param amount int8s
 */
#define emberAfFillCommandThermostatClusterSetpointRaiseLower(mode,amount) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_THERMOSTAT_CLUSTER_ID,\
                            ZCL_SETPOINT_RAISE_LOWER_COMMAND_ID,\
                            "uu",\
                            mode,\
                            amount\
                            );


/** @} END Thermostat Commands */


/** @name Fan Control Commands */
// @{
/** @} END Fan Control Commands */


/** @name Dehumidification Control Commands */
// @{
/** @} END Dehumidification Control Commands */


/** @name Thermostat User Interface Configuration Commands */
// @{
/** @} END Thermostat User Interface Configuration Commands */


/** @name Color Control Commands */
// @{
/** @brief Command description for MoveToHue
 *
 * Cluster: Color Control, Attributes and commands for controlling the color properties of a color-capable light.
 * Command: MoveToHue
 * @param hue int8u
 * @param direction int8u
 * @param transitionTime int16u
 */
#define emberAfFillCommandColorControlClusterMoveToHue(hue,direction,transitionTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COLOR_CONTROL_CLUSTER_ID,\
                            ZCL_MOVE_TO_HUE_COMMAND_ID,\
                            "uuv",\
                            hue,\
                            direction,\
                            transitionTime\
                            );


/** @brief Command description for MoveHue
 *
 * Cluster: Color Control, Attributes and commands for controlling the color properties of a color-capable light.
 * Command: MoveHue
 * @param moveMode int8u
 * @param rate int8u
 */
#define emberAfFillCommandColorControlClusterMoveHue(moveMode,rate) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COLOR_CONTROL_CLUSTER_ID,\
                            ZCL_MOVE_HUE_COMMAND_ID,\
                            "uu",\
                            moveMode,\
                            rate\
                            );


/** @brief Command description for StepHue
 *
 * Cluster: Color Control, Attributes and commands for controlling the color properties of a color-capable light.
 * Command: StepHue
 * @param stepMode int8u
 * @param stepSize int8u
 * @param transitionTime int8u
 */
#define emberAfFillCommandColorControlClusterStepHue(stepMode,stepSize,transitionTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COLOR_CONTROL_CLUSTER_ID,\
                            ZCL_STEP_HUE_COMMAND_ID,\
                            "uuu",\
                            stepMode,\
                            stepSize,\
                            transitionTime\
                            );


/** @brief Command description for MoveToSaturation
 *
 * Cluster: Color Control, Attributes and commands for controlling the color properties of a color-capable light.
 * Command: MoveToSaturation
 * @param saturation int8u
 * @param transitionTime int16u
 */
#define emberAfFillCommandColorControlClusterMoveToSaturation(saturation,transitionTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COLOR_CONTROL_CLUSTER_ID,\
                            ZCL_MOVE_TO_SATURATION_COMMAND_ID,\
                            "uv",\
                            saturation,\
                            transitionTime\
                            );


/** @brief Command description for MoveSaturation
 *
 * Cluster: Color Control, Attributes and commands for controlling the color properties of a color-capable light.
 * Command: MoveSaturation
 * @param moveMode int8u
 * @param rate int8u
 */
#define emberAfFillCommandColorControlClusterMoveSaturation(moveMode,rate) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COLOR_CONTROL_CLUSTER_ID,\
                            ZCL_MOVE_SATURATION_COMMAND_ID,\
                            "uu",\
                            moveMode,\
                            rate\
                            );


/** @brief Command description for StepSaturation
 *
 * Cluster: Color Control, Attributes and commands for controlling the color properties of a color-capable light.
 * Command: StepSaturation
 * @param stepMode int8u
 * @param stepSize int8u
 * @param transitionTime int8u
 */
#define emberAfFillCommandColorControlClusterStepSaturation(stepMode,stepSize,transitionTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COLOR_CONTROL_CLUSTER_ID,\
                            ZCL_STEP_SATURATION_COMMAND_ID,\
                            "uuu",\
                            stepMode,\
                            stepSize,\
                            transitionTime\
                            );


/** @brief Command description for MoveToHueAndSaturation
 *
 * Cluster: Color Control, Attributes and commands for controlling the color properties of a color-capable light.
 * Command: MoveToHueAndSaturation
 * @param hue int8u
 * @param saturation int8u
 * @param transitionTime int16u
 */
#define emberAfFillCommandColorControlClusterMoveToHueAndSaturation(hue,saturation,transitionTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COLOR_CONTROL_CLUSTER_ID,\
                            ZCL_MOVE_TO_HUE_AND_SATURATION_COMMAND_ID,\
                            "uuv",\
                            hue,\
                            saturation,\
                            transitionTime\
                            );


/** @brief Moves the lighting to a specific color.
 *
 * Cluster: Color Control, Attributes and commands for controlling the color properties of a color-capable light.
 * Command: MoveToColor
 * @param colorX int16u
 * @param colorY int16u
 * @param transitionTime int16u
 */
#define emberAfFillCommandColorControlClusterMoveToColor(colorX,colorY,transitionTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COLOR_CONTROL_CLUSTER_ID,\
                            ZCL_MOVE_TO_COLOR_COMMAND_ID,\
                            "vvv",\
                            colorX,\
                            colorY,\
                            transitionTime\
                            );


/** @brief Moves the color.
 *
 * Cluster: Color Control, Attributes and commands for controlling the color properties of a color-capable light.
 * Command: MoveColor
 * @param rateX int16s
 * @param rateY int16s
 */
#define emberAfFillCommandColorControlClusterMoveColor(rateX,rateY) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COLOR_CONTROL_CLUSTER_ID,\
                            ZCL_MOVE_COLOR_COMMAND_ID,\
                            "vv",\
                            rateX,\
                            rateY\
                            );


/** @brief Steps the lighting to a specific color.
 *
 * Cluster: Color Control, Attributes and commands for controlling the color properties of a color-capable light.
 * Command: StepColor
 * @param stepX int16s
 * @param stepY int16s
 * @param transitionTime int16u
 */
#define emberAfFillCommandColorControlClusterStepColor(stepX,stepY,transitionTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COLOR_CONTROL_CLUSTER_ID,\
                            ZCL_STEP_COLOR_COMMAND_ID,\
                            "vvv",\
                            stepX,\
                            stepY,\
                            transitionTime\
                            );


/** @brief Moves the lighting to a specific color temperature.
 *
 * Cluster: Color Control, Attributes and commands for controlling the color properties of a color-capable light.
 * Command: MoveToColorTemperature
 * @param colorTemperature int16u
 * @param transitionTime int16u
 */
#define emberAfFillCommandColorControlClusterMoveToColorTemperature(colorTemperature,transitionTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_COLOR_CONTROL_CLUSTER_ID,\
                            ZCL_MOVE_TO_COLOR_TEMPERATURE_COMMAND_ID,\
                            "vv",\
                            colorTemperature,\
                            transitionTime\
                            );


/** @} END Color Control Commands */


/** @name Ballast Configuration Commands */
// @{
/** @} END Ballast Configuration Commands */


/** @name Illuminance Measurement Commands */
// @{
/** @} END Illuminance Measurement Commands */


/** @name Illuminance Level Sensing Commands */
// @{
/** @} END Illuminance Level Sensing Commands */


/** @name Temperature Measurement Commands */
// @{
/** @} END Temperature Measurement Commands */


/** @name Pressure Measurement Commands */
// @{
/** @} END Pressure Measurement Commands */


/** @name Flow Measurement Commands */
// @{
/** @} END Flow Measurement Commands */


/** @name Relative Humidity Measurement Commands */
// @{
/** @} END Relative Humidity Measurement Commands */


/** @name Occupancy Sensing Commands */
// @{
/** @} END Occupancy Sensing Commands */


/** @name IAS Zone Commands */
// @{
/** @brief Command description for zoneEnrollResponse
 *
 * Cluster: IAS Zone, Attributes and commands for IAS security zone devices.
 * Command: ZoneEnrollResponse
 * @param enrollResponseCode int8u
 * @param zoneId int8u
 */
#define emberAfFillCommandIasZoneClusterZoneEnrollResponse(enrollResponseCode,zoneId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_IAS_ZONE_CLUSTER_ID,\
                            ZCL_ZONE_ENROLL_RESPONSE_COMMAND_ID,\
                            "uu",\
                            enrollResponseCode,\
                            zoneId\
                            );


/** @brief Command description for zoneStatusChangeNotification
 *
 * Cluster: IAS Zone, Attributes and commands for IAS security zone devices.
 * Command: ZoneStatusChangeNotification
 * @param zoneStatus int16u
 * @param extendedStatus int8u
 */
#define emberAfFillCommandIasZoneClusterZoneStatusChangeNotification(zoneStatus,extendedStatus) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_IAS_ZONE_CLUSTER_ID,\
                            ZCL_ZONE_STATUS_CHANGE_NOTIFICATION_COMMAND_ID,\
                            "vu",\
                            zoneStatus,\
                            extendedStatus\
                            );


/** @brief Command description for zoneEnrollRequest
 *
 * Cluster: IAS Zone, Attributes and commands for IAS security zone devices.
 * Command: ZoneEnrollRequest
 * @param zoneType int16u
 * @param manufacturerCode int16u
 */
#define emberAfFillCommandIasZoneClusterZoneEnrollRequest(zoneType,manufacturerCode) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_IAS_ZONE_CLUSTER_ID,\
                            ZCL_ZONE_ENROLL_REQUEST_COMMAND_ID,\
                            "vv",\
                            zoneType,\
                            manufacturerCode\
                            );


/** @} END IAS Zone Commands */


/** @name IAS ACE Commands */
// @{
/** @brief Command description for Arm
 *
 * Cluster: IAS ACE, Attributes and commands for IAS Ancillary Control Equipment.
 * Command: Arm
 * @param armMode int8u
 */
#define emberAfFillCommandIasAceClusterArm(armMode) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_IAS_ACE_CLUSTER_ID,\
                            ZCL_ARM_COMMAND_ID,\
                            "u",\
                            armMode\
                            );


/** @brief Command description for Bypass
 *
 * Cluster: IAS ACE, Attributes and commands for IAS Ancillary Control Equipment.
 * Command: Bypass
 * @param numberOfZones int8u
 * @param zoneIds int8u*
 * @param zoneIdsLen int8u
 */
#define emberAfFillCommandIasAceClusterBypass(numberOfZones,zoneIds,zoneIdsLen) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_IAS_ACE_CLUSTER_ID,\
                            ZCL_BYPASS_COMMAND_ID,\
                            "ub",\
                            numberOfZones,\
                            zoneIds,\
                            zoneIdsLen\
                            );


/** @brief Command description for Emergency
 *
 * Cluster: IAS ACE, Attributes and commands for IAS Ancillary Control Equipment.
 * Command: Emergency
 */
#define emberAfFillCommandIasAceClusterEmergency() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_IAS_ACE_CLUSTER_ID,\
                            ZCL_EMERGENCY_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for Fire
 *
 * Cluster: IAS ACE, Attributes and commands for IAS Ancillary Control Equipment.
 * Command: Fire
 */
#define emberAfFillCommandIasAceClusterFire() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_IAS_ACE_CLUSTER_ID,\
                            ZCL_FIRE_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for Panic
 *
 * Cluster: IAS ACE, Attributes and commands for IAS Ancillary Control Equipment.
 * Command: Panic
 */
#define emberAfFillCommandIasAceClusterPanic() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_IAS_ACE_CLUSTER_ID,\
                            ZCL_PANIC_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for GetZoneIdMap
 *
 * Cluster: IAS ACE, Attributes and commands for IAS Ancillary Control Equipment.
 * Command: GetZoneIdMap
 */
#define emberAfFillCommandIasAceClusterGetZoneIdMap() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_IAS_ACE_CLUSTER_ID,\
                            ZCL_GET_ZONE_ID_MAP_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for GetZoneInformation
 *
 * Cluster: IAS ACE, Attributes and commands for IAS Ancillary Control Equipment.
 * Command: GetZoneInformation
 * @param zoneId int8u
 */
#define emberAfFillCommandIasAceClusterGetZoneInformation(zoneId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_IAS_ACE_CLUSTER_ID,\
                            ZCL_GET_ZONE_INFORMATION_COMMAND_ID,\
                            "u",\
                            zoneId\
                            );


/** @brief Command description for ArmResponse
 *
 * Cluster: IAS ACE, Attributes and commands for IAS Ancillary Control Equipment.
 * Command: ArmResponse
 * @param armNotification int8u
 */
#define emberAfFillCommandIasAceClusterArmResponse(armNotification) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_IAS_ACE_CLUSTER_ID,\
                            ZCL_ARM_RESPONSE_COMMAND_ID,\
                            "u",\
                            armNotification\
                            );


/** @brief Command description for GetZoneIdMapResponse
 *
 * Cluster: IAS ACE, Attributes and commands for IAS Ancillary Control Equipment.
 * Command: GetZoneIdMapResponse
 * @param section0 int16u
 * @param section1 int16u
 * @param section2 int16u
 * @param section3 int16u
 * @param section4 int16u
 * @param section5 int16u
 * @param section6 int16u
 * @param section7 int16u
 * @param section8 int16u
 * @param section9 int16u
 * @param section10 int16u
 * @param section11 int16u
 * @param section12 int16u
 * @param section13 int16u
 * @param section14 int16u
 * @param section15 int16u
 */
#define emberAfFillCommandIasAceClusterGetZoneIdMapResponse(section0,section1,section2,section3,section4,section5,section6,section7,section8,section9,section10,section11,section12,section13,section14,section15) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_IAS_ACE_CLUSTER_ID,\
                            ZCL_GET_ZONE_ID_MAP_RESPONSE_COMMAND_ID,\
                            "vvvvvvvvvvvvvvvv",\
                            section0,\
                            section1,\
                            section2,\
                            section3,\
                            section4,\
                            section5,\
                            section6,\
                            section7,\
                            section8,\
                            section9,\
                            section10,\
                            section11,\
                            section12,\
                            section13,\
                            section14,\
                            section15\
                            );


/** @brief Command description for GetZoneInformationResponse
 *
 * Cluster: IAS ACE, Attributes and commands for IAS Ancillary Control Equipment.
 * Command: GetZoneInformationResponse
 * @param zoneId int8u
 * @param zoneType int16u
 * @param ieeeAddress int8u*
 */
#define emberAfFillCommandIasAceClusterGetZoneInformationResponse(zoneId,zoneType,ieeeAddress) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_IAS_ACE_CLUSTER_ID,\
                            ZCL_GET_ZONE_INFORMATION_RESPONSE_COMMAND_ID,\
                            "uv8",\
                            zoneId,\
                            zoneType,\
                            ieeeAddress\
                            );


/** @} END IAS ACE Commands */


/** @name IAS WD Commands */
// @{
/** @brief Command description for StartWarning
 *
 * Cluster: IAS WD, Attributes and commands for IAS Warning Devices.
 * Command: StartWarning
 * @param warningInfo int8u
 * @param warningDuration int16u
 */
#define emberAfFillCommandIasWdClusterStartWarning(warningInfo,warningDuration) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_IAS_WD_CLUSTER_ID,\
                            ZCL_START_WARNING_COMMAND_ID,\
                            "uv",\
                            warningInfo,\
                            warningDuration\
                            );


/** @brief Command description for Squawk
 *
 * Cluster: IAS WD, Attributes and commands for IAS Warning Devices.
 * Command: Squawk
 * @param squawkInfo int8u
 */
#define emberAfFillCommandIasWdClusterSquawk(squawkInfo) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_IAS_WD_CLUSTER_ID,\
                            ZCL_SQUAWK_COMMAND_ID,\
                            "u",\
                            squawkInfo\
                            );


/** @} END IAS WD Commands */


/** @name Door Lock Commands */
// @{
/** @brief Locks the door
 *
 * Cluster: Door Lock, Provides an interface into a generic way to secure a door.
 * Command: LockDoor
 */
#define emberAfFillCommandDoorLockClusterLockDoor() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_DOOR_LOCK_CLUSTER_ID,\
                            ZCL_LOCK_DOOR_COMMAND_ID,\
                            ""\
                            );


/** @brief Unlocks the door
 *
 * Cluster: Door Lock, Provides an interface into a generic way to secure a door.
 * Command: UnlockDoor
 */
#define emberAfFillCommandDoorLockClusterUnlockDoor() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_DOOR_LOCK_CLUSTER_ID,\
                            ZCL_UNLOCK_DOOR_COMMAND_ID,\
                            ""\
                            );


/** @brief Indicates lock success or failure
 *
 * Cluster: Door Lock, Provides an interface into a generic way to secure a door.
 * Command: LockDoorResponse
 * @param status int8u
 */
#define emberAfFillCommandDoorLockClusterLockDoorResponse(status) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_DOOR_LOCK_CLUSTER_ID,\
                            ZCL_LOCK_DOOR_RESPONSE_COMMAND_ID,\
                            "u",\
                            status\
                            );


/** @brief Indicates unlock success or failure
 *
 * Cluster: Door Lock, Provides an interface into a generic way to secure a door.
 * Command: UnlockDoorResponse
 * @param status int8u
 */
#define emberAfFillCommandDoorLockClusterUnlockDoorResponse(status) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_DOOR_LOCK_CLUSTER_ID,\
                            ZCL_UNLOCK_DOOR_RESPONSE_COMMAND_ID,\
                            "u",\
                            status\
                            );


/** @} END Door Lock Commands */


/** @name Window Covering Commands */
// @{
/** @brief Moves window covering to InstalledOpenLimit - Lift and InstalledOpenLimit - Tilt
 *
 * Cluster: Window Covering, Provides an interface for controlling and adjusting automatic window coverings.
 * Command: WindowCoveringUpOpen
 */
#define emberAfFillCommandWindowCoveringClusterWindowCoveringUpOpen() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_WINDOW_COVERING_CLUSTER_ID,\
                            ZCL_WINDOW_COVERING_UP_OPEN_COMMAND_ID,\
                            ""\
                            );


/** @brief Moves window covering to InstalledClosedLimit - Lift and InstalledCloseLimit - Tilt
 *
 * Cluster: Window Covering, Provides an interface for controlling and adjusting automatic window coverings.
 * Command: WindowCoveringDownClose
 */
#define emberAfFillCommandWindowCoveringClusterWindowCoveringDownClose() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_WINDOW_COVERING_CLUSTER_ID,\
                            ZCL_WINDOW_COVERING_DOWN_CLOSE_COMMAND_ID,\
                            ""\
                            );


/** @brief Stop any adjusting of window covering
 *
 * Cluster: Window Covering, Provides an interface for controlling and adjusting automatic window coverings.
 * Command: WindowCoveringStop
 */
#define emberAfFillCommandWindowCoveringClusterWindowCoveringStop() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_WINDOW_COVERING_CLUSTER_ID,\
                            ZCL_WINDOW_COVERING_STOP_COMMAND_ID,\
                            ""\
                            );


/** @brief Goto lift to value specified
 *
 * Cluster: Window Covering, Provides an interface for controlling and adjusting automatic window coverings.
 * Command: WindowCoveringGoToLiftSetpoint
 * @param indexOfLiftSetpoint int8u
 */
#define emberAfFillCommandWindowCoveringClusterWindowCoveringGoToLiftSetpoint(indexOfLiftSetpoint) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_WINDOW_COVERING_CLUSTER_ID,\
                            ZCL_WINDOW_COVERING_GO_TO_LIFT_SETPOINT_COMMAND_ID,\
                            "u",\
                            indexOfLiftSetpoint\
                            );


/** @brief Goto lift value specified
 *
 * Cluster: Window Covering, Provides an interface for controlling and adjusting automatic window coverings.
 * Command: WindowCoveringGoToLiftValue
 * @param liftValue int16u
 */
#define emberAfFillCommandWindowCoveringClusterWindowCoveringGoToLiftValue(liftValue) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_WINDOW_COVERING_CLUSTER_ID,\
                            ZCL_WINDOW_COVERING_GO_TO_LIFT_VALUE_COMMAND_ID,\
                            "v",\
                            liftValue\
                            );


/** @brief Goto lift percentage specifiec
 *
 * Cluster: Window Covering, Provides an interface for controlling and adjusting automatic window coverings.
 * Command: WindowCoveringGoToLiftPercentage
 * @param percentageLiftValue int8u
 */
#define emberAfFillCommandWindowCoveringClusterWindowCoveringGoToLiftPercentage(percentageLiftValue) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_WINDOW_COVERING_CLUSTER_ID,\
                            ZCL_WINDOW_COVERING_GO_TO_LIFT_PERCENTAGE_COMMAND_ID,\
                            "u",\
                            percentageLiftValue\
                            );


/** @brief Goto tilt setpoint
 *
 * Cluster: Window Covering, Provides an interface for controlling and adjusting automatic window coverings.
 * Command: WindowCoveringGoToTiltSetpoint
 * @param indexOfTiltSetpoint int8u
 */
#define emberAfFillCommandWindowCoveringClusterWindowCoveringGoToTiltSetpoint(indexOfTiltSetpoint) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_WINDOW_COVERING_CLUSTER_ID,\
                            ZCL_WINDOW_COVERING_GO_TO_TILT_SETPOINT_COMMAND_ID,\
                            "u",\
                            indexOfTiltSetpoint\
                            );


/** @brief Goto tilt value specified
 *
 * Cluster: Window Covering, Provides an interface for controlling and adjusting automatic window coverings.
 * Command: WindowCoveringGoToTiltValue
 * @param tiltValue int16u
 */
#define emberAfFillCommandWindowCoveringClusterWindowCoveringGoToTiltValue(tiltValue) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_WINDOW_COVERING_CLUSTER_ID,\
                            ZCL_WINDOW_COVERING_GO_TO_TILT_VALUE_COMMAND_ID,\
                            "v",\
                            tiltValue\
                            );


/** @brief Goto tilt percentage specified
 *
 * Cluster: Window Covering, Provides an interface for controlling and adjusting automatic window coverings.
 * Command: WindowCoveringGoToTiltPercentage
 * @param percentageTiltValue int8u
 */
#define emberAfFillCommandWindowCoveringClusterWindowCoveringGoToTiltPercentage(percentageTiltValue) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_WINDOW_COVERING_CLUSTER_ID,\
                            ZCL_WINDOW_COVERING_GO_TO_TILT_PERCENTAGE_COMMAND_ID,\
                            "u",\
                            percentageTiltValue\
                            );


/** @brief 
 *
 * Cluster: Window Covering, Provides an interface for controlling and adjusting automatic window coverings.
 * Command: WindowCoveringGoToProgramSetpoint
 * @param setpointType int8u
 * @param setpointIndex int8u
 * @param setpointValue int16u
 */
#define emberAfFillCommandWindowCoveringClusterWindowCoveringGoToProgramSetpoint(setpointType,setpointIndex,setpointValue) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_WINDOW_COVERING_CLUSTER_ID,\
                            ZCL_WINDOW_COVERING_GO_TO_PROGRAM_SETPOINT_COMMAND_ID,\
                            "uuv",\
                            setpointType,\
                            setpointIndex,\
                            setpointValue\
                            );


/** @} END Window Covering Commands */


/** @name Generic Tunnel Commands */
// @{
/** @brief This command is generated when an application wishes to find the ZigBee address (node, endpoint) of the Generic Tunnel server cluster with a given ProtocolAddress attribute. The command is typically multicast to a group of inter-communicating Generic Tunnel clusters
 *
 * Cluster: Generic Tunnel, The minimum common commands and attributes required to tunnel any protocol.
 * Command: MatchProtocolAddress
 * @param protocolAddress int8u*
 */
#define emberAfFillCommandGenericTunnelClusterMatchProtocolAddress(protocolAddress) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_GENERIC_TUNNEL_CLUSTER_ID,\
                            ZCL_MATCH_PROTOCOL_ADDRESS_COMMAND_ID,\
                            "s",\
                            protocolAddress\
                            );


/** @brief This command is generated upon receipt of a Match Protocol Address command to indicate that the Protocol Address was successfully matched.
 *
 * Cluster: Generic Tunnel, The minimum common commands and attributes required to tunnel any protocol.
 * Command: MatchProtocolAddressResponse
 */
#define emberAfFillCommandGenericTunnelClusterMatchProtocolAddressResponse() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_GENERIC_TUNNEL_CLUSTER_ID,\
                            ZCL_MATCH_PROTOCOL_ADDRESS_RESPONSE_COMMAND_ID,\
                            ""\
                            );


/** @brief This command is typically sent upon startup, and whenever the ProtocolAddress attribute changes. It is typically multicast to a group of inter-communicating Generic Tunnel clusters.
 *
 * Cluster: Generic Tunnel, The minimum common commands and attributes required to tunnel any protocol.
 * Command: AdvertiseProtocolAddress
 * @param protocolAddress int8u*
 */
#define emberAfFillCommandGenericTunnelClusterAdvertiseProtocolAddress(protocolAddress) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_GENERIC_TUNNEL_CLUSTER_ID,\
                            ZCL_ADVERTISE_PROTOCOL_ADDRESS_COMMAND_ID,\
                            "s",\
                            protocolAddress\
                            );


/** @} END Generic Tunnel Commands */


/** @name BACnet Protocol Tunnel Commands */
// @{
/** @brief This command is generated when a BACnet network layer wishes to transfer a BACnet NPDU across a ZigBee tunnel to another BACnet network layer.
 *
 * Cluster: BACnet Protocol Tunnel, Commands and attributes required to tunnel the BACnet protocol.
 * Command: TransferNpdu
 * @param NPDU int8u*
 */
#define emberAfFillCommandBacnetProtocolTunnelClusterTransferNpdu(NPDU) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_BACNET_PROTOCOL_TUNNEL_CLUSTER_ID,\
                            ZCL_TRANSFER_NPDU_COMMAND_ID,\
                            "s",\
                            NPDU\
                            );


/** @} END BACnet Protocol Tunnel Commands */


/** @name Over the Air Bootloading Cluster Commands */
// @{
/** @brief This command is generated when the upgrade server wishes to notify the clients of the available OTA upgrade image.  The command can be sent as unicast which provides a way for the server to force the upgrade on the client.  The command can also be sent as broadcast or multicast to certain class of clients (for example, the ones that have matching manufacturing and device ids).
 *
 * Cluster: Over the Air Bootloading Cluster, Zigbee Over-the-air Bootloading cluster
 * Command: ImageNotify
 * @param payloadType int8u
 * @param queryJitter int8u
 * @param manufacturerId int16u
 * @param imageType int16u
 * @param newFileVersion int32u
 */
#define emberAfFillCommandOtaBootloadClusterImageNotify(payloadType,queryJitter,manufacturerId,imageType,newFileVersion) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_OTA_BOOTLOAD_CLUSTER_ID,\
                            ZCL_IMAGE_NOTIFY_COMMAND_ID,\
                            "uuvvw",\
                            payloadType,\
                            queryJitter,\
                            manufacturerId,\
                            imageType,\
                            newFileVersion\
                            );


/** @brief This command is generated upon receipt of an Image Notify command to indicate that the client is looking for the next firmware image to upgrade to.  The client may also choose to send the command periodically to the server.
 *
 * Cluster: Over the Air Bootloading Cluster, Zigbee Over-the-air Bootloading cluster
 * Command: QueryNextImageRequest
 * @param fieldControl int8u
 * @param manufacturerId int16u
 * @param imageType int16u
 * @param currentFileVersion int32u
 * @param hardwareVersion int16u
 */
#define emberAfFillCommandOtaBootloadClusterQueryNextImageRequest(fieldControl,manufacturerId,imageType,currentFileVersion,hardwareVersion) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_OTA_BOOTLOAD_CLUSTER_ID,\
                            ZCL_QUERY_NEXT_IMAGE_REQUEST_COMMAND_ID,\
                            "uvvwv",\
                            fieldControl,\
                            manufacturerId,\
                            imageType,\
                            currentFileVersion,\
                            hardwareVersion\
                            );


/** @brief This command is generated upon receipt of an QueryNextImageRequest command to response whether the server has a valid OTA upgrade image for the client or not.  If the server has the file, information regarding the file and OTA upgrade process will be included in the command.
 *
 * Cluster: Over the Air Bootloading Cluster, Zigbee Over-the-air Bootloading cluster
 * Command: QueryNextImageResponse
 * @param status int8u
 * @param manufacturerId int16u
 * @param imageType int16u
 * @param fileVersion int32u
 * @param imageSize int32u
 */
#define emberAfFillCommandOtaBootloadClusterQueryNextImageResponse(status,manufacturerId,imageType,fileVersion,imageSize) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_OTA_BOOTLOAD_CLUSTER_ID,\
                            ZCL_QUERY_NEXT_IMAGE_RESPONSE_COMMAND_ID,\
                            "uvvww",\
                            status,\
                            manufacturerId,\
                            imageType,\
                            fileVersion,\
                            imageSize\
                            );


/** @brief This command is generated by the client to request blocks of OTA upgrade file data.
 *
 * Cluster: Over the Air Bootloading Cluster, Zigbee Over-the-air Bootloading cluster
 * Command: ImageBlockRequest
 * @param fieldControl int8u
 * @param manufacturerId int16u
 * @param imageType int16u
 * @param fileVersion int32u
 * @param fileOffset int32u
 * @param maxDataSize int8u
 * @param requestNodeAddress int8u*
 */
#define emberAfFillCommandOtaBootloadClusterImageBlockRequest(fieldControl,manufacturerId,imageType,fileVersion,fileOffset,maxDataSize,requestNodeAddress) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_OTA_BOOTLOAD_CLUSTER_ID,\
                            ZCL_IMAGE_BLOCK_REQUEST_COMMAND_ID,\
                            "uvvwwu8",\
                            fieldControl,\
                            manufacturerId,\
                            imageType,\
                            fileVersion,\
                            fileOffset,\
                            maxDataSize,\
                            requestNodeAddress\
                            );


/** @brief This command is generated by the client to request pages of OTA upgrade file data. A page would contain multiple blocks of data.
 *
 * Cluster: Over the Air Bootloading Cluster, Zigbee Over-the-air Bootloading cluster
 * Command: ImagePageRequest
 * @param fieldControl int8u
 * @param manufacturerId int16u
 * @param imageType int16u
 * @param fileVersion int32u
 * @param fileOffset int32u
 * @param maxDataSize int8u
 * @param pageSize int16u
 * @param responseSpacing int16u
 * @param requestNodeAddress int8u*
 */
#define emberAfFillCommandOtaBootloadClusterImagePageRequest(fieldControl,manufacturerId,imageType,fileVersion,fileOffset,maxDataSize,pageSize,responseSpacing,requestNodeAddress) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_OTA_BOOTLOAD_CLUSTER_ID,\
                            ZCL_IMAGE_PAGE_REQUEST_COMMAND_ID,\
                            "uvvwwuvv8",\
                            fieldControl,\
                            manufacturerId,\
                            imageType,\
                            fileVersion,\
                            fileOffset,\
                            maxDataSize,\
                            pageSize,\
                            responseSpacing,\
                            requestNodeAddress\
                            );


/** @brief This command is generated by the server in response to the block or page request command.  If the server has the data available, it will reply back with a SUCCESS status.  For other error cases, it may reply with status WAIT_FOR_DATA (server does not have the data available yet) or ABORT (invalid requested parameters or other failure cases).
 *
 * Cluster: Over the Air Bootloading Cluster, Zigbee Over-the-air Bootloading cluster
 * Command: ImageBlockResponse
 * @param status int8u
 * @param manufacturerId int16u
 * @param imageType int16u
 * @param fileVersion int32u
 * @param fileOffset int32u
 * @param dataSize int8u
 * @param imageData int8u*
 */
#define emberAfFillCommandOtaBootloadClusterImageBlockResponse(status,manufacturerId,imageType,fileVersion,fileOffset,dataSize,imageData) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_OTA_BOOTLOAD_CLUSTER_ID,\
                            ZCL_IMAGE_BLOCK_RESPONSE_COMMAND_ID,\
                            "uvvwwus",\
                            status,\
                            manufacturerId,\
                            imageType,\
                            fileVersion,\
                            fileOffset,\
                            dataSize,\
                            imageData\
                            );


/** @brief This command is generated by the client to notify the server of the end of the upgrade process.  The process may end with success or error status.
 *
 * Cluster: Over the Air Bootloading Cluster, Zigbee Over-the-air Bootloading cluster
 * Command: UpgradeEndRequest
 * @param status int8u
 * @param manufacturerId int16u
 * @param imageType int16u
 * @param fileVersion int32u
 */
#define emberAfFillCommandOtaBootloadClusterUpgradeEndRequest(status,manufacturerId,imageType,fileVersion) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_OTA_BOOTLOAD_CLUSTER_ID,\
                            ZCL_UPGRADE_END_REQUEST_COMMAND_ID,\
                            "uvvw",\
                            status,\
                            manufacturerId,\
                            imageType,\
                            fileVersion\
                            );


/** @brief This command is generated by the server in response to the upgrade request in order to let the client know when to upgrade to running new firmware image.
 *
 * Cluster: Over the Air Bootloading Cluster, Zigbee Over-the-air Bootloading cluster
 * Command: UpgradeEndResponse
 * @param manufacturerId int16u
 * @param imageType int16u
 * @param fileVersion int32u
 * @param currentTime int32u
 * @param upgradeTime int32u
 */
#define emberAfFillCommandOtaBootloadClusterUpgradeEndResponse(manufacturerId,imageType,fileVersion,currentTime,upgradeTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_OTA_BOOTLOAD_CLUSTER_ID,\
                            ZCL_UPGRADE_END_RESPONSE_COMMAND_ID,\
                            "vvwww",\
                            manufacturerId,\
                            imageType,\
                            fileVersion,\
                            currentTime,\
                            upgradeTime\
                            );


/** @brief This command is generated by the client to request a file that is specific to itself.  The intention is to provide a way for the client to request non-OTA upgrade file.
 *
 * Cluster: Over the Air Bootloading Cluster, Zigbee Over-the-air Bootloading cluster
 * Command: QuerySpecificFileRequest
 * @param requestNodeAddress int8u*
 * @param manufacturerId int16u
 * @param imageType int16u
 * @param fileVersion int32u
 * @param currentZigbeeStackVersion int16u
 */
#define emberAfFillCommandOtaBootloadClusterQuerySpecificFileRequest(requestNodeAddress,manufacturerId,imageType,fileVersion,currentZigbeeStackVersion) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_OTA_BOOTLOAD_CLUSTER_ID,\
                            ZCL_QUERY_SPECIFIC_FILE_REQUEST_COMMAND_ID,\
                            "8vvwv",\
                            requestNodeAddress,\
                            manufacturerId,\
                            imageType,\
                            fileVersion,\
                            currentZigbeeStackVersion\
                            );


/** @brief This command is generated upon receipt of an QuerySpecificFileRequest command to response whether the server has a valid file for the client or not.  If the server has the file, information regarding the file and OTA process will be included in the command.
 *
 * Cluster: Over the Air Bootloading Cluster, Zigbee Over-the-air Bootloading cluster
 * Command: QuerySpecificFileResponse
 * @param status int8u
 * @param manufacturerId int16u
 * @param imageType int16u
 * @param fileVersion int32u
 * @param imageSize int32u
 */
#define emberAfFillCommandOtaBootloadClusterQuerySpecificFileResponse(status,manufacturerId,imageType,fileVersion,imageSize) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_OTA_BOOTLOAD_CLUSTER_ID,\
                            ZCL_QUERY_SPECIFIC_FILE_RESPONSE_COMMAND_ID,\
                            "uvvww",\
                            status,\
                            manufacturerId,\
                            imageType,\
                            fileVersion,\
                            imageSize\
                            );


/** @} END Over the Air Bootloading Cluster Commands */


/** @name Demand Response and Load Control Commands */
// @{
/** @brief Command description for LoadControlEvent
 *
 * Cluster: Demand Response and Load Control, This cluster provides an interface to the functionality of Smart Energy Demand Response and Load Control. Devices targeted by this cluster include thermostats and devices that support load control.
 * Command: LoadControlEvent
 * @param issuerEventId int32u
 * @param deviceClass int16u
 * @param utilityEnrollmentGroup int8u
 * @param startTime int32u
 * @param durationInMinutes int16u
 * @param criticalityLevel int8u
 * @param coolingTemperatureOffset int8u
 * @param heatingTemperatureOffset int8u
 * @param coolingTemperatureSetPoint int16s
 * @param heatingTemperatureSetPoint int16s
 * @param averageLoadAdjustmentPercentage int8s
 * @param dutyCycle int8u
 * @param eventControl int8u
 */
#define emberAfFillCommandDemandResponseLoadControlClusterLoadControlEvent(issuerEventId,deviceClass,utilityEnrollmentGroup,startTime,durationInMinutes,criticalityLevel,coolingTemperatureOffset,heatingTemperatureOffset,coolingTemperatureSetPoint,heatingTemperatureSetPoint,averageLoadAdjustmentPercentage,dutyCycle,eventControl) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID,\
                            ZCL_LOAD_CONTROL_EVENT_COMMAND_ID,\
                            "wvuwvuuuvvuuu",\
                            issuerEventId,\
                            deviceClass,\
                            utilityEnrollmentGroup,\
                            startTime,\
                            durationInMinutes,\
                            criticalityLevel,\
                            coolingTemperatureOffset,\
                            heatingTemperatureOffset,\
                            coolingTemperatureSetPoint,\
                            heatingTemperatureSetPoint,\
                            averageLoadAdjustmentPercentage,\
                            dutyCycle,\
                            eventControl\
                            );


/** @brief Command description for CancelLoadControlEvent
 *
 * Cluster: Demand Response and Load Control, This cluster provides an interface to the functionality of Smart Energy Demand Response and Load Control. Devices targeted by this cluster include thermostats and devices that support load control.
 * Command: CancelLoadControlEvent
 * @param issuerEventId int32u
 * @param deviceClass int16u
 * @param utilityEnrollmentGroup int8u
 * @param cancelControl int8u
 * @param effectiveTime int32u
 */
#define emberAfFillCommandDemandResponseLoadControlClusterCancelLoadControlEvent(issuerEventId,deviceClass,utilityEnrollmentGroup,cancelControl,effectiveTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID,\
                            ZCL_CANCEL_LOAD_CONTROL_EVENT_COMMAND_ID,\
                            "wvuuw",\
                            issuerEventId,\
                            deviceClass,\
                            utilityEnrollmentGroup,\
                            cancelControl,\
                            effectiveTime\
                            );


/** @brief Command description for CancelAllLoadControlEvents
 *
 * Cluster: Demand Response and Load Control, This cluster provides an interface to the functionality of Smart Energy Demand Response and Load Control. Devices targeted by this cluster include thermostats and devices that support load control.
 * Command: CancelAllLoadControlEvents
 * @param cancelControl int8u
 */
#define emberAfFillCommandDemandResponseLoadControlClusterCancelAllLoadControlEvents(cancelControl) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID,\
                            ZCL_CANCEL_ALL_LOAD_CONTROL_EVENTS_COMMAND_ID,\
                            "u",\
                            cancelControl\
                            );


/** @brief Command description for ReportEventStatus
 *
 * Cluster: Demand Response and Load Control, This cluster provides an interface to the functionality of Smart Energy Demand Response and Load Control. Devices targeted by this cluster include thermostats and devices that support load control.
 * Command: ReportEventStatus
 * @param issuerEventId int32u
 * @param eventStatus int8u
 * @param eventStatusTime int32u
 * @param criticalityLevelApplied int8u
 * @param coolingTemperatureSetPointApplied int16s
 * @param heatingTemperatureSetPointApplied int16s
 * @param averageLoadAdjustmentPercentageApplied int8s
 * @param dutyCycleApplied int8u
 * @param eventControl int8u
 * @param signatureType int8u
 * @param signature int8u*
 */
#define emberAfFillCommandDemandResponseLoadControlClusterReportEventStatus(issuerEventId,eventStatus,eventStatusTime,criticalityLevelApplied,coolingTemperatureSetPointApplied,heatingTemperatureSetPointApplied,averageLoadAdjustmentPercentageApplied,dutyCycleApplied,eventControl,signatureType,signature) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID,\
                            ZCL_REPORT_EVENT_STATUS_COMMAND_ID,\
                            "wuwuvvuuuub",\
                            issuerEventId,\
                            eventStatus,\
                            eventStatusTime,\
                            criticalityLevelApplied,\
                            coolingTemperatureSetPointApplied,\
                            heatingTemperatureSetPointApplied,\
                            averageLoadAdjustmentPercentageApplied,\
                            dutyCycleApplied,\
                            eventControl,\
                            signatureType,\
                            signature,\
                            42\
                            );


/** @brief Command description for GetScheduledEvents
 *
 * Cluster: Demand Response and Load Control, This cluster provides an interface to the functionality of Smart Energy Demand Response and Load Control. Devices targeted by this cluster include thermostats and devices that support load control.
 * Command: GetScheduledEvents
 * @param startTime int32u
 * @param numberOfEvents int8u
 */
#define emberAfFillCommandDemandResponseLoadControlClusterGetScheduledEvents(startTime,numberOfEvents) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID,\
                            ZCL_GET_SCHEDULED_EVENTS_COMMAND_ID,\
                            "wu",\
                            startTime,\
                            numberOfEvents\
                            );


/** @} END Demand Response and Load Control Commands */


/** @name Simple Metering Commands */
// @{
/** @brief Command description for GetProfileResponse
 *
 * Cluster: Simple Metering, The Metering Cluster provides a mechanism to retrieve usage information from Electric, Gas, Water, and potentially Thermal metering devices.
 * Command: GetProfileResponse
 * @param endTime int32u
 * @param status int8u
 * @param profileIntervalPeriod int8u
 * @param numberOfPeriodsDelivered int8u
 * @param intervals int8u*
 * @param intervalsLen int8u
 */
#define emberAfFillCommandSimpleMeteringClusterGetProfileResponse(endTime,status,profileIntervalPeriod,numberOfPeriodsDelivered,intervals,intervalsLen) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_SIMPLE_METERING_CLUSTER_ID,\
                            ZCL_GET_PROFILE_RESPONSE_COMMAND_ID,\
                            "wuuub",\
                            endTime,\
                            status,\
                            profileIntervalPeriod,\
                            numberOfPeriodsDelivered,\
                            intervals,\
                            intervalsLen\
                            );


/** @brief Command description for RequestMirror
 *
 * Cluster: Simple Metering, The Metering Cluster provides a mechanism to retrieve usage information from Electric, Gas, Water, and potentially Thermal metering devices.
 * Command: RequestMirror
 */
#define emberAfFillCommandSimpleMeteringClusterRequestMirror() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_SIMPLE_METERING_CLUSTER_ID,\
                            ZCL_REQUEST_MIRROR_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for RemoveMirror
 *
 * Cluster: Simple Metering, The Metering Cluster provides a mechanism to retrieve usage information from Electric, Gas, Water, and potentially Thermal metering devices.
 * Command: RemoveMirror
 */
#define emberAfFillCommandSimpleMeteringClusterRemoveMirror() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_SIMPLE_METERING_CLUSTER_ID,\
                            ZCL_REMOVE_MIRROR_COMMAND_ID,\
                            ""\
                            );


/** @brief Command sent as a response to fast poll request.
 *
 * Cluster: Simple Metering, The Metering Cluster provides a mechanism to retrieve usage information from Electric, Gas, Water, and potentially Thermal metering devices.
 * Command: RequestFastPollModeResponse
 * @param appliedUpdatePeriod int8u
 * @param fastPollModeEndtime int32u
 */
#define emberAfFillCommandSimpleMeteringClusterRequestFastPollModeResponse(appliedUpdatePeriod,fastPollModeEndtime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_SIMPLE_METERING_CLUSTER_ID,\
                            ZCL_REQUEST_FAST_POLL_MODE_RESPONSE_COMMAND_ID,\
                            "uw",\
                            appliedUpdatePeriod,\
                            fastPollModeEndtime\
                            );


/** @brief Command description for GetProfile
 *
 * Cluster: Simple Metering, The Metering Cluster provides a mechanism to retrieve usage information from Electric, Gas, Water, and potentially Thermal metering devices.
 * Command: GetProfile
 * @param intervalChannel int8u
 * @param endTime int32u
 * @param numberOfPeriods int8u
 */
#define emberAfFillCommandSimpleMeteringClusterGetProfile(intervalChannel,endTime,numberOfPeriods) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_SIMPLE_METERING_CLUSTER_ID,\
                            ZCL_GET_PROFILE_COMMAND_ID,\
                            "uwu",\
                            intervalChannel,\
                            endTime,\
                            numberOfPeriods\
                            );


/** @brief Command description for RequestMirrorResponse
 *
 * Cluster: Simple Metering, The Metering Cluster provides a mechanism to retrieve usage information from Electric, Gas, Water, and potentially Thermal metering devices.
 * Command: RequestMirrorResponse
 * @param endpointId int16u
 */
#define emberAfFillCommandSimpleMeteringClusterRequestMirrorResponse(endpointId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_SIMPLE_METERING_CLUSTER_ID,\
                            ZCL_REQUEST_MIRROR_RESPONSE_COMMAND_ID,\
                            "v",\
                            endpointId\
                            );


/** @brief Command description for MirrorRemoved
 *
 * Cluster: Simple Metering, The Metering Cluster provides a mechanism to retrieve usage information from Electric, Gas, Water, and potentially Thermal metering devices.
 * Command: MirrorRemoved
 * @param endpointId int16u
 */
#define emberAfFillCommandSimpleMeteringClusterMirrorRemoved(endpointId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_SIMPLE_METERING_CLUSTER_ID,\
                            ZCL_MIRROR_REMOVED_COMMAND_ID,\
                            "v",\
                            endpointId\
                            );


/** @brief Command to request fast poll mode.
 *
 * Cluster: Simple Metering, The Metering Cluster provides a mechanism to retrieve usage information from Electric, Gas, Water, and potentially Thermal metering devices.
 * Command: RequestFastPollMode
 * @param fastPollUpdatePeriod int8u
 * @param duration int8u
 */
#define emberAfFillCommandSimpleMeteringClusterRequestFastPollMode(fastPollUpdatePeriod,duration) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_SIMPLE_METERING_CLUSTER_ID,\
                            ZCL_REQUEST_FAST_POLL_MODE_COMMAND_ID,\
                            "uu",\
                            fastPollUpdatePeriod,\
                            duration\
                            );


/** @} END Simple Metering Commands */


/** @name Price Commands */
// @{
/** @brief Command description for PublishPrice
 *
 * Cluster: Price, The Price Cluster provides the mechanism for communicating Gas, Energy, or Water pricing information within the premise.
 * Command: PublishPrice
 * @param providerId int32u
 * @param rateLabel int8u*
 * @param issuerEventId int32u
 * @param currentTime int32u
 * @param unitOfMeasure int8u
 * @param currency int16u
 * @param priceTrailingDigitAndPriceTier int8u
 * @param numberOfPriceTiersAndRegisterTier int8u
 * @param startTime int32u
 * @param durationInMinutes int16u
 * @param price int32u
 * @param priceRatio int8u
 * @param generationPrice int32u
 * @param generationPriceRatio int8u
 * @param alternateCostDelivered int32u
 * @param alternateCostUnit int8u
 * @param alternateCostTrailingDigit int8u
 * @param numberOfBlockThresholds int8u
 * @param priceControl int8u
 */
#define emberAfFillCommandPriceClusterPublishPrice(providerId,rateLabel,issuerEventId,currentTime,unitOfMeasure,currency,priceTrailingDigitAndPriceTier,numberOfPriceTiersAndRegisterTier,startTime,durationInMinutes,price,priceRatio,generationPrice,generationPriceRatio,alternateCostDelivered,alternateCostUnit,alternateCostTrailingDigit,numberOfBlockThresholds,priceControl) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_PRICE_CLUSTER_ID,\
                            ZCL_PUBLISH_PRICE_COMMAND_ID,\
                            "wswwuvuuwvwuwuwuuuu",\
                            providerId,\
                            rateLabel,\
                            issuerEventId,\
                            currentTime,\
                            unitOfMeasure,\
                            currency,\
                            priceTrailingDigitAndPriceTier,\
                            numberOfPriceTiersAndRegisterTier,\
                            startTime,\
                            durationInMinutes,\
                            price,\
                            priceRatio,\
                            generationPrice,\
                            generationPriceRatio,\
                            alternateCostDelivered,\
                            alternateCostUnit,\
                            alternateCostTrailingDigit,\
                            numberOfBlockThresholds,\
                            priceControl\
                            );


/** @brief Command description for PublishBlockPeriod
 *
 * Cluster: Price, The Price Cluster provides the mechanism for communicating Gas, Energy, or Water pricing information within the premise.
 * Command: PublishBlockPeriod
 * @param providerId int32u
 * @param issuerEventId int32u
 * @param blockPeriodStartTime int32u
 * @param blockPeriodDurationInMinutes int32u
 * @param numberOfPriceTiersAndNumberOfBlockThresholds int8u
 * @param blockPeriodControl int8u
 */
#define emberAfFillCommandPriceClusterPublishBlockPeriod(providerId,issuerEventId,blockPeriodStartTime,blockPeriodDurationInMinutes,numberOfPriceTiersAndNumberOfBlockThresholds,blockPeriodControl) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_PRICE_CLUSTER_ID,\
                            ZCL_PUBLISH_BLOCK_PERIOD_COMMAND_ID,\
                            "www3uu",\
                            providerId,\
                            issuerEventId,\
                            blockPeriodStartTime,\
                            blockPeriodDurationInMinutes,\
                            numberOfPriceTiersAndNumberOfBlockThresholds,\
                            blockPeriodControl\
                            );


/** @brief Command description for GetCurrentPrice
 *
 * Cluster: Price, The Price Cluster provides the mechanism for communicating Gas, Energy, or Water pricing information within the premise.
 * Command: GetCurrentPrice
 * @param commandOptions int8u
 */
#define emberAfFillCommandPriceClusterGetCurrentPrice(commandOptions) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_PRICE_CLUSTER_ID,\
                            ZCL_GET_CURRENT_PRICE_COMMAND_ID,\
                            "u",\
                            commandOptions\
                            );


/** @brief Command description for GetScheduledPrices
 *
 * Cluster: Price, The Price Cluster provides the mechanism for communicating Gas, Energy, or Water pricing information within the premise.
 * Command: GetScheduledPrices
 * @param startTime int32u
 * @param numberOfEvents int8u
 */
#define emberAfFillCommandPriceClusterGetScheduledPrices(startTime,numberOfEvents) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_PRICE_CLUSTER_ID,\
                            ZCL_GET_SCHEDULED_PRICES_COMMAND_ID,\
                            "wu",\
                            startTime,\
                            numberOfEvents\
                            );


/** @brief Command description for PriceAcknowledgement
 *
 * Cluster: Price, The Price Cluster provides the mechanism for communicating Gas, Energy, or Water pricing information within the premise.
 * Command: PriceAcknowledgement
 * @param providerId int32u
 * @param issuerEventId int32u
 * @param priceAckTime int32u
 * @param control int8u
 */
#define emberAfFillCommandPriceClusterPriceAcknowledgement(providerId,issuerEventId,priceAckTime,control) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_PRICE_CLUSTER_ID,\
                            ZCL_PRICE_ACKNOWLEDGEMENT_COMMAND_ID,\
                            "wwwu",\
                            providerId,\
                            issuerEventId,\
                            priceAckTime,\
                            control\
                            );


/** @brief Command description for GetBlockPeriod(s)
 *
 * Cluster: Price, The Price Cluster provides the mechanism for communicating Gas, Energy, or Water pricing information within the premise.
 * Command: GetBlockPeriods
 * @param startTime int32u
 * @param numberOfEvents int8u
 */
#define emberAfFillCommandPriceClusterGetBlockPeriods(startTime,numberOfEvents) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_PRICE_CLUSTER_ID,\
                            ZCL_GET_BLOCK_PERIODS_COMMAND_ID,\
                            "wu",\
                            startTime,\
                            numberOfEvents\
                            );


/** @} END Price Commands */


/** @name Messaging Commands */
// @{
/** @brief Command description for DisplayMessage
 *
 * Cluster: Messaging, This cluster provides an interface for passing text messages between SE devices.
 * Command: DisplayMessage
 * @param messageId int32u
 * @param messageControl int8u
 * @param startTime int32u
 * @param durationInMinutes int16u
 * @param message int8u*
 */
#define emberAfFillCommandMessagingClusterDisplayMessage(messageId,messageControl,startTime,durationInMinutes,message) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_MESSAGING_CLUSTER_ID,\
                            ZCL_DISPLAY_MESSAGE_COMMAND_ID,\
                            "wuwvs",\
                            messageId,\
                            messageControl,\
                            startTime,\
                            durationInMinutes,\
                            message\
                            );


/** @brief Command description for CancelMessage
 *
 * Cluster: Messaging, This cluster provides an interface for passing text messages between SE devices.
 * Command: CancelMessage
 * @param messageId int32u
 * @param messageControl int8u
 */
#define emberAfFillCommandMessagingClusterCancelMessage(messageId,messageControl) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_MESSAGING_CLUSTER_ID,\
                            ZCL_CANCEL_MESSAGE_COMMAND_ID,\
                            "wu",\
                            messageId,\
                            messageControl\
                            );


/** @brief Command description for GetLastMessage
 *
 * Cluster: Messaging, This cluster provides an interface for passing text messages between SE devices.
 * Command: GetLastMessage
 */
#define emberAfFillCommandMessagingClusterGetLastMessage() \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_MESSAGING_CLUSTER_ID,\
                            ZCL_GET_LAST_MESSAGE_COMMAND_ID,\
                            ""\
                            );


/** @brief Command description for MessageConfirmation
 *
 * Cluster: Messaging, This cluster provides an interface for passing text messages between SE devices.
 * Command: MessageConfirmation
 * @param messageId int32u
 * @param confirmationTime int32u
 */
#define emberAfFillCommandMessagingClusterMessageConfirmation(messageId,confirmationTime) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_MESSAGING_CLUSTER_ID,\
                            ZCL_MESSAGE_CONFIRMATION_COMMAND_ID,\
                            "ww",\
                            messageId,\
                            confirmationTime\
                            );


/** @} END Messaging Commands */


/** @name Tunneling Commands */
// @{
/** @brief Command description for RequestTunnel
 *
 * Cluster: Tunneling, The tunneling cluster provides an interface for tunneling protocols.
 * Command: RequestTunnel
 * @param protocolId int8u
 * @param manufacturerCode int16u
 * @param flowControlSupport int8u
 */
#define emberAfFillCommandTunnelingClusterRequestTunnel(protocolId,manufacturerCode,flowControlSupport) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_TUNNELING_CLUSTER_ID,\
                            ZCL_REQUEST_TUNNEL_COMMAND_ID,\
                            "uvu",\
                            protocolId,\
                            manufacturerCode,\
                            flowControlSupport\
                            );


/** @brief Command description for CloseTunnel
 *
 * Cluster: Tunneling, The tunneling cluster provides an interface for tunneling protocols.
 * Command: CloseTunnel
 * @param tunnelId int16u
 */
#define emberAfFillCommandTunnelingClusterCloseTunnel(tunnelId) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_TUNNELING_CLUSTER_ID,\
                            ZCL_CLOSE_TUNNEL_COMMAND_ID,\
                            "v",\
                            tunnelId\
                            );


/** @brief Command description for TransferData
 *
 * Cluster: Tunneling, The tunneling cluster provides an interface for tunneling protocols.
 * Command: TransferDataClientToServer
 * @param tunnelId int16u
 * @param data int8u*
 * @param dataLen int8u
 */
#define emberAfFillCommandTunnelingClusterTransferDataClientToServer(tunnelId,data,dataLen) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_TUNNELING_CLUSTER_ID,\
                            ZCL_TRANSFER_DATA_CLIENT_TO_SERVER_COMMAND_ID,\
                            "vb",\
                            tunnelId,\
                            data,\
                            dataLen\
                            );


/** @brief Command description for TransferDataError
 *
 * Cluster: Tunneling, The tunneling cluster provides an interface for tunneling protocols.
 * Command: TransferDataErrorClientToServer
 * @param tunnelId int16u
 * @param transferDataStatus int8u
 */
#define emberAfFillCommandTunnelingClusterTransferDataErrorClientToServer(tunnelId,transferDataStatus) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_TUNNELING_CLUSTER_ID,\
                            ZCL_TRANSFER_DATA_ERROR_CLIENT_TO_SERVER_COMMAND_ID,\
                            "vu",\
                            tunnelId,\
                            transferDataStatus\
                            );


/** @brief Command description for AckTransferData
 *
 * Cluster: Tunneling, The tunneling cluster provides an interface for tunneling protocols.
 * Command: AckTransferDataClientToServer
 * @param tunnelId int16u
 * @param numberOfBytesLeft int16u
 */
#define emberAfFillCommandTunnelingClusterAckTransferDataClientToServer(tunnelId,numberOfBytesLeft) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_TUNNELING_CLUSTER_ID,\
                            ZCL_ACK_TRANSFER_DATA_CLIENT_TO_SERVER_COMMAND_ID,\
                            "vv",\
                            tunnelId,\
                            numberOfBytesLeft\
                            );


/** @brief Command description for ReadyData
 *
 * Cluster: Tunneling, The tunneling cluster provides an interface for tunneling protocols.
 * Command: ReadyDataClientToServer
 * @param tunnelId int16u
 * @param numberOfOctetsLeft int16u
 */
#define emberAfFillCommandTunnelingClusterReadyDataClientToServer(tunnelId,numberOfOctetsLeft) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_TUNNELING_CLUSTER_ID,\
                            ZCL_READY_DATA_CLIENT_TO_SERVER_COMMAND_ID,\
                            "vv",\
                            tunnelId,\
                            numberOfOctetsLeft\
                            );


/** @brief Command description for RequestTunnelResponse
 *
 * Cluster: Tunneling, The tunneling cluster provides an interface for tunneling protocols.
 * Command: RequestTunnelResponse
 * @param tunnelId int16u
 * @param tunnelStatus int8u
 */
#define emberAfFillCommandTunnelingClusterRequestTunnelResponse(tunnelId,tunnelStatus) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_TUNNELING_CLUSTER_ID,\
                            ZCL_REQUEST_TUNNEL_RESPONSE_COMMAND_ID,\
                            "vu",\
                            tunnelId,\
                            tunnelStatus\
                            );


/** @brief Command description for TransferData
 *
 * Cluster: Tunneling, The tunneling cluster provides an interface for tunneling protocols.
 * Command: TransferDataServerToClient
 * @param tunnelId int16u
 * @param data int8u*
 * @param dataLen int8u
 */
#define emberAfFillCommandTunnelingClusterTransferDataServerToClient(tunnelId,data,dataLen) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_TUNNELING_CLUSTER_ID,\
                            ZCL_TRANSFER_DATA_SERVER_TO_CLIENT_COMMAND_ID,\
                            "vb",\
                            tunnelId,\
                            data,\
                            dataLen\
                            );


/** @brief Command description for TransferDataError
 *
 * Cluster: Tunneling, The tunneling cluster provides an interface for tunneling protocols.
 * Command: TransferDataErrorServerToClient
 * @param tunnelId int16u
 * @param transferDataStatus int8u
 */
#define emberAfFillCommandTunnelingClusterTransferDataErrorServerToClient(tunnelId,transferDataStatus) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_TUNNELING_CLUSTER_ID,\
                            ZCL_TRANSFER_DATA_ERROR_SERVER_TO_CLIENT_COMMAND_ID,\
                            "vu",\
                            tunnelId,\
                            transferDataStatus\
                            );


/** @brief Command description for AckTransferData
 *
 * Cluster: Tunneling, The tunneling cluster provides an interface for tunneling protocols.
 * Command: AckTransferDataServerToClient
 * @param tunnelId int16u
 * @param numberOfBytesLeft int16u
 */
#define emberAfFillCommandTunnelingClusterAckTransferDataServerToClient(tunnelId,numberOfBytesLeft) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_TUNNELING_CLUSTER_ID,\
                            ZCL_ACK_TRANSFER_DATA_SERVER_TO_CLIENT_COMMAND_ID,\
                            "vv",\
                            tunnelId,\
                            numberOfBytesLeft\
                            );


/** @brief Command description for ReadyData
 *
 * Cluster: Tunneling, The tunneling cluster provides an interface for tunneling protocols.
 * Command: ReadyDataServerToClient
 * @param tunnelId int16u
 * @param numberOfOctetsLeft int16u
 */
#define emberAfFillCommandTunnelingClusterReadyDataServerToClient(tunnelId,numberOfOctetsLeft) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_TUNNELING_CLUSTER_ID,\
                            ZCL_READY_DATA_SERVER_TO_CLIENT_COMMAND_ID,\
                            "vv",\
                            tunnelId,\
                            numberOfOctetsLeft\
                            );


/** @} END Tunneling Commands */


/** @name Prepayment Commands */
// @{
/** @brief Command description for SelectAvailableEmergencyCredit
 *
 * Cluster: Prepayment, The Prepayment Cluster provides the facility to pass messages relating to prepayment between devices on the HAN.
 * Command: SelectAvailableEmergencyCredit
 * @param commandDateTime int32u
 * @param originatingDevice int8u
 * @param siteId int8u*
 * @param meterSerialNumber int8u*
 */
#define emberAfFillCommandPrepaymentClusterSelectAvailableEmergencyCredit(commandDateTime,originatingDevice,siteId,meterSerialNumber) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_PREPAYMENT_CLUSTER_ID,\
                            ZCL_SELECT_AVAILABLE_EMERGENCY_CREDIT_COMMAND_ID,\
                            "wuss",\
                            commandDateTime,\
                            originatingDevice,\
                            siteId,\
                            meterSerialNumber\
                            );


/** @brief Command description for ChangeSupply
 *
 * Cluster: Prepayment, The Prepayment Cluster provides the facility to pass messages relating to prepayment between devices on the HAN.
 * Command: ChangeSupply
 * @param providerId int32u
 * @param requestDateTime int32u
 * @param siteId int8u*
 * @param meterSerialNumber int8u*
 * @param implementationDateTime int32u
 * @param proposedSupplyStatus int8u
 * @param originatorIdSupplyControlBits int8u
 */
#define emberAfFillCommandPrepaymentClusterChangeSupply(providerId,requestDateTime,siteId,meterSerialNumber,implementationDateTime,proposedSupplyStatus,originatorIdSupplyControlBits) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_PREPAYMENT_CLUSTER_ID,\
                            ZCL_CHANGE_SUPPLY_COMMAND_ID,\
                            "wwsswuu",\
                            providerId,\
                            requestDateTime,\
                            siteId,\
                            meterSerialNumber,\
                            implementationDateTime,\
                            proposedSupplyStatus,\
                            originatorIdSupplyControlBits\
                            );


/** @brief Command description for SupplyStatusResponse
 *
 * Cluster: Prepayment, The Prepayment Cluster provides the facility to pass messages relating to prepayment between devices on the HAN.
 * Command: SupplyStatusResponse
 * @param providerId int32u
 * @param implementationtDateTime int32u
 * @param supplyStatus int8u
 */
#define emberAfFillCommandPrepaymentClusterSupplyStatusResponse(providerId,implementationtDateTime,supplyStatus) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_PREPAYMENT_CLUSTER_ID,\
                            ZCL_SUPPLY_STATUS_RESPONSE_COMMAND_ID,\
                            "wwu",\
                            providerId,\
                            implementationtDateTime,\
                            supplyStatus\
                            );


/** @} END Prepayment Commands */


/** @name Key establishment Commands */
// @{
/** @brief Command description for InitiateKeyEstablishmentRequest
 *
 * Cluster: Key establishment, Key establishment cluster
 * Command: InitiateKeyEstablishmentRequest
 * @param keyEstablishmentSuite int16u
 * @param ephemeralDataGenerateTime int8u
 * @param confirmKeyGenerateTime int8u
 * @param identity int8u*
 */
#define emberAfFillCommandKeyEstablishmentClusterInitiateKeyEstablishmentRequest(keyEstablishmentSuite,ephemeralDataGenerateTime,confirmKeyGenerateTime,identity) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_KEY_ESTABLISHMENT_CLUSTER_ID,\
                            ZCL_INITIATE_KEY_ESTABLISHMENT_REQUEST_COMMAND_ID,\
                            "vuub",\
                            keyEstablishmentSuite,\
                            ephemeralDataGenerateTime,\
                            confirmKeyGenerateTime,\
                            identity,\
                            48\
                            );


/** @brief Command description for EphemeralDataRequest
 *
 * Cluster: Key establishment, Key establishment cluster
 * Command: EphemeralDataRequest
 * @param ephemeralData int8u*
 */
#define emberAfFillCommandKeyEstablishmentClusterEphemeralDataRequest(ephemeralData) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_KEY_ESTABLISHMENT_CLUSTER_ID,\
                            ZCL_EPHEMERAL_DATA_REQUEST_COMMAND_ID,\
                            "b",\
                            ephemeralData,\
                            22\
                            );


/** @brief Command description for ConfirmKeyDataRequest
 *
 * Cluster: Key establishment, Key establishment cluster
 * Command: ConfirmKeyDataRequest
 * @param secureMessageAuthenticationCode int8u*
 */
#define emberAfFillCommandKeyEstablishmentClusterConfirmKeyDataRequest(secureMessageAuthenticationCode) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_KEY_ESTABLISHMENT_CLUSTER_ID,\
                            ZCL_CONFIRM_KEY_DATA_REQUEST_COMMAND_ID,\
                            "G",\
                            secureMessageAuthenticationCode\
                            );


/** @brief Command description for TerminateKeyEstablishment
 *
 * Cluster: Key establishment, Key establishment cluster
 * Command: TerminateKeyEstablishment
 * @param statusCode int8u
 * @param waitTime int8u
 * @param keyEstablishmentSuite int16u
 */
#define emberAfFillCommandKeyEstablishmentClusterServerToClientTerminateKeyEstablishment(statusCode,waitTime,keyEstablishmentSuite) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_KEY_ESTABLISHMENT_CLUSTER_ID,\
                            ZCL_TERMINATE_KEY_ESTABLISHMENT_COMMAND_ID,\
                            "uuv",\
                            statusCode,\
                            waitTime,\
                            keyEstablishmentSuite\
                            );


/** @brief Command description for TerminateKeyEstablishment
 *
 * Cluster: Key establishment, Key establishment cluster
 * Command: TerminateKeyEstablishment
 * @param statusCode int8u
 * @param waitTime int8u
 * @param keyEstablishmentSuite int16u
 */
#define emberAfFillCommandKeyEstablishmentClusterClientToServerTerminateKeyEstablishment(statusCode,waitTime,keyEstablishmentSuite) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_KEY_ESTABLISHMENT_CLUSTER_ID,\
                            ZCL_TERMINATE_KEY_ESTABLISHMENT_COMMAND_ID,\
                            "uuv",\
                            statusCode,\
                            waitTime,\
                            keyEstablishmentSuite\
                            );


/** @brief Command description for InitiateKeyEstablishmentResponse
 *
 * Cluster: Key establishment, Key establishment cluster
 * Command: InitiateKeyEstablishmentResponse
 * @param requestedKeyEstablishmentSuite int16u
 * @param ephemeralDataGenerateTime int8u
 * @param confirmKeyGenerateTime int8u
 * @param identity int8u*
 */
#define emberAfFillCommandKeyEstablishmentClusterInitiateKeyEstablishmentResponse(requestedKeyEstablishmentSuite,ephemeralDataGenerateTime,confirmKeyGenerateTime,identity) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_KEY_ESTABLISHMENT_CLUSTER_ID,\
                            ZCL_INITIATE_KEY_ESTABLISHMENT_RESPONSE_COMMAND_ID,\
                            "vuub",\
                            requestedKeyEstablishmentSuite,\
                            ephemeralDataGenerateTime,\
                            confirmKeyGenerateTime,\
                            identity,\
                            48\
                            );


/** @brief Command description for EphemeralDataResponse
 *
 * Cluster: Key establishment, Key establishment cluster
 * Command: EphemeralDataResponse
 * @param ephemeralData int8u*
 */
#define emberAfFillCommandKeyEstablishmentClusterEphemeralDataResponse(ephemeralData) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_KEY_ESTABLISHMENT_CLUSTER_ID,\
                            ZCL_EPHEMERAL_DATA_RESPONSE_COMMAND_ID,\
                            "b",\
                            ephemeralData,\
                            22\
                            );


/** @brief Command description for ConfirmKeyDataResponse
 *
 * Cluster: Key establishment, Key establishment cluster
 * Command: ConfirmKeyDataResponse
 * @param secureMessageAuthenticationCode int8u*
 */
#define emberAfFillCommandKeyEstablishmentClusterConfirmKeyDataResponse(secureMessageAuthenticationCode) \
  emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,\
                            ZCL_KEY_ESTABLISHMENT_CLUSTER_ID,\
                            ZCL_CONFIRM_KEY_DATA_RESPONSE_COMMAND_ID,\
                            "G",\
                            secureMessageAuthenticationCode\
                            );


/** @} END Key establishment Commands */


/** @name Sample Mfg Specific Cluster Commands */
// @{
/** @brief A sample manufacturer specific command within the sample manufacturer specific
        cluster.
 *
 * Cluster: Sample Mfg Specific Cluster, This cluster provides an example of how the Application 
      Framework can be extended to include manufacturer specific clusters.
 * Command: CommandOne
 * @param argOne int8u
 */
#define emberAfFillCommandSampleMfgSpecificClusterCommandOne(argOne) \
  emberAfFillExternalManufacturerSpecificBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND|ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,\
                            ZCL_SAMPLE_MFG_SPECIFIC_CLUSTER_ID,\
                            0x1002,\
                            ZCL_COMMAND_ONE_COMMAND_ID,\
                            "u",\
                            argOne\
                            );


/** @} END Sample Mfg Specific Cluster Commands */





/** @} END addtogroup */
#endif // CLUSTER_CLIENT_API
