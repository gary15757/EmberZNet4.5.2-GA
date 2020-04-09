// *******************************************************************
// * scenes.h
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

EmberAfStatus emberAfScenesSetSceneCountAttribute(int8u endpoint,
                                                  int8u newCount);
EmberAfStatus emberAfScenesMakeValid(int8u endpoint,
                                     int8u sceneId,
                                     int16u groupId);
EmberAfStatus emberAfScenesMakeInvalid(int8u endpoint);
void emAfPluginScenesServerPrintInfo(void);
