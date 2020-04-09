// *******************************************************************
// * ias-zone-table.h
// *
// * The IAS ZONE Table maintains information related to the enrollment
// * of security devices as defined by the ZCL Security and Safety
// * Specification. (Document 075123r00ZB)
// *
// * This table provides for the functions required by the specification
// * including, enroll, unenroll, retrieval of the Zone Id Map and
// * retrieval of specific zone enrollment information.
// *
// * This table is intended to be included with any IAS Zone or ACE
// * client responsible for maintaining information related to zone
// * enrollment.
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#define ZONE_TABLE_SIZE 16
#define ZONE_ID_MAP_SECTION_SIZE 16
#define ZONE_TABLE_MAP_SIZE ZONE_TABLE_SIZE / ZONE_ID_MAP_SECTION_SIZE
#define ZONE_TABLE_VALUE_DEFAULT_8 0xff
#define ZONE_TABLE_VALUE_DEFAULT_16 0xffff

typedef struct {
  int16u zoneType;
  int8u ieeeAdd[8];
} EmberAfIasZoneTableEntry;

void enroll(int8u zoneId, int16u zoneType, int8u* ieeeAdd);
void unenroll(int8u zoneId);
void initZoneTable(void);
void getZoneIdMap(int16u *map);
EmberAfIasZoneTableEntry *getZoneInfo(int8u zoneId);
EmberAfStatus getNextZoneId(int8u* zoneId);
void printZoneIdMap(int16u *map);
void printZoneInfo(int8u zoneId);
void printZoneTable(void);
