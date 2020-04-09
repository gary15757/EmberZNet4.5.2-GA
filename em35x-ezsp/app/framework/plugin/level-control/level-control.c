// *******************************************************************
// * level-control.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the util
#include "../../include/af.h"
#include "../../util/attribute-storage.h"

// clusters specific header
#include "level-control.h"

#ifdef EMBER_AF_PLUGIN_SCENES
  #include "../scenes/scenes.h"
#endif //EMBER_AF_PLUGIN_SCENES

#ifdef EMBER_AF_PLUGIN_ON_OFF
  #include "../on-off/on-off.h"
#endif //EMBER_AF_PLUGIN_ON_OFF

#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
typedef struct {
  boolean active;
  int8u commandId;
  int8u tickCount;
  int8u moveToLevel;
  int32u transTime;      // transition time in milliseconds
  int8u rateMovePerTick; // how much to move per tick
  boolean moveToLevelUp; // TRUE for up, FALSE for down
  int16u numTickForMove;
  int32u diff;
  int8u moveMode;
  int8u moveRate;        // in units per second
  int8u stepSize;
} EmberAfLevelControlState;

static EmberAfLevelControlState stateTable[MAX_ENDPOINT_COUNT];

static EmberAfLevelControlState *emAfGetLevelControlState(int8u endpoint);
static int8u afLevelControlFigureMoveAmount(int32u totalAmountToMove,
                                            int16u numTicksToMove);

static void emAfLevelControlClusterMoveToLevelHandler(int8u commandId,
                                                      int8u level,
                                                      int16u transitionTime);
static void emAfLevelControlClusterMoveHandler(int8u commandId,
                                               int8u moveMode,
                                               int8u rate);
static void emAfLevelControlClusterStepHandler(int8u commandId,
                                               int8u stepMode,
                                               int8u stepSize,
                                               int16u transitionTime);
static void emAfLevelControlClusterStopHandler(int8u commandId);

static void setOnOffValue(int8u endpoint, boolean onOff);

static void emAfActivateLevelControl(EmberAfLevelControlState *state, 
                                     int8u endpoint) {
  state->active = TRUE;
  // schedule the first tick
  emberAfScheduleClusterTick(endpoint, 
                             ZCL_LEVEL_CONTROL_CLUSTER_ID, 
                             EMBER_AF_SERVER_CLUSTER_TICK, 
                             0x01, 
                             EMBER_AF_STAY_AWAKE);
}

static void emAfDeactivateLevelControl(EmberAfLevelControlState *state) {
  state->active = FALSE;
}

static EmberAfLevelControlState *emAfGetLevelControlState(int8u endpoint)
{
  int8u index = emberAfIndexFromEndpoint(endpoint);
  return (index == 0xFF ? NULL : &stateTable[index]);
}

void emberAfLevelControlClusterServerInitCallback(int8u endpoint)
{
  EmberAfLevelControlState *state = emAfGetLevelControlState(endpoint);
  if (state == NULL) {
    return;
  }
  emAfDeactivateLevelControl(state);
}

void emberAfLevelControlClusterServerTickCallback(int8u endpoint)
{
  EmberAfLevelControlState *state = emAfGetLevelControlState(endpoint);
  EmberAfStatus status;
  int8u currentLevel, setNewLevel;
  int16u newLevel;
  int8u moveRatePerTick, moveRatePerSecAdjust;

  if (state == NULL || !state->active) {
    return;
  } else {
    // reschedule the tick
    emberAfScheduleClusterTick(endpoint, 
                               ZCL_LEVEL_CONTROL_CLUSTER_ID, 
                               EMBER_AF_SERVER_CLUSTER_TICK, 
                               LC_TICK_TIME, 
                               EMBER_AF_STAY_AWAKE);
  }

  // increment tick count - this allows us to act differently on each
  // second - this accounts for rounding so we dont have big jumps at the
  // end of a transition, any jumps are at the end of each second.
  state->tickCount++;

  // read the attribute and error out if cant read it
  status = emberAfReadAttribute(endpoint,
                                ZCL_LEVEL_CONTROL_CLUSTER_ID,
                                ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&currentLevel,
                                sizeof(currentLevel),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfLevelControlClusterPrintln("ERR: reading current level %x", status);
    return;
  }
  // if something goes wrong, we will set the newLevel to the currentLevel
  newLevel = currentLevel;

  // handle actions: move-to-level, move, or step
  switch (state->commandId) {

    // we treat the step the same as a move to level
  case ZCL_MOVE_TO_LEVEL_COMMAND_ID:
  case ZCL_MOVE_TO_LEVEL_WITH_ON_OFF_COMMAND_ID:
    {
      int8u amountToMove;

      // check if we are at the level requested yet
      if (currentLevel == state->moveToLevel) {
        // we are done, stop moving
        emAfDeactivateLevelControl(state);
        if (currentLevel == 0) {
          if (state->commandId == ZCL_MOVE_TO_LEVEL_WITH_ON_OFF_COMMAND_ID) {
            setOnOffValue(endpoint, FALSE);
          }
        }
        return;
      }

      // determine how much to move by this tick
      amountToMove = afLevelControlFigureMoveAmount(state->diff, 
                                                    state->numTickForMove);

      // adjust by the proper amount, either up or down
      if (state->moveToLevelUp) {
        if (state->commandId == ZCL_MOVE_TO_LEVEL_WITH_ON_OFF_COMMAND_ID) {
          setOnOffValue(endpoint, TRUE);
        }
        newLevel = currentLevel + amountToMove;
        if (newLevel > state->moveToLevel) {
          newLevel = state->moveToLevel;
        }
      } else {
        newLevel = currentLevel - amountToMove;
        if (newLevel < state->moveToLevel) {
          newLevel = state->moveToLevel;
        }
        if (newLevel == 0) {
          if (state->commandId == ZCL_MOVE_TO_LEVEL_WITH_ON_OFF_COMMAND_ID) {
            setOnOffValue(endpoint, FALSE);
          }
        }
      }

      // decrement the variables keeping track of how much more left to go
      state->numTickForMove--;
      state->diff -= amountToMove;

      emberAfLevelControlClusterPrint("tick %x move from %x to %2x ",
                                      state->tickCount,
                                      currentLevel,
                                      newLevel);
      emberAfLevelControlClusterPrintln("(diff %p%x)",
                                        state->moveToLevelUp ? "+" : "-",
                                        amountToMove);
      emberAfLevelControlClusterFlush();
    }
    break;

  case ZCL_STEP_COMMAND_ID:
  case ZCL_STEP_WITH_ON_OFF_COMMAND_ID:
    // check if we are at the level requested yet
    if (currentLevel == state->moveToLevel) {
      // we are done, stop moving
      emAfDeactivateLevelControl(state);
      if (currentLevel == 0) {
        if (state->commandId == ZCL_STEP_WITH_ON_OFF_COMMAND_ID) {
          setOnOffValue(endpoint, FALSE);
        }
      }
      return;
    }

    // if the trans time is less than the tick time, move to the new level...
    if (state->transTime < (int32u)LC_TICK_TIME) {
      newLevel = state->moveToLevel;
    }
    // ...otherwise, increase by the normal rate amount
    else {
      // adding
      if (state->moveToLevelUp) {
        if (state->commandId == ZCL_STEP_WITH_ON_OFF_COMMAND_ID) {
          setOnOffValue(endpoint, TRUE);
        }
        newLevel = currentLevel + state->rateMovePerTick;
        // dont let the newLevel go above the target
        if (newLevel > state->moveToLevel) {
          newLevel = state->moveToLevel;
          emAfDeactivateLevelControl(state);
        }
      } else {
        newLevel = currentLevel - state->rateMovePerTick;
        // dont let the newLevel go below the target
        // unsigned, the number wraps which means the high byte gets a value
        if (HIGH_BYTE(newLevel) > 0) {
          newLevel = state->moveToLevel;
          emAfDeactivateLevelControl(state);
          if (state->commandId == ZCL_STEP_WITH_ON_OFF_COMMAND_ID) {
            setOnOffValue(endpoint, FALSE);
          }
        }
      }

      state->transTime = state->transTime - LC_TICK_TIME;
    }
    emberAfLevelControlClusterPrintln("tick %x move from %x to %2x",
                                      state->tickCount,
                                      currentLevel,
                                      newLevel);
    break;

  case ZCL_MOVE_COMMAND_ID:
  case ZCL_MOVE_WITH_ON_OFF_COMMAND_ID:
    // TODO: If the Rate field is 0xff, the device should move as fast as it is
    // able.

    // rate is specified in units per second - determine how many to adjust
    // for each tick and an adjustment factor (if any) on each second
    moveRatePerTick = state->moveRate / LC_TICKS_PER_SECOND;
    moveRatePerSecAdjust = state->moveRate - (LC_TICKS_PER_SECOND * moveRatePerTick);

    // adjust either up or down
    if (state->moveMode == EMBER_ZCL_MOVE_MODE_UP) {
      if (state->commandId == ZCL_MOVE_WITH_ON_OFF_COMMAND_ID) {
        setOnOffValue(endpoint, TRUE);
      }
      
      newLevel = currentLevel + moveRatePerTick;
      // adjust on each second
      if ((state->tickCount + 1) % LC_TICKS_PER_SECOND == 0) {
        newLevel += moveRatePerSecAdjust;
      }
      // make sure we dont go over the max
      if (newLevel > 0x00FF) {
        newLevel = 0x00FF;
        emAfDeactivateLevelControl(state);
      }
    }
    else if (state->moveMode == EMBER_ZCL_MOVE_MODE_DOWN) {
      newLevel = currentLevel - moveRatePerTick;
      // adjust on each second
      if ((state->tickCount + 1) % LC_TICKS_PER_SECOND == 0) {
        newLevel -= moveRatePerSecAdjust;
      }
      // make sure we dont go under 0
      // unsigned, the number wraps which means the high byte gets a value
      if (HIGH_BYTE(newLevel) > 0) {
        newLevel = 0;
        emAfDeactivateLevelControl(state);
        if (state->commandId == ZCL_MOVE_WITH_ON_OFF_COMMAND_ID) {
          setOnOffValue(endpoint, FALSE);
        }
      }
    }
    emberAfLevelControlClusterPrintln("tick %x, move from %x to newLevel %2x",
                                      state->tickCount,
                                      currentLevel,
                                      newLevel);
    break;
  }

  // newLevel is 2 bytes to detect rollover in either direction
  // need to make it 1 byte to pass to the write attributes call
  setNewLevel = LOW_BYTE(newLevel);

  // set the current level, implement a callback if you want
  // hardware action at this point.
  status = emberAfWriteAttribute(endpoint,
                                 ZCL_LEVEL_CONTROL_CLUSTER_ID,
                                 ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,
                                 CLUSTER_MASK_SERVER,
                                 (int8u *)&setNewLevel,
                                 ZCL_INT8U_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfLevelControlClusterPrintln("Err: writing current level %x", status);
  }

#ifdef EMBER_AF_PLUGIN_SCENES
  // the scene has been changed (the value of level has changed) so
  // the current scene as descibed in the attribute table is invalid,
  // so mark it as invalid (just writes the valid/invalid attribute)
  if (emberAfContainsServer(endpoint, ZCL_SCENES_CLUSTER_ID)) {
    emberAfScenesMakeInvalid(endpoint);
  }
#endif //EMBER_AF_PLUGIN_SCENES
}

// internal helper function
static int8u afLevelControlFigureMoveAmount(int32u totalAmountToMove,
                                            int16u numTicksToMove)
{
  // the return value
  int8u amountToMove = 0;

  // if this is the last tick or the num ticks passed in is zero
  // then just return the whole amount
  if (numTicksToMove == 0 || numTicksToMove == 1) {
    return BYTE_0(totalAmountToMove);
  }

  // get the whole number amount to move up by
  while (totalAmountToMove > numTicksToMove) {
    totalAmountToMove -= numTicksToMove;
    amountToMove++;
  }

  // the remainder tells us if we go up by 1 more for this tick or not
  if (((int16u)(totalAmountToMove & 0xFFFF)) > (numTicksToMove >> 1)) {
    amountToMove++;
  }

  return amountToMove;
}

static void calculateTickParameters(EmberAfLevelControlState *state)
{
  // figure out the number of ticks the change will happen over
  state->tickCount = 0;
  state->numTickForMove = (state->transTime + LC_TICK_TIME - 1) / LC_TICK_TIME;
  if (state->numTickForMove == 0) {
    state->numTickForMove = 1;
  }

  // get the rate per tick
  // get this by dividing diff we want to move by the number of ticks we need
  // to move.
  state->rateMovePerTick = BYTE_0((int32u)(state->diff / state->numTickForMove));

  // if the rate per second is 0 then make it one, we dont deal
  // well with rates less than 1 per sec
  if (state->rateMovePerTick == 0) {
    state->rateMovePerTick = 1;
  }
}

static void setOnOffValue(int8u endpoint, boolean onOff)
{
#ifdef EMBER_AF_PLUGIN_ON_OFF
  if (emberAfContainsServer(endpoint, ZCL_ON_OFF_CLUSTER_ID)) {
    emberAfLevelControlClusterPrintln("Setting on/off to %p due to level change",
                                      onOff ? "ON" : "OFF");
    emberAfOnOffSetValue(endpoint,
                         (onOff ? ZCL_ON_COMMAND_ID : ZCL_OFF_COMMAND_ID),
                         TRUE);
  }
#endif // EMBER_AF_PLUGIN_ON_OFF
}

boolean emberAfLevelControlClusterMoveToLevelCallback(int8u level,
                                                  int16u transitionTime)
{
  emberAfLevelControlClusterPrintln("%pMOVE_TO_LEVEL %x %2x",
                                    "RX level-control:",
                                    level,
                                    transitionTime);
  emAfLevelControlClusterMoveToLevelHandler(ZCL_MOVE_TO_LEVEL_COMMAND_ID,
                                            level,
                                            transitionTime);
  return TRUE;
}

boolean emberAfLevelControlClusterMoveToLevelWithOnOffCallback(int8u level,
                                                           int16u transitionTime)
{
  emberAfLevelControlClusterPrintln("%pMOVE_TO_LEVEL_WITH_ON_OFF %x %2x",
                                    "RX level-control:",
                                    level,
                                    transitionTime);
  emAfLevelControlClusterMoveToLevelHandler(ZCL_MOVE_TO_LEVEL_WITH_ON_OFF_COMMAND_ID,
                                            level,
                                            transitionTime);
  return TRUE;
}

boolean emberAfLevelControlClusterMoveCallback(int8u moveMode, int8u rate)
{
  emberAfLevelControlClusterPrintln("%pMOVE %x %x",
                                    "RX level-control:",
                                    moveMode,
                                    rate);
  emAfLevelControlClusterMoveHandler(ZCL_MOVE_COMMAND_ID, moveMode, rate);
  return TRUE;
}

boolean emberAfLevelControlClusterMoveWithOnOffCallback(int8u moveMode, int8u rate)
{
  emberAfLevelControlClusterPrintln("%pMOVE_WITH_ON_OFF %x %x",
                                    "RX level-control:",
                                    moveMode,
                                    rate);
  emAfLevelControlClusterMoveHandler(ZCL_MOVE_WITH_ON_OFF_COMMAND_ID,
                                     moveMode,
                                     rate);
  return TRUE;
}

boolean emberAfLevelControlClusterStepCallback(int8u stepMode,
                                           int8u stepSize,
                                           int16u transitionTime)
{
  emberAfLevelControlClusterPrintln("%pSTEP %x %x %2x",
                                    "RX level-control:",
                                    stepMode,
                                    stepSize,
                                    transitionTime);
  emAfLevelControlClusterStepHandler(ZCL_STEP_COMMAND_ID,
                                     stepMode,
                                     stepSize,
                                     transitionTime);
  return TRUE;
}

boolean emberAfLevelControlClusterStepWithOnOffCallback(int8u stepMode,
                                                    int8u stepSize,
                                                    int16u transitionTime)
{
  emberAfLevelControlClusterPrintln("%pSTEP_WITH_ON_OFF %x %x %2x",
                                    "RX level-control:",
                                    stepMode,
                                    stepSize,
                                    transitionTime);
  emAfLevelControlClusterStepHandler(ZCL_STEP_WITH_ON_OFF_COMMAND_ID,
                                     stepMode,
                                     stepSize,
                                     transitionTime);
  return TRUE;
}

boolean emberAfLevelControlClusterStopCallback(void)
{
  emberAfLevelControlClusterPrintln("%pSTOP", "RX level-control:");
  emAfLevelControlClusterStopHandler(ZCL_STOP_COMMAND_ID);
  return TRUE;
}

boolean emberAfLevelControlClusterStopWithOnOffCallback(void)
{
  emberAfLevelControlClusterPrintln("%pSTOP_WITH_ON_OFF", "RX level-control:");
  emAfLevelControlClusterStopHandler(ZCL_STOP_WITH_ON_OFF_COMMAND_ID);
  return TRUE;
}

static void emAfLevelControlClusterMoveToLevelHandler(int8u commandId,
                                                      int8u level,
                                                      int16u transitionTime)
{
  EmberAfLevelControlState *state = emAfGetLevelControlState(emberAfCurrentEndpoint());
  EmberAfStatus status;
  int8u currentLevel;

  if (state == NULL) {
    status = EMBER_ZCL_STATUS_FAILURE;
    goto send_default_response;
  }

  // Cancel any currently active command before fiddling with the state.
  emAfDeactivateLevelControl(state);

  status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                ZCL_LEVEL_CONTROL_CLUSTER_ID,
                                ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&currentLevel,
                                sizeof(currentLevel),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfLevelControlClusterPrintln("ERR: reading current level %x", status);
    goto send_default_response;
  }

  // Keep the new level within range.
  if (level >= LEVEL_CONTROL_MAXIMUM_LEVEL) {
    state->moveToLevel = LEVEL_CONTROL_MAXIMUM_LEVEL;
  } else if (level <= LEVEL_CONTROL_MINIMUM_LEVEL) {
    state->moveToLevel = LEVEL_CONTROL_MINIMUM_LEVEL;
  } else {
    state->moveToLevel = level;
  }

  // Figure out if we're moving up or down and by how much.
  if (state->moveToLevel > currentLevel) {
    state->diff = state->moveToLevel - currentLevel;
    state->moveToLevelUp = TRUE;
  } else if (state->moveToLevel < currentLevel) {
    state->diff = currentLevel - state->moveToLevel;
    state->moveToLevelUp = FALSE;
  } else {
    status = EMBER_ZCL_STATUS_SUCCESS;
    goto send_default_response;
  }

  // If the Transition time field takes the value 0xFFFF, then the time taken to
  // move to the new level shall instead be determined by the On/Off Transition
  // Time attribute.  If On/Off Transition Time, which is an optional attribute,
  // is not present, the device shall move to its new level as fast as it is
  // able.
  if (transitionTime == 0xFFFF) {
#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_ON_OFF_TRANSITION_TIME_ATTRIBUTE
    status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                  ZCL_LEVEL_CONTROL_CLUSTER_ID,
                                  ZCL_ON_OFF_TRANSITION_TIME_ATTRIBUTE_ID,
                                  CLUSTER_MASK_SERVER,
                                  (int8u *)&transitionTime,
                                  sizeof(transitionTime),
                                  NULL); // data type
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      emberAfLevelControlClusterPrintln("ERR: reading on/off transition time %x",
                                        status);
      goto send_default_response;
    }
#else //ZCL_USING_LEVEL_CONTROL_CLUSTER_ON_OFF_TRANSITION_TIME_ATTRIBUTE
    // TODO: If the Transition Time field is 0xFFFF and On/Off Transition Time,
    // which is an optional attribute, is not present, the device shall move to
    // its new level as fast as it is able.
    transitionTime = 0;
#endif //ZCL_USING_LEVEL_CONTROL_CLUSTER_ON_OFF_TRANSITION_TIME_ATTRIBUTE
  }

  // Transition time comes in (or is stored, in the case of On/Off Transition
  // Time) as tenths of a second, but we work in milliseconds.
  state->transTime = transitionTime * (MILLISECOND_TICKS_PER_SECOND / 100);

  // Calculate the tick parameters necessary for this movement.
  calculateTickParameters(state);

  // The setup was successful, so mark the new state as active and return.
  emAfActivateLevelControl(state, emberAfCurrentEndpoint());

  state->commandId = commandId;

  status = EMBER_ZCL_STATUS_SUCCESS;
  goto send_default_response;

send_default_response:
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
}

static void emAfLevelControlClusterMoveHandler(int8u commandId,
                                               int8u moveMode,
                                               int8u rate)
{
  EmberAfLevelControlState *state = emAfGetLevelControlState(emberAfCurrentEndpoint());
  EmberAfStatus status;
  int8u currentLevel;

  if (state == NULL) {
    status = EMBER_ZCL_STATUS_FAILURE;
    goto send_default_response;
  }

  // Cancel any currently active command before fiddling with the state.
  emAfDeactivateLevelControl(state);

  status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                ZCL_LEVEL_CONTROL_CLUSTER_ID,
                                ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&currentLevel,
                                sizeof(currentLevel),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfLevelControlClusterPrintln("ERR: reading current level %x", status);
    goto send_default_response;
  }

  state->moveMode = moveMode;
  switch (moveMode) {
  case EMBER_ZCL_MOVE_MODE_UP:
    if (currentLevel == LEVEL_CONTROL_MAXIMUM_LEVEL) {
      status = EMBER_ZCL_STATUS_SUCCESS;
      goto send_default_response;
    }
    state->moveToLevelUp = TRUE;
    break;
  case EMBER_ZCL_MOVE_MODE_DOWN:
    if (currentLevel == LEVEL_CONTROL_MINIMUM_LEVEL) {
      status = EMBER_ZCL_STATUS_SUCCESS;
      goto send_default_response;
    }
    state->moveToLevelUp = FALSE;
    break;
  default:
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
    goto send_default_response;
  }

  // TODO: If the Rate field is 0xFF, the device should move as fast as it is
  // able.
  state->moveRate = rate;

  // The setup was successful, so mark the new state as active and return.
  emAfActivateLevelControl(state, emberAfCurrentEndpoint());
  state->commandId = commandId;
  
  status = EMBER_ZCL_STATUS_SUCCESS;
  goto send_default_response;

send_default_response:
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
}

static void emAfLevelControlClusterStepHandler(int8u commandId,
                                               int8u stepMode,
                                               int8u stepSize,
                                               int16u transitionTime)
{
  EmberAfLevelControlState *state = emAfGetLevelControlState(emberAfCurrentEndpoint());
  EmberAfStatus status;
  int8u currentLevel;

  if (state == NULL) {
    status = EMBER_ZCL_STATUS_FAILURE;
    goto send_default_response;
  }

  // Cancel any currently active command before fiddling with the state.
  emAfDeactivateLevelControl(state);

  status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                ZCL_LEVEL_CONTROL_CLUSTER_ID,
                                ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&currentLevel,
                                sizeof(currentLevel),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfLevelControlClusterPrintln("ERR: reading current level %x", status);
    goto send_default_response;
  }

  state->moveMode = stepMode;
  switch (stepMode) {
  case EMBER_ZCL_STEP_MODE_UP:
    if (currentLevel == LEVEL_CONTROL_MAXIMUM_LEVEL) {
      status = EMBER_ZCL_STATUS_SUCCESS;
      goto send_default_response;
    } else if (LEVEL_CONTROL_MAXIMUM_LEVEL - currentLevel > stepSize) {
      state->moveToLevel = currentLevel + stepSize;
    } else {
      // TODO: If the new level was pegged at the maximum level, the transition
      // time shall be proportionally reduced.
      state->moveToLevel = LEVEL_CONTROL_MAXIMUM_LEVEL;
    }
    state->diff = state->moveToLevel - currentLevel;
    state->moveToLevelUp = TRUE;
    break;
  case EMBER_ZCL_STEP_MODE_DOWN:
    if (currentLevel == LEVEL_CONTROL_MINIMUM_LEVEL) {
      status = EMBER_ZCL_STATUS_SUCCESS;
      goto send_default_response;
    } else if (currentLevel - LEVEL_CONTROL_MINIMUM_LEVEL > stepSize) {
      state->moveToLevel = currentLevel - stepSize;
    } else {
      // TODO: If the new level was pegged at the minimum level, the transition
      // time shall be proportionally reduced.
      state->moveToLevel = LEVEL_CONTROL_MINIMUM_LEVEL;
    }
    state->diff = currentLevel - state->moveToLevel;
    state->moveToLevelUp = FALSE;
    break;
  default:
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
    goto send_default_response;
  }

  // TODO: If the Transition Time field is 0xFFFF, the device should move as
  // fast as it is able.
  if (transitionTime == 0xFFFF) {
    transitionTime = 0;
  }

  // Transition time comes in as tenths of a second, but we work in milliseconds.
  state->transTime = transitionTime * 100;

  // Calculate the tick parameters necessary for this movement.
  calculateTickParameters(state);

  // The setup was successful, so mark the new state as active and return.
  emAfActivateLevelControl(state, emberAfCurrentEndpoint());
  state->commandId = commandId;

  status = EMBER_ZCL_STATUS_SUCCESS;
  goto send_default_response;

send_default_response:
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
}

static void emAfLevelControlClusterStopHandler(int8u commandId)
{
  EmberAfLevelControlState *state = emAfGetLevelControlState(emberAfCurrentEndpoint());
  EmberAfStatus status;

  if (state == NULL) {
    status = EMBER_ZCL_STATUS_FAILURE;
    goto send_default_response;
  }

  // Cancel any currently active command.
  emAfDeactivateLevelControl(state);
  state->commandId = commandId;
  status = EMBER_ZCL_STATUS_SUCCESS;
  goto send_default_response;

send_default_response:
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
}
#endif //ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
