// *******************************************************************
// * ota-cli-common.c
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

#include "app/framework/gen/callback.h"

// client and server use same storage interface
#include "app/framework/plugin/ota-storage-common/ota-storage.h"  

#if defined (EMBER_AF_PLUGIN_OTA_CLIENT) \
 || defined (EMBER_AF_PLUGIN_OTA_SERVER)

//------------------------------------------------------------------------------
// Globals

EmberCommandEntry otaCommands[] = {
  OTA_CLIENT_COMMANDS
  OTA_SERVER_COMMANDS
  { NULL }
};

#define MAX_TAGS 10
   
//------------------------------------------------------------------------------
// Forward Declarations

// Create a shorter name for printing to make the code more readable.
#define otaPrintln(...) emberAfOtaBootloadClusterPrintln(__VA_ARGS__)

//------------------------------------------------------------------------------
// Functions

void emAfOtaPrintAllImages(void)
{
  int8u i = 0;
  EmberAfOtaImageId id = emberAfOtaStorageIteratorFirstCallback();
  while (emberAfIsOtaImageIdValid(&id)) {
    EmberAfOtaHeader header;
    EmberAfTagData tagInfo[MAX_TAGS];
    int16u totalTags;
    otaPrintln("Image %d", i);
    if (EMBER_AF_OTA_STORAGE_SUCCESS
        != emberAfOtaStorageGetFullHeaderCallback(&id,
                                                  &header)) {
      otaPrintln("  ERROR: Could not get full header!");
    } else {
      otaPrintln("  Header Version: 0x%2X", header.headerVersion);
      otaPrintln("  Header Length:  %d bytes", header.headerLength);
      otaPrintln("  Field Control:  0x%2X", header.fieldControl);
      emberAfOtaBootloadClusterFlush();
      otaPrintln("  Manuf ID:       0x%2X", header.manufacturerId);
      otaPrintln("  Image Type:     0x%2X", header.imageTypeId);
      otaPrintln("  Version:        0x%4X", header.firmwareVersion);
      emberAfOtaBootloadClusterFlush();
      otaPrintln("  Zigbee Version: 0x%2X", header.zigbeeStackVersion);
      otaPrintln("  Header String:  %s",    header.headerString);
      otaPrintln("  Image Size:     %l bytes",    header.imageSize);
      emberAfOtaBootloadClusterFlush();
      if (headerHasSecurityCredentials(&header)) {
        otaPrintln("  Security Cred:  0x%X", header.securityCredentials);
      }
      if (headerHasUpgradeFileDest(&header)) {
        emberAfOtaBootloadClusterPrint("  Upgrade Dest:   ");
        emberAfOtaBootloadClusterDebugExec(emberAfPrintBigEndianEui64(header.upgradeFileDestination));
        emberAfOtaBootloadClusterFlush();
        otaPrintln("");
      }
      if (headerHasHardwareVersions(&header)) {
        otaPrintln("  Min. HW Ver:    0x%2X", header.minimumHardwareVersion);
        otaPrintln("  Max. HW Ver:    0x%2X", header.maximumHardwareVersion);
        emberAfOtaBootloadClusterFlush();
      }
      if (EMBER_AF_OTA_STORAGE_SUCCESS == emAfOtaStorageReadAllTagInfo(&id,
                                                                       tagInfo,
                                                                       MAX_TAGS,
                                                                       &totalTags)) {
        int16u i;
        otaPrintln("  Total Tags: %d", totalTags);
        for (i = 0; i < MAX_TAGS && i < totalTags; i++) {
          otaPrintln("    Tag: 0x%2X", tagInfo[i].id);
          otaPrintln("      Length: %l", tagInfo[i].length);
        }
        emberAfOtaBootloadClusterFlush();
      } else {
        otaPrintln("Error: Could not obtain tag info from image.");
      }
    }
    id = emberAfOtaStorageIteratorNextCallback();
    i++;
  }

  otaPrintln("\n%d images in OTA storage.", emberAfOtaStorageGetCountCallback());
}

EmberAfOtaImageId emAfOtaFindImageIdByIndex(int8u index)
{
  int8u i = 0;
  EmberAfOtaImageId id = emberAfOtaStorageIteratorFirstCallback();
  do {
    if (i == index) {
      return id;
    }
    i++;
    id = emberAfOtaStorageIteratorNextCallback();
  } while (emberAfIsOtaImageIdValid(&id));
  
  return emberAfInvalidImageId;
}

void emAfOtaImageDelete(void)
{
  int8u index = (int8u)emberUnsignedCommandArgument(0);
  EmberAfOtaImageId id = emAfOtaFindImageIdByIndex(index);

  if (!emberAfIsOtaImageIdValid(&id)) {
    otaPrintln("Error: No image at index %d", index);
    return;
  }
  if (EMBER_AF_OTA_STORAGE_SUCCESS
      == emberAfOtaStorageDeleteImageCallback(&id)) {
    otaPrintln("Image deleted.");
    return;
  }
  otaPrintln("Error: Failed to delete image.");
}


#endif
