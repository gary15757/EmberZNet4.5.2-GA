// This callback file is created for your convenience. You may add application
// code to this file. If you regenerate this file over a previous version, the
// previous version will be overwritten and any code you have added will be
// lost.

#include "app/framework/include/af.h"


/** @brief Finished
 *
 * This callback is fired when the network-find plugin is finished with the
 * forming or joining process.  The result of the operation will be returned in
 * the status parameter.
 *
 * @param status   Ver.: always
 */
void emberAfPluginNetworkFindFinishedCallback(EmberStatus status)
{
}

/** @brief Request Mirror
 *
 * This function is called by the Simple Metering client plugin whenever a
 * Request Mirror command is received.  The application should return the
 * endpoint to which the mirror has been assigned.  If no mirror could be
 * assigned, the application should return 0xFFFF.
 *
 * @param requestingDeviceIeeeAddress   Ver.: always
 */
int16u emberAfPluginSimpleMeteringClientRequestMirrorCallback(EmberEUI64 requestingDeviceIeeeAddress)
{
  return 0xFFFF;
}

/** @brief Remove Mirror
 *
 * This function is called by the Simple Metering client plugin whenever a
 * Remove Mirror command is received.  The application should return the
 * endpoint on which the mirror has been removed.  If the mirror could not be
 * removed, the application should return 0xFFFF.
 *
 * @param requestingDeviceIeeeAddress   Ver.: always
 */
int16u emberAfPluginSimpleMeteringClientRemoveMirrorCallback(EmberEUI64 requestingDeviceIeeeAddress)
{
  return 0xFFFF;
}

/** @brief Price Started
 *
 * This function is called by the Price client plugin whenever a price starts.
 *
 * @param price The price that has started.  Ver.: always
 */
void emberAfPluginPriceClientPriceStartedCallback(EmberAfPluginPriceClientPrice *price)
{
}

/** @brief Price Expired
 *
 * This function is called by the Price client plugin whenever a price expires.
 *
 * @param price The price that has expired.  Ver.: always
 */
void emberAfPluginPriceClientPriceExpiredCallback(EmberAfPluginPriceClientPrice *price)
{
}


