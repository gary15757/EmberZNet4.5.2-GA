// *******************************************************************
// * bacnet-protocol-tunnel.c
// *
// *
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

// this file contains all the common includes for clusters in the util
#include "../../util/common.h"

// clusters specific header
#include "bacnet-protocol-tunnel.h"

#if defined(EMBER_AF_PLUGIN_GENERIC_TUNNEL)
  #include "../generic-tunnel/generic-tunnel.h"
#endif

#ifdef ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_SERVER
// -------------------------------------------------------
// BACNET PROTOCOL TUNNEL
// -------------------------------------------------------
void sendBACnetIAmMessage(int16u destShortAddress,
                          int8u destEndpoint,
                          int8u sourceEndpoint);

boolean emberAfBacnetProtocolTunnelClusterTransferNpduCallback(int8u* npdu)
{
  int16u length, i;
  int16u startLine = 0;
  int8u finger = 0;

  emberAfBacnetProtocolTunnelClusterPrintln("RX BACnet tunnel: transfer NPDU");

  // length is one byte
  length = npdu[0];

  // error check length
  if (length > BACNET_PROTOCOL_CLUSTER_MAX_NPDU_SIZE) {
    emberAfBacnetProtocolTunnelClusterPrintln("length %2x too large, "
                                         "setting to max value of %2x",
                                         length,
                                         BACNET_PROTOCOL_CLUSTER_MAX_NPDU_SIZE);

    length = BACNET_PROTOCOL_CLUSTER_MAX_NPDU_SIZE;
  }

  emberAfBacnetProtocolTunnelClusterPrint("    length: %d payload:", 
                                         length);

  // print the NPDU
  for (i=2; i<(length+2); i++) {
    // make a new line every 8 characters
    if ((i==2) || (((i-2) % 8) == 0)) {
      emberAfBacnetProtocolTunnelClusterPrint("\r\n%d", startLine);
      if (startLine < 10) emberAfBacnetProtocolTunnelClusterPrint(" ");
      if (startLine < 100) emberAfBacnetProtocolTunnelClusterPrint(" ");
      emberAfBacnetProtocolTunnelClusterPrint(": ");
      startLine += 8;

      emberAfBacnetProtocolTunnelClusterFlush();
    }
    emberAfBacnetProtocolTunnelClusterPrint("%x ", npdu[i]);
  }
  emberAfBacnetProtocolTunnelClusterPrintln("");

  // decode the BACnet protocol
  // start after the length
  finger = 1;
  // byte 0: BACnet version, expect 1
  emberAfBacnetProtocolTunnelClusterPrintln("%x : BACnet version = %x",
                                       npdu[finger], npdu[finger]);
  // frame control, 0x20 = dnet, dlen, hop present; 0x00 = not present
  emberAfBacnetProtocolTunnelClusterPrint("%x : Frame Control = ",
                                     npdu[finger+1]);
  if (npdu[finger+1] == 0x20) {
    emberAfBacnetProtocolTunnelClusterPrintln("dnet, dlen, hop present");

    emberAfBacnetProtocolTunnelClusterPrintln("%x %x : Dnet",
                                           npdu[finger+2], npdu[finger+3]);
    emberAfBacnetProtocolTunnelClusterPrintln("%x : Dlen",
                                           npdu[finger+4]);
    emberAfBacnetProtocolTunnelClusterPrintln("%x : hop",
                                           npdu[finger+5]);
    finger += 6;
  } else if (npdu[finger+1] == 0x00) {
    emberAfBacnetProtocolTunnelClusterPrintln("no addr");
    finger += 2;
  } else {
    emberAfBacnetProtocolTunnelClusterPrintln("unknown, abort decoding");
    emberAfSendDefaultResponse(emberAfCurrentCommand(),
                               EMBER_ZCL_STATUS_FAILURE);
    return TRUE;
  }

  // PDU
  emberAfBacnetProtocolTunnelClusterPrint("%x : PDU type = ", npdu[finger]);
  if (npdu[finger] == 0x10) {
    emberAfBacnetProtocolTunnelClusterPrintln("unconfirmed service request");
    
    // service choice
    emberAfBacnetProtocolTunnelClusterPrint("%x : service choice =", 
                                           npdu[finger+1]);
    if (npdu[finger+1] == 0x8) {
      emberAfBacnetProtocolTunnelClusterPrintln("WHOIS request"); 
      sendBACnetIAmMessage(emberAfResponseDestination,
                           emberAfResponseApsFrame.sourceEndpoint,
                           emberAfResponseApsFrame.destinationEndpoint);
    }
    else if (npdu[finger+1] == 0x0) {
      emberAfBacnetProtocolTunnelClusterPrintln("IAM response"); 
    }
    else {
      emberAfBacnetProtocolTunnelClusterPrintln("unknown, abort decoding");
      emberAfSendDefaultResponse(emberAfCurrentCommand(),
                                 EMBER_ZCL_STATUS_FAILURE);
      return TRUE;
    }
  }
  else {
    emberAfBacnetProtocolTunnelClusterPrintln("unknown, abort decoding");
    emberAfSendDefaultResponse(emberAfCurrentCommand(),
                               EMBER_ZCL_STATUS_FAILURE);
    return TRUE;
  }

  emberAfSendDefaultResponse(emberAfCurrentCommand(),
                             EMBER_ZCL_STATUS_SUCCESS);
  return TRUE;
}

void sendBACnetIAmMessage(int16u destShortAddress,
                          int8u destEndpoint,
                          int8u sourceEndpoint)
{
  int8u i;
  int8u finger = 0;
  int8u* protocolAddress;

  // frame control
  appResponseData[0] = ZCL_CLUSTER_SPECIFIC_COMMAND
    | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER;
  // sequence number
  appResponseData[1] = emberAfNextSequence();
  // command
  appResponseData[2] = ZCL_TRANSFER_NPDU_COMMAND_ID;
  // length - 1 byte
  appResponseData[3] = 20;
  finger = 4;

  appResponseData[finger++]  = 0x01;
  appResponseData[finger++]  = 0x20;
  appResponseData[finger++]  = 0xFF;
  appResponseData[finger++]  = 0xFF;
  appResponseData[finger++]  = 0x00;
  appResponseData[finger++]  = 0xFF;
  appResponseData[finger++]  = 0x10;
  appResponseData[finger++]  = 0x00;

  // add in the length of the address and the address
  protocolAddress = emAfPluginGenericTunnelGetProtocolAddress(sourceEndpoint);
  for (i = 0; i <= protocolAddress[0]; i++) {
    appResponseData[finger++]  = protocolAddress[i];
  }
  appResponseData[finger++] = 0x01; // pdu size
  appResponseData[finger++] = 0xF4; // pdu size = 0x01F4 = 500
  appResponseData[finger++] = 0x22;
  appResponseData[finger++] = 0x01; // Max APDU =
  appResponseData[finger++] = 0xE0; // 480
  appResponseData[finger++] = 0x91;
  appResponseData[finger++] = 0x00; // Segmentation supported both (none = 3)
  appResponseData[finger++] = 0x21; // Vendor ID
  appResponseData[finger++] = 0xDE; // Vendor ID = 0x21DE

  // size of the message
  appResponseLength = finger;
  // setup the APS Frame
  emberAfResponseApsFrame.clusterId = ZCL_BACNET_PROTOCOL_TUNNEL_CLUSTER_ID;
  emberAfResponseApsFrame.sourceEndpoint = sourceEndpoint;
  emberAfResponseApsFrame.destinationEndpoint = destEndpoint;
  // don't change the options
  //emberAfResponseApsFrame.options = ...;

  emberAfResponseDestination = destShortAddress;
  emberAfSendResponse();
}

void bacnetProtocolTxTransferNpdu(int16u npduLength, 
                                  int8u* npdu,
                                  int16u destShortAddress,
                                  int8u destEndpoint,
                                  int8u sourceEndpoint)
{
  int8u i;

  // frame control
  appResponseData[0] = ZCL_CLUSTER_SPECIFIC_COMMAND
    | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER;
  // sequence number
  appResponseData[1] = emberAfNextSequence();
  // command
  appResponseData[2] = ZCL_TRANSFER_NPDU_COMMAND_ID;
  // length
  appResponseData[3] = LOW_BYTE(npduLength);
  appResponseData[4] = HIGH_BYTE(npduLength);
  // npdu
  for (i=0; i<npduLength; i++) {
    appResponseData[5+i] = npdu[i];
  }
  // size of the message
  appResponseLength = 5 + npduLength;
  // setup the APS Frame
  emberAfResponseApsFrame.clusterId = ZCL_BACNET_PROTOCOL_TUNNEL_CLUSTER_ID;
  emberAfResponseApsFrame.sourceEndpoint = sourceEndpoint;
  emberAfResponseApsFrame.destinationEndpoint = destEndpoint;
  // don't change the options
  //emberAfResponseApsFrame.options = ...;

  emberAfResponseDestination = destShortAddress;
  emberAfSendResponse();
}


#endif //ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_SERVER
