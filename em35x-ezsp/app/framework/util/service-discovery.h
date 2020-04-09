// *****************************************************************************
// * service-discovery.h
// *
// * Interface for initiating and processing ZDO service discovery 
// * (match descriptor) requests and response.
// *
// * Copyright 2008 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include "../include/af.h"

// Internal Functions
void emAfServiceDiscoveryComplete(void);
void emAfServiceDiscoveryMatched(EmberNodeId nodeId,
                                 int8u endpointListLength,
                                 int8u* endpointList);

// Platform specific call to send a match descriptor request.
EmberStatus emAfSendMatchDescriptor(EmberNodeId target,
                                    EmberAfProfileId profileId,
                                    EmberAfClusterId clusterId,
                                    boolean serverCluster);

boolean emAfServiceDiscoveryIncoming(EmberNodeId sender,
                                     EmberApsFrame* apsFrame,
                                     const int8u* message,
                                     int16u length);

