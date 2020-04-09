// Copyright 2007 - 2011 by Ember Corporation. All rights reserved.
// 
// This file contains customized application tokens


// Identifier tags for tokens
#define CREATOR_HALIGHT_NODE      0x1111
#define CREATOR_HALIGHT_ENDPOINT  0x1112

// Types for the tokens
#ifdef DEFINETYPES
#endif // DEFINETYPES


// Actual token definitions
#ifdef DEFINETOKENS
DEFINE_BASIC_TOKEN(HALIGHT_NODE, int16u,  0xFFFF)
DEFINE_BASIC_TOKEN(HALIGHT_ENDPOINT, int8u,  0xFF)
#endif // DEFINETOKENS
