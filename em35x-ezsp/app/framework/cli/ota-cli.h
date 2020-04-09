// *******************************************************************
// * ota-cli.h
// *
// * Zigbee Over-the-air bootload cluster for upgrading firmware and 
// * downloading specific file.  This is the CLI to interact with the
// * main cluster code.
// * 
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************


// Common CLI interface

#if defined (EMBER_AF_PLUGIN_OTA_CLIENT) || \
    defined (EMBER_AF_PLUGIN_OTA_SERVER)
  extern EmberCommandEntry otaCommands[];
  #define OTA_COMMANDS \
{"ota", NULL, (PGM_P)otaCommands},
#else
  #define OTA_COMMANDS
#endif

void emAfOtaPrintAllImages(void);
EmberAfOtaImageId emAfOtaFindImageIdByIndex(int8u index);

// Client CLI interface

#if defined (EMBER_AF_PLUGIN_OTA_CLIENT)
  extern EmberCommandEntry otaClientCommands[];
  #define OTA_CLIENT_COMMANDS \
{ "client", NULL, (PGM_P)otaClientCommands},
#else
  #define OTA_CLIENT_COMMANDS
#endif

void otaFindServerCommand(void);
void otaQueryServerCommand(void);
void otaUsePageRequestCommand(void);
void otaQuerySpecificFileCommand(void);
void otaSendUpgradeCommand(void);
void emAfOtaImageDelete(void);

// Server CLI interface

#if defined (EMBER_AF_PLUGIN_OTA_SERVER)
  extern EmberCommandEntry otaServerCommands[];
  #define OTA_SERVER_COMMANDS \
{ "server", NULL, (PGM_P)otaServerCommands},
#else
  #define OTA_SERVER_COMMANDS
#endif

void otaImageNotifyCommand(void);
