// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generatePluginCallbackPrototypes()
//

/**
 * @addtogroup callback Application Framework V2 callback interface Reference
 * This header provides callback function prototypes for the Tunneling client
 * cluster application framework plugin.
 * @{
 */


/** @brief Tunnel Opened
 *
 * This function is called by the Tunneling client plugin whenever a tunnel is
 * opened.  Clients may open tunnels by sending a Request Tunnel command.
 *
 * @param tunnelId The identifier of the tunnel that has been opened.  Ver.:
 * always
 */
void emberAfPluginTunnelingClientTunnelOpenedCallback(int16u tunnelId);

/** @brief Data Received
 *
 * This function is called by the Tunneling client plugin whenever data is
 * received from a server through a tunnel.
 *
 * @param tunnelId The identifier of the tunnel through which the data was
 * received.  Ver.: always
 * @param data Buffer containing the raw octets of the data.  Ver.: always
 * @param dataLen The length in octets of the data.  Ver.: always
 */
void emberAfPluginTunnelingClientDataReceivedCallback(int16u tunnelId, 
                                                      int8u * data, 
                                                      int16u dataLen);

/** @brief Data Error
 *
 * This function is called by the Tunneling client plugin whenever a data
 * error occurs on a tunnel.  Errors occur if a device attempts to send data
 * on tunnel that is no longer active or if the tunneling does not belong to
 * the device.
 *
 * @param tunnelId The identifier of the tunnel on which this data error
 * occurred.  Ver.: always
 * @param transferDataStatus The error that occurred.  Ver.: always
 */
void emberAfPluginTunnelingClientDataErrorCallback(int16u tunnelId, 
                                                   EmberAfTunnelingTransferDataStatus transferDataStatus);



/** @} END addtogroup */
