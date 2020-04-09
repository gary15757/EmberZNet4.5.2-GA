// *******************************************************************
// * tunneling-server.h
// *
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#define ZCL_TUNNELING_CLUSTER_INVALID_TUNNEL_ID 0xFFFF
#define CLOSE_INITIATED_BY_CLIENT TRUE
#define CLOSE_INITIATED_BY_SERVER FALSE

#ifndef EMBER_AF_PLUGIN_TUNNELING_SERVER_TUNNEL_LIMIT
#define EMBER_AF_PLUGIN_TUNNELING_SERVER_TUNNEL_LIMIT 8
#endif

/**
 * @brief Transfer data to a client through a Tunneling cluster tunnel.
 *
 * This function can be used to transfer data to a client through a tunnel. The
 * Tunneling server plugin will send the data to the endpoint on the node that
 * opened the given tunnel.
 *
 * @param tunnelId The identifier of the tunnel through which to send the data.
 * @param data Buffer containing the raw octets of the data.
 * @param dataLen The length in octets of the data.
 * @return ::EMBER_ZCL_STATUS_SUCCESS if the data was sent,
 * ::EMBER_ZCL_STATUS_FAILURE if an error occurred, or
 * ::EMBER_ZCL_STATUS_NOT_FOUND if the tunnel does not exist.
 */
EmberAfStatus emberAfPluginTunnelingServerTransferData(int16u tunnelId,
                                                       int8u *data,
                                                       int16u dataLen);
