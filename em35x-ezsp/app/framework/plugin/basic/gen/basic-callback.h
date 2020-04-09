// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generatePluginCallbackPrototypes()
//

/**
 * @addtogroup callback Application Framework V2 callback interface Reference
 * This header provides callback function prototypes for the Basic server cluster
 * application framework plugin.
 * @{
 */


/** @brief Reset To Factory Defaults
 *
 * This function is called by the Basic server plugin when a request to reset
 * to factory defaults is received.  The plugin will reset attributes managed
 * by the framework to their default values.  The application should preform
 * any other necessary reset-related operations in this callback, including
 * resetting any externally-stored attributes.
 *
 */
void emberAfPluginBasicResetToFactoryDefaultsCallback(void);



/** @} END addtogroup */
