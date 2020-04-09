// *******************************************************************
// * simple-metering-test.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the util
#include "../../util/common.h"
#include "../../util/af-main.h"
#include "../../util/client-api.h"
#include "../../gen/enums.h"
#include "simple-metering-test.h"

#ifdef EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ENABLE

// Test mode:
//   bit 0: 0 - electric, 1 - gas
//   bit 1: reserved for future use
//   bit 2: 0 - no profiles, 1 - profiles
//   bit 3: 0 - no tick, 1 = tick
int8u testMode = 0;
int8u errorChance = 0;
int16u meterConsumptionRate = 0;
int16u meterConsumptionVariance = 0;

static void addToByteArray(int8u *data,
			   int8u len,
			   int32u toAdd,
			   boolean lowHigh) {
  int16u sum = 0;
  int8s loc, end, incr;
  if (lowHigh) {
    loc  = 0;
    end  = len;
    incr = 1;
  } else {
    loc  = len - 1;
    end  = -1;
    incr = -1;
  }

  while ( loc != end ) {
    int8u t, s;
    t = data[loc];
    s = toAdd & 0xff;
    sum += t + s;
    data[loc] = sum & 0xff;
    sum >>= 8;
    toAdd >>= 8;
    loc += incr;
  }
}
static void addToByteArrayLowHigh(int8u *data,
				  int8u len,
				  int32u toAdd) {
  addToByteArray(data, len, toAdd, TRUE);
}
static void addToByteArrayHighLow(int8u *data,
				  int8u len,
				  int32u toAdd) {
  addToByteArray(data, len, toAdd, FALSE);
}



void afTestMeterPrint(void) {
  emberAfSimpleMeteringClusterPrintln("TM:\r\nmode:%x"
				      "meterConsumptionRate:%2x\r\n"
				      "meterConsumptionVariance:%2x\r\n",
				      testMode,
				      meterConsumptionRate,
				      meterConsumptionVariance);
}
void afTestMeterSetConsumptionRate(int16u rate) {
  emberAfSimpleMeteringClusterPrintln("TM: set consumption rate %2x", rate);
  meterConsumptionRate = rate;
}
void afTestMeterSetConsumptionVariance(int16u variance) {
  emberAfSimpleMeteringClusterPrintln("TM: set consumption variance %2x", variance);
  meterConsumptionVariance = variance;
}
void afTestMeterAdjust(int8u endpoint) {

  int8u summation[] = {0,0,0,0,0,0};

  // Seconds in day
  int32u ct = emberAfGetCurrentTime() % 86400;
  int32u diff;

  emberAfSimpleMeteringClusterPrintln("TM: adjust");

  diff = (int32u)meterConsumptionRate * ct;
  if ( meterConsumptionVariance > 0 )
    diff += ct * (int32u)(halCommonGetRandom() % meterConsumptionVariance);

  if (BIGENDIAN_CPU)
    addToByteArrayHighLow(summation, 6, diff);
  else
    addToByteArrayLowHigh(summation, 6, diff);

  emberAfSimpleMeteringClusterPrintln("Summation:%x %x %x %x %x %x",
				      summation[0],
				      summation[1],
				      summation[2],
				      summation[3],
				      summation[4],
				      summation[5]);

  emberAfWriteAttribute(endpoint,
                        ZCL_SIMPLE_METERING_CLUSTER_ID,
                        ZCL_CURRENT_SUMMATION_DELIVERED_ATTRIBUTE_ID,
                        CLUSTER_MASK_SERVER,
                        summation,
                        ZCL_INT48U_ATTRIBUTE_TYPE);
}

#ifdef EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ENABLE
// 0 off, 1 if electric, 2 if gas
void afTestMeterMode(int8u endpoint, int8u mode) {
  int8u status = 0;
  int8u unitOfMeasure;
  int8u deviceType;
  int8u summationFormatting = 0x2C; // 00101100

  if ( mode == 0 ) {
    testMode &= ( ~0x08);
  } else if ( mode == 1 ) {
    testMode &= (~0x01);
    testMode |= 0x08;
    unitOfMeasure = EMBER_ZCL_AMI_UNIT_OF_MEASURE_KILO_WATT_HOURS;
    deviceType = EMBER_ZCL_METER_DEVICE_TYPE_ELECTRIC_METER;
  } else if ( mode == 2 ) {
    testMode |= (0x01|0x08);
    unitOfMeasure = EMBER_ZCL_AMI_UNIT_OF_MEASURE_BT_US_OR_BTU_PER_HOUR;
    deviceType = EMBER_ZCL_METER_DEVICE_TYPE_GAS_METER;
  }
  emberAfSimpleMeteringClusterPrintln("TM: mode %x", testMode);

  // Set attributes...

  // Status = OK
  emberAfWriteAttribute(endpoint,
                        ZCL_SIMPLE_METERING_CLUSTER_ID,
                        ZCL_STATUS_ATTRIBUTE_ID,
                        CLUSTER_MASK_SERVER,
                        &status,
                        ZCL_BITMAP8_ATTRIBUTE_TYPE);

  // Device type is either gas or electric
  emberAfWriteAttribute(endpoint,
                        ZCL_SIMPLE_METERING_CLUSTER_ID,
                        ZCL_METERING_DEVICE_TYPE_ATTRIBUTE_ID,
                        CLUSTER_MASK_SERVER,
                        &deviceType,
                        ZCL_BITMAP8_ATTRIBUTE_TYPE);

  // Unit of meausre is either KWH or BTU
  emberAfWriteAttribute(endpoint,
                        ZCL_SIMPLE_METERING_CLUSTER_ID,
                        ZCL_UNIT_OF_MEASURE_ATTRIBUTE_ID,
                        CLUSTER_MASK_SERVER,
                        &unitOfMeasure,
                        ZCL_ENUM8_ATTRIBUTE_TYPE);

  // Summation formatting is 0x2C
  emberAfWriteAttribute(endpoint,
                        ZCL_SIMPLE_METERING_CLUSTER_ID,
                        ZCL_SUMMATION_FORMATTING_ATTRIBUTE_ID,
                        CLUSTER_MASK_SERVER,
                        &summationFormatting,
                        ZCL_BITMAP8_ATTRIBUTE_TYPE);
}
#endif  // EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ENABLE

#ifdef EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ERRORS
void afTestMeterSetError(int8u endpoint,
			 int8u error) {
  emberAfSimpleMeteringClusterPrintln("TM: set error %x", error);
  emberAfWriteAttribute(endpoint,
                        ZCL_SIMPLE_METERING_CLUSTER_ID,
                        ZCL_STATUS_ATTRIBUTE_ID,
                        CLUSTER_MASK_SERVER,
                        &error,
                        ZCL_BITMAP8_ATTRIBUTE_TYPE);
}

void afTestMeterRandomError(int8u chanceIn256) {
  emberAfSimpleMeteringClusterPrintln("TM: random error %x", chanceIn256);
  errorChance = chanceIn256;
}
#endif //EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ERRORS

#if ( EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES != 0 )

int8u testMeterProfiles[EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES][3];

void afTestMeterEnableProfiles(int8u enable) {
  int8u i;
  emberAfSimpleMeteringClusterPrintln("TM: profiles %x", enable);
  switch(enable) {
  case 0:
    testMode &= (~0x04);
    break;
  case 1:
    testMode |= 0x04;
    break;
  case 2:
    for ( i=0; i<EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES; i++ ) {
      testMeterProfiles[i][0]
        = testMeterProfiles[i][1]
        = testMeterProfiles[i][2]
        = 0x00;
    }
  case 3:
    for ( i=0; i<EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES; i++ ) {
      emberAfSimpleMeteringClusterPrintln("P %x: %x%x%x",
					  i,
					  testMeterProfiles[i][0],
					  testMeterProfiles[i][1],
					  testMeterProfiles[i][2]);
    }
    break;
  }
}

#endif // EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES != 0


void emAfTestMeterInit(int8u endpoint) {
      MEMSET(testMeterProfiles,
	     0,
	     (EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES * 3));
}

// Note: In the final implementation, according to the SE spec following must
//  happen:
//   - ReadingSnapShotTime attribute must be set to the actual UTC time of
//        when the CurrentSummationDelivered, CurrentSummationReceived,
//        CurrentMaxDemandDelievered and CurrentMaxDemandReceived were measured.
//   - CurrentMaxDemandDeliveredTime must be set to UTC time of when the
//        CurrentMaxDelivered was read
//   - CurrentMaxDemandReceivedTime must be set to UTC time of when the
//        CurrentMaxDemandReceived was read
void emAfTestMeterTick(int8u endpoint) {
  int32u diff, currentTime;
  int8u status, dataType;
  int8u summation[] = {0,0,0,0,0,0};
#ifdef EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ERRORS
  int8u meterStatus;
#endif // EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ERRORS

#if (EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES != 0)
  int8u intervalSummation[] = {0,0,0};
#endif

  // Now let's adjust the summation
  status = emberAfReadAttribute(endpoint,
                                ZCL_SIMPLE_METERING_CLUSTER_ID,
                                ZCL_CURRENT_SUMMATION_DELIVERED_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                summation,
                                6,
                                &dataType);
  if ( status != EMBER_ZCL_STATUS_SUCCESS ) {
    emberAfSimpleMeteringClusterPrintln("ERR: can't read summation");
    return;
  }


  diff = (int32u)meterConsumptionRate;
  if ( meterConsumptionVariance > 0 )
    diff += (int32u)(halCommonGetRandom() % meterConsumptionVariance);

  if (BIGENDIAN_CPU)
    addToByteArrayHighLow(summation, 6, diff);
  else
    addToByteArrayLowHigh(summation, 6, diff);

  emberAfSimpleMeteringClusterPrintln("TM summation:%x %x %x %x %x %x",
				      summation[0],
				      summation[1],
				      summation[2],
				      summation[3],
				      summation[4],
				      summation[5]);

  emberAfWriteAttribute(endpoint,
                        ZCL_SIMPLE_METERING_CLUSTER_ID,
                        ZCL_CURRENT_SUMMATION_DELIVERED_ATTRIBUTE_ID,
                        CLUSTER_MASK_SERVER,
                        summation,
                        ZCL_INT48U_ATTRIBUTE_TYPE);

#ifdef EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ERRORS
  if ( errorChance > 0 ) {
    if ( (halCommonGetRandom() % 256) < errorChance ) {
      emberAfReadAttribute(endpoint,
                           ZCL_SIMPLE_METERING_CLUSTER_ID,
                           ZCL_STATUS_ATTRIBUTE_ID,
                           CLUSTER_MASK_SERVER,
                           &meterStatus,
                           1,
                           &dataType);
      if ( meterStatus == 0 ) {
        emberAfSimpleMeteringClusterPrintln("TM: random error set");
        meterStatus = 1;
        emberAfWriteAttribute(endpoint,
                              ZCL_SIMPLE_METERING_CLUSTER_ID,
                              ZCL_STATUS_ATTRIBUTE_ID,
                              CLUSTER_MASK_SERVER,
                              &meterStatus,
                              ZCL_BITMAP8_ATTRIBUTE_TYPE);
      }
    }
  }
#endif // EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ERRORS

#if (EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES != 0)
  if ( testMode & 0x04 ) { // Profiles are enabled
    // add diff to CurrentPartialProfileIntervalValueDelivered
    status = emberAfReadAttribute(endpoint,
                                  ZCL_SIMPLE_METERING_CLUSTER_ID,
                                  ZCL_CURRENT_PARTIAL_PROFILE_INTERVAL_VALUE_DELIVERED_ATTRIBUTE_ID,
                                  CLUSTER_MASK_SERVER,
                                  intervalSummation,
                                  3,
                                  &dataType);
    if ( status != EMBER_ZCL_STATUS_SUCCESS ) {
      emberAfSimpleMeteringClusterPrintln("ERR: can't read interval summation");
      return;
    }

    if (BIGENDIAN_CPU)
      addToByteArrayHighLow(intervalSummation, 3, diff);
    else
      addToByteArrayLowHigh(intervalSummation, 3, diff);

    emberAfSimpleMeteringClusterPrintln("TM interval summation: %x%x%x",
					intervalSummation[0],
					intervalSummation[1],
					intervalSummation[2] );

    emberAfWriteAttribute(endpoint,
                          ZCL_SIMPLE_METERING_CLUSTER_ID,
                          ZCL_CURRENT_PARTIAL_PROFILE_INTERVAL_VALUE_DELIVERED_ATTRIBUTE_ID,
                          CLUSTER_MASK_SERVER,
                          intervalSummation,
                          ZCL_INT24U_ATTRIBUTE_TYPE);

    // Profile swap...
    emberAfSimpleMeteringClusterPrintln("TM: swapping profile");

    for ( status = EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES - 1;
	  status > 0;
	  status -- ) {
      MEMCOPY(testMeterProfiles[status],
	      testMeterProfiles[status-1],
	      3);
    }
    MEMCOPY(testMeterProfiles[0],
	    intervalSummation,
	    3);

    intervalSummation[0]
      = intervalSummation[1]
      = intervalSummation[2] = 0;

    // Reset summation
    emberAfWriteAttribute(endpoint,
			  ZCL_SIMPLE_METERING_CLUSTER_ID,
			  ZCL_CURRENT_PARTIAL_PROFILE_INTERVAL_VALUE_DELIVERED_ATTRIBUTE_ID,
			  CLUSTER_MASK_SERVER,
			  intervalSummation,
			  ZCL_INT24U_ATTRIBUTE_TYPE);

    // Set interval time
    currentTime = emberAfGetCurrentTime();
    emberAfWriteAttribute(endpoint,
			  ZCL_SIMPLE_METERING_CLUSTER_ID,
			  ZCL_CURRENT_PARTIAL_PROFILE_INTERVAL_START_TIME_DELIVERED_ATTRIBUTE_ID,
			  CLUSTER_MASK_SERVER,
			  (int8u*)&currentTime,
			  ZCL_UTC_TIME_ATTRIBUTE_TYPE);

    for ( status=0;
	  status<EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES;
	  status++ ) {
      emberAfSimpleMeteringClusterPrintln("TM: Pr %x: %x%x%x",
					  status,
					  testMeterProfiles[status][0],
					  testMeterProfiles[status][1],
					  testMeterProfiles[status][2]);
    }
  } // testMode & 0x04
#endif // (EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES != 0)
}



boolean emAfTestMeterGetProfiles(int8u intervalChannel,
                                 int32u endTime,
                                 int8u numberOfPeriods)
{
#if (EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES != 0)
  // Get the current time
  int32u ct;
  int8u start, stop, dt, i, profilesReturned;
  int8u ep = emberAfCurrentCommand()->apsFrame->destinationEndpoint;
  EmberAfStatus status = emberAfReadAttribute(ep,
					      ZCL_SIMPLE_METERING_CLUSTER_ID,
					      ZCL_CURRENT_PARTIAL_PROFILE_INTERVAL_START_TIME_DELIVERED_ATTRIBUTE_ID,
					      CLUSTER_MASK_SERVER,
					      (int8u*)&ct,
					      4,
					      &dt);

  // If we can read the last profile time, AND either the endTime requested is 0 OR it is greater than
  // the oldest read time, we can handle this - otherwise we return failure 0x05.
  if ((status == EMBER_ZCL_STATUS_SUCCESS) &&
      (endTime == 0 ||
       (endTime > ((ct > TOTAL_PROFILE_TIME_SPAN_IN_SECONDS) ?
		   (ct - TOTAL_PROFILE_TIME_SPAN_IN_SECONDS) : 0)))) {

    start = ((endTime > 0 && ct > endTime) ? ((ct - endTime) / PROFILE_INTERVAL_PERIOD_IN_SECONDS) : 0);
    stop = (((MAX_PROFILE_INDEX - start) >
	     numberOfPeriods) ? (start + numberOfPeriods - 1) :
	    MAX_PROFILE_INDEX);
    profilesReturned = (stop - start + 1);

    //DEBUG
    emberAfSimpleMeteringClusterPrintln("start: %x, stop: %x, preq: %x, pret, %x", start, stop, numberOfPeriods, profilesReturned);
    emberAfSimpleMeteringClusterFlush();

    emberAfFillCommandSimpleMeteringClusterGetProfileResponse(endTime,
							      0x00,
							      PROFILE_INTERVAL_PERIOD_TIMEFRAME,
							      profilesReturned,
							      appResponseData,
							      profilesReturned * 3);
    appResponseData[1] = emberAfIncomingZclSequenceNumber;

    for (i = 0; i < profilesReturned; i++) {
      emberAfCopyInt24u(appResponseData, 10 + (i * 3), (int32u)testMeterProfiles[start + i]);
    }
    appResponseLength = 10 + (3 * profilesReturned);

    emberAfSendResponse();

    emberAfSimpleMeteringClusterPrintln("get profile: 0x%x, 0x%4x, 0x%x",
					intervalChannel,
					endTime,
					numberOfPeriods);

    return TRUE;
  }
#endif //(EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES != 0)
  //Otherwise we send back a failure

  emberAfFillCommandSimpleMeteringClusterGetProfileResponse(endTime,
                                                            0x05,
                                                            0,
                                                            0,
                                                            appResponseData,
                                                            0);
  appResponseData[1] = emberAfIncomingZclSequenceNumber;
  appResponseLength = 10;
  emberAfSendResponse();
  return TRUE;
}

#else
void emAfTestMeterInit(int8u endpoint) {}
void emAfTestMeterTick(int8u endpoint) {}
boolean emAfTestMeterGetProfiles(int8u intervalChannel,
				 int32u endTime,
				 int8u numberOfPeriods) {
  return FALSE;

}
#endif //EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ENABLE


