// *******************************************************************
// * color-control.h
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// These two define the value of a "step". Color control
// spec mentions stepping commands as units, which may be different
// than changing the value of the actual hue and/or saturation by 1.
// Therefore step or move functions use these. You may set this to 1
// so that the "step" will be the same as changing value by 1.
// Note: the moveTo command will not use these value as they
// move continuously by 1 (or whatever needed by the tick).
#define ZCL_COLOR_CONTROL_HUE_STEP_UNIT 1
#define ZCL_COLOR_CONTROL_SATURATION_STEP_UNIT 1
#define ZCL_INVALID_COLOR_CONTROL_COMMAND_ID 0xFF
