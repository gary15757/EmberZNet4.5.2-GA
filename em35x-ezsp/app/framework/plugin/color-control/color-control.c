// *******************************************************************
// * color-control.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the util
#include "../../util/common.h"

// clusters specific header
#include "color-control.h"

#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER
typedef struct {
  int8u hueCommand;
  int8u hueStart;
  int8u hueFinal;
  int8s hueDirection;
  int8u hueRate;
  int8u hueRateConsumed;
  int32u hueCommandCompletionTime;
  int8u saturationCommand;
  int8u saturationStart;
  int8u saturationFinal;
  int8s saturationDirection;
  int8u saturationRate;
  int8u saturationRateConsumed;
  int32u saturationCommandCompletionTime;
} ColorControlState;

static ColorControlState stateTable[MAX_ENDPOINT_COUNT];

static ColorControlState *getColorControlState(int8u endpoint);
static void colorControlClearRemainingTime(int8u endpoint);
static void colorControlReconsiderRemainingTime(int8u endpoint,
                                                int16u remainingTime);
static void colorControlSetHue(int8u endpoint, int8u hue);
static void colorControlSetSaturation(int8u endpoint, int8u saturation);
static void colorControlSetColorModeToZero(void);
static EmberAfStatus colorControlReadCurrentHue(int8u endpoint, int8u* hue);
static EmberAfStatus colorControlReadCurrentSaturation(int8u endpoint,
                                                       int8u* saturation);
static void colorControlProcessHue(int8u endpoint, int32u currentTime);
static void colorControlProcessSaturation(int8u endpoint, int32u currentTime);

static int8u getColorControlTickRate(ColorControlState *state);

static ColorControlState *getColorControlState(int8u endpoint)
{
  int8u index = emberAfIndexFromEndpoint(endpoint);
  return (index == 0xFF ? NULL : &stateTable[index]);
}

void emberAfColorControlClusterServerInitCallback(int8u endpoint)
{
  ColorControlState *state = getColorControlState(endpoint);
  if (state == NULL) {
    return;
  }

  state->hueCommand = ZCL_INVALID_COLOR_CONTROL_COMMAND_ID;
  state->hueStart = 0;
  state->hueFinal = 0;
  state->hueDirection = 0;
  state->hueRate = 0;
  state->hueRateConsumed = 0;
  state->hueCommandCompletionTime = 0;
  state->saturationCommand = ZCL_INVALID_COLOR_CONTROL_COMMAND_ID;
  state->saturationStart = 0;
  state->saturationFinal = 0;
  state->saturationDirection = 0;
  state->saturationRate = 0;
  state->saturationRateConsumed = 0;
  state->saturationCommandCompletionTime = 0;
}

// This function should only be called every 1/4 second
void emberAfColorControlClusterServerTickCallback(int8u endpoint)
{
  ColorControlState *state = getColorControlState(endpoint);
  int32u time = halCommonGetInt32uMillisecondTick();
  boolean timeResetFlag = FALSE;

  if (state == NULL) {
    return;
  }

  // Here we process movement.
  if (state->hueCommand != ZCL_INVALID_COLOR_CONTROL_COMMAND_ID) {
    // We need to process hue.
    colorControlProcessHue(endpoint, time);
    timeResetFlag = TRUE;
  }

  if (state->saturationCommand != ZCL_INVALID_COLOR_CONTROL_COMMAND_ID) {
    // We need to process saturation.
    colorControlProcessSaturation(endpoint, time);
    timeResetFlag = TRUE;
  }

  if (timeResetFlag) { // some commands were processed
    if (state->hueCommand == ZCL_INVALID_COLOR_CONTROL_COMMAND_ID 
        && state->saturationCommand == ZCL_INVALID_COLOR_CONTROL_COMMAND_ID) {
      // None of the remaining commands keep remaining time any more,
      // so clean it.
      colorControlClearRemainingTime(endpoint);
      return;
    }
  }

  //schedule the next tick
  emberAfScheduleClusterTick(endpoint,
                             ZCL_COLOR_CONTROL_CLUSTER_ID,
                             EMBER_AF_SERVER_CLUSTER_TICK,
                             getColorControlTickRate(state),
                             EMBER_AF_STAY_AWAKE);
  
}

static int8u getColorControlTickRate(ColorControlState *state) {
  if (state->hueCommand != ZCL_INVALID_COLOR_CONTROL_COMMAND_ID &&
      state->saturationCommand == ZCL_INVALID_COLOR_CONTROL_COMMAND_ID)
    return state->hueRate;
  else if (state->hueCommand == ZCL_INVALID_COLOR_CONTROL_COMMAND_ID &&
           state->saturationCommand != ZCL_INVALID_COLOR_CONTROL_COMMAND_ID)
    return state->saturationRate;
  else {
    if (state->hueRateConsumed < state->saturationRateConsumed) {
      int8u rr = state->hueRateConsumed;
      state->saturationRateConsumed -= rr;
      state->hueRateConsumed = 0;
      return rr;
    } else if (state->hueRateConsumed > state->saturationRateConsumed) {
      int8u rr = state->saturationRateConsumed;
      state->hueRateConsumed -= rr;
      state->saturationRateConsumed = 0;
      return rr;
    } else {
      int8u rr = state->hueRateConsumed;
      state->hueRateConsumed = 0;
      state->saturationRateConsumed = 0;
      return rr;
    }
  }
}

// Clear remaining time
static void colorControlClearRemainingTime(int8u endpoint)
{
  int16u data = 0xFFFF;
  EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                               ZCL_COLOR_CONTROL_CLUSTER_ID,
                                               ZCL_COLOR_CONTROL_REMAINING_TIME_ATTRIBUTE_ID,
                                               CLUSTER_MASK_SERVER,
                                               (int8u *)&data,
                                               ZCL_INT16U_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfColorControlClusterPrintln("ERR: writing remaining time %x", status);
    return;
  }
}

// This function will change the RemainingTime attribute value if
// the passed remaining time is LARGER than current remaining time.
static void colorControlReconsiderRemainingTime(int8u endpoint,
                                                int16u remainingTime)
{
  EmberAfStatus status;
  int16u currentValue;

  status = emberAfReadAttribute(endpoint,
                                ZCL_COLOR_CONTROL_CLUSTER_ID,
                                ZCL_COLOR_CONTROL_REMAINING_TIME_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&currentValue,
                                sizeof(currentValue),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfColorControlClusterPrintln("ERR: reading remaining time %x", status);
    return;
  }

  // we reset the value only if new remainingTime
  // is bigger than the current remainingTime
  //
  // Note that step commands do not touch this value, but leave it at 0xFFFF
  if (currentValue < remainingTime) {
    status = emberAfWriteAttribute(endpoint,
                                   ZCL_COLOR_CONTROL_CLUSTER_ID,
                                   ZCL_COLOR_CONTROL_REMAINING_TIME_ATTRIBUTE_ID,
                                   CLUSTER_MASK_SERVER,
                                   (int8u *)&remainingTime,
                                   ZCL_INT16U_ATTRIBUTE_TYPE);
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      emberAfColorControlClusterPrintln("ERR: writing remaining time %x",
                                        status);
      return;
    }
  }
}

// Sets the hue attribute
static void colorControlSetHue(int8u endpoint, int8u hue)
{
  EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                               ZCL_COLOR_CONTROL_CLUSTER_ID,
                                               ZCL_COLOR_CONTROL_CURRENT_HUE_ATTRIBUTE_ID,
                                               CLUSTER_MASK_SERVER,
                                               (int8u *)&hue,
                                               ZCL_INT8U_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfColorControlClusterPrintln("ERR: writing current hue %x", status); emberAfColorControlClusterFlush();
    return;
  }
  emberAfDebugPrintln("hue=%x", hue);
}

// Sets the saturation attribute
static void colorControlSetSaturation(int8u endpoint, int8u saturation)
{
  EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                               ZCL_COLOR_CONTROL_CLUSTER_ID,
                                               ZCL_COLOR_CONTROL_CURRENT_SATURATION_ATTRIBUTE_ID,
                                               CLUSTER_MASK_SERVER,
                                               (int8u *)&saturation,
                                               ZCL_INT8U_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfColorControlClusterPrintln("ERR: writing current saturation %x",
                                      status);
    return;
  }
  emberAfDebugPrintln("saturation=%x", saturation); 
}

static void colorControlSetColorModeToZero(void)
{
#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_COLOR_MODE_ATTRIBUTE
  // Set the optional Color Mode attribute to zero as per the spec.  If an
  // error occurs, log it, but ignore it.
  int8u colorMode = 0;
  EmberAfStatus status = emberAfWriteAttribute(emberAfCurrentEndpoint(),
                                               ZCL_COLOR_CONTROL_CLUSTER_ID, 
                                               ZCL_COLOR_CONTROL_COLOR_MODE_ATTRIBUTE_ID, 
                                               CLUSTER_MASK_SERVER,
                                               &colorMode,
                                               ZCL_ENUM8_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfColorControlClusterPrintln("ERR: writing color mode%x", status);
  }
  emberAfDebugPrintln("colorMode=%x", colorMode); emberAfColorControlClusterFlush();
#else
  emberAfDebugPrintln("no color mode attribute"); emberAfColorControlClusterFlush();
#endif //ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_COLOR_MODE_ATTRIBUTE
}

// returns a ZCL status, EMBER_ZCL_STATUS_SUCCESS when it works. Sets newHue to the
// current Hue attribute value
static EmberAfStatus colorControlReadCurrentHue(int8u endpoint, int8u* hue)
{
  EmberAfStatus status = emberAfReadAttribute(endpoint,
                                              ZCL_COLOR_CONTROL_CLUSTER_ID,
                                              ZCL_COLOR_CONTROL_CURRENT_HUE_ATTRIBUTE_ID,
                                              CLUSTER_MASK_SERVER,
                                              hue,
                                              sizeof(int8u),
                                              NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfColorControlClusterPrintln("ERR: reading current hue %x", status);
  }
  return status;
}

// returns a ZCL status, EMBER_ZCL_STATUS_SUCCESS when it works. Sets newHue to the
// current Hue attribute value
static EmberAfStatus colorControlReadCurrentSaturation(int8u endpoint,
                                                       int8u* saturation)
{
  EmberAfStatus status = emberAfReadAttribute(endpoint,
                                              ZCL_COLOR_CONTROL_CLUSTER_ID,
                                              ZCL_COLOR_CONTROL_CURRENT_SATURATION_ATTRIBUTE_ID,
                                              CLUSTER_MASK_SERVER,
                                              saturation,
                                              sizeof(int8u),
                                              NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfColorControlClusterPrintln("ERR: reading current saturation %x",
                                      status);
  }
  return status;
}

static void colorControlProcessHue(int8u endpoint, int32u currentTime)
{
  ColorControlState *state = getColorControlState(endpoint);
  EmberAfStatus status;
  int8u newHue;

  if (state == NULL) {
    return;
  }

  switch (state->hueCommand) {
  case ZCL_STEP_HUE_COMMAND_ID:
  case ZCL_MOVE_TO_HUE_COMMAND_ID:
  case ZCL_MOVE_TO_HUE_AND_SATURATION_COMMAND_ID:
    if (currentTime >= state->hueCommandCompletionTime) {
      colorControlSetHue(endpoint, state->hueFinal);
      state->hueCommand = ZCL_INVALID_COLOR_CONTROL_COMMAND_ID; // we're done.
      break;
    } else {
      colorControlReconsiderRemainingTime(endpoint,
                                         (int16u)(state->hueCommandCompletionTime
                                         - currentTime));
    }
  case ZCL_MOVE_HUE_COMMAND_ID:
    if (state->hueRate == 0) {
      break;
    }
    status = colorControlReadCurrentHue(endpoint, &newHue);
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      break;
    }
    if (state->hueDirection > 0) {
      newHue += (newHue == 0xFE ? 2 : 1);
    } else {
      newHue -= (newHue == 0 ? 2 : 1);
    }
    colorControlSetHue(endpoint, newHue);
  }
}

static void colorControlProcessSaturation(int8u endpoint, int32u currentTime)
{
  ColorControlState *state = getColorControlState(endpoint);
  EmberAfStatus status;
  int8u newSaturation;

  if (state == NULL) {
    return;
  }

  switch (state->saturationCommand) {
  case ZCL_STEP_SATURATION_COMMAND_ID:
  case ZCL_MOVE_TO_SATURATION_COMMAND_ID:
  case ZCL_MOVE_TO_HUE_AND_SATURATION_COMMAND_ID:
    if (currentTime >= state->saturationCommandCompletionTime) {
      colorControlSetSaturation(endpoint, state->saturationFinal);
      state->saturationCommand = ZCL_INVALID_COLOR_CONTROL_COMMAND_ID; // we're done.
      break;
    } else {
      colorControlReconsiderRemainingTime(endpoint,
                                         (int16u)(state->saturationCommandCompletionTime
                                         - currentTime));
    }
  case ZCL_MOVE_SATURATION_COMMAND_ID:
    if (state->saturationRate == 0) {
      break;
    }
    status = colorControlReadCurrentSaturation(endpoint, &newSaturation);
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      break;
    }
    if (state->saturationDirection > 0) {
      newSaturation += (newSaturation == 0xFE ? 2 : 1);
    } else {
      newSaturation -= (newSaturation == 0 ? 2 : 1);
    }
    colorControlSetSaturation(endpoint, newSaturation);
  }
}

/****************** COMMAND HANDLERS **********************/

// Move hue to a given hue, taking transitionTime until completed.
boolean emberAfColorControlClusterMoveToHueCallback(int8u hue,
                                                int8u direction,
                                                int16u transitionTime)
{
  ColorControlState *state = getColorControlState(emberAfCurrentEndpoint());
  EmberAfStatus status;
  int8u currentHue;

  emberAfColorControlClusterPrintln("ColorControl: MoveToHue (%x, %x, %2x)",
                                    hue,
                                    direction,
                                    transitionTime);

  if (state == NULL) {
    status = EMBER_ZCL_STATUS_FAILURE;
    goto send_default_response;
  }

  // TODO: If the color specified is not achievable by the hardware, then the
  // color shall not be set and a ZCL default response command shall be
  // generated with status code equal to INVALID_VALUE.

  status = colorControlReadCurrentHue(emberAfCurrentEndpoint(), &currentHue);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    goto send_default_response;
  }

  // As hue is effectively measured on a circle, the new hue may be moved to in
  // either direction.  The direction of hue change is given by the Direction
  // field. If Directionis "Shortest distance," the direction is taken that
  // involves the shortest path round the circle.  This case corresponds to
  // expected normal usage.  If Direction is "Longest distance," the direction
  // is taken that involves the longest path round the circle.  This case can be
  // used for "rainbow effects."  In both cases, if both distances are the same,
  // the Up direction shall be taken.
  switch (direction) {
  case EMBER_ZCL_HUE_DIRECTION_SHORTEST_DISTANCE:
    state->hueDirection = (hue - currentHue <= 127 ? 1 : -1);
    break;
  case EMBER_ZCL_HUE_DIRECTION_LONGEST_DISTANCE:
    state->hueDirection = (hue - currentHue >= 127 ? 1 : -1);
    break;
  case EMBER_ZCL_HUE_DIRECTION_UP:
    state->hueDirection = 1;
    break;
  case EMBER_ZCL_HUE_DIRECTION_DOWN:
    state->hueDirection = -1;
    break;
  default:
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
    goto send_default_response;
  }

  state->hueCommand = ZCL_MOVE_TO_HUE_COMMAND_ID;
  state->hueCommandCompletionTime = halCommonGetInt32uMillisecondTick() + transitionTime * 100;
  state->hueFinal = hue;
  state->hueStart = currentHue;
  colorControlReconsiderRemainingTime(emberAfCurrentEndpoint(), transitionTime);
  state->hueRate = (transitionTime * 100) / ((state->hueDirection == 1) ? 
                                             (state->hueFinal - state->hueStart) : 
                                             (state->hueStart - state->hueFinal));
  // Set the Color Mode attribute to zero as per the spec, ignoring any errors.
  colorControlSetColorModeToZero();

  //schedule the next tick
  if (emberAfScheduleClusterTick(emberAfCurrentEndpoint(),
                                 ZCL_COLOR_CONTROL_CLUSTER_ID,
                                 EMBER_AF_SERVER_CLUSTER_TICK,
                                 state->hueRate,
                                 EMBER_AF_STAY_AWAKE)
      != EMBER_SUCCESS)
    status = EMBER_ZCL_STATUS_SOFTWARE_FAILURE;
  else
    status = EMBER_ZCL_STATUS_SUCCESS;

  goto send_default_response;

send_default_response:
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}

// Move hue continuously at the given rate. If mode is stop, then stop.
boolean emberAfColorControlClusterMoveHueCallback(int8u moveMode, int8u rate)
{
  ColorControlState *state = getColorControlState(emberAfCurrentEndpoint());
  EmberAfStatus status;

  emberAfColorControlClusterPrintln("ColorControl: MoveHue (%x, %x)",
                                    moveMode,
                                    rate);

  if (state == NULL) {
    status = EMBER_ZCL_STATUS_FAILURE;
    goto send_default_response;
  }

  // TODO: If the color specified is not achievable by the hardware, then the
  // color shall not be set and a ZCL default response command shall be
  // generated with status code equal to INVALID_VALUE.

  if (rate == 0) {
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
    goto send_default_response;
  }

  switch (moveMode) {
  case EMBER_ZCL_HUE_MOVE_MODE_STOP:
    state->hueCommand = ZCL_INVALID_COLOR_CONTROL_COMMAND_ID;
    break;
  case EMBER_ZCL_HUE_MOVE_MODE_UP:
    state->hueDirection = 1;
    break;
  case EMBER_ZCL_HUE_MOVE_MODE_DOWN:
    state->hueDirection = -1;
    break;
  default:
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
    goto send_default_response;
  }
  
  state->hueCommand = ZCL_MOVE_HUE_COMMAND_ID;
  state->hueStart = state->hueFinal = 0xFF;
  state->hueRate = rate;

  // Set the Color Mode attribute to zero as per the spec, ignoring any errors.
  colorControlSetColorModeToZero();

  //schedule the next tick
  if (emberAfScheduleClusterTick(emberAfCurrentEndpoint(),
                                 ZCL_COLOR_CONTROL_CLUSTER_ID,
                                 EMBER_AF_SERVER_CLUSTER_TICK,
                                 state->hueRate,
                                 EMBER_AF_STAY_AWAKE)
      != EMBER_SUCCESS)
    status = EMBER_ZCL_STATUS_SOFTWARE_FAILURE;
  else
    status = EMBER_ZCL_STATUS_SUCCESS;

  goto send_default_response;

send_default_response:
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);

  return TRUE;
}

// Step hue by one step, taking time as specified.
boolean emberAfColorControlClusterStepHueCallback(int8u stepMode,
                                                  int8u stepSize,
                                                  int8u transitionTime)
{
  ColorControlState *state = getColorControlState(emberAfCurrentEndpoint());
  EmberAfStatus status;
  int8u currentHue;

  emberAfColorControlClusterPrintln("ColorControl: StepHue (%x, %x, %x)",
                                    stepMode,
                                    stepSize,
                                    transitionTime);

  if (state == NULL) {
    status = EMBER_ZCL_STATUS_FAILURE;
    goto send_default_response;
  }

  // TODO: If the color specified is not achievable by the hardware, then the
  // color shall not be set and a ZCL default response command shall be
  // generated with status code equal to INVALID_VALUE.

  status = colorControlReadCurrentHue(emberAfCurrentEndpoint(), &currentHue);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    goto send_default_response;
  }

  // Add or subtract the step size to/from the current hue to get the final hue.
  // However, the range for hues is 0x00 to 0xFE, so if we land on 0xFF or if we
  // roll past it, we have to add or subtract one to the final hue, effectively
  // skipping over the invalid 0xFF.
  switch (stepMode) {
  case EMBER_ZCL_HUE_STEP_MODE_UP:
    state->hueFinal = currentHue + stepSize;
    if (stepSize >= 0xFF - currentHue) {
      state->hueFinal++;
    }
    state->hueDirection = 1;
    break;
  case EMBER_ZCL_HUE_STEP_MODE_DOWN:
    state->hueFinal = currentHue - stepSize;
    if (stepSize > currentHue) {
      state->hueFinal--;
    }
    state->hueDirection = -1;
    break;
  default:
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
    goto send_default_response;
  }

  state->hueCommand = ZCL_STEP_HUE_COMMAND_ID;
  state->hueCommandCompletionTime = halCommonGetInt32uMillisecondTick() + transitionTime * 100;
  state->hueStart = currentHue;
  state->hueRate = (transitionTime * 100) / ((state->hueDirection == 1) ? 
                                             (state->hueFinal - state->hueStart) : 
                                             (state->hueStart - state->hueFinal));

  colorControlReconsiderRemainingTime(emberAfCurrentEndpoint(), transitionTime);

  // Set the Color Mode attribute to zero as per the spec, ignoring any errors.
  colorControlSetColorModeToZero();

  //schedule the next tick
  if (emberAfScheduleClusterTick(emberAfCurrentEndpoint(),
                                 ZCL_COLOR_CONTROL_CLUSTER_ID,
                                 EMBER_AF_SERVER_CLUSTER_TICK,
                                 state->hueRate,
                                 EMBER_AF_STAY_AWAKE)
      != EMBER_SUCCESS)
    status = EMBER_ZCL_STATUS_SOFTWARE_FAILURE;
  else
    status = EMBER_ZCL_STATUS_SUCCESS;

  goto send_default_response;

send_default_response:
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);

  return TRUE;
}

// Move saturation to a given saturation, taking transitionTime until completed.
boolean emberAfColorControlClusterMoveToSaturationCallback(int8u saturation,
                                                           int16u transitionTime)
{
  ColorControlState *state = getColorControlState(emberAfCurrentEndpoint());
  EmberAfStatus status;
  int8u currentSaturation;

  emberAfColorControlClusterPrintln("ColorControl: MoveToSaturation (%x, %2x)",
                                    saturation,
                                    transitionTime);

  if (state == NULL) {
    status = EMBER_ZCL_STATUS_FAILURE;
    goto send_default_response;
  }

  // TODO: If the color specified is not achievable by the hardware, then the
  // color shall not be set and a ZCL default response command shall be
  // generated with status code equal to INVALID_VALUE.

  status = colorControlReadCurrentSaturation(emberAfCurrentEndpoint(),
                                             &currentSaturation);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    goto send_default_response;
  }

  state->saturationCommand = ZCL_MOVE_TO_SATURATION_COMMAND_ID;
  state->saturationCommandCompletionTime = halCommonGetInt32uMillisecondTick() + ((int32u)transitionTime) * 100;
  state->saturationFinal = saturation;
  state->saturationStart = currentSaturation;
  state->saturationDirection = (state->saturationFinal - state->saturationStart <= 127 ? 1 : -1);
  state->saturationRate = (transitionTime * 100) / ((state->saturationDirection == 1) ? 
                                                    (state->saturationFinal - state->saturationStart) : 
                                                    (state->saturationStart - state->saturationFinal));
  colorControlReconsiderRemainingTime(emberAfCurrentEndpoint(), transitionTime);


  // Set the Color Mode attribute to zero as per the spec, ignoring any errors.
  colorControlSetColorModeToZero();

  //schedule the next tick
  if (emberAfScheduleClusterTick(emberAfCurrentEndpoint(),
                                 ZCL_COLOR_CONTROL_CLUSTER_ID,
                                 EMBER_AF_SERVER_CLUSTER_TICK,
                                 state->saturationRate,
                                 EMBER_AF_STAY_AWAKE)
      != EMBER_SUCCESS)
    status = EMBER_ZCL_STATUS_SOFTWARE_FAILURE;
  else
    status = EMBER_ZCL_STATUS_SUCCESS;

  goto send_default_response;

send_default_response:
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);

  return TRUE;
}

// Move sat continuously at the given rate. If mode is stop, then stop.
boolean emberAfColorControlClusterMoveSaturationCallback(int8u moveMode, int8u rate)
{
  ColorControlState *state = getColorControlState(emberAfCurrentEndpoint());
  EmberAfStatus status;

  emberAfColorControlClusterPrintln("ColorControl: MoveSaturation (%x, %x)",
                                    moveMode,
                                    rate);

  if (state == NULL) {
    status = EMBER_ZCL_STATUS_FAILURE;
    goto send_default_response;
  }

  // TODO: If the color specified is not achievable by the hardware, then the
  // color shall not be set and a ZCL default response command shall be
  // generated with status code equal to INVALID_VALUE.

  if (rate == 0) {
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
    goto send_default_response;
  }

  switch (moveMode) {
  case EMBER_ZCL_SATURATION_MOVE_MODE_STOP:
    state->saturationCommand = ZCL_INVALID_COLOR_CONTROL_COMMAND_ID;
    break;
  case EMBER_ZCL_SATURATION_MOVE_MODE_UP:
    state->saturationDirection = 1;
    break;
  case EMBER_ZCL_SATURATION_MOVE_MODE_DOWN:
    state->saturationDirection = -1;
    break;
  default:
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
    goto send_default_response;
  }

  state->saturationCommand = ZCL_MOVE_SATURATION_COMMAND_ID;
  state->saturationFinal = state->saturationStart = 0xFF;
  state->saturationRate = rate;

  // Set the Color Mode attribute to zero as per the spec, ignoring any errors.
  colorControlSetColorModeToZero();

  //schedule the next tick
  if (emberAfScheduleClusterTick(emberAfCurrentEndpoint(),
                                 ZCL_COLOR_CONTROL_CLUSTER_ID,
                                 EMBER_AF_SERVER_CLUSTER_TICK,
                                 state->saturationRate,
                                 EMBER_AF_STAY_AWAKE)
      != EMBER_SUCCESS)
    status = EMBER_ZCL_STATUS_SOFTWARE_FAILURE;
  else
    status = EMBER_ZCL_STATUS_SUCCESS;
  goto send_default_response;

send_default_response:
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);

  return TRUE;
}

// Step sat by one step, taking time as specified.
boolean emberAfColorControlClusterStepSaturationCallback(int8u stepMode,
                                                         int8u stepSize,
                                                         int8u transitionTime)
{
  ColorControlState *state = getColorControlState(emberAfCurrentEndpoint());
  EmberAfStatus status;
  int8u currentSaturation;

  emberAfColorControlClusterPrintln("ColorControl: StepSaturation (%x, %x, %x)",
                                    stepMode,
                                    stepSize,
                                    transitionTime);

  if (state == NULL) {
    status = EMBER_ZCL_STATUS_FAILURE;
    goto send_default_response;
  }

  // TODO: If the color specified is not achievable by the hardware, then the
  // color shall not be set and a ZCL default response command shall be
  // generated with status code equal to INVALID_VALUE.

  status = colorControlReadCurrentSaturation(emberAfCurrentEndpoint(),
                                             &currentSaturation);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    goto send_default_response;
  }

  // Add or subtract the step size to/from the current saturation to get the
  // final saturation.  However, the range for saturations is 0x00 to 0xFE, so
  // don't increment or decrement past those bounds.
  switch (stepMode) {
  case EMBER_ZCL_SATURATION_STEP_MODE_UP:
    state->saturationFinal = (stepSize > 0xFE - currentSaturation
                              ? 0xFE
                              : currentSaturation + stepSize);
    state->saturationDirection = 1;
    break;
  case EMBER_ZCL_SATURATION_STEP_MODE_DOWN:
    state->saturationFinal = (stepSize > currentSaturation
                              ? 0x00
                              : currentSaturation - stepSize);
    state->saturationDirection = -1;
    break;
  default:
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
    goto send_default_response;
  }

  state->saturationCommand = ZCL_STEP_SATURATION_COMMAND_ID;
  state->saturationCommandCompletionTime = halCommonGetInt32uMillisecondTick() + ((int32u)transitionTime) * 100;
  state->saturationStart = currentSaturation;
  state->saturationRate = (transitionTime * 100) / ((state->saturationDirection == 1) ? 
                                                    (state->saturationFinal - state->saturationStart) : 
                                                    (state->saturationStart - state->saturationFinal));

  colorControlReconsiderRemainingTime(emberAfCurrentEndpoint(), transitionTime);

  // Set the Color Mode attribute to zero as per the spec, ignoring any errors.
  colorControlSetColorModeToZero();

  //schedule the next tick
  if (emberAfScheduleClusterTick(emberAfCurrentEndpoint(),
                                 ZCL_COLOR_CONTROL_CLUSTER_ID,
                                 EMBER_AF_SERVER_CLUSTER_TICK,
                                 state->saturationRate,
                                 EMBER_AF_STAY_AWAKE)
      != EMBER_SUCCESS)
    status = EMBER_ZCL_STATUS_SOFTWARE_FAILURE;
  else
    status = EMBER_ZCL_STATUS_SUCCESS;

  goto send_default_response;

send_default_response:
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);

  return TRUE;
}

// Move hue and saturation to a given values, taking time as specified.
boolean emberAfColorControlClusterMoveToHueAndSaturationCallback(int8u hue,
                                                                 int8u saturation,
                                                                 int16u transitionTime)
{
  ColorControlState *state = getColorControlState(emberAfCurrentEndpoint());
  EmberAfStatus status;
  int8u currentSaturation, currentHue;

  emberAfColorControlClusterPrintln("ColorControl: MoveToHueAndSaturation (%x, %x, %2x)",
                                    hue,
                                    saturation,
                                    transitionTime);

  if (state == NULL) {
    status = EMBER_ZCL_STATUS_FAILURE;
    goto send_default_response;
  }

  // TODO: If the color specified is not achievable by the hardware, then the
  // color shall not be set and a ZCL default response command shall be
  // generated with status code equal to INVALID_VALUE.

  status = colorControlReadCurrentSaturation(emberAfCurrentEndpoint(),
                                             &currentSaturation);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    goto send_default_response;
  }

  status = colorControlReadCurrentHue(emberAfCurrentEndpoint(), &currentHue);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    goto send_default_response;
  }

  state->hueCommand = ZCL_MOVE_TO_HUE_AND_SATURATION_COMMAND_ID;
  state->hueCommandCompletionTime = halCommonGetInt32uMillisecondTick() + ((int32u)transitionTime) * 100;
  state->hueFinal = hue;
  state->hueStart = currentHue;
  state->hueDirection = (state->hueFinal - state->hueStart <= 127 ? 1 : -1);

  state->saturationCommand = ZCL_MOVE_TO_HUE_AND_SATURATION_COMMAND_ID;
  state->saturationCommandCompletionTime = state->hueCommandCompletionTime;
  state->saturationFinal = saturation;
  state->saturationStart = currentSaturation;
  state->saturationDirection = (state->saturationFinal - state->saturationStart <= 127 ? 1 : -1);

  state->saturationRate = (transitionTime * 100) / ((state->saturationDirection == 1) ? 
                                                    (state->saturationFinal - state->saturationStart) : 
                                                    (state->saturationStart - state->saturationFinal));

  state->hueRate = (transitionTime * 100) / ((state->hueDirection == 1) ? 
                                             (state->hueFinal - state->hueStart) : 
                                             (state->hueStart - state->hueFinal));

  state->saturationRateConsumed = state->saturationRate;
  state->hueRateConsumed = state->hueRate;

  colorControlReconsiderRemainingTime(emberAfCurrentEndpoint(), transitionTime);

  // Set the Color Mode attribute to zero as per the spec, ignoring any errors.
  colorControlSetColorModeToZero();

  //schedule the next tick
  if (emberAfScheduleClusterTick(emberAfCurrentEndpoint(),
                                 ZCL_COLOR_CONTROL_CLUSTER_ID,
                                 EMBER_AF_SERVER_CLUSTER_TICK,
                                 getColorControlTickRate(state),
                                 EMBER_AF_STAY_AWAKE)
      != EMBER_SUCCESS)
    status = EMBER_ZCL_STATUS_SOFTWARE_FAILURE;
  else
    status = EMBER_ZCL_STATUS_SUCCESS;

  goto send_default_response;

send_default_response:
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);

  return TRUE;
}
#endif //ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER
