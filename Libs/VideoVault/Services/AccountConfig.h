//
//  AcountConfig.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

// ======
// Debug output configuration options
// ======
#ifndef DEBUG_ACCOUNT_STATUS
// set to '1' to enable
#define DEBUG_ACCOUNT_STATUS 0
#endif

#if !defined(DEBUG) || DEBUG == 0
#define SMLOG(...) do {} while (0)
#elif  defined(DEBUG)
#define SMLOG(...) NSLog(__VA_ARGS__)
#endif