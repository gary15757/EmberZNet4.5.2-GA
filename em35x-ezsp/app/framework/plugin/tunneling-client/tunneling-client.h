// *******************************************************************
// * tunneling-client.h
// *
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#ifndef EMBER_AF_PLUGIN_TUNNELING_CLIENT_TUNNEL_LIMIT
#define EMBER_AF_PLUGIN_TUNNELING_CLIENT_TUNNEL_LIMIT 8
#endif

/**
 * @brief Transfer data to a server through a Tunneling cluster tunnel.
 *
 * This function can be used to transfer data to a server through a tunnel. The
 * Tunneling client plugin will send the data to the endpoint on the node that
 * is managing the given tunnel.
 *
 * @param tunnelId The identifier of the tunnel through which to send the data.
 * @param data Buffer containing the raw octets of the data.
 * @param dataLen The length in octets of the data.
 * @return ::EMBER_ZCL_STATUS_SUCCESS if the data was sent,
 * ::EMBER_ZCL_STATUS_FAILURE if an error occurred, or
 * ::EMBER_ZCL_STATUS_NOT_FOUND if the tunnel does not exist.
 */
EmberAfStatus emberAfPluginTunnelingClientTransferData(int16u tunnelId,
                                                       int8u *data,
                                                       int16u dataLen);

/**
 * @brief Close a Tunneling cluster tunnel.
 *
 * This function can be used to close a tunnel.  The Tunneling client plugin
 * will send the close command to the endpoint on the node that is managing the
 * given tunnel.
 *
 * @param tunnelId The identifier of the tunnel to close.
 * @return ::EMBER_ZCL_STATUS_SUCCESS if the close request was sent,
 * ::EMBER_ZCL_STATUS_FAILURE if an error occurred, or
 * ::EMBER_ZCL_STATUS_NOT_FOUND if the tunnel does not exist.
 */
EmberAfStatus emberAfPluginTunnelingClientCloseTunnel(int16u tunnelId);
