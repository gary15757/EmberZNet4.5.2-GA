// *******************************************************************
// * price.c
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include "../../include/af.h"
#include "../../util/common.h"
#include "price-server.h"

static EmberAfScheduledPrice priceTable[EMBER_AF_PLUGIN_PRICE_SERVER_PRICE_TABLE_SIZE];

typedef struct {
  boolean isIntraPan;
  union {
    struct {
      EmberNodeId nodeId;
      int8u       clientEndpoint;
      int8u       serverEndpoint;
    } intra;
    struct {
      EmberEUI64 eui64;
      EmberPanId panId;
    } inter;
  } pan;
  int8u  sequence;
  int8u  index;
  int32u startTime;
  int8u  numberOfEvents;
} GetScheduledPricesPartner;
static GetScheduledPricesPartner partner;

void emberAfPriceClearPriceTable(void)
{
  int8u i;
  for (i = 0; i < EMBER_AF_PLUGIN_PRICE_SERVER_PRICE_TABLE_SIZE; i++) {
    priceTable[i].valid = FALSE;
  }
}

// Returns a pointer to the price at the index or NULL if the index is invalid.
EmberAfScheduledPrice* emberAfPriceGetPriceTableEntry(int8u index)
{
  return (index < EMBER_AF_PLUGIN_PRICE_SERVER_PRICE_TABLE_SIZE
          ? &priceTable[index]
          : NULL);
}


// Returns the index in the price table of the current price.  The first price
// in the table that starts in the past and ends in the future in considered
// the current price.
int8u emberAfGetCurrentPriceIndex(void)
{
  int32u now = emberAfGetCurrentTime();
  int8u i;

  for (i = 0; i < EMBER_AF_PLUGIN_PRICE_SERVER_PRICE_TABLE_SIZE; i++) {
    if (priceTable[i].valid) {
      int32u startTime = ((priceTable[i].startTime
                           == ZCL_PRICE_CLUSTER_START_TIME_NOW)
                          ? now
                          : priceTable[i].startTime);
      int32u endTime = ((priceTable[i].duration
                         == ZCL_PRICE_CLUSTER_DURATION_UNTIL_CHANGED)
                        ? ZCL_PRICE_CLUSTER_END_TIME_NEVER
                        : startTime + priceTable[i].duration * 60);

      emberAfPriceClusterPrint("checking price %x, currTime %4x, start %4x, end %4x ",
                               i,
                               now,
                               startTime,
                               endTime);

      if (startTime <= now && now < endTime) {
        emberAfPriceClusterPrintln("valid");
        emberAfPriceClusterFlush();
        return i;
      } else {
        emberAfPriceClusterPrintln("no");
        emberAfPriceClusterFlush();
      }
    }
  }

  return ZCL_PRICE_INVALID_INDEX;
}

// Returns a pointer to the current price or NULL if there is no current price.
EmberAfScheduledPrice* emberAfGetCurrentPrice(void)
{
  return emberAfPriceGetPriceTableEntry(emberAfGetCurrentPriceIndex());
}

// Returns TRUE if the price will be current or scheduled at the given time.
static boolean priceIsCurrentOrScheduled(EmberAfScheduledPrice *price,
                                         int32u time)
{
  return (price->valid
          && (price->duration == ZCL_PRICE_CLUSTER_DURATION_UNTIL_CHANGED
              || time <= ((price->startTime == ZCL_PRICE_CLUSTER_START_TIME_NOW
                           ? emberAfGetCurrentTime()
                           : price->startTime)
                          + price->duration * 60)));
}

// Returns the number of all current or scheduled prices.
static int8u scheduledPriceCount(int32u startTime)
{
  int8u i, count = 0;
  for (i = 0; i < EMBER_AF_PLUGIN_PRICE_SERVER_PRICE_TABLE_SIZE; i++) {
    if (priceIsCurrentOrScheduled(&priceTable[i], startTime)) {
      count++;
    }
  }
  return count;
}

void emberAfPricePrintTable(void)
{
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_PRICE_CLUSTER)
  int8u i;
  int8u currPriceIndex = emberAfGetCurrentPriceIndex();

  emberAfPriceClusterFlush();
  emberAfPriceClusterPrintln("Configured Prices: (total %x, curr index %x)",
                             scheduledPriceCount(0),
                             currPriceIndex);
  emberAfPriceClusterFlush();
  emberAfPriceClusterPrintln("  Note: ALL values given in HEX\r\n");
  emberAfPriceClusterFlush();
  for (i = 0; i < EMBER_AF_PLUGIN_PRICE_SERVER_PRICE_TABLE_SIZE; i++) {
    if (!priceTable[i].valid) {
      continue;
    }

    emberAfPriceClusterPrintln("= PRICE %x =%p",
                               i,
                               (i == currPriceIndex ? " (Current Price)" : ""));
  
    emberAfPriceClusterPrint("  label: ");
    emberAfPriceClusterPrintString(priceTable[i].rateLabel);
  
    emberAfPriceClusterPrint("(%x)\r\n  uom/cur: %x/%2x"
                             "\r\n  pid/eid: %4x/%4x"
                             "\r\n  ct/st/dur: %4x/%4x/",
                             emberAfStringLength(priceTable[i].rateLabel),
                             priceTable[i].unitOfMeasure,
                             priceTable[i].currency,
                             priceTable[i].providerId,
                             priceTable[i].issuerEventID,
                             emberAfGetCurrentTime(),
                             priceTable[i].startTime);
    if (priceTable[i].duration == ZCL_PRICE_CLUSTER_DURATION_UNTIL_CHANGED) {
      emberAfPriceClusterPrint("INF");
    } else {
      emberAfPriceClusterPrint("%2x", priceTable[i].duration);
    }
    emberAfPriceClusterFlush();
    emberAfPriceClusterPrintln("\r\n  ptdt/ptrt: %x/%x"
                               "\r\n  p/pr: %4x/%x"
                               "\r\n  gp/gpr: %4x/%x"
                               "\r\n  acd/acu/actd: %4x/%x/%x",
                               priceTable[i].priceTrailingDigitAndTier,
                               priceTable[i].numberOfPriceTiersAndTier,
                               priceTable[i].price,
                               priceTable[i].priceRatio,
                               priceTable[i].generationPrice,
                               priceTable[i].generationPriceRatio,
                               priceTable[i].alternateCostDelivered,
                               priceTable[i].alternateCostUnit,
                               priceTable[i].alternateCostTrailingDigit);
    emberAfPriceClusterFlush();
    emberAfPriceClusterPrintln("  nobt: %x", priceTable[i].numberOfBlockThresholds);
    emberAfPriceClusterPrintln("  pc: %x", priceTable[i].priceControl);
    emberAfPriceClusterPrint("  price is valid from time %4x until ",
                             priceTable[i].startTime);
    if (priceTable[i].duration == ZCL_PRICE_CLUSTER_DURATION_UNTIL_CHANGED) {
      emberAfPriceClusterPrintln("eternity");
    } else {
      emberAfPriceClusterPrintln("%4x",
                                 (priceTable[i].startTime
                                  + (priceTable[i].duration * 60)));
    }
    emberAfPriceClusterFlush();
  }
#endif // defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_PRICE_CLUSTER)
}

void emberAfPriceClusterServerInitCallback(int8u endpoint)
{
  partner.index = ZCL_PRICE_INVALID_INDEX;

  // set the first entry in the price table
  priceTable[0].providerId = 0x00000001;

  // label of "Normal"
  priceTable[0].rateLabel[0] = 6;
  priceTable[0].rateLabel[1] = 'N';
  priceTable[0].rateLabel[2] = 'o';
  priceTable[0].rateLabel[3] = 'r';
  priceTable[0].rateLabel[4] = 'm';
  priceTable[0].rateLabel[5] = 'a';
  priceTable[0].rateLabel[6] = 'l';

  // first event
  priceTable[0].issuerEventID= 0x00000001;

  priceTable[0].unitOfMeasure = EMBER_ZCL_AMI_UNIT_OF_MEASURE_KILO_WATT_HOURS;

  // this is USD = US dollars
  priceTable[0].currency = 840;

  // top nibble means 2 digits to right of decimal point
  // bottom nibble the current price tier.
  // Valid values are from 1-15 (0 is not valid)
  // and correspond to the tier labels, 1-15.
  priceTable[0].priceTrailingDigitAndTier = 0x21;

  // initialize the numberOfPriceTiersAndTier
  priceTable[0].numberOfPriceTiersAndTier =
    (EMBER_AF_PLUGIN_PRICE_SERVER_PRICE_TABLE_SIZE << 4) + 0x00;

  // start time is 0, so it is always valid
  priceTable[0].startTime = 0x00000000;

  // valid for 1 hr = 60 minutes
  priceTable[0].duration = 60;

  // price is 0.09 per Kw/Hr
  // we set price as 9 and two digits to right of decimal
  priceTable[0].price = 9;

  // the next fields arent used
  priceTable[0].priceRatio = 0xFF;
  priceTable[0].generationPrice = 0xFFFFFFFFUL;
  priceTable[0].generationPriceRatio = 0xFF;
  priceTable[0].alternateCostDelivered = 0xFFFFFFFFUL;
  priceTable[0].alternateCostUnit = 0xFF;
  priceTable[0].alternateCostTrailingDigit = 0xFF;
  priceTable[0].numberOfBlockThresholds = 0xFF;
  priceTable[0].priceControl = 0x00;

  priceTable[0].valid = TRUE;
}

void emberAfPriceClusterServerTickCallback(int8u endpoint)
{
  while (partner.index < EMBER_AF_PLUGIN_PRICE_SERVER_PRICE_TABLE_SIZE) {
    EmberAfScheduledPrice *price = &priceTable[partner.index];
    partner.index++;
    if (priceIsCurrentOrScheduled(price, partner.startTime)) {
      emberAfPriceClusterPrintln("TX price at index %x", partner.index - 1);
      emberAfFillCommandPriceClusterPublishPrice(price->providerId,
                                                 price->rateLabel,
                                                 price->issuerEventID,
                                                 emberAfGetCurrentTime(),
                                                 price->unitOfMeasure,
                                                 price->currency,
                                                 price->priceTrailingDigitAndTier,
                                                 price->numberOfPriceTiersAndTier,
                                                 price->startTime,
                                                 price->duration,
                                                 price->price,
                                                 price->priceRatio,
                                                 price->generationPrice,
                                                 price->generationPriceRatio,
                                                 price->alternateCostDelivered,
                                                 price->alternateCostUnit,
                                                 price->alternateCostTrailingDigit,
                                                 price->numberOfBlockThresholds,
                                                 price->priceControl);
      // Rewrite the sequence number of the response so it matches the request.
      appResponseData[1] = partner.sequence;
      if (partner.isIntraPan) {
        emberAfGetCommandApsFrame()->sourceEndpoint      = partner.pan.intra.serverEndpoint;
        emberAfGetCommandApsFrame()->destinationEndpoint = partner.pan.intra.clientEndpoint;
        emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, partner.pan.intra.nodeId);
      } else {
        emberAfSendCommandInterPan(partner.pan.inter.panId,
                                   partner.pan.inter.eui64,
                                   EMBER_NULL_NODE_ID,
                                   0, // multicast id - unused
                                   SE_PROFILE_ID);
      }

      partner.numberOfEvents--;
      break;
    }
  }

  if (partner.numberOfEvents != 0
      && partner.index < EMBER_AF_PLUGIN_PRICE_SERVER_PRICE_TABLE_SIZE) {
    emberAfScheduleClusterTick(endpoint,
                               ZCL_PRICE_CLUSTER_ID,
                               EMBER_AF_SERVER_CLUSTER_TICK,
                               MILLISECOND_TICKS_PER_QUARTERSECOND,
                               EMBER_AF_OK_TO_HIBERNATE);
  } else {
    partner.index = ZCL_PRICE_INVALID_INDEX;
  }
}

boolean emberAfPriceClusterGetCurrentPriceCallback(int8u commandOptions)
{
  EmberAfScheduledPrice *price = emberAfGetCurrentPrice();
  emberAfPriceClusterPrintln("RX: GetCurrentPrice 0x%x", commandOptions);
  if (price == NULL) {
    emberAfPriceClusterPrintln("no valid price to return!");
    emberAfSendDefaultResponse(emberAfCurrentCommand(),
                               EMBER_ZCL_STATUS_NOT_FOUND);
  } else {
    emberAfFillCommandPriceClusterPublishPrice(price->providerId,
                                               price->rateLabel,
                                               price->issuerEventID,
                                               emberAfGetCurrentTime(),
                                               price->unitOfMeasure,
                                               price->currency,
                                               price->priceTrailingDigitAndTier,
                                               price->numberOfPriceTiersAndTier,
                                               price->startTime,
                                               price->duration,
                                               price->price,
                                               price->priceRatio,
                                               price->generationPrice,
                                               price->generationPriceRatio,
                                               price->alternateCostDelivered,
                                               price->alternateCostUnit,
                                               price->alternateCostTrailingDigit,
                                               price->numberOfBlockThresholds,
                                               price->priceControl);
    emberAfSendResponse();
  }
  return TRUE;
}

boolean emberAfPriceClusterGetScheduledPricesCallback(int32u startTime,
                                                      int8u numberOfEvents)
{
  EmberAfClusterCommand *cmd = emberAfCurrentCommand();

  emberAfPriceClusterPrintln("RX: GetScheduledPrices 0x%4x, 0x%x",
                             startTime,
                             numberOfEvents);

  // Only one GetScheduledPrices can be processed at a time.
  if (partner.index != ZCL_PRICE_INVALID_INDEX) {
    emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_FAILURE);
    return TRUE;
  }

  partner.startTime = (startTime == ZCL_PRICE_CLUSTER_START_TIME_NOW
                       ? emberAfGetCurrentTime()
                       : startTime);
  partner.numberOfEvents = (numberOfEvents == ZCL_PRICE_CLUSTER_NUMBER_OF_EVENTS_ALL
                            ? scheduledPriceCount(partner.startTime)
                            : numberOfEvents);

  if (partner.numberOfEvents == 0) {
    emberAfPriceClusterPrintln("no valid price to return!");
    emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_NOT_FOUND);
  } else {
    partner.isIntraPan = (cmd->interPanHeader == NULL);
    if (partner.isIntraPan) {
      partner.pan.intra.nodeId = cmd->source;
      partner.pan.intra.clientEndpoint = cmd->apsFrame->sourceEndpoint;
      partner.pan.intra.serverEndpoint = cmd->apsFrame->destinationEndpoint;
    } else {
      partner.pan.inter.panId = cmd->interPanHeader->panId;
      MEMCOPY(partner.pan.inter.eui64, cmd->interPanHeader->longAddress, EUI64_SIZE);
    }
    partner.sequence = cmd->seqNum;
    partner.index = 0;
    emberAfScheduleClusterTick(emberAfCurrentEndpoint(),
                               ZCL_PRICE_CLUSTER_ID,
                               EMBER_AF_SERVER_CLUSTER_TICK,
                               MILLISECOND_TICKS_PER_QUARTERSECOND,
                               EMBER_AF_OK_TO_HIBERNATE);
  }
  return TRUE;
}
