// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generateStackHandlerMacros()
//

// Enclosing macro to prevent multiple inclusion
#ifndef __EMBER_AF_STACK_HANDLERS__
#define __EMBER_AF_STACK_HANDLERS__


// Macros required for implemented stack handlers.


#ifdef EZSP_HOST
// This is called by the EZSP when a data poll to the parent is complete. See EZSP documentation for more information.
// 
// Application framework itself defines this callback and calls function emberAfEzspPollCompleteHandler(). If you wish to 
// add functionality to this handler, while still maintaining app framework functionality, then implement it yourself and make
// sure you call emberAfEzspPollCompleteHandler() function within your implementation of ezspPollCompleteHandler().
  #define EZSP_APPLICATION_HAS_POLL_COMPLETE_HANDLER

#else // ! EZSP_HOST
// This is called by the stack when a data poll to the parent is complete. See stack documentation for more information.
// 
// Application framework itself defines this callback and calls function emberAfPollCompleteHandler(). If you wish to 
// add functionality to this handler, while still maintaining app framework functionality, then implement it yourself and make
// sure you call emberAfPollCompleteHandler() function within your implementation of emberPollCompleteHandler().
  #define EMBER_APPLICATION_HAS_POLL_COMPLETE_HANDLER

#endif // EZSP_HOST
#endif // __EMBER_AF_STACK_HANDLERS__
