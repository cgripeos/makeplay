//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#ifndef MAKEPLAY_INC_PROTO_H
#define MAKEPLAY_INC_PROTO_H
//-----------------------------------------------------------------------------

#include <stdint.h>
#include "config.h"

#ifdef MP_WINDOWS
# define WIN32_LEAN_AND_MEAN
# define VC_EXTRALEAN
# include <windows.h>
#endif // MP_WINDOWS

#include <cstddef>
#include <cstdint>

namespace makeplay {
    typedef int8_t   int8;
    typedef int16_t  int16;
    typedef int32_t  int32;
    typedef int64_t  int64;
    typedef uint8_t  uint8;
    typedef uint16_t uint16;
    typedef uint32_t uint32;
    typedef uint64_t uint64;
} // namespace "makeplay"

#ifndef MAKEPLAY_INC_COR_MEM_H
#include "mem.h"
#endif // MAKEPLAY_INC_COR_MEM_H

#ifndef MAKEPLAY_INC_ERROR_H
#include "error.h"
#endif // MAKEPLAY_INC_ERROR_H

//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_PROTO_H

