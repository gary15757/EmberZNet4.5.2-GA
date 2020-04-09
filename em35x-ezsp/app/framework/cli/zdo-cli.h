// *****************************************************************************
// * zdo-cli.h
// *
// * CLI commands for sending ZDO messages.
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

extern EmberCommandEntry zdoCommands[];

//#define EMBER_AF_ENABLE_TX_ZDO
#ifdef EMBER_AF_ENABLE_TX_ZDO
  #define ZDO_COMMANDS \
{"zdo", NULL, (PGM_P)zdoCommands},
#else
  #define ZDO_COMMANDS
#endif

