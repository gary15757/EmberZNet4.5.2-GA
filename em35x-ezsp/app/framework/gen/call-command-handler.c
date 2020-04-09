// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generateParseCommand()
//

// This is a set of generated functions that parse the
// the incomming message, and call appropriate command handler.



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

#include "app/framework/util/util.h"
#include "af-structs.h"
#include "call-command-handler.h"
#include "command-id.h"
#include "callback.h"



// Main command parsing controller.
EmberAfStatus emberAfClusterSpecificCommandParse( EmberAfClusterCommand *cmd ) {
  if ( cmd->direction == ZCL_DIRECTION_SERVER_TO_CLIENT ) {
    switch ( cmd->apsFrame->clusterId ) {
#ifdef ZCL_USING_IDENTIFY_CLUSTER_CLIENT
    case ZCL_IDENTIFY_CLUSTER_ID:
      return emberAfIdentifyClusterClientCommandParse( cmd );
#endif // ZCL_USING_IDENTIFY_CLUSTER_CLIENT

#ifdef ZCL_USING_GROUPS_CLUSTER_CLIENT
    case ZCL_GROUPS_CLUSTER_ID:
      return emberAfGroupsClusterClientCommandParse( cmd );
#endif // ZCL_USING_GROUPS_CLUSTER_CLIENT

#ifdef ZCL_USING_SCENES_CLUSTER_CLIENT
    case ZCL_SCENES_CLUSTER_ID:
      return emberAfScenesClusterClientCommandParse( cmd );
#endif // ZCL_USING_SCENES_CLUSTER_CLIENT

#ifdef ZCL_USING_ALARM_CLUSTER_CLIENT
    case ZCL_ALARM_CLUSTER_ID:
      return emberAfAlarmClusterClientCommandParse( cmd );
#endif // ZCL_USING_ALARM_CLUSTER_CLIENT

#ifdef ZCL_USING_RSSI_LOCATION_CLUSTER_CLIENT
    case ZCL_RSSI_LOCATION_CLUSTER_ID:
      return emberAfRssiLocationClusterClientCommandParse( cmd );
#endif // ZCL_USING_RSSI_LOCATION_CLUSTER_CLIENT

#ifdef ZCL_USING_COMMISSIONING_CLUSTER_CLIENT
    case ZCL_COMMISSIONING_CLUSTER_ID:
      return emberAfCommissioningClusterClientCommandParse( cmd );
#endif // ZCL_USING_COMMISSIONING_CLUSTER_CLIENT

#ifdef ZCL_USING_IAS_ZONE_CLUSTER_CLIENT
    case ZCL_IAS_ZONE_CLUSTER_ID:
      return emberAfIasZoneClusterClientCommandParse( cmd );
#endif // ZCL_USING_IAS_ZONE_CLUSTER_CLIENT

#ifdef ZCL_USING_IAS_ACE_CLUSTER_CLIENT
    case ZCL_IAS_ACE_CLUSTER_ID:
      return emberAfIasAceClusterClientCommandParse( cmd );
#endif // ZCL_USING_IAS_ACE_CLUSTER_CLIENT

#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_CLIENT
    case ZCL_DOOR_LOCK_CLUSTER_ID:
      return emberAfDoorLockClusterClientCommandParse( cmd );
#endif // ZCL_USING_DOOR_LOCK_CLUSTER_CLIENT

#ifdef ZCL_USING_GENERIC_TUNNEL_CLUSTER_CLIENT
    case ZCL_GENERIC_TUNNEL_CLUSTER_ID:
      return emberAfGenericTunnelClusterClientCommandParse( cmd );
#endif // ZCL_USING_GENERIC_TUNNEL_CLUSTER_CLIENT

#ifdef ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT
    case ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID:
      return emberAfDemandResponseLoadControlClusterClientCommandParse( cmd );
#endif // ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT

#ifdef ZCL_USING_SIMPLE_METERING_CLUSTER_CLIENT
    case ZCL_SIMPLE_METERING_CLUSTER_ID:
      return emberAfSimpleMeteringClusterClientCommandParse( cmd );
#endif // ZCL_USING_SIMPLE_METERING_CLUSTER_CLIENT

#ifdef ZCL_USING_PRICE_CLUSTER_CLIENT
    case ZCL_PRICE_CLUSTER_ID:
      return emberAfPriceClusterClientCommandParse( cmd );
#endif // ZCL_USING_PRICE_CLUSTER_CLIENT

#ifdef ZCL_USING_MESSAGING_CLUSTER_CLIENT
    case ZCL_MESSAGING_CLUSTER_ID:
      return emberAfMessagingClusterClientCommandParse( cmd );
#endif // ZCL_USING_MESSAGING_CLUSTER_CLIENT

#ifdef ZCL_USING_TUNNELING_CLUSTER_CLIENT
    case ZCL_TUNNELING_CLUSTER_ID:
      return emberAfTunnelingClusterClientCommandParse( cmd );
#endif // ZCL_USING_TUNNELING_CLUSTER_CLIENT

#ifdef ZCL_USING_PREPAYMENT_CLUSTER_CLIENT
    case ZCL_PREPAYMENT_CLUSTER_ID:
      return emberAfPrepaymentClusterClientCommandParse( cmd );
#endif // ZCL_USING_PREPAYMENT_CLUSTER_CLIENT

#ifdef ZCL_USING_KEY_ESTABLISHMENT_CLUSTER_CLIENT
    case ZCL_KEY_ESTABLISHMENT_CLUSTER_ID:
      return emberAfKeyEstablishmentClusterClientCommandParse( cmd );
#endif // ZCL_USING_KEY_ESTABLISHMENT_CLUSTER_CLIENT

    }
  } else { 
    switch ( cmd->apsFrame->clusterId ) {
#ifdef ZCL_USING_BASIC_CLUSTER_SERVER
    case ZCL_BASIC_CLUSTER_ID:
      return emberAfBasicClusterServerCommandParse( cmd );
#endif // ZCL_USING_BASIC_CLUSTER_SERVER

#ifdef ZCL_USING_IDENTIFY_CLUSTER_SERVER
    case ZCL_IDENTIFY_CLUSTER_ID:
      return emberAfIdentifyClusterServerCommandParse( cmd );
#endif // ZCL_USING_IDENTIFY_CLUSTER_SERVER

#ifdef ZCL_USING_GROUPS_CLUSTER_SERVER
    case ZCL_GROUPS_CLUSTER_ID:
      return emberAfGroupsClusterServerCommandParse( cmd );
#endif // ZCL_USING_GROUPS_CLUSTER_SERVER

#ifdef ZCL_USING_SCENES_CLUSTER_SERVER
    case ZCL_SCENES_CLUSTER_ID:
      return emberAfScenesClusterServerCommandParse( cmd );
#endif // ZCL_USING_SCENES_CLUSTER_SERVER

#ifdef ZCL_USING_ON_OFF_CLUSTER_SERVER
    case ZCL_ON_OFF_CLUSTER_ID:
      return emberAfOnOffClusterServerCommandParse( cmd );
#endif // ZCL_USING_ON_OFF_CLUSTER_SERVER

#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
    case ZCL_LEVEL_CONTROL_CLUSTER_ID:
      return emberAfLevelControlClusterServerCommandParse( cmd );
#endif // ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER

#ifdef ZCL_USING_ALARM_CLUSTER_SERVER
    case ZCL_ALARM_CLUSTER_ID:
      return emberAfAlarmClusterServerCommandParse( cmd );
#endif // ZCL_USING_ALARM_CLUSTER_SERVER

#ifdef ZCL_USING_RSSI_LOCATION_CLUSTER_SERVER
    case ZCL_RSSI_LOCATION_CLUSTER_ID:
      return emberAfRssiLocationClusterServerCommandParse( cmd );
#endif // ZCL_USING_RSSI_LOCATION_CLUSTER_SERVER

#ifdef ZCL_USING_COMMISSIONING_CLUSTER_SERVER
    case ZCL_COMMISSIONING_CLUSTER_ID:
      return emberAfCommissioningClusterServerCommandParse( cmd );
#endif // ZCL_USING_COMMISSIONING_CLUSTER_SERVER

#ifdef ZCL_USING_THERMOSTAT_CLUSTER_SERVER
    case ZCL_THERMOSTAT_CLUSTER_ID:
      return emberAfThermostatClusterServerCommandParse( cmd );
#endif // ZCL_USING_THERMOSTAT_CLUSTER_SERVER

#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER
    case ZCL_COLOR_CONTROL_CLUSTER_ID:
      return emberAfColorControlClusterServerCommandParse( cmd );
#endif // ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER

#ifdef ZCL_USING_IAS_ZONE_CLUSTER_SERVER
    case ZCL_IAS_ZONE_CLUSTER_ID:
      return emberAfIasZoneClusterServerCommandParse( cmd );
#endif // ZCL_USING_IAS_ZONE_CLUSTER_SERVER

#ifdef ZCL_USING_IAS_ACE_CLUSTER_SERVER
    case ZCL_IAS_ACE_CLUSTER_ID:
      return emberAfIasAceClusterServerCommandParse( cmd );
#endif // ZCL_USING_IAS_ACE_CLUSTER_SERVER

#ifdef ZCL_USING_IAS_WD_CLUSTER_SERVER
    case ZCL_IAS_WD_CLUSTER_ID:
      return emberAfIasWdClusterServerCommandParse( cmd );
#endif // ZCL_USING_IAS_WD_CLUSTER_SERVER

#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_SERVER
    case ZCL_DOOR_LOCK_CLUSTER_ID:
      return emberAfDoorLockClusterServerCommandParse( cmd );
#endif // ZCL_USING_DOOR_LOCK_CLUSTER_SERVER

#ifdef ZCL_USING_WINDOW_COVERING_CLUSTER_SERVER
    case ZCL_WINDOW_COVERING_CLUSTER_ID:
      return emberAfWindowCoveringClusterServerCommandParse( cmd );
#endif // ZCL_USING_WINDOW_COVERING_CLUSTER_SERVER

#ifdef ZCL_USING_GENERIC_TUNNEL_CLUSTER_SERVER
    case ZCL_GENERIC_TUNNEL_CLUSTER_ID:
      return emberAfGenericTunnelClusterServerCommandParse( cmd );
#endif // ZCL_USING_GENERIC_TUNNEL_CLUSTER_SERVER

#ifdef ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_SERVER
    case ZCL_BACNET_PROTOCOL_TUNNEL_CLUSTER_ID:
      return emberAfBacnetProtocolTunnelClusterServerCommandParse( cmd );
#endif // ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_SERVER

#ifdef ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_SERVER
    case ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID:
      return emberAfDemandResponseLoadControlClusterServerCommandParse( cmd );
#endif // ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_SERVER

#ifdef ZCL_USING_SIMPLE_METERING_CLUSTER_SERVER
    case ZCL_SIMPLE_METERING_CLUSTER_ID:
      return emberAfSimpleMeteringClusterServerCommandParse( cmd );
#endif // ZCL_USING_SIMPLE_METERING_CLUSTER_SERVER

#ifdef ZCL_USING_PRICE_CLUSTER_SERVER
    case ZCL_PRICE_CLUSTER_ID:
      return emberAfPriceClusterServerCommandParse( cmd );
#endif // ZCL_USING_PRICE_CLUSTER_SERVER

#ifdef ZCL_USING_MESSAGING_CLUSTER_SERVER
    case ZCL_MESSAGING_CLUSTER_ID:
      return emberAfMessagingClusterServerCommandParse( cmd );
#endif // ZCL_USING_MESSAGING_CLUSTER_SERVER

#ifdef ZCL_USING_TUNNELING_CLUSTER_SERVER
    case ZCL_TUNNELING_CLUSTER_ID:
      return emberAfTunnelingClusterServerCommandParse( cmd );
#endif // ZCL_USING_TUNNELING_CLUSTER_SERVER

#ifdef ZCL_USING_PREPAYMENT_CLUSTER_SERVER
    case ZCL_PREPAYMENT_CLUSTER_ID:
      return emberAfPrepaymentClusterServerCommandParse( cmd );
#endif // ZCL_USING_PREPAYMENT_CLUSTER_SERVER

#ifdef ZCL_USING_KEY_ESTABLISHMENT_CLUSTER_SERVER
    case ZCL_KEY_ESTABLISHMENT_CLUSTER_ID:
      return emberAfKeyEstablishmentClusterServerCommandParse( cmd );
#endif // ZCL_USING_KEY_ESTABLISHMENT_CLUSTER_SERVER

#ifdef ZCL_USING_SAMPLE_MFG_SPECIFIC_CLUSTER_SERVER
    case ZCL_SAMPLE_MFG_SPECIFIC_CLUSTER_ID:
      return emberAfSampleMfgSpecificClusterServerCommandParse( cmd );
#endif // ZCL_USING_SAMPLE_MFG_SPECIFIC_CLUSTER_SERVER

    }
  }
  return EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND;
}



// Cluster: Basic, client
//    No commands avialable.


// Cluster: Basic, server
#ifdef ZCL_USING_BASIC_CLUSTER_SERVER
EmberAfStatus emberAfBasicClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_BASIC_CLUSTER_RESET_TO_FACTORY_DEFAULTS
      case ZCL_RESET_TO_FACTORY_DEFAULTS_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfBasicClusterResetToFactoryDefaultsCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_BASIC_CLUSTER_RESET_TO_FACTORY_DEFAULTS
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_BASIC_CLUSTER_SERVER



// Cluster: Power Configuration, client
//    No commands avialable.


// Cluster: Power Configuration, server
//    No commands avialable.



// Cluster: Device Temperature Configuration, client
//    No commands avialable.


// Cluster: Device Temperature Configuration, server
//    No commands avialable.



// Cluster: Identify, client
#ifdef ZCL_USING_IDENTIFY_CLUSTER_CLIENT
EmberAfStatus emberAfIdentifyClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_QUERY_RESPONSE
      case ZCL_IDENTIFY_QUERY_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u timeout;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        timeout = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIdentifyClusterIdentifyQueryResponseCallback(
          timeout
        );
      break;
      }
  #endif // EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_QUERY_RESPONSE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_IDENTIFY_CLUSTER_CLIENT


// Cluster: Identify, server
#ifdef ZCL_USING_IDENTIFY_CLUSTER_SERVER
EmberAfStatus emberAfIdentifyClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY
      case ZCL_IDENTIFY_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u identifyTime;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        identifyTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIdentifyClusterIdentifyCallback(
          identifyTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY
  #ifdef EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_QUERY
      case ZCL_IDENTIFY_QUERY_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfIdentifyClusterIdentifyQueryCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_QUERY
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_IDENTIFY_CLUSTER_SERVER



// Cluster: Groups, client
#ifdef ZCL_USING_GROUPS_CLUSTER_CLIENT
EmberAfStatus emberAfGroupsClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_GROUPS_CLUSTER_ADD_GROUP_RESPONSE
      case ZCL_ADD_GROUP_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        int16u groupId;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfGroupsClusterAddGroupResponseCallback(
          status,
          groupId
        );
      break;
      }
  #endif // EMBER_CALLBACK_GROUPS_CLUSTER_ADD_GROUP_RESPONSE
  #ifdef EMBER_CALLBACK_GROUPS_CLUSTER_VIEW_GROUP_RESPONSE
      case ZCL_VIEW_GROUP_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        int16u groupId;  // Ver.: always
        int8u* groupName;  // Ver.: always
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupName = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfGroupsClusterViewGroupResponseCallback(
          status,
          groupId,
          groupName
        );
      break;
      }
  #endif // EMBER_CALLBACK_GROUPS_CLUSTER_VIEW_GROUP_RESPONSE
  #ifdef EMBER_CALLBACK_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP_RESPONSE
      case ZCL_GET_GROUP_MEMBERSHIP_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u capacity;  // Ver.: always
        int8u groupCount;  // Ver.: always
        int8u* groupList;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        capacity = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        groupCount = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        groupList = cmd->buffer + payloadOffset;
        wasHandled = emberAfGroupsClusterGetGroupMembershipResponseCallback(
          capacity,
          groupCount,
          groupList
        );
      break;
      }
  #endif // EMBER_CALLBACK_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP_RESPONSE
  #ifdef EMBER_CALLBACK_GROUPS_CLUSTER_REMOVE_GROUP_RESPONSE
      case ZCL_REMOVE_GROUP_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        int16u groupId;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfGroupsClusterRemoveGroupResponseCallback(
          status,
          groupId
        );
      break;
      }
  #endif // EMBER_CALLBACK_GROUPS_CLUSTER_REMOVE_GROUP_RESPONSE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_GROUPS_CLUSTER_CLIENT


// Cluster: Groups, server
#ifdef ZCL_USING_GROUPS_CLUSTER_SERVER
EmberAfStatus emberAfGroupsClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_GROUPS_CLUSTER_ADD_GROUP
      case ZCL_ADD_GROUP_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u groupId;  // Ver.: always
        int8u* groupName;  // Ver.: always
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupName = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfGroupsClusterAddGroupCallback(
          groupId,
          groupName
        );
      break;
      }
  #endif // EMBER_CALLBACK_GROUPS_CLUSTER_ADD_GROUP
  #ifdef EMBER_CALLBACK_GROUPS_CLUSTER_VIEW_GROUP
      case ZCL_VIEW_GROUP_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u groupId;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfGroupsClusterViewGroupCallback(
          groupId
        );
      break;
      }
  #endif // EMBER_CALLBACK_GROUPS_CLUSTER_VIEW_GROUP
  #ifdef EMBER_CALLBACK_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP
      case ZCL_GET_GROUP_MEMBERSHIP_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u groupCount;  // Ver.: always
        int8u* groupList;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupCount = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        groupList = cmd->buffer + payloadOffset;
        wasHandled = emberAfGroupsClusterGetGroupMembershipCallback(
          groupCount,
          groupList
        );
      break;
      }
  #endif // EMBER_CALLBACK_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP
  #ifdef EMBER_CALLBACK_GROUPS_CLUSTER_REMOVE_GROUP
      case ZCL_REMOVE_GROUP_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u groupId;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfGroupsClusterRemoveGroupCallback(
          groupId
        );
      break;
      }
  #endif // EMBER_CALLBACK_GROUPS_CLUSTER_REMOVE_GROUP
  #ifdef EMBER_CALLBACK_GROUPS_CLUSTER_REMOVE_ALL_GROUPS
      case ZCL_REMOVE_ALL_GROUPS_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfGroupsClusterRemoveAllGroupsCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_GROUPS_CLUSTER_REMOVE_ALL_GROUPS
  #ifdef EMBER_CALLBACK_GROUPS_CLUSTER_ADD_GROUP_IF_IDENTIFYING
      case ZCL_ADD_GROUP_IF_IDENTIFYING_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u groupId;  // Ver.: always
        int8u* groupName;  // Ver.: always
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupName = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfGroupsClusterAddGroupIfIdentifyingCallback(
          groupId,
          groupName
        );
      break;
      }
  #endif // EMBER_CALLBACK_GROUPS_CLUSTER_ADD_GROUP_IF_IDENTIFYING
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_GROUPS_CLUSTER_SERVER



// Cluster: Scenes, client
#ifdef ZCL_USING_SCENES_CLUSTER_CLIENT
EmberAfStatus emberAfScenesClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_ADD_SCENE_RESPONSE
      case ZCL_ADD_SCENE_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        int16u groupId;  // Ver.: always
        int8u sceneId;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfScenesClusterAddSceneResponseCallback(
          status,
          groupId,
          sceneId
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_ADD_SCENE_RESPONSE
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_VIEW_SCENE_RESPONSE
      case ZCL_VIEW_SCENE_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        int16u groupId;  // Ver.: always
        int8u sceneId;  // Ver.: always
        int16u transitionTime;  // Ver.: always
        int8u* sceneName;  // Ver.: always
        int8u* extensionFieldSets;  // Ver.: always
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        sceneName = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1;
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        extensionFieldSets = cmd->buffer + payloadOffset;
        wasHandled = emberAfScenesClusterViewSceneResponseCallback(
          status,
          groupId,
          sceneId,
          transitionTime,
          sceneName,
          extensionFieldSets
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_VIEW_SCENE_RESPONSE
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_REMOVE_SCENE_RESPONSE
      case ZCL_REMOVE_SCENE_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        int16u groupId;  // Ver.: always
        int8u sceneId;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfScenesClusterRemoveSceneResponseCallback(
          status,
          groupId,
          sceneId
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_REMOVE_SCENE_RESPONSE
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_REMOVE_ALL_SCENES_RESPONSE
      case ZCL_REMOVE_ALL_SCENES_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        int16u groupId;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfScenesClusterRemoveAllScenesResponseCallback(
          status,
          groupId
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_REMOVE_ALL_SCENES_RESPONSE
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_STORE_SCENE_RESPONSE
      case ZCL_STORE_SCENE_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        int16u groupId;  // Ver.: always
        int8u sceneId;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfScenesClusterStoreSceneResponseCallback(
          status,
          groupId,
          sceneId
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_STORE_SCENE_RESPONSE
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_RESPONSE
      case ZCL_GET_SCENE_MEMBERSHIP_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        int8u capacity;  // Ver.: always
        int16u groupId;  // Ver.: always
        int8u sceneCount;  // Ver.: always
        int8u* sceneList;  // Ver.: always
        // Command is fixed length: 5
        if (cmd->bufLen < payloadOffset + 5) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        capacity = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        sceneCount = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        sceneList = cmd->buffer + payloadOffset;
        wasHandled = emberAfScenesClusterGetSceneMembershipResponseCallback(
          status,
          capacity,
          groupId,
          sceneCount,
          sceneList
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_RESPONSE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_SCENES_CLUSTER_CLIENT


// Cluster: Scenes, server
#ifdef ZCL_USING_SCENES_CLUSTER_SERVER
EmberAfStatus emberAfScenesClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_ADD_SCENE
      case ZCL_ADD_SCENE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u groupId;  // Ver.: always
        int8u sceneId;  // Ver.: always
        int16u transitionTime;  // Ver.: always
        int8u* sceneName;  // Ver.: always
        int8u* extensionFieldSets;  // Ver.: always
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        sceneName = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1;
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        extensionFieldSets = cmd->buffer + payloadOffset;
        wasHandled = emberAfScenesClusterAddSceneCallback(
          groupId,
          sceneId,
          transitionTime,
          sceneName,
          extensionFieldSets
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_ADD_SCENE
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_VIEW_SCENE
      case ZCL_VIEW_SCENE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u groupId;  // Ver.: always
        int8u sceneId;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfScenesClusterViewSceneCallback(
          groupId,
          sceneId
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_VIEW_SCENE
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_REMOVE_SCENE
      case ZCL_REMOVE_SCENE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u groupId;  // Ver.: always
        int8u sceneId;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfScenesClusterRemoveSceneCallback(
          groupId,
          sceneId
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_REMOVE_SCENE
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_REMOVE_ALL_SCENES
      case ZCL_REMOVE_ALL_SCENES_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u groupId;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfScenesClusterRemoveAllScenesCallback(
          groupId
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_REMOVE_ALL_SCENES
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_STORE_SCENE
      case ZCL_STORE_SCENE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u groupId;  // Ver.: always
        int8u sceneId;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfScenesClusterStoreSceneCallback(
          groupId,
          sceneId
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_STORE_SCENE
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_RECALL_SCENE
      case ZCL_RECALL_SCENE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u groupId;  // Ver.: always
        int8u sceneId;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfScenesClusterRecallSceneCallback(
          groupId,
          sceneId
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_RECALL_SCENE
  #ifdef EMBER_CALLBACK_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP
      case ZCL_GET_SCENE_MEMBERSHIP_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u groupId;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfScenesClusterGetSceneMembershipCallback(
          groupId
        );
      break;
      }
  #endif // EMBER_CALLBACK_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_SCENES_CLUSTER_SERVER



// Cluster: On/off, client
//    No commands avialable.


// Cluster: On/off, server
#ifdef ZCL_USING_ON_OFF_CLUSTER_SERVER
EmberAfStatus emberAfOnOffClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (cmd->mfgSpecific) {
  #ifdef EMBER_CALLBACK_ON_OFF_CLUSTER_SAMPLE_MFG_SPECIFIC_OFF_WITH_TRANSITION
    if (!wasHandled &&
        (cmd->mfgCode == 0x1002 ) &&
        (cmd->commandId == ZCL_SAMPLE_MFG_SPECIFIC_OFF_WITH_TRANSITION_COMMAND_ID )) {
        // Command is fixed length: 0
        wasHandled = emberAfOnOffClusterSampleMfgSpecificOffWithTransitionCallback(
        );
    }
  #endif // EMBER_CALLBACK_ON_OFF_CLUSTER_SAMPLE_MFG_SPECIFIC_OFF_WITH_TRANSITION
  #ifdef EMBER_CALLBACK_ON_OFF_CLUSTER_SAMPLE_MFG_SPECIFIC_ON_WITH_TRANSITION
    if (!wasHandled &&
        (cmd->mfgCode == 0x1002 ) &&
        (cmd->commandId == ZCL_SAMPLE_MFG_SPECIFIC_ON_WITH_TRANSITION_COMMAND_ID )) {
        // Command is fixed length: 0
        wasHandled = emberAfOnOffClusterSampleMfgSpecificOnWithTransitionCallback(
        );
    }
  #endif // EMBER_CALLBACK_ON_OFF_CLUSTER_SAMPLE_MFG_SPECIFIC_ON_WITH_TRANSITION
  #ifdef EMBER_CALLBACK_ON_OFF_CLUSTER_SAMPLE_MFG_SPECIFIC_TOGGLE_WITH_TRANSITION
    if (!wasHandled &&
        (cmd->mfgCode == 0x1002 ) &&
        (cmd->commandId == ZCL_SAMPLE_MFG_SPECIFIC_TOGGLE_WITH_TRANSITION_COMMAND_ID )) {
        // Command is fixed length: 0
        wasHandled = emberAfOnOffClusterSampleMfgSpecificToggleWithTransitionCallback(
        );
    }
  #endif // EMBER_CALLBACK_ON_OFF_CLUSTER_SAMPLE_MFG_SPECIFIC_TOGGLE_WITH_TRANSITION
  } else {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_ON_OFF_CLUSTER_OFF
      case ZCL_OFF_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfOnOffClusterOffCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_ON_OFF_CLUSTER_OFF
  #ifdef EMBER_CALLBACK_ON_OFF_CLUSTER_ON
      case ZCL_ON_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfOnOffClusterOnCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_ON_OFF_CLUSTER_ON
  #ifdef EMBER_CALLBACK_ON_OFF_CLUSTER_TOGGLE
      case ZCL_TOGGLE_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfOnOffClusterToggleCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_ON_OFF_CLUSTER_TOGGLE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_ON_OFF_CLUSTER_SERVER



// Cluster: On/off Switch Configuration, client
//    No commands avialable.


// Cluster: On/off Switch Configuration, server
//    No commands avialable.



// Cluster: Level Control, client
//    No commands avialable.


// Cluster: Level Control, server
#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
EmberAfStatus emberAfLevelControlClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL
      case ZCL_MOVE_TO_LEVEL_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u level;  // Ver.: always
        int16u transitionTime;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        level = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfLevelControlClusterMoveToLevelCallback(
          level,
          transitionTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL
  #ifdef EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_MOVE
      case ZCL_MOVE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u moveMode;  // Ver.: always
        int8u rate;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        moveMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        rate = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfLevelControlClusterMoveCallback(
          moveMode,
          rate
        );
      break;
      }
  #endif // EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_MOVE
  #ifdef EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_STEP
      case ZCL_STEP_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u stepMode;  // Ver.: always
        int8u stepSize;  // Ver.: always
        int16u transitionTime;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        stepMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        stepSize = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfLevelControlClusterStepCallback(
          stepMode,
          stepSize,
          transitionTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_STEP
  #ifdef EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_STOP
      case ZCL_STOP_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfLevelControlClusterStopCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_STOP
  #ifdef EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_WITH_ON_OFF
      case ZCL_MOVE_TO_LEVEL_WITH_ON_OFF_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u level;  // Ver.: always
        int16u transitionTime;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        level = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfLevelControlClusterMoveToLevelWithOnOffCallback(
          level,
          transitionTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_WITH_ON_OFF
  #ifdef EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_MOVE_WITH_ON_OFF
      case ZCL_MOVE_WITH_ON_OFF_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u moveMode;  // Ver.: always
        int8u rate;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        moveMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        rate = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfLevelControlClusterMoveWithOnOffCallback(
          moveMode,
          rate
        );
      break;
      }
  #endif // EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_MOVE_WITH_ON_OFF
  #ifdef EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_STEP_WITH_ON_OFF
      case ZCL_STEP_WITH_ON_OFF_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u stepMode;  // Ver.: always
        int8u stepSize;  // Ver.: always
        int16u transitionTime;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        stepMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        stepSize = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfLevelControlClusterStepWithOnOffCallback(
          stepMode,
          stepSize,
          transitionTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_STEP_WITH_ON_OFF
  #ifdef EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_STOP_WITH_ON_OFF
      case ZCL_STOP_WITH_ON_OFF_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfLevelControlClusterStopWithOnOffCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_STOP_WITH_ON_OFF
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER



// Cluster: Alarms, client
#ifdef ZCL_USING_ALARM_CLUSTER_CLIENT
EmberAfStatus emberAfAlarmClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_ALARM_CLUSTER_ALARM
      case ZCL_ALARM_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u alarmCode;  // Ver.: always
        int16u clusterId;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        alarmCode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        clusterId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfAlarmClusterAlarmCallback(
          alarmCode,
          clusterId
        );
      break;
      }
  #endif // EMBER_CALLBACK_ALARM_CLUSTER_ALARM
  #ifdef EMBER_CALLBACK_ALARM_CLUSTER_GET_ALARM_RESPONSE
      case ZCL_GET_ALARM_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        int8u alarmCode;  // Ver.: always
        int16u clusterId;  // Ver.: always
        int32u timeStamp;  // Ver.: always
        // Command is fixed length: 8
        if (cmd->bufLen < payloadOffset + 8) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        alarmCode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        clusterId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        timeStamp = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfAlarmClusterGetAlarmResponseCallback(
          status,
          alarmCode,
          clusterId,
          timeStamp
        );
      break;
      }
  #endif // EMBER_CALLBACK_ALARM_CLUSTER_GET_ALARM_RESPONSE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_ALARM_CLUSTER_CLIENT


// Cluster: Alarms, server
#ifdef ZCL_USING_ALARM_CLUSTER_SERVER
EmberAfStatus emberAfAlarmClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_ALARM_CLUSTER_RESET_ALARM
      case ZCL_RESET_ALARM_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u alarmCode;  // Ver.: always
        int16u clusterId;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        alarmCode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        clusterId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfAlarmClusterResetAlarmCallback(
          alarmCode,
          clusterId
        );
      break;
      }
  #endif // EMBER_CALLBACK_ALARM_CLUSTER_RESET_ALARM
  #ifdef EMBER_CALLBACK_ALARM_CLUSTER_RESET_ALL_ALARMS
      case ZCL_RESET_ALL_ALARMS_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfAlarmClusterResetAllAlarmsCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_ALARM_CLUSTER_RESET_ALL_ALARMS
  #ifdef EMBER_CALLBACK_ALARM_CLUSTER_GET_ALARM
      case ZCL_GET_ALARM_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfAlarmClusterGetAlarmCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_ALARM_CLUSTER_GET_ALARM
  #ifdef EMBER_CALLBACK_ALARM_CLUSTER_RESET_ALARM_LOG
      case ZCL_RESET_ALARM_LOG_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfAlarmClusterResetAlarmLogCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_ALARM_CLUSTER_RESET_ALARM_LOG
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_ALARM_CLUSTER_SERVER



// Cluster: Time, client
//    No commands avialable.


// Cluster: Time, server
//    No commands avialable.



// Cluster: RSSI Location, client
#ifdef ZCL_USING_RSSI_LOCATION_CLUSTER_CLIENT
EmberAfStatus emberAfRssiLocationClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_DEVICE_CONFIGURATION_RESPONSE
      case ZCL_DEVICE_CONFIGURATION_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        int16s power;  // Ver.: always
        int16u pathLossExponent;  // Ver.: always
        int16u calculationPeriod;  // Ver.: always
        int8u numberRssiMeasurements;  // Ver.: always
        int16u reportingPeriod;  // Ver.: always
        // Command is fixed length: 10
        if (cmd->bufLen < payloadOffset + 10) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        power = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        pathLossExponent = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        calculationPeriod = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        numberRssiMeasurements = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        reportingPeriod = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfRssiLocationClusterDeviceConfigurationResponseCallback(
          status,
          power,
          pathLossExponent,
          calculationPeriod,
          numberRssiMeasurements,
          reportingPeriod
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_DEVICE_CONFIGURATION_RESPONSE
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_LOCATION_DATA_RESPONSE
      case ZCL_LOCATION_DATA_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        int8u locationType;  // Ver.: always
        int16s coordinate1;  // Ver.: always
        int16s coordinate2;  // Ver.: always
        int16s coordinate3;  // Ver.: always
        int16s power;  // Ver.: always
        int16u pathLossExponent;  // Ver.: always
        int8u locationMethod;  // Ver.: always
        int8u qualityMeasure;  // Ver.: always
        int16u locationAge;  // Ver.: always
        // Command is fixed length: 16
        if (cmd->bufLen < payloadOffset + 16) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        locationType = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        coordinate1 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        coordinate2 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        coordinate3 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        power = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        pathLossExponent = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        locationMethod = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        qualityMeasure = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        locationAge = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfRssiLocationClusterLocationDataResponseCallback(
          status,
          locationType,
          coordinate1,
          coordinate2,
          coordinate3,
          power,
          pathLossExponent,
          locationMethod,
          qualityMeasure,
          locationAge
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_LOCATION_DATA_RESPONSE
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_LOCATION_DATA_NOTIFICATION
      case ZCL_LOCATION_DATA_NOTIFICATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u locationType;  // Ver.: always
        int16s coordinate1;  // Ver.: always
        int16s coordinate2;  // Ver.: always
        int16s coordinate3;  // Ver.: always
        int16s power;  // Ver.: always
        int16u pathLossExponent;  // Ver.: always
        int8u locationMethod;  // Ver.: always
        int8u qualityMeasure;  // Ver.: always
        int16u locationAge;  // Ver.: always
        // Command is fixed length: 15
        if (cmd->bufLen < payloadOffset + 15) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        locationType = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        coordinate1 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        coordinate2 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        coordinate3 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        power = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        pathLossExponent = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        locationMethod = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        qualityMeasure = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        locationAge = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfRssiLocationClusterLocationDataNotificationCallback(
          locationType,
          coordinate1,
          coordinate2,
          coordinate3,
          power,
          pathLossExponent,
          locationMethod,
          qualityMeasure,
          locationAge
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_LOCATION_DATA_NOTIFICATION
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_COMPACT_LOCATION_DATA_NOTIFICATION
      case ZCL_COMPACT_LOCATION_DATA_NOTIFICATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u locationType;  // Ver.: always
        int16s coordinate1;  // Ver.: always
        int16s coordinate2;  // Ver.: always
        int16s coordinate3;  // Ver.: always
        int8u qualityMeasure;  // Ver.: always
        int16u locationAge;  // Ver.: always
        // Command is fixed length: 10
        if (cmd->bufLen < payloadOffset + 10) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        locationType = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        coordinate1 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        coordinate2 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        coordinate3 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        qualityMeasure = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        locationAge = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfRssiLocationClusterCompactLocationDataNotificationCallback(
          locationType,
          coordinate1,
          coordinate2,
          coordinate3,
          qualityMeasure,
          locationAge
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_COMPACT_LOCATION_DATA_NOTIFICATION
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_RSSI_PING
      case ZCL_RSSI_PING_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u locationType;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        locationType = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfRssiLocationClusterRssiPingCallback(
          locationType
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_RSSI_PING
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_RSSI_REQUEST
      case ZCL_RSSI_REQUEST_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfRssiLocationClusterRssiRequestCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_RSSI_REQUEST
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_REPORT_RSSI_MEASUREMENTS
      case ZCL_REPORT_RSSI_MEASUREMENTS_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* measuringDevice;  // Ver.: always
        int8u neighbors;  // Ver.: always
        int8u* neighborsInfo;  // Ver.: always
        // Command is fixed length: 9
        if (cmd->bufLen < payloadOffset + 9) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        measuringDevice = cmd->buffer + payloadOffset;
        payloadOffset += 8;
        neighbors = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        neighborsInfo = cmd->buffer + payloadOffset;
        wasHandled = emberAfRssiLocationClusterReportRssiMeasurementsCallback(
          measuringDevice,
          neighbors,
          neighborsInfo
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_REPORT_RSSI_MEASUREMENTS
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_REQUEST_OWN_LOCATION
      case ZCL_REQUEST_OWN_LOCATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* blindNode;  // Ver.: always
        // Command is fixed length: 8
        if (cmd->bufLen < payloadOffset + 8) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        blindNode = cmd->buffer + payloadOffset;
        wasHandled = emberAfRssiLocationClusterRequestOwnLocationCallback(
          blindNode
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_REQUEST_OWN_LOCATION
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_RSSI_LOCATION_CLUSTER_CLIENT


// Cluster: RSSI Location, server
#ifdef ZCL_USING_RSSI_LOCATION_CLUSTER_SERVER
EmberAfStatus emberAfRssiLocationClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_SET_ABSOLUTE_LOCATION
      case ZCL_SET_ABSOLUTE_LOCATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16s coordinate1;  // Ver.: always
        int16s coordinate2;  // Ver.: always
        int16s coordinate3;  // Ver.: always
        int16s power;  // Ver.: always
        int16u pathLossExponent;  // Ver.: always
        // Command is fixed length: 10
        if (cmd->bufLen < payloadOffset + 10) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        coordinate1 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        coordinate2 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        coordinate3 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        power = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        pathLossExponent = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfRssiLocationClusterSetAbsoluteLocationCallback(
          coordinate1,
          coordinate2,
          coordinate3,
          power,
          pathLossExponent
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_SET_ABSOLUTE_LOCATION
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_SET_DEVICE_CONFIGURATION
      case ZCL_SET_DEVICE_CONFIGURATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16s power;  // Ver.: always
        int16u pathLossExponent;  // Ver.: always
        int16u calculationPeriod;  // Ver.: always
        int8u numberRssiMeasurements;  // Ver.: always
        int16u reportingPeriod;  // Ver.: always
        // Command is fixed length: 9
        if (cmd->bufLen < payloadOffset + 9) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        power = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        pathLossExponent = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        calculationPeriod = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        numberRssiMeasurements = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        reportingPeriod = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfRssiLocationClusterSetDeviceConfigurationCallback(
          power,
          pathLossExponent,
          calculationPeriod,
          numberRssiMeasurements,
          reportingPeriod
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_SET_DEVICE_CONFIGURATION
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_GET_DEVICE_CONFIGURATION
      case ZCL_GET_DEVICE_CONFIGURATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* targetAddress;  // Ver.: always
        // Command is fixed length: 8
        if (cmd->bufLen < payloadOffset + 8) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        targetAddress = cmd->buffer + payloadOffset;
        wasHandled = emberAfRssiLocationClusterGetDeviceConfigurationCallback(
          targetAddress
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_GET_DEVICE_CONFIGURATION
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_GET_LOCATION_DATA
      case ZCL_GET_LOCATION_DATA_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u flags;  // Ver.: always
        int8u numberResponses;  // Ver.: always
        int8u* targetAddress;  // Ver.: always
        // Command is fixed length: 10
        if (cmd->bufLen < payloadOffset + 10) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        flags = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        numberResponses = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        targetAddress = cmd->buffer + payloadOffset;
        wasHandled = emberAfRssiLocationClusterGetLocationDataCallback(
          flags,
          numberResponses,
          targetAddress
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_GET_LOCATION_DATA
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_RSSI_RESPONSE
      case ZCL_RSSI_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* replyingDevice;  // Ver.: always
        int16s coordinate1;  // Ver.: always
        int16s coordinate2;  // Ver.: always
        int16s coordinate3;  // Ver.: always
        int8s rssi;  // Ver.: always
        int8u numberRssiMeasurements;  // Ver.: always
        // Command is fixed length: 16
        if (cmd->bufLen < payloadOffset + 16) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        replyingDevice = cmd->buffer + payloadOffset;
        payloadOffset += 8;
        coordinate1 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        coordinate2 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        coordinate3 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        rssi = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        numberRssiMeasurements = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfRssiLocationClusterRssiResponseCallback(
          replyingDevice,
          coordinate1,
          coordinate2,
          coordinate3,
          rssi,
          numberRssiMeasurements
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_RSSI_RESPONSE
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_SEND_PINGS
      case ZCL_SEND_PINGS_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* targetAddress;  // Ver.: always
        int8u numberRssiMeasurements;  // Ver.: always
        int16u calculationPeriod;  // Ver.: always
        // Command is fixed length: 11
        if (cmd->bufLen < payloadOffset + 11) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        targetAddress = cmd->buffer + payloadOffset;
        payloadOffset += 8;
        numberRssiMeasurements = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        calculationPeriod = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfRssiLocationClusterSendPingsCallback(
          targetAddress,
          numberRssiMeasurements,
          calculationPeriod
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_SEND_PINGS
  #ifdef EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_ANCHOR_NODE_ANNOUNCE
      case ZCL_ANCHOR_NODE_ANNOUNCE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* anchorNodeIeeeAddress;  // Ver.: always
        int16s coordinate1;  // Ver.: always
        int16s coordinate2;  // Ver.: always
        int16s coordinate3;  // Ver.: always
        // Command is fixed length: 14
        if (cmd->bufLen < payloadOffset + 14) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        anchorNodeIeeeAddress = cmd->buffer + payloadOffset;
        payloadOffset += 8;
        coordinate1 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        coordinate2 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        coordinate3 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfRssiLocationClusterAnchorNodeAnnounceCallback(
          anchorNodeIeeeAddress,
          coordinate1,
          coordinate2,
          coordinate3
        );
      break;
      }
  #endif // EMBER_CALLBACK_RSSI_LOCATION_CLUSTER_ANCHOR_NODE_ANNOUNCE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_RSSI_LOCATION_CLUSTER_SERVER



// Cluster: Binary Input (Basic), client
//    No commands avialable.


// Cluster: Binary Input (Basic), server
//    No commands avialable.



// Cluster: Commissioning, client
#ifdef ZCL_USING_COMMISSIONING_CLUSTER_CLIENT
EmberAfStatus emberAfCommissioningClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_COMMISSIONING_CLUSTER_RESTART_DEVICE_RESPONSE
      case ZCL_RESTART_DEVICE_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfCommissioningClusterRestartDeviceResponseCallback(
          status
        );
      break;
      }
  #endif // EMBER_CALLBACK_COMMISSIONING_CLUSTER_RESTART_DEVICE_RESPONSE
  #ifdef EMBER_CALLBACK_COMMISSIONING_CLUSTER_SAVE_STARTUP_PARAMETERS_RESPONSE
      case ZCL_SAVE_STARTUP_PARAMETERS_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfCommissioningClusterSaveStartupParametersResponseCallback(
          status
        );
      break;
      }
  #endif // EMBER_CALLBACK_COMMISSIONING_CLUSTER_SAVE_STARTUP_PARAMETERS_RESPONSE
  #ifdef EMBER_CALLBACK_COMMISSIONING_CLUSTER_RESTORE_STARTUP_PARAMETERS_RESPONSE
      case ZCL_RESTORE_STARTUP_PARAMETERS_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfCommissioningClusterRestoreStartupParametersResponseCallback(
          status
        );
      break;
      }
  #endif // EMBER_CALLBACK_COMMISSIONING_CLUSTER_RESTORE_STARTUP_PARAMETERS_RESPONSE
  #ifdef EMBER_CALLBACK_COMMISSIONING_CLUSTER_RESET_STARTUP_PARAMETERS_RESPONSE
      case ZCL_RESET_STARTUP_PARAMETERS_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfCommissioningClusterResetStartupParametersResponseCallback(
          status
        );
      break;
      }
  #endif // EMBER_CALLBACK_COMMISSIONING_CLUSTER_RESET_STARTUP_PARAMETERS_RESPONSE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_COMMISSIONING_CLUSTER_CLIENT


// Cluster: Commissioning, server
#ifdef ZCL_USING_COMMISSIONING_CLUSTER_SERVER
EmberAfStatus emberAfCommissioningClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_COMMISSIONING_CLUSTER_RESTART_DEVICE
      case ZCL_RESTART_DEVICE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u options;  // Ver.: always
        int8u delay;  // Ver.: always
        int8u jitter;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        options = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        delay = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        jitter = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfCommissioningClusterRestartDeviceCallback(
          options,
          delay,
          jitter
        );
      break;
      }
  #endif // EMBER_CALLBACK_COMMISSIONING_CLUSTER_RESTART_DEVICE
  #ifdef EMBER_CALLBACK_COMMISSIONING_CLUSTER_SAVE_STARTUP_PARAMETERS
      case ZCL_SAVE_STARTUP_PARAMETERS_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u options;  // Ver.: always
        int8u index;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        options = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        index = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfCommissioningClusterSaveStartupParametersCallback(
          options,
          index
        );
      break;
      }
  #endif // EMBER_CALLBACK_COMMISSIONING_CLUSTER_SAVE_STARTUP_PARAMETERS
  #ifdef EMBER_CALLBACK_COMMISSIONING_CLUSTER_RESTORE_STARTUP_PARAMETERS
      case ZCL_RESTORE_STARTUP_PARAMETERS_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u options;  // Ver.: always
        int8u index;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        options = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        index = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfCommissioningClusterRestoreStartupParametersCallback(
          options,
          index
        );
      break;
      }
  #endif // EMBER_CALLBACK_COMMISSIONING_CLUSTER_RESTORE_STARTUP_PARAMETERS
  #ifdef EMBER_CALLBACK_COMMISSIONING_CLUSTER_RESET_STARTUP_PARAMETERS
      case ZCL_RESET_STARTUP_PARAMETERS_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u options;  // Ver.: always
        int8u index;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        options = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        index = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfCommissioningClusterResetStartupParametersCallback(
          options,
          index
        );
      break;
      }
  #endif // EMBER_CALLBACK_COMMISSIONING_CLUSTER_RESET_STARTUP_PARAMETERS
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_COMMISSIONING_CLUSTER_SERVER



// Cluster: Shade Configuration, client
//    No commands avialable.


// Cluster: Shade Configuration, server
//    No commands avialable.



// Cluster: Pump Configuration and Control, client
//    No commands avialable.


// Cluster: Pump Configuration and Control, server
//    No commands avialable.



// Cluster: Thermostat, client
//    No commands avialable.


// Cluster: Thermostat, server
#ifdef ZCL_USING_THERMOSTAT_CLUSTER_SERVER
EmberAfStatus emberAfThermostatClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_THERMOSTAT_CLUSTER_SETPOINT_RAISE_LOWER
      case ZCL_SETPOINT_RAISE_LOWER_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u mode;  // Ver.: always
        int8s amount;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        mode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        amount = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfThermostatClusterSetpointRaiseLowerCallback(
          mode,
          amount
        );
      break;
      }
  #endif // EMBER_CALLBACK_THERMOSTAT_CLUSTER_SETPOINT_RAISE_LOWER
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_THERMOSTAT_CLUSTER_SERVER



// Cluster: Fan Control, client
//    No commands avialable.


// Cluster: Fan Control, server
//    No commands avialable.



// Cluster: Dehumidification Control, client
//    No commands avialable.


// Cluster: Dehumidification Control, server
//    No commands avialable.



// Cluster: Thermostat User Interface Configuration, client
//    No commands avialable.


// Cluster: Thermostat User Interface Configuration, server
//    No commands avialable.



// Cluster: Color Control, client
//    No commands avialable.


// Cluster: Color Control, server
#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER
EmberAfStatus emberAfColorControlClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_HUE
      case ZCL_MOVE_TO_HUE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u hue;  // Ver.: always
        int8u direction;  // Ver.: always
        int16u transitionTime;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        hue = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        direction = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfColorControlClusterMoveToHueCallback(
          hue,
          direction,
          transitionTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_HUE
  #ifdef EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_HUE
      case ZCL_MOVE_HUE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u moveMode;  // Ver.: always
        int8u rate;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        moveMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        rate = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfColorControlClusterMoveHueCallback(
          moveMode,
          rate
        );
      break;
      }
  #endif // EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_HUE
  #ifdef EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_STEP_HUE
      case ZCL_STEP_HUE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u stepMode;  // Ver.: always
        int8u stepSize;  // Ver.: always
        int8u transitionTime;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        stepMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        stepSize = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        transitionTime = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfColorControlClusterStepHueCallback(
          stepMode,
          stepSize,
          transitionTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_STEP_HUE
  #ifdef EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_SATURATION
      case ZCL_MOVE_TO_SATURATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u saturation;  // Ver.: always
        int16u transitionTime;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        saturation = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfColorControlClusterMoveToSaturationCallback(
          saturation,
          transitionTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_SATURATION
  #ifdef EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_SATURATION
      case ZCL_MOVE_SATURATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u moveMode;  // Ver.: always
        int8u rate;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        moveMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        rate = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfColorControlClusterMoveSaturationCallback(
          moveMode,
          rate
        );
      break;
      }
  #endif // EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_SATURATION
  #ifdef EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_STEP_SATURATION
      case ZCL_STEP_SATURATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u stepMode;  // Ver.: always
        int8u stepSize;  // Ver.: always
        int8u transitionTime;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        stepMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        stepSize = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        transitionTime = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfColorControlClusterStepSaturationCallback(
          stepMode,
          stepSize,
          transitionTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_STEP_SATURATION
  #ifdef EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_HUE_AND_SATURATION
      case ZCL_MOVE_TO_HUE_AND_SATURATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u hue;  // Ver.: always
        int8u saturation;  // Ver.: always
        int16u transitionTime;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        hue = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        saturation = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfColorControlClusterMoveToHueAndSaturationCallback(
          hue,
          saturation,
          transitionTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_HUE_AND_SATURATION
  #ifdef EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_COLOR
      case ZCL_MOVE_TO_COLOR_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u colorX;  // Ver.: always
        int16u colorY;  // Ver.: always
        int16u transitionTime;  // Ver.: always
        // Command is fixed length: 6
        if (cmd->bufLen < payloadOffset + 6) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        colorX = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        colorY = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfColorControlClusterMoveToColorCallback(
          colorX,
          colorY,
          transitionTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_COLOR
  #ifdef EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_COLOR
      case ZCL_MOVE_COLOR_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16s rateX;  // Ver.: always
        int16s rateY;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        rateX = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        rateY = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfColorControlClusterMoveColorCallback(
          rateX,
          rateY
        );
      break;
      }
  #endif // EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_COLOR
  #ifdef EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_STEP_COLOR
      case ZCL_STEP_COLOR_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16s stepX;  // Ver.: always
        int16s stepY;  // Ver.: always
        int16u transitionTime;  // Ver.: always
        // Command is fixed length: 6
        if (cmd->bufLen < payloadOffset + 6) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        stepX = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        stepY = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfColorControlClusterStepColorCallback(
          stepX,
          stepY,
          transitionTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_STEP_COLOR
  #ifdef EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_COLOR_TEMPERATURE
      case ZCL_MOVE_TO_COLOR_TEMPERATURE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u colorTemperature;  // Ver.: always
        int16u transitionTime;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        colorTemperature = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfColorControlClusterMoveToColorTemperatureCallback(
          colorTemperature,
          transitionTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_COLOR_TEMPERATURE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER



// Cluster: Ballast Configuration, client
//    No commands avialable.


// Cluster: Ballast Configuration, server
//    No commands avialable.



// Cluster: Illuminance Measurement, client
//    No commands avialable.


// Cluster: Illuminance Measurement, server
//    No commands avialable.



// Cluster: Illuminance Level Sensing, client
//    No commands avialable.


// Cluster: Illuminance Level Sensing, server
//    No commands avialable.



// Cluster: Temperature Measurement, client
//    No commands avialable.


// Cluster: Temperature Measurement, server
//    No commands avialable.



// Cluster: Pressure Measurement, client
//    No commands avialable.


// Cluster: Pressure Measurement, server
//    No commands avialable.



// Cluster: Flow Measurement, client
//    No commands avialable.


// Cluster: Flow Measurement, server
//    No commands avialable.



// Cluster: Relative Humidity Measurement, client
//    No commands avialable.


// Cluster: Relative Humidity Measurement, server
//    No commands avialable.



// Cluster: Occupancy Sensing, client
//    No commands avialable.


// Cluster: Occupancy Sensing, server
//    No commands avialable.



// Cluster: IAS Zone, client
#ifdef ZCL_USING_IAS_ZONE_CLUSTER_CLIENT
EmberAfStatus emberAfIasZoneClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_IAS_ZONE_CLUSTER_ZONE_STATUS_CHANGE_NOTIFICATION
      case ZCL_ZONE_STATUS_CHANGE_NOTIFICATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u zoneStatus;  // Ver.: always
        int8u extendedStatus;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        zoneStatus = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        extendedStatus = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIasZoneClusterZoneStatusChangeNotificationCallback(
          zoneStatus,
          extendedStatus
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ZONE_CLUSTER_ZONE_STATUS_CHANGE_NOTIFICATION
  #ifdef EMBER_CALLBACK_IAS_ZONE_CLUSTER_ZONE_ENROLL_REQUEST
      case ZCL_ZONE_ENROLL_REQUEST_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u zoneType;  // Ver.: always
        int16u manufacturerCode;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        zoneType = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        manufacturerCode = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIasZoneClusterZoneEnrollRequestCallback(
          zoneType,
          manufacturerCode
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ZONE_CLUSTER_ZONE_ENROLL_REQUEST
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_IAS_ZONE_CLUSTER_CLIENT


// Cluster: IAS Zone, server
#ifdef ZCL_USING_IAS_ZONE_CLUSTER_SERVER
EmberAfStatus emberAfIasZoneClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_IAS_ZONE_CLUSTER_ZONE_ENROLL_RESPONSE
      case ZCL_ZONE_ENROLL_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u enrollResponseCode;  // Ver.: always
        int8u zoneId;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        enrollResponseCode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        zoneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIasZoneClusterZoneEnrollResponseCallback(
          enrollResponseCode,
          zoneId
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ZONE_CLUSTER_ZONE_ENROLL_RESPONSE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_IAS_ZONE_CLUSTER_SERVER



// Cluster: IAS ACE, client
#ifdef ZCL_USING_IAS_ACE_CLUSTER_CLIENT
EmberAfStatus emberAfIasAceClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_IAS_ACE_CLUSTER_ARM_RESPONSE
      case ZCL_ARM_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u armNotification;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        armNotification = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIasAceClusterArmResponseCallback(
          armNotification
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ACE_CLUSTER_ARM_RESPONSE
  #ifdef EMBER_CALLBACK_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_RESPONSE
      case ZCL_GET_ZONE_ID_MAP_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u section0;  // Ver.: always
        int16u section1;  // Ver.: always
        int16u section2;  // Ver.: always
        int16u section3;  // Ver.: always
        int16u section4;  // Ver.: always
        int16u section5;  // Ver.: always
        int16u section6;  // Ver.: always
        int16u section7;  // Ver.: always
        int16u section8;  // Ver.: always
        int16u section9;  // Ver.: always
        int16u section10;  // Ver.: always
        int16u section11;  // Ver.: always
        int16u section12;  // Ver.: always
        int16u section13;  // Ver.: always
        int16u section14;  // Ver.: always
        int16u section15;  // Ver.: always
        // Command is fixed length: 32
        if (cmd->bufLen < payloadOffset + 32) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        section0 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section1 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section2 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section3 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section4 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section5 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section6 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section7 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section8 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section9 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section10 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section11 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section12 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section13 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section14 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        section15 = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIasAceClusterGetZoneIdMapResponseCallback(
          section0,
          section1,
          section2,
          section3,
          section4,
          section5,
          section6,
          section7,
          section8,
          section9,
          section10,
          section11,
          section12,
          section13,
          section14,
          section15
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_RESPONSE
  #ifdef EMBER_CALLBACK_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_RESPONSE
      case ZCL_GET_ZONE_INFORMATION_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u zoneId;  // Ver.: always
        int16u zoneType;  // Ver.: always
        int8u* ieeeAddress;  // Ver.: always
        // Command is fixed length: 11
        if (cmd->bufLen < payloadOffset + 11) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        zoneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        zoneType = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        ieeeAddress = cmd->buffer + payloadOffset;
        wasHandled = emberAfIasAceClusterGetZoneInformationResponseCallback(
          zoneId,
          zoneType,
          ieeeAddress
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_RESPONSE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_IAS_ACE_CLUSTER_CLIENT


// Cluster: IAS ACE, server
#ifdef ZCL_USING_IAS_ACE_CLUSTER_SERVER
EmberAfStatus emberAfIasAceClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_IAS_ACE_CLUSTER_ARM
      case ZCL_ARM_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u armMode;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        armMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIasAceClusterArmCallback(
          armMode
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ACE_CLUSTER_ARM
  #ifdef EMBER_CALLBACK_IAS_ACE_CLUSTER_BYPASS
      case ZCL_BYPASS_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u numberOfZones;  // Ver.: always
        int8u* zoneIds;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        numberOfZones = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        zoneIds = cmd->buffer + payloadOffset;
        wasHandled = emberAfIasAceClusterBypassCallback(
          numberOfZones,
          zoneIds
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ACE_CLUSTER_BYPASS
  #ifdef EMBER_CALLBACK_IAS_ACE_CLUSTER_EMERGENCY
      case ZCL_EMERGENCY_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfIasAceClusterEmergencyCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ACE_CLUSTER_EMERGENCY
  #ifdef EMBER_CALLBACK_IAS_ACE_CLUSTER_FIRE
      case ZCL_FIRE_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfIasAceClusterFireCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ACE_CLUSTER_FIRE
  #ifdef EMBER_CALLBACK_IAS_ACE_CLUSTER_PANIC
      case ZCL_PANIC_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfIasAceClusterPanicCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ACE_CLUSTER_PANIC
  #ifdef EMBER_CALLBACK_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP
      case ZCL_GET_ZONE_ID_MAP_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfIasAceClusterGetZoneIdMapCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP
  #ifdef EMBER_CALLBACK_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION
      case ZCL_GET_ZONE_INFORMATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u zoneId;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        zoneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIasAceClusterGetZoneInformationCallback(
          zoneId
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_IAS_ACE_CLUSTER_SERVER



// Cluster: IAS WD, client
//    No commands avialable.


// Cluster: IAS WD, server
#ifdef ZCL_USING_IAS_WD_CLUSTER_SERVER
EmberAfStatus emberAfIasWdClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_IAS_WD_CLUSTER_START_WARNING
      case ZCL_START_WARNING_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u warningInfo;  // Ver.: always
        int16u warningDuration;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        warningInfo = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        warningDuration = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIasWdClusterStartWarningCallback(
          warningInfo,
          warningDuration
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_WD_CLUSTER_START_WARNING
  #ifdef EMBER_CALLBACK_IAS_WD_CLUSTER_SQUAWK
      case ZCL_SQUAWK_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u squawkInfo;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        squawkInfo = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIasWdClusterSquawkCallback(
          squawkInfo
        );
      break;
      }
  #endif // EMBER_CALLBACK_IAS_WD_CLUSTER_SQUAWK
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_IAS_WD_CLUSTER_SERVER



// Cluster: Door Lock, client
#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_CLIENT
EmberAfStatus emberAfDoorLockClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_DOOR_LOCK_CLUSTER_LOCK_DOOR_RESPONSE
      case ZCL_LOCK_DOOR_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfDoorLockClusterLockDoorResponseCallback(
          status
        );
      break;
      }
  #endif // EMBER_CALLBACK_DOOR_LOCK_CLUSTER_LOCK_DOOR_RESPONSE
  #ifdef EMBER_CALLBACK_DOOR_LOCK_CLUSTER_UNLOCK_DOOR_RESPONSE
      case ZCL_UNLOCK_DOOR_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u status;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfDoorLockClusterUnlockDoorResponseCallback(
          status
        );
      break;
      }
  #endif // EMBER_CALLBACK_DOOR_LOCK_CLUSTER_UNLOCK_DOOR_RESPONSE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_DOOR_LOCK_CLUSTER_CLIENT


// Cluster: Door Lock, server
#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_SERVER
EmberAfStatus emberAfDoorLockClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_DOOR_LOCK_CLUSTER_LOCK_DOOR
      case ZCL_LOCK_DOOR_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfDoorLockClusterLockDoorCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_DOOR_LOCK_CLUSTER_LOCK_DOOR
  #ifdef EMBER_CALLBACK_DOOR_LOCK_CLUSTER_UNLOCK_DOOR
      case ZCL_UNLOCK_DOOR_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfDoorLockClusterUnlockDoorCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_DOOR_LOCK_CLUSTER_UNLOCK_DOOR
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_DOOR_LOCK_CLUSTER_SERVER



// Cluster: Window Covering, client
//    No commands avialable.


// Cluster: Window Covering, server
#ifdef ZCL_USING_WINDOW_COVERING_CLUSTER_SERVER
EmberAfStatus emberAfWindowCoveringClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_UP_OPEN
      case ZCL_WINDOW_COVERING_UP_OPEN_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfWindowCoveringClusterWindowCoveringUpOpenCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_UP_OPEN
  #ifdef EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_DOWN_CLOSE
      case ZCL_WINDOW_COVERING_DOWN_CLOSE_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfWindowCoveringClusterWindowCoveringDownCloseCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_DOWN_CLOSE
  #ifdef EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_STOP
      case ZCL_WINDOW_COVERING_STOP_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfWindowCoveringClusterWindowCoveringStopCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_STOP
  #ifdef EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_LIFT_SETPOINT
      case ZCL_WINDOW_COVERING_GO_TO_LIFT_SETPOINT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u indexOfLiftSetpoint;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        indexOfLiftSetpoint = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfWindowCoveringClusterWindowCoveringGoToLiftSetpointCallback(
          indexOfLiftSetpoint
        );
      break;
      }
  #endif // EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_LIFT_SETPOINT
  #ifdef EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_LIFT_VALUE
      case ZCL_WINDOW_COVERING_GO_TO_LIFT_VALUE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u liftValue;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        liftValue = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfWindowCoveringClusterWindowCoveringGoToLiftValueCallback(
          liftValue
        );
      break;
      }
  #endif // EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_LIFT_VALUE
  #ifdef EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_LIFT_PERCENTAGE
      case ZCL_WINDOW_COVERING_GO_TO_LIFT_PERCENTAGE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u percentageLiftValue;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        percentageLiftValue = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfWindowCoveringClusterWindowCoveringGoToLiftPercentageCallback(
          percentageLiftValue
        );
      break;
      }
  #endif // EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_LIFT_PERCENTAGE
  #ifdef EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_TILT_SETPOINT
      case ZCL_WINDOW_COVERING_GO_TO_TILT_SETPOINT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u indexOfTiltSetpoint;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        indexOfTiltSetpoint = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfWindowCoveringClusterWindowCoveringGoToTiltSetpointCallback(
          indexOfTiltSetpoint
        );
      break;
      }
  #endif // EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_TILT_SETPOINT
  #ifdef EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_TILT_VALUE
      case ZCL_WINDOW_COVERING_GO_TO_TILT_VALUE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u tiltValue;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        tiltValue = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfWindowCoveringClusterWindowCoveringGoToTiltValueCallback(
          tiltValue
        );
      break;
      }
  #endif // EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_TILT_VALUE
  #ifdef EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_TILT_PERCENTAGE
      case ZCL_WINDOW_COVERING_GO_TO_TILT_PERCENTAGE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u percentageTiltValue;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        percentageTiltValue = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfWindowCoveringClusterWindowCoveringGoToTiltPercentageCallback(
          percentageTiltValue
        );
      break;
      }
  #endif // EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_TILT_PERCENTAGE
  #ifdef EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_PROGRAM_SETPOINT
      case ZCL_WINDOW_COVERING_GO_TO_PROGRAM_SETPOINT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u setpointType;  // Ver.: always
        int8u setpointIndex;  // Ver.: always
        int16u setpointValue;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        setpointType = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        setpointIndex = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        setpointValue = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfWindowCoveringClusterWindowCoveringGoToProgramSetpointCallback(
          setpointType,
          setpointIndex,
          setpointValue
        );
      break;
      }
  #endif // EMBER_CALLBACK_WINDOW_COVERING_CLUSTER_WINDOW_COVERING_GO_TO_PROGRAM_SETPOINT
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_WINDOW_COVERING_CLUSTER_SERVER



// Cluster: Generic Tunnel, client
#ifdef ZCL_USING_GENERIC_TUNNEL_CLUSTER_CLIENT
EmberAfStatus emberAfGenericTunnelClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_GENERIC_TUNNEL_CLUSTER_MATCH_PROTOCOL_ADDRESS_RESPONSE
      case ZCL_MATCH_PROTOCOL_ADDRESS_RESPONSE_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfGenericTunnelClusterMatchProtocolAddressResponseCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_GENERIC_TUNNEL_CLUSTER_MATCH_PROTOCOL_ADDRESS_RESPONSE
  #ifdef EMBER_CALLBACK_GENERIC_TUNNEL_CLUSTER_ADVERTISE_PROTOCOL_ADDRESS
      case ZCL_ADVERTISE_PROTOCOL_ADDRESS_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* protocolAddress;  // Ver.: always
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        protocolAddress = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfGenericTunnelClusterAdvertiseProtocolAddressCallback(
          protocolAddress
        );
      break;
      }
  #endif // EMBER_CALLBACK_GENERIC_TUNNEL_CLUSTER_ADVERTISE_PROTOCOL_ADDRESS
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_GENERIC_TUNNEL_CLUSTER_CLIENT


// Cluster: Generic Tunnel, server
#ifdef ZCL_USING_GENERIC_TUNNEL_CLUSTER_SERVER
EmberAfStatus emberAfGenericTunnelClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_GENERIC_TUNNEL_CLUSTER_MATCH_PROTOCOL_ADDRESS
      case ZCL_MATCH_PROTOCOL_ADDRESS_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* protocolAddress;  // Ver.: always
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        protocolAddress = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfGenericTunnelClusterMatchProtocolAddressCallback(
          protocolAddress
        );
      break;
      }
  #endif // EMBER_CALLBACK_GENERIC_TUNNEL_CLUSTER_MATCH_PROTOCOL_ADDRESS
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_GENERIC_TUNNEL_CLUSTER_SERVER



// Cluster: BACnet Protocol Tunnel, client
//    No commands avialable.


// Cluster: BACnet Protocol Tunnel, server
#ifdef ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_SERVER
EmberAfStatus emberAfBacnetProtocolTunnelClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_BACNET_PROTOCOL_TUNNEL_CLUSTER_TRANSFER_NPDU
      case ZCL_TRANSFER_NPDU_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* NPDU;  // Ver.: always
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        NPDU = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfBacnetProtocolTunnelClusterTransferNpduCallback(
          NPDU
        );
      break;
      }
  #endif // EMBER_CALLBACK_BACNET_PROTOCOL_TUNNEL_CLUSTER_TRANSFER_NPDU
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_SERVER



// Cluster: Demand Response and Load Control, client
#ifdef ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT
EmberAfStatus emberAfDemandResponseLoadControlClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_LOAD_CONTROL_EVENT
      case ZCL_LOAD_CONTROL_EVENT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u issuerEventId;  // Ver.: always
        int16u deviceClass;  // Ver.: always
        int8u utilityEnrollmentGroup;  // Ver.: always
        int32u startTime;  // Ver.: always
        int16u durationInMinutes;  // Ver.: always
        int8u criticalityLevel;  // Ver.: always
        int8u coolingTemperatureOffset;  // Ver.: always
        int8u heatingTemperatureOffset;  // Ver.: always
        int16s coolingTemperatureSetPoint;  // Ver.: always
        int16s heatingTemperatureSetPoint;  // Ver.: always
        int8s averageLoadAdjustmentPercentage;  // Ver.: always
        int8u dutyCycle;  // Ver.: always
        int8u eventControl;  // Ver.: always
        // Command is fixed length: 23
        if (cmd->bufLen < payloadOffset + 23) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        issuerEventId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        deviceClass = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        utilityEnrollmentGroup = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        startTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        durationInMinutes = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        criticalityLevel = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        coolingTemperatureOffset = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        heatingTemperatureOffset = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        coolingTemperatureSetPoint = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        heatingTemperatureSetPoint = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        averageLoadAdjustmentPercentage = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        dutyCycle = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        eventControl = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfDemandResponseLoadControlClusterLoadControlEventCallback(
          issuerEventId,
          deviceClass,
          utilityEnrollmentGroup,
          startTime,
          durationInMinutes,
          criticalityLevel,
          coolingTemperatureOffset,
          heatingTemperatureOffset,
          coolingTemperatureSetPoint,
          heatingTemperatureSetPoint,
          averageLoadAdjustmentPercentage,
          dutyCycle,
          eventControl
        );
      break;
      }
  #endif // EMBER_CALLBACK_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_LOAD_CONTROL_EVENT
  #ifdef EMBER_CALLBACK_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CANCEL_LOAD_CONTROL_EVENT
      case ZCL_CANCEL_LOAD_CONTROL_EVENT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u issuerEventId;  // Ver.: always
        int16u deviceClass;  // Ver.: always
        int8u utilityEnrollmentGroup;  // Ver.: always
        int8u cancelControl;  // Ver.: always
        int32u effectiveTime;  // Ver.: always
        // Command is fixed length: 12
        if (cmd->bufLen < payloadOffset + 12) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        issuerEventId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        deviceClass = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        utilityEnrollmentGroup = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        cancelControl = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        effectiveTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfDemandResponseLoadControlClusterCancelLoadControlEventCallback(
          issuerEventId,
          deviceClass,
          utilityEnrollmentGroup,
          cancelControl,
          effectiveTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CANCEL_LOAD_CONTROL_EVENT
  #ifdef EMBER_CALLBACK_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CANCEL_ALL_LOAD_CONTROL_EVENTS
      case ZCL_CANCEL_ALL_LOAD_CONTROL_EVENTS_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u cancelControl;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        cancelControl = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfDemandResponseLoadControlClusterCancelAllLoadControlEventsCallback(
          cancelControl
        );
      break;
      }
  #endif // EMBER_CALLBACK_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CANCEL_ALL_LOAD_CONTROL_EVENTS
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT


// Cluster: Demand Response and Load Control, server
#ifdef ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_SERVER
EmberAfStatus emberAfDemandResponseLoadControlClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_REPORT_EVENT_STATUS
      case ZCL_REPORT_EVENT_STATUS_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u issuerEventId;  // Ver.: always
        int8u eventStatus;  // Ver.: always
        int32u eventStatusTime;  // Ver.: always
        int8u criticalityLevelApplied;  // Ver.: always
        int16s coolingTemperatureSetPointApplied;  // Ver.: always
        int16s heatingTemperatureSetPointApplied;  // Ver.: always
        int8s averageLoadAdjustmentPercentageApplied;  // Ver.: always
        int8u dutyCycleApplied;  // Ver.: always
        int8u eventControl;  // Ver.: always
        int8u signatureType;  // Ver.: always
        int8u* signature;  // Ver.: until SE_1.1, 105638r08
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        issuerEventId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        eventStatus = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        eventStatusTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        criticalityLevelApplied = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        coolingTemperatureSetPointApplied = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        heatingTemperatureSetPointApplied = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        averageLoadAdjustmentPercentageApplied = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        dutyCycleApplied = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        eventControl = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        signatureType = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 42) {
          // Argument is not present in all version if ZCL spec,
          // so we don't complain if it's missing for backward compatibility.
          signature = NULL;
        } else {
          signature = cmd->buffer + payloadOffset;
        }
        wasHandled = emberAfDemandResponseLoadControlClusterReportEventStatusCallback(
          issuerEventId,
          eventStatus,
          eventStatusTime,
          criticalityLevelApplied,
          coolingTemperatureSetPointApplied,
          heatingTemperatureSetPointApplied,
          averageLoadAdjustmentPercentageApplied,
          dutyCycleApplied,
          eventControl,
          signatureType,
          signature
        );
      break;
      }
  #endif // EMBER_CALLBACK_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_REPORT_EVENT_STATUS
  #ifdef EMBER_CALLBACK_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_GET_SCHEDULED_EVENTS
      case ZCL_GET_SCHEDULED_EVENTS_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u startTime;  // Ver.: always
        int8u numberOfEvents;  // Ver.: always
        // Command is fixed length: 5
        if (cmd->bufLen < payloadOffset + 5) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        startTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        numberOfEvents = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfDemandResponseLoadControlClusterGetScheduledEventsCallback(
          startTime,
          numberOfEvents
        );
      break;
      }
  #endif // EMBER_CALLBACK_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_GET_SCHEDULED_EVENTS
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_SERVER



// Cluster: Simple Metering, client
#ifdef ZCL_USING_SIMPLE_METERING_CLUSTER_CLIENT
EmberAfStatus emberAfSimpleMeteringClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_GET_PROFILE_RESPONSE
      case ZCL_GET_PROFILE_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u endTime;  // Ver.: always
        int8u status;  // Ver.: always
        int8u profileIntervalPeriod;  // Ver.: always
        int8u numberOfPeriodsDelivered;  // Ver.: always
        int8u* intervals;  // Ver.: always
        // Command is fixed length: 7
        if (cmd->bufLen < payloadOffset + 7) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        endTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        profileIntervalPeriod = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        numberOfPeriodsDelivered = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        intervals = cmd->buffer + payloadOffset;
        wasHandled = emberAfSimpleMeteringClusterGetProfileResponseCallback(
          endTime,
          status,
          profileIntervalPeriod,
          numberOfPeriodsDelivered,
          intervals
        );
      break;
      }
  #endif // EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_GET_PROFILE_RESPONSE
  #ifdef EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_REQUEST_MIRROR
      case ZCL_REQUEST_MIRROR_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfSimpleMeteringClusterRequestMirrorCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_REQUEST_MIRROR
  #ifdef EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_REMOVE_MIRROR
      case ZCL_REMOVE_MIRROR_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfSimpleMeteringClusterRemoveMirrorCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_REMOVE_MIRROR
  #ifdef EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_REQUEST_FAST_POLL_MODE_RESPONSE
      case ZCL_REQUEST_FAST_POLL_MODE_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u appliedUpdatePeriod;  // Ver.: always
        int32u fastPollModeEndtime;  // Ver.: always
        // Command is fixed length: 5
        if (cmd->bufLen < payloadOffset + 5) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        appliedUpdatePeriod = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        fastPollModeEndtime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfSimpleMeteringClusterRequestFastPollModeResponseCallback(
          appliedUpdatePeriod,
          fastPollModeEndtime
        );
      break;
      }
  #endif // EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_REQUEST_FAST_POLL_MODE_RESPONSE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_SIMPLE_METERING_CLUSTER_CLIENT


// Cluster: Simple Metering, server
#ifdef ZCL_USING_SIMPLE_METERING_CLUSTER_SERVER
EmberAfStatus emberAfSimpleMeteringClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_GET_PROFILE
      case ZCL_GET_PROFILE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u intervalChannel;  // Ver.: always
        int32u endTime;  // Ver.: always
        int8u numberOfPeriods;  // Ver.: always
        // Command is fixed length: 6
        if (cmd->bufLen < payloadOffset + 6) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        intervalChannel = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        endTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        numberOfPeriods = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfSimpleMeteringClusterGetProfileCallback(
          intervalChannel,
          endTime,
          numberOfPeriods
        );
      break;
      }
  #endif // EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_GET_PROFILE
  #ifdef EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_REQUEST_MIRROR_RESPONSE
      case ZCL_REQUEST_MIRROR_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u endpointId;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        endpointId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfSimpleMeteringClusterRequestMirrorResponseCallback(
          endpointId
        );
      break;
      }
  #endif // EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_REQUEST_MIRROR_RESPONSE
  #ifdef EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_MIRROR_REMOVED
      case ZCL_MIRROR_REMOVED_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u endpointId;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        endpointId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfSimpleMeteringClusterMirrorRemovedCallback(
          endpointId
        );
      break;
      }
  #endif // EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_MIRROR_REMOVED
  #ifdef EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_REQUEST_FAST_POLL_MODE
      case ZCL_REQUEST_FAST_POLL_MODE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u fastPollUpdatePeriod;  // Ver.: always
        int8u duration;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        fastPollUpdatePeriod = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        duration = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfSimpleMeteringClusterRequestFastPollModeCallback(
          fastPollUpdatePeriod,
          duration
        );
      break;
      }
  #endif // EMBER_CALLBACK_SIMPLE_METERING_CLUSTER_REQUEST_FAST_POLL_MODE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_SIMPLE_METERING_CLUSTER_SERVER



// Cluster: Price, client
#ifdef ZCL_USING_PRICE_CLUSTER_CLIENT
EmberAfStatus emberAfPriceClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_PRICE_CLUSTER_PUBLISH_PRICE
      case ZCL_PUBLISH_PRICE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u providerId;  // Ver.: always
        int8u* rateLabel;  // Ver.: always
        int32u issuerEventId;  // Ver.: always
        int32u currentTime;  // Ver.: always
        int8u unitOfMeasure;  // Ver.: always
        int16u currency;  // Ver.: always
        int8u priceTrailingDigitAndPriceTier;  // Ver.: always
        int8u numberOfPriceTiersAndRegisterTier;  // Ver.: always
        int32u startTime;  // Ver.: always
        int16u durationInMinutes;  // Ver.: always
        int32u price;  // Ver.: always
        int8u priceRatio;  // Ver.: always
        int32u generationPrice;  // Ver.: always
        int8u generationPriceRatio;  // Ver.: always
        int32u alternateCostDelivered;  // Ver.: since SE_1.0, 075356r15
        int8u alternateCostUnit;  // Ver.: since SE_1.0, 075356r15
        int8u alternateCostTrailingDigit;  // Ver.: since SE_1.0, 075356r15
        int8u numberOfBlockThresholds;  // Ver.: since SE_1.1, 105638r09
        int8u priceControl;  // Ver.: since SE_1.1, 105638r09
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        providerId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        rateLabel = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1;
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        issuerEventId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        currentTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        unitOfMeasure = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        currency = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        priceTrailingDigitAndPriceTier = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        numberOfPriceTiersAndRegisterTier = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        startTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        durationInMinutes = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        price = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        priceRatio = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        generationPrice = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        generationPriceRatio = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 4) {
          // Argument is not present in all version if ZCL spec,
          // so we don't complain if it's missing for backward compatibility.
          alternateCostDelivered = 0xFFFFFFFF;
        } else {
          alternateCostDelivered = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 4;
        }
        if (cmd->bufLen < payloadOffset + 1) {
          // Argument is not present in all version if ZCL spec,
          // so we don't complain if it's missing for backward compatibility.
          alternateCostUnit = 0xFF;
        } else {
          alternateCostUnit = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1;
        }
        if (cmd->bufLen < payloadOffset + 1) {
          // Argument is not present in all version if ZCL spec,
          // so we don't complain if it's missing for backward compatibility.
          alternateCostTrailingDigit = 0xFF;
        } else {
          alternateCostTrailingDigit = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1;
        }
        if (cmd->bufLen < payloadOffset + 1) {
          // Argument is not present in all version if ZCL spec,
          // so we don't complain if it's missing for backward compatibility.
          numberOfBlockThresholds = 0xFF;
        } else {
          numberOfBlockThresholds = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1;
        }
        if (cmd->bufLen < payloadOffset + 1) {
          // Argument is not present in all version if ZCL spec,
          // so we don't complain if it's missing for backward compatibility.
          priceControl = 0x00;
        } else {
          priceControl = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfPriceClusterPublishPriceCallback(
          providerId,
          rateLabel,
          issuerEventId,
          currentTime,
          unitOfMeasure,
          currency,
          priceTrailingDigitAndPriceTier,
          numberOfPriceTiersAndRegisterTier,
          startTime,
          durationInMinutes,
          price,
          priceRatio,
          generationPrice,
          generationPriceRatio,
          alternateCostDelivered,
          alternateCostUnit,
          alternateCostTrailingDigit,
          numberOfBlockThresholds,
          priceControl
        );
      break;
      }
  #endif // EMBER_CALLBACK_PRICE_CLUSTER_PUBLISH_PRICE
  #ifdef EMBER_CALLBACK_PRICE_CLUSTER_PUBLISH_BLOCK_PERIOD
      case ZCL_PUBLISH_BLOCK_PERIOD_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u providerId;  // Ver.: always
        int32u issuerEventId;  // Ver.: always
        int32u blockPeriodStartTime;  // Ver.: always
        int32u blockPeriodDurationInMinutes;  // Ver.: always
        int8u numberOfPriceTiersAndNumberOfBlockThresholds;  // Ver.: always
        int8u blockPeriodControl;  // Ver.: always
        // Command is fixed length: 17
        if (cmd->bufLen < payloadOffset + 17) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        providerId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        issuerEventId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        blockPeriodStartTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        blockPeriodDurationInMinutes = emberAfGetInt24u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 3;
        numberOfPriceTiersAndNumberOfBlockThresholds = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        blockPeriodControl = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfPriceClusterPublishBlockPeriodCallback(
          providerId,
          issuerEventId,
          blockPeriodStartTime,
          blockPeriodDurationInMinutes,
          numberOfPriceTiersAndNumberOfBlockThresholds,
          blockPeriodControl
        );
      break;
      }
  #endif // EMBER_CALLBACK_PRICE_CLUSTER_PUBLISH_BLOCK_PERIOD
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_PRICE_CLUSTER_CLIENT


// Cluster: Price, server
#ifdef ZCL_USING_PRICE_CLUSTER_SERVER
EmberAfStatus emberAfPriceClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_PRICE_CLUSTER_GET_CURRENT_PRICE
      case ZCL_GET_CURRENT_PRICE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u commandOptions;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        commandOptions = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfPriceClusterGetCurrentPriceCallback(
          commandOptions
        );
      break;
      }
  #endif // EMBER_CALLBACK_PRICE_CLUSTER_GET_CURRENT_PRICE
  #ifdef EMBER_CALLBACK_PRICE_CLUSTER_GET_SCHEDULED_PRICES
      case ZCL_GET_SCHEDULED_PRICES_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u startTime;  // Ver.: always
        int8u numberOfEvents;  // Ver.: always
        // Command is fixed length: 5
        if (cmd->bufLen < payloadOffset + 5) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        startTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        numberOfEvents = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfPriceClusterGetScheduledPricesCallback(
          startTime,
          numberOfEvents
        );
      break;
      }
  #endif // EMBER_CALLBACK_PRICE_CLUSTER_GET_SCHEDULED_PRICES
  #ifdef EMBER_CALLBACK_PRICE_CLUSTER_PRICE_ACKNOWLEDGEMENT
      case ZCL_PRICE_ACKNOWLEDGEMENT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u providerId;  // Ver.: always
        int32u issuerEventId;  // Ver.: always
        int32u priceAckTime;  // Ver.: always
        int8u control;  // Ver.: always
        // Command is fixed length: 13
        if (cmd->bufLen < payloadOffset + 13) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        providerId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        issuerEventId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        priceAckTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        control = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfPriceClusterPriceAcknowledgementCallback(
          providerId,
          issuerEventId,
          priceAckTime,
          control
        );
      break;
      }
  #endif // EMBER_CALLBACK_PRICE_CLUSTER_PRICE_ACKNOWLEDGEMENT
  #ifdef EMBER_CALLBACK_PRICE_CLUSTER_GET_BLOCK_PERIODS
      case ZCL_GET_BLOCK_PERIODS_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u startTime;  // Ver.: always
        int8u numberOfEvents;  // Ver.: always
        // Command is fixed length: 5
        if (cmd->bufLen < payloadOffset + 5) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        startTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        numberOfEvents = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfPriceClusterGetBlockPeriodsCallback(
          startTime,
          numberOfEvents
        );
      break;
      }
  #endif // EMBER_CALLBACK_PRICE_CLUSTER_GET_BLOCK_PERIODS
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_PRICE_CLUSTER_SERVER



// Cluster: Messaging, client
#ifdef ZCL_USING_MESSAGING_CLUSTER_CLIENT
EmberAfStatus emberAfMessagingClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_MESSAGING_CLUSTER_DISPLAY_MESSAGE
      case ZCL_DISPLAY_MESSAGE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u messageId;  // Ver.: always
        int8u messageControl;  // Ver.: always
        int32u startTime;  // Ver.: always
        int16u durationInMinutes;  // Ver.: always
        int8u* message;  // Ver.: always
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        messageId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        messageControl = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        startTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        durationInMinutes = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        message = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfMessagingClusterDisplayMessageCallback(
          messageId,
          messageControl,
          startTime,
          durationInMinutes,
          message
        );
      break;
      }
  #endif // EMBER_CALLBACK_MESSAGING_CLUSTER_DISPLAY_MESSAGE
  #ifdef EMBER_CALLBACK_MESSAGING_CLUSTER_CANCEL_MESSAGE
      case ZCL_CANCEL_MESSAGE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u messageId;  // Ver.: always
        int8u messageControl;  // Ver.: always
        // Command is fixed length: 5
        if (cmd->bufLen < payloadOffset + 5) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        messageId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        messageControl = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfMessagingClusterCancelMessageCallback(
          messageId,
          messageControl
        );
      break;
      }
  #endif // EMBER_CALLBACK_MESSAGING_CLUSTER_CANCEL_MESSAGE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_MESSAGING_CLUSTER_CLIENT


// Cluster: Messaging, server
#ifdef ZCL_USING_MESSAGING_CLUSTER_SERVER
EmberAfStatus emberAfMessagingClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_MESSAGING_CLUSTER_GET_LAST_MESSAGE
      case ZCL_GET_LAST_MESSAGE_COMMAND_ID: {
        // Command is fixed length: 0
        wasHandled = emberAfMessagingClusterGetLastMessageCallback(
        );
      break;
      }
  #endif // EMBER_CALLBACK_MESSAGING_CLUSTER_GET_LAST_MESSAGE
  #ifdef EMBER_CALLBACK_MESSAGING_CLUSTER_MESSAGE_CONFIRMATION
      case ZCL_MESSAGE_CONFIRMATION_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u messageId;  // Ver.: always
        int32u confirmationTime;  // Ver.: always
        // Command is fixed length: 8
        if (cmd->bufLen < payloadOffset + 8) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        messageId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        confirmationTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfMessagingClusterMessageConfirmationCallback(
          messageId,
          confirmationTime
        );
      break;
      }
  #endif // EMBER_CALLBACK_MESSAGING_CLUSTER_MESSAGE_CONFIRMATION
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_MESSAGING_CLUSTER_SERVER



// Cluster: Tunneling, client
#ifdef ZCL_USING_TUNNELING_CLUSTER_CLIENT
EmberAfStatus emberAfTunnelingClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_TUNNELING_CLUSTER_REQUEST_TUNNEL_RESPONSE
      case ZCL_REQUEST_TUNNEL_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u tunnelId;  // Ver.: always
        int8u tunnelStatus;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        tunnelId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        tunnelStatus = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfTunnelingClusterRequestTunnelResponseCallback(
          tunnelId,
          tunnelStatus
        );
      break;
      }
  #endif // EMBER_CALLBACK_TUNNELING_CLUSTER_REQUEST_TUNNEL_RESPONSE
  #ifdef EMBER_CALLBACK_TUNNELING_CLUSTER_TRANSFER_DATA_SERVER_TO_CLIENT
      case ZCL_TRANSFER_DATA_SERVER_TO_CLIENT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u tunnelId;  // Ver.: always
        int8u* data;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        tunnelId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        data = cmd->buffer + payloadOffset;
        wasHandled = emberAfTunnelingClusterTransferDataServerToClientCallback(
          tunnelId,
          data
        );
      break;
      }
  #endif // EMBER_CALLBACK_TUNNELING_CLUSTER_TRANSFER_DATA_SERVER_TO_CLIENT
  #ifdef EMBER_CALLBACK_TUNNELING_CLUSTER_TRANSFER_DATA_ERROR_SERVER_TO_CLIENT
      case ZCL_TRANSFER_DATA_ERROR_SERVER_TO_CLIENT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u tunnelId;  // Ver.: always
        int8u transferDataStatus;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        tunnelId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        transferDataStatus = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfTunnelingClusterTransferDataErrorServerToClientCallback(
          tunnelId,
          transferDataStatus
        );
      break;
      }
  #endif // EMBER_CALLBACK_TUNNELING_CLUSTER_TRANSFER_DATA_ERROR_SERVER_TO_CLIENT
  #ifdef EMBER_CALLBACK_TUNNELING_CLUSTER_ACK_TRANSFER_DATA_SERVER_TO_CLIENT
      case ZCL_ACK_TRANSFER_DATA_SERVER_TO_CLIENT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u tunnelId;  // Ver.: always
        int16u numberOfBytesLeft;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        tunnelId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        numberOfBytesLeft = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfTunnelingClusterAckTransferDataServerToClientCallback(
          tunnelId,
          numberOfBytesLeft
        );
      break;
      }
  #endif // EMBER_CALLBACK_TUNNELING_CLUSTER_ACK_TRANSFER_DATA_SERVER_TO_CLIENT
  #ifdef EMBER_CALLBACK_TUNNELING_CLUSTER_READY_DATA_SERVER_TO_CLIENT
      case ZCL_READY_DATA_SERVER_TO_CLIENT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u tunnelId;  // Ver.: always
        int16u numberOfOctetsLeft;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        tunnelId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        numberOfOctetsLeft = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfTunnelingClusterReadyDataServerToClientCallback(
          tunnelId,
          numberOfOctetsLeft
        );
      break;
      }
  #endif // EMBER_CALLBACK_TUNNELING_CLUSTER_READY_DATA_SERVER_TO_CLIENT
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_TUNNELING_CLUSTER_CLIENT


// Cluster: Tunneling, server
#ifdef ZCL_USING_TUNNELING_CLUSTER_SERVER
EmberAfStatus emberAfTunnelingClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_TUNNELING_CLUSTER_REQUEST_TUNNEL
      case ZCL_REQUEST_TUNNEL_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u protocolId;  // Ver.: always
        int16u manufacturerCode;  // Ver.: always
        int8u flowControlSupport;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        protocolId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        manufacturerCode = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        flowControlSupport = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfTunnelingClusterRequestTunnelCallback(
          protocolId,
          manufacturerCode,
          flowControlSupport
        );
      break;
      }
  #endif // EMBER_CALLBACK_TUNNELING_CLUSTER_REQUEST_TUNNEL
  #ifdef EMBER_CALLBACK_TUNNELING_CLUSTER_CLOSE_TUNNEL
      case ZCL_CLOSE_TUNNEL_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u tunnelId;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        tunnelId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfTunnelingClusterCloseTunnelCallback(
          tunnelId
        );
      break;
      }
  #endif // EMBER_CALLBACK_TUNNELING_CLUSTER_CLOSE_TUNNEL
  #ifdef EMBER_CALLBACK_TUNNELING_CLUSTER_TRANSFER_DATA_CLIENT_TO_SERVER
      case ZCL_TRANSFER_DATA_CLIENT_TO_SERVER_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u tunnelId;  // Ver.: always
        int8u* data;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        tunnelId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        data = cmd->buffer + payloadOffset;
        wasHandled = emberAfTunnelingClusterTransferDataClientToServerCallback(
          tunnelId,
          data
        );
      break;
      }
  #endif // EMBER_CALLBACK_TUNNELING_CLUSTER_TRANSFER_DATA_CLIENT_TO_SERVER
  #ifdef EMBER_CALLBACK_TUNNELING_CLUSTER_TRANSFER_DATA_ERROR_CLIENT_TO_SERVER
      case ZCL_TRANSFER_DATA_ERROR_CLIENT_TO_SERVER_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u tunnelId;  // Ver.: always
        int8u transferDataStatus;  // Ver.: always
        // Command is fixed length: 3
        if (cmd->bufLen < payloadOffset + 3) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        tunnelId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        transferDataStatus = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfTunnelingClusterTransferDataErrorClientToServerCallback(
          tunnelId,
          transferDataStatus
        );
      break;
      }
  #endif // EMBER_CALLBACK_TUNNELING_CLUSTER_TRANSFER_DATA_ERROR_CLIENT_TO_SERVER
  #ifdef EMBER_CALLBACK_TUNNELING_CLUSTER_ACK_TRANSFER_DATA_CLIENT_TO_SERVER
      case ZCL_ACK_TRANSFER_DATA_CLIENT_TO_SERVER_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u tunnelId;  // Ver.: always
        int16u numberOfBytesLeft;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        tunnelId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        numberOfBytesLeft = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfTunnelingClusterAckTransferDataClientToServerCallback(
          tunnelId,
          numberOfBytesLeft
        );
      break;
      }
  #endif // EMBER_CALLBACK_TUNNELING_CLUSTER_ACK_TRANSFER_DATA_CLIENT_TO_SERVER
  #ifdef EMBER_CALLBACK_TUNNELING_CLUSTER_READY_DATA_CLIENT_TO_SERVER
      case ZCL_READY_DATA_CLIENT_TO_SERVER_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u tunnelId;  // Ver.: always
        int16u numberOfOctetsLeft;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        tunnelId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        numberOfOctetsLeft = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfTunnelingClusterReadyDataClientToServerCallback(
          tunnelId,
          numberOfOctetsLeft
        );
      break;
      }
  #endif // EMBER_CALLBACK_TUNNELING_CLUSTER_READY_DATA_CLIENT_TO_SERVER
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_TUNNELING_CLUSTER_SERVER



// Cluster: Prepayment, client
#ifdef ZCL_USING_PREPAYMENT_CLUSTER_CLIENT
EmberAfStatus emberAfPrepaymentClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_PREPAYMENT_CLUSTER_SUPPLY_STATUS_RESPONSE
      case ZCL_SUPPLY_STATUS_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u providerId;  // Ver.: always
        int32u implementationtDateTime;  // Ver.: always
        int8u supplyStatus;  // Ver.: always
        // Command is fixed length: 9
        if (cmd->bufLen < payloadOffset + 9) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        providerId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        implementationtDateTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        supplyStatus = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfPrepaymentClusterSupplyStatusResponseCallback(
          providerId,
          implementationtDateTime,
          supplyStatus
        );
      break;
      }
  #endif // EMBER_CALLBACK_PREPAYMENT_CLUSTER_SUPPLY_STATUS_RESPONSE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_PREPAYMENT_CLUSTER_CLIENT


// Cluster: Prepayment, server
#ifdef ZCL_USING_PREPAYMENT_CLUSTER_SERVER
EmberAfStatus emberAfPrepaymentClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_PREPAYMENT_CLUSTER_SELECT_AVAILABLE_EMERGENCY_CREDIT
      case ZCL_SELECT_AVAILABLE_EMERGENCY_CREDIT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u commandDateTime;  // Ver.: always
        int8u originatingDevice;  // Ver.: always
        int8u* siteId;  // Ver.: always
        int8u* meterSerialNumber;  // Ver.: always
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        commandDateTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        originatingDevice = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        siteId = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1;
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        meterSerialNumber = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfPrepaymentClusterSelectAvailableEmergencyCreditCallback(
          commandDateTime,
          originatingDevice,
          siteId,
          meterSerialNumber
        );
      break;
      }
  #endif // EMBER_CALLBACK_PREPAYMENT_CLUSTER_SELECT_AVAILABLE_EMERGENCY_CREDIT
  #ifdef EMBER_CALLBACK_PREPAYMENT_CLUSTER_CHANGE_SUPPLY
      case ZCL_CHANGE_SUPPLY_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int32u providerId;  // Ver.: always
        int32u requestDateTime;  // Ver.: always
        int8u* siteId;  // Ver.: always
        int8u* meterSerialNumber;  // Ver.: always
        int32u implementationDateTime;  // Ver.: always
        int8u proposedSupplyStatus;  // Ver.: always
        int8u originatorIdSupplyControlBits;  // Ver.: always
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        providerId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        requestDateTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        siteId = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1;
        if (cmd->bufLen < payloadOffset + emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        meterSerialNumber = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen) + 1;
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        implementationDateTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 4;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        proposedSupplyStatus = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        originatorIdSupplyControlBits = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfPrepaymentClusterChangeSupplyCallback(
          providerId,
          requestDateTime,
          siteId,
          meterSerialNumber,
          implementationDateTime,
          proposedSupplyStatus,
          originatorIdSupplyControlBits
        );
      break;
      }
  #endif // EMBER_CALLBACK_PREPAYMENT_CLUSTER_CHANGE_SUPPLY
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_PREPAYMENT_CLUSTER_SERVER



// Cluster: Key establishment, client
#ifdef ZCL_USING_KEY_ESTABLISHMENT_CLUSTER_CLIENT
EmberAfStatus emberAfKeyEstablishmentClusterClientCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_TERMINATE_KEY_ESTABLISHMENT
      case ZCL_TERMINATE_KEY_ESTABLISHMENT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u statusCode;  // Ver.: always
        int8u waitTime;  // Ver.: always
        int16u keyEstablishmentSuite;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        statusCode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        waitTime = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        keyEstablishmentSuite = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfKeyEstablishmentClusterTerminateKeyEstablishmentCallback(
          statusCode,
          waitTime,
          keyEstablishmentSuite
        );
      break;
      }
  #endif // EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_TERMINATE_KEY_ESTABLISHMENT
  #ifdef EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_INITIATE_KEY_ESTABLISHMENT_RESPONSE
      case ZCL_INITIATE_KEY_ESTABLISHMENT_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u requestedKeyEstablishmentSuite;  // Ver.: always
        int8u ephemeralDataGenerateTime;  // Ver.: always
        int8u confirmKeyGenerateTime;  // Ver.: always
        int8u* identity;  // Ver.: always
        // Command is fixed length: 52
        if (cmd->bufLen < payloadOffset + 52) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        requestedKeyEstablishmentSuite = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        ephemeralDataGenerateTime = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        confirmKeyGenerateTime = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        identity = cmd->buffer + payloadOffset;
        wasHandled = emberAfKeyEstablishmentClusterInitiateKeyEstablishmentResponseCallback(
          requestedKeyEstablishmentSuite,
          ephemeralDataGenerateTime,
          confirmKeyGenerateTime,
          identity
        );
      break;
      }
  #endif // EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_INITIATE_KEY_ESTABLISHMENT_RESPONSE
  #ifdef EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_EPHEMERAL_DATA_RESPONSE
      case ZCL_EPHEMERAL_DATA_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* ephemeralData;  // Ver.: always
        // Command is fixed length: 22
        if (cmd->bufLen < payloadOffset + 22) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        ephemeralData = cmd->buffer + payloadOffset;
        wasHandled = emberAfKeyEstablishmentClusterEphemeralDataResponseCallback(
          ephemeralData
        );
      break;
      }
  #endif // EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_EPHEMERAL_DATA_RESPONSE
  #ifdef EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_CONFIRM_KEY_DATA_RESPONSE
      case ZCL_CONFIRM_KEY_DATA_RESPONSE_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* secureMessageAuthenticationCode;  // Ver.: always
        // Command is fixed length: 16
        if (cmd->bufLen < payloadOffset + 16) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        secureMessageAuthenticationCode = cmd->buffer + payloadOffset;
        wasHandled = emberAfKeyEstablishmentClusterConfirmKeyDataResponseCallback(
          secureMessageAuthenticationCode
        );
      break;
      }
  #endif // EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_CONFIRM_KEY_DATA_RESPONSE
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_KEY_ESTABLISHMENT_CLUSTER_CLIENT


// Cluster: Key establishment, server
#ifdef ZCL_USING_KEY_ESTABLISHMENT_CLUSTER_SERVER
EmberAfStatus emberAfKeyEstablishmentClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (!cmd->mfgSpecific) {
    switch( cmd->commandId ) {
  #ifdef EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_INITIATE_KEY_ESTABLISHMENT_REQUEST
      case ZCL_INITIATE_KEY_ESTABLISHMENT_REQUEST_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int16u keyEstablishmentSuite;  // Ver.: always
        int8u ephemeralDataGenerateTime;  // Ver.: always
        int8u confirmKeyGenerateTime;  // Ver.: always
        int8u* identity;  // Ver.: always
        // Command is fixed length: 52
        if (cmd->bufLen < payloadOffset + 52) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        keyEstablishmentSuite = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2;
        ephemeralDataGenerateTime = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        confirmKeyGenerateTime = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        identity = cmd->buffer + payloadOffset;
        wasHandled = emberAfKeyEstablishmentClusterInitiateKeyEstablishmentRequestCallback(
          keyEstablishmentSuite,
          ephemeralDataGenerateTime,
          confirmKeyGenerateTime,
          identity
        );
      break;
      }
  #endif // EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_INITIATE_KEY_ESTABLISHMENT_REQUEST
  #ifdef EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_EPHEMERAL_DATA_REQUEST
      case ZCL_EPHEMERAL_DATA_REQUEST_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* ephemeralData;  // Ver.: always
        // Command is fixed length: 22
        if (cmd->bufLen < payloadOffset + 22) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        ephemeralData = cmd->buffer + payloadOffset;
        wasHandled = emberAfKeyEstablishmentClusterEphemeralDataRequestCallback(
          ephemeralData
        );
      break;
      }
  #endif // EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_EPHEMERAL_DATA_REQUEST
  #ifdef EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_CONFIRM_KEY_DATA_REQUEST
      case ZCL_CONFIRM_KEY_DATA_REQUEST_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u* secureMessageAuthenticationCode;  // Ver.: always
        // Command is fixed length: 16
        if (cmd->bufLen < payloadOffset + 16) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        secureMessageAuthenticationCode = cmd->buffer + payloadOffset;
        wasHandled = emberAfKeyEstablishmentClusterConfirmKeyDataRequestCallback(
          secureMessageAuthenticationCode
        );
      break;
      }
  #endif // EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_CONFIRM_KEY_DATA_REQUEST
  #ifdef EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_TERMINATE_KEY_ESTABLISHMENT
      case ZCL_TERMINATE_KEY_ESTABLISHMENT_COMMAND_ID: {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u statusCode;  // Ver.: always
        int8u waitTime;  // Ver.: always
        int16u keyEstablishmentSuite;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        statusCode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        waitTime = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1;
        keyEstablishmentSuite = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfKeyEstablishmentClusterTerminateKeyEstablishmentCallback(
          statusCode,
          waitTime,
          keyEstablishmentSuite
        );
      break;
      }
  #endif // EMBER_CALLBACK_KEY_ESTABLISHMENT_CLUSTER_TERMINATE_KEY_ESTABLISHMENT
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_KEY_ESTABLISHMENT_CLUSTER_SERVER



// Cluster: Sample Mfg Specific Cluster, client
//    No commands avialable.


// Cluster: Sample Mfg Specific Cluster, server
#ifdef ZCL_USING_SAMPLE_MFG_SPECIFIC_CLUSTER_SERVER
EmberAfStatus emberAfSampleMfgSpecificClusterServerCommandParse( EmberAfClusterCommand *cmd ) {
  boolean wasHandled = FALSE;
  if (cmd->mfgSpecific) {
  #ifdef EMBER_CALLBACK_SAMPLE_MFG_SPECIFIC_CLUSTER_COMMAND_ONE
    if (!wasHandled &&
        (cmd->mfgCode == 0x1002 ) &&
        (cmd->commandId == ZCL_COMMAND_ONE_COMMAND_ID )) {
        int16u payloadOffset = cmd->payloadStartIndex;
        int8u argOne;  // Ver.: always
        // Command is fixed length: 1
        if (cmd->bufLen < payloadOffset + 1) return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
        argOne = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfSampleMfgSpecificClusterCommandOneCallback(
          argOne
        );
    }
  #endif // EMBER_CALLBACK_SAMPLE_MFG_SPECIFIC_CLUSTER_COMMAND_ONE
  } else {
    switch( cmd->commandId ) {
    }
  }
  return (wasHandled ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND);
}
#endif // ZCL_USING_SAMPLE_MFG_SPECIFIC_CLUSTER_SERVER



