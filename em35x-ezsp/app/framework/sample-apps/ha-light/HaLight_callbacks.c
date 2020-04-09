// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
//

// This callback file is created for your convenience. You may add application code
// to this file. If you regenerate this file over a previous version, the previous
// version will be overwritten and any code you have added will be lost.

#include "app/framework/include/af.h"


/** @brief Server Attribute Changed
 *
 * On/off cluster, server-side attribute changed.
 *
 * @param endpoint Endpoint that is being initialized
 * @param attributeId Attribute that changed
 */
void emberAfOnOffClusterServerAttributeChangedCallback(int8u endpoint, 
                                                       EmberAfAttributeId attributeId) {
  if (attributeId == ZCL_ON_OFF_ATTRIBUTE_ID) {
    boolean onOff;
    EmberAfStatus status = emberAfReadAttribute(endpoint,
                                                ZCL_ON_OFF_CLUSTER_ID,
                                                ZCL_ON_OFF_ATTRIBUTE_ID,
                                                CLUSTER_MASK_SERVER,
                                                (int8u *)&onOff,
                                                sizeof(onOff),
                                                NULL); // data type
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      emberAfCorePrintln("ERR: reading on/off %x", status);
    } else {
      emberAfCorePrintln("Light on 0x%x is now %p",
                         endpoint,
                         onOff ? "ON" : "OFF");
      emberAfCoreFlush();
      if ( onOff )
        halSetLed(BOARDLED1);
      else
        halClearLed(BOARDLED1);
    }
  }
}

/** @brief Finished
 *
 * This callback is fired when the network-find plugin is finished with the
 * forming or joining process.  The result of the operation will be returned
 * in the status parameter.
 *
 * @param status   Ver.: always
 */
void emberAfPluginNetworkFindFinishedCallback(EmberStatus status) {
  
}
