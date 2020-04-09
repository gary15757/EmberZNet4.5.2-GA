// File: network-cli.c
//
// Copyright 2009 by Ember Corporation. All rights reserved.                *80*

#include "app/framework/util/common.h"
#include "app/framework/util/af-main.h"  // For APP_XXX_PRINT
#include "app/util/serial/command-interpreter2.h"

#include "network-cli.h"

// For zaNodeSecurityInit() and zaTrustCenterSecurityInit()
#include "app/framework/security/af-security.h"

//------------------------------------------------------------------------------

static void networkJoinCommand(void);
static void networkRejoinCommand(void);
static void networkFormCommand(void);
static void networkExtendedPanIdCommand(void);
static void networkLeaveCommand(void);
static void networkPermitJoinCommand(void);
static void findJoinableNetworkCommand(void);
static void findUnusedPanIdCommand(void);

#if defined(EMBER_AF_TC_SWAP_OUT_TEST)
  static void networkInitCommand(void);
#endif

/**
 * @addtogroup cli
 * @{
 */
/**
 * @brief 
 *        <b>network form &lt;channel&gt; &lt;power> &lt;panid></b>
 *        - <i>Form a network on a given channel, with a given Tx Power and Pan Id.</i>
 *           - <i>channel - int8u. The channel on which to form the network.</i>
 *           - <i>power   - int8s. One byte signed value indicating the TX power 
 *                                 That the radio should be set to.</i>
 *           - <i>panId   - int16u. The Pan Id on which to form the network.</i> 
 * 
 *        <b>network join &lt;channel&gt; &lt;power&gt; &lt;panid&gt;</b>
 *        - <i>Join a network on a given channel, with a given TX Power and Pan Id.</i>
 *           - <i>channel - int8u. The channel on which to join the network.</i>
 *           - <i>power   - int8s. One byte signed value indicating the TX power 
 *                                 That the radio should be set to.</i>
 *           - <i>panId   - int16u. The Pan Id on which to join the network.</i>
 *
 *        <b>network rejoin &lt;encrypted&gt;</b>
 *        - <i>Find and rejoin the previous network the device was connected to.</i>
 *           - <i>encrypted - int8u. A single byte boolean 0 or 1 indicating
 *                            whether or not the rejoin should be done with encryption.</i>
 *
 *        <b>network leave</b>
 *        - <i>Leave the current network that the device is connected to.</i>
 *
 *        <b>network pjoin &lt;seconds&gt;</b>
 *        - <i>Turn permit joining on for the amount of time indicated.</i>
 *           - <i>seconds - int8u. A single byte indicating how long the device
 *                         should have permit joining turn on for. A value of
 *                         0xff turns permit join of indefinitely.</i>
 *
 *        <b>network extpanid &lt;bytes&gt;</b>
 *        - <i>Write the extended pan id of the device.</i>
 *           - <i>bytes - byte array. An array of bytes which represent
 *                        the extended pan id for the device.</i>
 *
 *        <b>network find unused</b>
 *        - <i>Begins a search for an unused Channel and Pan Id. Will automatically
 *             form a network on the first unused Channel and Pan Id it finds.</i>
 * 
 *        <b>network find joinable</b>
 *        - <i>Begins a search for a joinable network. Will automatically
 *             attempt to join the first network it finds.</i>
 */
#define EMBER_AF_DOXYGEN_CLI__NETWORK_COMMANDS
/** @} END addtogroup */

// form and join library ocmmands.
static EmberCommandEntry findCommands[] = {
  {"joinable", findJoinableNetworkCommand, "" },
  {"unused",   findUnusedPanIdCommand, "" },
  { NULL },
};
EmberCommandEntry networkCommands[] = {
  {"form", networkFormCommand, "usv"},
  {"join", networkJoinCommand, "usv"},
  {"rejoin", networkRejoinCommand, "uw"},
  {"leave", networkLeaveCommand, ""},
  {"pjoin", networkPermitJoinCommand, "u"},
  {"extpanid", networkExtendedPanIdCommand, "b"},
  {"find", NULL, (PGM_P)findCommands},

#if defined(EMBER_AF_TC_SWAP_OUT_TEST)
  // Do not document this command.
  {"init", networkInitCommand, "" },
#endif

  { NULL }
};

//------------------------------------------------------------------------------

void emberAfPrintChannelListFromMask(int32u channelMask)
{
  int8u i;
  boolean firstPrint = TRUE;
  channelMask >>= 11;           // valid 802.15.4 channels start from 11
  for (i = 11; i <= 26; i++) {
    if (channelMask & 0x01UL) {
      emberAfAppPrint("%c %d", 
                      (firstPrint
                       ? ' '
                       : ','),
                      i);
      firstPrint = FALSE;
      emberAfAppFlush();
    }
    channelMask >>= 1;
  }
}

static void initNetworkParams(EmberNetworkParameters *networkParams)
{
  MEMSET(networkParams, 0, sizeof(EmberNetworkParameters));
  MEMCOPY(networkParams->extendedPanId, 
          emAfExtendedPanId,
          EXTENDED_PAN_ID_SIZE);
  networkParams->radioChannel = (int8u)emberUnsignedCommandArgument(0);
  networkParams->radioTxPower = (int8s)emberSignedCommandArgument(1);
  networkParams->panId = (int16u)emberUnsignedCommandArgument(2);
}

// network join <channel> <power> <panid>
static void networkJoinCommand(void)
{
  EmberStatus status;
  EmberNetworkParameters networkParams;
  initNetworkParams(&networkParams);
  status = emberAfJoinNetwork(&networkParams);
  emberAfAppPrintln("%p 0x%x", "join", status);
}

// network rejoin <haveCurrentNetworkKey:1> <channelMask:4>
static void networkRejoinCommand(void)
{
  boolean haveCurrentNetworkKey = (boolean)emberUnsignedCommandArgument(0);
  int32u channelMask = emberUnsignedCommandArgument(1);
  EmberStatus status = emberFindAndRejoinNetwork(haveCurrentNetworkKey,
                                                 channelMask);
  emberAfAppPrintln("%p 0x%x", "rejoin", status);
}

// network form <channel> <power> <panid>
static void networkFormCommand(void)
{
#if (ZA_DEVICE_TYPE == ZA_COORDINATOR)
  EmberStatus status;
  EmberNetworkParameters networkParams;
  initNetworkParams(&networkParams);
  status = emberAfFormNetwork(&networkParams);
  emberAfAppPrintln("%p 0x%x", "form", status);
  emberAfAppFlush();
#else  // (ZA_DEVICE_TYPE == ZA_COORDINATOR)
  emberAfAppPrintln("only coordinators can form");
#endif // (ZA_DEVICE_TYPE == ZA_COORDINATOR)
}

// network extpanid <8 BYTES>
static void networkExtendedPanIdCommand(void)
{
  emberAfCopyBigEndianEui64Argument(0, emAfExtendedPanId);
  emberAfAppPrint("ext. PAN ID: ");
  emberAfAppDebugExec(emberAfPrintBigEndianEui64(emAfExtendedPanId));
  emberAfAppPrintln("");
}

// network leave
static void networkLeaveCommand(void)
{
  EmberStatus status;
  status = emberLeaveNetwork();
  emberAfAppPrintln("%p 0x%x", "leave",  status);
}

// network pjoin <time>
static void networkPermitJoinCommand(void)
{
  int8u duration = (int8u)emberUnsignedCommandArgument(0);
  emAfPermitJoin(duration);

#if defined (ZA_SECURITY_RANDOM_LINK_KEY) && ZA_DEVICE_TYPE == ZA_COORDINATOR
  // Random link keys means that joining nodes don't have a preconfigured key
  // so we must send the NWK key in the clear.
  // This will automatically timeout in 30 seconds and stop sending the NWK
  // key in the clear.
  zaTrustCenterSetJoinPolicy(EMBER_SEND_KEY_IN_THE_CLEAR);
#endif
}

static void findJoinableNetworkCommand(void)
{
  emberAfStartSearchForJoinableNetwork();
}

static void findUnusedPanIdCommand(void)
{
  emberAfFindUnusedPanIdAndForm();
}

#if defined(EMBER_AF_TC_SWAP_OUT_TEST)
static void networkInitCommand(void)
{
  emAfNetworkInitReturnCodeStatus = emberNetworkInit();
  emberAfAppPrintln("Network Init returned: 0x%X", 
                    emAfNetworkInitReturnCodeStatus);
  emAfNetworkInit();
}
#endif
