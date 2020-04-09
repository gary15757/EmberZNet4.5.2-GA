// *****************************************************************************
// * service-discovery-host.c
// *
// * Host specific routines for performing service discovery.
// *
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include PLATFORM_HEADER     // Micro and compiler specific typedefs and macros

#include "common.h"

// ZDO - ZigBee Device Object
#include "app/util/zigbee-framework/zigbee-device-host.h"
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
  int8u inCount = 0;
  int8u outCount = 0;
  EmberAfClusterId inCluster, outCluster;

  if ( serverCluster ) {
    inCount = 1;
    inCluster = clusterId;
    outCluster = 0x0000;
  } else {
    outCount = 1;
    outCluster = clusterId;
    inCluster = 0x0000;
  }

  return ezspMatchDescriptorsRequest(target,
                                     profileId,
                                     inCount,
                                     outCount,
                                     &inCluster,
                                     &outCluster,
                                     EMBER_AF_DEFAULT_APS_OPTIONS);
}

