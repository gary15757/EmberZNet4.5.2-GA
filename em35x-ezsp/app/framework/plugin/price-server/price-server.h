// *******************************************************************
// * price.h
// *
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#ifndef EMBER_AF_PLUGIN_PRICE_SERVER_PRICE_TABLE_SIZE
  #define EMBER_AF_PLUGIN_PRICE_SERVER_PRICE_TABLE_SIZE 5
#endif

#define ZCL_PRICE_CLUSTER_PRICE_ACKNOWLEDGEMENT_MASK BIT(0)

#define ZCL_PRICE_CLUSTER_START_TIME_NOW         0x00000000UL
#define ZCL_PRICE_CLUSTER_END_TIME_NEVER         0xFFFFFFFFUL
#define ZCL_PRICE_CLUSTER_DURATION_UNTIL_CHANGED 0xFFFF
#define ZCL_PRICE_CLUSTER_NUMBER_OF_EVENTS_ALL   0x00

// This struct is used to store the scheduled price. 
typedef struct {
  int32u  providerId;
  int8u   rateLabel[ZCL_PRICE_CLUSTER_MAXIMUM_RATE_LABEL_LENGTH + 1];
  int32u  issuerEventID;
  int8u   unitOfMeasure;
  int16u  currency;
  int8u   priceTrailingDigitAndTier;
  int8u   numberOfPriceTiersAndTier; // added later in errata
  int32u  startTime;
  int16u  duration; // in minutes
  int32u  price;
  int8u   priceRatio;
  int32u  generationPrice;
  int8u   generationPriceRatio;
  int32u  alternateCostDelivered;
  int8u   alternateCostUnit;
  int8u   alternateCostTrailingDigit;
  int8u   numberOfBlockThresholds;
  int8u   priceControl;
  boolean valid; // for use in the price table
} EmberAfScheduledPrice;

#define ZCL_PRICE_INVALID_INDEX 0xFF

// these are for inputting prices into a price table
void emberAfPriceClearPriceTable(void);
EmberAfScheduledPrice* emberAfPriceGetPriceTableEntry(int8u index);
void emberAfPricePrintTable(void);
EmberAfScheduledPrice* emberAfGetCurrentPrice(void);
