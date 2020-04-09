// *******************************************************************
// * thermostat.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the util
#include "../../util/common.h"

// clusters specific header
#include "thermostat.h"


#ifdef ZCL_USING_THERMOSTAT_CLUSTER_SERVER
// -------------------------------------------------------
// THERMOSTAT
// -------------------------------------------------------

// this reads the current ZCL_OCCUPIED_HEATING_SETPOINT_ATTRIBUTE_ID or
// ZCL_OCCUPIED_COOLING_SETPOINT_ATTRIBUTE_ID, adds the amount specified
// (which may be negative) and writes it back to the attribute
static EmberAfStatus afThermostatAdjust(int8u endpoint,
                                        EmberAfAttributeId attrId,
                                        int8s amount)
{
  EmberAfStatus status;
  int16s currentSetting, newSetting;

  // read the heat or cool setting
  status = emberAfReadAttribute(endpoint,
                                ZCL_THERMOSTAT_CLUSTER_ID,
                                attrId,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&currentSetting,
                                sizeof(currentSetting),
                                NULL); // data type
  // check the status
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfThermostatClusterPrintln("ERR: read TSTAT attr 0x%2x status 0x%x",
                                    attrId,
                                    status);
  } else {
    // add the amount
    newSetting = currentSetting + amount;
    emberAfThermostatClusterPrintln("changing %2x by %d from %d to %d",
                                    attrId,
                                    amount,
                                    currentSetting,
                                    newSetting);

    // TODO: error check, min and max vals and not too close (deadband spacing)

    // write the new value
    status = emberAfWriteAttribute(endpoint,
                                   ZCL_THERMOSTAT_CLUSTER_ID,
                                   attrId,
                                   CLUSTER_MASK_SERVER,
                                   (int8u *)&newSetting,
                                   ZCL_INT16S_ATTRIBUTE_TYPE);
    // check the status
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      emberAfThermostatClusterPrintln("ERR: write TSTAT attr 0x%2x status 0x%x",
                                      attrId,
                                      status);
    }
  }

  return status;
}

boolean emberAfThermostatClusterSetpointRaiseLowerCallback(int8u mode,
                                                           int8s amount)
{
  EmberAfStatus status = EMBER_ZCL_STATUS_SUCCESS;

  emberAfThermostatClusterPrintln("RX thermostat:SETPOINT_RAISE_LOWER 0x%x 0x%x",
                                  mode,
                                  amount);

  // adjust heat it we are supposed to adjust heat or both
  if (mode == EMBER_ZCL_SETPOINT_ADJUST_MODE_HEAT_SETPOINT ||
      mode == EMBER_ZCL_SETPOINT_ADJUST_MODE_HEAT_AND_COOL_SETPOINTS) {
    status = afThermostatAdjust(emberAfCurrentEndpoint(),
                                ZCL_OCCUPIED_HEATING_SETPOINT_ATTRIBUTE_ID,
                                amount);
  }

  // adjust cool it we are supposed to adjust cool or both, unless we failed
  // updating the cool
  if (status == EMBER_ZCL_STATUS_SUCCESS
      && (mode == EMBER_ZCL_SETPOINT_ADJUST_MODE_COOL_SETPOINT ||
          mode == EMBER_ZCL_SETPOINT_ADJUST_MODE_HEAT_AND_COOL_SETPOINTS)) {
    status = afThermostatAdjust(emberAfCurrentEndpoint(),
                                ZCL_OCCUPIED_COOLING_SETPOINT_ATTRIBUTE_ID,
                                amount);
  }

  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}

EmberAfStatus emAfSetLocalTemperature(int8u endpoint, int16s localTemperature)
{
  EmberAfStatus status = emberAfWriteAttribute(endpoint, 
                                               ZCL_THERMOSTAT_CLUSTER_ID, 
                                               ZCL_LOCAL_TEMPERATURE_ATTRIBUTE_ID,
                                               CLUSTER_MASK_SERVER,
                                               (int8u *)&localTemperature,
                                               ZCL_INT16S_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfThermostatClusterPrintln("ERR: writing local temperature %x",
                                    status);
  }
  return status;
}
#endif //ZCL_USING_THERMOSTAT_CLUSTER_SERVER
