// *****************************************************************************
// * af-eeprom.h
// *
// * Code for manipulating the EEPROM from the Application Framework
// * In particular, sleepies that use the EEPROM will require re-initialization
// * of the driver code after they wake up from sleep.  This code helps
// * manage the state of the driver. 
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

void emAfNoteEepromInitializedState(boolean state);
void emAfEepromInit(void);
int8u emAfEepromWrite(int32u address, const int8u *data, int16u totalLength);
int8u emAfEepromRead(int32u address, int8u *data, int16u totalLength);

