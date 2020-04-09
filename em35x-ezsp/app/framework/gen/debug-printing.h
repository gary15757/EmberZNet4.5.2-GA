// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generateDebugPrinting()
//

// Printing macros for cluster: Basic
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_BASIC_CLUSTER)
#define emberAfBasicClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_BASIC_CLUSTER, __VA_ARGS__)
#define emberAfBasicClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_BASIC_CLUSTER,  __VA_ARGS__)
#define emberAfBasicClusterFlush() emberAfFlush(EMBER_AF_PRINT_BASIC_CLUSTER)
#define emberAfBasicClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_BASIC_CLUSTER) ) { x; }
#define emberAfBasicClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_BASIC_CLUSTER, (buffer), (len), (withSpace))
#define emberAfBasicClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_BASIC_CLUSTER, (buffer))
#else
#define emberAfBasicClusterPrint(...)
#define emberAfBasicClusterPrintln(...)
#define emberAfBasicClusterFlush()
#define emberAfBasicClusterDebugExec(x)
#define emberAfBasicClusterPrintBuffer(buffer, len, withSpace)
#define emberAfBasicClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_BASIC_CLUSTER)


// Printing macros for cluster: Power Configuration
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_POWER_CONFIG_CLUSTER)
#define emberAfPowerConfigClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_POWER_CONFIG_CLUSTER, __VA_ARGS__)
#define emberAfPowerConfigClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_POWER_CONFIG_CLUSTER,  __VA_ARGS__)
#define emberAfPowerConfigClusterFlush() emberAfFlush(EMBER_AF_PRINT_POWER_CONFIG_CLUSTER)
#define emberAfPowerConfigClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_POWER_CONFIG_CLUSTER) ) { x; }
#define emberAfPowerConfigClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_POWER_CONFIG_CLUSTER, (buffer), (len), (withSpace))
#define emberAfPowerConfigClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_POWER_CONFIG_CLUSTER, (buffer))
#else
#define emberAfPowerConfigClusterPrint(...)
#define emberAfPowerConfigClusterPrintln(...)
#define emberAfPowerConfigClusterFlush()
#define emberAfPowerConfigClusterDebugExec(x)
#define emberAfPowerConfigClusterPrintBuffer(buffer, len, withSpace)
#define emberAfPowerConfigClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_POWER_CONFIG_CLUSTER)


// Printing macros for cluster: Device Temperature Configuration
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DEVICE_TEMP_CLUSTER)
#define emberAfDeviceTempClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_DEVICE_TEMP_CLUSTER, __VA_ARGS__)
#define emberAfDeviceTempClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_DEVICE_TEMP_CLUSTER,  __VA_ARGS__)
#define emberAfDeviceTempClusterFlush() emberAfFlush(EMBER_AF_PRINT_DEVICE_TEMP_CLUSTER)
#define emberAfDeviceTempClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_DEVICE_TEMP_CLUSTER) ) { x; }
#define emberAfDeviceTempClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_DEVICE_TEMP_CLUSTER, (buffer), (len), (withSpace))
#define emberAfDeviceTempClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_DEVICE_TEMP_CLUSTER, (buffer))
#else
#define emberAfDeviceTempClusterPrint(...)
#define emberAfDeviceTempClusterPrintln(...)
#define emberAfDeviceTempClusterFlush()
#define emberAfDeviceTempClusterDebugExec(x)
#define emberAfDeviceTempClusterPrintBuffer(buffer, len, withSpace)
#define emberAfDeviceTempClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DEVICE_TEMP_CLUSTER)


// Printing macros for cluster: Identify
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IDENTIFY_CLUSTER)
#define emberAfIdentifyClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_IDENTIFY_CLUSTER, __VA_ARGS__)
#define emberAfIdentifyClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_IDENTIFY_CLUSTER,  __VA_ARGS__)
#define emberAfIdentifyClusterFlush() emberAfFlush(EMBER_AF_PRINT_IDENTIFY_CLUSTER)
#define emberAfIdentifyClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_IDENTIFY_CLUSTER) ) { x; }
#define emberAfIdentifyClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_IDENTIFY_CLUSTER, (buffer), (len), (withSpace))
#define emberAfIdentifyClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_IDENTIFY_CLUSTER, (buffer))
#else
#define emberAfIdentifyClusterPrint(...)
#define emberAfIdentifyClusterPrintln(...)
#define emberAfIdentifyClusterFlush()
#define emberAfIdentifyClusterDebugExec(x)
#define emberAfIdentifyClusterPrintBuffer(buffer, len, withSpace)
#define emberAfIdentifyClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IDENTIFY_CLUSTER)


// Printing macros for cluster: Groups
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_GROUPS_CLUSTER)
#define emberAfGroupsClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_GROUPS_CLUSTER, __VA_ARGS__)
#define emberAfGroupsClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_GROUPS_CLUSTER,  __VA_ARGS__)
#define emberAfGroupsClusterFlush() emberAfFlush(EMBER_AF_PRINT_GROUPS_CLUSTER)
#define emberAfGroupsClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_GROUPS_CLUSTER) ) { x; }
#define emberAfGroupsClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_GROUPS_CLUSTER, (buffer), (len), (withSpace))
#define emberAfGroupsClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_GROUPS_CLUSTER, (buffer))
#else
#define emberAfGroupsClusterPrint(...)
#define emberAfGroupsClusterPrintln(...)
#define emberAfGroupsClusterFlush()
#define emberAfGroupsClusterDebugExec(x)
#define emberAfGroupsClusterPrintBuffer(buffer, len, withSpace)
#define emberAfGroupsClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_GROUPS_CLUSTER)


// Printing macros for cluster: Scenes
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SCENES_CLUSTER)
#define emberAfScenesClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_SCENES_CLUSTER, __VA_ARGS__)
#define emberAfScenesClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_SCENES_CLUSTER,  __VA_ARGS__)
#define emberAfScenesClusterFlush() emberAfFlush(EMBER_AF_PRINT_SCENES_CLUSTER)
#define emberAfScenesClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_SCENES_CLUSTER) ) { x; }
#define emberAfScenesClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_SCENES_CLUSTER, (buffer), (len), (withSpace))
#define emberAfScenesClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_SCENES_CLUSTER, (buffer))
#else
#define emberAfScenesClusterPrint(...)
#define emberAfScenesClusterPrintln(...)
#define emberAfScenesClusterFlush()
#define emberAfScenesClusterDebugExec(x)
#define emberAfScenesClusterPrintBuffer(buffer, len, withSpace)
#define emberAfScenesClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SCENES_CLUSTER)


// Printing macros for cluster: On/off
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ON_OFF_CLUSTER)
#define emberAfOnOffClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_ON_OFF_CLUSTER, __VA_ARGS__)
#define emberAfOnOffClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_ON_OFF_CLUSTER,  __VA_ARGS__)
#define emberAfOnOffClusterFlush() emberAfFlush(EMBER_AF_PRINT_ON_OFF_CLUSTER)
#define emberAfOnOffClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_ON_OFF_CLUSTER) ) { x; }
#define emberAfOnOffClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_ON_OFF_CLUSTER, (buffer), (len), (withSpace))
#define emberAfOnOffClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_ON_OFF_CLUSTER, (buffer))
#else
#define emberAfOnOffClusterPrint(...)
#define emberAfOnOffClusterPrintln(...)
#define emberAfOnOffClusterFlush()
#define emberAfOnOffClusterDebugExec(x)
#define emberAfOnOffClusterPrintBuffer(buffer, len, withSpace)
#define emberAfOnOffClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ON_OFF_CLUSTER)


// Printing macros for cluster: On/off Switch Configuration
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ON_OFF_SWITCH_CONFIG_CLUSTER)
#define emberAfOnOffSwitchConfigClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_ON_OFF_SWITCH_CONFIG_CLUSTER, __VA_ARGS__)
#define emberAfOnOffSwitchConfigClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_ON_OFF_SWITCH_CONFIG_CLUSTER,  __VA_ARGS__)
#define emberAfOnOffSwitchConfigClusterFlush() emberAfFlush(EMBER_AF_PRINT_ON_OFF_SWITCH_CONFIG_CLUSTER)
#define emberAfOnOffSwitchConfigClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_ON_OFF_SWITCH_CONFIG_CLUSTER) ) { x; }
#define emberAfOnOffSwitchConfigClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_ON_OFF_SWITCH_CONFIG_CLUSTER, (buffer), (len), (withSpace))
#define emberAfOnOffSwitchConfigClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_ON_OFF_SWITCH_CONFIG_CLUSTER, (buffer))
#else
#define emberAfOnOffSwitchConfigClusterPrint(...)
#define emberAfOnOffSwitchConfigClusterPrintln(...)
#define emberAfOnOffSwitchConfigClusterFlush()
#define emberAfOnOffSwitchConfigClusterDebugExec(x)
#define emberAfOnOffSwitchConfigClusterPrintBuffer(buffer, len, withSpace)
#define emberAfOnOffSwitchConfigClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ON_OFF_SWITCH_CONFIG_CLUSTER)


// Printing macros for cluster: Level Control
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_LEVEL_CONTROL_CLUSTER)
#define emberAfLevelControlClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_LEVEL_CONTROL_CLUSTER, __VA_ARGS__)
#define emberAfLevelControlClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_LEVEL_CONTROL_CLUSTER,  __VA_ARGS__)
#define emberAfLevelControlClusterFlush() emberAfFlush(EMBER_AF_PRINT_LEVEL_CONTROL_CLUSTER)
#define emberAfLevelControlClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_LEVEL_CONTROL_CLUSTER) ) { x; }
#define emberAfLevelControlClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_LEVEL_CONTROL_CLUSTER, (buffer), (len), (withSpace))
#define emberAfLevelControlClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_LEVEL_CONTROL_CLUSTER, (buffer))
#else
#define emberAfLevelControlClusterPrint(...)
#define emberAfLevelControlClusterPrintln(...)
#define emberAfLevelControlClusterFlush()
#define emberAfLevelControlClusterDebugExec(x)
#define emberAfLevelControlClusterPrintBuffer(buffer, len, withSpace)
#define emberAfLevelControlClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_LEVEL_CONTROL_CLUSTER)


// Printing macros for cluster: Alarms
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ALARM_CLUSTER)
#define emberAfAlarmClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_ALARM_CLUSTER, __VA_ARGS__)
#define emberAfAlarmClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_ALARM_CLUSTER,  __VA_ARGS__)
#define emberAfAlarmClusterFlush() emberAfFlush(EMBER_AF_PRINT_ALARM_CLUSTER)
#define emberAfAlarmClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_ALARM_CLUSTER) ) { x; }
#define emberAfAlarmClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_ALARM_CLUSTER, (buffer), (len), (withSpace))
#define emberAfAlarmClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_ALARM_CLUSTER, (buffer))
#else
#define emberAfAlarmClusterPrint(...)
#define emberAfAlarmClusterPrintln(...)
#define emberAfAlarmClusterFlush()
#define emberAfAlarmClusterDebugExec(x)
#define emberAfAlarmClusterPrintBuffer(buffer, len, withSpace)
#define emberAfAlarmClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ALARM_CLUSTER)


// Printing macros for cluster: Time
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_TIME_CLUSTER)
#define emberAfTimeClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_TIME_CLUSTER, __VA_ARGS__)
#define emberAfTimeClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_TIME_CLUSTER,  __VA_ARGS__)
#define emberAfTimeClusterFlush() emberAfFlush(EMBER_AF_PRINT_TIME_CLUSTER)
#define emberAfTimeClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_TIME_CLUSTER) ) { x; }
#define emberAfTimeClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_TIME_CLUSTER, (buffer), (len), (withSpace))
#define emberAfTimeClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_TIME_CLUSTER, (buffer))
#else
#define emberAfTimeClusterPrint(...)
#define emberAfTimeClusterPrintln(...)
#define emberAfTimeClusterFlush()
#define emberAfTimeClusterDebugExec(x)
#define emberAfTimeClusterPrintBuffer(buffer, len, withSpace)
#define emberAfTimeClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_TIME_CLUSTER)


// Printing macros for cluster: RSSI Location
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_RSSI_LOCATION_CLUSTER)
#define emberAfRssiLocationClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_RSSI_LOCATION_CLUSTER, __VA_ARGS__)
#define emberAfRssiLocationClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_RSSI_LOCATION_CLUSTER,  __VA_ARGS__)
#define emberAfRssiLocationClusterFlush() emberAfFlush(EMBER_AF_PRINT_RSSI_LOCATION_CLUSTER)
#define emberAfRssiLocationClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_RSSI_LOCATION_CLUSTER) ) { x; }
#define emberAfRssiLocationClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_RSSI_LOCATION_CLUSTER, (buffer), (len), (withSpace))
#define emberAfRssiLocationClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_RSSI_LOCATION_CLUSTER, (buffer))
#else
#define emberAfRssiLocationClusterPrint(...)
#define emberAfRssiLocationClusterPrintln(...)
#define emberAfRssiLocationClusterFlush()
#define emberAfRssiLocationClusterDebugExec(x)
#define emberAfRssiLocationClusterPrintBuffer(buffer, len, withSpace)
#define emberAfRssiLocationClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_RSSI_LOCATION_CLUSTER)


// Printing macros for cluster: Binary Input (Basic)
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_BINARY_INPUT_BASIC_CLUSTER)
#define emberAfBinaryInputBasicClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_BINARY_INPUT_BASIC_CLUSTER, __VA_ARGS__)
#define emberAfBinaryInputBasicClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_BINARY_INPUT_BASIC_CLUSTER,  __VA_ARGS__)
#define emberAfBinaryInputBasicClusterFlush() emberAfFlush(EMBER_AF_PRINT_BINARY_INPUT_BASIC_CLUSTER)
#define emberAfBinaryInputBasicClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_BINARY_INPUT_BASIC_CLUSTER) ) { x; }
#define emberAfBinaryInputBasicClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_BINARY_INPUT_BASIC_CLUSTER, (buffer), (len), (withSpace))
#define emberAfBinaryInputBasicClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_BINARY_INPUT_BASIC_CLUSTER, (buffer))
#else
#define emberAfBinaryInputBasicClusterPrint(...)
#define emberAfBinaryInputBasicClusterPrintln(...)
#define emberAfBinaryInputBasicClusterFlush()
#define emberAfBinaryInputBasicClusterDebugExec(x)
#define emberAfBinaryInputBasicClusterPrintBuffer(buffer, len, withSpace)
#define emberAfBinaryInputBasicClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_BINARY_INPUT_BASIC_CLUSTER)


// Printing macros for cluster: Commissioning
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_COMMISSIONING_CLUSTER)
#define emberAfCommissioningClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_COMMISSIONING_CLUSTER, __VA_ARGS__)
#define emberAfCommissioningClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_COMMISSIONING_CLUSTER,  __VA_ARGS__)
#define emberAfCommissioningClusterFlush() emberAfFlush(EMBER_AF_PRINT_COMMISSIONING_CLUSTER)
#define emberAfCommissioningClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_COMMISSIONING_CLUSTER) ) { x; }
#define emberAfCommissioningClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_COMMISSIONING_CLUSTER, (buffer), (len), (withSpace))
#define emberAfCommissioningClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_COMMISSIONING_CLUSTER, (buffer))
#else
#define emberAfCommissioningClusterPrint(...)
#define emberAfCommissioningClusterPrintln(...)
#define emberAfCommissioningClusterFlush()
#define emberAfCommissioningClusterDebugExec(x)
#define emberAfCommissioningClusterPrintBuffer(buffer, len, withSpace)
#define emberAfCommissioningClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_COMMISSIONING_CLUSTER)


// Printing macros for cluster: Shade Configuration
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SHADE_CONFIG_CLUSTER)
#define emberAfShadeConfigClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_SHADE_CONFIG_CLUSTER, __VA_ARGS__)
#define emberAfShadeConfigClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_SHADE_CONFIG_CLUSTER,  __VA_ARGS__)
#define emberAfShadeConfigClusterFlush() emberAfFlush(EMBER_AF_PRINT_SHADE_CONFIG_CLUSTER)
#define emberAfShadeConfigClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_SHADE_CONFIG_CLUSTER) ) { x; }
#define emberAfShadeConfigClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_SHADE_CONFIG_CLUSTER, (buffer), (len), (withSpace))
#define emberAfShadeConfigClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_SHADE_CONFIG_CLUSTER, (buffer))
#else
#define emberAfShadeConfigClusterPrint(...)
#define emberAfShadeConfigClusterPrintln(...)
#define emberAfShadeConfigClusterFlush()
#define emberAfShadeConfigClusterDebugExec(x)
#define emberAfShadeConfigClusterPrintBuffer(buffer, len, withSpace)
#define emberAfShadeConfigClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SHADE_CONFIG_CLUSTER)


// Printing macros for cluster: Pump Configuration and Control
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_PUMP_CONFIG_CONTROL_CLUSTER)
#define emberAfPumpConfigControlClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_PUMP_CONFIG_CONTROL_CLUSTER, __VA_ARGS__)
#define emberAfPumpConfigControlClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_PUMP_CONFIG_CONTROL_CLUSTER,  __VA_ARGS__)
#define emberAfPumpConfigControlClusterFlush() emberAfFlush(EMBER_AF_PRINT_PUMP_CONFIG_CONTROL_CLUSTER)
#define emberAfPumpConfigControlClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_PUMP_CONFIG_CONTROL_CLUSTER) ) { x; }
#define emberAfPumpConfigControlClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_PUMP_CONFIG_CONTROL_CLUSTER, (buffer), (len), (withSpace))
#define emberAfPumpConfigControlClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_PUMP_CONFIG_CONTROL_CLUSTER, (buffer))
#else
#define emberAfPumpConfigControlClusterPrint(...)
#define emberAfPumpConfigControlClusterPrintln(...)
#define emberAfPumpConfigControlClusterFlush()
#define emberAfPumpConfigControlClusterDebugExec(x)
#define emberAfPumpConfigControlClusterPrintBuffer(buffer, len, withSpace)
#define emberAfPumpConfigControlClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_PUMP_CONFIG_CONTROL_CLUSTER)


// Printing macros for cluster: Thermostat
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_THERMOSTAT_CLUSTER)
#define emberAfThermostatClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_THERMOSTAT_CLUSTER, __VA_ARGS__)
#define emberAfThermostatClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_THERMOSTAT_CLUSTER,  __VA_ARGS__)
#define emberAfThermostatClusterFlush() emberAfFlush(EMBER_AF_PRINT_THERMOSTAT_CLUSTER)
#define emberAfThermostatClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_THERMOSTAT_CLUSTER) ) { x; }
#define emberAfThermostatClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_THERMOSTAT_CLUSTER, (buffer), (len), (withSpace))
#define emberAfThermostatClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_THERMOSTAT_CLUSTER, (buffer))
#else
#define emberAfThermostatClusterPrint(...)
#define emberAfThermostatClusterPrintln(...)
#define emberAfThermostatClusterFlush()
#define emberAfThermostatClusterDebugExec(x)
#define emberAfThermostatClusterPrintBuffer(buffer, len, withSpace)
#define emberAfThermostatClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_THERMOSTAT_CLUSTER)


// Printing macros for cluster: Fan Control
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_FAN_CONTROL_CLUSTER)
#define emberAfFanControlClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_FAN_CONTROL_CLUSTER, __VA_ARGS__)
#define emberAfFanControlClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_FAN_CONTROL_CLUSTER,  __VA_ARGS__)
#define emberAfFanControlClusterFlush() emberAfFlush(EMBER_AF_PRINT_FAN_CONTROL_CLUSTER)
#define emberAfFanControlClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_FAN_CONTROL_CLUSTER) ) { x; }
#define emberAfFanControlClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_FAN_CONTROL_CLUSTER, (buffer), (len), (withSpace))
#define emberAfFanControlClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_FAN_CONTROL_CLUSTER, (buffer))
#else
#define emberAfFanControlClusterPrint(...)
#define emberAfFanControlClusterPrintln(...)
#define emberAfFanControlClusterFlush()
#define emberAfFanControlClusterDebugExec(x)
#define emberAfFanControlClusterPrintBuffer(buffer, len, withSpace)
#define emberAfFanControlClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_FAN_CONTROL_CLUSTER)


// Printing macros for cluster: Dehumidification Control
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DEHUMID_CONTROL_CLUSTER)
#define emberAfDehumidControlClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_DEHUMID_CONTROL_CLUSTER, __VA_ARGS__)
#define emberAfDehumidControlClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_DEHUMID_CONTROL_CLUSTER,  __VA_ARGS__)
#define emberAfDehumidControlClusterFlush() emberAfFlush(EMBER_AF_PRINT_DEHUMID_CONTROL_CLUSTER)
#define emberAfDehumidControlClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_DEHUMID_CONTROL_CLUSTER) ) { x; }
#define emberAfDehumidControlClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_DEHUMID_CONTROL_CLUSTER, (buffer), (len), (withSpace))
#define emberAfDehumidControlClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_DEHUMID_CONTROL_CLUSTER, (buffer))
#else
#define emberAfDehumidControlClusterPrint(...)
#define emberAfDehumidControlClusterPrintln(...)
#define emberAfDehumidControlClusterFlush()
#define emberAfDehumidControlClusterDebugExec(x)
#define emberAfDehumidControlClusterPrintBuffer(buffer, len, withSpace)
#define emberAfDehumidControlClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DEHUMID_CONTROL_CLUSTER)


// Printing macros for cluster: Thermostat User Interface Configuration
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_THERMOSTAT_UI_CONFIG_CLUSTER)
#define emberAfThermostatUiConfigClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_THERMOSTAT_UI_CONFIG_CLUSTER, __VA_ARGS__)
#define emberAfThermostatUiConfigClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_THERMOSTAT_UI_CONFIG_CLUSTER,  __VA_ARGS__)
#define emberAfThermostatUiConfigClusterFlush() emberAfFlush(EMBER_AF_PRINT_THERMOSTAT_UI_CONFIG_CLUSTER)
#define emberAfThermostatUiConfigClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_THERMOSTAT_UI_CONFIG_CLUSTER) ) { x; }
#define emberAfThermostatUiConfigClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_THERMOSTAT_UI_CONFIG_CLUSTER, (buffer), (len), (withSpace))
#define emberAfThermostatUiConfigClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_THERMOSTAT_UI_CONFIG_CLUSTER, (buffer))
#else
#define emberAfThermostatUiConfigClusterPrint(...)
#define emberAfThermostatUiConfigClusterPrintln(...)
#define emberAfThermostatUiConfigClusterFlush()
#define emberAfThermostatUiConfigClusterDebugExec(x)
#define emberAfThermostatUiConfigClusterPrintBuffer(buffer, len, withSpace)
#define emberAfThermostatUiConfigClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_THERMOSTAT_UI_CONFIG_CLUSTER)


// Printing macros for cluster: Color Control
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_COLOR_CONTROL_CLUSTER)
#define emberAfColorControlClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_COLOR_CONTROL_CLUSTER, __VA_ARGS__)
#define emberAfColorControlClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_COLOR_CONTROL_CLUSTER,  __VA_ARGS__)
#define emberAfColorControlClusterFlush() emberAfFlush(EMBER_AF_PRINT_COLOR_CONTROL_CLUSTER)
#define emberAfColorControlClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_COLOR_CONTROL_CLUSTER) ) { x; }
#define emberAfColorControlClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_COLOR_CONTROL_CLUSTER, (buffer), (len), (withSpace))
#define emberAfColorControlClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_COLOR_CONTROL_CLUSTER, (buffer))
#else
#define emberAfColorControlClusterPrint(...)
#define emberAfColorControlClusterPrintln(...)
#define emberAfColorControlClusterFlush()
#define emberAfColorControlClusterDebugExec(x)
#define emberAfColorControlClusterPrintBuffer(buffer, len, withSpace)
#define emberAfColorControlClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_COLOR_CONTROL_CLUSTER)


// Printing macros for cluster: Ballast Configuration
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_BALLAST_CONFIGURATION_CLUSTER)
#define emberAfBallastConfigurationClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_BALLAST_CONFIGURATION_CLUSTER, __VA_ARGS__)
#define emberAfBallastConfigurationClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_BALLAST_CONFIGURATION_CLUSTER,  __VA_ARGS__)
#define emberAfBallastConfigurationClusterFlush() emberAfFlush(EMBER_AF_PRINT_BALLAST_CONFIGURATION_CLUSTER)
#define emberAfBallastConfigurationClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_BALLAST_CONFIGURATION_CLUSTER) ) { x; }
#define emberAfBallastConfigurationClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_BALLAST_CONFIGURATION_CLUSTER, (buffer), (len), (withSpace))
#define emberAfBallastConfigurationClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_BALLAST_CONFIGURATION_CLUSTER, (buffer))
#else
#define emberAfBallastConfigurationClusterPrint(...)
#define emberAfBallastConfigurationClusterPrintln(...)
#define emberAfBallastConfigurationClusterFlush()
#define emberAfBallastConfigurationClusterDebugExec(x)
#define emberAfBallastConfigurationClusterPrintBuffer(buffer, len, withSpace)
#define emberAfBallastConfigurationClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_BALLAST_CONFIGURATION_CLUSTER)


// Printing macros for cluster: Illuminance Measurement
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ILLUM_MEASUREMENT_CLUSTER)
#define emberAfIllumMeasurementClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_ILLUM_MEASUREMENT_CLUSTER, __VA_ARGS__)
#define emberAfIllumMeasurementClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_ILLUM_MEASUREMENT_CLUSTER,  __VA_ARGS__)
#define emberAfIllumMeasurementClusterFlush() emberAfFlush(EMBER_AF_PRINT_ILLUM_MEASUREMENT_CLUSTER)
#define emberAfIllumMeasurementClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_ILLUM_MEASUREMENT_CLUSTER) ) { x; }
#define emberAfIllumMeasurementClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_ILLUM_MEASUREMENT_CLUSTER, (buffer), (len), (withSpace))
#define emberAfIllumMeasurementClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_ILLUM_MEASUREMENT_CLUSTER, (buffer))
#else
#define emberAfIllumMeasurementClusterPrint(...)
#define emberAfIllumMeasurementClusterPrintln(...)
#define emberAfIllumMeasurementClusterFlush()
#define emberAfIllumMeasurementClusterDebugExec(x)
#define emberAfIllumMeasurementClusterPrintBuffer(buffer, len, withSpace)
#define emberAfIllumMeasurementClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ILLUM_MEASUREMENT_CLUSTER)


// Printing macros for cluster: Illuminance Level Sensing
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ILLUM_LEVEL_SENSING_CLUSTER)
#define emberAfIllumLevelSensingClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_ILLUM_LEVEL_SENSING_CLUSTER, __VA_ARGS__)
#define emberAfIllumLevelSensingClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_ILLUM_LEVEL_SENSING_CLUSTER,  __VA_ARGS__)
#define emberAfIllumLevelSensingClusterFlush() emberAfFlush(EMBER_AF_PRINT_ILLUM_LEVEL_SENSING_CLUSTER)
#define emberAfIllumLevelSensingClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_ILLUM_LEVEL_SENSING_CLUSTER) ) { x; }
#define emberAfIllumLevelSensingClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_ILLUM_LEVEL_SENSING_CLUSTER, (buffer), (len), (withSpace))
#define emberAfIllumLevelSensingClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_ILLUM_LEVEL_SENSING_CLUSTER, (buffer))
#else
#define emberAfIllumLevelSensingClusterPrint(...)
#define emberAfIllumLevelSensingClusterPrintln(...)
#define emberAfIllumLevelSensingClusterFlush()
#define emberAfIllumLevelSensingClusterDebugExec(x)
#define emberAfIllumLevelSensingClusterPrintBuffer(buffer, len, withSpace)
#define emberAfIllumLevelSensingClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ILLUM_LEVEL_SENSING_CLUSTER)


// Printing macros for cluster: Temperature Measurement
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_TEMP_MEASUREMENT_CLUSTER)
#define emberAfTempMeasurementClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_TEMP_MEASUREMENT_CLUSTER, __VA_ARGS__)
#define emberAfTempMeasurementClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_TEMP_MEASUREMENT_CLUSTER,  __VA_ARGS__)
#define emberAfTempMeasurementClusterFlush() emberAfFlush(EMBER_AF_PRINT_TEMP_MEASUREMENT_CLUSTER)
#define emberAfTempMeasurementClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_TEMP_MEASUREMENT_CLUSTER) ) { x; }
#define emberAfTempMeasurementClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_TEMP_MEASUREMENT_CLUSTER, (buffer), (len), (withSpace))
#define emberAfTempMeasurementClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_TEMP_MEASUREMENT_CLUSTER, (buffer))
#else
#define emberAfTempMeasurementClusterPrint(...)
#define emberAfTempMeasurementClusterPrintln(...)
#define emberAfTempMeasurementClusterFlush()
#define emberAfTempMeasurementClusterDebugExec(x)
#define emberAfTempMeasurementClusterPrintBuffer(buffer, len, withSpace)
#define emberAfTempMeasurementClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_TEMP_MEASUREMENT_CLUSTER)


// Printing macros for cluster: Pressure Measurement
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_PRESSURE_MEASUREMENT_CLUSTER)
#define emberAfPressureMeasurementClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_PRESSURE_MEASUREMENT_CLUSTER, __VA_ARGS__)
#define emberAfPressureMeasurementClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_PRESSURE_MEASUREMENT_CLUSTER,  __VA_ARGS__)
#define emberAfPressureMeasurementClusterFlush() emberAfFlush(EMBER_AF_PRINT_PRESSURE_MEASUREMENT_CLUSTER)
#define emberAfPressureMeasurementClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_PRESSURE_MEASUREMENT_CLUSTER) ) { x; }
#define emberAfPressureMeasurementClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_PRESSURE_MEASUREMENT_CLUSTER, (buffer), (len), (withSpace))
#define emberAfPressureMeasurementClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_PRESSURE_MEASUREMENT_CLUSTER, (buffer))
#else
#define emberAfPressureMeasurementClusterPrint(...)
#define emberAfPressureMeasurementClusterPrintln(...)
#define emberAfPressureMeasurementClusterFlush()
#define emberAfPressureMeasurementClusterDebugExec(x)
#define emberAfPressureMeasurementClusterPrintBuffer(buffer, len, withSpace)
#define emberAfPressureMeasurementClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_PRESSURE_MEASUREMENT_CLUSTER)


// Printing macros for cluster: Flow Measurement
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_FLOW_MEASUREMENT_CLUSTER)
#define emberAfFlowMeasurementClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_FLOW_MEASUREMENT_CLUSTER, __VA_ARGS__)
#define emberAfFlowMeasurementClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_FLOW_MEASUREMENT_CLUSTER,  __VA_ARGS__)
#define emberAfFlowMeasurementClusterFlush() emberAfFlush(EMBER_AF_PRINT_FLOW_MEASUREMENT_CLUSTER)
#define emberAfFlowMeasurementClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_FLOW_MEASUREMENT_CLUSTER) ) { x; }
#define emberAfFlowMeasurementClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_FLOW_MEASUREMENT_CLUSTER, (buffer), (len), (withSpace))
#define emberAfFlowMeasurementClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_FLOW_MEASUREMENT_CLUSTER, (buffer))
#else
#define emberAfFlowMeasurementClusterPrint(...)
#define emberAfFlowMeasurementClusterPrintln(...)
#define emberAfFlowMeasurementClusterFlush()
#define emberAfFlowMeasurementClusterDebugExec(x)
#define emberAfFlowMeasurementClusterPrintBuffer(buffer, len, withSpace)
#define emberAfFlowMeasurementClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_FLOW_MEASUREMENT_CLUSTER)


// Printing macros for cluster: Relative Humidity Measurement
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER)
#define emberAfRelativeHumidityMeasurementClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER, __VA_ARGS__)
#define emberAfRelativeHumidityMeasurementClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER,  __VA_ARGS__)
#define emberAfRelativeHumidityMeasurementClusterFlush() emberAfFlush(EMBER_AF_PRINT_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER)
#define emberAfRelativeHumidityMeasurementClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER) ) { x; }
#define emberAfRelativeHumidityMeasurementClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER, (buffer), (len), (withSpace))
#define emberAfRelativeHumidityMeasurementClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER, (buffer))
#else
#define emberAfRelativeHumidityMeasurementClusterPrint(...)
#define emberAfRelativeHumidityMeasurementClusterPrintln(...)
#define emberAfRelativeHumidityMeasurementClusterFlush()
#define emberAfRelativeHumidityMeasurementClusterDebugExec(x)
#define emberAfRelativeHumidityMeasurementClusterPrintBuffer(buffer, len, withSpace)
#define emberAfRelativeHumidityMeasurementClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER)


// Printing macros for cluster: Occupancy Sensing
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_OCCUPANCY_SENSING_CLUSTER)
#define emberAfOccupancySensingClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_OCCUPANCY_SENSING_CLUSTER, __VA_ARGS__)
#define emberAfOccupancySensingClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_OCCUPANCY_SENSING_CLUSTER,  __VA_ARGS__)
#define emberAfOccupancySensingClusterFlush() emberAfFlush(EMBER_AF_PRINT_OCCUPANCY_SENSING_CLUSTER)
#define emberAfOccupancySensingClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_OCCUPANCY_SENSING_CLUSTER) ) { x; }
#define emberAfOccupancySensingClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_OCCUPANCY_SENSING_CLUSTER, (buffer), (len), (withSpace))
#define emberAfOccupancySensingClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_OCCUPANCY_SENSING_CLUSTER, (buffer))
#else
#define emberAfOccupancySensingClusterPrint(...)
#define emberAfOccupancySensingClusterPrintln(...)
#define emberAfOccupancySensingClusterFlush()
#define emberAfOccupancySensingClusterDebugExec(x)
#define emberAfOccupancySensingClusterPrintBuffer(buffer, len, withSpace)
#define emberAfOccupancySensingClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_OCCUPANCY_SENSING_CLUSTER)


// Printing macros for cluster: IAS Zone
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IAS_ZONE_CLUSTER)
#define emberAfIasZoneClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_IAS_ZONE_CLUSTER, __VA_ARGS__)
#define emberAfIasZoneClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_IAS_ZONE_CLUSTER,  __VA_ARGS__)
#define emberAfIasZoneClusterFlush() emberAfFlush(EMBER_AF_PRINT_IAS_ZONE_CLUSTER)
#define emberAfIasZoneClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_IAS_ZONE_CLUSTER) ) { x; }
#define emberAfIasZoneClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_IAS_ZONE_CLUSTER, (buffer), (len), (withSpace))
#define emberAfIasZoneClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_IAS_ZONE_CLUSTER, (buffer))
#else
#define emberAfIasZoneClusterPrint(...)
#define emberAfIasZoneClusterPrintln(...)
#define emberAfIasZoneClusterFlush()
#define emberAfIasZoneClusterDebugExec(x)
#define emberAfIasZoneClusterPrintBuffer(buffer, len, withSpace)
#define emberAfIasZoneClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IAS_ZONE_CLUSTER)


// Printing macros for cluster: IAS ACE
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IAS_ACE_CLUSTER)
#define emberAfIasAceClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_IAS_ACE_CLUSTER, __VA_ARGS__)
#define emberAfIasAceClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_IAS_ACE_CLUSTER,  __VA_ARGS__)
#define emberAfIasAceClusterFlush() emberAfFlush(EMBER_AF_PRINT_IAS_ACE_CLUSTER)
#define emberAfIasAceClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_IAS_ACE_CLUSTER) ) { x; }
#define emberAfIasAceClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_IAS_ACE_CLUSTER, (buffer), (len), (withSpace))
#define emberAfIasAceClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_IAS_ACE_CLUSTER, (buffer))
#else
#define emberAfIasAceClusterPrint(...)
#define emberAfIasAceClusterPrintln(...)
#define emberAfIasAceClusterFlush()
#define emberAfIasAceClusterDebugExec(x)
#define emberAfIasAceClusterPrintBuffer(buffer, len, withSpace)
#define emberAfIasAceClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IAS_ACE_CLUSTER)


// Printing macros for cluster: IAS WD
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IAS_WD_CLUSTER)
#define emberAfIasWdClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_IAS_WD_CLUSTER, __VA_ARGS__)
#define emberAfIasWdClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_IAS_WD_CLUSTER,  __VA_ARGS__)
#define emberAfIasWdClusterFlush() emberAfFlush(EMBER_AF_PRINT_IAS_WD_CLUSTER)
#define emberAfIasWdClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_IAS_WD_CLUSTER) ) { x; }
#define emberAfIasWdClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_IAS_WD_CLUSTER, (buffer), (len), (withSpace))
#define emberAfIasWdClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_IAS_WD_CLUSTER, (buffer))
#else
#define emberAfIasWdClusterPrint(...)
#define emberAfIasWdClusterPrintln(...)
#define emberAfIasWdClusterFlush()
#define emberAfIasWdClusterDebugExec(x)
#define emberAfIasWdClusterPrintBuffer(buffer, len, withSpace)
#define emberAfIasWdClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IAS_WD_CLUSTER)


// Printing macros for cluster: Door Lock
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DOOR_LOCK_CLUSTER)
#define emberAfDoorLockClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_DOOR_LOCK_CLUSTER, __VA_ARGS__)
#define emberAfDoorLockClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_DOOR_LOCK_CLUSTER,  __VA_ARGS__)
#define emberAfDoorLockClusterFlush() emberAfFlush(EMBER_AF_PRINT_DOOR_LOCK_CLUSTER)
#define emberAfDoorLockClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_DOOR_LOCK_CLUSTER) ) { x; }
#define emberAfDoorLockClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_DOOR_LOCK_CLUSTER, (buffer), (len), (withSpace))
#define emberAfDoorLockClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_DOOR_LOCK_CLUSTER, (buffer))
#else
#define emberAfDoorLockClusterPrint(...)
#define emberAfDoorLockClusterPrintln(...)
#define emberAfDoorLockClusterFlush()
#define emberAfDoorLockClusterDebugExec(x)
#define emberAfDoorLockClusterPrintBuffer(buffer, len, withSpace)
#define emberAfDoorLockClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DOOR_LOCK_CLUSTER)


// Printing macros for cluster: Window Covering
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_WINDOW_COVERING_CLUSTER)
#define emberAfWindowCoveringClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_WINDOW_COVERING_CLUSTER, __VA_ARGS__)
#define emberAfWindowCoveringClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_WINDOW_COVERING_CLUSTER,  __VA_ARGS__)
#define emberAfWindowCoveringClusterFlush() emberAfFlush(EMBER_AF_PRINT_WINDOW_COVERING_CLUSTER)
#define emberAfWindowCoveringClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_WINDOW_COVERING_CLUSTER) ) { x; }
#define emberAfWindowCoveringClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_WINDOW_COVERING_CLUSTER, (buffer), (len), (withSpace))
#define emberAfWindowCoveringClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_WINDOW_COVERING_CLUSTER, (buffer))
#else
#define emberAfWindowCoveringClusterPrint(...)
#define emberAfWindowCoveringClusterPrintln(...)
#define emberAfWindowCoveringClusterFlush()
#define emberAfWindowCoveringClusterDebugExec(x)
#define emberAfWindowCoveringClusterPrintBuffer(buffer, len, withSpace)
#define emberAfWindowCoveringClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_WINDOW_COVERING_CLUSTER)


// Printing macros for cluster: Generic Tunnel
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_GENERIC_TUNNEL_CLUSTER)
#define emberAfGenericTunnelClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_GENERIC_TUNNEL_CLUSTER, __VA_ARGS__)
#define emberAfGenericTunnelClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_GENERIC_TUNNEL_CLUSTER,  __VA_ARGS__)
#define emberAfGenericTunnelClusterFlush() emberAfFlush(EMBER_AF_PRINT_GENERIC_TUNNEL_CLUSTER)
#define emberAfGenericTunnelClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_GENERIC_TUNNEL_CLUSTER) ) { x; }
#define emberAfGenericTunnelClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_GENERIC_TUNNEL_CLUSTER, (buffer), (len), (withSpace))
#define emberAfGenericTunnelClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_GENERIC_TUNNEL_CLUSTER, (buffer))
#else
#define emberAfGenericTunnelClusterPrint(...)
#define emberAfGenericTunnelClusterPrintln(...)
#define emberAfGenericTunnelClusterFlush()
#define emberAfGenericTunnelClusterDebugExec(x)
#define emberAfGenericTunnelClusterPrintBuffer(buffer, len, withSpace)
#define emberAfGenericTunnelClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_GENERIC_TUNNEL_CLUSTER)


// Printing macros for cluster: BACnet Protocol Tunnel
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_BACNET_PROTOCOL_TUNNEL_CLUSTER)
#define emberAfBacnetProtocolTunnelClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_BACNET_PROTOCOL_TUNNEL_CLUSTER, __VA_ARGS__)
#define emberAfBacnetProtocolTunnelClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_BACNET_PROTOCOL_TUNNEL_CLUSTER,  __VA_ARGS__)
#define emberAfBacnetProtocolTunnelClusterFlush() emberAfFlush(EMBER_AF_PRINT_BACNET_PROTOCOL_TUNNEL_CLUSTER)
#define emberAfBacnetProtocolTunnelClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_BACNET_PROTOCOL_TUNNEL_CLUSTER) ) { x; }
#define emberAfBacnetProtocolTunnelClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_BACNET_PROTOCOL_TUNNEL_CLUSTER, (buffer), (len), (withSpace))
#define emberAfBacnetProtocolTunnelClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_BACNET_PROTOCOL_TUNNEL_CLUSTER, (buffer))
#else
#define emberAfBacnetProtocolTunnelClusterPrint(...)
#define emberAfBacnetProtocolTunnelClusterPrintln(...)
#define emberAfBacnetProtocolTunnelClusterFlush()
#define emberAfBacnetProtocolTunnelClusterDebugExec(x)
#define emberAfBacnetProtocolTunnelClusterPrintBuffer(buffer, len, withSpace)
#define emberAfBacnetProtocolTunnelClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_BACNET_PROTOCOL_TUNNEL_CLUSTER)


// Printing macros for cluster: Over the Air Bootloading Cluster
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_OTA_BOOTLOAD_CLUSTER)
#define emberAfOtaBootloadClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_OTA_BOOTLOAD_CLUSTER, __VA_ARGS__)
#define emberAfOtaBootloadClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_OTA_BOOTLOAD_CLUSTER,  __VA_ARGS__)
#define emberAfOtaBootloadClusterFlush() emberAfFlush(EMBER_AF_PRINT_OTA_BOOTLOAD_CLUSTER)
#define emberAfOtaBootloadClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_OTA_BOOTLOAD_CLUSTER) ) { x; }
#define emberAfOtaBootloadClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_OTA_BOOTLOAD_CLUSTER, (buffer), (len), (withSpace))
#define emberAfOtaBootloadClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_OTA_BOOTLOAD_CLUSTER, (buffer))
#else
#define emberAfOtaBootloadClusterPrint(...)
#define emberAfOtaBootloadClusterPrintln(...)
#define emberAfOtaBootloadClusterFlush()
#define emberAfOtaBootloadClusterDebugExec(x)
#define emberAfOtaBootloadClusterPrintBuffer(buffer, len, withSpace)
#define emberAfOtaBootloadClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_OTA_BOOTLOAD_CLUSTER)


// Printing macros for cluster: Demand Response and Load Control
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER)
#define emberAfDemandResponseLoadControlClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER, __VA_ARGS__)
#define emberAfDemandResponseLoadControlClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER,  __VA_ARGS__)
#define emberAfDemandResponseLoadControlClusterFlush() emberAfFlush(EMBER_AF_PRINT_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER)
#define emberAfDemandResponseLoadControlClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER) ) { x; }
#define emberAfDemandResponseLoadControlClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER, (buffer), (len), (withSpace))
#define emberAfDemandResponseLoadControlClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER, (buffer))
#else
#define emberAfDemandResponseLoadControlClusterPrint(...)
#define emberAfDemandResponseLoadControlClusterPrintln(...)
#define emberAfDemandResponseLoadControlClusterFlush()
#define emberAfDemandResponseLoadControlClusterDebugExec(x)
#define emberAfDemandResponseLoadControlClusterPrintBuffer(buffer, len, withSpace)
#define emberAfDemandResponseLoadControlClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER)


// Printing macros for cluster: Simple Metering
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SIMPLE_METERING_CLUSTER)
#define emberAfSimpleMeteringClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_SIMPLE_METERING_CLUSTER, __VA_ARGS__)
#define emberAfSimpleMeteringClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_SIMPLE_METERING_CLUSTER,  __VA_ARGS__)
#define emberAfSimpleMeteringClusterFlush() emberAfFlush(EMBER_AF_PRINT_SIMPLE_METERING_CLUSTER)
#define emberAfSimpleMeteringClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_SIMPLE_METERING_CLUSTER) ) { x; }
#define emberAfSimpleMeteringClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_SIMPLE_METERING_CLUSTER, (buffer), (len), (withSpace))
#define emberAfSimpleMeteringClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_SIMPLE_METERING_CLUSTER, (buffer))
#else
#define emberAfSimpleMeteringClusterPrint(...)
#define emberAfSimpleMeteringClusterPrintln(...)
#define emberAfSimpleMeteringClusterFlush()
#define emberAfSimpleMeteringClusterDebugExec(x)
#define emberAfSimpleMeteringClusterPrintBuffer(buffer, len, withSpace)
#define emberAfSimpleMeteringClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SIMPLE_METERING_CLUSTER)


// Printing macros for cluster: Price
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_PRICE_CLUSTER)
#define emberAfPriceClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_PRICE_CLUSTER, __VA_ARGS__)
#define emberAfPriceClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_PRICE_CLUSTER,  __VA_ARGS__)
#define emberAfPriceClusterFlush() emberAfFlush(EMBER_AF_PRINT_PRICE_CLUSTER)
#define emberAfPriceClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_PRICE_CLUSTER) ) { x; }
#define emberAfPriceClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_PRICE_CLUSTER, (buffer), (len), (withSpace))
#define emberAfPriceClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_PRICE_CLUSTER, (buffer))
#else
#define emberAfPriceClusterPrint(...)
#define emberAfPriceClusterPrintln(...)
#define emberAfPriceClusterFlush()
#define emberAfPriceClusterDebugExec(x)
#define emberAfPriceClusterPrintBuffer(buffer, len, withSpace)
#define emberAfPriceClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_PRICE_CLUSTER)


// Printing macros for cluster: Messaging
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_MESSAGING_CLUSTER)
#define emberAfMessagingClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_MESSAGING_CLUSTER, __VA_ARGS__)
#define emberAfMessagingClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_MESSAGING_CLUSTER,  __VA_ARGS__)
#define emberAfMessagingClusterFlush() emberAfFlush(EMBER_AF_PRINT_MESSAGING_CLUSTER)
#define emberAfMessagingClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_MESSAGING_CLUSTER) ) { x; }
#define emberAfMessagingClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_MESSAGING_CLUSTER, (buffer), (len), (withSpace))
#define emberAfMessagingClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_MESSAGING_CLUSTER, (buffer))
#else
#define emberAfMessagingClusterPrint(...)
#define emberAfMessagingClusterPrintln(...)
#define emberAfMessagingClusterFlush()
#define emberAfMessagingClusterDebugExec(x)
#define emberAfMessagingClusterPrintBuffer(buffer, len, withSpace)
#define emberAfMessagingClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_MESSAGING_CLUSTER)


// Printing macros for cluster: Tunneling
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_TUNNELING_CLUSTER)
#define emberAfTunnelingClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_TUNNELING_CLUSTER, __VA_ARGS__)
#define emberAfTunnelingClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_TUNNELING_CLUSTER,  __VA_ARGS__)
#define emberAfTunnelingClusterFlush() emberAfFlush(EMBER_AF_PRINT_TUNNELING_CLUSTER)
#define emberAfTunnelingClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_TUNNELING_CLUSTER) ) { x; }
#define emberAfTunnelingClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_TUNNELING_CLUSTER, (buffer), (len), (withSpace))
#define emberAfTunnelingClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_TUNNELING_CLUSTER, (buffer))
#else
#define emberAfTunnelingClusterPrint(...)
#define emberAfTunnelingClusterPrintln(...)
#define emberAfTunnelingClusterFlush()
#define emberAfTunnelingClusterDebugExec(x)
#define emberAfTunnelingClusterPrintBuffer(buffer, len, withSpace)
#define emberAfTunnelingClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_TUNNELING_CLUSTER)


// Printing macros for cluster: Prepayment
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_PREPAYMENT_CLUSTER)
#define emberAfPrepaymentClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_PREPAYMENT_CLUSTER, __VA_ARGS__)
#define emberAfPrepaymentClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_PREPAYMENT_CLUSTER,  __VA_ARGS__)
#define emberAfPrepaymentClusterFlush() emberAfFlush(EMBER_AF_PRINT_PREPAYMENT_CLUSTER)
#define emberAfPrepaymentClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_PREPAYMENT_CLUSTER) ) { x; }
#define emberAfPrepaymentClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_PREPAYMENT_CLUSTER, (buffer), (len), (withSpace))
#define emberAfPrepaymentClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_PREPAYMENT_CLUSTER, (buffer))
#else
#define emberAfPrepaymentClusterPrint(...)
#define emberAfPrepaymentClusterPrintln(...)
#define emberAfPrepaymentClusterFlush()
#define emberAfPrepaymentClusterDebugExec(x)
#define emberAfPrepaymentClusterPrintBuffer(buffer, len, withSpace)
#define emberAfPrepaymentClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_PREPAYMENT_CLUSTER)


// Printing macros for cluster: Key establishment
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_KEY_ESTABLISHMENT_CLUSTER)
#define emberAfKeyEstablishmentClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_KEY_ESTABLISHMENT_CLUSTER, __VA_ARGS__)
#define emberAfKeyEstablishmentClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_KEY_ESTABLISHMENT_CLUSTER,  __VA_ARGS__)
#define emberAfKeyEstablishmentClusterFlush() emberAfFlush(EMBER_AF_PRINT_KEY_ESTABLISHMENT_CLUSTER)
#define emberAfKeyEstablishmentClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_KEY_ESTABLISHMENT_CLUSTER) ) { x; }
#define emberAfKeyEstablishmentClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_KEY_ESTABLISHMENT_CLUSTER, (buffer), (len), (withSpace))
#define emberAfKeyEstablishmentClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_KEY_ESTABLISHMENT_CLUSTER, (buffer))
#else
#define emberAfKeyEstablishmentClusterPrint(...)
#define emberAfKeyEstablishmentClusterPrintln(...)
#define emberAfKeyEstablishmentClusterFlush()
#define emberAfKeyEstablishmentClusterDebugExec(x)
#define emberAfKeyEstablishmentClusterPrintBuffer(buffer, len, withSpace)
#define emberAfKeyEstablishmentClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_KEY_ESTABLISHMENT_CLUSTER)


// Printing macros for cluster: Sample Mfg Specific Cluster
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SAMPLE_MFG_SPECIFIC_CLUSTER)
#define emberAfSampleMfgSpecificClusterPrint(...) emberAfPrint(EMBER_AF_PRINT_SAMPLE_MFG_SPECIFIC_CLUSTER, __VA_ARGS__)
#define emberAfSampleMfgSpecificClusterPrintln(...) emberAfPrintln(EMBER_AF_PRINT_SAMPLE_MFG_SPECIFIC_CLUSTER,  __VA_ARGS__)
#define emberAfSampleMfgSpecificClusterFlush() emberAfFlush(EMBER_AF_PRINT_SAMPLE_MFG_SPECIFIC_CLUSTER)
#define emberAfSampleMfgSpecificClusterDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_SAMPLE_MFG_SPECIFIC_CLUSTER) ) { x; }
#define emberAfSampleMfgSpecificClusterPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_SAMPLE_MFG_SPECIFIC_CLUSTER, (buffer), (len), (withSpace))
#define emberAfSampleMfgSpecificClusterPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_SAMPLE_MFG_SPECIFIC_CLUSTER, (buffer))
#else
#define emberAfSampleMfgSpecificClusterPrint(...)
#define emberAfSampleMfgSpecificClusterPrintln(...)
#define emberAfSampleMfgSpecificClusterFlush()
#define emberAfSampleMfgSpecificClusterDebugExec(x)
#define emberAfSampleMfgSpecificClusterPrintBuffer(buffer, len, withSpace)
#define emberAfSampleMfgSpecificClusterPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SAMPLE_MFG_SPECIFIC_CLUSTER)


// Printing macros for Core
// Prints messages for global flow of the receive/send
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_CORE)
#define emberAfCorePrint(...) emberAfPrint(EMBER_AF_PRINT_CORE, __VA_ARGS__)
#define emberAfCorePrintln(...) emberAfPrintln(EMBER_AF_PRINT_CORE,  __VA_ARGS__)
#define emberAfCoreFlush() emberAfFlush(EMBER_AF_PRINT_CORE)
#define emberAfCoreDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_CORE) ) { x; }
#define emberAfCorePrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_CORE, (buffer), (len), (withSpace))
#define emberAfCorePrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_CORE, (buffer))
#else
#define emberAfCorePrint(...)
#define emberAfCorePrintln(...)
#define emberAfCoreFlush()
#define emberAfCoreDebugExec(x)
#define emberAfCorePrintBuffer(buffer, len, withSpace)
#define emberAfCorePrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_CORE)


// Printing macros for Debug
// Prints messages for random debugging
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DEBUG)
#define emberAfDebugPrint(...) emberAfPrint(EMBER_AF_PRINT_DEBUG, __VA_ARGS__)
#define emberAfDebugPrintln(...) emberAfPrintln(EMBER_AF_PRINT_DEBUG,  __VA_ARGS__)
#define emberAfDebugFlush() emberAfFlush(EMBER_AF_PRINT_DEBUG)
#define emberAfDebugDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_DEBUG) ) { x; }
#define emberAfDebugPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_DEBUG, (buffer), (len), (withSpace))
#define emberAfDebugPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_DEBUG, (buffer))
#else
#define emberAfDebugPrint(...)
#define emberAfDebugPrintln(...)
#define emberAfDebugFlush()
#define emberAfDebugDebugExec(x)
#define emberAfDebugPrintBuffer(buffer, len, withSpace)
#define emberAfDebugPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DEBUG)


// Printing macros for Application
// Prints messages for application part
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
#define emberAfAppPrint(...) emberAfPrint(EMBER_AF_PRINT_APP, __VA_ARGS__)
#define emberAfAppPrintln(...) emberAfPrintln(EMBER_AF_PRINT_APP,  __VA_ARGS__)
#define emberAfAppFlush() emberAfFlush(EMBER_AF_PRINT_APP)
#define emberAfAppDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_APP) ) { x; }
#define emberAfAppPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_APP, (buffer), (len), (withSpace))
#define emberAfAppPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_APP, (buffer))
#else
#define emberAfAppPrint(...)
#define emberAfAppPrintln(...)
#define emberAfAppFlush()
#define emberAfAppDebugExec(x)
#define emberAfAppPrintBuffer(buffer, len, withSpace)
#define emberAfAppPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)


// Printing macros for Security
// Prints messages related to security
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SECURITY)
#define emberAfSecurityPrint(...) emberAfPrint(EMBER_AF_PRINT_SECURITY, __VA_ARGS__)
#define emberAfSecurityPrintln(...) emberAfPrintln(EMBER_AF_PRINT_SECURITY,  __VA_ARGS__)
#define emberAfSecurityFlush() emberAfFlush(EMBER_AF_PRINT_SECURITY)
#define emberAfSecurityDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_SECURITY) ) { x; }
#define emberAfSecurityPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_SECURITY, (buffer), (len), (withSpace))
#define emberAfSecurityPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_SECURITY, (buffer))
#else
#define emberAfSecurityPrint(...)
#define emberAfSecurityPrintln(...)
#define emberAfSecurityFlush()
#define emberAfSecurityDebugExec(x)
#define emberAfSecurityPrintBuffer(buffer, len, withSpace)
#define emberAfSecurityPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SECURITY)


// Printing macros for Attributes
// Prints messages related to attributes
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ATTRIBUTES)
#define emberAfAttributesPrint(...) emberAfPrint(EMBER_AF_PRINT_ATTRIBUTES, __VA_ARGS__)
#define emberAfAttributesPrintln(...) emberAfPrintln(EMBER_AF_PRINT_ATTRIBUTES,  __VA_ARGS__)
#define emberAfAttributesFlush() emberAfFlush(EMBER_AF_PRINT_ATTRIBUTES)
#define emberAfAttributesDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_ATTRIBUTES) ) { x; }
#define emberAfAttributesPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_ATTRIBUTES, (buffer), (len), (withSpace))
#define emberAfAttributesPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_ATTRIBUTES, (buffer))
#else
#define emberAfAttributesPrint(...)
#define emberAfAttributesPrintln(...)
#define emberAfAttributesFlush()
#define emberAfAttributesDebugExec(x)
#define emberAfAttributesPrintBuffer(buffer, len, withSpace)
#define emberAfAttributesPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ATTRIBUTES)


// Printing macros for Reporting
// Prints messages related to reporting
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_REPORTING)
#define emberAfReportingPrint(...) emberAfPrint(EMBER_AF_PRINT_REPORTING, __VA_ARGS__)
#define emberAfReportingPrintln(...) emberAfPrintln(EMBER_AF_PRINT_REPORTING,  __VA_ARGS__)
#define emberAfReportingFlush() emberAfFlush(EMBER_AF_PRINT_REPORTING)
#define emberAfReportingDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_REPORTING) ) { x; }
#define emberAfReportingPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_REPORTING, (buffer), (len), (withSpace))
#define emberAfReportingPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_REPORTING, (buffer))
#else
#define emberAfReportingPrint(...)
#define emberAfReportingPrintln(...)
#define emberAfReportingFlush()
#define emberAfReportingDebugExec(x)
#define emberAfReportingPrintBuffer(buffer, len, withSpace)
#define emberAfReportingPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_REPORTING)


// Printing macros for Service discovery
// Prints messages related to service discovery
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SERVICE_DISCOVERY)
#define emberAfServiceDiscoveryPrint(...) emberAfPrint(EMBER_AF_PRINT_SERVICE_DISCOVERY, __VA_ARGS__)
#define emberAfServiceDiscoveryPrintln(...) emberAfPrintln(EMBER_AF_PRINT_SERVICE_DISCOVERY,  __VA_ARGS__)
#define emberAfServiceDiscoveryFlush() emberAfFlush(EMBER_AF_PRINT_SERVICE_DISCOVERY)
#define emberAfServiceDiscoveryDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_SERVICE_DISCOVERY) ) { x; }
#define emberAfServiceDiscoveryPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_SERVICE_DISCOVERY, (buffer), (len), (withSpace))
#define emberAfServiceDiscoveryPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_SERVICE_DISCOVERY, (buffer))
#else
#define emberAfServiceDiscoveryPrint(...)
#define emberAfServiceDiscoveryPrintln(...)
#define emberAfServiceDiscoveryFlush()
#define emberAfServiceDiscoveryDebugExec(x)
#define emberAfServiceDiscoveryPrintBuffer(buffer, len, withSpace)
#define emberAfServiceDiscoveryPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SERVICE_DISCOVERY)


// Printing macros for Registration
// Prints messages related to registration
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_REGISTRATION)
#define emberAfRegistrationPrint(...) emberAfPrint(EMBER_AF_PRINT_REGISTRATION, __VA_ARGS__)
#define emberAfRegistrationPrintln(...) emberAfPrintln(EMBER_AF_PRINT_REGISTRATION,  __VA_ARGS__)
#define emberAfRegistrationFlush() emberAfFlush(EMBER_AF_PRINT_REGISTRATION)
#define emberAfRegistrationDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_REGISTRATION) ) { x; }
#define emberAfRegistrationPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_REGISTRATION, (buffer), (len), (withSpace))
#define emberAfRegistrationPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_REGISTRATION, (buffer))
#else
#define emberAfRegistrationPrint(...)
#define emberAfRegistrationPrintln(...)
#define emberAfRegistrationFlush()
#define emberAfRegistrationDebugExec(x)
#define emberAfRegistrationPrintBuffer(buffer, len, withSpace)
#define emberAfRegistrationPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_REGISTRATION)


// Printing macros for ZDO (ZigBee Device Object)
// Prints messages related to ZDO functionality
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ZDO)
#define emberAfZdoPrint(...) emberAfPrint(EMBER_AF_PRINT_ZDO, __VA_ARGS__)
#define emberAfZdoPrintln(...) emberAfPrintln(EMBER_AF_PRINT_ZDO,  __VA_ARGS__)
#define emberAfZdoFlush() emberAfFlush(EMBER_AF_PRINT_ZDO)
#define emberAfZdoDebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_ZDO) ) { x; }
#define emberAfZdoPrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_ZDO, (buffer), (len), (withSpace))
#define emberAfZdoPrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_ZDO, (buffer))
#else
#define emberAfZdoPrint(...)
#define emberAfZdoPrintln(...)
#define emberAfZdoFlush()
#define emberAfZdoDebugExec(x)
#define emberAfZdoPrintBuffer(buffer, len, withSpace)
#define emberAfZdoPrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_ZDO)


// Printing macros for Custom messages (1)
// Messages that can be used by the end developer
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_CUSTOM1)
#define emberAfCustom1Print(...) emberAfPrint(EMBER_AF_PRINT_CUSTOM1, __VA_ARGS__)
#define emberAfCustom1Println(...) emberAfPrintln(EMBER_AF_PRINT_CUSTOM1,  __VA_ARGS__)
#define emberAfCustom1Flush() emberAfFlush(EMBER_AF_PRINT_CUSTOM1)
#define emberAfCustom1DebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_CUSTOM1) ) { x; }
#define emberAfCustom1PrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_CUSTOM1, (buffer), (len), (withSpace))
#define emberAfCustom1PrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_CUSTOM1, (buffer))
#else
#define emberAfCustom1Print(...)
#define emberAfCustom1Println(...)
#define emberAfCustom1Flush()
#define emberAfCustom1DebugExec(x)
#define emberAfCustom1PrintBuffer(buffer, len, withSpace)
#define emberAfCustom1PrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_CUSTOM1)


// Printing macros for Custom messages (2)
// Messages that can be used by the end developer
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_CUSTOM2)
#define emberAfCustom2Print(...) emberAfPrint(EMBER_AF_PRINT_CUSTOM2, __VA_ARGS__)
#define emberAfCustom2Println(...) emberAfPrintln(EMBER_AF_PRINT_CUSTOM2,  __VA_ARGS__)
#define emberAfCustom2Flush() emberAfFlush(EMBER_AF_PRINT_CUSTOM2)
#define emberAfCustom2DebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_CUSTOM2) ) { x; }
#define emberAfCustom2PrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_CUSTOM2, (buffer), (len), (withSpace))
#define emberAfCustom2PrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_CUSTOM2, (buffer))
#else
#define emberAfCustom2Print(...)
#define emberAfCustom2Println(...)
#define emberAfCustom2Flush()
#define emberAfCustom2DebugExec(x)
#define emberAfCustom2PrintBuffer(buffer, len, withSpace)
#define emberAfCustom2PrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_CUSTOM2)


// Printing macros for Custom messages (3)
// Messages that can be used by the end developer
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_CUSTOM3)
#define emberAfCustom3Print(...) emberAfPrint(EMBER_AF_PRINT_CUSTOM3, __VA_ARGS__)
#define emberAfCustom3Println(...) emberAfPrintln(EMBER_AF_PRINT_CUSTOM3,  __VA_ARGS__)
#define emberAfCustom3Flush() emberAfFlush(EMBER_AF_PRINT_CUSTOM3)
#define emberAfCustom3DebugExec(x) if ( emberAfPrintEnabled(EMBER_AF_PRINT_CUSTOM3) ) { x; }
#define emberAfCustom3PrintBuffer(buffer, len, withSpace) emberAfPrintBuffer(EMBER_AF_PRINT_CUSTOM3, (buffer), (len), (withSpace))
#define emberAfCustom3PrintString(buffer) emberAfPrintString(EMBER_AF_PRINT_CUSTOM3, (buffer))
#else
#define emberAfCustom3Print(...)
#define emberAfCustom3Println(...)
#define emberAfCustom3Flush()
#define emberAfCustom3DebugExec(x)
#define emberAfCustom3PrintBuffer(buffer, len, withSpace)
#define emberAfCustom3PrintString(buffer)
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_CUSTOM3)


