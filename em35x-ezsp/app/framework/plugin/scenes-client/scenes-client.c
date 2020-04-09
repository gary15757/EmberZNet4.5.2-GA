// *******************************************************************
// * scenes-client.c
// *
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"

boolean emberAfScenesClusterAddSceneResponseCallback(int8u status,
                                                     int16u groupId,
                                                     int8u sceneId)
{
  emberAfScenesClusterPrintln("RX: AddSceneResponse 0x%x, 0x%2x, 0x%x",
                              status,
                              groupId,
                              sceneId);
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

boolean emberAfScenesClusterViewSceneResponseCallback(int8u status,
                                                      int16u groupId,
                                                      int8u sceneId,
                                                      int16u transitionTime,
                                                      int8u *sceneName,
                                                      int8u *extensionFieldSets)
{
  emberAfScenesClusterPrint("RX: ViewSceneResponse 0x%x, 0x%2x, 0x%x",
                            status,
                            groupId,
                            sceneId);

  // Transition time, scene name, and the extension field sets only appear in
  // the payload if the status is SUCCESS.
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    int16u extensionFieldSetsLen = (emberAfCurrentCommand()->bufLen
                                    - (emberAfCurrentCommand()->payloadStartIndex
                                       + sizeof(status)
                                       + sizeof(groupId)
                                       + sizeof(sceneId)
                                       + sizeof(transitionTime)
                                       + emberAfStringLength(sceneName) + 1));
    int16u extensionFieldSetsIndex = 0;

    emberAfScenesClusterPrint(", 0x%2x, \"", transitionTime);
    emberAfScenesClusterPrintString(sceneName);
    emberAfScenesClusterPrint("\",");

    // Each extension field set contains at least a two-byte cluster id and a
    // one-byte length.
    while (extensionFieldSetsIndex + 3 <= extensionFieldSetsLen) {
      EmberAfClusterId clusterId;
      int8u length;
      clusterId = emberAfGetInt16u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
      extensionFieldSetsIndex += 2;
      length = emberAfGetInt8u(extensionFieldSets, extensionFieldSetsIndex, extensionFieldSetsLen);
      extensionFieldSetsIndex++;
      emberAfScenesClusterPrint(" [0x%2x 0x%x ", clusterId, length);
      if (extensionFieldSetsIndex + length <= extensionFieldSetsLen) {
        emberAfScenesClusterPrintBuffer(extensionFieldSets + extensionFieldSetsIndex, length, FALSE);
      }
      emberAfScenesClusterPrint("]");
      emberAfScenesClusterFlush();
      extensionFieldSetsIndex += length;
    }
  }

  emberAfScenesClusterPrintln("");
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

boolean emberAfScenesClusterRemoveSceneResponseCallback(int8u status,
                                                        int16u groupId,
                                                        int8u sceneId)
{
  emberAfScenesClusterPrintln("RX: RemoveSceneResponse 0x%x, 0x%2x, 0x%x",
                              status,
                              groupId,
                              sceneId);
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

boolean emberAfScenesClusterRemoveAllScenesResponseCallback(int8u status,
                                                            int16u groupId)
{
  emberAfScenesClusterPrintln("RX: RemoveAllScenesResponse 0x%x, 0x%2x",
                              status,
                              groupId);
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

boolean emberAfScenesClusterStoreSceneResponseCallback(int8u status,
                                                       int16u groupId,
                                                       int8u sceneId)
{
  emberAfScenesClusterPrintln("RX: StoreSceneResponse 0x%x, 0x%2x, 0x%x",
                              status,
                              groupId,
                              sceneId);
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

boolean emberAfScenesClusterGetSceneMembershipResponseCallback(int8u status,
                                                               int8u capacity,
                                                               int16u groupId,
                                                               int8u sceneCount,
                                                               int8u *sceneList)
{
  emberAfScenesClusterPrint("RX: GetSceneMembershipResponse 0x%x, 0x%x, 0x%2x",
                            status,
                            capacity,
                            groupId);

  // Scene count and the scene list only appear in the payload if the status is
  // SUCCESS.
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    int8u i;
    emberAfScenesClusterPrint(", 0x%x,", sceneCount);
    for (i = 0; i < sceneCount; i++) {
      emberAfScenesClusterPrint(" [0x%x]", sceneList[i]);
    }
  }

  emberAfScenesClusterPrintln("");
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}
