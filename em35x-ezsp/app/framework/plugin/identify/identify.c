// *******************************************************************
// * identify.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the util
#include "../../include/af.h"

#if defined(EMBER_AF_PLUGIN_IDENTIFY_USE_LEDS) && !defined(EZSP_HOST)
#include "hal/hal.h"
#endif
// clusters specific header
#include "identify.h"

#ifdef ZCL_USING_IDENTIFY_CLUSTER_SERVER
static EmberAfStatus readIdentifyTime(int8u endpoint, int16u *identifyTime);
static EmberAfStatus writeIdentifyTime(int8u endpoint, int16u identifyTime);
static EmberStatus scheduleIdentifyTick(int8u endpoint);

void emberAfIdentifyClusterServerInitCallback(int8u endpoint)
{
  scheduleIdentifyTick(endpoint);
}

void emberAfIdentifyClusterServerTickCallback(int8u endpoint)
{
  int16u identifyTime;
  if (readIdentifyTime(endpoint, &identifyTime) == EMBER_ZCL_STATUS_SUCCESS
      && identifyTime > 0) {
#if defined(EMBER_AF_PLUGIN_IDENTIFY_USE_LEDS) && !defined(EZSP_HOST)
    halToggleLed(BOARDLED0);
    halToggleLed(BOARDLED1);
    halToggleLed(BOARDLED2);
    halToggleLed(BOARDLED3);
#endif //EZSP_HOST

    // This tick writes the new attribute, which will trigger the Attribute
    // Changed callback below, which in turn will schedule or cancel the tick.
    // Because of this, the tick does not have to be scheduled here.
    writeIdentifyTime(endpoint, identifyTime - 1);
  }
}

void emberAfIdentifyClusterServerAttributeChangedCallback(int8u endpoint,
                                                          EmberAfAttributeId attributeId)
{
  if (attributeId == ZCL_IDENTIFY_TIME_ATTRIBUTE_ID) {
    scheduleIdentifyTick(endpoint);
  }
}

boolean emberAfIdentifyClusterIdentifyCallback(int16u time)
{
  // This Identify callback writes the new attribute, which will trigger the
  // Attribute Changed callback above, which in turn will schedule or cancel the
  // tick.  Because of this, the tick does not have to be scheduled here.
  emberAfIdentifyClusterPrintln("RX identify:IDENTIFY 0x%2x", time);
  emberAfSendDefaultResponse(emberAfCurrentCommand(),
                             writeIdentifyTime(emberAfCurrentEndpoint(), time));
  return TRUE;
}

boolean emberAfIdentifyClusterIdentifyQueryCallback(void)
{
  EmberAfStatus status;
  int16u identifyTime;

  emberAfIdentifyClusterPrintln("RX identify:QUERY");

  // According to the 075123r02ZB, a device shall not send an Identify Query
  // Response if it is not currently identifying.  Instead, or if reading the
  // Identify Time attribute fails, send a Default Response.
  status = readIdentifyTime(emberAfCurrentEndpoint(), &identifyTime);
  if (status != EMBER_ZCL_STATUS_SUCCESS || identifyTime == 0) {
    emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
    return TRUE;
  }

  emberAfFillCommandIdentifyClusterIdentifyQueryResponse(identifyTime);
  emberAfSendResponse();
  return TRUE;
}

boolean emberAfIsDeviceIdentifying(int8u endpoint)
{
  int16u identifyTime;
  return (readIdentifyTime(endpoint, &identifyTime) == EMBER_ZCL_STATUS_SUCCESS
          && identifyTime > 0);
}

void emAfIdentifyPrintInfo(void)
{
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IDENTIFY_CLUSTER)
  int8u i;
  for (i = 0; i < emberAfEndpointCount(); ++i) {
    int8u endpoint = emberAfEndpointFromIndex(i);
    emberAfIdentifyClusterPrintln("Endpoint 0x%x is identifying: %p",
                                  endpoint,
                                  (emberAfIsDeviceIdentifying(endpoint)
                                   ? "TRUE"
                                   : "FALSE"));
  }
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IDENTIFY_CLUSTER)
}

static EmberAfStatus readIdentifyTime(int8u endpoint, int16u *identifyTime)
{
  EmberAfStatus status = emberAfReadAttribute(endpoint,
                                              ZCL_IDENTIFY_CLUSTER_ID,
                                              ZCL_IDENTIFY_TIME_ATTRIBUTE_ID,
                                              CLUSTER_MASK_SERVER,
                                              (int8u *)identifyTime,
                                              sizeof(*identifyTime),
                                              NULL); // data type
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IDENTIFY_CLUSTER)
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfIdentifyClusterPrintln("ERR: reading identify time %x", status);
  }
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IDENTIFY_CLUSTER)
  return status;
}

static EmberAfStatus writeIdentifyTime(int8u endpoint, int16u identifyTime)
{
  EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                               ZCL_IDENTIFY_CLUSTER_ID,
                                               ZCL_IDENTIFY_TIME_ATTRIBUTE_ID,
                                               CLUSTER_MASK_SERVER,
                                               (int8u *)&identifyTime,
                                               ZCL_INT16U_ATTRIBUTE_TYPE);
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IDENTIFY_CLUSTER)
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfIdentifyClusterPrintln("ERR: writing identify time %x", status);
  }
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_IDENTIFY_CLUSTER)
  return status;
}

static EmberStatus scheduleIdentifyTick(int8u endpoint)
{
  int16u identifyTime;
  if (readIdentifyTime(endpoint, &identifyTime) == EMBER_ZCL_STATUS_SUCCESS
      && identifyTime > 0) {
    return emberAfScheduleClusterTick(endpoint,
                                      ZCL_IDENTIFY_CLUSTER_ID,
                                      EMBER_AF_SERVER_CLUSTER_TICK,
                                      MILLISECOND_TICKS_PER_SECOND,
                                      EMBER_AF_OK_TO_HIBERNATE);
  } else {
    return emberAfDeactivateClusterTick(endpoint,
                                        ZCL_IDENTIFY_CLUSTER_ID,
                                        EMBER_AF_SERVER_CLUSTER_TICK);
  }
}
#endif //ZCL_USING_IDENTIFY_CLUSTER_SERVER
