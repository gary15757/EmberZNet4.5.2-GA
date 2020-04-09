// *******************************************************************
// * tunneling-server.c
// *
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "../../util/common.h"
#include "tunneling-server.h"
#include "gen/tunneling-server-callback.h"

typedef struct {
  boolean    inUse;
  EmberEUI64 client;
  int8u      clientEndpoint;
  int8u      serverEndpoint;
  int16u     tunnelId;
  //int8u      protocolId;
  //int16u     manufacturerCode;
  //boolean    flowControlSupport;
  int32u     lastActive;
} EmAfTunnelingServerTunnel;

static EmAfTunnelingServerTunnel tunnels[EMBER_AF_PLUGIN_TUNNELING_SERVER_TUNNEL_LIMIT];

static EmberAfStatus emAfTunnelingServerFindTunnel(int16u tunnelId,
                                                   EmberNodeId nodeId,
                                                   int8u clientEndpoint,
                                                   int8u serverEndpoint,
                                                   EmAfTunnelingServerTunnel **tunnel);
static void emAfTunnelingServerCloseInactiveTunnels(int8u endpoint);

void emberAfTunnelingClusterServerInitCallback(int8u endpoint)
{
  EmberAfStatus status;
  int16u closeTunnelTimeout = EMBER_AF_PLUGIN_TUNNELING_SERVER_CLOSE_TUNNEL_TIMEOUT;
  int8u i;

  for (i = 0; i < EMBER_AF_PLUGIN_TUNNELING_SERVER_TUNNEL_LIMIT; i++) {
    tunnels[i].inUse = FALSE;
  }

  status = emberAfWriteAttribute(endpoint,
                                 ZCL_TUNNELING_CLUSTER_ID,
                                 ZCL_CLOSE_TUNNEL_TIMEOUT_ATTRIBUTE_ID,
                                 CLUSTER_MASK_SERVER,
                                 (int8u *)&closeTunnelTimeout,
                                 ZCL_INT16U_ATTRIBUTE_TYPE);
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_TUNNELING_CLUSTER)
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfIdentifyClusterPrintln("ERR: writing close tunnel timeout 0x%x",
                                  status);
  }
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_TUNNELING_CLUSTER)
}

void emberAfTunnelingClusterServerTickCallback(int8u endpoint)
{
  emAfTunnelingServerCloseInactiveTunnels(endpoint);
}

void emberAfTunnelingClusterServerAttributeChangedCallback(int8u endpoint,
                                                           EmberAfAttributeId attributeId)
{
  if (attributeId == ZCL_CLOSE_TUNNEL_TIMEOUT_ATTRIBUTE_ID) {
    emAfTunnelingServerCloseInactiveTunnels(endpoint);
  }
}

boolean emberAfTunnelingClusterRequestTunnelCallback(int8u protocolId,
                                                     int16u manufacturerCode,
                                                     int8u flowControlSupport)
{
  int16u tunnelId = ZCL_TUNNELING_CLUSTER_INVALID_TUNNEL_ID;
  EmberAfTunnelingTunnelStatus status = EMBER_ZCL_TUNNELING_TUNNEL_STATUS_NO_MORE_TUNNEL_IDS;

  emberAfTunnelingClusterPrintln("RX: RequestTunnel 0x%x, 0x%2x, 0x%x",
                                 protocolId,
                                 manufacturerCode,
                                 flowControlSupport);

  if (!emberAfPluginTunnelingServerIsProtocolSupportedCallback(protocolId,
                                                               manufacturerCode)) {
    status = EMBER_ZCL_TUNNELING_TUNNEL_STATUS_PROTOCOL_NOT_SUPPORTED;
  } else if (flowControlSupport) {
    // TODO: Implement support for flow control.
    status = EMBER_ZCL_TUNNELING_TUNNEL_STATUS_FLOW_CONTROL_NOT_SUPPORTED;
  } else {
    int8u i;
    for (i = 0; i < EMBER_AF_PLUGIN_TUNNELING_SERVER_TUNNEL_LIMIT; i++) {
      if (!tunnels[i].inUse) {
        tunnels[i].inUse = TRUE;
        emberLookupEui64ByNodeId(emberAfCurrentCommand()->source, tunnels[i].client);
        tunnels[i].clientEndpoint = emberAfCurrentCommand()->apsFrame->sourceEndpoint;
        tunnels[i].serverEndpoint = emberAfCurrentCommand()->apsFrame->destinationEndpoint;
        tunnels[i].tunnelId = tunnelId = i;
        //tunnels[i].protocolId = protocolId;
        //tunnels[i].manufacturerCode = manufacturerCode;
        //tunnels[i].flowControlSupport = flowControlSupport;
        tunnels[i].lastActive = emberAfGetCurrentTime();
        emAfTunnelingServerCloseInactiveTunnels(emberAfCurrentCommand()->apsFrame->sourceEndpoint);
        status = EMBER_ZCL_TUNNELING_TUNNEL_STATUS_SUCCESS;
        break;
      }
    }
  }

  if (status == EMBER_ZCL_TUNNELING_TUNNEL_STATUS_SUCCESS) {
    emberAfPluginTunnelingServerTunnelOpenedCallback(tunnelId,
                                                     protocolId,
                                                     manufacturerCode);
  }

  emberAfFillCommandTunnelingClusterRequestTunnelResponse(tunnelId, status);
  emberAfGetCommandApsFrame()->options |= EMBER_APS_OPTION_SOURCE_EUI64;
  emberAfSendResponse();
  return TRUE;
}

boolean emberAfTunnelingClusterCloseTunnelCallback(int16u tunnelId)
{
  EmAfTunnelingServerTunnel *tunnel;
  EmberAfStatus status;

  emberAfTunnelingClusterPrintln("RX: CloseTunnel 0x%2x", tunnelId);

  status = emAfTunnelingServerFindTunnel(tunnelId,
                                         emberAfCurrentCommand()->source,
                                         emberAfCurrentCommand()->apsFrame->sourceEndpoint,
                                         emberAfCurrentCommand()->apsFrame->destinationEndpoint,
                                         &tunnel);
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    tunnel->inUse = FALSE;
    emberAfPluginTunnelingServerTunnelClosedCallback(tunnelId,
                                                     CLOSE_INITIATED_BY_CLIENT);
  }

  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}

boolean emberAfTunnelingClusterTransferDataClientToServerCallback(int16u tunnelId,
                                                                  int8u* data)
{
  EmAfTunnelingServerTunnel *tunnel;
  EmberAfStatus status;
  int16u dataLen = (emberAfCurrentCommand()->bufLen
                    - (emberAfCurrentCommand()->payloadStartIndex
                       + sizeof(tunnelId)));

  emberAfTunnelingClusterPrint("RX: TransferData 0x%2x, [", tunnelId);
  emberAfTunnelingClusterPrintBuffer(data, dataLen, FALSE);
  emberAfTunnelingClusterPrintln("]");

  status = emAfTunnelingServerFindTunnel(tunnelId,
                                         emberAfCurrentCommand()->source,
                                         emberAfCurrentCommand()->apsFrame->sourceEndpoint,
                                         emberAfCurrentCommand()->apsFrame->destinationEndpoint,
                                         &tunnel);
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    tunnel->lastActive = emberAfGetCurrentTime();
    emberAfPluginTunnelingServerDataReceivedCallback(tunnelId, data, dataLen);
    emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  } else {
    emberAfFillCommandTunnelingClusterTransferDataErrorServerToClient(tunnelId,
                                                                      (status == EMBER_ZCL_STATUS_NOT_AUTHORIZED
                                                                       ? EMBER_ZCL_TUNNELING_TRANSFER_DATA_STATUS_WRONG_DEVICE
                                                                       : EMBER_ZCL_TUNNELING_TRANSFER_DATA_STATUS_NO_SUCH_TUNNEL));
    emberAfGetCommandApsFrame()->options |= EMBER_APS_OPTION_SOURCE_EUI64;
    emberAfSendResponse();
  }

  return TRUE;
}

boolean emberAfTunnelingClusterTransferDataErrorClientToServerCallback(int16u tunnelId,
                                                                       int8u transferDataStatus)
{
  EmAfTunnelingServerTunnel *tunnel;
  EmberAfStatus status;

  emberAfTunnelingClusterPrintln("RX: TransferDataError 0x%2x, 0x%x",
                                 tunnelId,
                                 transferDataStatus);

  status = emAfTunnelingServerFindTunnel(tunnelId,
                                         emberAfCurrentCommand()->source,
                                         emberAfCurrentCommand()->apsFrame->sourceEndpoint,
                                         emberAfCurrentCommand()->apsFrame->destinationEndpoint,
                                         &tunnel);
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    tunnel->inUse = FALSE;
    emberAfPluginTunnelingServerDataErrorCallback(tunnelId, transferDataStatus);
  }

  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}

EmberAfStatus emberAfPluginTunnelingServerTransferData(int16u tunnelId,
                                                       int8u *data,
                                                       int16u dataLen)
{
  int8u i;
  for (i = 0; i < EMBER_AF_PLUGIN_TUNNELING_SERVER_TUNNEL_LIMIT; i++) {
    if (tunnels[i].inUse && tunnels[i].tunnelId == tunnelId) {
      EmberStatus status;
      EmberNodeId nodeId = emberLookupNodeIdByEui64(tunnels[i].client);
      emberAfFillCommandTunnelingClusterTransferDataServerToClient(tunnelId,
                                                                   data,
                                                                   dataLen);
      emberAfGetCommandApsFrame()->sourceEndpoint = tunnels[i].serverEndpoint;
      emberAfGetCommandApsFrame()->destinationEndpoint = tunnels[i].clientEndpoint;
      emberAfGetCommandApsFrame()->options |= EMBER_APS_OPTION_SOURCE_EUI64;
      status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, nodeId);
      tunnels[i].lastActive = emberAfGetCurrentTime();
      return (status == EMBER_SUCCESS
              ? EMBER_ZCL_STATUS_SUCCESS
              : EMBER_ZCL_STATUS_FAILURE);
    }
  }
  return EMBER_ZCL_STATUS_NOT_FOUND;
}

static EmberAfStatus emAfTunnelingServerFindTunnel(int16u tunnelId,
                                                   EmberNodeId nodeId,
                                                   int8u clientEndpoint,
                                                   int8u serverEndpoint,
                                                   EmAfTunnelingServerTunnel **tunnel)
{
  EmberEUI64 client;
  int8u i;
  emberLookupEui64ByNodeId(nodeId, client);
  for (i = 0; i < EMBER_AF_PLUGIN_TUNNELING_SERVER_TUNNEL_LIMIT; i++) {
    if (tunnels[i].inUse
        && tunnels[i].tunnelId == tunnelId
        && tunnels[i].serverEndpoint == serverEndpoint) {
      if (MEMCOMPARE(tunnels[i].client, client, EUI64_SIZE) == 0
          && tunnels[i].clientEndpoint == clientEndpoint) {
        *tunnel = &tunnels[i];
        return EMBER_ZCL_STATUS_SUCCESS;
      } else {
        return EMBER_ZCL_STATUS_NOT_AUTHORIZED;
      }
    }
  }
  return EMBER_ZCL_STATUS_NOT_FOUND;
}

static void emAfTunnelingServerCloseInactiveTunnels(int8u endpoint)
{
  EmberAfStatus status;
  int32u currentTime = emberAfGetCurrentTime();
  int32u leastRecentlyActive = 0xFFFFFFFFUL;
  int16u closeTunnelTimeout;
  boolean activeTunnels = FALSE;
  int8u i;

  status = emberAfReadAttribute(endpoint,
                                ZCL_TUNNELING_CLUSTER_ID,
                                ZCL_CLOSE_TUNNEL_TIMEOUT_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (int8u *)&closeTunnelTimeout,
                                sizeof(closeTunnelTimeout),
                                NULL); // data type
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfIdentifyClusterPrintln("ERR: reading close tunnel timeout 0x%x",
                                  status);
    return;
  }

  for (i = 0; i < EMBER_AF_PLUGIN_TUNNELING_SERVER_TUNNEL_LIMIT; i++) {
    if (tunnels[i].inUse && tunnels[i].serverEndpoint == endpoint) {
      if (currentTime - tunnels[i].lastActive > closeTunnelTimeout) {
        tunnels[i].inUse = FALSE;
        emberAfPluginTunnelingServerTunnelClosedCallback(tunnels[i].tunnelId,
                                                         CLOSE_INITIATED_BY_SERVER);
      } else {
        activeTunnels = TRUE;
        if (tunnels[i].lastActive < leastRecentlyActive) {
          leastRecentlyActive = tunnels[i].lastActive;
        }
      }
    }
  }

  if (activeTunnels) {
    emberAfScheduleClusterTick(endpoint,
                              ZCL_TUNNELING_CLUSTER_ID,
                              FALSE, // server cluster
                              ((closeTunnelTimeout
                                - (currentTime - leastRecentlyActive))
                               * MILLISECOND_TICKS_PER_SECOND),
                              EMBER_AF_OK_TO_HIBERNATE);
  }
}
