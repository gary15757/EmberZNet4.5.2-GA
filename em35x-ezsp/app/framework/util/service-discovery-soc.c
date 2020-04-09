// *****************************************************************************
// * service-discovery-soc.c
// *
// * SOC specific routines for performing service discovery.
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include PLATFORM_HEADER     // Micro and compiler specific typedefs and macros

// Ember stack and related utilities
#include "stack/include/ember.h"         // Main stack definitions

// ZDO - ZigBee Device Object
#include "app/util/zigbee-framework/zigbee-device-library.h"
#include "app/util/zigbee-framework/zigbee-device-common.h"

#include "print.h"
#include "service-discovery.h"

#include "attribute-storage.h"  // emberAfPrimaryProfileId()

//------------------------------------------------------------------------------

EmberStatus emAfSendMatchDescriptor(EmberNodeId target,
                                    EmberAfProfileId profileId,
                                    EmberAfClusterId clusterId,
                                    boolean serverCluster)
{
  EmberMessageBuffer clusterList;
  clusterList = emberAllocateLinkedBuffers(1);

  if ( clusterList != EMBER_NULL_MESSAGE_BUFFER ) {
    emberSetMessageBufferLength(clusterList, 2);
    emberSetLinkedBuffersByte(clusterList, 0, LOW_BYTE(clusterId));
    emberSetLinkedBuffersByte(clusterList, 1, HIGH_BYTE(clusterId));

    emberMatchDescriptorsRequest(target, 
                                 profileId,
                                 serverCluster
                                 ? clusterList
                                 : EMBER_NULL_MESSAGE_BUFFER,
                                 serverCluster
                                 ? EMBER_NULL_MESSAGE_BUFFER 
                                 : clusterList,
                                 EMBER_AF_DEFAULT_APS_OPTIONS);
    emberReleaseMessageBuffer(clusterList);
    return EMBER_SUCCESS;
  }
  return EMBER_NO_BUFFERS;
}
