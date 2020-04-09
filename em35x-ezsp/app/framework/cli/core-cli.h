// *****************************************************************************
// * core-cli.h
// *
// * Core CLI commands used by all applications regardless of profile.
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

extern EmberCommandEntry debugPrintCommands[];
void emAfCliCountersCommand(void);
void emAfCliHelpCommand(void);
void emAfCliInfoCommand(void);
void emAfCliResetCommand(void);
void emAfCliEchoCommand(void);

#define EMBER_AF_CORE_COMMANDS                        \
  {"counters", emAfCliCountersCommand, ""},                  \
  {"help", emAfCliHelpCommand, ""},                          \
  {"reset", emAfCliResetCommand, ""},                    \
  {"echo",  emAfCliEchoCommand, "u" },

#define EMBER_AF_INFO_COMMAND {"info", emAfCliInfoCommand, ""},
