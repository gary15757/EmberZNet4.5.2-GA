// *****************************************************************************
// * af-event.c
// *
// * Application event code that is common to both the SOC and EZSP platforms.
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include PLATFORM_HEADER     // Micro and compiler specific typedefs and macros
#include "../include/af.h"
#include "../gen/callback.h"
#include "af-event.h"
#include "stack/include/error.h"
#include "hal/hal.h"
#include "../security/crypto-state.h"
#ifdef EMBER_AF_ENABLE_FRAGMENTATION
#include "fragmentation.h"
#endif 

#include "app/framework/plugin/smart-energy-registration/smart-energy-registration.h"
#include "app/framework/plugin/test-harness/test-harness.h"

EmberAfEventSleepControl emAfDefaultSleepControl = EMBER_AF_OK_TO_HIBERNATE;

#ifdef ZA_DEVICE_IS_SLEEPY
int32u emAfCurrentAppTasks = 0;
int16u emAfLastAppTaskScheduleTime = 0;
#endif

#ifdef EMBER_AF_GENERATED_EVENT_CODE
  EMBER_AF_GENERATED_EVENT_CODE
#endif //EMBER_AF_GENERATED_EVENT_CODE

EmberEventData appEvents[] = {
#ifdef EMBER_AF_GENERATED_EVENTS
  EMBER_AF_GENERATED_EVENTS
#endif //EMBER_AF_GENERATED_EVENTS

  EMBER_KEY_ESTABLISHMENT_TEST_HARNESS_EVENT

  {NULL, NULL}
};

#if defined(EMBER_AF_GENERATED_EVENT_CONTEXT)
int16u appEventContextLength = EMBER_AF_EVENT_CONTEXT_LENGTH;
EmberAfEventContext appEventContext[] = {
  EMBER_AF_GENERATED_EVENT_CONTEXT
};
#endif //EMBER_AF_GENERATED_EVENT_CONTEXT


extern EmberEventControl emAfServiceDiscoveryEventControl;
extern void emAfServiceDiscoveryComplete(void);

extern EmberEventControl emAfMoveEventControl;
extern void emAfMoveEvent(void);

#ifdef EMBER_AF_PLUGIN_TRUST_CENTER_KEEPALIVE
extern EmberEventControl emAfPluginTrustCenterKeepaliveEventControl;
extern void emAfPluginTrustCenterKeepaliveTick(void);
#endif

#ifndef ZA_NO_REPORTING_OPTIMIZATION
extern EmberEventControl emAfReportTableEventControl;
extern void emberAfReportTableTick(void);
#endif

#if !defined(EZSP_HOST) && (defined(ZA_DEVICE_IS_SLEEPY) || defined(ZA_DEVICE_IS_NONSLEEPY_END_DEVICE))
extern EmberEventControl emAfPollEventControl;
extern void emAfPollEvent(void);
#endif 

EmberEventData afEvents[] = {
  {&emAfServiceDiscoveryEventControl, emAfServiceDiscoveryComplete},
  {&emAfMoveEventControl, emAfMoveEvent},
#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION
  {&emAfPluginSmartEnergyRegistrationEventControl, emAfPluginSmartEnergyRegistrationTick},
#endif
#ifdef EMBER_AF_PLUGIN_TRUST_CENTER_KEEPALIVE
  {&emAfPluginTrustCenterKeepaliveEventControl, emAfPluginTrustCenterKeepaliveTick},
#endif
#if !defined(EZSP_HOST) && (defined(ZA_DEVICE_IS_SLEEPY) || defined(ZA_DEVICE_IS_NONSLEEPY_END_DEVICE))
  {&emAfPollEventControl, emAfPollEvent},
#endif
#ifndef ZA_NO_REPORTING_OPTIMIZATION
  {&emAfReportTableEventControl, emberAfReportTableTick},
#endif
#ifdef EMBER_AF_ENABLE_FRAGMENTATION
  {&emAfFragmentationEventControl, emAfFragmentationAbortReception},
#endif
  {NULL, NULL}
};


void emberAfRunEvents(void) {
    
  // Don't run events while crypto operation is in progress
  // (BUGZID: 12127)
  if (emAfIsCryptoOperationInProgress()) {
    // DEBUG Bugzid: 11944
    emberAfCoreFlush();
    return;
  }

  emberRunEvents(appEvents);
  emberRunEvents(afEvents);
}

static EmberAfEventContext *emAfFindEventContext(int8u endpoint,
                                         int16u clusterId,
                                         boolean isClient) {
#if defined(EMBER_AF_GENERATED_EVENT_CONTEXT)
  int8u i;
  for (i = 0; i < appEventContextLength; i++) {
    EmberAfEventContext *context = &(appEventContext[i]);
    if (context->endpoint == endpoint &&
        context->clusterId == clusterId &&
        context->isClient == isClient) {
      return context;
    }
  }
#endif //EMBER_AF_GENERATED_EVENT_CONTEXT
  return NULL;
}

void emberAfSetDefaultSleepControl(EmberAfEventSleepControl control) {
  emAfDefaultSleepControl = control;
}

EmberAfEventSleepControl emberAfGetCurrentSleepControl() {
  EmberAfEventSleepControl sleepControl = emAfDefaultSleepControl;
#if defined(EMBER_AF_GENERATED_EVENT_CONTEXT)
  int8u i;
  for (i = 0; i < appEventContextLength; i++) {
    EmberAfEventContext *context = &(appEventContext[i]);
    if (context->eventControl->status
        && context->sleepControl > sleepControl) {
      sleepControl = context->sleepControl;
    }
  }
#endif //EMBER_AF_GENERATED_EVENT_CONTEXT
  return sleepControl;
}

EmberStatus emberAfEventControlSetDelay(EmberEventControl *eventControl, int32u timeMs)
{
  if (timeMs < MAX_SLEEP_UNITS) {
    emberEventControlSetDelayMS(*eventControl, (int16u)timeMs);
  } else if ((timeMs / MILLISECOND_TICKS_PER_QUARTERSECOND) < MAX_SLEEP_UNITS) {
    emberEventControlSetDelayQS(*eventControl,
                                (int16u)(timeMs / MILLISECOND_TICKS_PER_QUARTERSECOND));
  } else if ((timeMs / MILLISECOND_TICKS_PER_MINUTE) < MAX_SLEEP_UNITS) {
    emberEventControlSetDelayMinutes(*eventControl,
                                     (int16u)(timeMs / MILLISECOND_TICKS_PER_MINUTE));
  } else {
    return EMBER_BAD_ARGUMENT;
  }
  return EMBER_SUCCESS;
}

EmberStatus emberAfScheduleClusterTick( int8u endpoint, 
                                        int16u clusterId, 
                                        boolean isClient, 
                                        int32u timeMs, 
                                        EmberAfEventSleepControl sleepControl) {
  EmberAfEventContext *context = 
    emAfFindEventContext(endpoint, clusterId, isClient);
  if (context != NULL &&
      (emberAfEventControlSetDelay(context->eventControl, timeMs) == 
       EMBER_SUCCESS)) { 
    context->sleepControl = sleepControl;
    return EMBER_SUCCESS;
  }
  return EMBER_BAD_ARGUMENT;
}


int32u emberAfMsToNextEvent(int32u maxMs) {
  int32u msToNextApp = emberMsToNextEvent(appEvents, maxMs);
  int32u msToNextAf = emberMsToNextEvent(afEvents, maxMs);
  
  return ((msToNextApp < msToNextAf) ? msToNextApp : msToNextAf);
}

EmberStatus emberAfDeactivateClusterTick(int8u endpoint,
                                         int16u clusterId,
                                         boolean isClient) {
  EmberAfEventContext *context = 
    emAfFindEventContext(endpoint, clusterId, isClient);
  if (context != NULL) {
    emberEventControlSetInactive((*(context->eventControl)));
    return EMBER_SUCCESS;
  }
  return EMBER_BAD_ARGUMENT;
}

// Used to track when the device is allowed to hibernate
#ifdef ZA_DEVICE_IS_SLEEPY

void emberAfAddToCurrentAppTasks(int32u mask) {
  emAfCurrentAppTasks |= mask;
  emAfLastAppTaskScheduleTime = halCommonGetInt16uMillisecondTick();
}

void emberAfRemoveFromCurrentAppTasks(int32u mask) {
  emAfCurrentAppTasks &= (~mask);
  emAfLastAppTaskScheduleTime = 0;
}

boolean emberAfOkToHibernate(void) {
  // short cut so we're not always doing the elapsed time calculation
  if (!emAfCurrentAppTasks)
    return (emberAfGetCurrentSleepControl() == EMBER_AF_OK_TO_HIBERNATE);
  // otherwise check to see if anything timed out
  else if (elapsedTimeInt16u(emAfLastAppTaskScheduleTime, 
                             halCommonGetInt16uMillisecondTick()) > 
           (EMBER_AF_WAKE_TIMEOUT * MILLISECOND_TICKS_PER_QUARTERSECOND)) {
    emAfCurrentAppTasks &= ~EMBER_AF_WAKE_TIMEOUT_MASK;
    emAfLastAppTaskScheduleTime = 0;
  }
  return (!emAfCurrentAppTasks && 
            (emberAfGetCurrentSleepControl() == EMBER_AF_OK_TO_HIBERNATE));
}
#else //ZA_DEVICE_IS_SLEEPY
void emberAfAddToCurrentAppTasks(int32u mask) {}
void emberAfRemoveFromCurrentAppTasks(int32u mask) {}
boolean emberAfOkToHibernate(void) { return FALSE; }
#endif //ZA_DEVICE_IS_SLEEPY


// Used to calculate the duration and unit used by the host to set the sleep timer
void emAfGetTimerDurationAndUnitFromMS(int32u ms, int16u *duration, int8u* unit) {
  if (ms <= MAX_TIMER_UNITS_HOST) {
    *unit = EMBER_EVENT_MS_TIME;
    *duration = ms;
  } else if ((ms / MILLISECOND_TICKS_PER_QUARTERSECOND) <= 
	     MAX_TIMER_UNITS_HOST) {
    *unit = EMBER_EVENT_QS_TIME;
    *duration = ms / MILLISECOND_TICKS_PER_QUARTERSECOND;
  } else {
    *unit = EMBER_EVENT_MINUTE_TIME;
    if ((ms / (MILLISECOND_TICKS_PER_MINUTE)) <= 
	MAX_TIMER_UNITS_HOST)
      *duration = (ms / (MILLISECOND_TICKS_PER_MINUTE));
    else
      *duration = MAX_TIMER_UNITS_HOST;
  }
}

int32u emAfGetMSFromTimerDurationAndUnit(int16u duration, int8u unit) {
  int32u ms = 0;
  if (unit == EMBER_EVENT_MINUTE_TIME) {
    ms = (duration * 
	  MILLISECOND_TICKS_PER_MINUTE);
  } else if (unit == EMBER_EVENT_QS_TIME) {
    ms = (duration * 
	  MILLISECOND_TICKS_PER_QUARTERSECOND);
  } else {
    ms = duration;
  }
  return ms;
}
