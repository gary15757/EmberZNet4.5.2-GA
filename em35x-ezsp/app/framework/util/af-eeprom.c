// *****************************************************************************
// * af-eeprom.c
// *
// * Code for manipulating the EEPROM from the Application Framework
// * In particular, sleepies that use the EEPROM will require re-initialization
// * of the driver code after they wake up from sleep.  This code helps
// * manage the state of the driver. 
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include PLATFORM_HEADER     // Micro and compiler specific typedefs and macros

#include "app/framework/include/af.h"

// There is no good App. Builder #define for this yet.  So we turn on/off
// this code based on another plugin or a user set #define.
#if defined(EMBER_AF_PLUGIN_OTA_STORAGE_SIMPLE_EEPROM) \
 || defined(EMBER_AF_ENABLE_FRAMEWORK_EEPROM_INTERFACE)         // user #define

//------------------------------------------------------------------------------
// Globals

static boolean eepromInitialized = FALSE;

// NOTE:
// The underlying EEPROM driver MUST have support for arbitrary page writes
// (i.e. writes that cross page boundaries and or are smaller than the page size)
// Specifically the OTA Storage EEPROM Driver plugin code for storing OTA images
// requires this.
// The App. Bootloader for the 35x SOC prior to 4.3 did NOT have this in place.
// Therefore the shared app. bootloader EEPROM routines CANNOT be used; a copy
// of the EEPROM driver must be included with the application to support the OTA
// cluster.  
// The 4.3 App. bootloader for the 35x does have arbitrary page-write support
// and thus the shared EEPROM routines may be used on the 35x SOC.

// The 250 has no shared bootloader EEPROM routines and so the application
// must include a copy of the EEPROM driver.  The Host co-processor based models
// must also include an EEPROM driver in their application that has arbitrary 
// page-write support.

#if defined(EZSP_HOST) \
 || defined(EMBER_AF_PLUGIN_OTA_STORAGE_SIMPLE_EEPROM_ENABLE_SOC_APP_BOOTLOADER_COMPATIBILITY_MODE)
  #define eepromInit() halEepromInit()
  #define eepromWrite(address, data, len) \
    halEepromWrite((address), (data), (len))
  #define eepromRead(address, data, len) \
    halEepromRead((address), (data), (len))

#else // EM35x SOC with 4.3 bootloader or later
  #define eepromInit() halAppBootloaderInit()
  #define eepromWrite(address, data, len) \
    halAppBootloaderWriteRawStorage((address), (data), (len))
  #define eepromRead(address, data, len) \
    halAppBootloaderReadRawStorage((address), (data), (len))
#endif

//------------------------------------------------------------------------------

// Sleepies will likely need a re-initialization of the driver after sleep,
// so this code helps manage that state and automatically re-init the driver
// if it is needed.

static boolean isEepromInitialized(void)
{
  return eepromInitialized;
}

void emAfNoteEepromInitializedState(boolean state)
{
  eepromInitialized = state;
}

void emAfEepromInit(void)
{
  if (isEepromInitialized()) {
    return;
  }
  eepromInit();
  emAfNoteEepromInitializedState(TRUE);
}

int8u emAfEepromWrite(int32u address, const int8u *data, int16u totalLength)
{
  emAfEepromInit();
  return eepromWrite(address, data, totalLength);
}

int8u emAfEepromRead(int32u address, int8u *data, int16u totalLength)
{
  emAfEepromInit();
  return eepromRead(address, data, totalLength);
}

//------------------------------------------------------------------------------

#else

// NOTE:  I only stubbed the one routine below because it is the only necessary
// stub if the user doesn't use EEPROM routines.  If the user want to use
// the read/write EEPROM primitives of App. Builder than they are going to need
// an EEPROM driver and thus they should just turn on this code anyway.
// We can't provide any sensible stub for those read/write/init primitives.

void emAfNoteEepromInitializedState(boolean state)
{
}

#endif // defined(EMBER_AF_PLUGIN_OTA_STORAGE_SIMPLE_EEPROM)
       // || defined(EMBER_AF_ENABLE_FRAMEWORK_EEPROM_INTERFACE)
