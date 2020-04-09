// *******************************************************************
// * ias-wd-server.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the util
#include "../../util/common.h"

// clusters specific header
#include "ias-wd-server.h"

#ifdef ZCL_USING_IAS_WD_CLUSTER_SERVER
static void iasWdReportStrobe(void);
static void iasWdReportSiren(void);

// cluster specific data
typedef struct {
  int16u iasWdSirenTimeLeft;
  int16u iasWdStrobeTimeLeft;
} EmberAfIasWdState;

static EmberAfIasWdState state[MAX_ENDPOINT_COUNT];
static boolean ledsSet = TRUE;
static int8u PGM siren[] = {
  NOTE_B5, 2,
  NOTE_B4, 2,
  NOTE_B3, 2,
  0,       0
};

void emberAfIasWdClusterServerInitCallback(int8u endpoint)
{
  EmberAfIasWdState *s = &(state[emberAfIndexFromEndpoint(endpoint)]);
  s->iasWdSirenTimeLeft = 0;
  s->iasWdStrobeTimeLeft = 0;
}

static void scheduleIfNeeded(int8u endpoint) {
  EmberAfIasWdState *s = &(state[emberAfIndexFromEndpoint(endpoint)]);
  if ( s->iasWdSirenTimeLeft > 0 
       || s->iasWdStrobeTimeLeft > 0 ) {
    emberAfScheduleClusterTick(endpoint,
                               ZCL_IAS_WD_CLUSTER_ID,
                               EMBER_AF_SERVER_CLUSTER_TICK,
                               250,
                               EMBER_AF_OK_TO_HIBERNATE);
  } else {
    emberAfDeactivateClusterTick(endpoint,
                                 ZCL_IAS_WD_CLUSTER_ID,
                                 EMBER_AF_SERVER_CLUSTER_TICK);
  }
}

// When the siren and strobe counters have time left, the tick plays a sound
// and flashes the LEDs.  A real implementation would play different sounds
// based on the current warning or squawk mode.
void emberAfIasWdClusterServerTickCallback(int8u endpoint)
{
  EmberAfIasWdState *s = &(state[emberAfIndexFromEndpoint(endpoint)]);

  //emberAfIasWdClusterPrintln("siren %x, strobe %x",
  //                           s->iasWdSirenTimeLeft,
  //                           s->iasWdStrobeTimeLeft);
  // count down the strobe and siren by 1 tick
  if (s->iasWdSirenTimeLeft != 0) {
    iasWdReportSiren();
    s->iasWdSirenTimeLeft--;
  }
  if (s->iasWdStrobeTimeLeft != 0) {
    iasWdReportStrobe();
    s->iasWdStrobeTimeLeft--;
  }
  scheduleIfNeeded(endpoint);
}

boolean emberAfIasWdClusterStartWarningCallback(int8u warningInfo,
                                                int16u warningDuration)
{
  int8u warningMode = warningInfo & ZCL_WARNING_INFO_MODE_MASK;
  int8u strobe = warningInfo & ZCL_WARNING_INFO_STROBE_MASK;
  EmberAfIasWdState *s = &(state[emberAfIndexFromEndpoint(emberAfCurrentEndpoint())]);

  emberAfIasWdClusterPrint("RX: IAS WD START WARNING: ");

  switch (warningMode) {
  case ZCL_WARNING_INFO_STOP:
    emberAfIasWdClusterPrint("Stop");
    break;
  case ZCL_WARNING_INFO_BURGLAR:
    emberAfIasWdClusterPrint("Burglar");
    break;
  case ZCL_WARNING_INFO_FIRE:
    emberAfIasWdClusterPrint("Fire");
    break;
  case ZCL_WARNING_INFO_EMERGENCY:
    emberAfIasWdClusterPrint("Emergency");
    break;
  default:
    emberAfIasWdClusterPrint("Unknown (0x%x)", warningMode);
    break;
  }

  emberAfIasWdClusterPrint(", ");

  switch (strobe) {
  case ZCL_WARNING_INFO_NO_STROBE:
    emberAfIasWdClusterPrint("No strobe");
    break;
  case ZCL_WARNING_INFO_STROBE:
    emberAfIasWdClusterPrint("Use strobe");
    s->iasWdStrobeTimeLeft = warningDuration;
    break;
  default:
    emberAfIasWdClusterPrint("Unknown (0x%x)", strobe);
    break;
  }

  emberAfIasWdClusterPrint(", ");
  emberAfIasWdClusterPrintln("duration: 0x%2x", warningDuration);

  s->iasWdSirenTimeLeft = (warningMode == ZCL_WARNING_INFO_STOP
                           ? 0
                           : warningDuration);
  s->iasWdStrobeTimeLeft = (strobe == ZCL_WARNING_INFO_NO_STROBE
                           ? 0
                           : warningDuration);
  scheduleIfNeeded(emberAfCurrentEndpoint());
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

boolean emberAfIasWdClusterSquawkCallback(int8u squawkInfo)
{
  EmberAfStatus status;
  int8u squawkMode = squawkInfo & ZCL_SQUAWK_INFO_MODE_MASK;
  boolean strobe = squawkInfo & ZCL_SQUAWK_INFO_STROBE_MASK;
  int8u squawkLevel = squawkInfo & ZCL_SQUAWK_INFO_LEVEL_MASK;
  EmberAfIasWdState *s = &(state[emberAfIndexFromEndpoint(emberAfCurrentEndpoint())]);

  if (s->iasWdSirenTimeLeft != 0 || s->iasWdStrobeTimeLeft != 0) {
    emberAfIasWdClusterPrintln("IAS WD: warning in progress,"
                               " squawk not activated");
    status = EMBER_ZCL_STATUS_FAILURE;
  } else {
    emberAfIasWdClusterPrint("IAS WD: SQUAWK: ");

    switch (squawkMode) {
    case ZCL_SQUAWK_INFO_ARMED:
      emberAfIasWdClusterPrint("Armed");
      break;
    case ZCL_SQUAWK_INFO_DISARMED:
      emberAfIasWdClusterPrint("Disarmed");
      break;
    default:
      emberAfIasWdClusterPrint("Unknown (0x%x)", squawkMode);
      break;
    }

    emberAfIasWdClusterPrint(", ");

    switch (strobe) {
    case ZCL_SQUAWK_INFO_NO_STROBE:
      emberAfIasWdClusterPrint("No strobe");
      break;
    case ZCL_SQUAWK_INFO_STROBE:
      emberAfIasWdClusterPrint("Use strobe");
      break;
    default:
      emberAfIasWdClusterPrint("Unknown (0x%x)", strobe);
      break;
    }

    emberAfIasWdClusterPrint(", ");

    switch (squawkLevel) {
    case ZCL_SQUAWK_INFO_LOW:
      emberAfIasWdClusterPrintln("Low");
      break;
    case ZCL_SQUAWK_INFO_MEDIUM:
      emberAfIasWdClusterPrintln("Medium");
      break;
    case ZCL_SQUAWK_INFO_HIGH:
      emberAfIasWdClusterPrintln("High");
      break;
    case ZCL_SQUAWK_INFO_VERY_HIGH:
      emberAfIasWdClusterPrintln("Very High");
      break;
    default:
      emberAfIasWdClusterPrintln("Unknown (0x%x)", squawkLevel);
      break;
    }

    s->iasWdSirenTimeLeft = 1; // one-second squawk
    s->iasWdStrobeTimeLeft = (strobe == ZCL_SQUAWK_INFO_NO_STROBE ? 0 : 1);

    status = EMBER_ZCL_STATUS_SUCCESS;
  }
  scheduleIfNeeded(emberAfCurrentEndpoint());
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}

static void iasWdReportStrobe(void)
{
  emberAfIasWdClusterPrintln("IAS WD: Strobe report!");

  // only do the LEDs on the EM250, not on the EM260 host
#ifndef EZSP_HOST
  if (ledsSet) {
    halClearLed(BOARDLED0);
    halClearLed(BOARDLED1);
    halClearLed(BOARDLED2);
    halClearLed(BOARDLED3);
    ledsSet = FALSE;
  } else {
    halSetLed(BOARDLED0);
    halSetLed(BOARDLED1);
    halSetLed(BOARDLED2);
    halSetLed(BOARDLED3);
    ledsSet = TRUE;
  }
#endif //!EZSP_HOST
}

static void iasWdReportSiren(void)
{
  emberAfIasWdClusterPrintln("IAS WD: Siren report!");
  halPlayTune_P(siren, FALSE);
}
#endif //ZCL_USING_IAS_WD_CLUSTER_SERVER
