// *******************************************************************
// * temperature-measurement.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the util
#include "../../include/af.h"
#include "../../util/common.h"

// clusters specific header
#include "temperature-measurement.h"

#ifdef EMBER_AF_PLUGIN_THERMOSTAT
#include "../thermostat/thermostat.h"
#endif //EMBER_AF_PLUGIN_THERMOSTAT

#ifdef ZCL_USING_TEMP_MEASUREMENT_CLUSTER_SERVER
// temp is measured in 0.01 degrees C
// ------------------------------------
// value of 0     = 0x0000 = 0.00 C
// value of 1     = 0x0001 = 0.01 C
//    ...
// value of 32767 = 0x7FFF = 0.00 C
//
// value of 65535 (-1) = 0xFFFF = -0.01 C
// value of 65534 (-2) = 0xFFFE = -0.02 C
//   ...
// value of 38221 (-2) = 0x954D = -273.15 C
//     (65536 - 38221) = 27315
//
// ------------------------------------

void emberAfTempMeasurementClusterServerInitCallback(int8u endpoint)
{
#ifndef GATEWAY_APP
  // Schedule half-second ticks, unless it is a gateway application.
  emberAfScheduleClusterTick(endpoint,
                             ZCL_TEMP_MEASUREMENT_CLUSTER_ID,
                             EMBER_AF_SERVER_CLUSTER_TICK,
                             MILLISECOND_TICKS_PER_SECOND >> 1,
                             EMBER_AF_OK_TO_HIBERNATE);
#endif //GATEWAY_APP
}

void emberAfTempMeasurementClusterServerTickCallback(int8u endpoint)
{
#ifndef GATEWAY_APP
  EmberAfStatus status;
  int16u tempReading;
  int16s volts;
  int32u tempC;
  int16u newTempSetting;

  // Reschedule half-second ticks.
  emberAfScheduleClusterTick(endpoint,
                             ZCL_TEMP_MEASUREMENT_CLUSTER_ID,
                             EMBER_AF_SERVER_CLUSTER_TICK,
                             MILLISECOND_TICKS_PER_SECOND >> 1,
                             EMBER_AF_OK_TO_HIBERNATE);

  // start the conversion - every other tick we start a reading
  halStartAdcConversion(ADC_USER_APP2,
                        ADC_REF_INT,
                        TEMP_SENSOR_ADC_CHANNEL,
                        ADC_CONVERSION_TIME_US_256);
  halCommonDelayMicroseconds((int16u)600);

  // read the temp - if we don't get a reading, exit
  if (halRequestAdcData(ADC_USER_APP2, &tempReading)
      != EMBER_ADC_CONVERSION_DONE) {
    return;
  }

  // convert to volts, volts=1234 means value +0.1234
  volts = halConvertValueToVolts(tempReading);

  // convert to temperature. After division, tempC val of 3116 means 31.16 C
  tempC = emberAfTempMeasurementClusterConvertVoltsToCelsiusCallback(volts)/100;

  // move the 4-byte value into a 2-byte value
  newTempSetting = ((BYTE_1(tempC)) << 8) + BYTE_0(tempC);

  status = emberAfWriteAttribute(endpoint,
                                 ZCL_TEMP_MEASUREMENT_CLUSTER_ID,
                                 ZCL_TEMP_MEASURED_VALUE_ATTRIBUTE_ID,
                                 CLUSTER_MASK_SERVER,
                                 (int8u *)&newTempSetting,
                                 ZCL_INT16S_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfTempMeasurementClusterPrintln("ERR: writing measured value %x",
                                         status);
  } else {
#ifdef EMBER_AF_PLUGIN_THERMOSTAT
    // If we successfully updated the temperature here, set it in the thermostat
    // cluster as well.
    emAfSetLocalTemperature(endpoint, newTempSetting);
#endif //EMBER_AF_PLUGIN_THERMOSTAT
  }
#endif //GATEWAY_APP
}
#endif //ZCL_USING_TEMP_MEASUREMENT_CLUSTER_SERVER
