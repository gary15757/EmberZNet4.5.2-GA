// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generateStackHandlerStubs()
//

// This c file provides stubs for all callbacks. These stubs
// will be used in the case where user defined implementations
// of the callbacks have not been provided.
#include PLATFORM_HEADER
#ifdef EZSP_HOST
// Includes needed for ember related functions for the EZSP host
#include "stack/include/error.h"
#include "stack/include/ember-types.h"
#include "app/util/ezsp/ezsp-protocol.h"
#include "app/util/ezsp/ezsp.h"
#include "app/util/ezsp/ezsp-utils.h"
#include "app/util/ezsp/serial-interface.h"
#else
// Includes needed for ember related functions for the EM250
#include "stack/include/ember.h"
#endif // EZSP_HOST

#include "app/framework/include/af.h"
#include "app/framework/util/attribute-table.h"
#include "app/framework/util/attribute-storage.h"
// Stubs required for implemented stack handlers.


#ifdef EZSP_HOST

/** @brief ezspPollCompleteHandler
 *
 * This is called by the EZSP when a data poll to the parent is complete. See
 * EZSP documentation for more information.

Application framework itself
 * defines this callback and calls function emberAfEzspPollCompleteHandler().
 * If you wish to 
add functionality to this handler, while still maintaining
 * app framework functionality, then implement it yourself and make
sure you
 * call emberAfEzspPollCompleteHandler() function within your implementation
 * of ezspPollCompleteHandler().
 *
 * @param status Ember status value.  Ver.: always
 */
  #ifndef EMBER_CALLBACK_EZSP_POLL_COMPLETE
void ezspPollCompleteHandler(EmberStatus status) {
  emberAfEzspPollCompleteHandler(status);
}
  #endif // EMBER_CALLBACK_EZSP_POLL_COMPLETE
#else // ! EZSP_HOST

/** @brief emberPollCompleteHandler
 *
 * This is called by the stack when a data poll to the parent is complete. See
 * stack documentation for more information.

Application framework itself
 * defines this callback and calls function emberAfPollCompleteHandler(). If
 * you wish to 
add functionality to this handler, while still maintaining app
 * framework functionality, then implement it yourself and make
sure you call
 * emberAfPollCompleteHandler() function within your implementation of
 * emberPollCompleteHandler().
 *
 * @param status Ember status value.  Ver.: always
 */
  #ifndef EMBER_CALLBACK_POLL_COMPLETE
void emberPollCompleteHandler(EmberStatus status) {
  emberAfPollCompleteHandler(status);
}
  #endif // EMBER_CALLBACK_POLL_COMPLETE
#endif // EZSP_HOST
