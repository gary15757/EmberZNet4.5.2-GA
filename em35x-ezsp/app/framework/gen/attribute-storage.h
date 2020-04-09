// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file is generated. Please do not edit manually.
// 
// This file is generated from java code via the following methods:
// com.ember.workbench.app_configurator.generator.EmbeddedCodeGenerator.generateAttributeStorageHeader()
//

// Enclosing macro to prevent multiple inclusion
#ifndef __ATTRIBUTE_STORAGE_GEN__
#define __ATTRIBUTE_STORAGE_GEN__



// Attribute masks modify how attributes are used by the framework
// Attribute that has this mask is NOT read-only
#define ATTRIBUTE_MASK_WRITABLE (0x01)
// Attribute that has this mask is saved to a token
#define ATTRIBUTE_MASK_TOKENIZE (0x02)
// Attribute that has this mask has a min/max values
#define ATTRIBUTE_MASK_MIN_MAX (0x04)
// Manufacturer specific attribute
#define ATTRIBUTE_MASK_MANUFACTURER_SPECIFIC (0x08)
// Attribute deferred to external storage
#define ATTRIBUTE_MASK_EXTERNAL_STORAGE (0x10)
// Attribute is singleton
#define ATTRIBUTE_MASK_SINGLETON (0x20)
// Attribute is a client attribute
#define ATTRIBUTE_MASK_CLIENT (0x40)


// Cluster masks modify how clusters are used by the framework
// Does this cluster have init function?
#define CLUSTER_MASK_INIT_FUNCTION (0x01)
// Does this cluster have attribute changed function?
#define CLUSTER_MASK_ATTRIBUTE_CHANGED_FUNCTION (0x02)
// Does this cluster have default response function?
#define CLUSTER_MASK_DEFAULT_RESPONSE_FUNCTION (0x04)
// Does this cluster have message sent function?
#define CLUSTER_MASK_MESSAGE_SENT_FUNCTION (0x08)
// Does this cluster have manufacturer specific attribute changed funciton?
#define CLUSTER_MASK_MANUFACTURER_SPECIFIC_ATTRIBUTE_CHANGED_FUNCTION (0x10)
// Cluster is a server
#define CLUSTER_MASK_SERVER (0x40)
// Cluster is a client
#define CLUSTER_MASK_CLIENT (0x80)


#endif // __ATTRIBUTE_STORAGE_GEN__
