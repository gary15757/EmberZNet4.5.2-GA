// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generateStructs()
//

// Enclosing macro to prevent multiple inclusion
#ifndef __EMBER_AF_STRUCTS__
#define __EMBER_AF_STRUCTS__


// Generated structs from the metadata
// Struct for ReadAttributeStatusRecord
typedef struct _ReadAttributeStatusRecord {
  int16u attributeId;
  int8u status;
  int8u attributeType;
  int8u attributeLocation;
} ReadAttributeStatusRecord;


// Struct for WriteAttributeRecord
typedef struct _WriteAttributeRecord {
  int16u attributeId;
  int8u attributeType;
  int8u attributeLocation;
} WriteAttributeRecord;


// Struct for WriteAttributeStatusRecord
typedef struct _WriteAttributeStatusRecord {
  int8u status;
  int16u attributeId;
} WriteAttributeStatusRecord;


// Struct for ConfigureReportingRecord
typedef struct _ConfigureReportingRecord {
  int8u direction;
  int16u attributeId;
  int8u attributeType;
  int16u minimumReportingInterval;
  int16u maximumReportingInterval;
  int8u reportableChangeLocation;
  int16u timeoutPeriod;
} ConfigureReportingRecord;


// Struct for ConfigureReportingStatusRecord
typedef struct _ConfigureReportingStatusRecord {
  int8u status;
  int8u direction;
  int16u attributeId;
} ConfigureReportingStatusRecord;


// Struct for ReadReportingConfigurationRecord
typedef struct _ReadReportingConfigurationRecord {
  int8u status;
  int8u direction;
  int16u attributeId;
  int8u attributeType;
  int16u minimumReportingInterval;
  int16u maximumReportingInterval;
  int8u reportableChangeLocation;
  int16u timeoutPeriod;
} ReadReportingConfigurationRecord;


// Struct for ReadReportingConfigurationAttributeRecord
typedef struct _ReadReportingConfigurationAttributeRecord {
  int8u direction;
  int16u attributeId;
} ReadReportingConfigurationAttributeRecord;


// Struct for ReportAttributeRecord
typedef struct _ReportAttributeRecord {
  int16u attributeId;
  int8u attributeType;
  int8u attributeLocation;
} ReportAttributeRecord;


// Struct for DiscoverAttributesInfoRecord
typedef struct _DiscoverAttributesInfoRecord {
  int16u attributeId;
  int8u attributeType;
} DiscoverAttributesInfoRecord;


// Struct for SceneExtensionAttributeInfo
typedef struct _SceneExtensionAttributeInfo {
  int8u attributeType;
  int8u attributeLocation;
} SceneExtensionAttributeInfo;


// Struct for SceneExtensionFieldSet
typedef struct _SceneExtensionFieldSet {
  int16u clusterId;
  int8u length;
  int8u value;
} SceneExtensionFieldSet;


// Struct for BlockThreshold
typedef struct _BlockThreshold {
  int8u blockThreshold;
  int8u priceControl;
  int32u blockPeriodStartTime;
  int32u blockPeriodDurationMinutes;
  int8u fuelType;
  int32u standingCharge;
} BlockThreshold;


// Struct for Notification
typedef struct _Notification {
  int16u contentId;
  int8u statusFeedback;
} Notification;


// Struct for NeighborInfo
typedef struct _NeighborInfo {
  int8u* neighbor;
  int16s x;
  int16s y;
  int16s z;
  int8s rssi;
  int8u numberRssiMeasurements;
} NeighborInfo;


// Struct for ChatParticipant
typedef struct _ChatParticipant {
  int16u uid;
  int8u* nickname;
} ChatParticipant;


// Struct for ChatRoom
typedef struct _ChatRoom {
  int16u cid;
  int8u* name;
} ChatRoom;


// Struct for NodeInformation
typedef struct _NodeInformation {
  int16u uid;
  int16u address;
  int8u endpoint;
  int8u* nickname;
} NodeInformation;


// Void typedef for Identity which is empty.
// this will result in all the references to the data being as int8u*
typedef int8u Identity;


// Void typedef for EphemeralData which is empty.
// this will result in all the references to the data being as int8u*
typedef int8u EphemeralData;


// Void typedef for Smac which is empty.
// this will result in all the references to the data being as int8u*
typedef int8u Smac;


// Void typedef for Signature which is empty.
// this will result in all the references to the data being as int8u*
typedef int8u Signature;


#endif // __EMBER_AF_STRUCTS__
