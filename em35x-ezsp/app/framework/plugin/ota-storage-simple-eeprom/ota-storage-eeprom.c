// *****************************************************************************
// * ota-storage-eeprom-driver.c
// *
// * This is an integration of the simple OTA storage driver with the low-level
// * EEPROM driver.
// * 
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include "app/framework/include/af.h"

#include "app/framework/plugin/ota-common/ota.h"
#include "app/framework/plugin/ota-storage-common/ota-storage.h"

#include "hal/micro/bootloader-eeprom.h"

#include "app/framework/util/af-eeprom.h"

//------------------------------------------------------------------------------
// Globals

#if defined EMBER_AF_PLUGIN_OTA_STORAGE_SIMPLE_EEPROM_SOC_BOOTLOADING_SUPPORT
  #define SOC_BOOTLOADING_SUPPORT
  #define SOC_BOOTLOADING_SUPPORT_TEXT "yes"
#else
  #define SOC_BOOTLOADING_SUPPORT_TEXT "no"
#endif

// I like shorter names, so redefine the App. Builder names.
#define EEPROM_START EMBER_AF_PLUGIN_OTA_STORAGE_SIMPLE_EEPROM_STORAGE_START
#define EEPROM_END   EMBER_AF_PLUGIN_OTA_STORAGE_SIMPLE_EEPROM_STORAGE_END
#define SAVE_RATE    EMBER_AF_PLUGIN_OTA_STORAGE_SIMPLE_EEPROM_DOWNLOAD_OFFSET_SAVE_RATE

// Layout of the EEPROM is dependent upon whether SOC Bootloading support is
// enabled.  When it is NOT enabled, the layout of data is pretty 
// straightforward:

// LAYOUT 1
//
// EEPROM Start                     ---------------
// Image Info Meta-data             |    Info     |
//                                  ---------------
// OTA Header (offset 0 for the     |    OTA      |
//             OTA storage module)  |   Header    |
//                                  ---------------
// Rest of OTA image                |             |
//  (upgrade image data)            |     EBL     |
//                                  |      +      |
//                                  |  Signature  |
// End of OTA image                 ---------------
//                                  |             |
// ... (unused) ...                 |             |
//                                  |             |
// EEPROM End                       ---------------


// For SOC Bootloading, we must put the EBL at the top of the EEPROM
// since existing bootloaders have no knowledge of OTA headers.

// LAYOUT 2
//
// EEPROM Start                     ---------------
// Beginning of EBL file            |             |
//  (upgrade image data)            |    EBL      |
//                                  |             |
// End of EBL data                  |             |
//                                  ---------------
// Other OTA image data             |             |
//  (e.g. signature)                |  Signature  |
//                                  |             |
// End of OTA image                 ---------------
//                                  |             |
// ... (unused) ...                 |             |
//                                  |             |
//                                  ---------------
// Image Info Meta-data             |    Info     |
//                                  ---------------
// OTA Header (offset 0 for the     |    OTA      |
//             OTA storage module)  |   Header    |
//  ...extra space...               |             |
// EEPROM End                       ---------------


// The Image Info Meta-data contains the following data:
//   Saved Download Offset for the currently downloaded file (4 bytes)
//   EBL Start offset within OTA file (4 bytes)

#define IMAGE_INFO_SIZE_AND_OTA_HEADER  100        // bytes
#if defined(SOC_BOOTLOADING_SUPPORT)
  #define IMAGE_INFO_START (EEPROM_END - IMAGE_INFO_SIZE_AND_OTA_HEADER)
#else
  #define IMAGE_INFO_START (EEPROM_START)
#endif

// The following indexes are all relative to the start of the Image Info section

// The last recorded offset we downloaded.  This may not be the same as the
// value stored in RAM by the OTA cluster itself.  This value will be
// the absolute offset of the file, regardless of the re-mapping
// this code does.  It is an offset understood by the OTA storage interfaces
// relative to the start of the OTA file.
#define SAVED_DOWNLOAD_OFFSET_INDEX 0

// The Offset within the OTA file (relative to offset 0) where the
// EBL data starts.  We assume EBL data starts right after the 1st
// tag meta-data.  However OTA headers are variable in size so we
// must keep track of how big the header is.
// This #define is actually the LOCATION where that offset is stored,
// not the actual offset.
#define EBL_START_OFFSET_INDEX      4

#define OTA_HEADER_INDEX            8

// The minimum offset we will write that determines if we store the current
// download offset persistently.  This is equal to the minimum OTA header size.
#define MINIMUM_FILE_SIZE_TO_STORE_OFFSET (OTA_MINIMUM_HEADER_LENGTH)

// Very very verbose debug printing.
//#define DEBUG_PRINT
#if defined(DEBUG_PRINT)
  #define debugPrint(...) otaPrintln(__VA_ARGS__)
  #define debugFlush()    emberAfCoreFlush()
#else
  #define debugPrint(...)
  #define debugFlush()    
#endif

// For debugging only
#define DATA_SIZE 48

//------------------------------------------------------------------------------

#if defined(DEBUG_PRINT)
  static void printImageInfoStartData(void);
  static void printDataBlock(const int8u* block);
#else
  #define printImageInfoStartData()
  #define printDataBlock(x)
#endif

//------------------------------------------------------------------------------

static int32u readInt32uFromEeprom(int32u realOffset)
{
  int8u value[4];
  emAfEepromRead(realOffset, value, 4);
  return (value[0]
          + ((int32u)value[1] << 8)
          + ((int32u)value[2] << 16)
          + ((int32u)value[3] << 24));
}

static void writeInt32uToEeprom(int32u value, int32u realOffset)
{
  int32u oldValue = readInt32uFromEeprom(realOffset);
  if (oldValue != value) {
    int8u data[4];
    data[0] = value;
    data[1] = (int8u)(value >> 8);
    data[2] = (int8u)(value >> 16);
    data[3] = (int8u)(value >> 24);

    emAfEepromWrite(realOffset, data, 4);
  }
}

static int32u getEblStartOffset(void)
{
#if defined (SOC_BOOTLOADING_SUPPORT)
  return readInt32uFromEeprom(IMAGE_INFO_START + EBL_START_OFFSET_INDEX);
#else
  return 0;
#endif
}

#if defined (SOC_BOOTLOADING_SUPPORT)
static void setEblStartOffset(int32u eblStart)
{
  debugPrint("Writing EBL start offset of 0x%4X to EEPROM offset 0x%4X",
             eblStart,
             IMAGE_INFO_START + EBL_START_OFFSET_INDEX);
  debugFlush();
  writeInt32uToEeprom(eblStart, IMAGE_INFO_START + EBL_START_OFFSET_INDEX);

  #if defined(DEBUG_PRINT)
  {
    int32u offset = getEblStartOffset();
    debugPrint("EBL Start Offset: 0x%4X", offset);
  }
  #endif
}
#endif

boolean emberAfOtaStorageDriverInitCallback(void)
{
  emAfEepromInit();
  return TRUE;
}

static boolean readWritePrimitive(boolean read,
                                  const int8u* writeData,
                                  int32u offset,
                                  int32u length,
                                  int8u* readData)
{
  int8u count = 1;
  int32u realOffset = IMAGE_INFO_START + OTA_HEADER_INDEX + offset;
  int32u eblOffset = getEblStartOffset();
  int32u realLength = length;
  int8u i;

  // Because the EEPROM code only handles the length as a 16-bit number,
  // we catch that error case.
  if (length > 65535) {
    return FALSE;
  }
 
  if (eblOffset == 0) {
    // SOC Bootloading support is assumed to be disabled
    // and we are using layout 1.  Do nothing
  } else if (offset < eblOffset) {
    // Layout 2, before the break in the OTA image, but spans the break.
    if ((offset + length) > eblOffset) {
      count = 2;
      realLength = eblOffset - offset;
    } // Else
      //   Data before the break in the OTA image, but doesn't span the break.
  } else {
    // Layout 2 starting after the break in the image
    realOffset = EEPROM_START + offset - eblOffset;
  }

  for (i = 0; i < count; i++) {
    int8u status;
    
    {
      debugPrint("%p realOffset: 0x%4X, realLength: %l", 
                 (read ? "read" : "write"),
                 realOffset, 
                 realLength);
//      printImageInfoStartData();
    }

    if (read) {
      status = emAfEepromRead(realOffset, readData, (int16u)realLength);
    } else {
      status = emAfEepromWrite(realOffset, writeData, (int16u)realLength);
    }

    if (status != EEPROM_SUCCESS) {
      return FALSE;
    }

    if (count > 1) {
      // Layout 2 only
      realOffset = EEPROM_START;
      if (read) {
        readData += realLength;
      } else {
        writeData += realLength;
      }
      realLength = length - realLength;
    }
  }
  return TRUE;
}

int32u emberAfOtaStorageDriverRetrieveLastStoredOffsetCallback(void)
{
  int32u offset = readInt32uFromEeprom(IMAGE_INFO_START
                                       + SAVED_DOWNLOAD_OFFSET_INDEX);
  if (offset == 0xFFFFFFFFL) {
    return 0;
  }
  return offset;
}

static void updateDownloadOffset(int32u offset, boolean forceWrite)
{
  int32u oldDownloadOffset = 
    emberAfOtaStorageDriverRetrieveLastStoredOffsetCallback();

  if (forceWrite
      || offset == 0
      || (offset > SAVE_RATE
          && (oldDownloadOffset + SAVE_RATE) <= offset)) {
    // The actual offset we are writing TO is the second parameter.
    // The data we are writing (first param) also happens to be an offset but
    // is not a location for the write operation in this context.
    debugPrint("Recording download offset: 0x%4X", offset);
    writeInt32uToEeprom(offset, IMAGE_INFO_START + SAVED_DOWNLOAD_OFFSET_INDEX);
    //printImageInfoStartData();
  }
}

boolean emberAfOtaStorageDriverReadCallback(int32u offset, 
                                            int32u length,
                                            int8u* returnData)
{
  return readWritePrimitive(TRUE,   // read?
                            NULL,   // writeData pointer
                            offset,
                            length,
                            returnData);
}

static boolean socBootloaderSupportWriteHandler(const int8u* dataToWrite,
                                                int32u offset, 
                                                int32u length)
{
#if defined(SOC_BOOTLOADING_SUPPORT)
  int16u headerLength;
  debugPrint("socBootloaderSupportWriteHandler()");
  if (offset == 0) {
    if (length < (HEADER_LENGTH_OFFSET + HEADER_LENGTH_FIELD_LENGTH)) {
      // The expectation is that the first write of download data has at least
      // the header length in it.  Otherwise we can't determine where the EBL
      // starting point is.
      debugPrint("Write to offset 0 is too short!  Must be at least %d bytes",
                 HEADER_LENGTH_OFFSET + HEADER_LENGTH_FIELD_LENGTH);
      return FALSE;
    }
    headerLength = ((dataToWrite[HEADER_LENGTH_OFFSET]
                     + (dataToWrite[HEADER_LENGTH_OFFSET+1] << 8))
                    + TAG_OVERHEAD); 
    setEblStartOffset(headerLength);
  }
#endif // defined(SOC_BOOTLOADING_SUPPORT)

  return TRUE;
}

boolean emberAfOtaStorageDriverWriteCallback(const int8u* dataToWrite,
                                             int32u offset, 
                                             int32u length)
{
  if (!socBootloaderSupportWriteHandler(dataToWrite,
                                        offset,
                                        length)) {
    return FALSE;
  }

  if (readWritePrimitive(FALSE,        // read?
                         dataToWrite,
                         offset,
                         length,
                         NULL)) {      // readData pointer
    updateDownloadOffset(offset, 
                         FALSE);  // force write?
    return TRUE;
  }
  return FALSE;
}

void emberAfOtaStorageDriverDownloadFinishCallback(int32u finalOffset)
{
  //  printImageInfoStartData();
  updateDownloadOffset(finalOffset, 
                       TRUE);  // force write?
  return;
}

#if defined(DEBUG_PRINT)

void emAfOtaStorageEepromPrintInfo(void)
{
  int32u downloadOffset = emberAfOtaStorageDriverRetrieveLastStoredOffsetCallback();
  int32u eblOffset = getEblStartOffset();
  int8u data[DATA_SIZE];

  otaPrintln("SOC Bootloading Support: " SOC_BOOTLOADING_SUPPORT_TEXT);
  emberAfCoreFlush();
  otaPrintln("Current Download Offset:   0x%4X", downloadOffset);

#if defined(SOC_BOOTLOADING_SUPPORT)
  emberAfCoreFlush();
  otaPrintln("EBL Start Offset:          0x%4X", eblOffset);
  emberAfCoreFlush();
#endif

  otaPrintln("EEPROM Start:              0x%4X", EEPROM_START);
  emberAfCoreFlush();
  otaPrintln("EEPROM End:                0x%4X", EEPROM_END);
  emberAfCoreFlush();
  otaPrintln("Image Info Start:          0x%4X", IMAGE_INFO_START);
  emberAfCoreFlush();
  otaPrintln("Save Rate (bytes)          0x%4X", SAVE_RATE);
  emberAfCoreFlush();
  otaPrintln("Offset of download offset  0x%4X", IMAGE_INFO_START + SAVED_DOWNLOAD_OFFSET_INDEX);
  emberAfCoreFlush();
  otaPrintln("Offset of EBL offset:      0x%4X", IMAGE_INFO_START + EBL_START_OFFSET_INDEX);
  emberAfCoreFlush();
  otaPrintln("Offset of image start:     0x%4X", IMAGE_INFO_START + OTA_HEADER_INDEX);
  emberAfCoreFlush();

  otaPrintln("\nData at EEPROM Start");
  emAfEepromRead(EEPROM_START, data, DATA_SIZE);
  emberAfPrintCert(data);  // certs are 48 bytes long
  emberAfCoreFlush();

  printImageInfoStartData();
}

static void printImageInfoStartData(void)
{
  int8u data[DATA_SIZE];
  otaPrintln("\nData at Image Info Start");
  emberAfCoreFlush();
  emAfEepromRead(IMAGE_INFO_START, data, DATA_SIZE);
  emberAfPrintCert(data);  // certs are 48 bytes long
  emberAfCoreFlush();

}

static void printDataBlock(const int8u* block)
{
  int8u i;
  for (i = 0; i < DATA_SIZE; i+= 8) {
    emberAfCoreFlush();
    otaPrintln("%X %X %X %X %X %X %X %X",
               block[i],
               block[i+1],
               block[i+2],
               block[i+3],
               block[i+4],
               block[i+5],
               block[i+6],
               block[i+7]);
    emberAfCoreFlush();
  }
}

void emAfEepromTest(void)
{
  int8u data[DATA_SIZE];
  int8u i;
  int32u addressOffset = 0;
  int8u value;
  int8u length = 4;
  
  for (i = 0; i < 2; i++) {
    int32u address = addressOffset + (i * DATA_SIZE);
    value = 0x09 + i;
    MEMSET(data, value, DATA_SIZE);
    otaPrintln("Writing value 0x%X to address 0x%4X", value, address);
    emAfEepromWrite(address, data, DATA_SIZE);
    MEMSET(data, 0, DATA_SIZE);
    emAfEepromRead(address, data, DATA_SIZE);
    printDataBlock(data);
    otaPrintln("");
    addressOffset += 240;  // this is less than the ATMEL part's page
                           // size (256) which means read/write operations
                           // will span two pages
  }

  addressOffset = 0;
  value = 0x02;
  otaPrintln("Re-writing value 0x%X of length %d to address 0x%4X",
             value,
             length,
             addressOffset);
  MEMSET(data, value, DATA_SIZE);
  emAfEepromWrite(addressOffset, data, length);
  MEMSET(data, 0, DATA_SIZE);
  emAfEepromRead(addressOffset, data, DATA_SIZE);
  printDataBlock(data);
  otaPrintln("");
  //  writeInt32uToEeprom(value, addressOffset);
}

#endif // if defined(DEBUG_PRINT)
