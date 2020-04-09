/**
 * @file client-api.h
 * @brief API for generating command buffer.
 */

#ifndef __CLIENT_API__
#define __CLIENT_API__

/** @name Client API functions */
// @{

/** 
 * @brief Function that fills in the buffer with command.
 *
 * Fills the outgoing zcl buffer and returns the number
 * of bytes used in a buffer. The buffers used are the
 * ones that were previously set with emberAfSetExternalBuffer.
 *
 * @param frameControl byte used for frame control
 * @param clusterId cluster id of message
 * @param commandId command id of message
 * @param format String format for further arguments to the function.
 *   Format values are: 
 *     - '1' - '9' and 'A' - 'G': 1-16 byte long generic blobs
 *     - 'u': int8u
 *     - 'v': int16u
 *     - 'w': int32u
 *     - 's': pointer to int8u, first byte contains remaining length
 *     - 'S': one argument is int8u*, next argument is int8u length. 
 *            Buffer is filled with length byte first and then the rest of data.
 *     - 'b': one argument is int8u*, next argument is int8u length.
 *            Buffer is filled only with the data in pointer, 
 *            length is used, but not written as a first byte.
 */
int16u emberAfFillExternalBuffer(int8u frameControl,
                                 EmberAfClusterId clusterId,
                                 int8u commandId,
                                 PGM_P format,
                                 ...);

/** 
 * @brief Function that fills in the buffer with manufacturer-specifc command.
 *
 * Fills the outgoing zcl buffer and returns the number
 * of bytes used in a buffer. The buffers used are the
 * ones that were previously set with emberAfSetExternalBuffer.
 *
 * @param frameControl byte used for frame control
 * @param clusterId cluster id of message
 * @param manufacturerCode manufacturer code of message
 * @param commandId command id of message
 * @param format String format for further arguments to the function.
 *   Format values are: 
 *     - '1' - '9' and 'A' - 'G': 1-16 byte long generic blobs
 *     - 'u': int8u
 *     - 'v': int16u
 *     - 'w': int32u
 *     - 's': pointer to int8u, first byte contains remaining length
 *     - 'S': one argument is int8u*, next argument is int8u length. 
 *            Buffer is filled with length byte first and then the rest of data.
 *     - 'b': one argument is int8u*, next argument is int8u length.
 *            Buffer is filled only with the data in pointer, 
 *            length is used, but not written as a first byte.
 */
int16u emberAfFillExternalManufacturerSpecificBuffer(int8u frameControl,
                                                     EmberAfClusterId clusterId,
                                                     int16u manufacturerCode,
                                                     int8u commandId,
                                                     PGM_P format,
                                                     ...);

/** 
 * @brief Function  that registers the buffer to use with the fill function.
 * Registers the buffer for use with the emberAfFillExternalBuffer function.
 *
 * @param buffer Main buffer for constructing message.
 * @param bufferLen Available length of buffer.
 * @param responseLengthPtr location where length of message will be written into.
 * @param apsFramePtr location where APS frame data will be written.
 */
void emberAfSetExternalBuffer(int8u *buffer, 
                              int16u bufferLen,
                              int16u *responseLengthPtr,
                              EmberApsFrame *apsFramePtr);

/** 
 * @brief Stateless function that fills the passed buffer with command data.
 *
 * Stateless method, that fill the passed buffer.
 * This method is used internally by emberAfFillExternalBuffer, but can be used
 * for generic buffer filling.
 */
int16u emberAfFillBuffer(int8u *buffer,
                         int16u bufferLen,
                         int8u frameControl,
                         int8u commandId,
                         PGM_P format,
                         ...);

// Generated macros
#include "../gen/client-command-macro.h"

/** @} END Client API functions */

#endif // __CLIENT_API__
