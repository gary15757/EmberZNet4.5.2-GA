// *******************************************************************
// * zcl-cli.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// common include file
#include "app/framework/util/common.h"

#include "app/framework/util/af-main.h"
#include "app/framework/util/attribute-storage.h"
#include "app/framework/util/service-discovery.h"

#include "app/util/serial/command-interpreter2.h"
#include "app/framework/cli/security-cli.h"
#include "app/framework/cli/zcl-cli.h"
#include "app/framework/cli/ota-cli.h"

// ZCL
#include "app/framework/report/report-table.h"

#include "app/util/concentrator/concentrator.h"
#include "app/util/common/library.h"

#ifdef EZSP_HOST
  // the EM260 host needs to include the config file
  #include "app/framework/util/config.h"
#endif

#ifdef EMBER_AF_PLUGIN_GROUPS_SERVER
#include "app/framework/plugin/groups-server/groups-server.h"
#endif //EMBER_AF_PLUGIN_GROUPS_SERVER

#ifdef EMBER_AF_PLUGIN_IAS_ACE_ZONE
#include "app/framework/plugin/ias-ace-zone/ias-ace-server.h"
#endif //EMBER_AF_PLUGIN_IAS_ACE_ZONE

#ifdef EMBER_AF_PLUGIN_IDENTIFY
#include "app/framework/plugin/identify/identify.h"
#endif //EMBER_AF_PLUGIN_IDENTIFY

#ifdef EMBER_AF_PLUGIN_MESSAGING_CLIENT
#include "app/framework/plugin/messaging-client/messaging-client.h"
#endif //EMBER_AF_PLUGIN_MESSAGING_CLIENT

#ifdef EMBER_AF_PLUGIN_MESSAGING_SERVER
#include "app/framework/plugin/messaging-server/messaging-server.h"
#endif //EMBER_AF_PLUGIN_MESSAGING_SERVER

#ifdef EMBER_AF_PLUGIN_PRICE_CLIENT
#include "app/framework/plugin/price-client/price-client.h"
#endif //EMBER_AF_PLUGIN_PRICE_CLIENT

#ifdef EMBER_AF_PLUGIN_PRICE_SERVER
#include "app/framework/plugin/price-server/price-server.h"
#endif //EMBER_AF_PLUGIN_PRICE_SERVER

#ifdef EMBER_AF_PLUGIN_SCENES
#include "app/framework/plugin/scenes/scenes.h"
#endif //EMBER_AF_PLUGIN_SCENES

#ifdef EMBER_AF_PLUGIN_DRLC
#include "app/framework/plugin/drlc/demand-response-load-control.h"
#include "app/framework/plugin/drlc/load-control-event-table.h"
#endif //EMBER_AF_PLUGIN_DRLC

#ifdef EMBER_AF_PLUGIN_DRLC_SERVER
#include "app/framework/plugin/drlc-server/drlc-server.h"
#endif //EMBER_AF_PLUGIN_DRLC_SERVER

#ifdef EMBER_AF_PLUGIN_GENERIC_TUNNEL
#include "app/framework/plugin/generic-tunnel/generic-tunnel.h"
#endif //EMBER_AF_PLUGIN_GENERIC_TUNNEL

#ifdef EMBER_AF_PLUGIN_IAS_ACE_ZONE
#include "app/framework/plugin/ias-ace-zone/ias-zone-table.h"
#endif //EMBER_AF_PLUGIN_IAS_ACE_ZONE

#ifdef EMBER_AF_PLUGIN_BACNET_PROTOCOL_TUNNEL
#include "app/framework/plugin/bacnet-protocol-tunnel/bacnet-protocol-tunnel.h"
#endif //EMBER_AF_PLUGIN_BACNET_PROTOCOL_TUNNEL

#ifdef EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ENABLE
#include "app/framework/plugin/simple-metering-server/simple-metering-test.h"
#endif //EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ENABLE

//------------------------------------------------------------------------------
// Globals

// APP_SERIAL is set in the project files
 
// EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH is set in config.h
#define APP_ZCL_BUFFER_SIZE EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH

// The command-interpreter doesn't handle individual arguments longer than
// 255 bytes (since it is uses a 1-byte max-length value
#define APP_ZCL_BUFFER_SIZE_CLI \
  (APP_ZCL_BUFFER_SIZE > 255    \
   ? 255                        \
   : APP_ZCL_BUFFER_SIZE)

int8u appZclBuffer[APP_ZCL_BUFFER_SIZE];
int16u appZclBufferLen;
boolean zclCmdIsBuilt = FALSE;
EmberApsFrame globalApsFrame;

// a variable containing the number of messages sent from the CLI since the 
// last reset

#ifdef EMBER_AF_ENABLE_STATISTICS 
int32u haZclCliNumPktsSent = 0;
#endif

// flag to keep track of the fact that we just sent a read attr for time and
// we should set our time to the result of the read attr response
extern boolean emAfSyncingTime;

// The direction of global commands, changeable via the "zcl global direction"
// command.  By default, send from client to server, which is how the CLI always
// functioned in the past.
static int8u zclGlobalDirection = ZCL_FRAME_CONTROL_CLIENT_TO_SERVER;


// ******************************************************
// zcl command functions
// ******************************************************

static void emAfApsFrameEndpointSetup(int8u srcEndpoint,
                                      int8u dstEndpoint) {
  globalApsFrame.sourceEndpoint = (srcEndpoint == 0
                                   ? emberAfEndpointFromIndex(0)
                                   : srcEndpoint);
  globalApsFrame.destinationEndpoint = (dstEndpoint == 0
                                        ? emberAfEndpointFromIndex(0)
                                        : dstEndpoint);
  
}

// used by zclBufferSetup and emAfCliRawCommand
static void emAfApsFrameClusterIdSetup(int16u clusterId)
{
  // setup the global options and cluster ID
  // send command will setup profile ID and endpoints.
  globalApsFrame.options = EMBER_AF_DEFAULT_APS_OPTIONS;
  globalApsFrame.clusterId = clusterId;
}

// used by zclCommand and emAfCliRawCommand
static void cliBufferPrint(void)
{
  int8u cmdIndex = (appZclBuffer[0] & ZCL_MANUFACTURER_SPECIFIC_MASK) ? 4 : 2;
  zclCmdIsBuilt = TRUE;
  emberAfGuaranteedPrintln("Msg: clus 0x%2x, cmd 0x%x, len %d",
                           globalApsFrame.clusterId, 
                           appZclBuffer[cmdIndex], 
                           appZclBufferLen);
  emberAfGuaranteedPrint("buffer: ", appZclBufferLen);
  emberAfGuaranteedPrintBuffer(appZclBuffer, appZclBufferLen, TRUE);
  emberAfGuaranteedPrintln("");
}

// for sending raw (user defined) ZCL messages 
// raw <cluster> <data bytes>
// note: limited to 0xff bytes in length

void emAfCliRawCommand(void)
{
  int8u seqNumIndex, length;
  emAfApsFrameClusterIdSetup((int16u)emberUnsignedCommandArgument(0));
  emberCopyStringArgument(1, appZclBuffer, APP_ZCL_BUFFER_SIZE_CLI, FALSE);
  seqNumIndex = (appZclBuffer[0] & ZCL_MANUFACTURER_SPECIFIC_MASK) ? 3 : 1;
  appZclBuffer[seqNumIndex] = emberAfNextSequence();
  emberStringCommandArgument(1, &length);
  appZclBufferLen = length;
  cliBufferPrint();
}

static void zclBufferSetup(int8u frameType, int16u clusterId, int8u commandId) 
{
  emAfApsFrameClusterIdSetup(clusterId);
  appZclBuffer[0] = frameType | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER;
  appZclBuffer[1] = emberAfNextSequence();
  appZclBuffer[2] = commandId;  
  appZclBufferLen = 3;
}

static void zclBufferAddByte(int8u byte)
{
  appZclBuffer[appZclBufferLen] = byte;
  appZclBufferLen += 1;
}

static void zclBufferAddWord(int16u word)
{
  zclBufferAddByte(LOW_BYTE(word));
  zclBufferAddByte(HIGH_BYTE(word));
}

static void zclBufferAddInt32(int32u value)
{
  int8u i;
  for (i = 0; i < 4; i++) {
    zclBufferAddByte(LOW_BYTE(value));
    value = value >> 8;
  }
}

static void zclBufferAddBuffer(const int8u *buffer, int8u length)
{
  MEMCOPY(appZclBuffer + appZclBufferLen, buffer, length);
  appZclBufferLen += length;
}

// Made non-static to remove warnings
void zclBufferAddString(const int8u *buffer)
{
  zclBufferAddBuffer(buffer, emberAfStringLength(buffer) + 1);
}

static void zclBufferAddByteFromArgument(int8u index)
{
  zclBufferAddByte((int8u)emberUnsignedCommandArgument(index));
}

static void zclBufferAddWordFromArgument(int8u index)
{
  zclBufferAddWord((int16u)emberUnsignedCommandArgument(index));
}

static void zclBufferAddInt32FromArgument(int8u index)
{
  zclBufferAddInt32(emberUnsignedCommandArgument(index));
}

// Writes the length and contents of the string found at argIndex
// into the zcl buffer.
static void zclBufferAddLengthAndStringFromArgument(int8u argIndex)
{
  int8u length = emberCopyStringArgument(argIndex,
                                         appZclBuffer + appZclBufferLen + 1,
                                         16,
                                         FALSE);
  appZclBuffer[appZclBufferLen] = length;
  appZclBufferLen += length + 1;
}

// This function fully formats the zcl buffer given all the necessary data.
// The format string describes how the subsequent arguments are to be
// written into the zcl buffer.  The format characters are the same as
// those used by the command interpreter, namely:
// 'u'   A one-byte unsigned value.
// 'v'   A two-byte unsigned value encoded low byte first.
// 'w'   A four-byte unsigned value encoded from low to high byte.
// 'b'   A sequence of unsigned bytes.  The first supplied value is a
//       pointer to the data and the second value is the number of bytes.

void makeZclBuffer(int8u frameControl,
                   int16u clusterId,
                   int8u commandId,
                   char *format,
                   ...)
{
  int8u i = 0;
  va_list argPointer;
  zclBufferSetup(frameControl, clusterId, commandId);
  va_start(argPointer, format);
  
  while (format[i] != 0) {
    char command = format[i];
    switch (command) {
    case 'u':
      zclBufferAddByte(va_arg(argPointer, int));
      break;
    case 'v':
      zclBufferAddWord(va_arg(argPointer, int));
      break;
    case 'w':
      zclBufferAddInt32(va_arg(argPointer, int));
      break;
    case 'b': {
      int8u *contents = va_arg(argPointer, int8u *);
      int8u count = va_arg(argPointer, int);
      zclBufferAddByte(count);
      zclBufferAddBuffer(contents, count);
      break;
    }
    default:
      assert(FALSE);
    }
    i += 1;
  }

  va_end(argPointer);
  cliBufferPrint();
}

// Handles any zcl command where the argument list of the
// command is simply appended to the zcl buffer.  Handles argument types
// 'u', 'v', 'w', and 'b'.  String arguments are written with a length
// byte first.
void zclSimpleCommand(int8u frameControl,
                             int16u clusterId, 
                             int8u commandId)
{
  int8u i;
  zclBufferSetup(frameControl, clusterId, commandId);
  for (i = 0; i < EMBER_MAX_COMMAND_ARGUMENTS; i++) {
    int8u type = emberCurrentCommand->argumentTypes[i];
    switch (type) {
    case 'u':
      zclBufferAddByteFromArgument(i);
      break;
    case 'v':
      zclBufferAddWordFromArgument(i);
      break;
    case 'w':
      zclBufferAddInt32FromArgument(i);
      break;
    case 'b':
      zclBufferAddLengthAndStringFromArgument(i);
    case 0:
      goto kickout;
    }
  }
 kickout:
  cliBufferPrint();
}

#define zclSimpleClientCommand(clusterId, commandId) \
  zclSimpleCommand(ZCL_CLUSTER_SPECIFIC_COMMAND | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER, \
                   (clusterId), \
                   (commandId))

#define zclSimpleServerCommand(clusterId, commandId)             \
  zclSimpleCommand(ZCL_CLUSTER_SPECIFIC_COMMAND | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT, \
                   (clusterId), \
                   (commandId))

static void zclGlobalSetup(int8u commandId)
{
  int16u clusterId = (int16u)emberUnsignedCommandArgument(0);
  zclBufferSetup(ZCL_PROFILE_WIDE_COMMAND | zclGlobalDirection,
                 clusterId,
                 commandId);
  zclBufferAddWordFromArgument(1);  // attr id
  if (commandId != ZCL_READ_ATTRIBUTES_COMMAND_ID) {
    zclBufferAddByteFromArgument(2);
  } 
}

// zcl global direction <direction:1>
static void zclGlobalDirectionCommand(void) 
{
  zclGlobalDirection = ((((int8u)emberUnsignedCommandArgument(0))
                         == ZCL_DIRECTION_CLIENT_TO_SERVER)
                        ? ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                        : ZCL_FRAME_CONTROL_SERVER_TO_CLIENT);
}

static void zclGlobalReadCommand(void) 
{
  zclGlobalSetup(ZCL_READ_ATTRIBUTES_COMMAND_ID);
  cliBufferPrint();
}


// zcl global write <cluster:2> <attrID:2> <type:1> <data>
// zcl global uwrite <cluster:2> <attrID:2> <type:1> <data>
// zcl global nwrite <cluster:2> <attrID:2> <type:1> <data>
static void zclGlobalWriteCommand(void) 
{
  int8u type;
  int8u commandChar = emberCurrentCommand->name[0];
  int8u commandId = (commandChar == 'u'
                     ? ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID
                     : (commandChar == 'n'
                        ? ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID
                        : ZCL_WRITE_ATTRIBUTES_COMMAND_ID));
  zclGlobalSetup(commandId);
  type = appZclBuffer[5];

  if (emberAfIsThisDataTypeAStringType(type)) {
    // TODO: the maximum length of the string should be obtained from
    // the attribute size table.  Currently the following helper function
    // has a hard-coded maximum length of 16.
    zclBufferAddLengthAndStringFromArgument(3);
  } else {
    int8u length = emberAfGetDataSize(type);
    emberCopyStringArgument(3, 
                            appZclBuffer + appZclBufferLen, 
                            length, 
                            TRUE);  // pad with zeroes
    appZclBufferLen += length;    
  }

  cliBufferPrint();
}

// zcl global discover <cluster> <attrID:2> <max # to report:1>
static void zclGlobalDiscoverCommand(void)
{
  zclGlobalSetup(ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID);
  cliBufferPrint();
}

// zcl global report <src endpoint id:1> <cluster id:2> <attribute id:2> <mask:1>
static void zclGlobalReportCommand(void)
{
  EmberAfStatus status;
  EmberAfClusterId clusterId = (EmberAfClusterId)emberUnsignedCommandArgument(1);
  EmberAfAttributeId attributeId = (EmberAfAttributeId)emberUnsignedCommandArgument(2);
  int8u mask = (int8u)emberUnsignedCommandArgument(3);
  EmberAfAttributeType type;
  int8u size;
  int8u data[ATTRIBUTE_LARGEST];

  status = emberAfReadAttribute((int8u)emberUnsignedCommandArgument(0), // endpoint
                                clusterId,
                                attributeId,
                                (mask == 0
                                 ? CLUSTER_MASK_CLIENT
                                 : CLUSTER_MASK_SERVER),
                                data,
                                sizeof(data),
                                &type);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfReportingPrintln("ERR: reading attribute %x", status);
    return;
  }

  zclBufferSetup(ZCL_PROFILE_WIDE_COMMAND
                 | (mask == 0
                    ? ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                    : ZCL_FRAME_CONTROL_SERVER_TO_CLIENT),
                 clusterId,
                 ZCL_REPORT_ATTRIBUTES_COMMAND_ID);
  zclBufferAddWord(attributeId);
  zclBufferAddByte(type);

  size = (emberAfIsThisDataTypeAStringType(type)
          ? data[0] + 1
          : emberAfGetDataSize(type));
#if (BIGENDIAN_CPU)
  if (isThisDataTypeSentLittleEndianOTA(type)) {
    emberReverseMemCopy(appZclBuffer + appZclBufferLen, data, size);
  } else {
    MEMCOPY(appZclBuffer + appZclBufferLen, data, size);
  }
#else
  MEMCOPY(appZclBuffer + appZclBufferLen, data, size);
#endif
  appZclBufferLen += size;

  cliBufferPrint();
}

// zcl global report-read <cluster> <attrID:2> <direction:1>
static void zclGlobalReportReadCommand(void)
{
  zclBufferSetup(ZCL_PROFILE_WIDE_COMMAND | zclGlobalDirection,
                 (EmberAfClusterId)emberUnsignedCommandArgument(0), // cluster id
                 ZCL_READ_REPORTING_CONFIGURATION_COMMAND_ID);
  zclBufferAddByteFromArgument(2); // direction
  zclBufferAddWordFromArgument(1); // attribute id
  cliBufferPrint();
}

// zcl global send-me-a-report <cluster id:2> <attribute id:2> <type:1> ...
// ... <min interval:2> <max interval:2> <reportable change:1-4>
static void zclGlobalSendMeAReportCommand(void)
{
  int8u type = (int8u)emberUnsignedCommandArgument(2);

  zclBufferSetup(ZCL_PROFILE_WIDE_COMMAND | zclGlobalDirection,
                 (EmberAfClusterId)emberUnsignedCommandArgument(0), // cluster id
                 ZCL_CONFIGURE_REPORTING_COMMAND_ID);
  zclBufferAddByte(EMBER_ZCL_REPORTING_DIRECTION_REPORTED);
  zclBufferAddWordFromArgument(1);  // attribute id
  zclBufferAddByte(type);           // type
  zclBufferAddWordFromArgument(3);  // minimum reporting interval
  zclBufferAddWordFromArgument(4);  // maximum reporting interval

  // If the data type is analog, then the reportable change field is the same
  // size as the data type.  Otherwise, it is omitted.
  if (emberAfGetAttributeAnalogOrDiscreteType(type)
      == EMBER_AF_DATA_TYPE_ANALOG) {
    int8u dataSize = emberAfGetDataSize(type);
    emberCopyStringArgument(5,
                            appZclBuffer + appZclBufferLen,
                            dataSize,
                            FALSE);
    appZclBufferLen += dataSize;
  }
  cliBufferPrint();
}

#ifndef ZA_NO_REPORTING_OPTIMIZATION
// zcl global expect-report-from-me <cluster id:2> <attribute id:2> <timeout:2>
static void zclGlobalExpectReportFromMeCommand(void)
{
  zclBufferSetup(ZCL_PROFILE_WIDE_COMMAND | zclGlobalDirection,
                 (EmberAfClusterId)emberUnsignedCommandArgument(0), // cluster id
                 ZCL_CONFIGURE_REPORTING_COMMAND_ID);
  zclBufferAddByte(EMBER_ZCL_REPORTING_DIRECTION_RECEIVED);
  zclBufferAddWordFromArgument(1); // attribute id
  zclBufferAddWordFromArgument(2); // timeout
  cliBufferPrint();
}

// add-report-entry <node id:2> <src endpoint id:1> <dst endpoint:1> ...
// ... <cluster id:2> <attribute id:2> <mask:1> <type:1> <min interval:2> ...
// ... <max interval:2> <reportable change:1-4>
void emAfCliAddReportEntryCommand(void)
{
  EmberAfStatus status;
  int32u reportableChange = 0;
  EmberAfAttributeType type;

  // If the data type is analog, then the reportable change field is the same
  // size as the data type.  Otherwise, it is ignored.
  type = (EmberAfAttributeType)emberUnsignedCommandArgument(6);
  if (emberAfGetAttributeAnalogOrDiscreteType(type)
      == EMBER_AF_DATA_TYPE_ANALOG) {
    emberCopyStringArgument(9,
                            (int8u *)&reportableChange,
                            emberAfGetDataSize(type),
                            FALSE);
  }

  status = emberAfAddTxReportEntry((EmberNodeId)emberUnsignedCommandArgument(0),        // node id
                                   (int8u)emberUnsignedCommandArgument(1),              // src endpoint id
                                   (int8u)emberUnsignedCommandArgument(2),              // dst endpoint id
                                   (EmberAfClusterId)emberUnsignedCommandArgument(3),   // cluster id
                                   (EmberAfAttributeId)emberUnsignedCommandArgument(4), // attribute id
                                   (emberUnsignedCommandArgument(5) == 0
                                    ? CLUSTER_MASK_CLIENT
                                    : CLUSTER_MASK_SERVER),
                                   EMBER_AF_NULL_MANUFACTURER_CODE,
                                   type,
                                   (int16u)emberUnsignedCommandArgument(7),             // min interval
                                   (int16u)emberUnsignedCommandArgument(8),             // max interval
                                   reportableChange);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfReportingPrintln("ERR: adding report %x", status);
  }
}
#endif //ZA_NO_REPORTING_OPTIMIZATION

// zcl test response on
static void zclTestResponseOnCommand(void)
{
  emberAfSetNoReplyForNextMessage(FALSE);  
}

// zcl test response off
static void zclTestResponseOffCommand(void)
{
  emberAfSetNoReplyForNextMessage(TRUE);
}

#ifdef ZCL_USING_BASIC_CLUSTER_CLIENT
// zcl basic rtfd
static void zclBasicRtfdCommand(void)
{
  zclSimpleClientCommand(ZCL_BASIC_CLUSTER_ID, 
                         ZCL_RESET_TO_FACTORY_DEFAULTS_COMMAND_ID);
}
#endif


static void zclTimeCommand(void)
{
  emberAfSetTime(emberUnsignedCommandArgument(0));
}

#ifdef ZCL_USING_IDENTIFY_CLUSTER_CLIENT
// zcl identify id <identify time:2>
static void zclIdentifyIdCommand(void)
{
  zclSimpleClientCommand(ZCL_IDENTIFY_CLUSTER_ID, ZCL_IDENTIFY_COMMAND_ID);
}

// zcl identify query
static void zclIdentifyQueryCommand(void)
{
  zclSimpleClientCommand(ZCL_IDENTIFY_CLUSTER_ID, ZCL_IDENTIFY_QUERY_COMMAND_ID);
}
#endif // ZCL_USING_IDENTIFY_CLUSTER_CLIENT

#ifdef ZCL_USING_IDENTIFY_CLUSTER_SERVER
// zcl identify on <endpoint:1> <time:2>
static void zclIdentifyOnCommand(void)
{
  int16u time = (int16u)emberUnsignedCommandArgument(1);
  if (time == 0) {
    time = 60;
  }
  emberAfWriteAttribute((int8u)emberUnsignedCommandArgument(0), // endpoint
                        ZCL_IDENTIFY_CLUSTER_ID,
                        ZCL_IDENTIFY_TIME_ATTRIBUTE_ID,
                        CLUSTER_MASK_SERVER,
                        (int8u *)&time,
                        ZCL_INT16U_ATTRIBUTE_TYPE);
}

// zcl identify off <endpoint:1>
static void zclIdentifyOffCommand(void)
{
  int16u time = 0;
  emberAfWriteAttribute((int8u)emberUnsignedCommandArgument(0), // endpoint
                        ZCL_IDENTIFY_CLUSTER_ID,
                        ZCL_IDENTIFY_TIME_ATTRIBUTE_ID,
                        CLUSTER_MASK_SERVER,
                        (int8u *)&time,
                        ZCL_INT16U_ATTRIBUTE_TYPE);
}
#endif // ZCL_USING_IDENTIFY_CLUSTER_SERVER


#ifdef ZCL_USING_GROUPS_CLUSTER_CLIENT
// zcl groups add <group id:2> <name:16>
// zcl groups ad-if-id <group id:2> <name:16>
static void zclGroupsAddCommand(void)
{
  int8u commandId = (emberCurrentCommand->name[2] == 'd'
                     ? ZCL_ADD_GROUP_COMMAND_ID
                     : ZCL_ADD_GROUP_IF_IDENTIFYING_COMMAND_ID);
  zclSimpleClientCommand(ZCL_GROUPS_CLUSTER_ID, commandId);
}

// zcl groups view <group id:2>
static void zclGroupsViewCommand(void)
{
  zclSimpleClientCommand(ZCL_GROUPS_CLUSTER_ID, ZCL_VIEW_GROUP_COMMAND_ID);
}

// zcl groups get <count:1> [<group id:2> * count]
static void zclGroupsGetCommand(void)
{
  int8u i;
  int8u count = (int8u)emberUnsignedCommandArgument(0);
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_GROUPS_CLUSTER_ID,
                 ZCL_GET_GROUP_MEMBERSHIP_COMMAND_ID);
  zclBufferAddByte(count); // group count
  for (i = 0; i < count; i++) {
    zclBufferAddWordFromArgument(1 + i);
  }
  cliBufferPrint();
}

// zcl groups remove <group id:2>
static void zclGroupsRemoveCommand(void)
{
  zclSimpleClientCommand(ZCL_GROUPS_CLUSTER_ID, ZCL_REMOVE_GROUP_COMMAND_ID);
}

// zcl groups rmall
static void zclGroupsRemoveAllCommand(void)
{
  zclSimpleClientCommand(ZCL_GROUPS_CLUSTER_ID, 
                         ZCL_REMOVE_ALL_GROUPS_COMMAND_ID);
}
#endif //ZCL_USING_GROUPS_CLUSTER_CLIENT

#ifdef ZCL_USING_SCENES_CLUSTER_CLIENT
#ifdef ZCL_USING_ON_OFF_CLUSTER_CLIENT
static boolean addScenesOnOffValue;
#endif
#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_CLIENT
static int8u addScenesLevelValue;
#endif

// zcl scenes add <groupId:2> <sceneId:1> <trans time:2> <name>
static void zclScenesAddCommand(void)
{
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_SCENES_CLUSTER_ID,
                 ZCL_ADD_SCENE_COMMAND_ID);
  zclBufferAddWordFromArgument(0);
  zclBufferAddByteFromArgument(1);
  zclBufferAddWordFromArgument(2);
  zclBufferAddLengthAndStringFromArgument(3);

#ifdef ZCL_USING_ON_OFF_CLUSTER_CLIENT
  // cluster:2 len:1 value:1 (on/off extension)
  zclBufferAddWord(ZCL_ON_OFF_CLUSTER_ID);
  zclBufferAddByte(1);
  zclBufferAddByte(addScenesOnOffValue);
#endif //ZCL_USING_ON_OFF_CLUSTER_CLIENT

#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_CLIENT
  // cluster:2 len:1 value:1 (level control extension)
  zclBufferAddWord(ZCL_LEVEL_CONTROL_CLUSTER_ID);
  zclBufferAddByte(1);
  zclBufferAddByte(addScenesLevelValue);
#endif //ZCL_USING_LEVEL_CONTROL_CLUSTER_CLIENT

  cliBufferPrint();
}

// zcl scenes view <groupId:2> <sceneId:1>
static void zclScenesViewCommand(void)
{
  zclSimpleClientCommand(ZCL_SCENES_CLUSTER_ID, ZCL_VIEW_SCENE_COMMAND_ID);
}

// zcl scenes remove <groupId:2> <sceneId:1>
static void zclScenesRemoveCommand(void)
{
  zclSimpleClientCommand(ZCL_SCENES_CLUSTER_ID, ZCL_REMOVE_SCENE_COMMAND_ID);
}

// zcl scenes rmall <groupId:2>
static void zclScenesRemoveAllCommand(void)
{
  zclSimpleClientCommand(ZCL_SCENES_CLUSTER_ID, ZCL_REMOVE_ALL_SCENES_COMMAND_ID);
}

// zcl scenes store <groupId:2> <sceneId:1>
static void zclScenesStoreCommand(void)
{
  zclSimpleClientCommand(ZCL_SCENES_CLUSTER_ID, ZCL_STORE_SCENE_COMMAND_ID);
}

// zcl scenes recall <groupId:2> <sceneId:1>
static void zclScenesRecallCommand(void)
{
  zclSimpleClientCommand(ZCL_SCENES_CLUSTER_ID, ZCL_RECALL_SCENE_COMMAND_ID);
}

// zcl scenes get <groupId:2>
static void zclScenesGetMembershipCommand(void)
{
  zclSimpleClientCommand(ZCL_SCENES_CLUSTER_ID, ZCL_GET_SCENE_MEMBERSHIP_COMMAND_ID);
}

// zcl scenes set [on|off] <level:1>
static void zclScenesSetCommand(void)
{
#ifdef ZCL_USING_ON_OFF_CLUSTER_CLIENT
  addScenesOnOffValue = (emberCurrentCommand->name[1] == 'n');
#endif
#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_CLIENT
  addScenesLevelValue = (int8u)emberUnsignedCommandArgument(0);
#endif
}
#endif //ZCL_USING_SCENES_CLUSTER_CLIENT

#ifdef ZCL_USING_ON_OFF_CLUSTER_CLIENT
// zcl on-off [ off | on | toggle ]
static void zclOnOffCommand(void)
{
  int8u secondChar = emberCurrentCommand->name[1];
  int8u commandId = (secondChar == 'n'
                     ? ZCL_ON_COMMAND_ID
                     : (secondChar == 'f'
                        ? ZCL_OFF_COMMAND_ID
                        : ZCL_TOGGLE_COMMAND_ID));
  zclSimpleClientCommand(ZCL_ON_OFF_CLUSTER_ID, commandId);
}

#endif //ZCL_USING_ON_OFF_CLUSTER_CLIENT

#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_CLIENT
// zcl level-control mv-to-level [level:1] [trans time:2]
// zcl level-control o-mv-to-level [level:1] [trans time:2]
static void zclLevelControlMoveToLevelCommand(void) 
{
  int8u commandId = (emberCurrentCommand->name[0] == 'o'
                     ? ZCL_MOVE_TO_LEVEL_WITH_ON_OFF_COMMAND_ID
                     : ZCL_MOVE_TO_LEVEL_COMMAND_ID);
  zclSimpleClientCommand(ZCL_LEVEL_CONTROL_CLUSTER_ID, commandId);
}

// zcl level-control move [mode:1] [rate:1]
// zcl level-control o-move [mode:1] [rate:1]
static void zclLevelControlMoveCommand(void) 
{
  int8u commandId = (emberCurrentCommand->name[0] == 'o'
                     ? ZCL_MOVE_WITH_ON_OFF_COMMAND_ID
                     : ZCL_MOVE_COMMAND_ID);
  zclSimpleClientCommand(ZCL_LEVEL_CONTROL_CLUSTER_ID, commandId);
}

// zcl level-control step [step:1] [step size:1] [trans time:2]
// zcl level-control o-step [step:1] [step size:1] [trans time:2]
static void zclLevelControlStepCommand(void) 
{
  int8u commandId = (emberCurrentCommand->name[0] == 'o'
                     ? ZCL_STEP_WITH_ON_OFF_COMMAND_ID
                     : ZCL_STEP_COMMAND_ID);
  zclSimpleClientCommand(ZCL_LEVEL_CONTROL_CLUSTER_ID, commandId);
}

// zcl level-control stop
// zcl level-control ostop
static void zclLevelControlStopCommand(void) 
{
  int8u commandId = (emberCurrentCommand->name[0] == 'o'
                     ? ZCL_STOP_WITH_ON_OFF_COMMAND_ID
                     : ZCL_STOP_COMMAND_ID);
  zclSimpleClientCommand(ZCL_LEVEL_CONTROL_CLUSTER_ID, commandId);
}
#endif //ZCL_USING_LEVEL_CONTROL_CLUSTER_CLIENT

#ifdef ZCL_USING_THERMOSTAT_CLUSTER_CLIENT
// zcl tstat set <mode:1 int> <amount:1 int>
static void zclThermostatSetCommand(void)
{
  zclSimpleClientCommand(ZCL_THERMOSTAT_CLUSTER_ID, 
                         ZCL_SETPOINT_RAISE_LOWER_COMMAND_ID);
}
#endif // ZCL_USING_THERMOSTAT_CLUSTER_CLIENT

#ifdef ZCL_USING_IAS_ZONE_CLUSTER_SERVER
// zcl ias-zone enroll <zone type: 2 int> <manuf code: 2 int>
static void zclIasZoneEnrollCommand(void)
{
  zclSimpleServerCommand(ZCL_IAS_ZONE_CLUSTER_ID, 
                         ZCL_ZONE_ENROLL_REQUEST_COMMAND_ID);
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
}

// zcl ias-zone sc <zone status: 2 int> <ext status: 1 int>
static void zclIasZoneStatusChangeCommand(void)
{
  zclSimpleServerCommand(ZCL_IAS_ZONE_CLUSTER_ID,
                         ZCL_ZONE_STATUS_CHANGE_NOTIFICATION_COMMAND_ID);
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
}
#endif // ZCL_USING_IAS_ZONE_CLUSTER_SERVER

#ifdef EMBER_AF_PLUGIN_IAS_ACE_ZONE
// zcl ias-zclient pt
static void zclIasZoneClientPrintCommand(void)
{
  printZoneTable();
}
#endif // ZCL_USING_IAS_ZONE_CLUSTER_CLIENT

#ifdef ZCL_USING_IAS_ACE_CLUSTER_CLIENT
// zcl ias-ace a <int:1>
static void zclIasAceArmCommand(void)
{
  zclSimpleClientCommand(ZCL_IAS_ACE_CLUSTER_ID, ZCL_ARM_COMMAND_ID);
}

// zcl ias-ace b <zones as hex string>
static void zclIasAceBypassCommand(void)
{
  zclSimpleClientCommand(ZCL_IAS_ACE_CLUSTER_ID, ZCL_BYPASS_COMMAND_ID);
}

// zcl ias-ace e
static void zclIasAceEmergencyCommand(void)
{
  zclSimpleClientCommand(ZCL_IAS_ACE_CLUSTER_ID, ZCL_EMERGENCY_COMMAND_ID);
}

// zcl ias-ace f
static void zclIasAceFireCommand(void)
{
  zclSimpleClientCommand(ZCL_IAS_ACE_CLUSTER_ID, ZCL_FIRE_COMMAND_ID);
}

// zcl ias-ace p
static void zclIasAcePanicCommand(void)
{
  zclSimpleClientCommand(ZCL_IAS_ACE_CLUSTER_ID, ZCL_PANIC_COMMAND_ID);
}

// zcl ias-ace getzm
static void zclIasAceGetZoneMapCommand(void)
{
  zclSimpleClientCommand(ZCL_IAS_ACE_CLUSTER_ID, 
                         ZCL_GET_ZONE_ID_MAP_COMMAND_ID);
}

// zcl ias-ace getzi <zone id:1>
static void zclIasAceGetZoneInfoCommand(void)
{
  zclSimpleClientCommand(ZCL_IAS_ACE_CLUSTER_ID, 
                         ZCL_GET_ZONE_INFORMATION_COMMAND_ID);
}
#endif // ZCL_USING_IAS_ACE_CLUSTER_CLIENT

#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_CLIENT
// zcl colorcontrol movetohue <hue:1> <direction:1> <transition time:2>
static void zclColorControlMoveToHueCommand(void)
{
  zclSimpleClientCommand(ZCL_COLOR_CONTROL_CLUSTER_ID,
                         ZCL_MOVE_TO_HUE_COMMAND_ID);
}

// zcl colorcontrol movehue <move mode:1> <rate:1>
static void zclColorControlMoveHueCommand(void)
{
  zclSimpleClientCommand(ZCL_COLOR_CONTROL_CLUSTER_ID, ZCL_MOVE_HUE_COMMAND_ID);
}

// zcl colorcontrol stephue <step mode:1> <step size:1> <transition time:1>
static void zclColorControlStepHueCommand(void)
{
  zclSimpleClientCommand(ZCL_COLOR_CONTROL_CLUSTER_ID, ZCL_STEP_HUE_COMMAND_ID);
}

// zcl colorcontrol movetosat <saturation:1> <transition time:2>
static void zclColorControlMoveToSatCommand(void)
{
  zclSimpleClientCommand(ZCL_COLOR_CONTROL_CLUSTER_ID,
                         ZCL_MOVE_TO_SATURATION_COMMAND_ID);
}

// zcl colorcontrol movesat <move mode:1> <rate:1>
static void zclColorControlMoveSatCommand(void)
{
  zclSimpleClientCommand(ZCL_COLOR_CONTROL_CLUSTER_ID,
                         ZCL_MOVE_SATURATION_COMMAND_ID);
}

// zcl colorcontrol stepsat <step mode:1> <step size:1> <transition time:1>
static void zclColorControlStepSatCommand(void)
{
  zclSimpleClientCommand(ZCL_COLOR_CONTROL_CLUSTER_ID,
                         ZCL_STEP_SATURATION_COMMAND_ID);
}

// zcl colorcontrol movetohueandsat <hue:1> <saturation:1> <transition time:2>
static void zclColorControlMoveToHueAndSatCommand(void)
{
  zclSimpleClientCommand(ZCL_COLOR_CONTROL_CLUSTER_ID,
                         ZCL_MOVE_TO_HUE_AND_SATURATION_COMMAND_ID);
}

// zcl movetocolor <color x:2> <color y:2> <transition time:2>
static void zclColorControlMoveToColorCommand(void)
{
  zclSimpleClientCommand(ZCL_COLOR_CONTROL_CLUSTER_ID,
                         ZCL_MOVE_TO_COLOR_COMMAND_ID);
}    

// zcl movecolor <rate x:2> <rate y:2>
static void zclColorControlMoveColorCommand(void)
{
  zclSimpleClientCommand(ZCL_COLOR_CONTROL_CLUSTER_ID,
                         ZCL_MOVE_COLOR_COMMAND_ID);
}    

// zcl stepcolor <step x:2> <step y:2> <transition time:2>
static void zclColorControlStepColorCommand(void)
{
  zclSimpleClientCommand(ZCL_COLOR_CONTROL_CLUSTER_ID,
                         ZCL_STEP_COLOR_COMMAND_ID);
}    

// zcl movetocolortemp <color temperature:2> <transition time:2>
static void zclColorControlMoveToColorTemperatureCommand(void)
{
  zclSimpleClientCommand(ZCL_COLOR_CONTROL_CLUSTER_ID,
                         ZCL_MOVE_TO_COLOR_TEMPERATURE_COMMAND_ID);
}    
#endif // ZCL_USING_COLOR_CONTROL_CLUSTER_CLIENT


#ifdef ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_SERVER

// zcl drlc lce <eventId:4> <start:4> <duration:2> <event control:1>
static void zclDrlcLoadControlEventCommand(void)
{
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,
                 ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID,
                 ZCL_LOAD_CONTROL_EVENT_COMMAND_ID);
  zclBufferAddInt32FromArgument(0);  // event id
  zclBufferAddWord(0x0fff);          // all device classes
  zclBufferAddByte(0);               // all uegs
  zclBufferAddInt32FromArgument(1);  // start
  zclBufferAddWordFromArgument(2);   // duration
  zclBufferAddByte(1);               // criticality level, normal
  zclBufferAddByte(0);               // 1.1c cooling temp offset
  zclBufferAddByte(0);               // 1.1c heating temp offset
  zclBufferAddWord(0x1a09);          // cool temp set point 23.3c
  zclBufferAddWord(0x1a09);          // heat temp set point
  zclBufferAddByte(0x0a);            // -10% avg load percent
  zclBufferAddByte(0);               // duty cycle
  zclBufferAddByteFromArgument(3);   // event control
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}

#ifdef EMBER_AF_PLUGIN_DRLC_SERVER
// zcl drlc slce <index:1> <length:1> <load control event bytes>
// load control event bytes are expected as 23 raw bytes in the form 
// {<eventId:4> <deviceClass:2> <ueg:1> <startTime:4> <duration:2> <criticalityLevel:1>
//  <coolingTempOffset:1> <heatingTempOffset:1> <coolingTempSetPoint:2> <heatingTempSetPoint:2>
//  <afgLoadPercentage:1> <dutyCycle:1> <eventControl:1> } all multibyte values should be 
// little endian as though they were coming over the air.
// Example: zcl drlc slce 0 23 { ab 00 00 00 ff 0f 00 00 00 00 00 01 00 01 00 00 09 1a 09 1a 0a 00 }
static void zclDrlcScheduleLoadControlEventCommand(void)
{
  int8u index = (int8u)emberUnsignedCommandArgument(0);
  int8u length = (int8u)emberUnsignedCommandArgument(1);
  int8u slceBuffer[sizeof(EmberAfLoadControlEvent)];
  EmberAfLoadControlEvent *event = emAfGetScheduledLoadControlEvent(index);

  if (event == NULL) {
    emberAfDemandResponseLoadControlClusterPrintln("slce fail, index out of range.");
    return;
  }
  if (length > sizeof(EmberAfLoadControlEvent)) {
    emberAfDemandResponseLoadControlClusterPrintln("slce fail, length: %x, max: %x", length, sizeof(EmberAfLoadControlEvent));
    return;
  }
  emberCopyStringArgument(2, slceBuffer, length, FALSE);

  event->eventId = emberAfGetInt32u(slceBuffer, 0, length) ;
  event->deviceClass = emberAfGetInt16u(slceBuffer, 4, length);
  event->utilityEnrollmentGroup = emberAfGetInt8u(slceBuffer, 6, length);
  event->startTime = emberAfGetInt32u(slceBuffer, 7, length);
  event->duration = emberAfGetInt16u(slceBuffer, 11, length);
  event->criticalityLevel = emberAfGetInt8u(slceBuffer, 13, length);
  event->coolingTempOffset = emberAfGetInt8u(slceBuffer, 14, length);
  event->heatingTempOffset = emberAfGetInt8u(slceBuffer, 15, length);
  event->coolingTempSetPoint = emberAfGetInt16u(slceBuffer, 16, length);
  event->heatingTempSetPoint = emberAfGetInt16u(slceBuffer, 18, length);
  event->avgLoadPercentage = emberAfGetInt8u(slceBuffer, 20, length);
  event->dutyCycle = emberAfGetInt8u(slceBuffer, 21, length);
  event->eventControl = emberAfGetInt8u(slceBuffer, 22, length);
  event->source[0] = 0x00; //activate the event in the table
  emberAfDemandResponseLoadControlClusterPrintln("DRLC event scheduled on server.");
}

// zcl drlc sslce <index:1>
// Reads a scheduled load control event into the send buffer so that it can be sent
static void zclDrlcSendScheduledLoadControlEventCommand(void) {
  int8u index = (int8u)emberUnsignedCommandArgument(0);
  EmberAfLoadControlEvent *event = emAfGetScheduledLoadControlEvent(index);

  if (event == NULL) {
    emberAfDemandResponseLoadControlClusterPrintln("send slce fail, index out of range.");
    return;
  }
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,
                 ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID,
                 ZCL_LOAD_CONTROL_EVENT_COMMAND_ID);
  zclBufferAddInt32(event->eventId);  
  zclBufferAddWord(event->deviceClass);
  zclBufferAddByte(event->utilityEnrollmentGroup);
  zclBufferAddInt32(event->startTime);
  zclBufferAddWord(event->duration);
  zclBufferAddByte(event->criticalityLevel);
  zclBufferAddByte(event->coolingTempOffset);
  zclBufferAddByte(event->heatingTempOffset);
  zclBufferAddWord(event->coolingTempSetPoint);
  zclBufferAddWord(event->heatingTempSetPoint);
  zclBufferAddByte(event->avgLoadPercentage);
  zclBufferAddByte(event->dutyCycle);
  zclBufferAddByte(event->eventControl);   // event control
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}

#endif //EMBER_AF_PLUGIN_DRLC_SERVER

// zcl drlc cl <eventId:4> <device class:2> <ueg: 1> <cancel control: 1> <start time:4>
static void zclDrlcCancelCommand(void)
{
  zclSimpleServerCommand(ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID,
                         ZCL_CANCEL_LOAD_CONTROL_EVENT_COMMAND_ID);
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
}

// zcl drlc ca
static void zclDrlcCancelAllCommand(void)
{
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,
                 ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID,
                 ZCL_CANCEL_ALL_LOAD_CONTROL_EVENTS_COMMAND_ID);
  zclBufferAddByte(0);  // bogus time
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}

#endif //ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_SERVER

#ifdef ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT
// zcl drlc gse <int:1>
static void zclDrlcGetScheduledEventsCommand(void)
{
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID,
                 ZCL_GET_SCHEDULED_EVENTS_COMMAND_ID);
  zclBufferAddInt32(0);  // now
  zclBufferAddByteFromArgument(0);
  cliBufferPrint();
}

#ifdef EMBER_AF_PLUGIN_DRLC
// zcl drlc opt <in | out> <id:4>
static void zclDrlcOptInOrOutCommand(void)
{
  emAfLoadControlEventOptInOrOut(emberUnsignedCommandArgument(0), 
                                 emberCurrentCommand->name[0] == 'i');
}
#endif //EMBER_AF_PLUGIN_DRLC

#endif //ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT


#ifdef ZCL_USING_SIMPLE_METERING_CLUSTER_CLIENT
// zcl sm  gp <type:1> <time:4> <intervals:1>
static void zclSimpleMeteringGetProfileCommand(void)
{
  zclSimpleClientCommand(ZCL_SIMPLE_METERING_CLUSTER_ID,
                         ZCL_GET_PROFILE_COMMAND_ID);
}

// zcl sm fp <update period:1> <duration:1>
static void zclSimpleMeteringFastPollCommand(void)
{
  zclSimpleClientCommand(ZCL_SIMPLE_METERING_CLUSTER_ID,
                         ZCL_REQUEST_FAST_POLL_MODE_COMMAND_ID);
}
#endif //ZCL_USING_SIMPLE_METERING_CLUSTER_CLIENT

#ifdef ZCL_USING_SIMPLE_METERING_CLUSTER_SERVER
// zcl sm rm
static void zclSimpleMeteringRequestMirrorCommand(void)
{
  zclSimpleServerCommand(ZCL_SIMPLE_METERING_CLUSTER_ID,
                         ZCL_REQUEST_MIRROR_COMMAND_ID);
}

// zcl sm dm
static void zclSimpleMeteringDeleteMirrorCommand(void)
{
  zclSimpleServerCommand(ZCL_SIMPLE_METERING_CLUSTER_ID,
                         ZCL_MIRROR_REMOVED_COMMAND_ID);
}
#endif //ZCL_USING_SIMPLE_METERING_CLUSTER_SERVER

int8u getEndpointArgument(int8u index)
{
  int8u endpoint = (int8u)emberUnsignedCommandArgument(index);
  return (endpoint == 0
          ? emberAfEndpointFromIndex(0)
          : endpoint);
}

#ifdef EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ENABLE
// zcl tm print
static void zclTestMeterPrintCommand(void) 
{
  afTestMeterPrint();
}

// zcl tm rate <int:2>
static void zclTestMeterRateCommand(void)
{
  afTestMeterSetConsumptionRate((int16u)emberUnsignedCommandArgument(0));
}

// zcl tm variance <int:2>
static void zclTestMeterVarianceCommand(void)
{
  afTestMeterSetConsumptionVariance((int16u)emberUnsignedCommandArgument(0));
}

// zcl tm adjust <endpoint:1>
static void zclTestMeterAdjustCommand(void)
{
  afTestMeterAdjust(getEndpointArgument(0));
}

// zcl tm off <endpoint: 1>
static void zclTestMeterOffCommand(void)
{
  afTestMeterMode(getEndpointArgument(0), 0);
}

#if (EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_TYPE == ELECTRIC_METER)
// zcl tm electric <endpoint:1>
static void zclTestMeterElectricCommand(void)
{
  afTestMeterMode(getEndpointArgument(0), 1);
}
#endif

#if (EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_TYPE == GAS_METER)
// zcl tm gas <endpoint:1>
static void zclTestMeterGasCommand(void)
{
  afTestMeterMode(getEndpointArgument(0), 2);
}
#endif

#ifdef EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ERRORS
// zcl tm rnd_error <data:1>
static void zclTestMeterRandomErrorCommand(void)
{
  // enables random error setting at each tick
  afTestMeterRandomError((int8u)emberUnsignedCommandArgument(0));  
}

// zcl tm set_error <data:1> <endpoint:1>
static void zclTestMeterSetErrorCommand(void)
{
  // sets error, in the process overriding random_error
  afTestMeterSetError(getEndpointArgument(1), 
                      (int8u)emberUnsignedCommandArgument(0));                           
}
#endif //EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ERRORS

#if ( EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES != 0 )
// zcl tm pofiles <data:1>
static void zclTestMeterProfilesCommand(void)
{
  afTestMeterEnableProfiles((int8u)emberUnsignedCommandArgument(0));
}
#endif
#endif //EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ENABLE


#ifdef ZCL_USING_PRICE_CLUSTER_CLIENT
// zcl price current
static void zclPriceGetCurrentCommand(void)
{
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_PRICE_CLUSTER_ID,
                 ZCL_GET_CURRENT_PRICE_COMMAND_ID);
  zclBufferAddByte(0);  // command options
  cliBufferPrint();
}

// zcl price scheduled <startTime:4> <num-events:1>
static void zclPriceGetScheduleCommand(void)
{
  zclSimpleClientCommand(ZCL_PRICE_CLUSTER_ID,
                         ZCL_GET_SCHEDULED_PRICES_COMMAND_ID);
}
#endif //ZCL_USING_PRICE_CLUSTER_CLIENT

#ifdef EMBER_AF_PLUGIN_PRICE_SERVER
// zcl set-price clear
static void zclPriceClearCommand(void)
{
  emberAfPriceClearPriceTable();
}

static EmberAfScheduledPrice *getPriceArgument(void)
{
  // figure out which price we are setting
  int8u priceIndex = (int8u)emberUnsignedCommandArgument(0);
  EmberAfScheduledPrice *price = emberAfPriceGetPriceTableEntry(priceIndex);
  if (price == NULL) {
    emberAfPriceClusterPrintln("price entry %d not present", priceIndex);
    return NULL;
  }
  price->valid = TRUE;
  return price;
}

// zcl set-price who <price index:1> <provId:4> <label:1-13> <eventId:4>
static void zclPriceSetWhoCommand(void)
{
  int8u length;
  EmberAfScheduledPrice *price = getPriceArgument();
  if (price == NULL)
    return;
  price->providerId = emberUnsignedCommandArgument(1);
  length = emberCopyStringArgument(2, price->rateLabel + 1, 12, FALSE);
  price->rateLabel[0] = length; 
  price->issuerEventID = emberUnsignedCommandArgument(3);
}  

// zcl set-price what <price index:1> <unitOfMeas:1> <curr:2> <ptd:1> <PTRT:1>
static void zclPriceSetWhatCommand(void)
{
  EmberAfScheduledPrice *price = getPriceArgument();
  if (price == NULL)
    return;
  price->unitOfMeasure = (int8u)emberUnsignedCommandArgument(1);
  price->currency = (int16u)emberUnsignedCommandArgument(2);
  price->priceTrailingDigitAndTier = (int8u)emberUnsignedCommandArgument(3);
  price->numberOfPriceTiersAndTier = (int8u)emberUnsignedCommandArgument(4);
}

// zcl set-price when <price index:1> <startTime:4> <duration:2>
static void zclPriceSetWhenCommand(void)
{
  EmberAfScheduledPrice *price = getPriceArgument();
  if (price == NULL)
    return;
  price->startTime = emberUnsignedCommandArgument(1);
  price->duration = (int16u)emberUnsignedCommandArgument(2);
}

// zcl set-price price <price index:1> <price:4> <ratio:1> <genPrice:4> <genRatio:1>
//                     <altCostDelivered:4> <altCostUnit:1> <altCostTrailingDigit:1>
//                     <numBlockThresholds:1> <priceControl:1>
static void zclPriceSetPriceCommand(void)
{
  EmberAfScheduledPrice *price = getPriceArgument();
  if (price == NULL)
    return;
  price->price = emberUnsignedCommandArgument(1);
  price->priceRatio = (int8u)emberUnsignedCommandArgument(2);
  price->generationPrice = emberUnsignedCommandArgument(3);
  price->generationPriceRatio = (int8u)emberUnsignedCommandArgument(4);
  //  price->alternateCostDelivered = emberUnsignedCommandArgument(5);
  //  price->alternateCostUnit = emberUnsignedCommandArgument(6);
  //  price->alternateCostTrailingDigit = emberUnsignedCommandArgument(7);
  //  price->numberOfBlockThresholds = emberUnsignedCommandArgument(8);
  //  price->priceControl = emberUnsignedCommandArgument(9);
}

// zcl set-price alternate <price index:1> <alternateCostDelivered:4> <alternateCostUnit:1> <alternateCostTrailingDigit:1>
static void zclPriceSetAlternateCommand(void)
{
  EmberAfScheduledPrice *price = getPriceArgument();
  if (price == NULL)
    return;
  price->alternateCostDelivered = emberUnsignedCommandArgument(1);
  price->alternateCostUnit = (int8u)emberUnsignedCommandArgument(2);
  price->alternateCostTrailingDigit = (int8u)emberUnsignedCommandArgument(3);
}

// zcl set-price acknowledge <req:1>
static void zclPriceSetAcknowledgementCommand(void)
{
  EmberAfScheduledPrice *price = getPriceArgument();
  if (price == NULL)
    return;
  price->priceControl &= ~ZCL_PRICE_CLUSTER_PRICE_ACKNOWLEDGEMENT_MASK;
  if (emberUnsignedCommandArgument(1) == 1) {
    price->priceControl |= EMBER_ZCL_PRICE_CONTROL_ACKNOWLEDGEMENT_REQUIRED;
  }
}

// zcl sprice publish
static void zclPricePublishCommand(void)
{
  int8u index = (int8u)emberUnsignedCommandArgument(0);
  EmberAfScheduledPrice *price = emberAfPriceGetPriceTableEntry(index);
  if (price == NULL) {
    emberAfPriceClusterPrintln("no price at index %d!", index);
    return;
  }
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,
                 ZCL_PRICE_CLUSTER_ID,
                 ZCL_PUBLISH_PRICE_COMMAND_ID);
  zclBufferAddInt32(price->providerId);
  zclBufferAddString(price->rateLabel);
  zclBufferAddInt32(price->issuerEventID);
  zclBufferAddInt32(emberAfGetCurrentTime());
  zclBufferAddByte(price->unitOfMeasure);
  zclBufferAddWord(price->currency);
  zclBufferAddByte(price->priceTrailingDigitAndTier);
  zclBufferAddByte(price->numberOfPriceTiersAndTier);
  zclBufferAddInt32(price->startTime);
  zclBufferAddWord(price->duration);
  zclBufferAddInt32(price->price);
  zclBufferAddByte(price->priceRatio);
  zclBufferAddInt32(price->generationPrice);
  zclBufferAddByte(price->generationPriceRatio);
  zclBufferAddInt32(price->alternateCostDelivered);
  zclBufferAddByte(price->alternateCostUnit);
  zclBufferAddByte(price->alternateCostTrailingDigit);
  zclBufferAddByte(price->numberOfBlockThresholds);
  zclBufferAddByte(price->priceControl);
  cliBufferPrint();
}
#endif //EMBER_AF_PLUGIN_PRICE_SERVER



#ifdef EMBER_AF_PLUGIN_MESSAGING_SERVER
// zcl set-message message <message string>
static void zclSetMessageCommand(void)
{
  EmberAfMessagingServerMessage* message = emAfPluginMessagingServerGetMessageStruct();
  int8u length = emberCopyStringArgument(0, 
                                         message->message + 1, 
                                         EMBER_AF_PLUGIN_MESSAGING_SERVER_MESSAGE_SIZE,
                                         FALSE);
  message->message[0] = length;
}

// zcl set-message append <message string>
static void zclSetMessageAppendCommand(void)
{
  EmberAfMessagingServerMessage* message = emAfPluginMessagingServerGetMessageStruct();
  int8u oldLength = message->message[0];
  int8u length = emberCopyStringArgument(0, 
                                         message->message + oldLength + 1,
                                         (EMBER_AF_PLUGIN_MESSAGING_SERVER_MESSAGE_SIZE
                                          - oldLength),
                                         FALSE);
  message->message[0] = oldLength + length;
}
 
// zcl set-message id <messageId:4>
static void zclSetMessageIdCommand(void)
{
  EmberAfMessagingServerMessage* message = emAfPluginMessagingServerGetMessageStruct();
  message->messageId = emberUnsignedCommandArgument(0);
}

// zcl set-message time <start time:4> <duration:2>
static void zclSetMessageTimeCommand(void)
{
  EmberAfMessagingServerMessage* message = emAfPluginMessagingServerGetMessageStruct();
  message->startTime = emberUnsignedCommandArgument(0);
  message->durationInMinutes = (int16u)emberUnsignedCommandArgument(1);
}

// zcl set-message transmission <normal | ipan | both>
static void zclSetMessageTransmissionCommand(void)
{
  EmberAfMessagingServerMessage* message = emAfPluginMessagingServerGetMessageStruct();
  int8u commandChar = emberCurrentCommand->name[0];
  message->messageControl &= ~ZCL_MESSAGING_CLUSTER_TRANSMISSION_MASK;
  if (commandChar == 'b') { // both
    message->messageControl |= EMBER_ZCL_MESSAGING_CONTROL_TRANSMISSION_NORMAL_AND_ANONYMOUS;  
  } else if (commandChar == 'i') { // inter pan
    message->messageControl |= EMBER_ZCL_MESSAGING_CONTROL_TRANSMISSION_ANONYMOUS;
  }
  // Do nothing for 'normal'.
}

// zcl set-message importance <low | medium | high | critical>
static void zclSetMessageImportanceCommand(void)
{
  EmberAfMessagingServerMessage* message = emAfPluginMessagingServerGetMessageStruct();
  int8u commandChar = emberCurrentCommand->name[0];
  message->messageControl &= ~ZCL_MESSAGING_CLUSTER_IMPORTANCE_MASK;
  if (commandChar == 'm') { // medium
    message->messageControl |= EMBER_ZCL_MESSAGING_CONTROL_IMPORTANCE_MEDIUM;
  } else if (commandChar == 'h') { // high
    message->messageControl |= EMBER_ZCL_MESSAGING_CONTROL_IMPORTANCE_HIGH;
  } else if (commandChar == 'c') { // critical
    message->messageControl |= EMBER_ZCL_MESSAGING_CONTROL_IMPORTANCE_CRITICAL;
  }
  // Do nothing for 'low' importance.
}

// zcl set-message confirm <not | req>
static void zclSetMessageConfirmCommand(void)
{
  EmberAfMessagingServerMessage* message = emAfPluginMessagingServerGetMessageStruct();
  int8u commandChar = emberCurrentCommand->name[0];  
  message->messageControl &= ~ZCL_MESSAGING_CLUSTER_CONFIRMATION_MASK;
  if (commandChar == 'r') { // required
    message->messageControl |= EMBER_ZCL_MESSAGING_CONTROL_CONFIRMATION_REQUIRED;    
  }
  // Do nothing for 'not' (not required).
}

// zcl set-message <valid | invalid>
static void zclSetMessageValidCommand(void)
{
  EmberAfMessagingServerMessage *message = emAfPluginMessagingServerGetMessageStruct();
  message->valid = (emberCurrentCommand->name[0] == 'v');
}

// zcl message display
static void zclMessageDisplayCommand(void)
{
  EmberAfMessagingServerMessage* message = emAfPluginMessagingServerGetMessageStruct();
  if (!message->valid) {
    emberAfMessagingClusterPrintln("invalid msg");
    return;
  }

  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,
                 ZCL_MESSAGING_CLUSTER_ID,
                 ZCL_DISPLAY_MESSAGE_COMMAND_ID);
  zclBufferAddInt32(message->messageId);
  zclBufferAddByte(message->messageControl);
  zclBufferAddInt32(message->startTime);
  zclBufferAddWord(message->durationInMinutes);
  zclBufferAddString(message->message);
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}

// zcl message cancel
static void zclMessageCancelCommand(void)
{
  EmberAfMessagingServerMessage* message = emAfPluginMessagingServerGetMessageStruct();
  if (!message->valid) {
    emberAfMessagingClusterPrintln("message is not valid");
    return;
  }
  // build the buffer - Table 71 of Zigbee Profile: Smart Energy doc
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,
                 ZCL_MESSAGING_CLUSTER_ID,
                 ZCL_CANCEL_MESSAGE_COMMAND_ID);
  zclBufferAddInt32(message->messageId);
  // BUGZID: 12250, Send whole message control even though only bits 0 and 1
  //         are valid. This is needed for cert test.
  zclBufferAddByte(message->messageControl);
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}
#endif //EMBER_AF_PLUGIN_MESSAGING_SERVER

#ifdef ZCL_USING_MESSAGING_CLUSTER_CLIENT
// zcl message get
static void zclMessageGetCommand(void)
{
  zclSimpleClientCommand(ZCL_MESSAGING_CLUSTER_ID,
                         ZCL_GET_LAST_MESSAGE_COMMAND_ID);
}
#endif //ZCL_USING_MESSAGING_CLUSTER_CLIENT

#ifdef EMBER_AF_PLUGIN_MESSAGING_CLIENT
// zcl message confirm
static void zclMessageConfirmCommand(void)
{
  emberAfPluginMessagingClientConfirmMessage();
}
#endif //EMBER_AF_PLUGIN_MESSAGING_CLIENT


#ifdef ZCL_USING_GENERIC_TUNNEL_CLUSTER_CLIENT
// zcl tunnel match <address bytes>
static void zclTunnelMatchCommand(void)
{
  zclSimpleClientCommand(ZCL_GENERIC_TUNNEL_CLUSTER_ID,
                         ZCL_MATCH_PROTOCOL_ADDRESS_COMMAND_ID);
}
#endif //ZCL_USING_GENERIC_TUNNEL_CLUSTER_CLIENT

#ifdef ZCL_USING_GENERIC_TUNNEL_CLUSTER_SERVER
// zcl tunnel advertise <address bytes>
static void zclTunnelAdvertiseCommand(void)
{
  zclSimpleServerCommand(ZCL_GENERIC_TUNNEL_CLUSTER_ID,
                         ZCL_ADVERTISE_PROTOCOL_ADDRESS_COMMAND_ID);
}

// zcl tunnel response
static void zclTunnelResponseCommand(void)
{
  zclSimpleServerCommand(ZCL_GENERIC_TUNNEL_CLUSTER_ID,
                         ZCL_MATCH_PROTOCOL_ADDRESS_RESPONSE_COMMAND_ID);
}
#endif //ZCL_USING_GENERIC_TUNNEL_CLUSTER_SERVER

#ifdef ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_CLIENT
// zcl bacnet transfer-npdu fixed <length:1> <bytes>
static void zclBacnetTransferFixedCommand(void)
{
  // not done yet
}

// zcl bacnet transfer-npdu random <length:1>
static void zclBacnetTransferRandomCommand(void)
{
  int8u i;
  int8u length = (int8u)emberUnsignedCommandArgument(0);
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_BACNET_PROTOCOL_TUNNEL_CLUSTER_ID,
                 ZCL_TRANSFER_NPDU_COMMAND_ID);
  zclBufferAddByte(length);
  for (i = 0; i < length; i++) {
    zclBufferAddByte(LOW_BYTE(halCommonGetRandom()));
  }
  cliBufferPrint();  
}

// zcl bacnet transfer-npdu whois
static void zclBacnetTransferWhoisCommand(void)
{
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_BACNET_PROTOCOL_TUNNEL_CLUSTER_ID,
                 ZCL_TRANSFER_NPDU_COMMAND_ID);
  //zclBufferAddByte(0);            // what is this?
  zclBufferAddInt32(0xFFFF2001);
  zclBufferAddInt32(0x0810FF00);
  cliBufferPrint();
}

#ifdef EMBER_AF_PLUGIN_GENERIC_TUNNEL
// zcl bacnet transfer-npdu iam <length:1> <endpoint:1>
static void zclBacnetTransferIamCommand(void)
{
  int8u length;
  int8u endpoint = (int8u)emberUnsignedCommandArgument(1);
  int8u *protocolAddress = emAfPluginGenericTunnelGetProtocolAddress(endpoint);
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_BACNET_PROTOCOL_TUNNEL_CLUSTER_ID,
                 ZCL_TRANSFER_NPDU_COMMAND_ID);
  zclBufferAddByteFromArgument(0);
  zclBufferAddInt32(0xFFFF2001);
  zclBufferAddInt32(0x0010FF00);
  zclBufferAddWord(0x02C4);

  length = protocolAddress[0];
  if (length > EMBER_AF_PLUGIN_GENERIC_TUNNEL_PROTOCOL_ADDRESS_SIZE) {
    length = EMBER_AF_PLUGIN_GENERIC_TUNNEL_PROTOCOL_ADDRESS_SIZE;
  }
  zclBufferAddBuffer(protocolAddress, length + 1);
  zclBufferAddByte(0x22);
  zclBufferAddByte(0x01); // Max APDU =
  zclBufferAddByte(0xE0); // 480
  zclBufferAddByte(0x91);
  zclBufferAddByte(0x00); // Segmentation supported both (none = 3)
  zclBufferAddByte(0x21);
  zclBufferAddByte(0x07); // Siemens Vendor ID
  cliBufferPrint();
}
#endif //EMBER_AF_PLUGIN_GENERIC_TUNNEL
#endif //ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_CLIENT

#ifdef EMBER_AF_PLUGIN_BACNET_PROTOCOL_TUNNEL
// option bacnet 1
static void optionBacnetCommand(void)
{
  if (emberUnsignedCommandArgument(0) == 1) {
    int16u length = 48;
    int8u npdu[48] = { 0xa, 2, 3, 4, 5, 6, 7, 8,
                       0xb, 2, 3, 4, 5, 6, 7, 8,
                       0xc, 2, 3, 4, 5, 6, 7, 8,
                       0xd, 2, 3, 4, 5, 6, 7, 8,
                       0xe, 2, 3, 4, 5, 6, 7, 8,
                       0xf, 2, 3, 4, 5, 6, 7, 8 };

    bacnetProtocolTxTransferNpdu(length,
                                 npdu,
                                 0xFFFF, // dest short addr
                                 10,     // destEndpoint,
                                 10);    // sourceEndpoint);
  }
}
#endif //EMBER_AF_PLUGIN_BACNET_PROTOCOL_TUNNEL

#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_CLIENT
// zcl lock [ lock | unlock ]
static void zclDoorLockCommand(void)
{
  zclSimpleClientCommand(ZCL_DOOR_LOCK_CLUSTER_ID,
                         (emberCurrentCommand->name[0] == 'l'
                          ? ZCL_LOCK_DOOR_COMMAND_ID
                          : ZCL_UNLOCK_DOOR_COMMAND_ID));
}
#endif //ZCL_USING_DOOR_LOCK_CLUSTER_CLIENT

#ifdef ZCL_USING_TUNNELING_CLUSTER_CLIENT
// zcl tunneling request <protocol id:1> <manufacturer code:2> <flow control:1>
static void zclTunnelingRequestCommand(void)
{
  zclSimpleClientCommand(ZCL_TUNNELING_CLUSTER_ID,
                         ZCL_REQUEST_TUNNEL_COMMAND_ID);
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
}

// zcl tunneling close <tunnel id:2>
static void zclTunnelingCloseCommand(void)
{
  zclSimpleClientCommand(ZCL_TUNNELING_CLUSTER_ID,
                         ZCL_CLOSE_TUNNEL_COMMAND_ID);
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
}

// zcl tunneling transfer-to-server <tunnel id:2> <data>
static void zclTunnelingTransferToServerCommand(void)
{
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_TUNNELING_CLUSTER_ID,
                 ZCL_TRANSFER_DATA_CLIENT_TO_SERVER_COMMAND_ID);
  zclBufferAddWordFromArgument(0);              // tunnel id
  appZclBufferLen += emberCopyStringArgument(1, // data
                                             appZclBuffer + appZclBufferLen,
                                             0xFF,   // copy as much data as possible
                                             FALSE); // no padding
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}

// zcl tunneling random-to-server <tunnel id:2> <length:2>
static void zclTunnelingRandomToServerCommand(void)
{
  int16u length = (int16u)emberUnsignedCommandArgument(1); // length of random data
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_TUNNELING_CLUSTER_ID,
                 ZCL_TRANSFER_DATA_CLIENT_TO_SERVER_COMMAND_ID);
  zclBufferAddWordFromArgument(0); // tunnel id
  appZclBufferLen = (appZclBufferLen + length < APP_ZCL_BUFFER_SIZE
                     ? appZclBufferLen + length
                     : APP_ZCL_BUFFER_SIZE);
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}
#endif //ZCL_USING_TUNNELING_CLUSTER_CLIENT

#ifdef ZCL_USING_TUNNELING_CLUSTER_SERVER
// zcl tunneling transfer-to-client <tunnel id:2> <data>
static void zclTunnelingTransferToClientCommand(void)
{
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,
                 ZCL_TUNNELING_CLUSTER_ID,
                 ZCL_TRANSFER_DATA_SERVER_TO_CLIENT_COMMAND_ID);
  zclBufferAddWordFromArgument(0);              // tunnel id
  appZclBufferLen += emberCopyStringArgument(1, // data
                                             appZclBuffer + appZclBufferLen,
                                             0xFF,   // copy as much data as possible
                                             FALSE); // no padding
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}

// zcl tunneling random-to-client <tunnel id:2> <length:2>
static void zclTunnelingRandomToClientCommand(void)
{
  int16u length = (int16u)emberUnsignedCommandArgument(1); // length of random data
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,
                 ZCL_TUNNELING_CLUSTER_ID,
                 ZCL_TRANSFER_DATA_SERVER_TO_CLIENT_COMMAND_ID);
  zclBufferAddWordFromArgument(0); // tunnel id
  appZclBufferLen = (appZclBufferLen + length < APP_ZCL_BUFFER_SIZE
                     ? appZclBufferLen + length
                     : APP_ZCL_BUFFER_SIZE);
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}
#endif //ZCL_USING_TUNNELING_CLUSTER_SERVER

// ******************************************************
// send <id> <src endpoint> <dst endpoint> 
// send_multicast <group id> <src endpoint> <dst endpoint>
//
// FFFC = all routers
// FFFD = all non-sleepy
// FFFE = all devices, include sleepy
// ******************************************************
void emAfCliSendCommand(void)
{
  int16u destination = (int16u)emberUnsignedCommandArgument(0);
  int8u srcEndpoint = (int8u)emberUnsignedCommandArgument(1);
  int8u dstEndpoint = (int8u)emberUnsignedCommandArgument(2);
  int8u *commandName = (int8u *)emberCurrentCommand->name;
  EmberStatus status;
  int8u label;

  // check that cmd is built
  if (zclCmdIsBuilt == FALSE) {
    emberAfCorePrintln("no cmd");
    return;
  }

  emAfApsFrameEndpointSetup(srcEndpoint, dstEndpoint);

  if (commandName[4] == '_') {
    label = 'M';
    status = emberAfSendMulticast(destination,
                                  &globalApsFrame,
                                  appZclBufferLen,
                                  appZclBuffer);
  } else if (destination >= EMBER_BROADCAST_ADDRESS) {
    label = 'B';
    status = emberAfSendBroadcast(destination,
                                  &globalApsFrame,
                                  appZclBufferLen,
                                  appZclBuffer);
  } else {
    label = 'U';
    status = emberAfSendUnicast(EMBER_OUTGOING_DIRECT,
                                destination,
                                &globalApsFrame,
                                appZclBufferLen,
                                appZclBuffer);
  }

  emberAfDebugPrintln("T%4x:TX (%p) %ccast 0x%x%p",
                      emberAfGetCurrentTime(),
                      "CLI",
                      label,
                      status,
                      ((globalApsFrame.options & EMBER_APS_OPTION_ENCRYPTION)
                       ? " w/ link key" : ""));
  emberAfDebugPrint("TX buffer: [");
  emberAfDebugFlush();
  emberAfDebugPrintBuffer(appZclBuffer, appZclBufferLen, TRUE);
  emberAfDebugPrintln("]");
  emberAfDebugFlush();

  zclCmdIsBuilt = FALSE;
}

// **********************************************************************
// bsend <src endpoint> - send using a binding based on the clusterId in
//            the globalApsFrame and the srcEndpoint specified (if the
//            src endpoint is zero it only sends based on the clusterId)
//
// **********************************************************************
void emAfCliBsendCommand(void)
{
  int8u srcEndpointToUse, i;
  EmberStatus status;
  EmberBindingTableEntry candidate;

  // check that cmd is built
  if (zclCmdIsBuilt == FALSE) {
    emberAfCorePrintln("cmd not built");
    return;
  }

  srcEndpointToUse = (int8u)emberUnsignedCommandArgument(0);

  emberAfCorePrintln("src ep %x, clus %2x",
                     srcEndpointToUse, 
                     globalApsFrame.clusterId);

  // find a binding to send on
  for (i = 0; i < EMBER_BINDING_TABLE_SIZE; i++) {
    status = emberGetBinding(i, &candidate);

    // if we can read the binding, it is unicast, the endpoint is the
    // one we want (or we have no preference) and the cluster matches
    // then use that binding to send the message
    if (status == EMBER_SUCCESS
        && candidate.type == EMBER_UNICAST_BINDING
        && (srcEndpointToUse == 0
            || candidate.local == srcEndpointToUse)
        && candidate.clusterId == globalApsFrame.clusterId) {
      emberAfCorePrintln("sending to bind %x", i);

      status = emberAfSendUnicast(EMBER_OUTGOING_VIA_BINDING,
                                  i,
                                  &globalApsFrame,
                                  appZclBufferLen,
                                  appZclBuffer);

      emberAfDebugPrintln("T%4x:TX (%p) %ccast 0x%x%p",
                         emberAfGetCurrentTime(),
                         "CLI",
                         'U',
                         status,
                         ((globalApsFrame.options & EMBER_APS_OPTION_ENCRYPTION)
                          ? " w/ link key" : ""));
      emberAfDebugPrint("TX buffer: [");
      emberAfDebugFlush();
      emberAfDebugPrintBuffer(appZclBuffer, appZclBufferLen, TRUE);
      emberAfDebugPrintln("]");
      emberAfDebugFlush();
    }
  }
}


// timesync <id> <src endpoint> <dest endpoint>
//
// This sends a read attr for the time of the device specified. It sets a flag
// so when it gets the response it writes the time to its own time attr
void emAfCliTimesyncCommand(void)
{
  // send a read attr for time 
  zclBufferSetup(ZCL_PROFILE_WIDE_COMMAND | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_TIME_CLUSTER_ID,
                 ZCL_READ_ATTRIBUTES_COMMAND_ID);
  zclBufferAddWord(ZCL_TIME_ATTRIBUTE_ID);
  emAfSyncingTime = TRUE;
  cliBufferPrint();
  emAfCliSendCommand();
}


// interpan group <groupId:2> <destPAN:2> <destProfileID:2>
// interpan short <shortId:2> <destPAN:2> <destProfileID:2>
static void interpanCommand(void) 
{
  EmberStatus status;
  EmberAfInterpanHeader header;
  int16u shortOrGroupId;

  if (zclCmdIsBuilt == FALSE) {
    emberAfCorePrintln("no cmd");
    return;
  }

  MEMSET(&header, 0, sizeof(EmberAfInterpanHeader));
  shortOrGroupId = (int16u)emberUnsignedCommandArgument(0);
  header.panId = (int16u)emberUnsignedCommandArgument(1);
  header.profileId = (int16u)emberUnsignedCommandArgument(2);
  header.clusterId = globalApsFrame.clusterId;

  if (emberCurrentCommand->name[0] == 'g') {
    header.groupId = shortOrGroupId;
    emberAfDebugPrintln("interpan %p %2x", "group", header.groupId);    
  } else {
    header.shortAddress = shortOrGroupId;
    emberAfDebugPrintln("interpan %p %2x", "short", shortOrGroupId);
  }

  status = emberAfInterpanSendMessageCallback(&header,
                                              appZclBufferLen,
                                              appZclBuffer);
  if (status != EMBER_SUCCESS) {
    emberAfDebugPrintln("%psend failed: 0x%X",
                        "ERR: Inter-PAN ",
                        status);
  }
}

// interpan long  <longId:8>  <destPAN:2> <destProfileID:2> <options:2>
//    Options: Bit(0) = encrypt.  Can only encrypt with this CLI command
//    since long address must be present.
static void interpanLongCommand(void) 
{
  EmberStatus status;
  EmberAfInterpanHeader header;

  if (zclCmdIsBuilt == FALSE) {
    emberAfCorePrintln("no cmd");
    return;
  }

  MEMSET(&header, 0, sizeof(EmberAfInterpanHeader));
  header.panId = (int16u)emberUnsignedCommandArgument(1);
  header.profileId = (int16u)emberUnsignedCommandArgument(2);
  header.options = ((int16u)emberUnsignedCommandArgument(3)
                    | EMBER_AF_INTERPAN_OPTION_MAC_HAS_LONG_ADDRESS);
  header.clusterId = globalApsFrame.clusterId;
  
  emberAfCopyBigEndianEui64Argument(0, header.longAddress);

  status = emberAfInterpanSendMessageCallback(&header,
                                              appZclBufferLen,
                                              appZclBuffer);
  if (status != EMBER_SUCCESS) {
    emberAfDebugPrintln("%psend failed: 0x%X",
                        "ERR: Inter-PAN ",
                        status);
  }
}

#if defined(EMBER_AF_PLUGIN_MESSAGING_CLIENT) || defined(EMBER_AF_PLUGIN_MESSAGING_SERVER)
static void printMessagingCommand(void) 
{
#ifdef EMBER_AF_PLUGIN_MESSAGING_SERVER
  emAfPluginMessagingServerPrintInfo();
#endif //EMBER_AF_PLUGIN_MESSAGING_SERVER
#ifdef EMBER_AF_PLUGIN_MESSAGING_CLIENT
  emAfPluginMessagingClientPrintInfo();
#endif //EMBER_AF_PLUGIN_MESSAGING_CLIENT
}
#endif

#if defined(EMBER_AF_PLUGIN_DRLC) || defined(EMBER_AF_PLUGIN_DRLC_SERVER)
static void printDrlcCommand(void)
{
#ifdef EMBER_AF_PLUGIN_DRLC
  emAfLoadControlEventTablePrint();
#endif //EMBER_AF_PLUGIN_DRLC
#ifdef EMBER_AF_PLUGIN_DRLC_SERVER
  emAfPluginDrlcServerPrintInfo();
#endif //EMBER_AF_PLUGIN_DRLC_SERVER
}
#endif

#if defined(EMBER_AF_PLUGIN_PRICE_CLIENT) || defined(EMBER_AF_PLUGIN_PRICE_SERVER)
static void printPriceCommand(void) 
{
#ifdef EMBER_AF_PLUGIN_PRICE_SERVER
  emberAfPricePrintTable();
#endif //EMBER_AF_PLUGIN_PRICE_SERVER
#ifdef EMBER_AF_PLUGIN_PRICE_CLIENT
  emAfPluginPriceClientPrintInfo();
#endif //EMBER_AF_PLUGIN_PRICE_CLIENT
}
#endif

static void printTimeCommand(void) 
{
  emberAfPrintTime(emberAfGetCurrentTime());
}

#define MAX_ATTR_DATA_SIZE 16

// read <endpoint:1> <cluster:2> <attribute:2> <mask:1>
void emAfCliReadCommand(void)
{
  EmberAfStatus status;
  int8u endpoint = (int8u)emberUnsignedCommandArgument(0);
  EmberAfClusterId cluster = (EmberAfClusterId)emberUnsignedCommandArgument(1);
  EmberAfAttributeId attribute = (EmberAfAttributeId)emberUnsignedCommandArgument(2);
  boolean serverAttribute = (boolean)emberUnsignedCommandArgument(3);
  int8u data[MAX_ATTR_DATA_SIZE];
  int8u dataType;
  
  emberAfCorePrint("%p: ep: %d, cl: 0x%2X, attr: 0x%2X", 
                   "read",
                   endpoint,
                   cluster,
                   attribute);
  emberAfCorePrintln(", svr: %c", (serverAttribute ? 'y' : 'n'));

  status = emberAfReadAttribute(endpoint,
                                cluster,
                                attribute,
                                (serverAttribute
                                 ? CLUSTER_MASK_SERVER
                                 : CLUSTER_MASK_CLIENT),
                                data,
                                sizeof(data),
                                &dataType);
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    if (emberAfIsThisDataTypeAStringType(dataType)) {
      emberAfCorePrintString(data);
    } else {
      emberAfCorePrintBuffer(data, emberAfGetDataSize(dataType), TRUE);
    }
    emberAfCorePrintln("");
  } else {
    emberAfCorePrintln("%p: read: 0x%x", "Error", status);
  }
}

// ******************************************************
// write <ep> <cluster> <attrID> <mask> <dataType> <data bytes>
// ******************************************************
void emAfCliWriteCommand(void) 
{
  //int8u i;
  boolean result;
  int8u data[MAX_ATTR_DATA_SIZE];

  int8u  endpoint  = (int8u)emberUnsignedCommandArgument(0);
  int16u cluster   = (int16u)emberUnsignedCommandArgument(1);
  int16u attribute = (int16u)emberUnsignedCommandArgument(2);
  boolean serverAttribute = (boolean)emberUnsignedCommandArgument(3);
  int8u  dataType  = (int8u)emberUnsignedCommandArgument(4);
  
  emberAfCorePrint("%p: ep: %d, cl: 0x%2X, attr: 0x%2X",
                   "write",
                   endpoint, 
                   cluster, 
                   attribute);
  emberAfCorePrintln(", svr: %c, dtype: 0x%X",
                     (serverAttribute ? 'y' : 'n'),
                     dataType);

  // If the data type is a string, automatically prepend a length to the data;
  // otherwise, just copy the raw bytes.
  MEMSET(data, 0, MAX_ATTR_DATA_SIZE);
  if (emberAfIsThisDataTypeAStringType(dataType)) {
    data[0] = emberCopyStringArgument(5,
                                      data + 1,
                                      MAX_ATTR_DATA_SIZE - 1,
                                      FALSE);
  } else {
     emberCopyStringArgument(5,
                             data,
                             emberAfGetDataSize(dataType),
                             FALSE);
  }


  result = emberAfWriteAttribute(endpoint,
                                 cluster,
                                 attribute,
                                 (serverAttribute
                                  ? CLUSTER_MASK_SERVER
                                  : CLUSTER_MASK_CLIENT),
                                 (int8u *)&data,
                                 dataType);
  emAfPrintStatus("write", result);
  emberAfCorePrintln("");
}

#ifdef EMBER_AF_PLUGIN_DRLC
void emAfCliClearEventsCommand(void)
{
  int8u i;
  for ( i = 0; i < emberAfEndpointCount(); i++ ) 
    afLoadControlEventTableInit(emberAfEndpointFromIndex(i));
  emberAfCorePrintln("Events cleared");
}
#endif //EMBER_AF_PLUGIN_DRLC

extern boolean emberAfPrintReceivedMessages;
extern boolean afApsSecurityOff;
extern int8u emberAfApsRetryOverride;

// option print-rx-msgs [enable | disable]
static void optionPrintRxCommand(void) 
{
  if (emberCurrentCommand->name[0] == 'e') {
    emberAfPrintReceivedMessages = TRUE;
  } else {
    emberAfPrintReceivedMessages = FALSE;
  }
  emberAfAppPrintln("%pd print", 
                      (emberAfPrintReceivedMessages
                       ? "enable"
                       : "disable"));
}

// option register
static void optionRegisterCommand(void) 
{
  emberAfRegistrationStartCallback();
}

#if defined(__MCCXAP2B__)
  // The XAP is very strict about type conversions with regard to EmberEUI64.
  // In order to cast "const int8u*" to "const EmberEUI64" 
  // we must first cast away the const of the int8u* type and then cast the
  // data to a 'const EmberEUI64'.
  #define INT8U_TO_EUI64_CAST(x) ((const EmberEUI64)((int8u*)x)) 
#else
  #define INT8U_TO_EUI64_CAST(x) (x)
#endif

void emAfCliServiceDiscoveryCallback(const EmberAfServiceDiscoveryResult* result)
{
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
  if (!emberAfHaveDiscoveryResponseStatus(result->status)) {
    // Do nothing
  } else if (result->zdoRequestClusterId == MATCH_DESCRIPTORS_REQUEST) {
    const EmberAfEndpointList* epList = (const EmberAfEndpointList*)result->responseData;
    emberAfAppPrintln("Match %py from 0x%2X, ep %d",
                      "discover",
                      result->matchAddress,
                      epList->list[0]);
  } else if (result->zdoRequestClusterId == NETWORK_ADDRESS_REQUEST) {
    const EmberNodeId* id =  (EmberNodeId*)(result->responseData);
    emberAfAppPrintln("NWK Address response: 0x%X", *id);
  } else if (result->zdoRequestClusterId == IEEE_ADDRESS_REQUEST) {
    const int8u* eui64ptr = (int8u*)(result->responseData);
    emberAfAppPrint("IEEE Address response: ");
    emberAfPrintBigEndianEui64(INT8U_TO_EUI64_CAST(eui64ptr));
    emberAfAppPrintln("");
  }

  if (result->status != EMBER_AF_BROADCAST_SERVICE_DISCOVERY_RESPONSE_RECEIVED) {
    emberAfAppPrintln("Service %py done.", 
                      "discover");
  }
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
}

// disc <profileId> <clusterId>
static void optionDiscoverCommand(void)
{
  EmberAfProfileId profileId = (int16u)emberUnsignedCommandArgument(0);
  EmberAfClusterId clusterId = (int16u)emberUnsignedCommandArgument(1);
  emberAfFindDevicesByProfileAndCluster(EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS,
                                      profileId,
                                      clusterId, 
                                      EMBER_AF_SERVER_CLUSTER_DISCOVERY,
                                      emAfCliServiceDiscoveryCallback);
}

// option agg
#ifdef EMBER_AF_CONCENTRATOR
static void optionAggregationCommand(void)
{
  emberConcentratorQueueRouteDiscovery();  
}
#endif

// option binding-table print
static void optionBindingTablePrintCommand(void)
{
  int8u i;
  EmberBindingTableEntry result;

  PGM_P typeStrings[] = {
    "EMPTY",
    "UNICA",
    "M2ONE",
    "MULTI",
    "?    ",
  };

  emberAfAppPrintln("#  type   loc rem clus eui");
  for (i = 0; i < EMBER_BINDING_TABLE_SIZE; i++) {
    EmberStatus status = emberGetBinding(i, &result);
    emberAfAppPrint("%x:", i);
    if (status == EMBER_SUCCESS) {
      if (result.type > EMBER_MULTICAST_BINDING) {
        result.type = 4;  // last entry in the string list above
      }
      emberAfAppPrint("%p", typeStrings[result.type]);
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
      if (result.type != EMBER_UNUSED_BINDING) {
        emberAfAppPrint("  %x  %x  %2x ",
                        result.local,
                        result.remote,
                        result.clusterId);
        emberAfAppDebugExec(emberAfPrintBigEndianEui64(result.identifier));
      }
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)
    } else {
      emberAfAppPrintln("emberGetBinding Error: %x", status);
      emberAfAppFlush();
    }
    emberAfAppPrintln("");
    emberAfAppFlush();
  }
}

// option binding-table clear
static void optionBindingTableClearCommand(void)
{
  emberClearBindingTable();
}

// option address-table print
static void optionAddressTablePrintCommand(void)
{
  int8u i;
  emberAfAppPrintln("#  node   eui");
  for (i = 0; i < EMBER_AF_ADDRESS_TABLE_SIZE; i++) {
    EmberNodeId nodeId = emberGetAddressTableRemoteNodeId(i);
    emberAfAppPrint("%x:", i);
    if (nodeId != EMBER_TABLE_ENTRY_UNUSED_NODE_ID) {
      EmberEUI64 eui64;
      emberAfAppPrint("0x%2x ", nodeId);
      emberGetAddressTableRemoteEui64(i, eui64);
      emberAfAppDebugExec(emberAfPrintBigEndianEui64(eui64));
    }
    emberAfAppPrintln("");
    emberAfAppFlush();
  }
}

// option address-table set <index> <eui64> <node id>
static void optionAddressTableSetCommand(void)
{
  EmberEUI64 eui64;
  EmberStatus status;
  int8u index = (int8u)emberUnsignedCommandArgument(0);
  EmberNodeId nodeId = (EmberNodeId)emberUnsignedCommandArgument(2);
  emberAfCopyBigEndianEui64Argument(1, eui64);
  status = emberAfSetAddressTableEntry(index, eui64, nodeId);
  emberAfAppPrintln("set address %d: 0x%x", index, status);
}

#ifdef EMBER_AF_USE_BUTTONS
// option button0
static void optionButton0Command(void)
{
  emberAfFirstButtonPressed = TRUE;
}

// option button1
static void optionButton1Command(void)
{
  emberAfSecondButtonPressed = TRUE;
}
#endif //EMBER_AF_USE_BUTTONS

// option edb <endpoint>
static void optionEndDeviceBindCommand(void)
{
  int8u endpoint = (int8u)emberUnsignedCommandArgument(0);
  emberAfSendEndDeviceBind(endpoint);
}

static void optionApsRetryCommand(void) 
{
  if ( emberCurrentCommand->name[1] == 'e' ) {
    emberAfApsRetryOverride = EMBER_AF_RETRY_OVERRIDE_NONE;
  } else if ( emberCurrentCommand->name[1] == 'n' ) {
    emberAfApsRetryOverride = EMBER_AF_RETRY_OVERRIDE_SET;
  } else if ( emberCurrentCommand->name[1] == 'f' ) {
    emberAfApsRetryOverride = EMBER_AF_RETRY_OVERRIDE_UNSET;
  }
}

// option security aps <off | on>
static void optionApsSecurityCommand(void)
{
  if (emberCurrentCommand->name[1] == 'f') {
    afApsSecurityOff = TRUE;
  } else {
    afApsSecurityOff = FALSE;    
  }
}

#if EMBER_KEY_TABLE_SIZE > 0
// option link <index> <eui64 in big endian format> <key in big endian format>
static void optionLinkCommand(void) 
{  
  EmberEUI64 partnerEUI64;
  EmberKeyData newKey;
  EmberStatus status;
  //int8u i;
  int8u index = (int8u)emberUnsignedCommandArgument(0);
  emberAfCopyBigEndianEui64Argument(1, partnerEUI64);
  emberCopyKeyArgument(2, &newKey);
  status = emberSetKeyTableEntry(index, 
                                 partnerEUI64,
                                 TRUE,
                                 &newKey);
  emberAfAppDebugExec(emAfPrintStatus("add link key", status));
  emberAfAppPrintln("");
  emberAfCoreFlush();
}
#endif

// option binding-table set <index> <cluster> <local ep> <remote ep> <EUI>
static void optionBindingTableSetCommand(void)
{
  EmberBindingTableEntry entry;
  int8u index, status;

  entry.type = EMBER_UNICAST_BINDING;
  index = (int8u)emberUnsignedCommandArgument(0);
  entry.clusterId = (EmberAfClusterId)emberUnsignedCommandArgument(1);
  entry.local = (int8u)emberUnsignedCommandArgument(2);
  entry.remote = (int8u)emberUnsignedCommandArgument(3);
  emberAfCopyBigEndianEui64Argument(4, entry.identifier);
  status = emberSetBinding(index, &entry);
  emberAfAppPrintln("set bind %d: 0x%x", index, status);
}


void eraseKeyTableEntry(int8u index)
{
  EmberStatus status = emberEraseKeyTableEntry(index);
  
  if (status != EMBER_SUCCESS) {
    emberAfCorePrintln("%perase key %d: 0x%x",
                       "ERROR: ",
                       index,
                       status);
  }
}

// keys clear
void keysClearCommand(void)
{
#if EMBER_KEY_TABLE_SIZE
  int8u i;
  for (i = 0; i < EMBER_KEY_TABLE_SIZE; i++) {
    eraseKeyTableEntry(i);
  }
#endif
}

// keys print
void keysPrintCommand(void)
{
  emberAfCorePrintln("%pSECURITY_LEVEL: %x",
                     "EMBER_",
                     EMBER_SECURITY_LEVEL);
  printKeyInfo();
}

// keys delete <index:1>
void keysDeleteCommand(void)
{
  int8u index = (int8u)emberUnsignedCommandArgument(0);
  eraseKeyTableEntry(index);
}

#ifdef CERTIFICATION_TESTING
void attributeReadCausingFragmentedResponseCommand(void)
{
  zclBufferSetup(ZCL_PROFILE_WIDE_COMMAND | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 0x0000,
                 ZCL_READ_ATTRIBUTES_COMMAND_ID);
  zclBufferAddWord(0x0000);
  zclBufferAddWord(0x1000);
  zclBufferAddWord(0x1001);
  zclBufferAddWord(0x1002);
  zclBufferAddWord(0x1003);
  zclBufferAddWord(0x1004);
  zclBufferAddWord(0x1005);
  zclBufferAddWord(0x1006);
  zclBufferAddWord(0x1007);
  zclBufferAddWord(0x1008);
  zclBufferAddWord(0x1009);
  zclBufferAddWord(0x100A);
  zclBufferAddWord(0x100B);
  zclBufferAddWord(0x100C);
  zclBufferAddWord(0x100D);
  zclBufferAddWord(0x100E);
  zclBufferAddWord(0x100F);
  zclBufferAddWord(0x1010);
  zclBufferAddWord(0x1011);
  zclBufferAddWord(0x1012);
  zclBufferAddWord(0x1013);
  zclBufferAddWord(0x1014);
  zclBufferAddWord(0x1015);
  zclBufferAddWord(0x1016);
  zclBufferAddWord(0x1017);
  zclBufferAddWord(0x1018);
  zclBufferAddWord(0x1019);
  zclBufferAddWord(0x101A);
  zclBufferAddWord(0x2001);
  zclBufferAddWord(0x2002);
  zclBufferAddWord(0x2003);
  zclBufferAddWord(0x2004);
  zclBufferAddWord(0x2005);
  zclBufferAddWord(0x2006);
  zclBufferAddWord(0x2007);
  zclBufferAddWord(0x2008);
  zclBufferAddWord(0x2009);
  cliBufferPrint();
}
#endif //CERTIFICATION_TESTING



//******************************************************************
// zcl command table entries
//******************************************************************

/**
 * @addtogroup cli
 * @{
 */
/**
 * @brief Commands used to send global commands in the zcl
 *
 *        <b>zcl global read &lt;cluster&gt; &lt;attribute id&gt; </b>
 *        - <i> Creates a global read command message to read from 
 *              the cluster and attribute specified.
 *          - cluster - int16u. The cluster id to read from.
 *          - attribute id - int16u. The attribute id to read from</i>
 *
 *        <b>zcl global write &lt;cluster&gt; &lt;attribute id&gt; &lt;data type&gt; &lt;data&gt;</b>
 *        - <i> Creates a global write  command message to write to 
 *              the cluster and attribute specified.
 *          - cluster - int16u. The cluster id to read from.
 *          - attribute id - int16u. The attribute id to read from
 *          - data type - int8u. The two byte zigbee type value
 *          - data - byte array. The data to write</i>
 *
 *        <b>zcl global uwrite &lt;cluster&gt; &lt;attribute id&gt; &lt;data type&gt; &lt;data&gt;</b>
 *        - <i> Creates a global write command message to write to the 
 *              cluster and attribute specified. 
 *          - cluster - int16u. The cluster id to read from.
 *          - attribute id - int16u. The attribute id to read from
 *          - data type - int8u. The two byte zigbee type value
 *          - data - byte array. The data to write</i>
 *
 *        <b>zcl global nwrite &lt;cluster&gt; &lt;attribute id&gt; &lt;data type&gt; &lt;data&gt;</b>
 *        - <i> Creates a global write command message to write to the 
 *              cluster and attribute specified. 
 *          - cluster - int16u. The cluster id to read from.
 *          - attribute id - int16u. The attribute id to read from
 *          - data type - int8u. The two byte zigbee type value
 *          - data - byte array. The data to write</i>
 *
 *        <b>zcl global discover &lt;cluster&gt; &lt;attribute id&gt; &lt;max&gt;</b>
 *        - <i> Creates discovery message for devices with the associated 
 *              cluster and attribute 
 *          - cluster - int16u. The cluster id to read from.
 *          - attribute id - int16u. The attribute id to read from
 *          - max - int8u. Max number of discovery responses.</i>
 *
 *        <b>zcl global report-read &lt;cluster&gt; &lt;attribute id&gt; &lt;direction&gt;</b>
 *        - <i> Creates a global read reporting command for the associated 
 *              cluster, attribute and server/client direction.
 *          - cluster - int16u. The cluster id to read from.
 *          - attribute id - int16u. The attribute id to read from
 *          - direction - int8u. 0 for client-to-server, 1 for server-to-client.</i>
 *
 *        <b>zcl global send-me-a-report &lt;cluster&gt; &lt;attribute id&gt; &lt;data type&gt; 
 *           &lt;min report time&gt; &lt;max report time&gt; &lt;reportable change&gt;</b>
 *        - <i> Creates a global send me a report command for the associated values.
 *          - cluster - int16u. The cluster id for requested report.
 *          - attribute id - int16u. The attribute for requested report.
 *          - data type - int8u. The two byte zigbee type value for the requested report
 *          - min report time - int16u. Minimum number of seconds between reports.
 *          - max report time - int16u. Maximum number of seconds between reports.
 *          - reportable change - byte array. Amount of change to trigger a report.
 *
 *        <b>zcl global expect-report-from-me &lt;cluster&gt &lt;attribute id&gt; &lt;timeout&gt;</b>
 *        - <i> Create a expect-report-from-me message with associated values.
 *          - cluster - int16u. The cluster id for requested report.
 *          - attribute id - int16u. The attribute for requested report.
 *          - timeout - int16u. The maximum amount of time between reports.
 *
 *        <b>zcl global direction &lt;direction&gt;</b>
 *        - <i> Sets the direction for global commands, either client to server 
 *              or server to client.
 *          - direction - int8u. The direction for global commands.
 *            client-to-server == 0, server-to-client == 1.</i>
 */
#define EMBER_AF_DOXYGEN_CLI__ZCL_GLOBAL_COMMANDS
/** @} END addtogroup */
EmberCommandEntry zclGlobalCommands[] = {
  {"read", zclGlobalReadCommand, "vv"},
  {"write", zclGlobalWriteCommand, "vvub"},
  {"uwrite", zclGlobalWriteCommand, "vvub"},
  {"nwrite", zclGlobalWriteCommand, "vvub"},
  {"discover", zclGlobalDiscoverCommand, "vvu"},
  {"report-read", zclGlobalReportReadCommand, "vvu"},
  {"send-me-a-report", zclGlobalSendMeAReportCommand, "vvuvvb"},
#ifndef ZA_NO_REPORTING_OPTIMIZATION
  {"expect-report-from-me", zclGlobalExpectReportFromMeCommand, "vvv"},
#endif //ZA_NO_REPORTING_OPTIMIZATION
  {"report", zclGlobalReportCommand, "uvvu"},
  {"direction", zclGlobalDirectionCommand, "u"},
  { NULL }
};

EmberCommandEntry zclTestResponseCommands[] = {
  {"on", zclTestResponseOnCommand, ""},
  {"off", zclTestResponseOffCommand, ""},  
  { NULL }
};

EmberCommandEntry zclTestCommands[] = {
  {"response", NULL, (PGM_P)zclTestResponseCommands},
  { NULL }
};

#ifdef ZCL_USING_BASIC_CLUSTER_CLIENT
EmberCommandEntry zclBasicCommands[] = {
  {"rtfd", zclBasicRtfdCommand, ""},
  { NULL }
};
#endif

#if defined(ZCL_USING_IDENTIFY_CLUSTER_CLIENT) || defined(ZCL_USING_IDENTIFY_CLUSTER_SERVER)
EmberCommandEntry zclIdentifyCommands[] = {
  #ifdef ZCL_USING_IDENTIFY_CLUSTER_CLIENT
  {"id", zclIdentifyIdCommand, "v"},
  {"query", zclIdentifyQueryCommand, ""},
  #endif
  #ifdef ZCL_USING_IDENTIFY_CLUSTER_SERVER
  {"on", zclIdentifyOnCommand, "uv"},
  {"off", zclIdentifyOffCommand, "u"},
  #endif
  { NULL }
};
#endif

#ifdef ZCL_USING_GROUPS_CLUSTER_CLIENT
EmberCommandEntry zclGroupsCommands[] = {
  {"add", zclGroupsAddCommand, "vb"},
  {"ad-if-id", zclGroupsAddCommand, "vb"},
  {"view", zclGroupsViewCommand, "v"},
  {"get", zclGroupsGetCommand, "uv*"},
  {"remove", zclGroupsRemoveCommand, "v"},
  {"rmall", zclGroupsRemoveAllCommand, ""},
  { NULL }
};
#endif

#ifdef ZCL_USING_SCENES_CLUSTER_CLIENT
EmberCommandEntry zclScenesSetCommands[] = {
  {"on", zclScenesSetCommand, "u"},
  {"off", zclScenesSetCommand, "u"},
  { NULL }
};

EmberCommandEntry zclScenesCommands[] = {
  {"add", zclScenesAddCommand, "vuvb"},
  {"view", zclScenesViewCommand, "vu"},
  {"remove", zclScenesRemoveCommand, "vu"},
  {"rmall", zclScenesRemoveAllCommand, "v"},
  {"store", zclScenesStoreCommand, "vu"},
  {"recall", zclScenesRecallCommand, "vu"},
  {"get", zclScenesGetMembershipCommand, "v"},
  {"set", NULL, (PGM_P)zclScenesSetCommands},
  { NULL }
};
#endif

#ifdef ZCL_USING_ON_OFF_CLUSTER_CLIENT
EmberCommandEntry zclOnOffCommands[] = {
  {"on", zclOnOffCommand, ""},
  {"off", zclOnOffCommand, ""},
  {"toggle", zclOnOffCommand, ""},
  { NULL }
};
#endif

#ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_CLIENT
EmberCommandEntry zclLevelControlCommands[] = {
  {"mv-to-level", zclLevelControlMoveToLevelCommand, "uv"},
  {"move", zclLevelControlMoveCommand, "uu"},
  {"step", zclLevelControlStepCommand, "uuv"},
  {"stop", zclLevelControlStopCommand, ""},
  {"o-mv-to-level", zclLevelControlMoveToLevelCommand, "uv"},
  {"o-move", zclLevelControlMoveCommand, "uu"},
  {"o-step", zclLevelControlStepCommand, "uuv"},
  {"o-stop", zclLevelControlStopCommand, ""},
  { NULL }
};
#endif

#ifdef ZCL_USING_THERMOSTAT_CLUSTER_CLIENT
EmberCommandEntry zclThermostatCommands[] = {
  {"set", zclThermostatSetCommand, "uu"},
  { NULL }
};
#endif

#ifdef EMBER_AF_PLUGIN_IAS_ZONE_SERVER
EmberCommandEntry zclIasZoneCommands[] = {
  {"enroll", zclIasZoneEnrollCommand, "vv"},
  {"sc", zclIasZoneStatusChangeCommand, "vu"},
  { NULL }
};
#endif

#ifdef EMBER_AF_PLUGIN_IAS_ACE_ZONE
EmberCommandEntry zclIasZoneClientCommands[] = {
  {"pt", zclIasZoneClientPrintCommand, "vu"},
  { NULL }
};
#endif

#ifdef ZCL_USING_IAS_ACE_CLUSTER_CLIENT
EmberCommandEntry zclIasAceCommands[] = {
  {"a", zclIasAceArmCommand, "u"},
  {"b", zclIasAceBypassCommand, "b"},
  {"e", zclIasAceEmergencyCommand, ""},
  {"f", zclIasAceFireCommand, ""},
  {"p", zclIasAcePanicCommand, ""},
  {"getzm", zclIasAceGetZoneMapCommand, ""},
  {"getzi", zclIasAceGetZoneInfoCommand, "u"},
  { NULL }
};
#endif

#ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_CLIENT
EmberCommandEntry zclColorControlCommands[] = {
  {"movetohue", zclColorControlMoveToHueCommand, "uuv"},
  {"movehue", zclColorControlMoveHueCommand, "uu"},
  {"stephue", zclColorControlStepHueCommand, "uuu"},
  {"movetosat", zclColorControlMoveToSatCommand, "uv"},
  {"movesat", zclColorControlMoveSatCommand, "uu"},
  {"stepsat", zclColorControlStepSatCommand, "uuu"},
  {"movetohueandsat", zclColorControlMoveToHueAndSatCommand, "uuv"},
  {"movetocolor",     zclColorControlMoveToColorCommand, "vvv"},
  {"movecolor",       zclColorControlMoveColorCommand, "vv"},
  {"stepcolor",       zclColorControlStepColorCommand, "vvv"},
  {"movetocolortemp", zclColorControlMoveToColorTemperatureCommand, "vv"},
  { NULL }
};
#endif

#if defined(ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT) || defined(ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_SERVER)

#if defined(EMBER_AF_PLUGIN_DRLC) && defined(ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT)
EmberCommandEntry zclDrlcOptCommands[] = {
  {"in", zclDrlcOptInOrOutCommand, "w"},
  {"out", zclDrlcOptInOrOutCommand, "w"},
  { NULL }
};
#endif

EmberCommandEntry zclDrlcCommands[] = {
  #ifdef ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_SERVER
  
  #if defined(EMBER_AF_PLUGIN_DRLC_SERVER) && defined(ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_SERVER)
  {"slce", zclDrlcScheduleLoadControlEventCommand, "uub"},
  {"sslce", zclDrlcSendScheduledLoadControlEventCommand, "u"},
  {"cslce", emAfClearScheduledLoadControlEvents, ""},
  #endif //defined(EMBER_AF_PLUGIN_DRLC_SERVER
  
  {"lce", zclDrlcLoadControlEventCommand, "wwvu"},
  {"cl", zclDrlcCancelCommand, "wvuuw"},
  {"ca", zclDrlcCancelAllCommand, ""},
  #endif
  #ifdef ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT
  {"gse", zclDrlcGetScheduledEventsCommand, "u"},
  #ifdef EMBER_AF_PLUGIN_DRLC
  {"opt", NULL, (PGM_P)zclDrlcOptCommands},
  #endif //EMBER_AF_PLUGIN_IAS_ACE_ZONE
  #endif
  { NULL }
};
#endif //ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT || SERVER



#if defined(ZCL_USING_SIMPLE_METERING_CLUSTER_CLIENT) || defined(ZCL_USING_SIMPLE_METERING_CLUSTER_SERVER)
EmberCommandEntry zclSimpleMeteringCommands[] = {
#ifdef ZCL_USING_SIMPLE_METERING_CLUSTER_CLIENT
  {"gp", zclSimpleMeteringGetProfileCommand, "uwu"},
  {"fp", zclSimpleMeteringFastPollCommand, "uu"},
#endif //ZCL_USING_SIMPLE_METERING_CLUSTER_CLIENT
#ifdef ZCL_USING_SIMPLE_METERING_CLUSTER_SERVER
  {"rm", zclSimpleMeteringRequestMirrorCommand, ""},
  {"dm", zclSimpleMeteringDeleteMirrorCommand, ""},
#endif //ZCL_USING_SIMPLE_METERING_CLUSTER_SERVER
  { NULL }
};
#endif //ZCL_USING_SIMPLE_METERING_CLUSTER_CLIENT || ZCL_USING_SIMPLE_METERING_CLUSTER_SERVER

#ifdef EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER
EmberCommandEntry zclTestMeterCommands[] = {
#ifdef EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ENABLE
  {"print", zclTestMeterPrintCommand, ""},
  {"rate", zclTestMeterRateCommand, "v"},
  {"variance", zclTestMeterVarianceCommand, "v"},
  {"adjust", zclTestMeterAdjustCommand, "u"},
  {"off", zclTestMeterOffCommand, "u"},
#if (EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_TYPE == ELECTRIC_METER)
  {"electric", zclTestMeterElectricCommand, "u"},
#endif
#if (EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_TYPE == GAS_METER)
  {"gas", zclTestMeterGasCommand, "u"},
#endif
#ifdef EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ERRORS
  {"rnd_error", zclTestMeterRandomErrorCommand, "u"},
  {"set_error", zclTestMeterSetErrorCommand, "uu"},
#endif
#if ( EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_PROFILES != 0 )
  {"profiles", zclTestMeterProfilesCommand, "u"},
#endif
#endif // EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ENABLE
  { NULL }
};
#endif //  EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER

#ifdef ZCL_USING_PRICE_CLUSTER_CLIENT
EmberCommandEntry zclPriceClientCommands[] = {
  {"cu", zclPriceGetCurrentCommand, ""},
  {"sc", zclPriceGetScheduleCommand, "wu"},
  { NULL }
};
#endif //ZCL_USING_PRICE_CLUSTER_CLIENT

#ifdef EMBER_AF_PLUGIN_PRICE_SERVER
EmberCommandEntry zclPriceServerCommands[] = {
  {"clear", zclPriceClearCommand, ""},
  {"who", zclPriceSetWhoCommand, "uwbw"},
  {"what", zclPriceSetWhatCommand, "uuvuu"},
  {"when", zclPriceSetWhenCommand, "uwv"},
  {"price", zclPriceSetPriceCommand, "uwuwu"},
  {"alternate", zclPriceSetAlternateCommand, "uwuu"},
  {"ack", zclPriceSetAcknowledgementCommand, "uu"},
  { NULL }
};

EmberCommandEntry zclSpriceCommands[] = {
  // params - price index
  {"publish", zclPricePublishCommand, "u"},
  { NULL }
};
#endif // EMBER_AF_PLUGIN_PRICE_SERVER

#ifdef EMBER_AF_PLUGIN_MESSAGING_SERVER
EmberCommandEntry zclSetMessageTransmissionCommands[] = {
  {"normal", zclSetMessageTransmissionCommand, ""},
  {"ipan", zclSetMessageTransmissionCommand, ""},
  {"both", zclSetMessageTransmissionCommand, ""},
  { NULL }
};

EmberCommandEntry zclSetMessageImportanceCommands[] = {
  {"low", zclSetMessageImportanceCommand, ""},
  {"medium", zclSetMessageImportanceCommand, ""},
  {"high", zclSetMessageImportanceCommand, ""},
  {"critical", zclSetMessageImportanceCommand, ""},
  { NULL }
};

EmberCommandEntry zclSetMessageConfirmCommands[] = {
  {"not", zclSetMessageConfirmCommand, ""},
  {"req", zclSetMessageConfirmCommand, ""},
  { NULL }
};

EmberCommandEntry zclSetMessageCommands[] = {
  {"message", zclSetMessageCommand, "b"},
  {"append", zclSetMessageAppendCommand, "b"},
  {"id", zclSetMessageIdCommand, "w"},
  {"time", zclSetMessageTimeCommand, "wv"},
  {"transmission", NULL, (PGM_P)zclSetMessageTransmissionCommands},
  {"importance", NULL, (PGM_P)zclSetMessageImportanceCommands},
  {"confirm", NULL, (PGM_P)zclSetMessageConfirmCommands},
  {"valid", zclSetMessageValidCommand, ""},
  {"invalid", zclSetMessageValidCommand, ""},
  { NULL }
};
#endif //EMBER_AF_PLUGIN_MESSAGING_SERVER

EmberCommandEntry zclMessageCommands[] = {
#ifdef EMBER_AF_PLUGIN_MESSAGING_SERVER
  {"display", zclMessageDisplayCommand, ""},
  {"cancel", zclMessageCancelCommand, ""},
#endif //EMBER_AF_PLUGIN_MESSAGING_SERVER
#ifdef ZCL_USING_MESSAGING_CLUSTER_CLIENT
  {"get", zclMessageGetCommand, ""},
#endif //ZCL_USING_MESSAGING_CLUSTER_CLIENT
#ifdef EMBER_AF_PLUGIN_MESSAGING_CLIENT
  {"confirm", zclMessageConfirmCommand, ""},
#endif //EMBER_AF_PLUGIN_MESSAGING_CLIENT
  { NULL }
};

#if defined(ZCL_USING_GENERIC_TUNNEL_CLUSTER_CLIENT) || defined(ZCL_USING_GENERIC_TUNNEL_CLUSTER_SERVER)
EmberCommandEntry zclTunnelCommands[] = {
#ifdef ZCL_USING_GENERIC_TUNNEL_CLUSTER_CLIENT
  {"match", zclTunnelMatchCommand, "b"},
#endif //ZCL_USING_GENERIC_TUNNEL_CLUSTER_CLIENT
#ifdef ZCL_USING_GENERIC_TUNNEL_CLUSTER_SERVER
  {"advertise", zclTunnelAdvertiseCommand, "b"},
  {"response", zclTunnelResponseCommand, ""},
#endif //ZCL_USING_GENERIC_TUNNEL_CLUSTER_SERVER
  { NULL }
};
#endif //ZCL_USING_GENERIC_TUNNEL_CLUSTER_CLIENT || ZCL_USING_GENERIC_TUNNEL_CLUSTER_SERVER

#ifdef ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_CLIENT
EmberCommandEntry zclBacnetTransferCommands[] = {
  {"fixed", zclBacnetTransferFixedCommand, "ub"},
  {"random", zclBacnetTransferRandomCommand, "u"},
  {"whois", zclBacnetTransferWhoisCommand, ""}, //removed length byte from whois
  #ifdef EMBER_AF_PLUGIN_GENERIC_TUNNEL
  {"iam", zclBacnetTransferIamCommand, "uu"},
  #endif //EMBER_AF_PLUGIN_GENERIC_TUNNEL
  { NULL },
};

EmberCommandEntry zclBacnetCommands[] = {
  {"transfer-npdu", NULL, (PGM_P)zclBacnetTransferCommands},
  { NULL }
};
#endif

#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_CLIENT
EmberCommandEntry zclDoorLockCommands[] = {
  {"lock", zclDoorLockCommand, ""},
  {"unlock", zclDoorLockCommand, ""},
  { NULL }
};
#endif //ZCL_USING_DOOR_LOCK_CLUSTER_CLIENT

#if defined(ZCL_USING_TUNNELING_CLUSTER_CLIENT) || defined(ZCL_USING_TUNNELING_CLUSTER_SERVER)
EmberCommandEntry zclTunnelingCommands[] = {
#ifdef ZCL_USING_TUNNELING_CLUSTER_CLIENT
  {"request", zclTunnelingRequestCommand, "uvu"},
  {"close", zclTunnelingCloseCommand, "v"},
  {"transfer-to-server", zclTunnelingTransferToServerCommand, "vb"},
  {"random-to-server", zclTunnelingRandomToServerCommand, "vv"},
#endif //ZCL_USING_TUNNELING_CLUSTER_CLIENT
#ifdef ZCL_USING_TUNNELING_CLUSTER_SERVER
  {"transfer-to-client", zclTunnelingTransferToClientCommand, "vb"},
  {"random-to-client", zclTunnelingRandomToClientCommand, "vv"},
#endif //ZCL_USING_TUNNELING_CLUSTER_SERVER
  { NULL }
};
#endif //defined(ZCL_USING_TUNNELING_CLUSTER_CLIENT) || defined(ZCL_USING_TUNNELING_CLUSTER_SERVER)

EmberCommandEntry zclCommands[] = {

//#define CERTIFICATION_TESTING
#ifdef CERTIFICATION_TESTING
  {"attr-read-frag-resp", attributeReadCausingFragmentedResponseCommand, ""},
#endif //CERTIFICATION_TESTING


  {"global", NULL, (PGM_P)zclGlobalCommands},
  {"test", NULL, (PGM_P)zclTestCommands},
  {"time", zclTimeCommand, "w"},
  #ifdef ZCL_USING_BASIC_CLUSTER_CLIENT  
  {"basic", NULL, (PGM_P)zclBasicCommands},
  #endif

  #if defined(ZCL_USING_IDENTIFY_CLUSTER_CLIENT) || defined(ZCL_USING_IDENTIFY_CLUSTER_SERVER)
  {"identify", NULL, (PGM_P)zclIdentifyCommands},
  #endif //ZCL_USING_IDENTIFY_CLUSTER_CLIENT || SERVER
  #ifdef ZCL_USING_GROUPS_CLUSTER_CLIENT
  {"groups", NULL, (PGM_P)zclGroupsCommands},
  #endif
  #ifdef ZCL_USING_SCENES_CLUSTER_CLIENT
  {"scenes", NULL, (PGM_P)zclScenesCommands},
  #endif
  #ifdef ZCL_USING_ON_OFF_CLUSTER_CLIENT
  {"on-off", NULL, (PGM_P)zclOnOffCommands},
  #endif
  #ifdef ZCL_USING_LEVEL_CONTROL_CLUSTER_CLIENT
  {"level-control", NULL, (PGM_P)zclLevelControlCommands},
  #endif
  #ifdef ZCL_USING_THERMOSTAT_CLUSTER_CLIENT
  {"tstat", NULL, (PGM_P)zclThermostatCommands},
  #endif
  #ifdef EMBER_AF_PLUGIN_IAS_ZONE_SERVER
  {"ias-zone", NULL, (PGM_P)zclIasZoneCommands},
  #endif
  #ifdef EMBER_AF_PLUGIN_IAS_ACE_ZONE
  {"ias-zclient", NULL, (PGM_P)zclIasZoneClientCommands},
  #endif
  #ifdef ZCL_USING_IAS_ACE_CLUSTER_CLIENT
  {"ias-ace", NULL, (PGM_P)zclIasAceCommands},
  #endif
  #ifdef ZCL_USING_COLOR_CONTROL_CLUSTER_CLIENT
  {"colorcontrol", NULL, (PGM_P)zclColorControlCommands},
  #endif
#if defined(ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT) || defined(ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_SERVER)
  {"drlc", NULL, (PGM_P)zclDrlcCommands},
#endif //ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT || SERVER
#if defined(ZCL_USING_SIMPLE_METERING_CLUSTER_CLIENT) || defined(ZCL_USING_SIMPLE_METERING_CLUSTER_SERVER)
  {"sm", NULL, (PGM_P)zclSimpleMeteringCommands},
#endif //ZCL_USING_SIMPLE_METERING_CLUSTER_CLIENT || ZCL_USING_SIMPLE_METERING_CLUSTER_SERVER

#ifdef EMBER_AF_PLUGIN_SIMPLE_METERING_SERVER_TEST_METER_ENABLE
  {"tm", NULL, (PGM_P)zclTestMeterCommands},
#endif
  #ifdef ZCL_USING_PRICE_CLUSTER_CLIENT
  {"pr", NULL, (PGM_P)zclPriceClientCommands},
  #endif
  #ifdef EMBER_AF_PLUGIN_PRICE_SERVER
  {"set-price", NULL, (PGM_P)zclPriceServerCommands},  
  {"spr", NULL, (PGM_P)zclSpriceCommands},
  #endif
  #ifdef EMBER_AF_PLUGIN_MESSAGING_SERVER
  {"set-message", NULL, (PGM_P)zclSetMessageCommands},
  #endif
  #if defined(ZCL_USING_MESSAGING_CLUSTER_CLIENT)  \
      || defined(EMBER_AF_PLUGIN_MESSAGING_SERVER) \
      || defined(EMBER_AF_PLUGIN_MESSAGING_CLIENT)
  {"message", NULL, (PGM_P)zclMessageCommands},
  #endif
#if defined(ZCL_USING_GENERIC_TUNNEL_CLUSTER_CLIENT) || defined(ZCL_USING_GENERIC_TUNNEL_CLUSTER_SERVER)
  {"tunnel", NULL, (PGM_P)zclTunnelCommands},
#endif //ZCL_USING_GENERIC_TUNNEL_CLUSTER_CLIENT || ZCL_USING_GENERIC_TUNNEL_CLUSTER_SERVER
  #ifdef ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_CLIENT
  {"bacnet", NULL, (PGM_P)zclBacnetCommands},
  #endif

  #ifdef ZCL_USING_DOOR_LOCK_CLUSTER_CLIENT
  {"lock", NULL, (PGM_P)zclDoorLockCommands},
  #endif //ZCL_USING_DOOR_LOCK_CLUSTER_CLIENT

#if defined(ZCL_USING_TUNNELING_CLUSTER_CLIENT) || defined(ZCL_USING_TUNNELING_CLUSTER_SERVER)
  {"tunneling", NULL, (PGM_P)zclTunnelingCommands},
#endif //defined(ZCL_USING_TUNNELING_CLUSTER_CLIENT) || defined(ZCL_USING_TUNNELING_CLUSTER_SERVER)

  OTA_COMMANDS

  { NULL }
};

// ******************************************************
// keys command functions
// ******************************************************

EmberCommandEntry keysCommands[] = {
  {"clear", keysClearCommand, ""},
  {"print", keysPrintCommand, ""},
  {"delete", keysDeleteCommand, "u"},
  { NULL }

};


// ******************************************************
// option command functions
// ******************************************************

// option print-rx-msgs enable
// option print-rx-msgs disable
EmberCommandEntry optionPrintRxCommands[] = {
  {"enable", optionPrintRxCommand, ""},
  {"disable", optionPrintRxCommand, ""},
  { NULL }
};

// option binding-table print
// option binding-table clear
// option binding-table set <index> <cluster> <local ep> <remote ep> <EUI>
EmberCommandEntry optionBindingCommands[] = {
  {"print", optionBindingTablePrintCommand, ""},
  {"clear", optionBindingTableClearCommand, ""},
  {"set", optionBindingTableSetCommand, "uvuub"},
  { NULL }
};

// option address-table print
// option address-table set <index> <eui64> <node id>
EmberCommandEntry optionAddressCommands[] = {
  {"print", optionAddressTablePrintCommand, ""},
  {"set", optionAddressTableSetCommand, "ubv"},
  { NULL }
};

// option security aps [off|on]
EmberCommandEntry optionApsSecurityCommands[] = {
  {"on", optionApsSecurityCommand, ""},
  {"off", optionApsSecurityCommand, ""},
  { NULL }
};

EmberCommandEntry apsretryCommands[] = {
  {"on", optionApsRetryCommand, ""},
  {"off", optionApsRetryCommand, ""},
  {"def", optionApsRetryCommand, ""},
  { NULL }
};

EmberCommandEntry optionSecurityCommands[] = {
  {"aps", NULL, (PGM_P)optionApsSecurityCommands},
  { NULL }
};

EmberCommandEntry optionCommands[] = {
  {"print-rx-msgs", NULL, (PGM_P)optionPrintRxCommands},
  {"register", optionRegisterCommand, ""},
  {"disc", optionDiscoverCommand, "v"},
#ifdef EMBER_AF_CONCENTRATOR
  {"agg", optionAggregationCommand, ""},
#endif
  {"binding-table", NULL, (PGM_P)optionBindingCommands},
  {"address-table", NULL, (PGM_P)optionAddressCommands},
#ifdef EMBER_AF_USE_BUTTONS
  {"button0", optionButton0Command, ""},
  {"button1", optionButton1Command, ""},
#endif //EMBER_AF_USE_BUTTONS
  {"edb", optionEndDeviceBindCommand, "u"},
  {"security", NULL, (PGM_P)optionSecurityCommands},
  {"apsretry", NULL, (PGM_P)apsretryCommands},

#ifdef DEBUG_PRINT_FOR_ROUTING_TABLE
  {"route", optionPrintRouteCommand, ""},
#endif

#if EMBER_KEY_TABLE_SIZE > 0
  {"link", optionLinkCommand, "ubb"},
#endif

#ifdef EMBER_AF_PLUGIN_BACNET_PROTOCOL_TUNNEL
  {"bacnet", optionBacnetCommand, "u"},
#endif
  { NULL }
};

// ******************************************************
// Print commands.
//
// print attr
// print identify
// print groups
// print scenes
// print c (ias-ace info)
// print report
// print price
// print messaging
// print time
// print d (load control)
// print tunnel
// print library
// ******************************************************

EmberCommandEntry printCommands[] = {
  {"time", printTimeCommand, ""},
  {"attr", emberAfPrintAttributeTable, ""},
#ifdef EMBER_AF_PLUGIN_IDENTIFY
  {"identify", emAfIdentifyPrintInfo, ""},
#endif //EMBER_AF_PLUGIN_IDENTIFY
#ifdef EMBER_AF_PLUGIN_GROUPS_SERVER
  {"groups", emAfPluginGroupsServerPrintInfo, ""},
#endif //EMBER_AF_PLUGIN_GROUPS_SERVER
#ifdef EMBER_AF_PLUGIN_SCENES
  {"scenes", emAfPluginScenesServerPrintInfo, ""},
#endif //EMBER_AF_PLUGIN_SCENES
#ifdef EMBER_AF_PLUGIN_IAS_ACE_ZONE
  {"c", emAfIasAcePrintInfo, ""},
#endif //EMBER_AF_PLUGIN_IAS_ACE_ZONE
#ifndef ZA_NO_REPORTING_OPTIMIZATION
  {"report", emberAfPrintReportTable, ""},
#endif //ZA_NO_REPORTING_OPTIMIZATION
#if defined(EMBER_AF_PLUGIN_PRICE_CLIENT) || defined(EMBER_AF_PLUGIN_PRICE_SERVER)
  {"price", printPriceCommand, ""},
#endif //EMBER_AF_PLUGIN_PRICE_CLIENT || EMBER_AF_PLUGIN_PRICE_SERVER
#if defined(EMBER_AF_PLUGIN_MESSAGING_CLIENT) || defined(EMBER_AF_PLUGIN_MESSAGING_SERVER)
  {"messaging", printMessagingCommand, ""},
#endif //EMBER_AF_PLUGIN_MESSAGING_CLIENT || EMBER_AF_PLUGIN_MESSAGING_SERVER
#if defined(EMBER_AF_PLUGIN_DRLC) || defined(EMBER_AF_PLUGIN_DRLC_SERVER)
  {"drlc", printDrlcCommand, ""},
#endif //EMBER_AF_PLUGIN_DRLC || EMBER_AF_PLUGIN_DRLC_SERVER
#ifdef EMBER_AF_PLUGIN_GENERIC_TUNNEL
  {"tunnel", emAfPluginGenericTunnelPrintInfo, ""},
#endif //EMBER_AF_PLUGIN_GENERIC_TUNNEL
  { NULL }
};

// ******************************************************
// interpan commands
//
// mac is     : [FC 2; seq 1; dest PAN 2; dest addr 2|8; src pan 2; src addr 8]
// stub nwk is: [Frame Control 2]
// stub APS is: [FC 1; groupId 0|2; clusterId 2; appProfileId 2]
//
// MAC FC = bits 0,1,2: frame type (Data) 1
//          bit 3: security enabled = false (0)
//          bit 4: frame pending  = false (0)
//          bit 5: ack required = true (1)
//          bit 6: intra PAN = false (0)
//          bit 7,8,9: reserved (0)
//          bit 10,11: dest addr mode = group (1), short (2), long(3)
//          bit 12,13: reserved (0)
//          bit 14,15: src addr mode = long(3)
//   for GROUP_DEST FC is: 0xC421
//   for SHORT_DEST FC is: 0xC821
//   for LONG_DEST FC is : 0xCC21
//
// Stub NWK FC: bits 0,1: frame type 3 (0b11)
//              bits 2-5: protocol version 2 (0b0010)
//              bits 6-15: reserved (0)
//   this is always 0x000B
//
// stub APS FC: bits 0,1: 3 (0b11)
//              bits 2,3: delivery mode unicast(0), bcast(2), group(3)
//              bit 4: reserved (0)
//              bit 5: security: none (0)
//              bit 6: ack request: NO ack (0)
//              bit 7: ext header present: No (0)
//   this is 03 for unicast, 0B for bcast, 0F for group
//
// ******************************************************

EmberCommandEntry interpanCommands[] = {
  {"group", interpanCommand, "vvv"},
  {"short", interpanCommand, "vvv"},
  {"long",  interpanLongCommand, "bvvv"},
  { NULL }
};
