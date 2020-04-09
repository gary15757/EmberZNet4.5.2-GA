// *******************************************************************
// * time-client.c
// *
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "../../util/common.h"
#include "time-client.h"

#ifdef ZCL_USING_TIME_CLUSTER_CLIENT
// The variable "time" represents seconds since the ZigBee epoch, which was 0
// hours, 0 minutes, 0 seconds, on the 1st of January, 2000 UTC.  The variable
// "tick" is the millsecond tick at which that time was set.  The variable
// "remainder" is used to track sub-second chunks of time when converting from
// ticks to seconds.
static int32u time, tick;
static int16u remainder;

void emberAfTimeClusterClientInitCallback(int8u endpoint)
{
  time = 0;
  tick = halCommonGetInt32uMillisecondTick();
  remainder = 0;
}

int32u emAfTimeClusterClientGetCurrentTime(void)
{
  // If the real time is available, report that.  Otherwise, calculate how much
  // time has elapsed since we last set the time.  That difference plus the old
  // time is our new time.  Remember the tick time right now too, so we can do
  // the same calculations again the next time we're asked for time.  Keep track
  // of the sub-second chunks of time during the conversion from ticks to
  // seconds so the clock doesn't lose time due to rounding.
  int32u currentTime = emberAfGetCurrentTimeCallback();
  if (currentTime == 0) {
    int32u elapsed, lastTick = tick;
    tick = halCommonGetInt32uMillisecondTick();
    elapsed = elapsedTimeInt32u(lastTick, tick);
    time += elapsed / MILLISECOND_TICKS_PER_SECOND;
    remainder += elapsed % MILLISECOND_TICKS_PER_SECOND;
    if (remainder >= MILLISECOND_TICKS_PER_SECOND) {
      time++;
      remainder -= MILLISECOND_TICKS_PER_SECOND;
    }
    return time;
  } else {
    return currentTime;
  }
}

void emAfTimeClusterClientSetCurrentTime(int32u utcTime)
{
  time = utcTime;
  tick = halCommonGetInt32uMillisecondTick();
}
#endif //ZCL_USING_TIME_CLUSTER_CLIENT
