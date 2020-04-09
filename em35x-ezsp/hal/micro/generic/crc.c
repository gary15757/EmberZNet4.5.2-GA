/** @file hal/micro/generic/crc.c
 *  @brief  Generic firmware source for Cyclic Redundancy Check calculations.
 *
 * <!-- Copyright 2004-2010 by Ember Corporation. All rights reserved.   *80*-->
 */

#include PLATFORM_HEADER
#include "hal/micro/crc.h"

/*
  16bit CRC notes:
  "CRC-CCITT"
    poly is g(X) = X^16 + X^12 + X^5 + 1  (0x1021)
    used in the FPGA (green boards and 15.4)
    initial remainder should be 0xFFFF
*/






int16u halCommonCrc16( int8u byte, int16u crc  )
{
  crc = (crc >> 8) | (crc << 8);
  crc ^= byte;
  crc ^= (crc & 0xff) >> 4;
  crc ^= (crc << 8) << 4;






  crc ^= ( (int8u) ( (int8u) ( (int8u) (crc & 0xff) ) << 5)) |
    ((int16u) ( (int8u) ( (int8u) (crc & 0xff)) >> 3) << 8);

  return crc;
}

//--------------------------------------------------------------
// CRC-32 
#define POLYNOMIAL              (0xEDB88320L)

int32u halCommonCrc32(int8u data, int32u accumulator)
{
  int8u jj;
  int32u previous;
  int32u oper;

  previous = (accumulator >> 8) & 0x00FFFFFFL;
  oper = (accumulator ^ data) & 0xFF;
  for (jj = 0; jj < 8; jj++) {
    oper = ((oper & 0x01)
                ? ((oper >> 1) ^ POLYNOMIAL)
                : (oper >> 1));
  }

  return (previous ^ oper);
}
