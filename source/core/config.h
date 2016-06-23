//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************

#ifndef MAKEPLAY_INC_CONFIG_H
#define MAKEPLAY_INC_CONFIG_H
//-----------------------------------------------------------------------------

#if defined(_MSC_VER)
    #include <SDKDDKVer.h>
    #if (_MSC_VER >= 1600)
        #define MP_WINDOWS
        #if defined(_DEBUG)
            #define MP_DEBUG
        #elif defined(_SHIP)
            #define MP_SHIP
        #else
            #define MP_RELEASE
        #endif
    #else
        #error unsupported compiler version
    #endif
#else
    #error unsupported compiler version
#endif


#if defined(MP_DEBUG)
    #define MP_USE_FAIL
    #define MP_USE_ASSERT
    #define MP_USE_WARN
    #define MP_USE_LOG
#elif defined(MP_RELEASE)
    #define MP_USE_FAIL
    #define MP_USE_ASSERT
#else defined(MP_SHIP)
    #define MP_USE_FAIL
#endif

#ifndef NULL
# define NULL nullptr
#endif // NULL


//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_CONFIG_H


