// *******************************************************************
// * ias-zone-table.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the util
#include "../../util/common.h"

// clusters specific header
#include "ias-zone-table.h"

// --------------------------
// IAS ZONE TABLE
// --------------------------

// MES ASSUMPTION: this table is shared across endpoints.
static EmberAfIasZoneTableEntry zoneTable[ZONE_TABLE_SIZE];

/**
 * Populates a single entry in the zoneTable
 */
void enroll(int8u zid, int16u zt, int8u *ieee)
{
  zoneTable[zid].zoneType = zt;
  MEMCOPY(zoneTable[zid].ieeeAdd, ieee, 8);
}

/**
 * Clears a single entry in the zoneTable
 */
void unenroll(int8u zid)
{
  int8u ieee[8];
  MEMSET(ieee, ZONE_TABLE_VALUE_DEFAULT_8, 8);
  enroll(zid, ZONE_TABLE_VALUE_DEFAULT_16, ieee);
}

/**
 * Clears the entire zoneTable
 */
void initZoneTable()
{
  int16u i;
  for (i=0;i<ZONE_TABLE_SIZE;i++)
  {
    unenroll(i);
  }
}

/**
 * Returns EMBER_ZCL_STATUS_SUCCESS and populates zoneId with the next available zoneId, or
 * returns EMBER_ZCL_STATUS_FAILURE if the table is full. Runs in linear O(N) time.
 */
EmberAfStatus getNextZoneId(int8u *zoneId)
{
  int8u i;
  for (i=0; i<ZONE_TABLE_SIZE; i++)
  {
    if (zoneTable[i].zoneType == ZONE_TABLE_VALUE_DEFAULT_16)
    {
      zoneId[0] = i;
      return EMBER_ZCL_STATUS_SUCCESS;
    }
  }
  return EMBER_ZCL_STATUS_FAILURE;
}

/**
 * Modifies the passed array of int16us into a bitmap
 * representation of how the zoneTable is populated.
 * Table entries which are populated are represented by
 * a 1, those that are clear are represented by a 0.
 *
 * Note: This function assumes that the passed map
 * is properly sized according to ZONE_TABLE_MAP_SIZE
 * defined in ias-zone-table.h
 */
void getZoneIdMap(int16u *map)
{
  int8u i;

  // Clear the map
  for (i=0; i<ZONE_TABLE_MAP_SIZE; i++)
  {
    map[i] = 0;
  }

  // Populate the map
  for (i=0; i<ZONE_TABLE_SIZE; i++)
  {
    int8u mapIndex = i/16;
    int8u bitIndex = (15 - (i % 16));
    if (zoneTable[i].zoneType != ZONE_TABLE_VALUE_DEFAULT_16)
      map[mapIndex] |= (1 << bitIndex);
  }
}

/**
 * Returns a pointer into the zoneTable for the
 * given zoneId
 */
EmberAfIasZoneTableEntry *getZoneInfo(int8u zoneId)
{
  return &(zoneTable[zoneId]);
}

/**
 * Print debug function:
 * Prints out the passed zoneTable bitmap
 */
void printZoneIdMap (int16u *map)
{
  int8u i;

  emberAfIasZoneClusterPrintln("ZoneIdMap:");
  for (i=0; i<ZONE_TABLE_SIZE; i++)
  {
    int8u mapIndex = i/16;
    int8u bitIndex = 15 - (i % 16);
    if (map[mapIndex] & (1 << bitIndex))
    {
      emberAfIasZoneClusterPrint("1");
    }
    else
    {
      emberAfIasZoneClusterPrint("0");
    }

    if (bitIndex == 0)
    {
      emberAfIasZoneClusterPrintln("");
    }
  }
}

/**
 * Print debug function:
 * Prints out an entry in the zoneTable for the given zoneId
 */
void printZoneInfo(int8u zoneId)
{
  EmberAfIasZoneTableEntry *entry = &zoneTable[zoneId];
  emberAfCorePrint("tableEntry: %x, %2x, ", zoneId, entry->zoneType);
  emberAfCorePrintBuffer(entry->ieeeAdd, 8, FALSE);
  emberAfCorePrintln("");
  emberAfCoreFlush();
}

/**
 * A debug method to print out the entire zone table
 */
void printZoneTable()
{
  int8u i;
  for (i=0; i<ZONE_TABLE_SIZE; i++)
  {
    printZoneInfo(i);
  }
}
