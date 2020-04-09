// File: ezsp-enum-decode.c
//
// *** Generated file. Do not edit! ***
// 
// Description: Convert an enumerated value into a human-readable string.
// 
// Copyright 2007 by Ember Corporation. All rights reserved.                *80*

#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "ezsp-enum.h"


const char *decodeEzspConfigId(int8u value) {
  switch(value) {
  case EZSP_CONFIG_PACKET_BUFFER_COUNT: return "EZSP_CONFIG_PACKET_BUFFER_COUNT";
  case EZSP_CONFIG_NEIGHBOR_TABLE_SIZE: return "EZSP_CONFIG_NEIGHBOR_TABLE_SIZE";
  case EZSP_CONFIG_APS_UNICAST_MESSAGE_COUNT: return "EZSP_CONFIG_APS_UNICAST_MESSAGE_COUNT";
  case EZSP_CONFIG_BINDING_TABLE_SIZE: return "EZSP_CONFIG_BINDING_TABLE_SIZE";
  case EZSP_CONFIG_ADDRESS_TABLE_SIZE: return "EZSP_CONFIG_ADDRESS_TABLE_SIZE";
  case EZSP_CONFIG_MULTICAST_TABLE_SIZE: return "EZSP_CONFIG_MULTICAST_TABLE_SIZE";
  case EZSP_CONFIG_ROUTE_TABLE_SIZE: return "EZSP_CONFIG_ROUTE_TABLE_SIZE";
  case EZSP_CONFIG_DISCOVERY_TABLE_SIZE: return "EZSP_CONFIG_DISCOVERY_TABLE_SIZE";
  case EZSP_CONFIG_BROADCAST_ALARM_DATA_SIZE: return "EZSP_CONFIG_BROADCAST_ALARM_DATA_SIZE";
  case EZSP_CONFIG_UNICAST_ALARM_DATA_SIZE: return "EZSP_CONFIG_UNICAST_ALARM_DATA_SIZE";
  case EZSP_CONFIG_STACK_PROFILE: return "EZSP_CONFIG_STACK_PROFILE";
  case EZSP_CONFIG_SECURITY_LEVEL: return "EZSP_CONFIG_SECURITY_LEVEL";
  case EZSP_CONFIG_MAX_HOPS: return "EZSP_CONFIG_MAX_HOPS";
  case EZSP_CONFIG_MAX_END_DEVICE_CHILDREN: return "EZSP_CONFIG_MAX_END_DEVICE_CHILDREN";
  case EZSP_CONFIG_INDIRECT_TRANSMISSION_TIMEOUT: return "EZSP_CONFIG_INDIRECT_TRANSMISSION_TIMEOUT";
  case EZSP_CONFIG_END_DEVICE_POLL_TIMEOUT: return "EZSP_CONFIG_END_DEVICE_POLL_TIMEOUT";
  case EZSP_CONFIG_MOBILE_NODE_POLL_TIMEOUT: return "EZSP_CONFIG_MOBILE_NODE_POLL_TIMEOUT";
  case EZSP_CONFIG_RESERVED_MOBILE_CHILD_ENTRIES: return "EZSP_CONFIG_RESERVED_MOBILE_CHILD_ENTRIES";
  case EZSP_CONFIG_TX_POWER_MODE: return "EZSP_CONFIG_TX_POWER_MODE";
  case EZSP_CONFIG_DISABLE_RELAY: return "EZSP_CONFIG_DISABLE_RELAY";
  case EZSP_CONFIG_TRUST_CENTER_ADDRESS_CACHE_SIZE: return "EZSP_CONFIG_TRUST_CENTER_ADDRESS_CACHE_SIZE";
  case EZSP_CONFIG_SOURCE_ROUTE_TABLE_SIZE: return "EZSP_CONFIG_SOURCE_ROUTE_TABLE_SIZE";
  case EZSP_CONFIG_END_DEVICE_POLL_TIMEOUT_SHIFT: return "EZSP_CONFIG_END_DEVICE_POLL_TIMEOUT_SHIFT";
  case EZSP_CONFIG_FRAGMENT_WINDOW_SIZE: return "EZSP_CONFIG_FRAGMENT_WINDOW_SIZE";
  case EZSP_CONFIG_FRAGMENT_DELAY_MS: return "EZSP_CONFIG_FRAGMENT_DELAY_MS";
  case EZSP_CONFIG_KEY_TABLE_SIZE: return "EZSP_CONFIG_KEY_TABLE_SIZE";
  case EZSP_CONFIG_APS_ACK_TIMEOUT: return "EZSP_CONFIG_APS_ACK_TIMEOUT";
  case EZSP_CONFIG_ACTIVE_SCAN_DURATION: return "EZSP_CONFIG_ACTIVE_SCAN_DURATION";
  case EZSP_CONFIG_END_DEVICE_BIND_TIMEOUT: return "EZSP_CONFIG_END_DEVICE_BIND_TIMEOUT";
  case EZSP_CONFIG_PAN_ID_CONFLICT_REPORT_THRESHOLD: return "EZSP_CONFIG_PAN_ID_CONFLICT_REPORT_THRESHOLD";
  case EZSP_CONFIG_REQUEST_KEY_TIMEOUT: return "EZSP_CONFIG_REQUEST_KEY_TIMEOUT";
  case EZSP_CONFIG_CERTIFICATE_TABLE_SIZE: return "EZSP_CONFIG_CERTIFICATE_TABLE_SIZE";
  case EZSP_CONFIG_APPLICATION_ZDO_FLAGS: return "EZSP_CONFIG_APPLICATION_ZDO_FLAGS";
  case EZSP_CONFIG_BROADCAST_TABLE_SIZE: return "EZSP_CONFIG_BROADCAST_TABLE_SIZE";
  }
  return "*** Not enumerated. ***";
}

const char *decodeEzspValueId(int8u value) {
  switch(value) {
  case EZSP_VALUE_TOKEN_STACK_NODE_DATA: return "EZSP_VALUE_TOKEN_STACK_NODE_DATA";
  case EZSP_VALUE_MAC_PASSTHROUGH_FLAGS: return "EZSP_VALUE_MAC_PASSTHROUGH_FLAGS";
  case EZSP_VALUE_EMBERNET_PASSTHROUGH_SOURCE_ADDRESS: return "EZSP_VALUE_EMBERNET_PASSTHROUGH_SOURCE_ADDRESS";
  case EZSP_VALUE_FREE_BUFFERS: return "EZSP_VALUE_FREE_BUFFERS";
  case EZSP_VALUE_UART_SYNCH_CALLBACKS: return "EZSP_VALUE_UART_SYNCH_CALLBACKS";
  case EZSP_VALUE_MAXIMUM_INCOMING_TRANSFER_SIZE: return "EZSP_VALUE_MAXIMUM_INCOMING_TRANSFER_SIZE";
  case EZSP_VALUE_MAXIMUM_OUTGOING_TRANSFER_SIZE: return "EZSP_VALUE_MAXIMUM_OUTGOING_TRANSFER_SIZE";
  case EZSP_VALUE_STACK_TOKEN_WRITING: return "EZSP_VALUE_STACK_TOKEN_WRITING";
  case EZSP_VALUE_STACK_IS_PERFORMING_REJOIN: return "EZSP_VALUE_STACK_IS_PERFORMING_REJOIN";
  }
  return "*** Not enumerated. ***";
}

const char *decodeEzspPolicyId(int8u value) {
  switch(value) {
  case EZSP_TRUST_CENTER_POLICY: return "EZSP_TRUST_CENTER_POLICY";
  case EZSP_BINDING_MODIFICATION_POLICY: return "EZSP_BINDING_MODIFICATION_POLICY";
  case EZSP_UNICAST_REPLIES_POLICY: return "EZSP_UNICAST_REPLIES_POLICY";
  case EZSP_POLL_HANDLER_POLICY: return "EZSP_POLL_HANDLER_POLICY";
  case EZSP_MESSAGE_CONTENTS_IN_CALLBACK_POLICY: return "EZSP_MESSAGE_CONTENTS_IN_CALLBACK_POLICY";
  case EZSP_TC_KEY_REQUEST_POLICY: return "EZSP_TC_KEY_REQUEST_POLICY";
  case EZSP_APP_KEY_REQUEST_POLICY: return "EZSP_APP_KEY_REQUEST_POLICY";
  }
  return "*** Not enumerated. ***";
}

const char *decodeEzspDecisionId(int8u value) {
  switch(value) {
  case EZSP_ALLOW_JOINS: return "EZSP_ALLOW_JOINS";
  case EZSP_ALLOW_JOINS_REJOINS_HAVE_LINK_KEY: return "EZSP_ALLOW_JOINS_REJOINS_HAVE_LINK_KEY";
  case EZSP_ALLOW_PRECONFIGURED_KEY_JOINS: return "EZSP_ALLOW_PRECONFIGURED_KEY_JOINS";
  case EZSP_ALLOW_REJOINS_ONLY: return "EZSP_ALLOW_REJOINS_ONLY";
  case EZSP_DISALLOW_ALL_JOINS_AND_REJOINS: return "EZSP_DISALLOW_ALL_JOINS_AND_REJOINS";
  case EZSP_DISALLOW_BINDING_MODIFICATION: return "EZSP_DISALLOW_BINDING_MODIFICATION";
  case EZSP_ALLOW_BINDING_MODIFICATION: return "EZSP_ALLOW_BINDING_MODIFICATION";
  case EZSP_HOST_WILL_NOT_SUPPLY_REPLY: return "EZSP_HOST_WILL_NOT_SUPPLY_REPLY";
  case EZSP_HOST_WILL_SUPPLY_REPLY: return "EZSP_HOST_WILL_SUPPLY_REPLY";
  case EZSP_POLL_HANDLER_IGNORE: return "EZSP_POLL_HANDLER_IGNORE";
  case EZSP_POLL_HANDLER_CALLBACK: return "EZSP_POLL_HANDLER_CALLBACK";
  case EZSP_MESSAGE_TAG_ONLY_IN_CALLBACK: return "EZSP_MESSAGE_TAG_ONLY_IN_CALLBACK";
  case EZSP_MESSAGE_TAG_AND_CONTENTS_IN_CALLBACK: return "EZSP_MESSAGE_TAG_AND_CONTENTS_IN_CALLBACK";
  case EZSP_DENY_TC_KEY_REQUESTS: return "EZSP_DENY_TC_KEY_REQUESTS";
  case EZSP_ALLOW_TC_KEY_REQUESTS: return "EZSP_ALLOW_TC_KEY_REQUESTS";
  case EZSP_DENY_APP_KEY_REQUESTS: return "EZSP_DENY_APP_KEY_REQUESTS";
  case EZSP_ALLOW_APP_KEY_REQUESTS: return "EZSP_ALLOW_APP_KEY_REQUESTS";
  }
  return "*** Not enumerated. ***";
}

const char *decodeEzspMfgTokenId(int8u value) {
  switch(value) {
  case EZSP_MFG_CUSTOM_VERSION: return "EZSP_MFG_CUSTOM_VERSION";
  case EZSP_MFG_STRING: return "EZSP_MFG_STRING";
  case EZSP_MFG_BOARD_NAME: return "EZSP_MFG_BOARD_NAME";
  case EZSP_MFG_MANUF_ID: return "EZSP_MFG_MANUF_ID";
  case EZSP_MFG_PHY_CONFIG: return "EZSP_MFG_PHY_CONFIG";
  case EZSP_MFG_BOOTLOAD_AES_KEY: return "EZSP_MFG_BOOTLOAD_AES_KEY";
  case EZSP_MFG_ASH_CONFIG: return "EZSP_MFG_ASH_CONFIG";
  case EZSP_MFG_EZSP_STORAGE: return "EZSP_MFG_EZSP_STORAGE";
  case EZSP_STACK_CAL_DATA: return "EZSP_STACK_CAL_DATA";
  case EZSP_MFG_CBKE_DATA: return "EZSP_MFG_CBKE_DATA";
  case EZSP_MFG_INSTALLATION_CODE: return "EZSP_MFG_INSTALLATION_CODE";
  case EZSP_STACK_CAL_FILTER: return "EZSP_STACK_CAL_FILTER";
  }
  return "*** Not enumerated. ***";
}

const char *decodeEzspStatus(int8u value) {
  switch(value) {
  case EZSP_SUCCESS: return "EZSP_SUCCESS";
  case EZSP_SPI_ERR_FATAL: return "EZSP_SPI_ERR_FATAL";
  case EZSP_SPI_ERR_NCP_RESET: return "EZSP_SPI_ERR_NCP_RESET";
  case EZSP_SPI_ERR_OVERSIZED_EZSP_FRAME: return "EZSP_SPI_ERR_OVERSIZED_EZSP_FRAME";
  case EZSP_SPI_ERR_ABORTED_TRANSACTION: return "EZSP_SPI_ERR_ABORTED_TRANSACTION";
  case EZSP_SPI_ERR_MISSING_FRAME_TERMINATOR: return "EZSP_SPI_ERR_MISSING_FRAME_TERMINATOR";
  case EZSP_SPI_ERR_WAIT_SECTION_TIMEOUT: return "EZSP_SPI_ERR_WAIT_SECTION_TIMEOUT";
  case EZSP_SPI_ERR_NO_FRAME_TERMINATOR: return "EZSP_SPI_ERR_NO_FRAME_TERMINATOR";
  case EZSP_SPI_ERR_EZSP_COMMAND_OVERSIZED: return "EZSP_SPI_ERR_EZSP_COMMAND_OVERSIZED";
  case EZSP_SPI_ERR_EZSP_RESPONSE_OVERSIZED: return "EZSP_SPI_ERR_EZSP_RESPONSE_OVERSIZED";
  case EZSP_SPI_WAITING_FOR_RESPONSE: return "EZSP_SPI_WAITING_FOR_RESPONSE";
  case EZSP_SPI_ERR_HANDSHAKE_TIMEOUT: return "EZSP_SPI_ERR_HANDSHAKE_TIMEOUT";
  case EZSP_SPI_ERR_STARTUP_TIMEOUT: return "EZSP_SPI_ERR_STARTUP_TIMEOUT";
  case EZSP_SPI_ERR_STARTUP_FAIL: return "EZSP_SPI_ERR_STARTUP_FAIL";
  case EZSP_SPI_ERR_UNSUPPORTED_SPI_COMMAND: return "EZSP_SPI_ERR_UNSUPPORTED_SPI_COMMAND";
  case EZSP_ASH_IN_PROGRESS: return "EZSP_ASH_IN_PROGRESS";
  case EZSP_ASH_HOST_FATAL_ERROR: return "EZSP_ASH_HOST_FATAL_ERROR";
  case EZSP_ASH_NCP_FATAL_ERROR: return "EZSP_ASH_NCP_FATAL_ERROR";
  case EZSP_ASH_DATA_FRAME_TOO_LONG: return "EZSP_ASH_DATA_FRAME_TOO_LONG";
  case EZSP_ASH_DATA_FRAME_TOO_SHORT: return "EZSP_ASH_DATA_FRAME_TOO_SHORT";
  case EZSP_ASH_NO_TX_SPACE: return "EZSP_ASH_NO_TX_SPACE";
  case EZSP_ASH_NO_RX_SPACE: return "EZSP_ASH_NO_RX_SPACE";
  case EZSP_ASH_NO_RX_DATA: return "EZSP_ASH_NO_RX_DATA";
  case EZSP_ASH_NOT_CONNECTED: return "EZSP_ASH_NOT_CONNECTED";
  case EZSP_ERROR_VERSION_NOT_SET: return "EZSP_ERROR_VERSION_NOT_SET";
  case EZSP_ERROR_INVALID_FRAME_ID: return "EZSP_ERROR_INVALID_FRAME_ID";
  case EZSP_ERROR_WRONG_DIRECTION: return "EZSP_ERROR_WRONG_DIRECTION";
  case EZSP_ERROR_TRUNCATED: return "EZSP_ERROR_TRUNCATED";
  case EZSP_ERROR_OVERFLOW: return "EZSP_ERROR_OVERFLOW";
  case EZSP_ERROR_OUT_OF_MEMORY: return "EZSP_ERROR_OUT_OF_MEMORY";
  case EZSP_ERROR_INVALID_VALUE: return "EZSP_ERROR_INVALID_VALUE";
  case EZSP_ERROR_INVALID_ID: return "EZSP_ERROR_INVALID_ID";
  case EZSP_ERROR_INVALID_CALL: return "EZSP_ERROR_INVALID_CALL";
  case EZSP_ERROR_NO_RESPONSE: return "EZSP_ERROR_NO_RESPONSE";
  case EZSP_ERROR_COMMAND_TOO_LONG: return "EZSP_ERROR_COMMAND_TOO_LONG";
  case EZSP_ERROR_QUEUE_FULL: return "EZSP_ERROR_QUEUE_FULL";
  case EZSP_ASH_ERROR_VERSION: return "EZSP_ASH_ERROR_VERSION";
  case EZSP_ASH_ERROR_TIMEOUTS: return "EZSP_ASH_ERROR_TIMEOUTS";
  case EZSP_ASH_ERROR_RESET_FAIL: return "EZSP_ASH_ERROR_RESET_FAIL";
  case EZSP_ASH_ERROR_NCP_RESET: return "EZSP_ASH_ERROR_NCP_RESET";
  case EZSP_ASH_ERROR_SERIAL_INIT: return "EZSP_ASH_ERROR_SERIAL_INIT";
  case EZSP_ASH_ERROR_NCP_TYPE: return "EZSP_ASH_ERROR_NCP_TYPE";
  case EZSP_ASH_ERROR_RESET_METHOD: return "EZSP_ASH_ERROR_RESET_METHOD";
  case EZSP_ASH_ERROR_XON_XOFF: return "EZSP_ASH_ERROR_XON_XOFF";
  case EZSP_ASH_STARTED: return "EZSP_ASH_STARTED";
  case EZSP_ASH_CONNECTED: return "EZSP_ASH_CONNECTED";
  case EZSP_ASH_DISCONNECTED: return "EZSP_ASH_DISCONNECTED";
  case EZSP_ASH_ACK_TIMEOUT: return "EZSP_ASH_ACK_TIMEOUT";
  case EZSP_ASH_CANCELLED: return "EZSP_ASH_CANCELLED";
  case EZSP_ASH_OUT_OF_SEQUENCE: return "EZSP_ASH_OUT_OF_SEQUENCE";
  case EZSP_ASH_BAD_CRC: return "EZSP_ASH_BAD_CRC";
  case EZSP_ASH_COMM_ERROR: return "EZSP_ASH_COMM_ERROR";
  case EZSP_ASH_BAD_ACKNUM: return "EZSP_ASH_BAD_ACKNUM";
  case EZSP_ASH_TOO_SHORT: return "EZSP_ASH_TOO_SHORT";
  case EZSP_ASH_TOO_LONG: return "EZSP_ASH_TOO_LONG";
  case EZSP_ASH_BAD_CONTROL: return "EZSP_ASH_BAD_CONTROL";
  case EZSP_ASH_BAD_LENGTH: return "EZSP_ASH_BAD_LENGTH";
  case EZSP_ASH_NO_ERROR: return "EZSP_ASH_NO_ERROR";
  }
  return "*** Not enumerated. ***";
}

const char *decodeEzspNetworkScanType(int8u value) {
  switch(value) {
  case EZSP_ENERGY_SCAN: return "EZSP_ENERGY_SCAN";
  case EZSP_ACTIVE_SCAN: return "EZSP_ACTIVE_SCAN";
  }
  return "*** Not enumerated. ***";
}

const char *decodeFrameId(int8u value) {
  switch(value) {

// Configuration Frames
  case EZSP_VERSION: return "EZSP_VERSION";
  case EZSP_GET_CONFIGURATION_VALUE: return "EZSP_GET_CONFIGURATION_VALUE";
  case EZSP_SET_CONFIGURATION_VALUE: return "EZSP_SET_CONFIGURATION_VALUE";
  case EZSP_ADD_ENDPOINT: return "EZSP_ADD_ENDPOINT";
  case EZSP_SET_POLICY: return "EZSP_SET_POLICY";
  case EZSP_GET_POLICY: return "EZSP_GET_POLICY";
  case EZSP_GET_VALUE: return "EZSP_GET_VALUE";
  case EZSP_SET_VALUE: return "EZSP_SET_VALUE";

// Utilities Frames
  case EZSP_NOP: return "EZSP_NOP";
  case EZSP_ECHO: return "EZSP_ECHO";
  case EZSP_INVALID_COMMAND: return "EZSP_INVALID_COMMAND";
  case EZSP_CALLBACK: return "EZSP_CALLBACK";
  case EZSP_NO_CALLBACKS: return "EZSP_NO_CALLBACKS";
  case EZSP_SET_TOKEN: return "EZSP_SET_TOKEN";
  case EZSP_GET_TOKEN: return "EZSP_GET_TOKEN";
  case EZSP_GET_MFG_TOKEN: return "EZSP_GET_MFG_TOKEN";
  case EZSP_GET_RANDOM_NUMBER: return "EZSP_GET_RANDOM_NUMBER";
  case EZSP_SET_TIMER: return "EZSP_SET_TIMER";
  case EZSP_GET_TIMER: return "EZSP_GET_TIMER";
  case EZSP_TIMER_HANDLER: return "EZSP_TIMER_HANDLER";
  case EZSP_DEBUG_WRITE: return "EZSP_DEBUG_WRITE";
  case EZSP_READ_AND_CLEAR_COUNTERS: return "EZSP_READ_AND_CLEAR_COUNTERS";
  case EZSP_DELAY_TEST: return "EZSP_DELAY_TEST";
  case EZSP_GET_LIBRARY_STATUS: return "EZSP_GET_LIBRARY_STATUS";

// Networking Frames
  case EZSP_SET_MANUFACTURER_CODE: return "EZSP_SET_MANUFACTURER_CODE";
  case EZSP_SET_POWER_DESCRIPTOR: return "EZSP_SET_POWER_DESCRIPTOR";
  case EZSP_NETWORK_INIT: return "EZSP_NETWORK_INIT";
  case EZSP_NETWORK_STATE: return "EZSP_NETWORK_STATE";
  case EZSP_STACK_STATUS_HANDLER: return "EZSP_STACK_STATUS_HANDLER";
  case EZSP_START_SCAN: return "EZSP_START_SCAN";
  case EZSP_ENERGY_SCAN_RESULT_HANDLER: return "EZSP_ENERGY_SCAN_RESULT_HANDLER";
  case EZSP_NETWORK_FOUND_HANDLER: return "EZSP_NETWORK_FOUND_HANDLER";
  case EZSP_SCAN_COMPLETE_HANDLER: return "EZSP_SCAN_COMPLETE_HANDLER";
  case EZSP_STOP_SCAN: return "EZSP_STOP_SCAN";
  case EZSP_FORM_NETWORK: return "EZSP_FORM_NETWORK";
  case EZSP_JOIN_NETWORK: return "EZSP_JOIN_NETWORK";
  case EZSP_LEAVE_NETWORK: return "EZSP_LEAVE_NETWORK";
  case EZSP_FIND_AND_REJOIN_NETWORK: return "EZSP_FIND_AND_REJOIN_NETWORK";
  case EZSP_PERMIT_JOINING: return "EZSP_PERMIT_JOINING";
  case EZSP_CHILD_JOIN_HANDLER: return "EZSP_CHILD_JOIN_HANDLER";
  case EZSP_ENERGY_SCAN_REQUEST: return "EZSP_ENERGY_SCAN_REQUEST";
  case EZSP_GET_EUI64: return "EZSP_GET_EUI64";
  case EZSP_GET_NODE_ID: return "EZSP_GET_NODE_ID";
  case EZSP_GET_NETWORK_PARAMETERS: return "EZSP_GET_NETWORK_PARAMETERS";
  case EZSP_GET_PARENT_CHILD_PARAMETERS: return "EZSP_GET_PARENT_CHILD_PARAMETERS";
  case EZSP_GET_CHILD_DATA: return "EZSP_GET_CHILD_DATA";
  case EZSP_GET_NEIGHBOR: return "EZSP_GET_NEIGHBOR";
  case EZSP_NEIGHBOR_COUNT: return "EZSP_NEIGHBOR_COUNT";
  case EZSP_GET_ROUTE_TABLE_ENTRY: return "EZSP_GET_ROUTE_TABLE_ENTRY";
  case EZSP_SET_RADIO_POWER: return "EZSP_SET_RADIO_POWER";
  case EZSP_SET_RADIO_CHANNEL: return "EZSP_SET_RADIO_CHANNEL";

// Binding Frames
  case EZSP_CLEAR_BINDING_TABLE: return "EZSP_CLEAR_BINDING_TABLE";
  case EZSP_SET_BINDING: return "EZSP_SET_BINDING";
  case EZSP_GET_BINDING: return "EZSP_GET_BINDING";
  case EZSP_DELETE_BINDING: return "EZSP_DELETE_BINDING";
  case EZSP_BINDING_IS_ACTIVE: return "EZSP_BINDING_IS_ACTIVE";
  case EZSP_GET_BINDING_REMOTE_NODE_ID: return "EZSP_GET_BINDING_REMOTE_NODE_ID";
  case EZSP_SET_BINDING_REMOTE_NODE_ID: return "EZSP_SET_BINDING_REMOTE_NODE_ID";
  case EZSP_REMOTE_SET_BINDING_HANDLER: return "EZSP_REMOTE_SET_BINDING_HANDLER";
  case EZSP_REMOTE_DELETE_BINDING_HANDLER: return "EZSP_REMOTE_DELETE_BINDING_HANDLER";

// Messaging Frames
  case EZSP_MAXIMUM_PAYLOAD_LENGTH: return "EZSP_MAXIMUM_PAYLOAD_LENGTH";
  case EZSP_SEND_UNICAST: return "EZSP_SEND_UNICAST";
  case EZSP_SEND_BROADCAST: return "EZSP_SEND_BROADCAST";
  case EZSP_SEND_MULTICAST: return "EZSP_SEND_MULTICAST";
  case EZSP_SEND_REPLY: return "EZSP_SEND_REPLY";
  case EZSP_MESSAGE_SENT_HANDLER: return "EZSP_MESSAGE_SENT_HANDLER";
  case EZSP_SEND_MANY_TO_ONE_ROUTE_REQUEST: return "EZSP_SEND_MANY_TO_ONE_ROUTE_REQUEST";
  case EZSP_POLL_FOR_DATA: return "EZSP_POLL_FOR_DATA";
  case EZSP_POLL_COMPLETE_HANDLER: return "EZSP_POLL_COMPLETE_HANDLER";
  case EZSP_POLL_HANDLER: return "EZSP_POLL_HANDLER";
  case EZSP_INCOMING_SENDER_EUI64_HANDLER: return "EZSP_INCOMING_SENDER_EUI64_HANDLER";
  case EZSP_INCOMING_MESSAGE_HANDLER: return "EZSP_INCOMING_MESSAGE_HANDLER";
  case EZSP_INCOMING_ROUTE_RECORD_HANDLER: return "EZSP_INCOMING_ROUTE_RECORD_HANDLER";
  case EZSP_SET_SOURCE_ROUTE: return "EZSP_SET_SOURCE_ROUTE";
  case EZSP_INCOMING_MANY_TO_ONE_ROUTE_REQUEST_HANDLER: return "EZSP_INCOMING_MANY_TO_ONE_ROUTE_REQUEST_HANDLER";
  case EZSP_INCOMING_ROUTE_ERROR_HANDLER: return "EZSP_INCOMING_ROUTE_ERROR_HANDLER";
  case EZSP_ADDRESS_TABLE_ENTRY_IS_ACTIVE: return "EZSP_ADDRESS_TABLE_ENTRY_IS_ACTIVE";
  case EZSP_SET_ADDRESS_TABLE_REMOTE_EUI64: return "EZSP_SET_ADDRESS_TABLE_REMOTE_EUI64";
  case EZSP_SET_ADDRESS_TABLE_REMOTE_NODE_ID: return "EZSP_SET_ADDRESS_TABLE_REMOTE_NODE_ID";
  case EZSP_GET_ADDRESS_TABLE_REMOTE_EUI64: return "EZSP_GET_ADDRESS_TABLE_REMOTE_EUI64";
  case EZSP_GET_ADDRESS_TABLE_REMOTE_NODE_ID: return "EZSP_GET_ADDRESS_TABLE_REMOTE_NODE_ID";
  case EZSP_SET_EXTENDED_TIMEOUT: return "EZSP_SET_EXTENDED_TIMEOUT";
  case EZSP_GET_EXTENDED_TIMEOUT: return "EZSP_GET_EXTENDED_TIMEOUT";
  case EZSP_REPLACE_ADDRESS_TABLE_ENTRY: return "EZSP_REPLACE_ADDRESS_TABLE_ENTRY";
  case EZSP_LOOKUP_NODE_ID_BY_EUI64: return "EZSP_LOOKUP_NODE_ID_BY_EUI64";
  case EZSP_LOOKUP_EUI64_BY_NODE_ID: return "EZSP_LOOKUP_EUI64_BY_NODE_ID";
  case EZSP_GET_MULTICAST_TABLE_ENTRY: return "EZSP_GET_MULTICAST_TABLE_ENTRY";
  case EZSP_SET_MULTICAST_TABLE_ENTRY: return "EZSP_SET_MULTICAST_TABLE_ENTRY";
  case EZSP_ID_CONFLICT_HANDLER: return "EZSP_ID_CONFLICT_HANDLER";
  case EZSP_SEND_RAW_MESSAGE: return "EZSP_SEND_RAW_MESSAGE";
  case EZSP_MAC_PASSTHROUGH_MESSAGE_HANDLER: return "EZSP_MAC_PASSTHROUGH_MESSAGE_HANDLER";
  case EZSP_RAW_TRANSMIT_COMPLETE_HANDLER: return "EZSP_RAW_TRANSMIT_COMPLETE_HANDLER";

// Security Frames
  case EZSP_SET_INITIAL_SECURITY_STATE: return "EZSP_SET_INITIAL_SECURITY_STATE";
  case EZSP_GET_CURRENT_SECURITY_STATE: return "EZSP_GET_CURRENT_SECURITY_STATE";
  case EZSP_GET_KEY: return "EZSP_GET_KEY";
  case EZSP_SWITCH_NETWORK_KEY_HANDLER: return "EZSP_SWITCH_NETWORK_KEY_HANDLER";
  case EZSP_GET_KEY_TABLE_ENTRY: return "EZSP_GET_KEY_TABLE_ENTRY";
  case EZSP_SET_KEY_TABLE_ENTRY: return "EZSP_SET_KEY_TABLE_ENTRY";
  case EZSP_FIND_KEY_TABLE_ENTRY: return "EZSP_FIND_KEY_TABLE_ENTRY";
  case EZSP_ADD_OR_UPDATE_KEY_TABLE_ENTRY: return "EZSP_ADD_OR_UPDATE_KEY_TABLE_ENTRY";
  case EZSP_ERASE_KEY_TABLE_ENTRY: return "EZSP_ERASE_KEY_TABLE_ENTRY";
  case EZSP_REQUEST_LINK_KEY: return "EZSP_REQUEST_LINK_KEY";
  case EZSP_ZIGBEE_KEY_ESTABLISHMENT_HANDLER: return "EZSP_ZIGBEE_KEY_ESTABLISHMENT_HANDLER";

// Trust Center Frames
  case EZSP_TRUST_CENTER_JOIN_HANDLER: return "EZSP_TRUST_CENTER_JOIN_HANDLER";
  case EZSP_BROADCAST_NEXT_NETWORK_KEY: return "EZSP_BROADCAST_NEXT_NETWORK_KEY";
  case EZSP_BROADCAST_NETWORK_KEY_SWITCH: return "EZSP_BROADCAST_NETWORK_KEY_SWITCH";
  case EZSP_BECOME_TRUST_CENTER: return "EZSP_BECOME_TRUST_CENTER";
  case EZSP_AES_MMO_HASH: return "EZSP_AES_MMO_HASH";
  case EZSP_REMOVE_DEVICE: return "EZSP_REMOVE_DEVICE";
  case EZSP_UNICAST_NWK_KEY_UPDATE: return "EZSP_UNICAST_NWK_KEY_UPDATE";

// Certificate Based Key Exchange (CBKE)
  case EZSP_GENERATE_CBKE_KEYS: return "EZSP_GENERATE_CBKE_KEYS";
  case EZSP_GENERATE_CBKE_KEYS_HANDLER: return "EZSP_GENERATE_CBKE_KEYS_HANDLER";
  case EZSP_CALCULATE_SMACS: return "EZSP_CALCULATE_SMACS";
  case EZSP_CALCULATE_SMACS_HANDLER: return "EZSP_CALCULATE_SMACS_HANDLER";
  case EZSP_CLEAR_TEMPORARY_DATA_MAYBE_STORE_LINK_KEY: return "EZSP_CLEAR_TEMPORARY_DATA_MAYBE_STORE_LINK_KEY";
  case EZSP_GET_CERTIFICATE: return "EZSP_GET_CERTIFICATE";
  case EZSP_DSA_SIGN: return "EZSP_DSA_SIGN";
  case EZSP_DSA_SIGN_HANDLER: return "EZSP_DSA_SIGN_HANDLER";
  case EZSP_DSA_VERIFY: return "EZSP_DSA_VERIFY";
  case EZSP_DSA_VERIFY_HANDLER: return "EZSP_DSA_VERIFY_HANDLER";
  case EZSP_SET_PREINSTALLED_CBKE_DATA: return "EZSP_SET_PREINSTALLED_CBKE_DATA";

// Mfglib
  case EZSP_MFGLIB_START: return "EZSP_MFGLIB_START";
  case EZSP_MFGLIB_END: return "EZSP_MFGLIB_END";
  case EZSP_MFGLIB_START_TONE: return "EZSP_MFGLIB_START_TONE";
  case EZSP_MFGLIB_STOP_TONE: return "EZSP_MFGLIB_STOP_TONE";
  case EZSP_MFGLIB_START_STREAM: return "EZSP_MFGLIB_START_STREAM";
  case EZSP_MFGLIB_STOP_STREAM: return "EZSP_MFGLIB_STOP_STREAM";
  case EZSP_MFGLIB_SEND_PACKET: return "EZSP_MFGLIB_SEND_PACKET";
  case EZSP_MFGLIB_SET_CHANNEL: return "EZSP_MFGLIB_SET_CHANNEL";
  case EZSP_MFGLIB_GET_CHANNEL: return "EZSP_MFGLIB_GET_CHANNEL";
  case EZSP_MFGLIB_SET_POWER: return "EZSP_MFGLIB_SET_POWER";
  case EZSP_MFGLIB_GET_POWER: return "EZSP_MFGLIB_GET_POWER";
  case EZSP_MFGLIB_RX_HANDLER: return "EZSP_MFGLIB_RX_HANDLER";

// Bootloader
  case EZSP_LAUNCH_STANDALONE_BOOTLOADER: return "EZSP_LAUNCH_STANDALONE_BOOTLOADER";
  case EZSP_SEND_BOOTLOAD_MESSAGE: return "EZSP_SEND_BOOTLOAD_MESSAGE";
  case EZSP_GET_STANDALONE_BOOTLOADER_VERSION_PLAT_MICRO_PHY: return "EZSP_GET_STANDALONE_BOOTLOADER_VERSION_PLAT_MICRO_PHY";
  case EZSP_INCOMING_BOOTLOAD_MESSAGE_HANDLER: return "EZSP_INCOMING_BOOTLOAD_MESSAGE_HANDLER";
  case EZSP_BOOTLOAD_TRANSMIT_COMPLETE_HANDLER: return "EZSP_BOOTLOAD_TRANSMIT_COMPLETE_HANDLER";
  case EZSP_AES_ENCRYPT: return "EZSP_AES_ENCRYPT";
  case EZSP_OVERRIDE_CURRENT_CHANNEL: return "EZSP_OVERRIDE_CURRENT_CHANNEL";
  }
  return "*** Not enumerated. ***";
}

