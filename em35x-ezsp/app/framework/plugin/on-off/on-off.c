// *******************************************************************
// * on-off.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "on-off.h"

#ifdef EMBER_AF_PLUGIN_LEVEL_CONTROL
  #include "../level-control/level-control.h"
#endif //EMBER_AF_PLUGIN_LEVEL_CONTROL

#ifdef EMBER_AF_PLUGIN_SCENES
  #include "../scenes/scenes.h"
#endif //EMBER_AF_PLUGIN_SCENES

EmberAfStatus emberAfOnOffSetValue(int8u endpoint,
                                   int8u command,
                                   boolean initiatedByLevelChange)
{
  EmberAfStatus status;
  boolean currentValue, newValue;

  emberAfOnOffClusterPrintln("On/Off set value: %x %x", endpoint, command);

  // read current on/off value
  status = emberAfReadAttribute(endpoint,
                                ZCL_ON_OFF_CLUSTER_ID,
                                ZCL_ON_OFF_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&currentValue,
                                sizeof(currentValue),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfOnOffClusterPrintln("ERR: reading on/off %x", status);
    return status;
  }

  // if the value is already what we want to set it to then do nothing
  if ((!currentValue && command == ZCL_OFF_COMMAND_ID) ||
      (currentValue && command == ZCL_ON_COMMAND_ID)) {
    emberAfOnOffClusterPrintln("On/off already set to new value");
    return EMBER_ZCL_STATUS_SUCCESS;
  }

  // we either got a toggle, or an on when off, or an off when on,
  // so we need to swap the value
  newValue = !currentValue;
  emberAfOnOffClusterPrintln("Toggle on/off from %x to %x", currentValue, newValue);

  // write tge new on/off value
  status = emberAfWriteAttribute(endpoint,
                                 ZCL_ON_OFF_CLUSTER_ID,
                                 ZCL_ON_OFF_ATTRIBUTE_ID,
                                 CLUSTER_MASK_SERVER,
                                 (int8u *)&newValue,
                                 ZCL_BOOLEAN_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfOnOffClusterPrintln("ERR: writing on/off %x", status);
    return status;
  }

#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
  // if using level control, the on/off command also adjusts the level
  if (!initiatedByLevelChange
      && emberAfContainsServer(endpoint, ZCL_LEVEL_CONTROL_CLUSTER_ID)) {
    static int8u storedLevelValue = 255;
    int8u currentLevel, newLevel;
    boolean enableLevelWrite = FALSE;

    status = emberAfReadAttribute(endpoint,
                                  ZCL_LEVEL_CONTROL_CLUSTER_ID,
                                  ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,
                                  CLUSTER_MASK_SERVER,
                                  (int8u *)&currentLevel,
                                  sizeof(currentLevel),
                                  NULL); // data type
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      emberAfOnOffClusterPrintln("ERR: reading current level %x", status);
    } else {
      if (!newValue) {
        emberAfOnOffClusterPrintln("setting to OFF, level of 0");
        // new level to write is 0
        newLevel = 0;
        enableLevelWrite = TRUE;
  
        // store the current setting so it can be restored in storedLevelValue
        storedLevelValue = currentLevel;
        emberAfOnOffClusterPrintln("setting storedLevel of %x", storedLevelValue);
  
        // make sure we arent storing a incorrect value
        if (storedLevelValue == 0) {
          storedLevelValue = 255;
        }
      } else {
        emberAfOnOffClusterPrintln("setting to ON, level of %x", storedLevelValue);
        // return the level back to where it was when the off command was issued
        // if the level isnt already set to nozero - like when we are moving
        // or stepping. Only do this if the level is not zero, otherwise this
        // screws up level, step, and move commands.
        if (storedLevelValue != 0) {
          emberAfOnOffClusterPrintln("setting level to storedLevel");
          newLevel = storedLevelValue;
          enableLevelWrite = TRUE;
        }
      }
  
      // write the level if we are supposed to
      if (enableLevelWrite) {
        emberAfOnOffClusterPrintln("Writing new level of %x", newLevel);
        // Write the level value.  Log any errors, but don't return failure.
        status = emberAfWriteAttribute(endpoint,
                                       ZCL_LEVEL_CONTROL_CLUSTER_ID,
                                       ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,
                                       CLUSTER_MASK_SERVER,
                                       (int8u *)&newLevel,
                                       ZCL_INT8U_ATTRIBUTE_TYPE);
        if (status != EMBER_ZCL_STATUS_SUCCESS) {
          emberAfOnOffClusterPrintln("ERR: writing current level %x", status);
        }
      }
    }
  }
#endif //ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER

#ifdef EMBER_AF_PLUGIN_SCENES
  // the scene has been changed (the value of on/off has changed) so
  // the current scene as descibed in the attribute table is invalid,
  // so mark it as invalid (just writes the valid/invalid attribute)
  if (emberAfContainsServer(endpoint, ZCL_SCENES_CLUSTER_ID)) {
    emberAfScenesMakeInvalid(endpoint);
  }
#endif //EMBER_AF_PLUGIN_SCENES

  // The returned status is based solely on the On/Off cluster.  Errors in the
  // Level Control and/or Scenes cluster are ignored.
  return EMBER_ZCL_STATUS_SUCCESS;
}

boolean emberAfOnOffClusterOffCallback(void)
{
  EmberAfStatus status = emberAfOnOffSetValue(emberAfCurrentEndpoint(),
                                              ZCL_OFF_COMMAND_ID,
                                              FALSE);
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}

boolean emberAfOnOffClusterOnCallback(void)
{
  EmberAfStatus status = emberAfOnOffSetValue(emberAfCurrentEndpoint(),
                                              ZCL_ON_COMMAND_ID,
                                              FALSE);
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}

boolean emberAfOnOffClusterToggleCallback(void)
{
  EmberAfStatus status = emberAfOnOffSetValue(emberAfCurrentEndpoint(),
                                              ZCL_TOGGLE_COMMAND_ID,
                                              FALSE);
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}
