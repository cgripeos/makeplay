//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#include "..\proto.h"
#include "..\mem.h"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>

namespace makeplay { namespace core {

extern void*  _platform_malloc(size_t _size, size_t _alignment)
{
    return _aligned_malloc(_size, _alignment);
}

extern void _platform_free(void* _mem)
{
    _aligned_free(_mem);
}

}} // namespace makeplay::core

