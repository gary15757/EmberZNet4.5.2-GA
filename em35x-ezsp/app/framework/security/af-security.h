// *******************************************************************
// * af-security.h
// *
// * Header file for App. Framework security code 
// *
// * Copyright 2009 by Ember Corporation. All rights reserved.              *80*
// *******************************************************************

void getLinkKeyFromCli(EmberKeyData* returnData);
void getNetworkKeyFromCli(EmberKeyData* returnData);
void printSecurityProfile(void);

#if EMBER_AF_SECURITY_PROFILE == NONE_SECURITY_PROFILE
  // For no security, simply #define the security init routines to no-ops.

  #define ZA_SECURITY_PRECONFIGURED_KEY DUMMY_KEY

  #if !defined USE_REAL_SECURITY_PROTOTYPES
    #define zaNodeSecurityInit()
    #define zaTrustCenterSecurityInit()
    #define zaTrustCenterTick()
    #define zaTrustCenterStartNetworkKeySwitch()
    #define zaTrustCenterSetJoinPolicy(policy)
    #define zaTrustCenterSecurityPolicyInit()
  #endif

#else // All other security profiles.
  EmberStatus zaNodeSecurityInit(void);
  EmberStatus zaTrustCenterSecurityInit(void);
  void zaTrustCenterTick(void);
  #define ZA_TRUST_CENTER_TICK zaTrustCenterTick
  EmberStatus zaTrustCenterStartNetworkKeySwitch(void);
  EmberStatus zaTrustCenterSetJoinPolicy(EmberJoinDecision decision);
  EmberStatus zaTrustCenterSecurityPolicyInit(void);
#endif

