// *******************************************************************
// * basic.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "basic.h"
#include "gen/basic-callback.h"

void emberAfLoadAttributesFromDefaults(void);

boolean emberAfBasicClusterResetToFactoryDefaultsCallback(void)
{
  emberAfBasicClusterPrintln("RX: ResetToFactoryDefaultsCallback");
  emberAfLoadAttributesFromDefaults();
  emberAfPluginBasicResetToFactoryDefaultsCallback();
  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}
