// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generatePluginCallbackPrototypes()
//

/**
 * @addtogroup callback Application Framework V2 callback interface Reference
 * This header provides callback function prototypes for the Messaging client
 * cluster application framework plugin.
 * @{
 */


/** @brief Display Message
 *
 * This function is called by the Messaging client plugin whenever the
 * application should display a message.
 *
 * @param message The message that should be displayed.  Ver.: always
 */
void emberAfPluginMessagingClientDisplayMessageCallback(EmberAfPluginMessagingClientMessage * message);

/** @brief Cancel Message
 *
 * This function is called by the Messaging client plugin whenever the
 * application should stop displaying a message.
 *
 * @param message The message that should no longer be displayed.  Ver.:
 * always
 */
void emberAfPluginMessagingClientCancelMessageCallback(EmberAfPluginMessagingClientMessage * message);



/** @} END addtogroup */
