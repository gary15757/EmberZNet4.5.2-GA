// *******************************************************************
// * level-control.h
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// Rate of level control tick execution.
// To increase tick frequency (for more granular updates of device state based
// on level), increase LC_TICKS_PER_SECOND.
#define LC_TICKS_PER_SECOND 32
#define LC_TICK_TIME (MILLISECOND_TICKS_PER_SECOND / LC_TICKS_PER_SECOND)

#define LEVEL_CONTROL_MINIMUM_LEVEL 0x00
#define LEVEL_CONTROL_MAXIMUM_LEVEL 0xFF
