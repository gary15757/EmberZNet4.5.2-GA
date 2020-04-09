// *******************************************************************
// * print.c
// *
// * Utilities and command line interface for printing.
// *
// * Copyright 2007 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

#include PLATFORM_HEADER
#include "stack/include/ember-types.h"

#include "hal/hal.h"
#include "app/util/serial/serial.h"
#include "app/util/serial/command-interpreter2.h"

#ifdef CONFIGURATION_HEADER
#include CONFIGURATION_HEADER
#endif

#include "print.h"

//------------------------------------------------------------------------------
// Globals


// Enable this if you want area names printed. It proved annoying
// so we're disabling it here.
//#define EMBER_AF_PRINT_AREA_NAME

#ifdef EMBER_AF_PRINT_AREA_NAME
  static void reallyPrintAreaName(int16u area);
  #define printAreaName(area) reallyPrintAreaName(area)
#else
  #define printAreaName(area)
#endif //EMBER_AF_PRINT_AREA_NAME

#ifdef EMBER_AF_PRINT_NAMES
static PGM_P areaNames[] = EMBER_AF_PRINT_NAMES;
#endif

#ifdef EMBER_AF_PRINT_BITS
static int8u enablementBytes[] = EMBER_AF_PRINT_BITS;
#endif

int16u emberAfPrintActiveArea = 0;

//------------------------------------------------------------------------------

void emberAfFlush(int16u area) 
{
  if ( emberAfPrintEnabled(area) ) {
    emberSerialWaitSend(EMBER_AF_PRINT_OUTPUT);
  }
}

static void emAfPrintBuffer(int16u area,
                            const int8u *buffer,
                            int16u bufferLen,
                            PGM_P formatString)
{
  if (emberAfPrintEnabled(area)) {
    int16u index = 0;
    for (; index < bufferLen; index++) {
      emberAfPrint(area, formatString, buffer[index]);
      if (index % 16 == 6) {
        emberAfFlush(area);
      }
    }
  }
}

void emberAfPrintBuffer(int16u area, 
                        const int8u *buffer, 
                        int16u bufferLen,
                        boolean withSpace) {
  emAfPrintBuffer(area, buffer, bufferLen, (withSpace ? "%x " : "%x"));
}

void emberAfPrintString(int16u area, const int8u *buffer) {
  emAfPrintBuffer(area, buffer + 1, emberAfStringLength(buffer), "%c");
}

// Returns true if the area print is enabled
boolean emberAfPrintEnabled(int16u area) 
{
#ifndef EMBER_AF_PRINT_BITS
  return FALSE;
#else 
  int8u index = (int8u)(area >> 8);
  if ( area == 0xFFFF ) {
    return TRUE;
  }
  if ( index >= sizeof(enablementBytes) ) {
    return FALSE;
  } else {
    int8u byte = enablementBytes[index];
    return ( ( byte & (int8u)(area & 0xFF) ) != 0x00 );
  }
#endif // EMBER_AF_PRINT_BITS
}

static void printEnable(int16u area, boolean on) 
{
#ifdef EMBER_AF_PRINT_BITS
  int8u index = (int8u)(area >> 8);
  if ( index < sizeof(enablementBytes) ) {
    if ( on ) {
      enablementBytes[index] |= (int8u)(area & 0xFF);
    } else {
      enablementBytes[index] &= ~(int8u)(area & 0xFF);
    }
  }
#endif // EMBER_AF_PRINT_BITS
}

static int16u convertUserNumberAreaToInternalArea(int16u userNumberedArea)
{
  int16u index = userNumberedArea / 8;
  index = (int16u)(index << 8 ) 
    + (int16u)( ((int16u)0x0001) << ( userNumberedArea % 8 ) );
  return index;
}

#if defined EMBER_AF_PRINT_AREA_NAME
static void reallyPrintAreaName(int16u area)
{
#ifdef EMBER_AF_PRINT_NAMES
  int8u hi,lo,count;
  int16u index;

  hi = (int8u)(area >> 8);
  lo = (int8u)(area & 0xFF);
  count = 0;
  
  if ( lo != 0 ) {
    while ( !(lo & 0x01) ) {
      lo >>= 1;
      count++;
    }
  }
  index = ((8 * hi) + count);

  if (area != 0xFFFF 
      && index < EMBER_AF_PRINT_NAME_NUMBER) {
    emberSerialPrintf(EMBER_AF_PRINT_OUTPUT, "%p:", areaNames[index]);
  }
#endif // EMBER_AF_PRINT_NAMES
}
#endif //EMBER_AF_PRINT_AREA_NAME

// Prints the trace if trace is enabled
static void emAfPrintInternalVarArg(int16u area, 
                                    boolean newLine, 
                                    PGM_P formatString, 
                                    va_list ap) {
  if ( !emberAfPrintEnabled(area) ) {
    return;
  }
  printAreaName(area);

  emberSerialPrintfVarArg(EMBER_AF_PRINT_OUTPUT, formatString, ap);

  if (newLine) {
    emberSerialPrintf(EMBER_AF_PRINT_OUTPUT, "\r\n");
  }
  emberAfPrintActiveArea = area;
}

void emberAfPrintln(int16u area, PGM_P formatString, ...) 
{
  va_list ap;
  va_start (ap, formatString);
  emAfPrintInternalVarArg(area, TRUE, formatString, ap);
  va_end(ap);
}

void emberAfPrint(int16u area, PGM_P formatString, ...) 
{
  va_list ap;
  va_start (ap, formatString);
  emAfPrintInternalVarArg(area, FALSE, formatString, ap);
  va_end(ap);
}

void emberAfPrintStatus(void)
{
#ifdef EMBER_AF_PRINT_NAMES
  int8u i;
  for (i = 0; i < EMBER_AF_PRINT_NAME_NUMBER; i++) {
    emberSerialPrintfLine(EMBER_AF_PRINT_OUTPUT, "[%d] %p : %p",
                          i,
                          areaNames[i],
                          (emberAfPrintEnabled(
                            convertUserNumberAreaToInternalArea(i)) 
                           ? "YES" 
                           : "no"));
    emberSerialWaitSend(EMBER_AF_PRINT_OUTPUT);
  }
#endif // EMBER_AF_PRINT_NAMES
}

void emberAfPrintAllOn(void)
{
#ifdef EMBER_AF_PRINT_BITS
  MEMSET(enablementBytes, 0xFF, sizeof(enablementBytes));
#endif
}

void emberAfPrintAllOff(void) 
{
#ifdef EMBER_AF_PRINT_BITS
  MEMSET(enablementBytes, 0x00, sizeof(enablementBytes));
#endif
}

// These are CLI functions where a user will supply a sequential numbered
// area; as opposed to the bitmask area number that we keep track
// of internally.

void emberAfPrintOn(int16u userArea) 
{
  printEnable(convertUserNumberAreaToInternalArea(userArea), 
              TRUE);   // enable?
}

void emberAfPrintOff(int16u userArea) 
{
  printEnable(convertUserNumberAreaToInternalArea(userArea), 
              FALSE);  // enable?
}

void emberAfPrintLittleEndianEui64(const EmberEUI64 eui64)
{
  emberAfPrint(emberAfPrintActiveArea,
               "(%c)%X%X%X%X%X%X%X%X",
               '<',
               eui64[0], 
               eui64[1], 
               eui64[2], 
               eui64[3],
               eui64[4], 
               eui64[5], 
               eui64[6], 
               eui64[7]);
}

void emberAfPrintBigEndianEui64(const EmberEUI64 eui64)
{
  emberAfPrint(emberAfPrintActiveArea,
               "(%c)%X%X%X%X%X%X%X%X",
               '>',
               eui64[7], 
               eui64[6], 
               eui64[5], 
               eui64[4],
               eui64[3], 
               eui64[2], 
               eui64[1], 
               eui64[0]);
}

void emberAfPrintZigbeeKey(const int8u *key)
{
  // Zigbee Keys are 16 bytes long
  emberAfPrint8ByteBlocks(2, key, FALSE);
}

void emberAfPrintCert(const int8u *cert)
{
  // Certificates are 48 bytes long
  emberAfPrint8ByteBlocks(6, cert, TRUE);
}

void emberAfPrintKey(boolean publicKey, const int8u *key)
{
  emberAfPrintZigbeeKey(key);
  emberAfPrintBuffer(emberAfPrintActiveArea, key + 16, 6, TRUE);
  emberAfPrintln(emberAfPrintActiveArea, (publicKey ? "%X" : ""), key[22]);
  emberAfFlush(emberAfPrintActiveArea);
}

void emberAfPrintIeeeLine(const EmberEUI64 ieee)
{
  emberAfPrintBigEndianEui64(ieee);
  emberAfPrintln(emberAfPrintActiveArea, "");
}

void emberAfPrintTextLine(PGM_P text)
{
  emberAfPrintln(emberAfPrintActiveArea, "%p", text);
}

void emberAfPrint8ByteBlocks(int8u numBlocks,
                             const int8u *block,
                             boolean crBetweenBlocks)
{
  int8u i;
  for (i = 0; i < numBlocks; i++) {
    emberAfPrintBuffer(emberAfPrintActiveArea, block + 8 * i, 8, TRUE);
    // By moving the '%p' to a separate function call, we can
    // save CONST space.  The above string is duplicated elsewhere in the
    // code and therefore will be deadstripped.
    emberAfPrint(emberAfPrintActiveArea,
                 " %p",
                 (crBetweenBlocks || ((i + 1) == numBlocks) ? "\r\n" : ""));
    emberAfFlush(emberAfPrintActiveArea);
  }
}

void emberAfPrintIssuer(const int8u* issuer)
{
  // The issuer field in the certificate is in big-endian form.
  emberAfPrint(emberAfPrintActiveArea, "(>) ");
  emberAfPrint8ByteBlocks(1, issuer, TRUE);
}
