//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#ifndef MAKEPLAY_INC_COR_STACKALLOC_H_
#define MAKEPLAY_INC_COR_STACKALLOC_H_
//-----------------------------------------------------------------------------

#ifndef MAKEPLAY_INC_PROTO_H
# include "proto.h"
#endif // MAKEPLAY_INC_PROTO_H


namespace makeplay { namespace core {


//-----------------------------------------------------------------------------
// FixedAllocBase
//-----------------------------------------------------------------------------
class FixedAllocBase
{
public:
    FixedAllocBase(char* _mem, size_t _size)
        : m_mem(_mem)
        , m_top(_mem)
    {
            
    }

    inline void* alloc(size_t _size, MemAllign _align)
    {
        char* p = (char*)pad_size((size_t)m_top, _align);
        m_top = p + _size;
        MP_ASSERT(m_top < m_mem + m_capacity);
        return p;
    }

    inline void  free(void* _mem) {} // do nothing

protected:
    size_t m_capacity;
    char*  m_mem;
    char*  m_top;
};


//-----------------------------------------------------------------------------
// StackAlloc
//-----------------------------------------------------------------------------
template <int CAPACITY>
class StackAlloc : public FixedAllocBase
{
public:
    StackAlloc() 
        : StackAllocBase(m_stack_mem, CAPACITY) {}
public:
    char m_stack_mem[CAPACITY];
};


class HeapStackedAlloc : public FixedAllocBase
{
public:
    HeapStackedAlloc(const size_t _capacity) 
        : FixedAllocBase(new char[_capacity], _capacity) {}
    ~HeapStackedAlloc() { delete m_mem; }
};


}} // namespace makeplay::core


//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_COR_STACKALLOC_H_

