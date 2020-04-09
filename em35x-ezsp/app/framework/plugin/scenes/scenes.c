// *******************************************************************
// * scenes.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "../../util/common.h"
#include "scenes.h"

#define ZCL_SCENES_CLUSTER_MODE_COPY_ALL_SCENES_MASK BIT(0)

#define emberAfScenesClusterReadErrorPrintln(attribute, status) \
  emberAfScenesClusterPrintln("ERR: %ping %p 0x%x", "read", attribute, status);
#define emberAfScenesClusterWriteErrorPrintln(attribute, status) \
  emberAfScenesClusterPrintln("ERR: %ping %p 0x%x", "writ", attribute, status);

#if defined(EMBER_AF_PLUGIN_SCENES_USE_TOKENS) && !defined(EZSP_HOST)
static int8u sceneTableNumEntriesInUse = 0;
// In this case, we use token storage

#define emAfRetrieveSceneEntry(entry, i) \
  halCommonGetIndexedToken(&entry, TOKEN_SCENES_TABLE, i)

#define emAfSaveSceneEntry(entry, i) \
  halCommonSetIndexedToken(TOKEN_SCENES_TABLE, i, &entry)

#define emAfNumSceneEntriesInUse() \
  (halCommonGetToken(&sceneTableNumEntriesInUse, TOKEN_SCENES_NUM_ENTRIES), \
   sceneTableNumEntriesInUse)

#define emAfSetNumSceneEntriesInUse(x) \
  (sceneTableNumEntriesInUse = x, \
   halCommonSetToken(TOKEN_SCENES_NUM_ENTRIES, &sceneTableNumEntriesInUse))

#define emAfIncrNumSceneEntriesInUse() \
  ((halCommonGetToken(&sceneTableNumEntriesInUse, TOKEN_SCENES_NUM_ENTRIES), \
    ++sceneTableNumEntriesInUse), \
   halCommonSetToken(TOKEN_SCENES_NUM_ENTRIES, &sceneTableNumEntriesInUse))

#define emAfDecrNumSceneEntriesInUse() \
  ((halCommonGetToken(&sceneTableNumEntriesInUse, TOKEN_SCENES_NUM_ENTRIES), \
    --sceneTableNumEntriesInUse), \
   halCommonSetToken(TOKEN_SCENES_NUM_ENTRIES, &sceneTableNumEntriesInUse))

#else
// Use normal RAM storage
static int8u sceneTableNumEntriesInUse = 0;
static EmberAfSceneTableEntry sceneTable[EMBER_AF_PLUGIN_SCENES_TABLE_SIZE];

#define emAfRetrieveSceneEntry(entry, i) (entry = sceneTable[i])
#define emAfSaveSceneEntry(entry, i)     (sceneTable[i] = entry)
#define emAfNumSceneEntriesInUse()       (sceneTableNumEntriesInUse)
#define emAfSetNumSceneEntriesInUse(x)   (sceneTableNumEntriesInUse = x)
#define emAfIncrNumSceneEntriesInUse()   (++sceneTableNumEntriesInUse)
#define emAfDecrNumSceneEntriesInUse()   (--sceneTableNumEntriesInUse)

#endif // Use tokens

void emberAfScenesClusterServerInitCallback(int8u endpoint)
{
#ifdef EMBER_AF_PLUGIN_SCENES_NAME_SUPPORT
  {
    // The high bit of Name Support indicates whether scene names are supported.
    EmberAfStatus status;
    int8u nameSupport = BIT(7);
    status = emberAfWriteAttribute(endpoint,
                                   ZCL_SCENES_CLUSTER_ID,
                                   ZCL_SCENE_NAME_SUPPORT_ATTRIBUTE_ID,
                                   CLUSTER_MASK_SERVER,
                                   (int8u *)&nameSupport,
                                   ZCL_BITMAP8_ATTRIBUTE_TYPE);
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      emberAfScenesClusterWriteErrorPrintln("name support", status);
    }
  }
#endif
#if !defined(EMBER_AF_PLUGIN_SCENES_USE_TOKENS) || defined(EZSP_HOST)
  {
    int8u i;
    for (i = 0; i < EMBER_AF_PLUGIN_SCENES_TABLE_SIZE; i++) {
      EmberAfSceneTableEntry entry;
      emAfRetrieveSceneEntry(entry, i);
      entry.endpoint = EMBER_AF_SCENE_TABLE_UNUSED_ENDPOINT_ID;
      emAfSaveSceneEntry(entry, i);
    }
    emAfSetNumSceneEntriesInUse(0);
  }
#endif
  emberAfScenesSetSceneCountAttribute(endpoint, emAfNumSceneEntriesInUse());
}

EmberAfStatus emberAfScenesSetSceneCountAttribute(int8u endpoint,
                                                  int8u newCount)
{
  EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                               ZCL_SCENES_CLUSTER_ID,
                                               ZCL_SCENE_COUNT_ATTRIBUTE_ID,
                                               CLUSTER_MASK_SERVER,
                                               (int8u *)&newCount,
                                               ZCL_INT8U_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfScenesClusterWriteErrorPrintln("scene count", status);
  }
  return status;
}

EmberAfStatus emberAfScenesMakeValid(int8u endpoint,
                                     int8u sceneId,
                                     int16u groupId)
{
  EmberAfStatus status;
  boolean valid = TRUE;

  // scene ID
  status = emberAfWriteAttribute(endpoint,
                                 ZCL_SCENES_CLUSTER_ID,
                                 ZCL_CURRENT_SCENE_ATTRIBUTE_ID,
                                 CLUSTER_MASK_SERVER,
                                 (int8u *)&sceneId,
                                 ZCL_INT8U_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfScenesClusterWriteErrorPrintln("current scene", status);
    return status;
  }

  // group ID
  status = emberAfWriteAttribute(endpoint,
                                 ZCL_SCENES_CLUSTER_ID,
                                 ZCL_CURRENT_GROUP_ATTRIBUTE_ID,
                                 CLUSTER_MASK_SERVER,
                                 (int8u *)&groupId,
                                 ZCL_INT16U_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfScenesClusterWriteErrorPrintln("current group", status);
    return status;
  }

  status = emberAfWriteAttribute(endpoint,
                                 ZCL_SCENES_CLUSTER_ID,
                                 ZCL_SCENE_VALID_ATTRIBUTE_ID,
                                 CLUSTER_MASK_SERVER,
                                 (int8u *)&valid,
                                 ZCL_BOOLEAN_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfScenesClusterWriteErrorPrintln("scene valid", status);
  }
  return status;
}

EmberAfStatus emberAfScenesMakeInvalid(int8u endpoint)
{
  EmberAfStatus status;
  boolean valid = FALSE;

  status = emberAfWriteAttribute(endpoint,
                                 ZCL_SCENES_CLUSTER_ID,
                                 ZCL_SCENE_VALID_ATTRIBUTE_ID,
                                 CLUSTER_MASK_SERVER,
                                 (int8u *)&valid,
                                 ZCL_BOOLEAN_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfScenesClusterWriteErrorPrintln("scene valid", status);
  }
  return status;
}

void emAfPluginScenesServerPrintInfo(void)
{
  int8u i;
  EmberAfSceneTableEntry entry;
  emberAfCorePrintln("using 0x%x out of 0x%x table slots",
                     emAfNumSceneEntriesInUse(),
                     EMBER_AF_PLUGIN_SCENES_TABLE_SIZE);
  for (i = 0; i < EMBER_AF_PLUGIN_SCENES_TABLE_SIZE; i++) {
    emAfRetrieveSceneEntry(entry, i);
    emberAfCorePrint("%x: ", i);
    if (entry.endpoint != EMBER_AF_SCENE_TABLE_UNUSED_ENDPOINT_ID) {
      emberAfCorePrint("ep %x grp %2x scene %x tt %d ",
                       entry.endpoint,
                       entry.groupId,
                       entry.sceneId,
                       entry.transitionTime);
#ifdef EMBER_AF_PLUGIN_SCENES_NAME_SUPPORT
      emberAfCorePrint("name(%x)\"", emberAfStringLength(entry.name));
      emberAfCorePrintString(entry.name);
      emberAfCorePrint("\"");
#endif
#ifdef ZCL_USING_ON_OFF_CLUSTER_SERVER
      emberAfCorePrint(" on/off %x", entry.onOffValue);
#endif
#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
      emberAfCorePrint(" lvl %x", entry.currentLevelValue);
#endif
#ifdef ZCL_USING_THERMOSTAT_CLUSTER_SERVER
      emberAfCorePrint(" therm %2x %2x %x",
                       entry.occupiedCoolingSetpointValue,
                       entry.occupiedHeatingSetpointValue,
                       entry.systemModeValue);
#endif
#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER
      emberAfCorePrint(" color %2x %2x",
                       entry.currentXValue,
                       entry.currentYValue);
      emberAfCoreFlush();
#endif
#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_SERVER
      emberAfCorePrint(" door %x", entry.lockStateValue);
#endif
#ifdef ZCL_USING_WINDOW_COVERING_CLUSTER_SERVER
      emberAfCorePrint(" window %x %x",
                       entry.currentPositionLiftPercentageValue,
                       entry.currentPositionTiltPercentageValue);
#endif
    }
    emberAfCorePrintln("");
  }
}

boolean emberAfScenesClusterAddSceneCallback(int16u groupId,
                                             int8u sceneId,
                                             int16u transitionTime,
                                             int8u* sceneName,
                                             int8u* extensionFieldSets)
{
  EmberAfSceneTableEntry entry;
  EmberAfStatus status;
  int16u extensionFieldSetsLen = (emberAfCurrentCommand()->bufLen
                                  - (emberAfCurrentCommand()->payloadStartIndex
                                     + sizeof(groupId)
                                     + sizeof(sceneId)
                                     + sizeof(transitionTime)
                                     + emberAfStringLength(sceneName) + 1));
  int16u extensionFieldSetsIndex = 0;
  int8u i, index = EMBER_AF_SCENE_TABLE_NULL_INDEX;

  emberAfScenesClusterPrint("RX: AddScene 0x%2x, 0x%x, 0x%2x, \"",
                            groupId,
                            sceneId,
                            transitionTime);
  emberAfScenesClusterPrintString(sceneName);
  emberAfScenesClusterPrint("\", ");
  emberAfScenesClusterPrintBuffer(extensionFieldSets, extensionFieldSetsLen, FALSE);
  emberAfScenesClusterPrintln("");

  if (groupId != ZCL_SCENES_GLOBAL_SCENE_GROUP_ID
      && !emberAfGroupsClusterEndpointInGroupCallback(emberAfCurrentEndpoint(),
                                                      groupId)) {
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
    goto kickout;
  }

  for (i = 0; i < EMBER_AF_PLUGIN_SCENES_TABLE_SIZE; i++) {
    emAfRetrieveSceneEntry(entry, i);
    if (entry.endpoint == emberAfCurrentEndpoint()
        && entry.groupId == groupId
        && entry.sceneId == sceneId) {
      index = i;
      break;
    } else if (index == EMBER_AF_SCENE_TABLE_NULL_INDEX
               && entry.endpoint == EMBER_AF_SCENE_TABLE_UNUSED_ENDPOINT_ID) {
      index = i;
    }
  }

  // If the target index is still zero, the table is full.
  if (index == EMBER_AF_SCENE_TABLE_NULL_INDEX) {
    status = EMBER_ZCL_STATUS_INSUFFICIENT_SPACE;
    goto kickout;
  }

  emAfRetrieveSceneEntry(entry, index);

  entry.transitionTime = transitionTime;
#ifdef EMBER_AF_PLUGIN_SCENES_NAME_SUPPORT
  emberAfCopyString(entry.name, sceneName, ZCL_SCENES_CLUSTER_MAXIMUM_NAME_LENGTH);
#endif

  // When adding a new scene, wipe out all of the extensions before parsing the
  // extension field sets data.
  if (i != index) {
#ifdef ZCL_USING_ON_OFF_CLUSTER_SERVER
    entry.hasOnOffValue = FALSE;
#endif
#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
    entry.hasCurrentLevelValue = FALSE;
#endif
#ifdef ZCL_USING_THERMOSTAT_CLUSTER_SERVER
    entry.hasOccupiedCoolingSetpointValue = FALSE;
    entry.hasOccupiedHeatingSetpointValue = FALSE;
    entry.hasSystemModeValue = FALSE;
#endif
#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER
    entry.hasCurrentXValue = FALSE;
    entry.hasCurrentYValue = FALSE;
#endif
#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_SERVER
    entry.hasLockStateValue = FALSE;
#endif
#ifdef ZCL_USING_WINDOW_COVERING_CLUSTER_SERVER
    entry.hasCurrentPositionLiftPercentageValue = FALSE;
    entry.hasCurrentPositionTiltPercentageValue = FALSE;
#endif
  }

  while (extensionFieldSetsIndex < extensionFieldSetsLen) {
    EmberAfClusterId clusterId;
    int8u length;

    // Each extension field set must contain a two-byte cluster id and a one-
    // byte length.  Otherwise, the command is malformed.
    if (extensionFieldSetsLen < extensionFieldSetsIndex + 3) {
      status = EMBER_ZCL_STATUS_MALFORMED_COMMAND;
      goto kickout;
    }

    clusterId = emberAfGetInt16u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
    extensionFieldSetsIndex += 2;
    length = emberAfGetInt8u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
    extensionFieldSetsIndex++;

    // If the length is off, the command is also malformed.
    if (length == 0) {
      continue;
    } else if (extensionFieldSetsLen < extensionFieldSetsIndex + length) {
      status = EMBER_ZCL_STATUS_MALFORMED_COMMAND;
      goto kickout;
    }

    switch (clusterId) {
#ifdef ZCL_USING_ON_OFF_CLUSTER_SERVER
    case ZCL_ON_OFF_CLUSTER_ID:
      // We only know of one extension for the On/Off cluster and it is just one
      // byte, which means we can skip some logic for this cluster.  If other
      // extensions are added in this cluster, more logic will be needed here.
      entry.hasOnOffValue = TRUE;
      entry.onOffValue = emberAfGetInt8u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
      break;
#endif
#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
    case ZCL_LEVEL_CONTROL_CLUSTER_ID:
      // We only know of one extension for the Color Control cluster and it is
      // just one byte, which means we can skip some logic for this cluster.  If
      // other extensions are added in this cluster, more logic will be needed
      // here.
      entry.hasCurrentLevelValue = TRUE;
      entry.currentLevelValue = emberAfGetInt8u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
      break;
#endif
#ifdef ZCL_USING_THERMOSTAT_CLUSTER_SERVER
    case ZCL_THERMOSTAT_CLUSTER_ID:
      if (length < 2) {
        break;
      }
      entry.hasOccupiedCoolingSetpointValue = TRUE;
      entry.occupiedCoolingSetpointValue = (int16s)emberAfGetInt16u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
      extensionFieldSetsIndex += 2;
      length -= 2;
      if (length < 2) {
        break;
      }
      entry.hasOccupiedHeatingSetpointValue = TRUE;
      entry.occupiedHeatingSetpointValue = (int16s)emberAfGetInt16u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
      extensionFieldSetsIndex += 2;
      length -= 2;
      if (length < 1) {
        break;
      }
      entry.hasSystemModeValue = TRUE;
      entry.systemModeValue = emberAfGetInt8u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
      // If additional Thermostat extensions are added, adjust the index and
      // length variables here.
      break;
#endif
#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER
    case ZCL_COLOR_CONTROL_CLUSTER_ID:
      if (length < 2) {
        break;
      }
      entry.hasCurrentXValue = TRUE;
      entry.currentXValue = emberAfGetInt16u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
      extensionFieldSetsIndex += 2;
      length -= 2;
      if (length < 2) {
        break;
      }
      entry.hasCurrentYValue = TRUE;
      entry.currentYValue = emberAfGetInt16u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
      // If additional Color Control extensions are added, adjust the index and
      // length variables here.
      break;
#endif
#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_SERVER
    case ZCL_DOOR_LOCK_CLUSTER_ID:
      // We only know of one extension for the Door Lock cluster and it is just
      // one byte, which means we can skip some logic for this cluster.  If
      // other extensions are added in this cluster, more logic will be needed
      // here.
      entry.hasLockStateValue = TRUE;
      entry.lockStateValue = emberAfGetInt8u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
      break;
#endif
#ifdef ZCL_USING_WINDOW_COVERING_CLUSTER_SERVER
    case ZCL_WINDOW_COVERING_CLUSTER_ID:
      // If we're here, we know we have at least one byte, so we can skip the
      // length check for the first field.
      entry.hasCurrentPositionLiftPercentageValue = TRUE;
      entry.currentPositionLiftPercentageValue = emberAfGetInt8u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
      extensionFieldSetsIndex++;
      length--;
      if (length < 1) {
        break;
      }
      entry.hasCurrentPositionTiltPercentageValue = TRUE;
      entry.currentPositionTiltPercentageValue = emberAfGetInt8u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
      // If additional Window Covering extensions are added, adjust the index
      // and length variables here.
      break;
#endif
    default:
      break;
    }

    extensionFieldSetsIndex += length;
  }

  // If we got this far, we either added a new entry or updated an existing one.
  // If we added, store the basic data and increment the scene count.  In either
  // case, save the entry.
  if (i != index) {
    entry.endpoint = emberAfCurrentEndpoint();
    entry.groupId = groupId;
    entry.sceneId = sceneId;
    emAfIncrNumSceneEntriesInUse();
    emberAfScenesSetSceneCountAttribute(emberAfCurrentEndpoint(),
                                        emAfNumSceneEntriesInUse());
  }
  emAfSaveSceneEntry(entry, index);
  status = EMBER_ZCL_STATUS_SUCCESS;

kickout:
  emberAfFillCommandScenesClusterAddSceneResponse(status, groupId, sceneId);
  emberAfSendResponse();
  return TRUE;
}

boolean emberAfScenesClusterViewSceneCallback(int16u groupId, int8u sceneId)
{
  EmberAfSceneTableEntry entry;
  EmberAfStatus status = EMBER_ZCL_STATUS_NOT_FOUND;

  emberAfScenesClusterPrintln("RX: ViewScene 0x%2x, 0x%x", groupId, sceneId);

  if (groupId != ZCL_SCENES_GLOBAL_SCENE_GROUP_ID
      && !emberAfGroupsClusterEndpointInGroupCallback(emberAfCurrentEndpoint(),
                                                      groupId)) {
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
  } else {
    int8u i;
    for (i = 0; i < EMBER_AF_PLUGIN_SCENES_TABLE_SIZE; i++) {
      emAfRetrieveSceneEntry(entry, i);
      if (entry.endpoint == emberAfCurrentEndpoint()
          && entry.groupId == groupId
          && entry.sceneId == sceneId) {
        status = EMBER_ZCL_STATUS_SUCCESS;
        break;
      }
    }
  }

  // The status, group id, and scene id are always included in the response, but
  // the transition time, name, and extension fields are only included if the
  // scene was found.
  emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND
                             | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT),
                            ZCL_SCENES_CLUSTER_ID,
                            ZCL_VIEW_SCENE_RESPONSE_COMMAND_ID,
                            "uvu",
                            status,
                            groupId,
                            sceneId);
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    emberAfPutInt16uInResp(entry.transitionTime);
#ifdef EMBER_AF_PLUGIN_SCENES_NAME_SUPPORT
    emberAfPutStringInResp(entry.name);
#else
    emberAfPutInt8uInResp(0); // name length
#endif
#ifdef ZCL_USING_ON_OFF_CLUSTER_SERVER
    if (entry.hasOnOffValue) {
      emberAfPutInt16uInResp(ZCL_ON_OFF_CLUSTER_ID);
      emberAfPutInt8uInResp(1); // length
      emberAfPutInt8uInResp(entry.onOffValue);
    }
#endif
#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
    if (entry.hasCurrentLevelValue) {
      emberAfPutInt16uInResp(ZCL_LEVEL_CONTROL_CLUSTER_ID);
      emberAfPutInt8uInResp(1); // length
      emberAfPutInt8uInResp(entry.currentLevelValue);
    }
#endif
#ifdef ZCL_USING_THERMOSTAT_CLUSTER_SERVER
    if (entry.hasOccupiedCoolingSetpointValue) {
      int8u *length;
      emberAfPutInt16uInResp(ZCL_THERMOSTAT_CLUSTER_ID);
      length = &appResponseData[appResponseLength];
      emberAfPutInt8uInResp(0); // temporary length
      emberAfPutInt16uInResp(entry.occupiedCoolingSetpointValue);
      *length += 2;
      if (entry.hasOccupiedHeatingSetpointValue) {
        emberAfPutInt16uInResp(entry.occupiedHeatingSetpointValue);
        *length += 2;
        if (entry.hasSystemModeValue) {
          emberAfPutInt8uInResp(entry.systemModeValue);
          (*length)++;
        }
      }
    }
#endif
#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER
    if (entry.hasCurrentXValue) {
      int8u *length;
      emberAfPutInt16uInResp(ZCL_COLOR_CONTROL_CLUSTER_ID);
      length = &appResponseData[appResponseLength];
      emberAfPutInt8uInResp(0); // temporary length
      emberAfPutInt16uInResp(entry.currentXValue);
      *length += 2;
      if (entry.hasCurrentYValue) {
        emberAfPutInt16uInResp(entry.currentYValue);
        *length += 2;
      }
    }
#endif
#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_SERVER
    if (entry.hasLockStateValue) {
      emberAfPutInt16uInResp(ZCL_DOOR_LOCK_CLUSTER_ID);
      emberAfPutInt8uInResp(1); // length
      emberAfPutInt8uInResp(entry.lockStateValue);
    }
#endif
#ifdef ZCL_USING_WINDOW_COVERING_CLUSTER_SERVER
    if (entry.hasCurrentPositionLiftPercentageValue) {
      int8u *length;
      emberAfPutInt16uInResp(ZCL_WINDOW_COVERING_CLUSTER_ID);
      length = &appResponseData[appResponseLength];
      emberAfPutInt8uInResp(0); // temporary length
      emberAfPutInt8uInResp(entry.currentPositionLiftPercentageValue);
      (*length)++;
      if (entry.hasCurrentPositionTiltPercentageValue) {
        emberAfPutInt8uInResp(entry.currentPositionTiltPercentageValue);
        (*length)++;
      }
    }
#endif
  }

  emberAfSendResponse();
  return TRUE;
}

boolean emberAfScenesClusterRemoveSceneCallback(int16u groupId, int8u sceneId)
{
  EmberAfStatus status = EMBER_ZCL_STATUS_NOT_FOUND;

  emberAfScenesClusterPrintln("RX: RemoveScene 0x%2x, 0x%x", groupId, sceneId);

  // If a group id is specified but this endpoint isn't in it, take no action.
  if (groupId != ZCL_SCENES_GLOBAL_SCENE_GROUP_ID
      && !emberAfGroupsClusterEndpointInGroupCallback(emberAfCurrentEndpoint(),
                                                      groupId)) {
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
  } else {
    int8u i;
    for (i = 0; i < EMBER_AF_PLUGIN_SCENES_TABLE_SIZE; i++) {
      EmberAfSceneTableEntry entry;
      emAfRetrieveSceneEntry(entry, i);
      if (entry.endpoint == emberAfCurrentEndpoint()
          && entry.groupId == groupId
          && entry.sceneId == sceneId) {
        entry.endpoint = EMBER_AF_SCENE_TABLE_UNUSED_ENDPOINT_ID;
        emAfSaveSceneEntry(entry, i);
        emAfDecrNumSceneEntriesInUse();
        emberAfScenesSetSceneCountAttribute(emberAfCurrentEndpoint(),
                                            emAfNumSceneEntriesInUse());
        status = EMBER_ZCL_STATUS_SUCCESS;
        break;
      }
    }
  }

  emberAfFillCommandScenesClusterRemoveSceneResponse(status, groupId, sceneId);
  emberAfSendResponse();
  return TRUE;
}

boolean emberAfScenesClusterRemoveAllScenesCallback(int16u groupId)
{
  EmberAfStatus status = EMBER_ZCL_STATUS_INVALID_FIELD;

  emberAfScenesClusterPrintln("RX: RemoveAllScenes 0x%2x", groupId);

  if (groupId == ZCL_SCENES_GLOBAL_SCENE_GROUP_ID
      || emberAfGroupsClusterEndpointInGroupCallback(emberAfCurrentEndpoint(),
                                                     groupId)) {
    int8u i;
    status = EMBER_ZCL_STATUS_SUCCESS;
    for (i = 0; i < EMBER_AF_PLUGIN_SCENES_TABLE_SIZE; i++) {
      EmberAfSceneTableEntry entry;
      emAfRetrieveSceneEntry(entry, i);
      if (entry.endpoint == emberAfCurrentEndpoint()
          && entry.groupId == groupId) {
        entry.endpoint = EMBER_AF_SCENE_TABLE_UNUSED_ENDPOINT_ID;
        emAfSaveSceneEntry(entry, i);
        emAfDecrNumSceneEntriesInUse();
      }
    }
    emberAfScenesSetSceneCountAttribute(emberAfCurrentEndpoint(),
                                        emAfNumSceneEntriesInUse());
  }

  emberAfFillCommandScenesClusterRemoveAllScenesResponse(status, groupId);
  emberAfSendResponse();
  return TRUE;
}

boolean emberAfScenesClusterStoreSceneCallback(int16u groupId, int8u sceneId)
{
  EmberAfStatus status;
  emberAfScenesClusterPrintln("RX: StoreScene 0x%2x, 0x%x", groupId, sceneId);
  status = emberAfScenesClusterStoreCurrentSceneCallback(emberAfCurrentEndpoint(),
                                                         groupId,
                                                         sceneId);
  emberAfFillCommandScenesClusterStoreSceneResponse(status, groupId, sceneId);
  emberAfSendResponse();
  return TRUE;
}

boolean emberAfScenesClusterRecallSceneCallback(int16u groupId, int8u sceneId)
{
  EmberAfStatus status;
  emberAfScenesClusterPrintln("RX: RecallScene 0x%2x, 0x%x", groupId, sceneId);
  status = emberAfScenesClusterRecallSavedSceneCallback(emberAfCurrentEndpoint(),
                                                        groupId,
                                                        sceneId);
  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}

boolean emberAfScenesClusterGetSceneMembershipCallback(int16u groupId)
{
  EmberAfStatus status = EMBER_ZCL_STATUS_SUCCESS;

  emberAfScenesClusterPrintln("RX: GetSceneMembership 0x%2x", groupId);

  if (!groupId == ZCL_SCENES_GLOBAL_SCENE_GROUP_ID
      && !emberAfGroupsClusterEndpointInGroupCallback(emberAfCurrentEndpoint(),
                                                      groupId)) {
    status = EMBER_ZCL_STATUS_INVALID_FIELD;
  }

  // The status, capacity, and group id are always included in the response, but
  // the scene count and scene list are only included if the group id matched.
  emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND
                             | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT),
                            ZCL_SCENES_CLUSTER_ID,
                            ZCL_GET_SCENE_MEMBERSHIP_RESPONSE_COMMAND_ID,
                            "uuv",
                            status,
                            (EMBER_AF_PLUGIN_SCENES_TABLE_SIZE
                             - emAfNumSceneEntriesInUse()), // capacity
                            groupId);
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    int8u i, sceneCount = 0;
    int8u sceneList[EMBER_AF_PLUGIN_SCENES_TABLE_SIZE];
    for (i = 0; i < EMBER_AF_PLUGIN_SCENES_TABLE_SIZE; i++) {
      EmberAfSceneTableEntry entry;
      emAfRetrieveSceneEntry(entry, i);
      if (entry.endpoint == emberAfCurrentEndpoint()
          && entry.groupId == groupId) {
        sceneList[sceneCount] = entry.sceneId;
        sceneCount++;
      }
    }
    emberAfPutInt8uInResp(sceneCount);
    for (i = 0; i < sceneCount; i++) {
      emberAfPutInt8uInResp(sceneList[i]);
    }
  }

  emberAfSendResponse();
  return TRUE;
}

EmberAfStatus emberAfScenesClusterStoreCurrentSceneCallback(int8u endpoint,
                                                            int16u groupId,
                                                            int8u sceneId)
{
  EmberAfSceneTableEntry entry;
  int8u i, index = EMBER_AF_SCENE_TABLE_NULL_INDEX;

  // If a group id is specified but this endpoint isn't in it, take no action.
  if (groupId != ZCL_SCENES_GLOBAL_SCENE_GROUP_ID
      && !emberAfGroupsClusterEndpointInGroupCallback(endpoint, groupId)) {
    return EMBER_ZCL_STATUS_INVALID_FIELD;
  }

  for (i = 0; i < EMBER_AF_PLUGIN_SCENES_TABLE_SIZE; i++) {
    emAfRetrieveSceneEntry(entry, i);
    if (entry.endpoint == endpoint
        && entry.groupId == groupId
        && entry.sceneId == sceneId) {
      index = i;
      break;
    } else if (index == EMBER_AF_SCENE_TABLE_NULL_INDEX
               && entry.endpoint == EMBER_AF_SCENE_TABLE_UNUSED_ENDPOINT_ID) {
      index = i;
    }
  }

  // If the target index is still zero, the table is full.
  if (index == EMBER_AF_SCENE_TABLE_NULL_INDEX) {
    return EMBER_ZCL_STATUS_INSUFFICIENT_SPACE;
  }

  emAfRetrieveSceneEntry(entry, index);

  // When creating a new entry or refreshing an existing one, the extension
  // fields are updated with the current state of other clusters on the device.
#ifdef ZCL_USING_ON_OFF_CLUSTER_SERVER
  entry.hasOnOffValue = FALSE;
  if (emberAfContainsServer(endpoint, ZCL_ON_OFF_CLUSTER_ID)) {
    EmberAfStatus status = emberAfReadAttribute(endpoint,
                                                ZCL_ON_OFF_CLUSTER_ID,
                                                ZCL_ON_OFF_ATTRIBUTE_ID,
                                                CLUSTER_MASK_SERVER,
                                                (int8u *)&entry.onOffValue,
                                                sizeof(entry.onOffValue),
                                                NULL); // data type
    if (status == EMBER_ZCL_STATUS_SUCCESS) {
      entry.hasOnOffValue = TRUE;
    } else {
      emberAfScenesClusterReadErrorPrintln("on/off", status);
    }
  }
#endif
#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
  entry.hasCurrentLevelValue = FALSE;
  if (emberAfContainsServer(endpoint, ZCL_LEVEL_CONTROL_CLUSTER_ID)) {
    EmberAfStatus status = emberAfReadAttribute(endpoint,
                                                ZCL_LEVEL_CONTROL_CLUSTER_ID,
                                                ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,
                                                CLUSTER_MASK_SERVER,
                                                (int8u *)&entry.currentLevelValue,
                                                sizeof(entry.currentLevelValue),
                                                NULL); // data type
    if (status == EMBER_ZCL_STATUS_SUCCESS) {
      entry.hasCurrentLevelValue = TRUE;
    } else {
      emberAfScenesClusterReadErrorPrintln("current level", status);
    }
  }
#endif
#ifdef ZCL_USING_THERMOSTAT_CLUSTER_SERVER
  entry.hasOccupiedCoolingSetpointValue = FALSE;
  entry.hasOccupiedHeatingSetpointValue = FALSE;
  entry.hasSystemModeValue = FALSE;
  if (emberAfContainsServer(endpoint, ZCL_THERMOSTAT_CLUSTER_ID)) {
    EmberAfStatus status = emberAfReadAttribute(endpoint,
                                                ZCL_THERMOSTAT_CLUSTER_ID,
                                                ZCL_OCCUPIED_COOLING_SETPOINT_ATTRIBUTE_ID,
                                                CLUSTER_MASK_SERVER,
                                                (int8u *)&entry.occupiedCoolingSetpointValue,
                                                sizeof(entry.occupiedCoolingSetpointValue),
                                                NULL); // data type
    if (status == EMBER_ZCL_STATUS_SUCCESS) {
      entry.hasOccupiedCoolingSetpointValue = TRUE;
    } else {
      emberAfScenesClusterReadErrorPrintln("occupied cooling setpoint", status);
    }
    status = emberAfReadAttribute(endpoint,
                                  ZCL_THERMOSTAT_CLUSTER_ID,
                                  ZCL_OCCUPIED_HEATING_SETPOINT_ATTRIBUTE_ID,
                                  CLUSTER_MASK_SERVER,
                                  (int8u *)&entry.occupiedHeatingSetpointValue,
                                  sizeof(entry.occupiedHeatingSetpointValue),
                                  NULL); // data type
    if (status == EMBER_ZCL_STATUS_SUCCESS) {
      entry.hasOccupiedHeatingSetpointValue = TRUE;
    } else {
      emberAfScenesClusterReadErrorPrintln("occupied heating setpoint", status);
    }
    status = emberAfReadAttribute(endpoint,
                                  ZCL_THERMOSTAT_CLUSTER_ID,
                                  ZCL_SYSTEM_MODE_ATTRIBUTE_ID,
                                  CLUSTER_MASK_SERVER,
                                  (int8u *)&entry.systemModeValue,
                                  sizeof(entry.systemModeValue),
                                  NULL); // data type
    if (status == EMBER_ZCL_STATUS_SUCCESS) {
      entry.hasSystemModeValue = TRUE;
    } else {
      emberAfScenesClusterReadErrorPrintln("system mode", status);
    }
  }
#endif
#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER
  entry.hasCurrentXValue = FALSE;
  entry.hasCurrentYValue = FALSE;
  if (emberAfContainsServer(endpoint, ZCL_COLOR_CONTROL_CLUSTER_ID)) {
    EmberAfStatus status = emberAfReadAttribute(endpoint,
                                                ZCL_COLOR_CONTROL_CLUSTER_ID,
                                                ZCL_COLOR_CONTROL_CURRENT_X_ATTRIBUTE_ID,
                                                CLUSTER_MASK_SERVER,
                                                (int8u *)&entry.currentXValue,
                                                sizeof(entry.currentXValue),
                                                NULL); // data type
    if (status == EMBER_ZCL_STATUS_SUCCESS) {
      entry.hasCurrentXValue = TRUE;
    } else {
      emberAfScenesClusterReadErrorPrintln("current x", status);
    }
    status = emberAfReadAttribute(endpoint,
                                  ZCL_COLOR_CONTROL_CLUSTER_ID,
                                  ZCL_COLOR_CONTROL_CURRENT_Y_ATTRIBUTE_ID,
                                  CLUSTER_MASK_SERVER,
                                  (int8u *)&entry.currentYValue,
                                  sizeof(entry.currentYValue),
                                  NULL); // data type
    if (status == EMBER_ZCL_STATUS_SUCCESS) {
      entry.hasCurrentYValue = TRUE;
    } else {
      emberAfScenesClusterReadErrorPrintln("current y", status);
    }
  }
#endif
#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_SERVER
  entry.hasLockStateValue = FALSE;
  if (emberAfContainsServer(endpoint, ZCL_DOOR_LOCK_CLUSTER_ID)) {
    int8u lockStateValue = 0;
    EmberAfStatus status = emberAfReadAttribute(endpoint,
                                                ZCL_DOOR_LOCK_CLUSTER_ID,
                                                ZCL_LOCK_STATE_ATTRIBUTE_ID,
                                                CLUSTER_MASK_SERVER,
                                                (int8u *)&entry.lockStateValue,
                                                sizeof(entry.lockStateValue),
                                                NULL); // data type
    if (status == EMBER_ZCL_STATUS_SUCCESS) {
      entry.hasLockStateValue = TRUE;
    } else {
      emberAfScenesClusterReadErrorPrintln("lock state", status);
    }
  }
#endif
#ifdef ZCL_USING_WINDOW_COVERING_CLUSTER_SERVER
  entry.hasCurrentPositionLiftPercentageValue = FALSE;
  entry.hasCurrentPositionTiltPercentageValue = FALSE;
  if (emberAfContainsServer(endpoint, ZCL_WINDOW_COVERING_CLUSTER_ID)) {
    EmberAfStatus status = emberAfReadAttribute(endpoint,
                                                ZCL_WINDOW_COVERING_CLUSTER_ID,
                                                ZCL_CURRENT_LIFT_PERCENTAGE_ATTRIBUTE_ID,
                                                CLUSTER_MASK_SERVER,
                                                (int8u *)&entry.currentPositionLiftPercentageValue,
                                                sizeof(entry.currentPositionLiftPercentageValue),
                                                NULL); // data type
    if (status == EMBER_ZCL_STATUS_SUCCESS) {
      entry.hasCurrentPositionLiftPercentageValue = TRUE;
    } else {
      emberAfScenesClusterReadErrorPrintln("current position lift percentage", status);
    }
    status = emberAfReadAttribute(endpoint,
                                  ZCL_WINDOW_COVERING_CLUSTER_ID,
                                  ZCL_CURRENT_TILT_PERCENTAGE_ATTRIBUTE_ID,
                                  CLUSTER_MASK_SERVER,
                                  (int8u *)&entry.currentPositionTiltPercentageValue,
                                  sizeof(entry.currentPositionTiltPercentageValue),
                                  NULL); // data type
    if (status == EMBER_ZCL_STATUS_SUCCESS) {
      entry.hasCurrentPositionTiltPercentageValue = TRUE;
    } else {
      emberAfScenesClusterReadErrorPrintln("current position tilt percentage", status);
    }
  }
#endif

  // When creating a new entry, the name is set to the null string (i.e., the
  // length is set to zero) and the transition time is set to zero.  The scene
  // count must be increased and written to the attribute table when adding a
  // new scene.  Otherwise, these fields and the count are left alone.
  if (i != index) {
    entry.endpoint = endpoint;
    entry.groupId = groupId;
    entry.sceneId = sceneId;
#ifdef EMBER_AF_PLUGIN_SCENES_NAME_SUPPORT
    entry.name[0] = 0;
#endif
    entry.transitionTime = 0;
    emAfIncrNumSceneEntriesInUse();
    emberAfScenesSetSceneCountAttribute(endpoint, emAfNumSceneEntriesInUse());
  }

  // Save the scene entry and mark is as valid by storing its scene and group
  // ids in the attribute table and setting valid to true.
  emAfSaveSceneEntry(entry, index);
  emberAfScenesMakeValid(endpoint, sceneId, groupId);
  return EMBER_ZCL_STATUS_SUCCESS;
}

EmberAfStatus emberAfScenesClusterRecallSavedSceneCallback(int8u endpoint,
                                                           int16u groupId,
                                                           int8u sceneId)
{
  if (groupId != ZCL_SCENES_GLOBAL_SCENE_GROUP_ID
      && !emberAfGroupsClusterEndpointInGroupCallback(endpoint, groupId)) {
    return EMBER_ZCL_STATUS_INVALID_FIELD;
  } else {
    int8u i;
    for (i = 0; i < EMBER_AF_PLUGIN_SCENES_TABLE_SIZE; i++) {
      EmberAfSceneTableEntry entry;
      emAfRetrieveSceneEntry(entry, i);
      if (entry.endpoint == endpoint
          && entry.groupId == groupId
          && entry.sceneId == sceneId) {
#ifdef ZCL_USING_ON_OFF_CLUSTER_SERVER
        if (entry.hasOnOffValue) {
          EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                                       ZCL_ON_OFF_CLUSTER_ID,
                                                       ZCL_ON_OFF_ATTRIBUTE_ID,
                                                       CLUSTER_MASK_SERVER,
                                                       (int8u *)&entry.onOffValue,
                                                       ZCL_BOOLEAN_ATTRIBUTE_TYPE);
          if (status != EMBER_ZCL_STATUS_SUCCESS) {
            emberAfScenesClusterWriteErrorPrintln("on/off", status);
          }
        }
#endif
#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
        if (entry.hasCurrentLevelValue) {
          EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                                       ZCL_LEVEL_CONTROL_CLUSTER_ID,
                                                       ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,
                                                       CLUSTER_MASK_SERVER,
                                                       (int8u *)&entry.currentLevelValue,
                                                       ZCL_INT8U_ATTRIBUTE_TYPE);
          if (status != EMBER_ZCL_STATUS_SUCCESS) {
            emberAfScenesClusterWriteErrorPrintln("current level", status);
          }
        }
#endif
#ifdef ZCL_USING_THERMOSTAT_CLUSTER_SERVER
        if (entry.hasOccupiedCoolingSetpointValue) {
          EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                                       ZCL_THERMOSTAT_CLUSTER_ID,
                                                       ZCL_OCCUPIED_COOLING_SETPOINT_ATTRIBUTE_ID,
                                                       CLUSTER_MASK_SERVER,
                                                       (int8u *)&entry.occupiedCoolingSetpointValue,
                                                       ZCL_INT16S_ATTRIBUTE_TYPE);
          if (status != EMBER_ZCL_STATUS_SUCCESS) {
            emberAfScenesClusterWriteErrorPrintln("occupied cooling setpoint", status);
          }
        }
        if (entry.hasOccupiedHeatingSetpointValue) {
          EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                                       ZCL_THERMOSTAT_CLUSTER_ID,
                                                       ZCL_OCCUPIED_HEATING_SETPOINT_ATTRIBUTE_ID,
                                                       CLUSTER_MASK_SERVER,
                                                       (int8u *)&entry.occupiedHeatingSetpointValue,
                                                       ZCL_INT16S_ATTRIBUTE_TYPE);
          if (status != EMBER_ZCL_STATUS_SUCCESS) {
            emberAfScenesClusterWriteErrorPrintln("occupied heating setpoint", status);
          }
        }
        if (entry.hasSystemModeValue) {
          EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                                       ZCL_THERMOSTAT_CLUSTER_ID,
                                                       ZCL_SYSTEM_MODE_ATTRIBUTE_ID,
                                                       CLUSTER_MASK_SERVER,
                                                       (int8u *)&entry.systemModeValue,
                                                       ZCL_INT8U_ATTRIBUTE_TYPE);
          if (status != EMBER_ZCL_STATUS_SUCCESS) {
            emberAfScenesClusterWriteErrorPrintln("system mode", status);
          }
        }
#endif
#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER
        if (entry.hasCurrentXValue) {
          EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                                       ZCL_COLOR_CONTROL_CLUSTER_ID,
                                                       ZCL_COLOR_CONTROL_CURRENT_X_ATTRIBUTE_ID,
                                                       CLUSTER_MASK_SERVER,
                                                       (int8u *)&entry.currentXValue,
                                                       ZCL_INT16U_ATTRIBUTE_TYPE);
          if (status != EMBER_ZCL_STATUS_SUCCESS) {
            emberAfScenesClusterWriteErrorPrintln("current x", status);
          }
        }
        if (entry.hasCurrentYValue) {
          EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                                       ZCL_COLOR_CONTROL_CLUSTER_ID,
                                                       ZCL_COLOR_CONTROL_CURRENT_Y_ATTRIBUTE_ID,
                                                       CLUSTER_MASK_SERVER,
                                                       (int8u *)&entry.currentYValue,
                                                       ZCL_INT16U_ATTRIBUTE_TYPE);
          if (status != EMBER_ZCL_STATUS_SUCCESS) {
            emberAfScenesClusterWriteErrorPrintln("current y", status);
          }
        }
#endif
#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_SERVER
        if (entry.hasLockStateValue) {
          EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                                       ZCL_DOOR_LOCK_CLUSTER_ID,
                                                       ZCL_LOCK_STATE_ATTRIBUTE_ID,
                                                       CLUSTER_MASK_SERVER,
                                                       (int8u *)&entry.lockStateValue,
                                                       ZCL_INT8U_ATTRIBUTE_TYPE);
          if (status != EMBER_ZCL_STATUS_SUCCESS) {
            emberAfScenesClusterWriteErrorPrintln("lock state", status);
          }
        }
#endif
#ifdef ZCL_USING_WINDOW_COVERING_CLUSTER_SERVER
        if (entry.hasCurrentPositionLiftPercentageValue) {
          EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                                       ZCL_WINDOW_COVERING_CLUSTER_ID,
                                                       ZCL_CURRENT_LIFT_PERCENTAGE_ATTRIBUTE_ID,
                                                       CLUSTER_MASK_SERVER,
                                                       (int8u *)&entry.currentPositionLiftPercentageValue,
                                                       ZCL_INT8U_ATTRIBUTE_TYPE);
          if (status != EMBER_ZCL_STATUS_SUCCESS) {
            emberAfScenesClusterWriteErrorPrintln("current position lift percentage", status);
          }
        }
        if (entry.hasCurrentPositionTiltPercentageValue) {
          EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                                       ZCL_WINDOW_COVERING_CLUSTER_ID,
                                                       ZCL_CURRENT_TILT_PERCENTAGE_ATTRIBUTE_ID,
                                                       CLUSTER_MASK_SERVER,
                                                       (int8u *)&entry.currentPositionTiltPercentageValue,
                                                       ZCL_INT8U_ATTRIBUTE_TYPE);
          if (status != EMBER_ZCL_STATUS_SUCCESS) {
            emberAfScenesClusterWriteErrorPrintln("current position tilt percentage", status);
          }
        }
#endif

        emberAfScenesMakeValid(endpoint, sceneId, groupId);
        return EMBER_ZCL_STATUS_SUCCESS;
      }
    }
  }

  return EMBER_ZCL_STATUS_NOT_FOUND;
}

void emberAfScenesClusterClearSceneTableCallback(void)
{
  int8u i;
  for (i = 0; i < EMBER_AF_PLUGIN_SCENES_TABLE_SIZE; i++) {
    EmberAfSceneTableEntry entry;
    emAfRetrieveSceneEntry(entry, i);
    entry.endpoint = EMBER_AF_SCENE_TABLE_UNUSED_ENDPOINT_ID;
    emAfSaveSceneEntry(entry, i);
    emAfDecrNumSceneEntriesInUse();
  }
  for (i = 0; i < emberAfEndpointCount(); i++) {
    emberAfScenesSetSceneCountAttribute(emberAfEndpointFromIndex(i),
                                        emAfNumSceneEntriesInUse());
  }
}
