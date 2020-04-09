// *******************************************************************
// * tunneling-client.c
// *
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "../../util/common.h"
#include "tunneling-client.h"
#include "gen/tunneling-client-callback.h"

typedef struct {
  boolean    inUse;
  EmberEUI64 server;
  int8u      clientEndpoint;
  int8u      serverEndpoint;
  int16u     tunnelId;
  //int8u      protocolId;
  //int16u     manufacturerCode;
  //boolean    flowControlSupport;
} EmAfTunnelingClientTunnel;

static EmAfTunnelingClientTunnel tunnels[EMBER_AF_PLUGIN_TUNNELING_CLIENT_TUNNEL_LIMIT];

static EmberAfStatus emAfTunnelingClientFindTunnel(int16u tunnelId,
                                                   EmberNodeId nodeId,
                                                   int8u clientEndpoint,
                                                   int8u serverEndpoint,
                                                   EmAfTunnelingClientTunnel **tunnel);

void emberAfTunnelingClusterClientInitCallback(int8u endpoint)
{
  int8u i;
  for (i = 0; i < EMBER_AF_PLUGIN_TUNNELING_CLIENT_TUNNEL_LIMIT; i++) {
    tunnels[i].inUse = FALSE;
  }
}

boolean emberAfTunnelingClusterRequestTunnelResponseCallback(int16u tunnelId,
                                                             int8u tunnelStatus)
{
  EmberAfStatus status;

  emberAfTunnelingClusterPrintln("RX: RequestTunnelResponse 0x%2x, 0x%x",
                                 tunnelId,
                                 tunnelStatus);

  if (tunnelStatus == EMBER_ZCL_TUNNELING_TUNNEL_STATUS_SUCCESS) {
    int8u i;
    status = EMBER_ZCL_STATUS_INSUFFICIENT_SPACE;
    for (i = 0; i < EMBER_AF_PLUGIN_TUNNELING_CLIENT_TUNNEL_LIMIT; i++) {
      if (!tunnels[i].inUse) {
        tunnels[i].inUse = TRUE;
        emberLookupEui64ByNodeId(emberAfCurrentCommand()->source, tunnels[i].server);
        tunnels[i].clientEndpoint = emberAfCurrentCommand()->apsFrame->destinationEndpoint;
        tunnels[i].serverEndpoint = emberAfCurrentCommand()->apsFrame->sourceEndpoint;
        tunnels[i].tunnelId = tunnelId;
        //tunnels[i].protocolId = protocolId;
        //tunnels[i].manufacturerCode = manufacturerCode;
        //tunnels[i].flowControlSupport = flowControlSupport;
        status = EMBER_ZCL_STATUS_SUCCESS;
        break;
      }
    }
  } else {
    status = EMBER_ZCL_STATUS_SUCCESS;
  }

  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    emberAfPluginTunnelingClientTunnelOpenedCallback(tunnelId);
  }

  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}

boolean emberAfTunnelingClusterTransferDataServerToClientCallback(int16u tunnelId,
                                                                  int8u* data)
{
  EmAfTunnelingClientTunnel *tunnel;
  EmberAfStatus status;
  int16u dataLen = (emberAfCurrentCommand()->bufLen
                    - (emberAfCurrentCommand()->payloadStartIndex
                       + sizeof(tunnelId)));

  emberAfTunnelingClusterPrint("RX: TransferData 0x%2x, [", tunnelId);
  emberAfTunnelingClusterPrintBuffer(data, dataLen, FALSE);
  emberAfTunnelingClusterPrintln("]");

  status = emAfTunnelingClientFindTunnel(tunnelId,
                                         emberAfCurrentCommand()->source,
                                         emberAfCurrentCommand()->apsFrame->destinationEndpoint,
                                         emberAfCurrentCommand()->apsFrame->sourceEndpoint,
                                         &tunnel);
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    emberAfPluginTunnelingClientDataReceivedCallback(tunnelId, data, dataLen);
    emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  } else {
    emberAfFillCommandTunnelingClusterTransferDataErrorClientToServer(tunnelId,
                                                                      (status == EMBER_ZCL_STATUS_NOT_AUTHORIZED
                                                                       ? EMBER_ZCL_TUNNELING_TRANSFER_DATA_STATUS_WRONG_DEVICE
                                                                       : EMBER_ZCL_TUNNELING_TRANSFER_DATA_STATUS_NO_SUCH_TUNNEL));
    emberAfGetCommandApsFrame()->options |= EMBER_APS_OPTION_SOURCE_EUI64;
    emberAfSendResponse();
  }

  return TRUE;
}

boolean emberAfTunnelingClusterTransferDataErrorServerToClientCallback(int16u tunnelId,
                                                                       int8u transferDataStatus)
{
  EmAfTunnelingClientTunnel *tunnel;
  EmberAfStatus status;

  emberAfTunnelingClusterPrintln("RX: TransferDataError 0x%2x, 0x%x",
                                 tunnelId,
                                 transferDataStatus);

  status = emAfTunnelingClientFindTunnel(tunnelId,
                                         emberAfCurrentCommand()->source,
                                         emberAfCurrentCommand()->apsFrame->destinationEndpoint,
                                         emberAfCurrentCommand()->apsFrame->sourceEndpoint,
                                         &tunnel);
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    tunnel->inUse = FALSE;
    emberAfPluginTunnelingClientDataErrorCallback(tunnelId, transferDataStatus);
  }

  emberAfSendDefaultResponse(emberAfCurrentCommand(), status);
  return TRUE;
}

EmberAfStatus emberAfPluginTunnelingClientTransferData(int16u tunnelId,
                                                       int8u *data,
                                                       int16u dataLen)
{
  int8u i;
  for (i = 0; i < EMBER_AF_PLUGIN_TUNNELING_CLIENT_TUNNEL_LIMIT; i++) {
    if (tunnels[i].inUse && tunnels[i].tunnelId == tunnelId) {
      EmberStatus status;
      EmberNodeId nodeId = emberLookupNodeIdByEui64(tunnels[i].server);
      emberAfFillCommandTunnelingClusterTransferDataClientToServer(tunnelId,
                                                                   data,
                                                                   dataLen);
      emberAfGetCommandApsFrame()->sourceEndpoint = tunnels[i].clientEndpoint;
      emberAfGetCommandApsFrame()->destinationEndpoint = tunnels[i].serverEndpoint;
      emberAfGetCommandApsFrame()->options |= EMBER_APS_OPTION_SOURCE_EUI64;
      status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, nodeId);
      return (status == EMBER_SUCCESS
              ? EMBER_ZCL_STATUS_SUCCESS
              : EMBER_ZCL_STATUS_FAILURE);
    }
  }
  return EMBER_ZCL_STATUS_NOT_FOUND;
}

EmberAfStatus emberAfPluginTunnelingClientCloseTunnel(int16u tunnelId)
{
  int8u i;
  for (i = 0; i < EMBER_AF_PLUGIN_TUNNELING_CLIENT_TUNNEL_LIMIT; i++) {
    if (tunnels[i].inUse && tunnels[i].tunnelId == tunnelId) {
      EmberStatus status;
      EmberNodeId nodeId = emberLookupNodeIdByEui64(tunnels[i].server);
      emberAfFillCommandTunnelingClusterCloseTunnel(tunnelId);
      emberAfGetCommandApsFrame()->sourceEndpoint = tunnels[i].clientEndpoint;
      emberAfGetCommandApsFrame()->destinationEndpoint = tunnels[i].serverEndpoint;
      emberAfGetCommandApsFrame()->options |= EMBER_APS_OPTION_SOURCE_EUI64;
      status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, nodeId);
      if (status == EMBER_SUCCESS) {
        tunnels[i].inUse = FALSE;
        return EMBER_ZCL_STATUS_SUCCESS;
      } else {
        return EMBER_ZCL_STATUS_FAILURE;
      }
    }
  }
  return EMBER_ZCL_STATUS_NOT_FOUND;
}

static EmberAfStatus emAfTunnelingClientFindTunnel(int16u tunnelId,
                                                   EmberNodeId nodeId,
                                                   int8u clientEndpoint,
                                                   int8u serverEndpoint,
                                                   EmAfTunnelingClientTunnel **tunnel)
{
  EmberEUI64 server;
  int8u i;
  emberLookupEui64ByNodeId(nodeId, server);
  for (i = 0; i < EMBER_AF_PLUGIN_TUNNELING_CLIENT_TUNNEL_LIMIT; i++) {
    if (tunnels[i].inUse
        && tunnels[i].tunnelId == tunnelId
        && tunnels[i].clientEndpoint == clientEndpoint) {
      if (MEMCOMPARE(tunnels[i].server, server, EUI64_SIZE) == 0
          && tunnels[i].serverEndpoint == serverEndpoint) {
        *tunnel = &tunnels[i];
        return EMBER_ZCL_STATUS_SUCCESS;
      } else {
        return EMBER_ZCL_STATUS_NOT_AUTHORIZED;
      }
    }
  }
  return EMBER_ZCL_STATUS_NOT_FOUND;
}
