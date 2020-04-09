// *******************************************************************
// * ota-cli-server.c
// *
// * Zigbee Over-the-air bootload cluster for upgrading firmware and 
// * downloading specific file.  This is the CLI to interact with the
// * main cluster code.
// * 
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "app/framework/util/common.h"
#include "app/util/serial/command-interpreter2.h"
#include "app/framework/plugin/ota-common/ota.h"
#include "app/framework/cli/ota-cli.h"
#include "app/framework/plugin/ota-server-policy/ota-server-policy.h"
#include "app/framework/plugin/ota-server/ota-server.h"

/**
 * @addtogroup cli
 * @{
 */
/**
 * @brief OTA Server CLI commands. Used to drive the OTA server.
 *        
 *        <b>zcl ota server notify &lt;destination&gt; &lt;payload type&gt; &lt;jitter&gt; 
 *             &lt;manuf-id&gt; &lt;device-id&gt; &lt;version&gt;</b>
 *        - <i>This command sends an OTA Image Notify message to the specified 
 *             destination indicating a new version of an image is available for 
 *             download.</i>
 *          - <i>destination - int16u.</i>  
 *          - <i>payload type - int8u. The payload type field is as follows:
 *            - 0: Include only jitter field
 *            - 1: Include jitter and manuf-id
 *            - 2: Include jitter, manuf-id, and device-id
 *            - 3: Include jitter, manuf-id, device-id, and version</i>
 *          - <i>jitter - int8u.</i>
 *          - <i>manuf-id - int16u.</i>
 *          - <i>device-id - int16u.</i>
 *          - <i>version - int16u.</i>
 *
 *            <i>All fields in the CLI command must be specified.  
 *            However if the payload type is less than 3, those 
 *            values will be ignored and not included in the message.</i>
 *
 *        <b>zcl ota server printImages</b>
 *        - <i>Prints all images that are stored in the OTA storage module 
 *             along with their index.</i>
 *
 *        <b>zcl ota server delete</b>
 *        - <i></i>
 *
 *        <b>zcl ota server upgrade</b>
 *        - <i></i>
 *
 *        <b>zcl ota server policy print</b>
 *        - <i>Prints the polices used by the OTA Server Policy Plugin.</I>
 *
 *        <b>zcl ota server policy query &lt;policy value&gt;</b>
 *        - <i>Sets the policy used by the OTA Server Policy Plugin 
 *             when it receives a query request from the client.</i>  
 *          - <i>policy value - int8u. The policy values are as follows:
 *            - 0: Upgrade if server has newer (default)
 *            - 1: Downgrade if server has older
 *            - 2: Reinstall if server has same
 *            - 3: No next version (no next image is available for download)</i>
 *
 *        <b>zcl ota server policy blockRequest &lt;policy value&gt;</b>
 *        - <i>Sets the policy used by the OTA Server Policy Plugin 
 *             when it receives an image block request.  
 *          - <i>policy value - int8u. The policy values are as follows:
 *            - 0: Send block (default)
 *            - 1: Delay download once for 2 minutes
 *            - 2: Always abort download after first block</i>
 *
 *        <b>zcl ota server policy upgrade &lt;policy value&gt;</b>
 *        - <i>Sets the policy used by the OTA Server Policy Plugin 
 *             when it receives an upgrade end request.  
 *          - <i>policy value - int8u. The policy values are as follows:
 *            - 0: Upgrade Now (default)
 *            - 1: Upgrade in 2 minutes
 *            - 2: Ask me later to upgrade</i>
 *
 *        <b>zcl ota server policy page-req-miss</b>
 *        - <i><i>
 *
 *        <b>zcl ota server policy page-req-sup</b>
 *        - <i></i>
 *
 */
#define EMBER_AF_DOXYGEN_CLI__OTA_SERVER_COMMANDS
/** @} END addtogroup */



#ifdef EMBER_AF_PLUGIN_OTA_SERVER

//------------------------------------------------------------------------------
// Globals

static void setPolicy(void);

#if defined(EMBER_AF_PLUGIN_OTA_SERVER_POLICY)
static EmberCommandEntry policyCommands[] = {
  { "print",        emAfOtaServerPolicyPrint, "" },
  { "query",        setPolicy, "v" },
  { "blockRequest", setPolicy, "v" },
  { "upgrade",      setPolicy, "v" },
  { "page-req-miss", setPolicy, "v" },
  { "page-req-sup",  setPolicy, "v" },
  { NULL },
};
#define POLICY_COMMANDS { "policy", NULL, (PGM_P)policyCommands},

#else
#define POLICY_COMMANDS
#endif

EmberCommandEntry otaServerCommands[] = {
  { "notify",      otaImageNotifyCommand, "vuuuvvv" },

  // These two are a duplicate of the same command on the client.  However
  // since devices may not have client and server defined, we need it here.
  { "printImages", emAfOtaPrintAllImages, "" },
  { "delete",         (CommandAction)emAfOtaImageDelete, "u"},

  // Instruct a device to upgrade now
  // Params:  nodeID endpoint
  { "upgrade",     otaSendUpgradeCommand, "vu" }, 

  POLICY_COMMANDS

  { NULL }
};

//------------------------------------------------------------------------------
// Forward Declarations


//------------------------------------------------------------------------------
// Functions

// zcl ota server notify <destination> <dst endpoint> <payload type>
//   <queryJitter> <manufacturer-id> <image-type-id> <firmware-version>
// Payload Type:
//   0 = jitter value only
//   1 = jitter and manufacuter id
//   2 = jitter, manufacuter id, and device id
//   3 = jitter, manufacuter id, device id, and firmware version
//
// The CLI requires all parameters, but if the payload type does not
// require that parameter, simply set it to 0.
void otaImageNotifyCommand(void)
{
  EmberAfOtaImageId id;
  EmberNodeId dest = (EmberNodeId)emberUnsignedCommandArgument(0);
  int8u endpoint = (int8u)emberUnsignedCommandArgument(1);
  int8u payloadType = (int8u)emberUnsignedCommandArgument(2);
  int8u jitter = (int8u)emberUnsignedCommandArgument(3);
  id.manufacturerId = (int16u)emberUnsignedCommandArgument(4);
  id.imageTypeId = (int16u)emberUnsignedCommandArgument(5);
  id.firmwareVersion = emberUnsignedCommandArgument(6);

  emberAfOtaServerSendImageNotifyCallback(dest,
                                          endpoint,
                                          payloadType,
                                          jitter,
                                          &id);
}


#if defined(EMBER_AF_PLUGIN_OTA_SERVER_POLICY)
static void setPolicy(void)
{
  int8u value = (int8u)emberUnsignedCommandArgument(0);
  if (emberCurrentCommand->name[0] == 'q') {
    emAfOtaServerSetQueryPolicy(value);
  } else if (emberCurrentCommand->name[0] == 'b') {
    emAfOtaServerSetBlockRequestPolicy(value);
  } else if (emberCurrentCommand->name[0] == 'u') {
    emAfOtaServerSetUpgradePolicy(value);
  } else if (emberCurrentCommand->name[0] == 'p') {
    if (emberCurrentCommand->name[9] == 'm') {
      emAfSetPageRequestMissedBlockModulus(value);
    } else if (emberCurrentCommand->name[9] == 's') {
      emAfOtaServerSetPageRequestPolicy(value);
    }
  }
}
#endif

void otaSendUpgradeCommand(void)
{
  EmberNodeId dest = (EmberNodeId)emberUnsignedCommandArgument(0);
  int8u endpoint = (int8u)emberUnsignedCommandArgument(1);
  EmberAfOtaImageId id;

  // The invalid image id is also the wild cards to tell any device
  // to upgrade, regardless of manufacturer Id, image type, or version.
  halCommonMemPGMCopy(&id, &emberAfInvalidImageId, sizeof(EmberAfOtaImageId));

  emberAfOtaServerSendUpgradeCommandCallback(dest, endpoint, &id);
}

#endif // (EMBER_AF_PLUGIN_OTA_SERVER)
