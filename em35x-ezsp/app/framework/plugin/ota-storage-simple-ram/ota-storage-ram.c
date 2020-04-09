// *****************************************************************************
// * ota-storage-custom-sample.c
// *
// * Zigbee Over-the-air bootload cluster for upgrading firmware and 
// * downloading specific file.
// *
// * THIS IS A TEST IMPLEMENTATION.  It defines a single static, NULL, upgrade 
// * file that contains the upgrade information for a single manufacturer
// * and device ID.  The payload is a real OTA file but dummy data.
// *
// * This can serve as both the storage for the OTA client and the server.
// * The data is stored in RAM and thus is limited by the size of available
// * memory.
// * 
// * Copyright 2010 by Ember Corporation. All rights reserved.              *80*
// *****************************************************************************

#include "app/framework/include/af.h"
#include "app/framework/gen/callback.h"
#include "app/framework/plugin/ota-common/ota.h"
#include "app/framework/plugin/ota-storage-common/ota-storage.h"

#include "app/framework/util/util.h"
#include "app/framework/util/common.h"

#include "ota-static-file-data.h"

//------------------------------------------------------------------------------
// Globals

// This is used to store both the static SERVER image, and to hold
// the temporary CLIENT image being downloaded.  It can't do both at the same
// time so a client download will wipe out the server image.
static int8u storage[] = STATIC_IMAGE_DATA;

static int32u lastDownloadOffset = STATIC_IMAGE_DATA_SIZE;

//------------------------------------------------------------------------------

boolean emberAfOtaStorageDriverInitCallback(void)
{
  return TRUE;
}

boolean emberAfOtaStorageDriverReadCallback(int32u offset, 
                                            int32u length,
                                            int8u* returnData)
{
  if ((offset + length) > STATIC_IMAGE_DATA_SIZE) {
    return FALSE;
  }
  
  MEMCOPY(returnData, storage + offset, length);
  return TRUE;
}

boolean emberAfOtaStorageDriverWriteCallback(const int8u* dataToWrite,
                                             int32u offset, 
                                             int32u length)
{
  if ((offset + length) > STATIC_IMAGE_DATA_SIZE) {
    return FALSE;
  }

  MEMCOPY(storage + offset, dataToWrite, length);
  return TRUE;
}

int32u emberAfOtaStorageDriverRetrieveLastStoredOffsetCallback(void)
{
  return lastDownloadOffset;
}

void emberAfOtaStorageDriverDownloadFinishCallback(int32u finalOffset)
{
  lastDownloadOffset = finalOffset;
}
