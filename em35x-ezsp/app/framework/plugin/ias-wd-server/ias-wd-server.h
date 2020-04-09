// *******************************************************************
// * ias-wd.h
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// ----------------------------------------------------------------------------
// Bits
// ----------------------------------------------------------------------------
#define ZCL_WARNING_INFO_MODE_MASK 0xF0
#define ZCL_WARNING_INFO_STOP      0x00
#define ZCL_WARNING_INFO_BURGLAR   0x10
#define ZCL_WARNING_INFO_FIRE      0x20
#define ZCL_WARNING_INFO_EMERGENCY 0x30

#define ZCL_WARNING_INFO_STROBE_MASK 0x0C
#define ZCL_WARNING_INFO_NO_STROBE   0x00
#define ZCL_WARNING_INFO_STROBE      0x04

#define ZCL_SQUAWK_INFO_MODE_MASK 0xF0
#define ZCL_SQUAWK_INFO_ARMED     0x00
#define ZCL_SQUAWK_INFO_DISARMED  0x10

#define ZCL_SQUAWK_INFO_STROBE_MASK 0x08
#define ZCL_SQUAWK_INFO_NO_STROBE   0x00
#define ZCL_SQUAWK_INFO_STROBE      0x08

#define ZCL_SQUAWK_INFO_LEVEL_MASK 0x03
#define ZCL_SQUAWK_INFO_LOW        0x00
#define ZCL_SQUAWK_INFO_MEDIUM     0x01
#define ZCL_SQUAWK_INFO_HIGH       0x02
#define ZCL_SQUAWK_INFO_VERY_HIGH  0x03
