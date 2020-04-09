// *******************************************************************
// * ami-simple-metering.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the util
#include "../../include/af.h"
#include "../../util/common.h"
#include "simple-metering-test.h"


void emberAfSimpleMeteringClusterServerInitCallback(int8u endpoint) 
{
  emAfTestMeterInit(endpoint);
  emberAfScheduleClusterTick(endpoint,
                             ZCL_SIMPLE_METERING_CLUSTER_ID,
                             EMBER_AF_SERVER_CLUSTER_TICK,
                             MILLISECOND_TICKS_PER_MINUTE,
                             EMBER_AF_OK_TO_HIBERNATE);
}

void emberAfSimpleMeteringClusterServerTickCallback(int8u endpoint) 
{
  emAfTestMeterTick(endpoint); //run test module
  emberAfScheduleClusterTick(endpoint,
                             ZCL_SIMPLE_METERING_CLUSTER_ID,
                             EMBER_AF_SERVER_CLUSTER_TICK,
                             MILLISECOND_TICKS_PER_MINUTE,
                             EMBER_AF_OK_TO_HIBERNATE);
}

boolean emberAfSimpleMeteringClusterGetProfileCallback(int8u intervalChannel,
                                                       int32u endTime,
                                                       int8u numberOfPeriods)
{
  return emAfTestMeterGetProfiles(intervalChannel, endTime, numberOfPeriods);
}

boolean emberAfSimpleMeteringClusterRequestFastPollModeCallback(int8u fastPollUpdatePeriod, 
                                                                int8u duration) 
{
  // A very simple example of fast polling.  When fast polling is requested we 
  // note the end time and any subsequent attempt to request
  // fast poll mode before the end time expires returns the same answer.  However
  // once the time has expired, another request will reset the time to 15
  // minutes.
  static int32u fastPollEndTimeUtc = 0;
  int8u  appliedUpdateRate = 5;

  if (emberAfGetCurrentTime() > fastPollEndTimeUtc) {
    emberAfSimpleMeteringClusterPrintln("Starting fast polling for 15 minutes");
    fastPollEndTimeUtc = emberAfGetCurrentTime() + (15 * 60);
  } else {
    emberAfSimpleMeteringClusterPrintln("Fast polling mode currently active.");
  }
  emberAfFillCommandSimpleMeteringClusterRequestFastPollModeResponse(appliedUpdateRate, 
                                                                     fastPollEndTimeUtc);
  emberAfSendResponse();
  return TRUE;
}
