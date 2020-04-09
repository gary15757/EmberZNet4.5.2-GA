// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generateCommandIDs()
//

// Enclosing macro to prevent multiple inclusion
#ifndef __EMBER_AF_COMMAND_ID__
#define __EMBER_AF_COMMAND_ID__


// Global commands

// Either direction
#define ZCL_READ_ATTRIBUTES_COMMAND_ID                       0x00    // Ver.: always
#define ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID              0x01    // Ver.: always
#define ZCL_WRITE_ATTRIBUTES_COMMAND_ID                      0x02    // Ver.: always
#define ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID            0x03    // Ver.: always
#define ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID             0x04    // Ver.: always
#define ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID          0x05    // Ver.: always
#define ZCL_CONFIGURE_REPORTING_COMMAND_ID                   0x06    // Ver.: always
#define ZCL_CONFIGURE_REPORTING_RESPONSE_COMMAND_ID          0x07    // Ver.: always
#define ZCL_READ_REPORTING_CONFIGURATION_COMMAND_ID          0x08    // Ver.: always
#define ZCL_READ_REPORTING_CONFIGURATION_RESPONSE_COMMAND_ID 0x09    // Ver.: always
#define ZCL_REPORT_ATTRIBUTES_COMMAND_ID                     0x0A    // Ver.: always
#define ZCL_DEFAULT_RESPONSE_COMMAND_ID                      0x0B    // Ver.: always
#define ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID                   0x0C    // Ver.: always
#define ZCL_DISCOVER_ATTRIBUTES_RESPONSE_COMMAND_ID          0x0D    // Ver.: always
// Command types for cluster: Basic
// Cluster specification level: 075123r03

// Client to server
#define ZCL_RESET_TO_FACTORY_DEFAULTS_COMMAND_ID 0x00    // Ver.: always


// Command types for cluster: Identify
// Cluster specification level: 075123r03

// Server to client
#define ZCL_IDENTIFY_QUERY_RESPONSE_COMMAND_ID 0x00    // Ver.: always

// Client to server
#define ZCL_IDENTIFY_COMMAND_ID 0x00    // Ver.: always
#define ZCL_IDENTIFY_QUERY_COMMAND_ID 0x01    // Ver.: always


// Command types for cluster: Groups
// Cluster specification level: 075123r03

// Server to client
#define ZCL_ADD_GROUP_RESPONSE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_VIEW_GROUP_RESPONSE_COMMAND_ID 0x01    // Ver.: always
#define ZCL_GET_GROUP_MEMBERSHIP_RESPONSE_COMMAND_ID 0x02    // Ver.: always
#define ZCL_REMOVE_GROUP_RESPONSE_COMMAND_ID 0x03    // Ver.: always

// Client to server
#define ZCL_ADD_GROUP_COMMAND_ID 0x00    // Ver.: always
#define ZCL_VIEW_GROUP_COMMAND_ID 0x01    // Ver.: always
#define ZCL_GET_GROUP_MEMBERSHIP_COMMAND_ID 0x02    // Ver.: always
#define ZCL_REMOVE_GROUP_COMMAND_ID 0x03    // Ver.: always
#define ZCL_REMOVE_ALL_GROUPS_COMMAND_ID 0x04    // Ver.: always
#define ZCL_ADD_GROUP_IF_IDENTIFYING_COMMAND_ID 0x05    // Ver.: always


// Command types for cluster: Scenes
// Cluster specification level: 075123r03

// Server to client
#define ZCL_ADD_SCENE_RESPONSE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_VIEW_SCENE_RESPONSE_COMMAND_ID 0x01    // Ver.: always
#define ZCL_REMOVE_SCENE_RESPONSE_COMMAND_ID 0x02    // Ver.: always
#define ZCL_REMOVE_ALL_SCENES_RESPONSE_COMMAND_ID 0x03    // Ver.: always
#define ZCL_STORE_SCENE_RESPONSE_COMMAND_ID 0x04    // Ver.: always
#define ZCL_GET_SCENE_MEMBERSHIP_RESPONSE_COMMAND_ID 0x06    // Ver.: always

// Client to server
#define ZCL_ADD_SCENE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_VIEW_SCENE_COMMAND_ID 0x01    // Ver.: always
#define ZCL_REMOVE_SCENE_COMMAND_ID 0x02    // Ver.: always
#define ZCL_REMOVE_ALL_SCENES_COMMAND_ID 0x03    // Ver.: always
#define ZCL_STORE_SCENE_COMMAND_ID 0x04    // Ver.: always
#define ZCL_RECALL_SCENE_COMMAND_ID 0x05    // Ver.: always
#define ZCL_GET_SCENE_MEMBERSHIP_COMMAND_ID 0x06    // Ver.: always


// Command types for cluster: On/off
// Cluster specification level: 075123r03

// Client to server
#define ZCL_OFF_COMMAND_ID 0x00    // Ver.: always
#define ZCL_ON_COMMAND_ID 0x01    // Ver.: always
#define ZCL_TOGGLE_COMMAND_ID 0x02    // Ver.: always
#define ZCL_SAMPLE_MFG_SPECIFIC_OFF_WITH_TRANSITION_COMMAND_ID 0x00    // Ver.: always mfgCode: 0x1002
#define ZCL_SAMPLE_MFG_SPECIFIC_ON_WITH_TRANSITION_COMMAND_ID 0x01    // Ver.: always mfgCode: 0x1002
#define ZCL_SAMPLE_MFG_SPECIFIC_TOGGLE_WITH_TRANSITION_COMMAND_ID 0x02    // Ver.: always mfgCode: 0x1002


// Command types for cluster: Level Control
// Cluster specification level: 075123r03

// Client to server
#define ZCL_MOVE_TO_LEVEL_COMMAND_ID 0x00    // Ver.: always
#define ZCL_MOVE_COMMAND_ID 0x01    // Ver.: always
#define ZCL_STEP_COMMAND_ID 0x02    // Ver.: always
#define ZCL_STOP_COMMAND_ID 0x03    // Ver.: always
#define ZCL_MOVE_TO_LEVEL_WITH_ON_OFF_COMMAND_ID 0x04    // Ver.: always
#define ZCL_MOVE_WITH_ON_OFF_COMMAND_ID 0x05    // Ver.: always
#define ZCL_STEP_WITH_ON_OFF_COMMAND_ID 0x06    // Ver.: always
#define ZCL_STOP_WITH_ON_OFF_COMMAND_ID 0x07    // Ver.: always


// Command types for cluster: Alarms
// Cluster specification level: 075123r03

// Server to client
#define ZCL_ALARM_COMMAND_ID 0x00    // Ver.: always
#define ZCL_GET_ALARM_RESPONSE_COMMAND_ID 0x01    // Ver.: always

// Client to server
#define ZCL_RESET_ALARM_COMMAND_ID 0x00    // Ver.: always
#define ZCL_RESET_ALL_ALARMS_COMMAND_ID 0x01    // Ver.: always
#define ZCL_GET_ALARM_COMMAND_ID 0x02    // Ver.: always
#define ZCL_RESET_ALARM_LOG_COMMAND_ID 0x03    // Ver.: always


// Command types for cluster: RSSI Location
// Cluster specification level: 075123r03

// Server to client
#define ZCL_DEVICE_CONFIGURATION_RESPONSE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_LOCATION_DATA_RESPONSE_COMMAND_ID 0x01    // Ver.: always
#define ZCL_LOCATION_DATA_NOTIFICATION_COMMAND_ID 0x02    // Ver.: always
#define ZCL_COMPACT_LOCATION_DATA_NOTIFICATION_COMMAND_ID 0x03    // Ver.: always
#define ZCL_RSSI_PING_COMMAND_ID 0x04    // Ver.: always
#define ZCL_RSSI_REQUEST_COMMAND_ID 0x05    // Ver.: always
#define ZCL_REPORT_RSSI_MEASUREMENTS_COMMAND_ID 0x06    // Ver.: always
#define ZCL_REQUEST_OWN_LOCATION_COMMAND_ID 0x07    // Ver.: always

// Client to server
#define ZCL_SET_ABSOLUTE_LOCATION_COMMAND_ID 0x00    // Ver.: always
#define ZCL_SET_DEVICE_CONFIGURATION_COMMAND_ID 0x01    // Ver.: always
#define ZCL_GET_DEVICE_CONFIGURATION_COMMAND_ID 0x02    // Ver.: always
#define ZCL_GET_LOCATION_DATA_COMMAND_ID 0x03    // Ver.: always
#define ZCL_RSSI_RESPONSE_COMMAND_ID 0x04    // Ver.: always
#define ZCL_SEND_PINGS_COMMAND_ID 0x05    // Ver.: always
#define ZCL_ANCHOR_NODE_ANNOUNCE_COMMAND_ID 0x06    // Ver.: always


// Command types for cluster: Commissioning
// Cluster specification level: 075123r03

// Server to client
#define ZCL_RESTART_DEVICE_RESPONSE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_SAVE_STARTUP_PARAMETERS_RESPONSE_COMMAND_ID 0x01    // Ver.: always
#define ZCL_RESTORE_STARTUP_PARAMETERS_RESPONSE_COMMAND_ID 0x02    // Ver.: always
#define ZCL_RESET_STARTUP_PARAMETERS_RESPONSE_COMMAND_ID 0x03    // Ver.: always

// Client to server
#define ZCL_RESTART_DEVICE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_SAVE_STARTUP_PARAMETERS_COMMAND_ID 0x01    // Ver.: always
#define ZCL_RESTORE_STARTUP_PARAMETERS_COMMAND_ID 0x02    // Ver.: always
#define ZCL_RESET_STARTUP_PARAMETERS_COMMAND_ID 0x03    // Ver.: always


// Command types for cluster: Thermostat
// Cluster specification level: 1.1, 053520r27

// Client to server
#define ZCL_SETPOINT_RAISE_LOWER_COMMAND_ID 0x00    // Ver.: always


// Command types for cluster: Color Control
// Cluster specification level: 1.1, 053520r27

// Client to server
#define ZCL_MOVE_TO_HUE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_MOVE_HUE_COMMAND_ID 0x01    // Ver.: always
#define ZCL_STEP_HUE_COMMAND_ID 0x02    // Ver.: always
#define ZCL_MOVE_TO_SATURATION_COMMAND_ID 0x03    // Ver.: always
#define ZCL_MOVE_SATURATION_COMMAND_ID 0x04    // Ver.: always
#define ZCL_STEP_SATURATION_COMMAND_ID 0x05    // Ver.: always
#define ZCL_MOVE_TO_HUE_AND_SATURATION_COMMAND_ID 0x06    // Ver.: always
#define ZCL_MOVE_TO_COLOR_COMMAND_ID 0x07    // Ver.: always
#define ZCL_MOVE_COLOR_COMMAND_ID 0x08    // Ver.: always
#define ZCL_STEP_COLOR_COMMAND_ID 0x09    // Ver.: always
#define ZCL_MOVE_TO_COLOR_TEMPERATURE_COMMAND_ID 0x0A    // Ver.: always


// Command types for cluster: IAS Zone
// Cluster specification level: 1.1, 053520r27

// Server to client
#define ZCL_ZONE_STATUS_CHANGE_NOTIFICATION_COMMAND_ID 0x00    // Ver.: always
#define ZCL_ZONE_ENROLL_REQUEST_COMMAND_ID 0x01    // Ver.: always

// Client to server
#define ZCL_ZONE_ENROLL_RESPONSE_COMMAND_ID 0x00    // Ver.: always


// Command types for cluster: IAS ACE
// Cluster specification level: 1.1, 053520r27

// Server to client
#define ZCL_ARM_RESPONSE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_GET_ZONE_ID_MAP_RESPONSE_COMMAND_ID 0x01    // Ver.: always
#define ZCL_GET_ZONE_INFORMATION_RESPONSE_COMMAND_ID 0x02    // Ver.: always

// Client to server
#define ZCL_ARM_COMMAND_ID 0x00    // Ver.: always
#define ZCL_BYPASS_COMMAND_ID 0x01    // Ver.: always
#define ZCL_EMERGENCY_COMMAND_ID 0x02    // Ver.: always
#define ZCL_FIRE_COMMAND_ID 0x03    // Ver.: always
#define ZCL_PANIC_COMMAND_ID 0x04    // Ver.: always
#define ZCL_GET_ZONE_ID_MAP_COMMAND_ID 0x05    // Ver.: always
#define ZCL_GET_ZONE_INFORMATION_COMMAND_ID 0x06    // Ver.: always


// Command types for cluster: IAS WD
// Cluster specification level: 1.1, 053520r27

// Client to server
#define ZCL_START_WARNING_COMMAND_ID 0x00    // Ver.: always
#define ZCL_SQUAWK_COMMAND_ID 0x01    // Ver.: always


// Command types for cluster: Door Lock
// Cluster specification level: 1.1, 053520r27

// Server to client
#define ZCL_LOCK_DOOR_RESPONSE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_UNLOCK_DOOR_RESPONSE_COMMAND_ID 0x01    // Ver.: always

// Client to server
#define ZCL_LOCK_DOOR_COMMAND_ID 0x00    // Ver.: always
#define ZCL_UNLOCK_DOOR_COMMAND_ID 0x01    // Ver.: always


// Command types for cluster: Window Covering
// Cluster specification level: 1.1, 053520r27

// Client to server
#define ZCL_WINDOW_COVERING_UP_OPEN_COMMAND_ID 0x00    // Ver.: always
#define ZCL_WINDOW_COVERING_DOWN_CLOSE_COMMAND_ID 0x01    // Ver.: always
#define ZCL_WINDOW_COVERING_STOP_COMMAND_ID 0x02    // Ver.: always
#define ZCL_WINDOW_COVERING_GO_TO_LIFT_SETPOINT_COMMAND_ID 0x03    // Ver.: always
#define ZCL_WINDOW_COVERING_GO_TO_LIFT_VALUE_COMMAND_ID 0x04    // Ver.: always
#define ZCL_WINDOW_COVERING_GO_TO_LIFT_PERCENTAGE_COMMAND_ID 0x05    // Ver.: always
#define ZCL_WINDOW_COVERING_GO_TO_TILT_SETPOINT_COMMAND_ID 0x06    // Ver.: always
#define ZCL_WINDOW_COVERING_GO_TO_TILT_VALUE_COMMAND_ID 0x07    // Ver.: always
#define ZCL_WINDOW_COVERING_GO_TO_TILT_PERCENTAGE_COMMAND_ID 0x08    // Ver.: always
#define ZCL_WINDOW_COVERING_GO_TO_PROGRAM_SETPOINT_COMMAND_ID 0x09    // Ver.: always


// Command types for cluster: Generic Tunnel
// Cluster specification level: unofficial

// Server to client
#define ZCL_MATCH_PROTOCOL_ADDRESS_RESPONSE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_ADVERTISE_PROTOCOL_ADDRESS_COMMAND_ID 0x01    // Ver.: always

// Client to server
#define ZCL_MATCH_PROTOCOL_ADDRESS_COMMAND_ID 0x00    // Ver.: always


// Command types for cluster: BACnet Protocol Tunnel
// Cluster specification level: unofficial

// Client to server
#define ZCL_TRANSFER_NPDU_COMMAND_ID 0x00    // Ver.: always


// Command types for cluster: Over the Air Bootloading Cluster
// Cluster specification level: 075123r03

// Server to client
#define ZCL_IMAGE_NOTIFY_COMMAND_ID 0x00    // Ver.: always
#define ZCL_QUERY_NEXT_IMAGE_RESPONSE_COMMAND_ID 0x02    // Ver.: always
#define ZCL_IMAGE_BLOCK_RESPONSE_COMMAND_ID 0x05    // Ver.: always
#define ZCL_UPGRADE_END_RESPONSE_COMMAND_ID 0x07    // Ver.: always
#define ZCL_QUERY_SPECIFIC_FILE_RESPONSE_COMMAND_ID 0x09    // Ver.: always

// Client to server
#define ZCL_QUERY_NEXT_IMAGE_REQUEST_COMMAND_ID 0x01    // Ver.: always
#define ZCL_IMAGE_BLOCK_REQUEST_COMMAND_ID 0x03    // Ver.: always
#define ZCL_IMAGE_PAGE_REQUEST_COMMAND_ID 0x04    // Ver.: always
#define ZCL_UPGRADE_END_REQUEST_COMMAND_ID 0x06    // Ver.: always
#define ZCL_QUERY_SPECIFIC_FILE_REQUEST_COMMAND_ID 0x08    // Ver.: always


// Command types for cluster: Demand Response and Load Control
// Cluster specification level: 1.1, 105638r09

// Server to client
#define ZCL_LOAD_CONTROL_EVENT_COMMAND_ID 0x00    // Ver.: always
#define ZCL_CANCEL_LOAD_CONTROL_EVENT_COMMAND_ID 0x01    // Ver.: always
#define ZCL_CANCEL_ALL_LOAD_CONTROL_EVENTS_COMMAND_ID 0x02    // Ver.: always

// Client to server
#define ZCL_REPORT_EVENT_STATUS_COMMAND_ID 0x00    // Ver.: always
#define ZCL_GET_SCHEDULED_EVENTS_COMMAND_ID 0x01    // Ver.: always


// Command types for cluster: Simple Metering
// Cluster specification level: 1.1, 105638r09

// Server to client
#define ZCL_GET_PROFILE_RESPONSE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_REQUEST_MIRROR_COMMAND_ID 0x01    // Ver.: always
#define ZCL_REMOVE_MIRROR_COMMAND_ID 0x02    // Ver.: always
#define ZCL_REQUEST_FAST_POLL_MODE_RESPONSE_COMMAND_ID 0x03    // Ver.: always

// Client to server
#define ZCL_GET_PROFILE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_REQUEST_MIRROR_RESPONSE_COMMAND_ID 0x01    // Ver.: always
#define ZCL_MIRROR_REMOVED_COMMAND_ID 0x02    // Ver.: always
#define ZCL_REQUEST_FAST_POLL_MODE_COMMAND_ID 0x03    // Ver.: always


// Command types for cluster: Price
// Cluster specification level: 1.1, 105638r09

// Server to client
#define ZCL_PUBLISH_PRICE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_PUBLISH_BLOCK_PERIOD_COMMAND_ID 0x01    // Ver.: always

// Client to server
#define ZCL_GET_CURRENT_PRICE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_GET_SCHEDULED_PRICES_COMMAND_ID 0x01    // Ver.: always
#define ZCL_PRICE_ACKNOWLEDGEMENT_COMMAND_ID 0x02    // Ver.: always
#define ZCL_GET_BLOCK_PERIODS_COMMAND_ID 0x03    // Ver.: always


// Command types for cluster: Messaging
// Cluster specification level: 1.1, 105638r09

// Server to client
#define ZCL_DISPLAY_MESSAGE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_CANCEL_MESSAGE_COMMAND_ID 0x01    // Ver.: always

// Client to server
#define ZCL_GET_LAST_MESSAGE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_MESSAGE_CONFIRMATION_COMMAND_ID 0x01    // Ver.: always


// Command types for cluster: Tunneling
// Cluster specification level: 1.1, 105638r09

// Server to client
#define ZCL_REQUEST_TUNNEL_RESPONSE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_TRANSFER_DATA_SERVER_TO_CLIENT_COMMAND_ID 0x01    // Ver.: always
#define ZCL_TRANSFER_DATA_ERROR_SERVER_TO_CLIENT_COMMAND_ID 0x02    // Ver.: always
#define ZCL_ACK_TRANSFER_DATA_SERVER_TO_CLIENT_COMMAND_ID 0x03    // Ver.: always
#define ZCL_READY_DATA_SERVER_TO_CLIENT_COMMAND_ID 0x04    // Ver.: always

// Client to server
#define ZCL_REQUEST_TUNNEL_COMMAND_ID 0x00    // Ver.: always
#define ZCL_CLOSE_TUNNEL_COMMAND_ID 0x01    // Ver.: always
#define ZCL_TRANSFER_DATA_CLIENT_TO_SERVER_COMMAND_ID 0x02    // Ver.: always
#define ZCL_TRANSFER_DATA_ERROR_CLIENT_TO_SERVER_COMMAND_ID 0x03    // Ver.: always
#define ZCL_ACK_TRANSFER_DATA_CLIENT_TO_SERVER_COMMAND_ID 0x04    // Ver.: always
#define ZCL_READY_DATA_CLIENT_TO_SERVER_COMMAND_ID 0x05    // Ver.: always


// Command types for cluster: Prepayment
// Cluster specification level: 1.1, 105638r09

// Server to client
#define ZCL_SUPPLY_STATUS_RESPONSE_COMMAND_ID 0x00    // Ver.: always

// Client to server
#define ZCL_SELECT_AVAILABLE_EMERGENCY_CREDIT_COMMAND_ID 0x00    // Ver.: always
#define ZCL_CHANGE_SUPPLY_COMMAND_ID 0x01    // Ver.: always


// Command types for cluster: Key establishment
// Cluster specification level: 1.1, 105638r09

// Server to client
#define ZCL_INITIATE_KEY_ESTABLISHMENT_RESPONSE_COMMAND_ID 0x00    // Ver.: always
#define ZCL_EPHEMERAL_DATA_RESPONSE_COMMAND_ID 0x01    // Ver.: always
#define ZCL_CONFIRM_KEY_DATA_RESPONSE_COMMAND_ID 0x02    // Ver.: always

// Client to server
#define ZCL_INITIATE_KEY_ESTABLISHMENT_REQUEST_COMMAND_ID 0x00    // Ver.: always
#define ZCL_EPHEMERAL_DATA_REQUEST_COMMAND_ID 0x01    // Ver.: always
#define ZCL_CONFIRM_KEY_DATA_REQUEST_COMMAND_ID 0x02    // Ver.: always

// Either direction
#define ZCL_TERMINATE_KEY_ESTABLISHMENT_COMMAND_ID 0x03    // Ver.: always


// Command types for cluster: Sample Mfg Specific Cluster
// Cluster specification level: UNKNOWN

// Client to server
#define ZCL_COMMAND_ONE_COMMAND_ID 0x00    // Ver.: always mfgCode: 0x1002


#endif // __EMBER_AF_COMMAND_ID__
