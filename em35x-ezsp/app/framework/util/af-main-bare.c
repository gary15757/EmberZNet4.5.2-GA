// *******************************************************************
// * af-main-bare.c
// *
// * This is a TEST file for helping to determine sizes of different 
// * pieces of the application.
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************
#include PLATFORM_HEADER     // Micro and compiler specific typedefs and macros

// Ember stack and related utilities
#include "stack/include/ember.h"         // Main stack definitions

// HAL - hardware abstraction layer
#include "hal/hal.h"
#include "app/util/serial/serial.h"  // Serial utility APIs

// CLI - command line interface
#include "app/util/serial/cli.h"

int main(void)
{
  EmberStatus status;

  //Initialize the hal
  halInit();
  INTERRUPTS_ON();  // Safe to enable interrupts at this point

  #ifdef DEBUG
  emberDebugInit(0);  // Use serial port 0 for debug output
  #endif

#if (EMBER_AF_BAUD_RATE == 9600)
  emberSerialInit(APP_SERIAL, BAUD_9600, PARITY_NONE, 1);
#elif (EMBER_AF_BAUD_RATE == 19200)
  emberSerialInit(APP_SERIAL, BAUD_19200, PARITY_NONE, 1);
#elif (EMBER_AF_BAUD_RATE == 38400)
  emberSerialInit(APP_SERIAL, BAUD_38400, PARITY_NONE, 1);
#elif (EMBER_AF_BAUD_RATE == 115200) 
  emberSerialInit(APP_SERIAL, BAUD_115200, PARITY_NONE, 1);
#else
  #error EMBER_AF_BAUD_RATE not set
#endif



  // Initialize the Ember Stack.
  status = emberInit();
  
  if (status != EMBER_SUCCESS) {
    assert(FALSE);
  } 

  while(TRUE) {
    halResetWatchdog();   // Periodically reset the watchdog.
    emberTick();          // Allow the stack to run.
    #ifdef DEBUG
    emberSerialBufferTick();   // Needed for buffered serial, which debug uses
    #endif
  }
}


#if (defined(BUTTON0) && defined(BUTTON1))
// WARNING: this callback is an ISR so the best approach is to set a
// flag here when an action should be taken and then perform the action
// somewhere else. In this case the actions are serviced in the appTick
// function
void halButtonIsr(int8u button, int8u state)
{}
#endif

void emberStackStatusHandler(EmberStatus status)
{}

// in form-and-join library
//void emberScanCompleteHandler( int8u channel, EmberStatus status )
//{}
//
//void emberEnergyScanResultHandler(int8u channel, int8s maxRssiValue)
//{}
//
//void emberNetworkFoundHandler(EmberZigbeeNetwork *networkFound)
//{}

void emberPollCompleteHandler(EmberStatus status)
{}

void emberPollHandler(EmberNodeId childId, boolean transmitExpected)
{}

void emberMessageSentHandler (EmberOutgoingMessageType type, 
                              int16u indexOrDestination, 
                              EmberApsFrame *apsFrame, 
                              EmberMessageBuffer message, 
                              EmberStatus status)
{}

void emberIncomingMessageHandler(EmberIncomingMessageType type,
                                 EmberApsFrame *apsFrame,
                                 EmberMessageBuffer message)
{}

void emberIncomingManyToOneRouteRequestHandler(EmberNodeId source,
                                               EmberEUI64 longId,
                                               int8u cost)
{}

int8u emberEndpointCount = 0;
int8u emberGetEndpoint(int8u index)
{}

boolean emberGetEndpointDescription(int8u endpoint,
                                    EmberEndpointDescription *result)
{}

int16u emberGetEndpointCluster(int8u endpoint,
                               EmberClusterListId listId,
                               int8u listIndex)
{}

// required by binding-table
EmberStatus emberRemoteSetBindingHandler(EmberBindingTableEntry *entry)
{}
EmberStatus emberRemoteDeleteBindingHandler(int8u index)
{}

// required by form-and-join
void scanError(EmberStatus status) 
{}

// required by CLI
int8u cliCmdListLen = 0;
PGM_P cliPrompt = "";
cliSerialCmdEntry cliCmdList[] = { {"null", 0} };

// used by ha-security-cli
// should this be protected by a security define?
EmberStatus emberGetKey(EmberKeyType type,
                        EmberKeyStruct* keyStruct)
{}
