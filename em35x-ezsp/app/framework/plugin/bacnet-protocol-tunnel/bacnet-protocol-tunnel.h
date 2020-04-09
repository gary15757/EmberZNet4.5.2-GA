// *******************************************************************
// * bacnet-protocol-tunnel.h
// *
// *
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// can be called to generate a "Transfer NPDU" command
void bacnetProtocolTxTransferNpdu(int16u npduLength, 
                                  int8u* npdu,
                                  int16u destShortAddress,
                                  int8u destEndpoint,
                                  int8u sourceEndpoint);

#define BACNET_PROTOCOL_CLUSTER_MAX_NPDU_SIZE 504

