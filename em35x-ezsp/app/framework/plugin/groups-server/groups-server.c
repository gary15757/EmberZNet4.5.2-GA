// *******************************************************************
// * groups-server.c
// *
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "groups-server.h"

#ifdef EZSP_HOST
  static EmberAfGroupTableEntry groupTable[EMBER_AF_PLUGIN_GROUPS_SERVER_TABLE_SIZE];
  #define emAfPluginGroupsServerGetGroup(i, entry) (*entry = groupTable[i])
  #define emAfPluginGroupsServerSetGroup(i, entry) (groupTable[i] = *entry)
#else
  #define emAfPluginGroupsServerGetGroup(i, entry) \
    halCommonGetIndexedToken(entry, TOKEN_GROUP_TABLE, i)
  #define emAfPluginGroupsServerSetGroup(i, entry) \
    halCommonSetIndexedToken(TOKEN_GROUP_TABLE, i, entry)
#endif

void emberAfGroupsClusterServerInitCallback(int8u endpoint)
{
#ifdef EMBER_AF_PLUGIN_GROUPS_SERVER_NAME_SUPPORT
  // The high bit of Name Support indicates whether group names are supported.
  EmberAfStatus status;
  int8u nameSupport = BIT(7);
  status = emberAfWriteAttribute(endpoint,
                                 ZCL_GROUPS_CLUSTER_ID,
                                 ZCL_GROUP_NAME_SUPPORT_ATTRIBUTE_ID,
                                 CLUSTER_MASK_SERVER,
                                 (int8u *)&nameSupport,
                                 ZCL_BITMAP8_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfGroupsClusterPrintln("ERR: writing name support %x", status);
  }
#endif
}

void emAfPluginGroupsServerPrintInfo(void)
{
  int8u i;
  for (i = 0; i < EMBER_AF_PLUGIN_GROUPS_SERVER_TABLE_SIZE; i++) {
    EmberAfGroupTableEntry entry;
    emAfPluginGroupsServerGetGroup(i, &entry);
    emberAfCorePrint("%x:", i);
    if (entry.endpoint != EMBER_AF_GROUP_TABLE_UNUSED_ENDPOINT_ID) {
      emberAfCorePrint("ep[%x] id[%2x]", entry.endpoint, entry.groupId);
#ifdef EMBER_AF_PLUGIN_GROUPS_SERVER_NAME_SUPPORT
      emberAfCorePrint(" name(%x)[", emberAfStringLength(entry.name));
      emberAfCorePrintString(entry.name);
      emberAfCorePrint("]");
#endif
    }
    emberAfCorePrintln("");
  }
}

// --------------------------
// Internal functions used to keep the group table synchronized with the binding
// table.
//
// In the binding:
// The first two bytes of the identifier is set to the groupId
// The next six bytes of the identifier are set to 0xFE
// The cluster is set to 0xFFFE
// The local endpoint is set to the endpoint that is mapped to this group
// The remote endpoint is set to 0xFE
// --------------------------
static EmberAfStatus addEntryToGroupTable(int8u endpoint,
                                          int16u groupId,
                                          int8u *groupName)
{
  int8u i, index = EMBER_AF_GROUP_TABLE_NULL_INDEX;

  // Check for duplicates and also watch for empty slots along the way.  If we
  // don't have room in the group table, we'll reject the group here.  We still
  // need to make sure there is space in the binding table as well.
  for (i = 0; i < EMBER_AF_PLUGIN_GROUPS_SERVER_TABLE_SIZE; i++) {
    EmberAfGroupTableEntry entry;
    emAfPluginGroupsServerGetGroup(i, &entry);
    if (entry.endpoint == endpoint && entry.groupId == groupId) {
      return EMBER_ZCL_STATUS_DUPLICATE_EXISTS;
    } else if (entry.endpoint == EMBER_AF_GROUP_TABLE_UNUSED_ENDPOINT_ID
               && index == EMBER_AF_GROUP_TABLE_NULL_INDEX) {
      index = i;
    }
  }
  if (index == EMBER_AF_GROUP_TABLE_NULL_INDEX) {
    emberAfGroupsClusterPrintln("ERR: Group table is full");
    return EMBER_ZCL_STATUS_INSUFFICIENT_SPACE;
  }

  // Look for an empty binding slot.
  for (i = 0; i < EMBER_BINDING_TABLE_SIZE; i++) {
    EmberBindingTableEntry binding;
    if (emberGetBinding(i, &binding) == EMBER_SUCCESS
        && binding.type == EMBER_UNUSED_BINDING) {
      EmberStatus status;
      int8u j;
      binding.type = EMBER_MULTICAST_BINDING;
      binding.identifier[0] = LOW_BYTE(groupId);
      binding.identifier[1] = HIGH_BYTE(groupId);
      for (j = 2; j < 8; j++) {
        binding.identifier[j] = 0xFE;
      }
      binding.local = endpoint;
      binding.remote = 0xFE;
      binding.clusterId = 0xFFFE;

      status = emberSetBinding(i, &binding);
      if (status == EMBER_SUCCESS) {
        EmberAfGroupTableEntry entry;
        entry.endpoint = endpoint;
        entry.groupId = groupId;
        entry.bindingIndex = i;
#ifdef EMBER_AF_PLUGIN_GROUPS_SERVER_NAME_SUPPORT
        emberAfCopyString(entry.name,
                          groupName,
                          ZCL_GROUPS_CLUSTER_MAXIMUM_NAME_LENGTH);
#endif
        emAfPluginGroupsServerSetGroup(index, &entry);
        return EMBER_ZCL_STATUS_SUCCESS;
      } else {
        emberAfGroupsClusterPrintln("ERR: Failed to create binding (0x%x)",
                                    status);
      }
    }
  }
  emberAfGroupsClusterPrintln("ERR: Binding table is full");
  return EMBER_ZCL_STATUS_INSUFFICIENT_SPACE;
}

static EmberAfStatus removeEntryFromGroupTable(int8u index)
{
  EmberAfGroupTableEntry entry;
  emAfPluginGroupsServerGetGroup(index, &entry);
  if (entry.endpoint != EMBER_AF_GROUP_TABLE_UNUSED_ENDPOINT_ID) {
    EmberStatus status = emberDeleteBinding(entry.bindingIndex);
    if (status == EMBER_SUCCESS) {
      entry.endpoint = EMBER_AF_GROUP_TABLE_UNUSED_ENDPOINT_ID;
      emAfPluginGroupsServerSetGroup(index, &entry);
      return EMBER_ZCL_STATUS_SUCCESS;
    } else {
      emberAfGroupsClusterPrintln("ERR: Failed to delete binding (0x%x)",
                                  status);
      return EMBER_ZCL_STATUS_FAILURE;
    }
  }
  return EMBER_ZCL_STATUS_SUCCESS;
}

boolean emberAfGroupsClusterAddGroupCallback(int16u groupId, int8u *groupName)
{
  EmberAfStatus status;

  emberAfGroupsClusterPrint("RX: AddGroup 0x%2x, \"", groupId);
  emberAfGroupsClusterPrintString(groupName);
  emberAfGroupsClusterPrintln("\"");

  status = addEntryToGroupTable(emberAfCurrentEndpoint(), groupId, groupName);
  emberAfFillCommandGroupsClusterAddGroupResponse(status, groupId);
  emberAfSendResponse();
  return TRUE;
}

boolean emberAfGroupsClusterViewGroupCallback(int16u groupId)
{
  EmberAfStatus status = EMBER_ZCL_STATUS_NOT_FOUND;
  int8u groupName[ZCL_GROUPS_CLUSTER_MAXIMUM_NAME_LENGTH + 1] = {0};
  int8u i;

  emberAfGroupsClusterPrintln("RX: ViewGroup 0x%2x", groupId);

  for (i = 0; i < EMBER_AF_PLUGIN_GROUPS_SERVER_TABLE_SIZE; i++) {
    EmberAfGroupTableEntry entry;
    emAfPluginGroupsServerGetGroup(i, &entry);
    if (entry.endpoint == emberAfCurrentEndpoint()
        && entry.groupId == groupId) {
#ifdef EMBER_AF_PLUGIN_GROUPS_SERVER_NAME_SUPPORT
      emberAfCopyString(groupName,
                        entry.name,
                        ZCL_GROUPS_CLUSTER_MAXIMUM_NAME_LENGTH);
#endif
      status = EMBER_ZCL_STATUS_SUCCESS;
      break;
    }
  }

  emberAfFillCommandGroupsClusterViewGroupResponse(status, groupId, groupName);
  emberAfSendResponse();
  return TRUE;
}

boolean emberAfGroupsClusterGetGroupMembershipCallback(int8u groupCount,
                                                       int8u *groupList)
{
  int8u i, j;
  int8u count = 0;
  int8u list[EMBER_AF_PLUGIN_GROUPS_SERVER_TABLE_SIZE << 1];
  int8u listLen = 0;

  emberAfGroupsClusterPrint("RX: GetGroupMembership 0x%x,", groupCount);
  for (i = 0; i < groupCount; i++) {
    emberAfGroupsClusterPrint(" [0x%2x]",
                              emberAfGetInt16u(groupList + (i << 1), 0, 2));
  }
  emberAfGroupsClusterPrintln("");

  // When Group Count is zero, respond with a list of all active groups.
  // Otherwise, respond with a list of matches.
  if (groupCount == 0) {
    for (i = 0; i < EMBER_AF_PLUGIN_GROUPS_SERVER_TABLE_SIZE; i++) {
      EmberAfGroupTableEntry entry;
      emAfPluginGroupsServerGetGroup(i, &entry);
      if (entry.endpoint == emberAfCurrentEndpoint()) {
        list[listLen]     = LOW_BYTE(entry.groupId);
        list[listLen + 1] = HIGH_BYTE(entry.groupId);
        listLen += 2;
        count++;
      }
    }
  } else {
    for (i = 0; i < groupCount; i++) {
      int16u groupId = emberAfGetInt16u(groupList + (i << 1), 0, 2);
      for (j = 0; j < EMBER_AF_PLUGIN_GROUPS_SERVER_TABLE_SIZE; j++) {
        EmberAfGroupTableEntry entry;
        emAfPluginGroupsServerGetGroup(j, &entry);
        if (entry.endpoint == emberAfCurrentEndpoint()
            && groupId == entry.groupId) {
          list[listLen]     = LOW_BYTE(entry.groupId);
          list[listLen + 1] = HIGH_BYTE(entry.groupId);
          listLen += 2;
          count++;
        }
      }
    }
  }

  // Only send a response if the Group Count was zero or if one or more active
  // groups matched.  Otherwise, a Default Response is sent.
  if (groupCount == 0 || count != 0) {
    // A capacity of 0xFF means that it is unknown if any further groups may be
    // added.  Each group requires a binding and, because the binding table is
    // used for other purposes besides groups, we can't be sure what the
    // capacity will be in the future.
    emberAfFillCommandGroupsClusterGetGroupMembershipResponse(0xFF, // capacity
                                                              count,
                                                              list,
                                                              listLen);
    emberAfSendResponse();
  } else {
    emberAfSendDefaultResponse(emberAfCurrentCommand(),
                               EMBER_ZCL_STATUS_NOT_FOUND);
  }
  return TRUE;
}

boolean emberAfGroupsClusterRemoveGroupCallback(int16u groupId)
{
  EmberAfStatus status = EMBER_ZCL_STATUS_NOT_FOUND;
  int8u i;

  emberAfGroupsClusterPrintln("RX: RemoveGroup 0x%2x", groupId);

  for (i = 0; i < EMBER_AF_PLUGIN_GROUPS_SERVER_TABLE_SIZE; i++) {
    EmberAfGroupTableEntry entry;
    emAfPluginGroupsServerGetGroup(i, &entry);
    if (entry.endpoint == emberAfCurrentEndpoint()
        && entry.groupId == groupId) {
      status = removeEntryFromGroupTable(i);
      break;
    }
  }

  emberAfFillCommandGroupsClusterRemoveGroupResponse(status, groupId);
  emberAfSendResponse();
  return TRUE;
}

boolean emberAfGroupsClusterRemoveAllGroupsCallback(void)
{
  int8u i;
  boolean success = TRUE;

  emberAfGroupsClusterPrintln("RX: RemoveAllGroups");

  for (i = 0; i < EMBER_AF_PLUGIN_GROUPS_SERVER_TABLE_SIZE; i++) {
    EmberAfGroupTableEntry entry;
    emAfPluginGroupsServerGetGroup(i, &entry);
    if (entry.endpoint == emberAfCurrentEndpoint()) {
      success = (removeEntryFromGroupTable(i) == EMBER_ZCL_STATUS_SUCCESS
                 && success);
    }
  }

  emberAfSendDefaultResponse(emberAfCurrentCommand(),
                             (success
                              ? EMBER_ZCL_STATUS_SUCCESS
                              : EMBER_ZCL_STATUS_FAILURE));
  return TRUE;
}

boolean emberAfGroupsClusterAddGroupIfIdentifyingCallback(int16u groupId,
                                                          int8u *groupName)
{
  EmberAfStatus status;

  emberAfGroupsClusterPrint("RX: AddGroupIfIdentifying 0x%2x, \"", groupId);
  emberAfGroupsClusterPrintString(groupName);
  emberAfGroupsClusterPrintln("\"");

#ifdef ZCL_USING_IDENTIFY_CLUSTER_SERVER
  {
    int16u identifyTime;
    status = emberAfReadAttribute(emberAfCurrentEndpoint(),
                                  ZCL_IDENTIFY_CLUSTER_ID,
                                  ZCL_IDENTIFY_TIME_ATTRIBUTE_ID,
                                  CLUSTER_MASK_SERVER,
                                  (int8u *)&identifyTime,
                                  sizeof(identifyTime),
                                  NULL); // data type
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      emberAfGroupsClusterPrintln("ERR: reading identify time %x", status);
    } else if (identifyTime == 0) {
      status = EMBER_ZCL_STATUS_FAILURE;
    } else {
      status = addEntryToGroupTable(emberAfCurrentEndpoint(),
                                    groupId,
                                    groupName);
    }
  }
#else
  status = EMBER_ZCL_STATUS_FAILURE;
#endif

  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}

boolean emberAfGroupsClusterEndpointInGroupCallback(int8u endpoint,
                                                    int16u groupId)
{
  int8u i;
  for (i = 0; i < EMBER_AF_PLUGIN_GROUPS_SERVER_TABLE_SIZE; i++) {
    EmberAfGroupTableEntry entry;
    emAfPluginGroupsServerGetGroup(i, &entry);
    if (entry.endpoint == endpoint && entry.groupId == groupId) {
      return TRUE;
    }
  }
  return FALSE;
}

void emberAfGroupsClusterClearGroupTableCallback(void)
{
  int8u i;
  for (i = 0; i < EMBER_AF_PLUGIN_GROUPS_SERVER_TABLE_SIZE; i++) {
    removeEntryFromGroupTable(i);
  }
}
