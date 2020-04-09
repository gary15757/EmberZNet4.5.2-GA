#ifndef CUSTOM_CLI_H
 #define CUSTOM_CLI_H
 #ifdef EMBER_AF_ENABLE_CUSTOM_COMMANDS
   extern EmberCommandEntry customCommands[];
   #define CUSTOM_COMMANDS   {"custom", NULL, (PGM_P)customCommands},
 #else
   #ifndef CUSTOM_COMMANDS
     #define CUSTOM_COMMANDS
   #endif
 #endif
#endif

