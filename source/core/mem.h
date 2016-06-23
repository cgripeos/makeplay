//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#ifndef MAKEPLAY_INC_COR_MEM_H
#define MAKEPLAY_INC_COR_MEM_H
//-----------------------------------------------------------------------------

#ifndef MAKEPLAY_INC_PROTO_H
# include "proto.h"
#endif // MAKEPLAY_INC_PROTO_H

#ifndef MAKEPLAY_INC_NONCOPYABLE_H
# include "noncopyable.h"
#endif // MAKEPLAY_INC_NONCOPYABLE_H

#include <string>

namespace makeplay {  namespace core { 

enum MemHeap
{
    MEMHEAP_MAIN,
    MEMHEAP_PROP,
    MEMHEAP_CRCTBL,
    MEMHEAP_GFX,
    MEMHEAP_AUDIO,
    MEMHEAP_USER1,
    MEMHEAP_USER2,
    MEMHEAP_USER3,
    MEMHEAP_USER4,
    MEMHEAP_USER5,
    MEMHEAP_USER6,
    MEMHEAP_USER7,
    MEMHEAP_USER8,

    MEMHEAP_MAX_COUNT
};


enum MemAllign
{
    MEMALIGN_1  =  1,
    MEMALIGN_2  =  2,
    MEMALIGN_4  =  4,
    MEMALIGN_8  =  8,
    MEMALIGN_16 = 16,
};

inline size_t pad_size(size_t _size, MemAllign _align)
{
    return ((_size + (_align - 1)) & (~((1 << (_align - 1)) - 1)));
}

void* aligned_alloc(size_t _size, MemAllign _allign);
void  aligned_free(void* _mem);

uint32_t mem_usage(MemHeap _heap);
uint32_t total_mem_usage();

MemHeap use_mem_heap(MemHeap _heap);

class ScopedHeap
{
private:
    ScopedHeap() {}
public:
    ScopedHeap(MemHeap _heap) : m_old_heap(use_mem_heap(_heap)) {}
    ~ScopedHeap() { use_mem_heap(m_old_heap); }
private:
    MemHeap m_old_heap;
};


}} // makeplay::core




// manual heap usage
#define SCOPED_MEM_HEAP(mem_heap) makeplay::core::ScopedHeap __scope_##mem_heap(makeplay::core::##mem_heap);


// class new/delete override 
#define DECL_MEM(mem_heap) \
    public: \
    inline void* operator new (size_t size)    { SCOPED_MEM_HEAP(mem_heap);  return makeplay::core::aligned_alloc(size, makeplay::core::MEMALIGN_8); } \
    inline void* operator new[](size_t size)   { SCOPED_MEM_HEAP(mem_heap);  return makeplay::core::aligned_alloc(size, makeplay::core::MEMALIGN_8); } \
    inline void  operator delete (void* ptr)   { makeplay::core::aligned_free(ptr); } \
    inline void  operator delete[] (void* ptr) { makeplay::core::aligned_free(ptr); }



//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_COR_MEM_H


