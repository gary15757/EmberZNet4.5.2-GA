// *******************************************************************
// * generic-tunnel.c
// *
// *
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "../../util/common.h"
#include "generic-tunnel.h"

// The stored protocol address of this device.  The address is shared by all
// endpoints.  The first byte is the length.
static int8u myGenericProtocolAddress[EMBER_AF_PLUGIN_GENERIC_TUNNEL_PROTOCOL_ADDRESS_SIZE + 1];

void emberAfGenericTunnelClusterServerInitCallback(int8u endpoint)
{
  EmberAfStatus status;
  int16u maxSize;

  maxSize = EMBER_AF_INCOMING_BUFFER_LENGTH;
  status = emberAfWriteAttribute(endpoint,
                                 ZCL_GENERIC_TUNNEL_CLUSTER_ID,
                                 ZCL_MAXIMUM_INCOMING_TRANSFER_SIZE_ATTRIBUTE_ID,
                                 CLUSTER_MASK_SERVER,
                                 (int8u *)&maxSize,
                                 ZCL_INT16U_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfGenericTunnelClusterPrintln("ERR: writing maximum incoming transfer size %x",
                                       status);
  }

  maxSize = EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH;
  status = emberAfWriteAttribute(endpoint,
                                 ZCL_GENERIC_TUNNEL_CLUSTER_ID,
                                 ZCL_MAXIMUM_OUTGOING_TRANSFER_SIZE_ATTRIBUTE_ID,
                                 CLUSTER_MASK_SERVER,
                                 (int8u *)&maxSize,
                                 ZCL_INT16U_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfGenericTunnelClusterPrintln("ERR: writing maximum outgoing transfer size %x",
                                       status);
  }

  // Set up the default address.  This could come from a token, for now it
  // starts out as 0x00FFFF, which means something to BACnet.  The first byte is
  // the length.
  myGenericProtocolAddress[0] = 3;
  myGenericProtocolAddress[1] = 0x00;
  myGenericProtocolAddress[2] = 0xFF;
  myGenericProtocolAddress[3] = 0xFF;
  status = emberAfWriteAttribute(endpoint,
                                 ZCL_GENERIC_TUNNEL_CLUSTER_ID,
                                 ZCL_PROTOCOL_ADDRESS_ATTRIBUTE_ID,
                                 CLUSTER_MASK_SERVER,
                                 myGenericProtocolAddress,
                                 ZCL_OCTET_STRING_ATTRIBUTE_TYPE);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfGenericTunnelClusterPrintln("ERR: writing protocol address %x",
                                       status);
  }
}

void emberAfGenericTunnelClusterServerAttributeChangedCallback(int8u endpoint,
                                                               EmberAfAttributeId attributeId)
{
  if (attributeId == ZCL_PROTOCOL_ADDRESS_ATTRIBUTE_ID) {
    EmberAfStatus status = emberAfReadAttribute(endpoint,
                                                ZCL_GENERIC_TUNNEL_CLUSTER_ID,
                                                ZCL_PROTOCOL_ADDRESS_ATTRIBUTE_ID,
                                                CLUSTER_MASK_SERVER,
                                                myGenericProtocolAddress,
                                                EMBER_AF_PLUGIN_GENERIC_TUNNEL_PROTOCOL_ADDRESS_SIZE + 1,
                                                NULL); // data type
    if (status != EMBER_ZCL_STATUS_SUCCESS) {
      emberAfGenericTunnelClusterPrintln("ERR: reading protocol address %x",
                                         status);
      return;
    }
    emberAfFillCommandGenericTunnelClusterAdvertiseProtocolAddress(myGenericProtocolAddress);
    emberAfSetEndpointsForResponse(endpoint, 0xFF);
    emberAfSendCommandBroadcast(0xFFFF);
  }
}

boolean emberAfGenericTunnelClusterMatchProtocolAddressCallback(int8u *protocolAddress)
{
  int8u i;

  emberAfGenericTunnelClusterPrint("RX: MatchProtocolAddress [");
  emberAfGenericTunnelClusterPrintBuffer(protocolAddress + 1,
                                         protocolAddress[0],
                                         FALSE);
  emberAfGenericTunnelClusterPrintln("]");

  // Starting with the length byte, make sure the incoming address matches our
  // address.  If not, send a default response.  If everything matches, send a
  // Match Protocol Address response.
  for (i = 0; i <= myGenericProtocolAddress[0]; i++) {
    if (protocolAddress[i] != myGenericProtocolAddress[i]) {
      emberAfSendDefaultResponse(emberAfCurrentCommand(),
                                 EMBER_ZCL_STATUS_NOT_FOUND);
      return TRUE;
    }
  }

  emberAfFillCommandGenericTunnelClusterMatchProtocolAddressResponse();
  emberAfSendResponse();
  return TRUE;
}

void emAfPluginGenericTunnelPrintInfo(void)
{
  emberAfGenericTunnelClusterPrintln("---- Generic Tunnel Information ----");
  emberAfGenericTunnelClusterPrint("Protocol Address: (%d): ",
                                   myGenericProtocolAddress[0]);
  emberAfGenericTunnelClusterPrintBuffer(myGenericProtocolAddress + 1,
                                         myGenericProtocolAddress[0],
                                         TRUE);
  emberAfGenericTunnelClusterPrintln("");
}

int8u *emAfPluginGenericTunnelGetProtocolAddress(int8u endpoint)
{
  return myGenericProtocolAddress;
}
