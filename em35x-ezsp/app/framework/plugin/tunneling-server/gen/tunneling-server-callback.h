// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generatePluginCallbackPrototypes()
//

/**
 * @addtogroup callback Application Framework V2 callback interface Reference
 * This header provides callback function prototypes for the Tunneling server
 * cluster application framework plugin.
 * @{
 */


/** @brief Is Protocol Supported
 *
 * This function is called by the Tunneling server plugin whenever a Request
 * Tunnel command is received.  The application should return TRUE if the
 * protocol is supported and FALSE otherwise.
 *
 * @param protocolId The identifier of the metering communication protocol for
 * which the tunnel is requested.  Ver.: always
 * @param manufacturerCode The manufacturer code for manufacturer-defined
 * protocols or 0xFFFF in unused.  Ver.: always
 */
boolean emberAfPluginTunnelingServerIsProtocolSupportedCallback(int8u protocolId, 
                                                                int16u manufacturerCode);

/** @brief Tunnel Opened
 *
 * This function is called by the Tunneling server plugin whenever a tunnel is
 * opened.  Clients may open tunnels by sending a Request Tunnel command.
 *
 * @param tunnelId The identifier of the tunnel that has been opened.  Ver.:
 * always
 * @param protocolId The identifier of the metering communication protocol for
 * the tunnel.  Ver.: always
 * @param manufacturerCode The manufacturer code for manufacturer-defined
 * protocols or 0xFFFF in unused.  Ver.: always
 */
void emberAfPluginTunnelingServerTunnelOpenedCallback(int16u tunnelId, 
                                                      int8u protocolId, 
                                                      int16u manufacturerCode);

/** @brief Data Received
 *
 * This function is called by the Tunneling server plugin whenever data is
 * received from a client through a tunnel.
 *
 * @param tunnelId The identifier of the tunnel through which the data was
 * received.  Ver.: always
 * @param data Buffer containing the raw octets of the data.  Ver.: always
 * @param dataLen The length in octets of the data.  Ver.: always
 */
void emberAfPluginTunnelingServerDataReceivedCallback(int16u tunnelId, 
                                                      int8u * data, 
                                                      int16u dataLen);

/** @brief Data Error
 *
 * This function is called by the Tunneling server plugin whenever a data
 * error occurs on a tunnel.  Errors occur if a device attempts to send data
 * on tunnel that is no longer active or if the tunneling does not belong to
 * the device.
 *
 * @param tunnelId The identifier of the tunnel on which this data error
 * occurred.  Ver.: always
 * @param transferDataStatus The error that occurred.  Ver.: always
 */
void emberAfPluginTunnelingServerDataErrorCallback(int16u tunnelId, 
                                                   EmberAfTunnelingTransferDataStatus transferDataStatus);

/** @brief Tunnel Closed
 *
 * This function is called by the Tunneling server plugin whenever a tunnel is
 * closed.  Clients may close tunnels by sending a Close Tunnel command.  The
 * server can preemptively close inactive tunnels after a timeout.
 *
 * @param tunnelId The identifier of the tunnel that has been closed.  Ver.:
 * always
 * @param clientInitiated TRUE if the client initiated the closing of the
 * tunnel or FALSE if the server closed the tunnel due to inactivity.  Ver.:
 * always
 */
void emberAfPluginTunnelingServerTunnelClosedCallback(int16u tunnelId, 
                                                      boolean clientInitiated);



/** @} END addtogroup */
