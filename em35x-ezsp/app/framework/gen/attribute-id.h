// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generateAttributeIDs()
//

// Enclosing macro to prevent multiple inclusion
#ifndef __EMBER_AF_ATTRIBUTE_ID__
#define __EMBER_AF_ATTRIBUTE_ID__


// Attribute types for cluster: Basic
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_VERSION_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_APPLICATION_VERSION_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_STACK_VERSION_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_HW_VERSION_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_MANUFACTURER_NAME_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_MODEL_IDENTIFIER_ATTRIBUTE_ID 0x0005    // Ver.: always
#define ZCL_DATE_CODE_ATTRIBUTE_ID 0x0006    // Ver.: always
#define ZCL_POWER_SOURCE_ATTRIBUTE_ID 0x0007    // Ver.: always
#define ZCL_LOCATION_DESCRIPTION_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_PHYSICAL_ENVIRONMENT_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_DEVICE_ENABLED_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_ALARM_MASK_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_DISABLE_LOCAL_CONFIG_ATTRIBUTE_ID 0x0014    // Ver.: always


// Attribute types for cluster: Power Configuration
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_MAINS_VOLTAGE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_MAINS_FREQUENCY_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_MAINS_ALARM_MASK_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_MAINS_VOLTAGE_MIN_THRESHOLD_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_MAINS_VOLTAGE_MAX_THRESHOLD_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_MAINS_VOLTAGE_DWELL_TRIP_POINT_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_BATTERY_VOLTAGE_ATTRIBUTE_ID 0x0020    // Ver.: always
#define ZCL_BATTERY_MANUFACTURER_ATTRIBUTE_ID 0x0030    // Ver.: always
#define ZCL_BATTERY_SIZE_ATTRIBUTE_ID 0x0031    // Ver.: always
#define ZCL_BATTERY_AHR_RATING_ATTRIBUTE_ID 0x0032    // Ver.: always
#define ZCL_BATTERY_QUANTITY_ATTRIBUTE_ID 0x0033    // Ver.: always
#define ZCL_BATTERY_RATED_VOLTAGE_ATTRIBUTE_ID 0x0034    // Ver.: always
#define ZCL_BATTERY_ALARM_MASK_ATTRIBUTE_ID 0x0035    // Ver.: always
#define ZCL_BATTERY_VOLTAGE_MIN_THRESHOLD_ATTRIBUTE_ID 0x0036    // Ver.: always


// Attribute types for cluster: Device Temperature Configuration
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_CURRENT_TEMPERATURE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_MIN_TEMP_EXPERIENCED_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_MAX_TEMP_EXPERIENCED_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_OVER_TEMP_TOTAL_DWELL_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_DEVICE_TEMP_ALARM_MASK_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_LOW_TEMP_THRESHOLD_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_HIGH_TEMP_THRESHOLD_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_LOW_TEMP_DWELL_TRIP_POINT_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_HIGH_TEMP_DWELL_TRIP_POINT_ATTRIBUTE_ID 0x0014    // Ver.: always


// Attribute types for cluster: Identify
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_IDENTIFY_TIME_ATTRIBUTE_ID 0x0000    // Ver.: always


// Attribute types for cluster: Groups
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_GROUP_NAME_SUPPORT_ATTRIBUTE_ID 0x0000    // Ver.: always


// Attribute types for cluster: Scenes
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_SCENE_COUNT_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_CURRENT_SCENE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_CURRENT_GROUP_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_SCENE_VALID_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_SCENE_NAME_SUPPORT_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_LAST_CONFIGURED_BY_ATTRIBUTE_ID 0x0005    // Ver.: always


// Attribute types for cluster: On/off
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_ON_OFF_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_SAMPLE_MFG_SPECIFIC_TRANSITION_TIME_ATTRIBUTE_ID 0x0000    // Ver.: always


// Attribute types for cluster: On/off Switch Configuration
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_SWITCH_TYPE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_SWITCH_ACTIONS_ATTRIBUTE_ID 0x0010    // Ver.: always


// Attribute types for cluster: Level Control
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_CURRENT_LEVEL_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_LEVEL_CONTROL_REMAINING_TIME_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_ON_OFF_TRANSITION_TIME_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_ON_LEVEL_ATTRIBUTE_ID 0x0011    // Ver.: always


// Attribute types for cluster: Alarms
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_ALARM_COUNT_ATTRIBUTE_ID 0x0000    // Ver.: always


// Attribute types for cluster: Time
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_TIME_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_TIME_STATUS_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_TIME_ZONE_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_DST_START_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_DST_END_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_DST_SHIFT_ATTRIBUTE_ID 0x0005    // Ver.: always
#define ZCL_STANDARD_TIME_ATTRIBUTE_ID 0x0006    // Ver.: always
#define ZCL_LOCAL_TIME_ATTRIBUTE_ID 0x0007    // Ver.: always
#define ZCL_LAST_SET_TIME_ATTRIBUTE_ID 0x0008    // Ver.: always
#define ZCL_VALID_UNTIL_TIME_ATTRIBUTE_ID 0x0009    // Ver.: always


// Attribute types for cluster: RSSI Location
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_LOCATION_TYPE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_LOCATION_METHOD_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_LOCATION_AGE_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_QUALITY_MEASURE_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_NUMBER_OF_DEVICES_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_COORDINATE1_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_COORDINATE2_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_COORDINATE3_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_POWER_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_PATH_LOSS_EXPONENT_ATTRIBUTE_ID 0x0014    // Ver.: always
#define ZCL_REPORTING_PERIOD_ATTRIBUTE_ID 0x0015    // Ver.: always
#define ZCL_CALCULATION_PERIOD_ATTRIBUTE_ID 0x0016    // Ver.: always
#define ZCL_NUMBER_RSSI_MEASUREMENTS_ATTRIBUTE_ID 0x0017    // Ver.: always


// Attribute types for cluster: Binary Input (Basic)
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_ACTIVE_TEXT_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_DESCRIPTION_ATTRIBUTE_ID 0x001C    // Ver.: always
#define ZCL_INACTIVE_TEXT_ATTRIBUTE_ID 0x002E    // Ver.: always
#define ZCL_OUT_OF_SERVICE_ATTRIBUTE_ID 0x0051    // Ver.: always
#define ZCL_POLARITY_ATTRIBUTE_ID 0x0054    // Ver.: always
#define ZCL_PRESENT_VALUE_ATTRIBUTE_ID 0x0055    // Ver.: always
#define ZCL_RELIABILITY_ATTRIBUTE_ID 0x0067    // Ver.: always
#define ZCL_STATUS_FLAGS_ATTRIBUTE_ID 0x006F    // Ver.: always
#define ZCL_APPLICATION_TYPE_ATTRIBUTE_ID 0x0100    // Ver.: always


// Attribute types for cluster: Commissioning
// Cluster specification level: 075123r03

// Server attributes
#define ZCL_SHORT_ADDRESS_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_EXTENDED_PAN_ID_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_PAN_ID_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_CHANNEL_MASK_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_PROTOCOL_VERSION_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_STACK_PROFILE_ATTRIBUTE_ID 0x0005    // Ver.: always
#define ZCL_STARTUP_CONTROL_ATTRIBUTE_ID 0x0006    // Ver.: always
#define ZCL_TRUST_CENTER_ADDRESS_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_TRUST_CENTER_MASTER_KEY_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_NETWORK_KEY_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_USE_INSECURE_JOIN_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_PRECONFIGURED_LINK_KEY_ATTRIBUTE_ID 0x0014    // Ver.: always
#define ZCL_NETWORK_KEY_SEQUENCE_NUMBER_ATTRIBUTE_ID 0x0015    // Ver.: always
#define ZCL_NETWORK_KEY_TYPE_ATTRIBUTE_ID 0x0016    // Ver.: always
#define ZCL_NETWORK_MANAGER_ADDRESS_ATTRIBUTE_ID 0x0017    // Ver.: always
#define ZCL_SCAN_ATTEMPTS_ATTRIBUTE_ID 0x0020    // Ver.: always
#define ZCL_TIME_BETWEEN_SCANS_ATTRIBUTE_ID 0x0021    // Ver.: always
#define ZCL_REJOIN_INTERVAL_ATTRIBUTE_ID 0x0022    // Ver.: always
#define ZCL_MAX_REJOIN_INTERVAL_ATTRIBUTE_ID 0x0023    // Ver.: always
#define ZCL_INDERECT_POLL_RATE_ATTRIBUTE_ID 0x0030    // Ver.: always
#define ZCL_PARENT_RETRY_THRESHOLD_ATTRIBUTE_ID 0x0031    // Ver.: always
#define ZCL_CONCENTRATOR_FLAG_ATTRIBUTE_ID 0x0040    // Ver.: always
#define ZCL_CONCENTRATOR_RADIUS_ATTRIBUTE_ID 0x0041    // Ver.: always
#define ZCL_CONCENTRATOR_DISCOVERY_TIME_ATTRIBUTE_ID 0x0042    // Ver.: always


// Attribute types for cluster: Shade Configuration
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_SHADE_CONFIG_PHYSICAL_CLOSED_LIMIT_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_SHADE_CONFIG_MOTOR_STEP_SIZE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_SHADE_CONFIG_STATUS_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_SHADE_CONFIG_CLOSED_LIMIT_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_SHADE_CONFIG_MODE_ATTRIBUTE_ID 0x0011    // Ver.: always


// Attribute types for cluster: Pump Configuration and Control
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_MAX_PRESSURE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_MAX_SPEED_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_MAX_FLOW_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_MIN_CONST_PRESSURE_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_MAX_CONST_PRESSURE_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_MIN_COMP_PRESSURE_ATTRIBUTE_ID 0x0005    // Ver.: always
#define ZCL_MAX_COMP_PRESSURE_ATTRIBUTE_ID 0x0006    // Ver.: always
#define ZCL_MIN_CONST_SPEED_ATTRIBUTE_ID 0x0007    // Ver.: always
#define ZCL_MAX_CONST_SPEED_ATTRIBUTE_ID 0x0008    // Ver.: always
#define ZCL_MIN_CONST_FLOW_ATTRIBUTE_ID 0x0009    // Ver.: always
#define ZCL_MAX_CONST_FLOW_ATTRIBUTE_ID 0x000A    // Ver.: always
#define ZCL_MIN_CONST_TEMP_ATTRIBUTE_ID 0x000B    // Ver.: always
#define ZCL_MAX_CONST_TEMP_ATTRIBUTE_ID 0x000C    // Ver.: always
#define ZCL_PUMP_STATUS_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_EFFECTIVE_OPERATION_MODE_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_EFFECTIVE_CONTROL_MODE_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_CAPACITY_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_SPEED_ATTRIBUTE_ID 0x0014    // Ver.: always
#define ZCL_LIFETIME_RUNNING_HOURS_ATTRIBUTE_ID 0x0015    // Ver.: always
#define ZCL_PUMP_POWER_ATTRIBUTE_ID 0x0016    // Ver.: always
#define ZCL_LIFETIME_ENERGY_CONSUMED_ATTRIBUTE_ID 0x0017    // Ver.: always
#define ZCL_OPERATION_MODE_ATTRIBUTE_ID 0x0020    // Ver.: always
#define ZCL_CONTROL_MODE_ATTRIBUTE_ID 0x0021    // Ver.: always
#define ZCL_PUMP_ALARM_MASK_ATTRIBUTE_ID 0x0022    // Ver.: always


// Attribute types for cluster: Thermostat
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_LOCAL_TEMPERATURE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_OUTDOOR_TEMPERATURE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_THERMOSTAT_OCCUPANCY_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_ABS_MIN_HEAT_SETPOINT_LIMIT_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_ABS_MAX_HEAT_SETPOINT_LIMIT_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_ABS_MIN_COOL_SETPOINT_LIMIT_ATTRIBUTE_ID 0x0005    // Ver.: always
#define ZCL_ABS_MAX_COOL_SETPOINT_LIMIT_ATTRIBUTE_ID 0x0006    // Ver.: always
#define ZCL_PI_COOLING_DEMAND_ATTRIBUTE_ID 0x0007    // Ver.: always
#define ZCL_PI_HEATING_DEMAND_ATTRIBUTE_ID 0x0008    // Ver.: always
#define ZCL_LOCAL_TEMPERATURE_CALIBRATION_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_OCCUPIED_COOLING_SETPOINT_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_OCCUPIED_HEATING_SETPOINT_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_UNOCCUPIED_COOLING_SETPOINT_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_UNOCCUPIED_HEATING_SETPOINT_ATTRIBUTE_ID 0x0014    // Ver.: always
#define ZCL_MIN_HEAT_SETPOINT_LIMIT_ATTRIBUTE_ID 0x0015    // Ver.: always
#define ZCL_MAX_HEAT_SETPOINT_LIMIT_ATTRIBUTE_ID 0x0016    // Ver.: always
#define ZCL_MIN_COOL_SETPOINT_LIMIT_ATTRIBUTE_ID 0x0017    // Ver.: always
#define ZCL_MAX_COOL_SETPOINT_LIMIT_ATTRIBUTE_ID 0x0018    // Ver.: always
#define ZCL_MIN_SETPOINT_DEAD_BAND_ATTRIBUTE_ID 0x0019    // Ver.: always
#define ZCL_REMOTE_SENSING_ATTRIBUTE_ID 0x001A    // Ver.: always
#define ZCL_CONTROL_SEQUENCE_OF_OPERATION_ATTRIBUTE_ID 0x001B    // Ver.: always
#define ZCL_SYSTEM_MODE_ATTRIBUTE_ID 0x001C    // Ver.: always
#define ZCL_THERMOSTAT_ALARM_MASK_ATTRIBUTE_ID 0x001D    // Ver.: always


// Attribute types for cluster: Fan Control
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_FAN_CONTROL_FAN_MODE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_FAN_CONTROL_FAN_MODE_SEQUENCE_ATTRIBUTE_ID 0x0001    // Ver.: always


// Attribute types for cluster: Dehumidification Control
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_RELATIVE_HUMIDITY_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_DEHUMIDIFICATION_COOLING_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_RH_DEHUMIDIFICATION_SETPOINT_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_RELATIVE_HUMIDITY_MODE_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_DEHUMIDIFICATION_LOCKOUT_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_DEHUMIDIFICATION_HYSTERESIS_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_DEHUMIDIFICATION_MAX_COOL_ATTRIBUTE_ID 0x0014    // Ver.: always
#define ZCL_RELATIVE_HUMIDITY_DISPLAY_ATTRIBUTE_ID 0x0015    // Ver.: always


// Attribute types for cluster: Thermostat User Interface Configuration
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_TEMPERATURE_DISPLAY_MODE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_KEYPAD_LOCKOUT_ATTRIBUTE_ID 0x0001    // Ver.: always


// Attribute types for cluster: Color Control
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_COLOR_CONTROL_CURRENT_HUE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_COLOR_CONTROL_CURRENT_SATURATION_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_COLOR_CONTROL_REMAINING_TIME_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_COLOR_CONTROL_CURRENT_X_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_COLOR_CONTROL_CURRENT_Y_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_COLOR_CONTROL_DRIFT_COMPENSATION_ATTRIBUTE_ID 0x0005    // Ver.: always
#define ZCL_COLOR_CONTROL_COMPENSATION_TEXT_ATTRIBUTE_ID 0x0006    // Ver.: always
#define ZCL_COLOR_CONTROL_COLOR_TEMPERATURE_ATTRIBUTE_ID 0x0007    // Ver.: always
#define ZCL_COLOR_CONTROL_COLOR_MODE_ATTRIBUTE_ID 0x0008    // Ver.: always
#define ZCL_COLOR_CONTROL_NUMBER_OF_PRIMARIES_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_1_X_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_1_Y_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_1_INTENSITY_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_2_X_ATTRIBUTE_ID 0x0015    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_2_Y_ATTRIBUTE_ID 0x0016    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_2_INTENSITY_ATTRIBUTE_ID 0x0017    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_3_X_ATTRIBUTE_ID 0x0019    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_3_Y_ATTRIBUTE_ID 0x001A    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_3_INTENSITY_ATTRIBUTE_ID 0x001B    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_4_X_ATTRIBUTE_ID 0x0020    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_4_Y_ATTRIBUTE_ID 0x0021    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_4_INTENSITY_ATTRIBUTE_ID 0x0022    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_5_X_ATTRIBUTE_ID 0x0024    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_5_Y_ATTRIBUTE_ID 0x0025    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_5_INTENSITY_ATTRIBUTE_ID 0x0026    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_6_X_ATTRIBUTE_ID 0x0028    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_6_Y_ATTRIBUTE_ID 0x0029    // Ver.: always
#define ZCL_COLOR_CONTROL_PRIMARY_6_INTENSITY_ATTRIBUTE_ID 0x002A    // Ver.: always
#define ZCL_COLOR_CONTROL_WHITE_POINT_X_ATTRIBUTE_ID 0x0030    // Ver.: always
#define ZCL_COLOR_CONTROL_WHITE_POINT_Y_ATTRIBUTE_ID 0x0031    // Ver.: always
#define ZCL_COLOR_CONTROL_COLOR_POINT_R_X_ATTRIBUTE_ID 0x0032    // Ver.: always
#define ZCL_COLOR_CONTROL_COLOR_POINT_R_Y_ATTRIBUTE_ID 0x0033    // Ver.: always
#define ZCL_COLOR_CONTROL_COLOR_POINT_R_INTENSITY_ATTRIBUTE_ID 0x0034    // Ver.: always
#define ZCL_COLOR_CONTROL_COLOR_POINT_G_X_ATTRIBUTE_ID 0x0036    // Ver.: always
#define ZCL_COLOR_CONTROL_COLOR_POINT_G_Y_ATTRIBUTE_ID 0x0037    // Ver.: always
#define ZCL_COLOR_CONTROL_COLOR_POINT_G_INTENSITY_ATTRIBUTE_ID 0x0038    // Ver.: always
#define ZCL_COLOR_CONTROL_COLOR_POINT_B_X_ATTRIBUTE_ID 0x003A    // Ver.: always
#define ZCL_COLOR_CONTROL_COLOR_POINT_B_Y_ATTRIBUTE_ID 0x003B    // Ver.: always
#define ZCL_COLOR_CONTROL_COLOR_POINT_B_INTENSITY_ATTRIBUTE_ID 0x003C    // Ver.: always


// Attribute types for cluster: Ballast Configuration
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_PHYSICAL_MIN_LEVEL_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_PHYSICAL_MAX_LEVEL_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_BALLAST_STATUS_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_MIN_LEVEL_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_MAX_LEVEL_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_POWER_ON_LEVEL_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_POWER_ON_FADE_TIME_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_INTRINSIC_BALLAST_FACTOR_ATTRIBUTE_ID 0x0014    // Ver.: always
#define ZCL_BALLAST_FACTOR_ADJUSTMENT_ATTRIBUTE_ID 0x0015    // Ver.: always
#define ZCL_LAMP_QUALITY_ATTRIBUTE_ID 0x0020    // Ver.: always
#define ZCL_LAMP_TYPE_ATTRIBUTE_ID 0x0030    // Ver.: always
#define ZCL_LAMP_MANUFACTURER_ATTRIBUTE_ID 0x0031    // Ver.: always
#define ZCL_LAMP_RATED_HOURS_ATTRIBUTE_ID 0x0032    // Ver.: always
#define ZCL_LAMP_BURN_HOURS_ATTRIBUTE_ID 0x0033    // Ver.: always
#define ZCL_LAMP_ALARM_MODE_ATTRIBUTE_ID 0x0034    // Ver.: always
#define ZCL_LAMP_BURN_HOURS_TRIP_POINT_ATTRIBUTE_ID 0x0035    // Ver.: always


// Attribute types for cluster: Illuminance Measurement
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_ILLUM_MEASURED_VALUE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_ILLUM_MIN_MEASURED_VALUE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_ILLUM_MAX_MEASURED_VALUE_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_ILLUM_TOLERANCE_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_MEASUREMENT_LIGHT_SENSOR_TYPE_ATTRIBUTE_ID 0x0004    // Ver.: always


// Attribute types for cluster: Illuminance Level Sensing
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_LEVEL_STATUS_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_SENSING_LIGHT_SENSOR_TYPE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_ILLUMINANCE_TARGET_LEVEL_ATTRIBUTE_ID 0x0010    // Ver.: always


// Attribute types for cluster: Temperature Measurement
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_TEMP_MEASURED_VALUE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_TEMP_MIN_MEASURED_VALUE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_TEMP_MAX_MEASURED_VALUE_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_TEMP_TOLERANCE_ATTRIBUTE_ID 0x0003    // Ver.: always


// Attribute types for cluster: Pressure Measurement
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_PRESSURE_MEASURED_VALUE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_PRESSURE_MIN_MEASURED_VALUE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_PRESSURE_MAX_MEASURED_VALUE_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_PRESSURE_TOLERANCE_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_PRESSURE_SCALED_VALUE_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_PRESSURE_MIN_SCALED_VALUE_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_PRESSURE_MAX_SCALED_VALUE_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_PRESSURE_SCALED_TOLERANCE_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_PRESSURE_SCALE_ATTRIBUTE_ID 0x0014    // Ver.: always


// Attribute types for cluster: Flow Measurement
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_FLOW_MEASURED_VALUE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_FLOW_MIN_MEASURED_VALUE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_FLOW_MAX_MEASURED_VALUE_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_FLOW_TOLERANCE_ATTRIBUTE_ID 0x0003    // Ver.: always


// Attribute types for cluster: Relative Humidity Measurement
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_RELATIVE_HUMIDITY_MEASURED_VALUE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_RELATIVE_HUMIDITY_MIN_MEASURED_VALUE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_RELATIVE_HUMIDITY_MAX_MEASURED_VALUE_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_RELATIVE_HUMIDITY_TOLERANCE_ATTRIBUTE_ID 0x0003    // Ver.: always


// Attribute types for cluster: Occupancy Sensing
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_OCCUPANCY_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_OCCUPANCY_SENSOR_TYPE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_PIR_OCCUPIED_TO_UNOCCUPIED_DELAY_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_PIR_UNOCCUPIED_TO_OCCUPIED_DELAY_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_PIR_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_ULTRASONIC_OCCUPIED_TO_UNOCCUPIED_DELAY_ATTRIBUTE_ID 0x0020    // Ver.: always
#define ZCL_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_DELAY_ATTRIBUTE_ID 0x0021    // Ver.: always
#define ZCL_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_ATTRIBUTE_ID 0x0022    // Ver.: always


// Attribute types for cluster: IAS Zone
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_ZONE_STATE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_ZONE_TYPE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_ZONE_STATUS_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_IAS_CIE_ADDRESS_ATTRIBUTE_ID 0x0010    // Ver.: always


// Attribute types for cluster: IAS WD
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_MAX_DURATION_ATTRIBUTE_ID 0x0000    // Ver.: always


// Attribute types for cluster: Door Lock
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_LOCK_STATE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_LOCK_TYPE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_ACTUATOR_ENABLED_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_DOOR_STATE_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_DOOR_OPEN_EVENTS_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_DOOR_CLOSED_EVENTS_ATTRIBUTE_ID 0x0005    // Ver.: always
#define ZCL_OPEN_PERIOD_ATTRIBUTE_ID 0x0006    // Ver.: always


// Attribute types for cluster: Window Covering
// Cluster specification level: 1.1, 053520r27

// Server attributes
#define ZCL_COVERING_TYPE_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_LIMIT_LIFT_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_LIMIT_TILT_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_CURRENT_LIFT_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_CURRENT_TILT_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_NUMBER_LIFT_ATTRIBUTE_ID 0x0005    // Ver.: always
#define ZCL_NUMBER_TILT_ATTRIBUTE_ID 0x0006    // Ver.: always
#define ZCL_CONFIG_STATUS_ATTRIBUTE_ID 0x0007    // Ver.: always
#define ZCL_CURRENT_LIFT_PERCENTAGE_ATTRIBUTE_ID 0x0008    // Ver.: always
#define ZCL_CURRENT_TILT_PERCENTAGE_ATTRIBUTE_ID 0x0009    // Ver.: always
#define ZCL_OPEN_LIMIT_LIFT_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_CLOSED_LIMIT_LIFT_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_OPEN_LIMIT_TILT_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_CLOSED_LIMIT_TILT_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_VELOCITY_LIFT_ATTRIBUTE_ID 0x0014    // Ver.: always
#define ZCL_ACCELERATION_LIFT_ATTRIBUTE_ID 0x0015    // Ver.: always
#define ZCL_DECELERATION_LIFT_ATTRIBUTE_ID 0x0016    // Ver.: always
#define ZCL_MODE_ATTRIBUTE_ID 0x0017    // Ver.: always
#define ZCL_SETPOINTS_LIFT_ATTRIBUTE_ID 0x0018    // Ver.: always
#define ZCL_SETPOINTS_TILT_ATTRIBUTE_ID 0x0019    // Ver.: always


// Attribute types for cluster: Generic Tunnel
// Cluster specification level: unofficial

// Server attributes
#define ZCL_MAXIMUM_INCOMING_TRANSFER_SIZE_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_MAXIMUM_OUTGOING_TRANSFER_SIZE_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_PROTOCOL_ADDRESS_ATTRIBUTE_ID 0x0003    // Ver.: always


// Attribute types for cluster: Over the Air Bootloading Cluster
// Cluster specification level: 075123r03

// Client attributes
#define ZCL_UPGRADE_SERVER_ID_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_FILE_OFFSET_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_CURRENT_FILE_VERSION_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_CURRENT_ZIGBEE_STACK_VERSION_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_DOWNLOADED_FILE_VERSION_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_DOWNLOADED_ZIGBEE_STACK_VERSION_ATTRIBUTE_ID 0x0005    // Ver.: always
#define ZCL_IMAGE_UPGRADE_STATUS_ATTRIBUTE_ID 0x0006    // Ver.: always
#define ZCL_MANUFACTURER_ID_ATTRIBUTE_ID 0x0007    // Ver.: always
#define ZCL_IMAGE_TYPE_ID_ATTRIBUTE_ID 0x0008    // Ver.: always


// Attribute types for cluster: Demand Response and Load Control
// Cluster specification level: 1.1, 105638r09

// Client attributes
#define ZCL_UTILITY_ENROLLMENT_GROUP_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_START_RANDOMIZE_MINUTES_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_STOP_RANDOMIZE_MINUTES_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_DEVICE_CLASS_VALUE_ATTRIBUTE_ID 0x0003    // Ver.: always


// Attribute types for cluster: Simple Metering
// Cluster specification level: 1.1, 105638r09

// Server attributes
#define ZCL_CURRENT_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_CURRENT_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_CURRENT_MAX_DEMAND_DELIVERED_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_CURRENT_MAX_DEMAND_RECEIVED_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_DFT_SUMMATION_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_DAILY_FREEZE_TIME_ATTRIBUTE_ID 0x0005    // Ver.: always
#define ZCL_POWER_FACTOR_ATTRIBUTE_ID 0x0006    // Ver.: always
#define ZCL_READING_SNAP_SHOT_TIME_ATTRIBUTE_ID 0x0007    // Ver.: always
#define ZCL_CURRENT_MAX_DEMAND_DELIVERED_TIME_ATTRIBUTE_ID 0x0008    // Ver.: always
#define ZCL_CURRENT_MAX_DEMAND_RECEIVED_TIME_ATTRIBUTE_ID 0x0009    // Ver.: always
#define ZCL_DEFAULT_UPDATE_PERIOD_ATTRIBUTE_ID 0x000A    // Ver.: always
#define ZCL_FAST_POLL_UPDATE_PERIOD_ATTRIBUTE_ID 0x000B    // Ver.: always
#define ZCL_CURRENT_BLOCK_PERIOD_CONSUMPTION_DELIVERED_ATTRIBUTE_ID 0x000C    // Ver.: always
#define ZCL_DAILY_CONSUMPTION_TARGET_ATTRIBUTE_ID 0x000D    // Ver.: always
#define ZCL_CURRENT_BLOCK_ATTRIBUTE_ID 0x000E    // Ver.: always
#define ZCL_PROFILE_INTERVAL_PERIOD_ATTRIBUTE_ID 0x000F    // Ver.: always
#define ZCL_INTERVAL_READ_REPORTING_PERIOD_ATTRIBUTE_ID 0x0010    // Ver.: always
#define ZCL_PRESET_READING_TIME_ATTRIBUTE_ID 0x0011    // Ver.: always
#define ZCL_VOLUME_PER_REPORT_ATTRIBUTE_ID 0x0012    // Ver.: always
#define ZCL_FLOW_RESTRICTION_ATTRIBUTE_ID 0x0013    // Ver.: always
#define ZCL_SUPPLY_STATUS_ATTRIBUTE_ID 0x0014    // Ver.: always
#define ZCL_CURRENT_INLET_ENERGY_CARRIER_SUMMATION_ATTRIBUTE_ID 0x0015    // Ver.: always
#define ZCL_CURRENT_OUTLET_ENERGY_CARRIER_SUMMATION_ATTRIBUTE_ID 0x0016    // Ver.: always
#define ZCL_INLET_TEMPERATURE_ATTRIBUTE_ID 0x0017    // Ver.: always
#define ZCL_OUTLET_TEMPERATURE_ATTRIBUTE_ID 0x0018    // Ver.: always
#define ZCL_CONTROL_TEMPERATURE_ATTRIBUTE_ID 0x0019    // Ver.: always
#define ZCL_CURRENT_INLET_ENERGY_CARRIER_DEMAND_ATTRIBUTE_ID 0x001A    // Ver.: always
#define ZCL_CURRENT_OUTLET_ENERGY_CARRIER_DEMAND_ATTRIBUTE_ID 0x001B    // Ver.: always
#define ZCL_CURRENT_TIER1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0100    // Ver.: always
#define ZCL_CURRENT_TIER1_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x0101    // Ver.: always
#define ZCL_CURRENT_TIER2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0102    // Ver.: always
#define ZCL_CURRENT_TIER2_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x0103    // Ver.: always
#define ZCL_CURRENT_TIER3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0104    // Ver.: always
#define ZCL_CURRENT_TIER3_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x0105    // Ver.: always
#define ZCL_CURRENT_TIER4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0106    // Ver.: always
#define ZCL_CURRENT_TIER4_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x0107    // Ver.: always
#define ZCL_CURRENT_TIER5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0108    // Ver.: always
#define ZCL_CURRENT_TIER5_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x0109    // Ver.: always
#define ZCL_CURRENT_TIER6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x010A    // Ver.: always
#define ZCL_CURRENT_TIER6_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x010B    // Ver.: always
#define ZCL_CURRENT_TIER7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x010C    // Ver.: always
#define ZCL_CURRENT_TIER7_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x010D    // Ver.: always
#define ZCL_CURRENT_TIER8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x010E    // Ver.: always
#define ZCL_CURRENT_TIER8_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x010F    // Ver.: always
#define ZCL_CURRENT_TIER9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0110    // Ver.: always
#define ZCL_CURRENT_TIER9_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x0111    // Ver.: always
#define ZCL_CURRENT_TIER10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0112    // Ver.: always
#define ZCL_CURRENT_TIER10_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x0113    // Ver.: always
#define ZCL_CURRENT_TIER11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0114    // Ver.: always
#define ZCL_CURRENT_TIER11_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x0115    // Ver.: always
#define ZCL_CURRENT_TIER12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0116    // Ver.: always
#define ZCL_CURRENT_TIER12_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x0117    // Ver.: always
#define ZCL_CURRENT_TIER13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0118    // Ver.: always
#define ZCL_CURRENT_TIER13_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x0119    // Ver.: always
#define ZCL_CURRENT_TIER14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x011A    // Ver.: always
#define ZCL_CURRENT_TIER14_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x011B    // Ver.: always
#define ZCL_CURRENT_TIER15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x011C    // Ver.: always
#define ZCL_CURRENT_TIER15_SUMMATION_RECEIVED_ATTRIBUTE_ID 0x011D    // Ver.: always
#define ZCL_STATUS_ATTRIBUTE_ID 0x0200    // Ver.: always
#define ZCL_REMAINING_BATTERY_LIFE_ATTRIBUTE_ID 0x0201    // Ver.: always
#define ZCL_HOURS_IN_OPERATION_ATTRIBUTE_ID 0x0202    // Ver.: always
#define ZCL_HOURS_IN_FAULT_ATTRIBUTE_ID 0x0203    // Ver.: always
#define ZCL_UNIT_OF_MEASURE_ATTRIBUTE_ID 0x0300    // Ver.: always
#define ZCL_MULTIPLIER_ATTRIBUTE_ID 0x0301    // Ver.: always
#define ZCL_DIVISOR_ATTRIBUTE_ID 0x0302    // Ver.: always
#define ZCL_SUMMATION_FORMATTING_ATTRIBUTE_ID 0x0303    // Ver.: always
#define ZCL_DEMAND_FORMATTING_ATTRIBUTE_ID 0x0304    // Ver.: always
#define ZCL_HISTORICAL_CONSUMPTION_FORMATTING_ATTRIBUTE_ID 0x0305    // Ver.: always
#define ZCL_METERING_DEVICE_TYPE_ATTRIBUTE_ID 0x0306    // Ver.: always
#define ZCL_SITE_ID_ATTRIBUTE_ID 0x0307    // Ver.: always
#define ZCL_METER_SERIAL_NUMBER_ATTRIBUTE_ID 0x0308    // Ver.: always
#define ZCL_ENERGY_CARRIER_UNIT_OF_MEASURE_ATTRIBUTE_ID 0x0309    // Ver.: always
#define ZCL_ENERGY_CARRIER_SUMMATION_FORMATTING_ATTRIBUTE_ID 0x030A    // Ver.: always
#define ZCL_ENERGY_CARRIER_DEMAND_FORMATTING_ATTRIBUTE_ID 0x030B    // Ver.: always
#define ZCL_TEMPERATURE_UNIT_OF_MEASURE_ATTRIBUTE_ID 0x030C    // Ver.: always
#define ZCL_TEMPERATURE_FORMATTING_ATTRIBUTE_ID 0x030D    // Ver.: always
#define ZCL_INSTANTANEOUS_DEMAND_ATTRIBUTE_ID 0x0400    // Ver.: always
#define ZCL_CURRENT_DAY_CONSUMPTION_DELIVERED_ATTRIBUTE_ID 0x0401    // Ver.: always
#define ZCL_CURRENT_DAY_CONSUMPTION_RECEIVED_ATTRIBUTE_ID 0x0402    // Ver.: always
#define ZCL_PREVIOUS_DAY_CONSUMPTION_DELIVERED_ATTRIBUTE_ID 0x0403    // Ver.: always
#define ZCL_PREVIOUS_DAY_CONSUMPTION_RECEIVED_ATTRIBUTE_ID 0x0404    // Ver.: always
#define ZCL_CURRENT_PARTIAL_PROFILE_INTERVAL_START_TIME_DELIVERED_ATTRIBUTE_ID 0x0405    // Ver.: always
#define ZCL_CURRENT_PARTIAL_PROFILE_INTERVAL_START_TIME_RECEIVED_ATTRIBUTE_ID 0x0406    // Ver.: always
#define ZCL_CURRENT_PARTIAL_PROFILE_INTERVAL_VALUE_DELIVERED_ATTRIBUTE_ID 0x0407    // Ver.: always
#define ZCL_CURRENT_PARTIAL_PROFILE_INTERVAL_VALUE_RECEIVED_ATTRIBUTE_ID 0x0408    // Ver.: always
#define ZCL_CURRENT_DAY_MAX_PRESSURE_ATTRIBUTE_ID 0x0409    // Ver.: always
#define ZCL_CURRENT_DAY_MIN_PRESSURE_ATTRIBUTE_ID 0x040A    // Ver.: always
#define ZCL_PREVIOUS_DAY_MAX_PRESSURE_ATTRIBUTE_ID 0x040B    // Ver.: always
#define ZCL_PREVIOUS_DAY_MIN_PRESSURE_ATTRIBUTE_ID 0x040C    // Ver.: always
#define ZCL_CURRENT_DAY_MAX_DEMAND_ATTRIBUTE_ID 0x040D    // Ver.: always
#define ZCL_PREVIOUS_DAY_MAX_DEMAND_ATTRIBUTE_ID 0x040E    // Ver.: always
#define ZCL_CURRENT_MONTH_MAX_DEMAND_ATTRIBUTE_ID 0x040F    // Ver.: always
#define ZCL_CURRENT_YEAR_MAX_DEMAND_ATTRIBUTE_ID 0x0410    // Ver.: always
#define ZCL_CURRENT_DAY_MAX_ENERGY_CARRIER_DEMAND_ATTRIBUTE_ID 0x0411    // Ver.: always
#define ZCL_PREVIOUS_DAY_MAX_ENERGY_CARRIER_DEMAND_ATTRIBUTE_ID 0x0412    // Ver.: always
#define ZCL_CURRENT_MONTH_MAX_ENERGY_CARRIER_DEMAND_ATTRIBUTE_ID 0x0413    // Ver.: always
#define ZCL_CURRENT_MONTH_MIN_ENERGY_CARRIER_DEMAND_ATTRIBUTE_ID 0x0414    // Ver.: always
#define ZCL_CURRENT_YEAR_MAX_ENERGY_CARRIER_DEMAND_ATTRIBUTE_ID 0x0415    // Ver.: always
#define ZCL_CURRENT_YEAR_MIN_ENERGY_CARRIER_DEMAND_ATTRIBUTE_ID 0x0416    // Ver.: always
#define ZCL_MAX_NUMBER_OF_PERIODS_DELIVERED_ATTRIBUTE_ID 0x0500    // Ver.: always
#define ZCL_CURRENT_DEMAND_DELIVERED_ATTRIBUTE_ID 0x0600    // Ver.: always
#define ZCL_DEMAND_LIMIT_ATTRIBUTE_ID 0x0601    // Ver.: always
#define ZCL_DEMAND_INTEGRATION_PERIOD_ATTRIBUTE_ID 0x0602    // Ver.: always
#define ZCL_NUMBER_OF_DEMAND_SUBINTERVALS_ATTRIBUTE_ID 0x0603    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0700    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0701    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0702    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0703    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0704    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0705    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0706    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0707    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0708    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0709    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x070A    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x070B    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x070C    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x070D    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x070E    // Ver.: always
#define ZCL_CURRENT_NO_TIER_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x070F    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0710    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0711    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0712    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0713    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0714    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0715    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0716    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0717    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0718    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0719    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x071A    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x071B    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x071C    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x071D    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x071E    // Ver.: always
#define ZCL_CURRENT_TIER1_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x071F    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0720    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0721    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0722    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0723    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0724    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0725    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0726    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0727    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0728    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0729    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x072A    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x072B    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x072C    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x072D    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x072E    // Ver.: always
#define ZCL_CURRENT_TIER2_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x072F    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0730    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0731    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0732    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0733    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0734    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0735    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0736    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0737    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0738    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0739    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x073A    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x073B    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x073C    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x073D    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x073E    // Ver.: always
#define ZCL_CURRENT_TIER3_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x073F    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0740    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0741    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0742    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0743    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0744    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0745    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0746    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0747    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0748    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0749    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x074A    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x074B    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x074C    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x074D    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x074E    // Ver.: always
#define ZCL_CURRENT_TIER4_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x074F    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0750    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0751    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0752    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0753    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0754    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0755    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0756    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0757    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0758    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0759    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x075A    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x075B    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x075C    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x075D    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x075E    // Ver.: always
#define ZCL_CURRENT_TIER5_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x075F    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0760    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0761    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0762    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0763    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0764    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0765    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0766    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0767    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0768    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0769    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x076A    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x076B    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x076C    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x076D    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x076E    // Ver.: always
#define ZCL_CURRENT_TIER6_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x076F    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0770    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0771    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0772    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0773    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0774    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0775    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0776    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0777    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0778    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0779    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x077A    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x077B    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x077C    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x077D    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x077E    // Ver.: always
#define ZCL_CURRENT_TIER7_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x077F    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0780    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0781    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0782    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0783    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0784    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0785    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0786    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0787    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0788    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0789    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x078A    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x078B    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x078C    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x078D    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x078E    // Ver.: always
#define ZCL_CURRENT_TIER8_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x078F    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0790    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0791    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0792    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0793    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0794    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0795    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0796    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0797    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0798    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x0799    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x079A    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x079B    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x079C    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x079D    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x079E    // Ver.: always
#define ZCL_CURRENT_TIER9_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x079F    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07A0    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07A1    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07A2    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07A3    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07A4    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07A5    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07A6    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07A7    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07A8    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07A9    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07AA    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07AB    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07AC    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07AD    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07AE    // Ver.: always
#define ZCL_CURRENT_TIER10_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07AF    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07B0    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07B1    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07B2    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07B3    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07B4    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07B5    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07B6    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07B7    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07B8    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07B9    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07BA    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07BB    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07BC    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07BD    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07BE    // Ver.: always
#define ZCL_CURRENT_TIER11_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07BF    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07C0    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07C1    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07C2    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07C3    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07C4    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07C5    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07C6    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07C7    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07C8    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07C9    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07CA    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07CB    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07CC    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07CD    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07CE    // Ver.: always
#define ZCL_CURRENT_TIER12_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07CF    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07D0    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07D1    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07D2    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07D3    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07D4    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07D5    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07D6    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07D7    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07D8    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07D9    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07DA    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07DB    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07DC    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07DD    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07DE    // Ver.: always
#define ZCL_CURRENT_TIER13_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07DF    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07E0    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07E1    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07E2    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07E3    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07E4    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07E5    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07E6    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07E7    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07E8    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07E9    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07EA    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07EB    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07EC    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07ED    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07EE    // Ver.: always
#define ZCL_CURRENT_TIER14_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07EF    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK1_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07F0    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK2_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07F1    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK3_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07F2    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK4_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07F3    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK5_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07F4    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK6_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07F5    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK7_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07F6    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK8_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07F7    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK9_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07F8    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK10_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07F9    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK11_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07FA    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK12_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07FB    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK13_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07FC    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK14_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07FD    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK15_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07FE    // Ver.: always
#define ZCL_CURRENT_TIER15_BLOCK16_SUMMATION_DELIVERED_ATTRIBUTE_ID 0x07FF    // Ver.: always
#define ZCL_GENERIC_ALARM_MASK_ATTRIBUTE_ID 0x0800    // Ver.: always
#define ZCL_ELECTRICITY_ALARM_MASK_ATTRIBUTE_ID 0x0801    // Ver.: always
#define ZCL_GENERIC_FLOW_PRESSURE_ALARM_MASK_ATTRIBUTE_ID 0x0802    // Ver.: always
#define ZCL_WATER_SPECIFIC_ALARM_MASK_ATTRIBUTE_ID 0x0803    // Ver.: always
#define ZCL_HEAT_AND_COOLING_SPECIFIC_ALARM_MASK_ATTRIBUTE_ID 0x0804    // Ver.: always
#define ZCL_GAS_SPECIFIC_ALARM_MASK_ATTRIBUTE_ID 0x0805    // Ver.: always
#define ZCL_MIRROR_IEEE_ADDRESS_ATTRIBUTE_ID 0xF000    // Ver.: always
#define ZCL_MIRROR_SYNC_PERIOD_ATTRIBUTE_ID 0xF001    // Ver.: always
#define ZCL_MIRROR_LAST_SYNC_TIME_ATTRIBUTE_ID 0xF002    // Ver.: always


// Attribute types for cluster: Price
// Cluster specification level: 1.1, 105638r09

// Client attributes
#define ZCL_PRICE_INCREASE_RANDOMIZE_MINUTES_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_PRICE_DECREASE_RANDOMIZE_MINUTES_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_COMMODITY_TYPE_CLIENT_ATTRIBUTE_ID 0x0002    // Ver.: always

// Server attributes
#define ZCL_TIER1_PRICE_LABEL_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_TIER2_PRICE_LABEL_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_TIER3_PRICE_LABEL_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_TIER4_PRICE_LABEL_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_TIER5_PRICE_LABEL_ATTRIBUTE_ID 0x0004    // Ver.: always
#define ZCL_TIER6_PRICE_LABEL_ATTRIBUTE_ID 0x0005    // Ver.: always
#define ZCL_TIER7_PRICE_LABEL_ATTRIBUTE_ID 0x0006    // Ver.: always
#define ZCL_TIER8_PRICE_LABEL_ATTRIBUTE_ID 0x0007    // Ver.: always
#define ZCL_TIER9_PRICE_LABEL_ATTRIBUTE_ID 0x0008    // Ver.: always
#define ZCL_TIER10_PRICE_LABEL_ATTRIBUTE_ID 0x0009    // Ver.: always
#define ZCL_TIER11_PRICE_LABEL_ATTRIBUTE_ID 0x000A    // Ver.: always
#define ZCL_TIER12_PRICE_LABEL_ATTRIBUTE_ID 0x000B    // Ver.: always
#define ZCL_TIER13_PRICE_LABEL_ATTRIBUTE_ID 0x000C    // Ver.: always
#define ZCL_TIER14_PRICE_LABEL_ATTRIBUTE_ID 0x000D    // Ver.: always
#define ZCL_TIER15_PRICE_LABEL_ATTRIBUTE_ID 0x000E    // Ver.: always
#define ZCL_BLOCK1_THRESHOLD_ATTRIBUTE_ID 0x0100    // Ver.: always
#define ZCL_BLOCK2_THRESHOLD_ATTRIBUTE_ID 0x0101    // Ver.: always
#define ZCL_BLOCK3_THRESHOLD_ATTRIBUTE_ID 0x0102    // Ver.: always
#define ZCL_BLOCK4_THRESHOLD_ATTRIBUTE_ID 0x0103    // Ver.: always
#define ZCL_BLOCK5_THRESHOLD_ATTRIBUTE_ID 0x0104    // Ver.: always
#define ZCL_BLOCK6_THRESHOLD_ATTRIBUTE_ID 0x0105    // Ver.: always
#define ZCL_BLOCK7_THRESHOLD_ATTRIBUTE_ID 0x0106    // Ver.: always
#define ZCL_BLOCK8_THRESHOLD_ATTRIBUTE_ID 0x0107    // Ver.: always
#define ZCL_BLOCK9_THRESHOLD_ATTRIBUTE_ID 0x0108    // Ver.: always
#define ZCL_BLOCK10_THRESHOLD_ATTRIBUTE_ID 0x0109    // Ver.: always
#define ZCL_BLOCK11_THRESHOLD_ATTRIBUTE_ID 0x010A    // Ver.: always
#define ZCL_BLOCK12_THRESHOLD_ATTRIBUTE_ID 0x010B    // Ver.: always
#define ZCL_BLOCK13_THRESHOLD_ATTRIBUTE_ID 0x010C    // Ver.: always
#define ZCL_BLOCK14_THRESHOLD_ATTRIBUTE_ID 0x010D    // Ver.: always
#define ZCL_BLOCK15_THRESHOLD_ATTRIBUTE_ID 0x010E    // Ver.: always
#define ZCL_START_OF_BLOCK_PERIOD_ATTRIBUTE_ID 0x0200    // Ver.: always
#define ZCL_BLOCK_PERIOD_DURATION_MINUTES_ATTRIBUTE_ID 0x0201    // Ver.: always
#define ZCL_THRESHOLD_MULTIPLIER_ATTRIBUTE_ID 0x0202    // Ver.: always
#define ZCL_THRESHOLD_DIVISOR_ATTRIBUTE_ID 0x0203    // Ver.: always
#define ZCL_COMMODITY_TYPE_SERVER_ATTRIBUTE_ID 0x0300    // Ver.: always
#define ZCL_STANDING_CHARGE_ATTRIBUTE_ID 0x0301    // Ver.: always
#define ZCL_NO_TIER_BLOCK1_PRICE_ATTRIBUTE_ID 0x0400    // Ver.: always
#define ZCL_NO_TIER_BLOCK2_PRICE_ATTRIBUTE_ID 0x0401    // Ver.: always
#define ZCL_NO_TIER_BLOCK3_PRICE_ATTRIBUTE_ID 0x0402    // Ver.: always
#define ZCL_NO_TIER_BLOCK4_PRICE_ATTRIBUTE_ID 0x0403    // Ver.: always
#define ZCL_NO_TIER_BLOCK5_PRICE_ATTRIBUTE_ID 0x0404    // Ver.: always
#define ZCL_NO_TIER_BLOCK6_PRICE_ATTRIBUTE_ID 0x0405    // Ver.: always
#define ZCL_NO_TIER_BLOCK7_PRICE_ATTRIBUTE_ID 0x0406    // Ver.: always
#define ZCL_NO_TIER_BLOCK8_PRICE_ATTRIBUTE_ID 0x0407    // Ver.: always
#define ZCL_NO_TIER_BLOCK9_PRICE_ATTRIBUTE_ID 0x0408    // Ver.: always
#define ZCL_NO_TIER_BLOCK10_PRICE_ATTRIBUTE_ID 0x0409    // Ver.: always
#define ZCL_NO_TIER_BLOCK11_PRICE_ATTRIBUTE_ID 0x040A    // Ver.: always
#define ZCL_NO_TIER_BLOCK12_PRICE_ATTRIBUTE_ID 0x040B    // Ver.: always
#define ZCL_NO_TIER_BLOCK13_PRICE_ATTRIBUTE_ID 0x040C    // Ver.: always
#define ZCL_NO_TIER_BLOCK14_PRICE_ATTRIBUTE_ID 0x040D    // Ver.: always
#define ZCL_NO_TIER_BLOCK15_PRICE_ATTRIBUTE_ID 0x040E    // Ver.: always
#define ZCL_NO_TIER_BLOCK16_PRICE_ATTRIBUTE_ID 0x040F    // Ver.: always
#define ZCL_TIER1_BLOCK1_PRICE_ATTRIBUTE_ID 0x0410    // Ver.: always
#define ZCL_TIER1_BLOCK2_PRICE_ATTRIBUTE_ID 0x0411    // Ver.: always
#define ZCL_TIER1_BLOCK3_PRICE_ATTRIBUTE_ID 0x0412    // Ver.: always
#define ZCL_TIER1_BLOCK4_PRICE_ATTRIBUTE_ID 0x0413    // Ver.: always
#define ZCL_TIER1_BLOCK5_PRICE_ATTRIBUTE_ID 0x0414    // Ver.: always
#define ZCL_TIER1_BLOCK6_PRICE_ATTRIBUTE_ID 0x0415    // Ver.: always
#define ZCL_TIER1_BLOCK7_PRICE_ATTRIBUTE_ID 0x0416    // Ver.: always
#define ZCL_TIER1_BLOCK8_PRICE_ATTRIBUTE_ID 0x0417    // Ver.: always
#define ZCL_TIER1_BLOCK9_PRICE_ATTRIBUTE_ID 0x0418    // Ver.: always
#define ZCL_TIER1_BLOCK10_PRICE_ATTRIBUTE_ID 0x0419    // Ver.: always
#define ZCL_TIER1_BLOCK11_PRICE_ATTRIBUTE_ID 0x041A    // Ver.: always
#define ZCL_TIER1_BLOCK12_PRICE_ATTRIBUTE_ID 0x041B    // Ver.: always
#define ZCL_TIER1_BLOCK13_PRICE_ATTRIBUTE_ID 0x041C    // Ver.: always
#define ZCL_TIER1_BLOCK14_PRICE_ATTRIBUTE_ID 0x041D    // Ver.: always
#define ZCL_TIER1_BLOCK15_PRICE_ATTRIBUTE_ID 0x041E    // Ver.: always
#define ZCL_TIER1_BLOCK16_PRICE_ATTRIBUTE_ID 0x041F    // Ver.: always
#define ZCL_TIER2_BLOCK1_PRICE_ATTRIBUTE_ID 0x0420    // Ver.: always
#define ZCL_TIER2_BLOCK2_PRICE_ATTRIBUTE_ID 0x0421    // Ver.: always
#define ZCL_TIER2_BLOCK3_PRICE_ATTRIBUTE_ID 0x0422    // Ver.: always
#define ZCL_TIER2_BLOCK4_PRICE_ATTRIBUTE_ID 0x0423    // Ver.: always
#define ZCL_TIER2_BLOCK5_PRICE_ATTRIBUTE_ID 0x0424    // Ver.: always
#define ZCL_TIER2_BLOCK6_PRICE_ATTRIBUTE_ID 0x0425    // Ver.: always
#define ZCL_TIER2_BLOCK7_PRICE_ATTRIBUTE_ID 0x0426    // Ver.: always
#define ZCL_TIER2_BLOCK8_PRICE_ATTRIBUTE_ID 0x0427    // Ver.: always
#define ZCL_TIER2_BLOCK9_PRICE_ATTRIBUTE_ID 0x0428    // Ver.: always
#define ZCL_TIER2_BLOCK10_PRICE_ATTRIBUTE_ID 0x0429    // Ver.: always
#define ZCL_TIER2_BLOCK11_PRICE_ATTRIBUTE_ID 0x042A    // Ver.: always
#define ZCL_TIER2_BLOCK12_PRICE_ATTRIBUTE_ID 0x042B    // Ver.: always
#define ZCL_TIER2_BLOCK13_PRICE_ATTRIBUTE_ID 0x042C    // Ver.: always
#define ZCL_TIER2_BLOCK14_PRICE_ATTRIBUTE_ID 0x042D    // Ver.: always
#define ZCL_TIER2_BLOCK15_PRICE_ATTRIBUTE_ID 0x042E    // Ver.: always
#define ZCL_TIER2_BLOCK16_PRICE_ATTRIBUTE_ID 0x042F    // Ver.: always
#define ZCL_TIER3_BLOCK1_PRICE_ATTRIBUTE_ID 0x0430    // Ver.: always
#define ZCL_TIER3_BLOCK2_PRICE_ATTRIBUTE_ID 0x0431    // Ver.: always
#define ZCL_TIER3_BLOCK3_PRICE_ATTRIBUTE_ID 0x0432    // Ver.: always
#define ZCL_TIER3_BLOCK4_PRICE_ATTRIBUTE_ID 0x0433    // Ver.: always
#define ZCL_TIER3_BLOCK5_PRICE_ATTRIBUTE_ID 0x0434    // Ver.: always
#define ZCL_TIER3_BLOCK6_PRICE_ATTRIBUTE_ID 0x0435    // Ver.: always
#define ZCL_TIER3_BLOCK7_PRICE_ATTRIBUTE_ID 0x0436    // Ver.: always
#define ZCL_TIER3_BLOCK8_PRICE_ATTRIBUTE_ID 0x0437    // Ver.: always
#define ZCL_TIER3_BLOCK9_PRICE_ATTRIBUTE_ID 0x0438    // Ver.: always
#define ZCL_TIER3_BLOCK10_PRICE_ATTRIBUTE_ID 0x0439    // Ver.: always
#define ZCL_TIER3_BLOCK11_PRICE_ATTRIBUTE_ID 0x043A    // Ver.: always
#define ZCL_TIER3_BLOCK12_PRICE_ATTRIBUTE_ID 0x043B    // Ver.: always
#define ZCL_TIER3_BLOCK13_PRICE_ATTRIBUTE_ID 0x043C    // Ver.: always
#define ZCL_TIER3_BLOCK14_PRICE_ATTRIBUTE_ID 0x043D    // Ver.: always
#define ZCL_TIER3_BLOCK15_PRICE_ATTRIBUTE_ID 0x043E    // Ver.: always
#define ZCL_TIER3_BLOCK16_PRICE_ATTRIBUTE_ID 0x043F    // Ver.: always
#define ZCL_TIER4_BLOCK1_PRICE_ATTRIBUTE_ID 0x0440    // Ver.: always
#define ZCL_TIER4_BLOCK2_PRICE_ATTRIBUTE_ID 0x0441    // Ver.: always
#define ZCL_TIER4_BLOCK3_PRICE_ATTRIBUTE_ID 0x0442    // Ver.: always
#define ZCL_TIER4_BLOCK4_PRICE_ATTRIBUTE_ID 0x0443    // Ver.: always
#define ZCL_TIER4_BLOCK5_PRICE_ATTRIBUTE_ID 0x0444    // Ver.: always
#define ZCL_TIER4_BLOCK6_PRICE_ATTRIBUTE_ID 0x0445    // Ver.: always
#define ZCL_TIER4_BLOCK7_PRICE_ATTRIBUTE_ID 0x0446    // Ver.: always
#define ZCL_TIER4_BLOCK8_PRICE_ATTRIBUTE_ID 0x0447    // Ver.: always
#define ZCL_TIER4_BLOCK9_PRICE_ATTRIBUTE_ID 0x0448    // Ver.: always
#define ZCL_TIER4_BLOCK10_PRICE_ATTRIBUTE_ID 0x0449    // Ver.: always
#define ZCL_TIER4_BLOCK11_PRICE_ATTRIBUTE_ID 0x044A    // Ver.: always
#define ZCL_TIER4_BLOCK12_PRICE_ATTRIBUTE_ID 0x044B    // Ver.: always
#define ZCL_TIER4_BLOCK13_PRICE_ATTRIBUTE_ID 0x044C    // Ver.: always
#define ZCL_TIER4_BLOCK14_PRICE_ATTRIBUTE_ID 0x044D    // Ver.: always
#define ZCL_TIER4_BLOCK15_PRICE_ATTRIBUTE_ID 0x044E    // Ver.: always
#define ZCL_TIER4_BLOCK16_PRICE_ATTRIBUTE_ID 0x044F    // Ver.: always
#define ZCL_TIER5_BLOCK1_PRICE_ATTRIBUTE_ID 0x0450    // Ver.: always
#define ZCL_TIER5_BLOCK2_PRICE_ATTRIBUTE_ID 0x0451    // Ver.: always
#define ZCL_TIER5_BLOCK3_PRICE_ATTRIBUTE_ID 0x0452    // Ver.: always
#define ZCL_TIER5_BLOCK4_PRICE_ATTRIBUTE_ID 0x0453    // Ver.: always
#define ZCL_TIER5_BLOCK5_PRICE_ATTRIBUTE_ID 0x0454    // Ver.: always
#define ZCL_TIER5_BLOCK6_PRICE_ATTRIBUTE_ID 0x0455    // Ver.: always
#define ZCL_TIER5_BLOCK7_PRICE_ATTRIBUTE_ID 0x0456    // Ver.: always
#define ZCL_TIER5_BLOCK8_PRICE_ATTRIBUTE_ID 0x0457    // Ver.: always
#define ZCL_TIER5_BLOCK9_PRICE_ATTRIBUTE_ID 0x0458    // Ver.: always
#define ZCL_TIER5_BLOCK10_PRICE_ATTRIBUTE_ID 0x0459    // Ver.: always
#define ZCL_TIER5_BLOCK11_PRICE_ATTRIBUTE_ID 0x045A    // Ver.: always
#define ZCL_TIER5_BLOCK12_PRICE_ATTRIBUTE_ID 0x045B    // Ver.: always
#define ZCL_TIER5_BLOCK13_PRICE_ATTRIBUTE_ID 0x045C    // Ver.: always
#define ZCL_TIER5_BLOCK14_PRICE_ATTRIBUTE_ID 0x045D    // Ver.: always
#define ZCL_TIER5_BLOCK15_PRICE_ATTRIBUTE_ID 0x045E    // Ver.: always
#define ZCL_TIER5_BLOCK16_PRICE_ATTRIBUTE_ID 0x045F    // Ver.: always
#define ZCL_TIER6_BLOCK1_PRICE_ATTRIBUTE_ID 0x0460    // Ver.: always
#define ZCL_TIER6_BLOCK2_PRICE_ATTRIBUTE_ID 0x0461    // Ver.: always
#define ZCL_TIER6_BLOCK3_PRICE_ATTRIBUTE_ID 0x0462    // Ver.: always
#define ZCL_TIER6_BLOCK4_PRICE_ATTRIBUTE_ID 0x0463    // Ver.: always
#define ZCL_TIER6_BLOCK5_PRICE_ATTRIBUTE_ID 0x0464    // Ver.: always
#define ZCL_TIER6_BLOCK6_PRICE_ATTRIBUTE_ID 0x0465    // Ver.: always
#define ZCL_TIER6_BLOCK7_PRICE_ATTRIBUTE_ID 0x0466    // Ver.: always
#define ZCL_TIER6_BLOCK8_PRICE_ATTRIBUTE_ID 0x0467    // Ver.: always
#define ZCL_TIER6_BLOCK9_PRICE_ATTRIBUTE_ID 0x0468    // Ver.: always
#define ZCL_TIER6_BLOCK10_PRICE_ATTRIBUTE_ID 0x0469    // Ver.: always
#define ZCL_TIER6_BLOCK11_PRICE_ATTRIBUTE_ID 0x046A    // Ver.: always
#define ZCL_TIER6_BLOCK12_PRICE_ATTRIBUTE_ID 0x046B    // Ver.: always
#define ZCL_TIER6_BLOCK13_PRICE_ATTRIBUTE_ID 0x046C    // Ver.: always
#define ZCL_TIER6_BLOCK14_PRICE_ATTRIBUTE_ID 0x046D    // Ver.: always
#define ZCL_TIER6_BLOCK15_PRICE_ATTRIBUTE_ID 0x046E    // Ver.: always
#define ZCL_TIER6_BLOCK16_PRICE_ATTRIBUTE_ID 0x046F    // Ver.: always
#define ZCL_TIER7_BLOCK1_PRICE_ATTRIBUTE_ID 0x0470    // Ver.: always
#define ZCL_TIER7_BLOCK2_PRICE_ATTRIBUTE_ID 0x0471    // Ver.: always
#define ZCL_TIER7_BLOCK3_PRICE_ATTRIBUTE_ID 0x0472    // Ver.: always
#define ZCL_TIER7_BLOCK4_PRICE_ATTRIBUTE_ID 0x0473    // Ver.: always
#define ZCL_TIER7_BLOCK5_PRICE_ATTRIBUTE_ID 0x0474    // Ver.: always
#define ZCL_TIER7_BLOCK6_PRICE_ATTRIBUTE_ID 0x0475    // Ver.: always
#define ZCL_TIER7_BLOCK7_PRICE_ATTRIBUTE_ID 0x0476    // Ver.: always
#define ZCL_TIER7_BLOCK8_PRICE_ATTRIBUTE_ID 0x0477    // Ver.: always
#define ZCL_TIER7_BLOCK9_PRICE_ATTRIBUTE_ID 0x0478    // Ver.: always
#define ZCL_TIER7_BLOCK10_PRICE_ATTRIBUTE_ID 0x0479    // Ver.: always
#define ZCL_TIER7_BLOCK11_PRICE_ATTRIBUTE_ID 0x047A    // Ver.: always
#define ZCL_TIER7_BLOCK12_PRICE_ATTRIBUTE_ID 0x047B    // Ver.: always
#define ZCL_TIER7_BLOCK13_PRICE_ATTRIBUTE_ID 0x047C    // Ver.: always
#define ZCL_TIER7_BLOCK14_PRICE_ATTRIBUTE_ID 0x047D    // Ver.: always
#define ZCL_TIER7_BLOCK15_PRICE_ATTRIBUTE_ID 0x047E    // Ver.: always
#define ZCL_TIER7_BLOCK16_PRICE_ATTRIBUTE_ID 0x047F    // Ver.: always
#define ZCL_TIER8_BLOCK1_PRICE_ATTRIBUTE_ID 0x0480    // Ver.: always
#define ZCL_TIER8_BLOCK2_PRICE_ATTRIBUTE_ID 0x0481    // Ver.: always
#define ZCL_TIER8_BLOCK3_PRICE_ATTRIBUTE_ID 0x0482    // Ver.: always
#define ZCL_TIER8_BLOCK4_PRICE_ATTRIBUTE_ID 0x0483    // Ver.: always
#define ZCL_TIER8_BLOCK5_PRICE_ATTRIBUTE_ID 0x0484    // Ver.: always
#define ZCL_TIER8_BLOCK6_PRICE_ATTRIBUTE_ID 0x0485    // Ver.: always
#define ZCL_TIER8_BLOCK7_PRICE_ATTRIBUTE_ID 0x0486    // Ver.: always
#define ZCL_TIER8_BLOCK8_PRICE_ATTRIBUTE_ID 0x0487    // Ver.: always
#define ZCL_TIER8_BLOCK9_PRICE_ATTRIBUTE_ID 0x0488    // Ver.: always
#define ZCL_TIER8_BLOCK10_PRICE_ATTRIBUTE_ID 0x0489    // Ver.: always
#define ZCL_TIER8_BLOCK11_PRICE_ATTRIBUTE_ID 0x048A    // Ver.: always
#define ZCL_TIER8_BLOCK12_PRICE_ATTRIBUTE_ID 0x048B    // Ver.: always
#define ZCL_TIER8_BLOCK13_PRICE_ATTRIBUTE_ID 0x048C    // Ver.: always
#define ZCL_TIER8_BLOCK14_PRICE_ATTRIBUTE_ID 0x048D    // Ver.: always
#define ZCL_TIER8_BLOCK15_PRICE_ATTRIBUTE_ID 0x048E    // Ver.: always
#define ZCL_TIER8_BLOCK16_PRICE_ATTRIBUTE_ID 0x048F    // Ver.: always
#define ZCL_TIER9_BLOCK1_PRICE_ATTRIBUTE_ID 0x0490    // Ver.: always
#define ZCL_TIER9_BLOCK2_PRICE_ATTRIBUTE_ID 0x0491    // Ver.: always
#define ZCL_TIER9_BLOCK3_PRICE_ATTRIBUTE_ID 0x0492    // Ver.: always
#define ZCL_TIER9_BLOCK4_PRICE_ATTRIBUTE_ID 0x0493    // Ver.: always
#define ZCL_TIER9_BLOCK5_PRICE_ATTRIBUTE_ID 0x0494    // Ver.: always
#define ZCL_TIER9_BLOCK6_PRICE_ATTRIBUTE_ID 0x0495    // Ver.: always
#define ZCL_TIER9_BLOCK7_PRICE_ATTRIBUTE_ID 0x0496    // Ver.: always
#define ZCL_TIER9_BLOCK8_PRICE_ATTRIBUTE_ID 0x0497    // Ver.: always
#define ZCL_TIER9_BLOCK9_PRICE_ATTRIBUTE_ID 0x0498    // Ver.: always
#define ZCL_TIER9_BLOCK10_PRICE_ATTRIBUTE_ID 0x0499    // Ver.: always
#define ZCL_TIER9_BLOCK11_PRICE_ATTRIBUTE_ID 0x049A    // Ver.: always
#define ZCL_TIER9_BLOCK12_PRICE_ATTRIBUTE_ID 0x049B    // Ver.: always
#define ZCL_TIER9_BLOCK13_PRICE_ATTRIBUTE_ID 0x049C    // Ver.: always
#define ZCL_TIER9_BLOCK14_PRICE_ATTRIBUTE_ID 0x049D    // Ver.: always
#define ZCL_TIER9_BLOCK15_PRICE_ATTRIBUTE_ID 0x049E    // Ver.: always
#define ZCL_TIER9_BLOCK16_PRICE_ATTRIBUTE_ID 0x049F    // Ver.: always
#define ZCL_TIER10_BLOCK1_PRICE_ATTRIBUTE_ID 0x04A0    // Ver.: always
#define ZCL_TIER10_BLOCK2_PRICE_ATTRIBUTE_ID 0x04A1    // Ver.: always
#define ZCL_TIER10_BLOCK3_PRICE_ATTRIBUTE_ID 0x04A2    // Ver.: always
#define ZCL_TIER10_BLOCK4_PRICE_ATTRIBUTE_ID 0x04A3    // Ver.: always
#define ZCL_TIER10_BLOCK5_PRICE_ATTRIBUTE_ID 0x04A4    // Ver.: always
#define ZCL_TIER10_BLOCK6_PRICE_ATTRIBUTE_ID 0x04A5    // Ver.: always
#define ZCL_TIER10_BLOCK7_PRICE_ATTRIBUTE_ID 0x04A6    // Ver.: always
#define ZCL_TIER10_BLOCK8_PRICE_ATTRIBUTE_ID 0x04A7    // Ver.: always
#define ZCL_TIER10_BLOCK9_PRICE_ATTRIBUTE_ID 0x04A8    // Ver.: always
#define ZCL_TIER10_BLOCK10_PRICE_ATTRIBUTE_ID 0x04A9    // Ver.: always
#define ZCL_TIER10_BLOCK11_PRICE_ATTRIBUTE_ID 0x04AA    // Ver.: always
#define ZCL_TIER10_BLOCK12_PRICE_ATTRIBUTE_ID 0x04AB    // Ver.: always
#define ZCL_TIER10_BLOCK13_PRICE_ATTRIBUTE_ID 0x04AC    // Ver.: always
#define ZCL_TIER10_BLOCK14_PRICE_ATTRIBUTE_ID 0x04AD    // Ver.: always
#define ZCL_TIER10_BLOCK15_PRICE_ATTRIBUTE_ID 0x04AE    // Ver.: always
#define ZCL_TIER10_BLOCK16_PRICE_ATTRIBUTE_ID 0x04AF    // Ver.: always
#define ZCL_TIER11_BLOCK1_PRICE_ATTRIBUTE_ID 0x04B0    // Ver.: always
#define ZCL_TIER11_BLOCK2_PRICE_ATTRIBUTE_ID 0x04B1    // Ver.: always
#define ZCL_TIER11_BLOCK3_PRICE_ATTRIBUTE_ID 0x04B2    // Ver.: always
#define ZCL_TIER11_BLOCK4_PRICE_ATTRIBUTE_ID 0x04B3    // Ver.: always
#define ZCL_TIER11_BLOCK5_PRICE_ATTRIBUTE_ID 0x04B4    // Ver.: always
#define ZCL_TIER11_BLOCK6_PRICE_ATTRIBUTE_ID 0x04B5    // Ver.: always
#define ZCL_TIER11_BLOCK7_PRICE_ATTRIBUTE_ID 0x04B6    // Ver.: always
#define ZCL_TIER11_BLOCK8_PRICE_ATTRIBUTE_ID 0x04B7    // Ver.: always
#define ZCL_TIER11_BLOCK9_PRICE_ATTRIBUTE_ID 0x04B8    // Ver.: always
#define ZCL_TIER11_BLOCK10_PRICE_ATTRIBUTE_ID 0x04B9    // Ver.: always
#define ZCL_TIER11_BLOCK11_PRICE_ATTRIBUTE_ID 0x04BA    // Ver.: always
#define ZCL_TIER11_BLOCK12_PRICE_ATTRIBUTE_ID 0x04BB    // Ver.: always
#define ZCL_TIER11_BLOCK13_PRICE_ATTRIBUTE_ID 0x04BC    // Ver.: always
#define ZCL_TIER11_BLOCK14_PRICE_ATTRIBUTE_ID 0x04BD    // Ver.: always
#define ZCL_TIER11_BLOCK15_PRICE_ATTRIBUTE_ID 0x04BE    // Ver.: always
#define ZCL_TIER11_BLOCK16_PRICE_ATTRIBUTE_ID 0x04BF    // Ver.: always
#define ZCL_TIER12_BLOCK1_PRICE_ATTRIBUTE_ID 0x04C0    // Ver.: always
#define ZCL_TIER12_BLOCK2_PRICE_ATTRIBUTE_ID 0x04C1    // Ver.: always
#define ZCL_TIER12_BLOCK3_PRICE_ATTRIBUTE_ID 0x04C2    // Ver.: always
#define ZCL_TIER12_BLOCK4_PRICE_ATTRIBUTE_ID 0x04C3    // Ver.: always
#define ZCL_TIER12_BLOCK5_PRICE_ATTRIBUTE_ID 0x04C4    // Ver.: always
#define ZCL_TIER12_BLOCK6_PRICE_ATTRIBUTE_ID 0x04C5    // Ver.: always
#define ZCL_TIER12_BLOCK7_PRICE_ATTRIBUTE_ID 0x04C6    // Ver.: always
#define ZCL_TIER12_BLOCK8_PRICE_ATTRIBUTE_ID 0x04C7    // Ver.: always
#define ZCL_TIER12_BLOCK9_PRICE_ATTRIBUTE_ID 0x04C8    // Ver.: always
#define ZCL_TIER12_BLOCK10_PRICE_ATTRIBUTE_ID 0x04C9    // Ver.: always
#define ZCL_TIER12_BLOCK11_PRICE_ATTRIBUTE_ID 0x04CA    // Ver.: always
#define ZCL_TIER12_BLOCK12_PRICE_ATTRIBUTE_ID 0x04CB    // Ver.: always
#define ZCL_TIER12_BLOCK13_PRICE_ATTRIBUTE_ID 0x04CC    // Ver.: always
#define ZCL_TIER12_BLOCK14_PRICE_ATTRIBUTE_ID 0x04CD    // Ver.: always
#define ZCL_TIER12_BLOCK15_PRICE_ATTRIBUTE_ID 0x04CE    // Ver.: always
#define ZCL_TIER12_BLOCK16_PRICE_ATTRIBUTE_ID 0x04CF    // Ver.: always
#define ZCL_TIER13_BLOCK1_PRICE_ATTRIBUTE_ID 0x04D0    // Ver.: always
#define ZCL_TIER13_BLOCK2_PRICE_ATTRIBUTE_ID 0x04D1    // Ver.: always
#define ZCL_TIER13_BLOCK3_PRICE_ATTRIBUTE_ID 0x04D2    // Ver.: always
#define ZCL_TIER13_BLOCK4_PRICE_ATTRIBUTE_ID 0x04D3    // Ver.: always
#define ZCL_TIER13_BLOCK5_PRICE_ATTRIBUTE_ID 0x04D4    // Ver.: always
#define ZCL_TIER13_BLOCK6_PRICE_ATTRIBUTE_ID 0x04D5    // Ver.: always
#define ZCL_TIER13_BLOCK7_PRICE_ATTRIBUTE_ID 0x04D6    // Ver.: always
#define ZCL_TIER13_BLOCK8_PRICE_ATTRIBUTE_ID 0x04D7    // Ver.: always
#define ZCL_TIER13_BLOCK9_PRICE_ATTRIBUTE_ID 0x04D8    // Ver.: always
#define ZCL_TIER13_BLOCK10_PRICE_ATTRIBUTE_ID 0x04D9    // Ver.: always
#define ZCL_TIER13_BLOCK11_PRICE_ATTRIBUTE_ID 0x04DA    // Ver.: always
#define ZCL_TIER13_BLOCK12_PRICE_ATTRIBUTE_ID 0x04DB    // Ver.: always
#define ZCL_TIER13_BLOCK13_PRICE_ATTRIBUTE_ID 0x04DC    // Ver.: always
#define ZCL_TIER13_BLOCK14_PRICE_ATTRIBUTE_ID 0x04DD    // Ver.: always
#define ZCL_TIER13_BLOCK15_PRICE_ATTRIBUTE_ID 0x04DE    // Ver.: always
#define ZCL_TIER13_BLOCK16_PRICE_ATTRIBUTE_ID 0x04DF    // Ver.: always
#define ZCL_TIER14_BLOCK1_PRICE_ATTRIBUTE_ID 0x04E0    // Ver.: always
#define ZCL_TIER14_BLOCK2_PRICE_ATTRIBUTE_ID 0x04E1    // Ver.: always
#define ZCL_TIER14_BLOCK3_PRICE_ATTRIBUTE_ID 0x04E2    // Ver.: always
#define ZCL_TIER14_BLOCK4_PRICE_ATTRIBUTE_ID 0x04E3    // Ver.: always
#define ZCL_TIER14_BLOCK5_PRICE_ATTRIBUTE_ID 0x04E4    // Ver.: always
#define ZCL_TIER14_BLOCK6_PRICE_ATTRIBUTE_ID 0x04E5    // Ver.: always
#define ZCL_TIER14_BLOCK7_PRICE_ATTRIBUTE_ID 0x04E6    // Ver.: always
#define ZCL_TIER14_BLOCK8_PRICE_ATTRIBUTE_ID 0x04E7    // Ver.: always
#define ZCL_TIER14_BLOCK9_PRICE_ATTRIBUTE_ID 0x04E8    // Ver.: always
#define ZCL_TIER14_BLOCK10_PRICE_ATTRIBUTE_ID 0x04E9    // Ver.: always
#define ZCL_TIER14_BLOCK11_PRICE_ATTRIBUTE_ID 0x04EA    // Ver.: always
#define ZCL_TIER14_BLOCK12_PRICE_ATTRIBUTE_ID 0x04EB    // Ver.: always
#define ZCL_TIER14_BLOCK13_PRICE_ATTRIBUTE_ID 0x04EC    // Ver.: always
#define ZCL_TIER14_BLOCK14_PRICE_ATTRIBUTE_ID 0x04ED    // Ver.: always
#define ZCL_TIER14_BLOCK15_PRICE_ATTRIBUTE_ID 0x04EE    // Ver.: always
#define ZCL_TIER14_BLOCK16_PRICE_ATTRIBUTE_ID 0x04EF    // Ver.: always
#define ZCL_TIER15_BLOCK1_PRICE_ATTRIBUTE_ID 0x04F0    // Ver.: always
#define ZCL_TIER15_BLOCK2_PRICE_ATTRIBUTE_ID 0x04F1    // Ver.: always
#define ZCL_TIER15_BLOCK3_PRICE_ATTRIBUTE_ID 0x04F2    // Ver.: always
#define ZCL_TIER15_BLOCK4_PRICE_ATTRIBUTE_ID 0x04F3    // Ver.: always
#define ZCL_TIER15_BLOCK5_PRICE_ATTRIBUTE_ID 0x04F4    // Ver.: always
#define ZCL_TIER15_BLOCK6_PRICE_ATTRIBUTE_ID 0x04F5    // Ver.: always
#define ZCL_TIER15_BLOCK7_PRICE_ATTRIBUTE_ID 0x04F6    // Ver.: always
#define ZCL_TIER15_BLOCK8_PRICE_ATTRIBUTE_ID 0x04F7    // Ver.: always
#define ZCL_TIER15_BLOCK9_PRICE_ATTRIBUTE_ID 0x04F8    // Ver.: always
#define ZCL_TIER15_BLOCK10_PRICE_ATTRIBUTE_ID 0x04F9    // Ver.: always
#define ZCL_TIER15_BLOCK11_PRICE_ATTRIBUTE_ID 0x04FA    // Ver.: always
#define ZCL_TIER15_BLOCK12_PRICE_ATTRIBUTE_ID 0x04FB    // Ver.: always
#define ZCL_TIER15_BLOCK13_PRICE_ATTRIBUTE_ID 0x04FC    // Ver.: always
#define ZCL_TIER15_BLOCK14_PRICE_ATTRIBUTE_ID 0x04FD    // Ver.: always
#define ZCL_TIER15_BLOCK15_PRICE_ATTRIBUTE_ID 0x04FE    // Ver.: always
#define ZCL_TIER15_BLOCK16_PRICE_ATTRIBUTE_ID 0x04FF    // Ver.: always


// Attribute types for cluster: Tunneling
// Cluster specification level: 1.1, 105638r09

// Server attributes
#define ZCL_CLOSE_TUNNEL_TIMEOUT_ATTRIBUTE_ID 0x0000    // Ver.: always


// Attribute types for cluster: Prepayment
// Cluster specification level: 1.1, 105638r09

// Server attributes
#define ZCL_PAYMENT_CONTROL_ATTRIBUTE_ID 0x0000    // Ver.: always
#define ZCL_CREDIT_REMAINING_ATTRIBUTE_ID 0x0001    // Ver.: always
#define ZCL_EMERGENCY_CREDIT_REMAINING_ATTRIBUTE_ID 0x0002    // Ver.: always
#define ZCL_CREDIT_STATUS_ATTRIBUTE_ID 0x0003    // Ver.: always
#define ZCL_TOP_UP_DATE_TIME_1_ATTRIBUTE_ID 0x0100    // Ver.: always
#define ZCL_TOP_UP_AMOUNT_1_ATTRIBUTE_ID 0x0101    // Ver.: always
#define ZCL_ORIGINATING_DEVICE_1_ATTRIBUTE_ID 0x0102    // Ver.: always
#define ZCL_TOP_UP_DATE_TIME_2_ATTRIBUTE_ID 0x0110    // Ver.: always
#define ZCL_TOP_UP_AMOUNT_2_ATTRIBUTE_ID 0x0111    // Ver.: always
#define ZCL_ORIGINATING_DEVICE_2_ATTRIBUTE_ID 0x0112    // Ver.: always
#define ZCL_TOP_UP_DATE_TIME_3_ATTRIBUTE_ID 0x0120    // Ver.: always
#define ZCL_TOP_UP_AMOUNT_3_ATTRIBUTE_ID 0x0121    // Ver.: always
#define ZCL_ORIGINATING_DEVICE_3_ATTRIBUTE_ID 0x0122    // Ver.: always
#define ZCL_TOP_UP_DATE_TIME_4_ATTRIBUTE_ID 0x0130    // Ver.: always
#define ZCL_TOP_UP_AMOUNT_4_ATTRIBUTE_ID 0x0131    // Ver.: always
#define ZCL_ORIGINATING_DEVICE_4_ATTRIBUTE_ID 0x0132    // Ver.: always
#define ZCL_TOP_UP_DATE_TIME_5_ATTRIBUTE_ID 0x0140    // Ver.: always
#define ZCL_TOP_UP_AMOUNT_5_ATTRIBUTE_ID 0x0141    // Ver.: always
#define ZCL_ORIGINATING_DEVICE_5_ATTRIBUTE_ID 0x0142    // Ver.: always
#define ZCL_FUEL_DEBT_REMAINING_ATTRIBUTE_ID 0x0200    // Ver.: always
#define ZCL_FUEL_DEBT_RECOVERY_RATE_ATTRIBUTE_ID 0x0201    // Ver.: always
#define ZCL_FUEL_DEBT_RECOVERY_PERIOD_ATTRIBUTE_ID 0x0202    // Ver.: always
#define ZCL_NON_FUEL_DEBT_REMAINING_ATTRIBUTE_ID 0x0203    // Ver.: always
#define ZCL_NON_FUEL_DEBT_RECOVERY_RATE_ATTRIBUTE_ID 0x0204    // Ver.: always
#define ZCL_NON_FUEL_DEBT_RECOVERY_PERIOD_ATTRIBUTE_ID 0x0205    // Ver.: always
#define ZCL_PROPOSED_CHANGE_PROVIDER_ID_ATTRIBUTE_ID 0x0300    // Ver.: always
#define ZCL_PROPOSED_CHANGE_IMPLEMENTATION_TIME_ATTRIBUTE_ID 0x0301    // Ver.: always
#define ZCL_PROPOSED_CHANGE_SUPPLY_STATUS_ATTRIBUTE_ID 0x0302    // Ver.: always
#define ZCL_DELAYED_SUPPLY_INTERRUPT_VALUE_REMAINING_ATTRIBUTE_ID 0x0303    // Ver.: always
#define ZCL_DELAYED_SUPPLY_INTERRUPT_VALUE_TYPE_ATTRIBUTE_ID 0x0304    // Ver.: always


// Attribute types for cluster: Key establishment
// Cluster specification level: 1.1, 105638r09

// Client attributes
#define ZCL_KEY_ESTABLISHMENT_SUITE_CLIENT_ATTRIBUTE_ID 0x0000    // Ver.: always

// Server attributes
#define ZCL_KEY_ESTABLISHMENT_SUITE_SERVER_ATTRIBUTE_ID 0x0000    // Ver.: always


// Attribute types for cluster: Sample Mfg Specific Cluster
// Cluster specification level: UNKNOWN

// Server attributes
#define ZCL_ATTRIBUTE_ONE_ATTRIBUTE_ID 0x0000    // Ver.: always


#endif // __EMBER_AF_ATTRIBUTE_ID__
