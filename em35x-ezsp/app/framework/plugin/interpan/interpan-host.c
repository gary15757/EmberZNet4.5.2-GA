// *******************************************************************
// * interpan-host.c
// *
// * Host-specific code related to the reception and processing of interpan
// * messages.
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "app/framework/include/af.h"
#include "interpan.h"
#include "app/framework/util/af-main.h"

//------------------------------------------------------------------------------

void ezspMacPassthroughMessageHandler(EmberMacPassthroughType messageType,
                                      int8u lastHopLqi,
                                      int8s lastHopRssi,
                                      int8u messageLength,
                                      int8u *messageContents)
{
  if (messageType != EMBER_MAC_PASSTHROUGH_SE_INTERPAN) {
    return;
  }
  emAfPluginInterpanProcessMessage(messageLength,
                                   messageContents);
}

EmberStatus emAfPluginInterpanSendRawMessage(int8u length, int8u* message)
{
  return ezspSendRawMessage(length, message);
}

void emberAfInterpanInitCallback(void)
{
  int8u value = EMBER_MAC_PASSTHROUGH_SE_INTERPAN;
  emberAfSetEzspValue(EZSP_VALUE_MAC_PASSTHROUGH_FLAGS,
                      1,
                      &value,
                      "MAC passthru");
}

EmberStatus emAfInterpanApsCryptMessage(boolean encrypt,
                                        int8u* message,
                                        int8u* messageLength,
                                        int8u apsHeaderEndIndex,
                                        EmberEUI64 remoteEui64)
{
#if defined(EMBER_AF_PLUGIN_INTERPAN_ALLOW_APS_ENCRYPTED_MESSAGES)
  #error Not supported by EZSP
#endif

  // Feature not yet supported on EZSP.
  return EMBER_LIBRARY_NOT_PRESENT;
}
