//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#include "proto.h"
#include <string>
#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "error.h"
#include "mem.h"
#include "mt.h"


namespace makeplay{ namespace core {

extern void* _platform_malloc(size_t _size, size_t _alignment);
extern void  _platform_free(void* _mem);

namespace
{
    TLSValue<MemHeap> g_current_heap(MEMHEAP_MAIN);
    CriticalSec       g_mem_cs;

    //MemHeap g_current_heap = MEMHEAP_MAIN;

    struct HeapStat
    {
        uint32_t m_mem_usage;
        uint32_t m_total_allocs;
        uint32_t m_existing_allocs;

        HeapStat() : m_mem_usage(0), m_total_allocs(0), m_existing_allocs(0) {}
    };

    HeapStat g_heap_stat[MEMHEAP_MAX_COUNT];

    struct MemHead
    {
        uint64_t  size : 24;
        uint64_t  heap : 8;
        uint64_t  allignment : 8;
    };

}

void * aligned_alloc(uint32_t _size, MemAllign _allign)
{
    SCOPED_CS(&g_mem_cs);

    const size_t header_size_pad = pad_size(sizeof(MemHead), _allign);
    char* buff = (char*)(_platform_malloc(_size + header_size_pad + sizeof(MemHeap), _allign));
    MemHead* head = (MemHead*)(buff + header_size_pad);
    head->size = _size;
    head->allignment = _allign;
    head->heap = *(g_current_heap.get());

    g_heap_stat[head->heap].m_mem_usage += (uint32_t)(_size);
    ++(g_heap_stat[head->heap].m_total_allocs);
    ++(g_heap_stat[head->heap].m_existing_allocs);

    return (head + 1);
}

void   aligned_free(void* _mem)
{
    SCOPED_CS(&g_mem_cs);

    MemHead* head = (MemHead*)(ptrdiff_t(_mem) - sizeof(MemHead));
    char* mem = (char*)( ( ptrdiff_t(head) & ~(head->allignment - 1) ) );

    g_heap_stat[head->heap].m_mem_usage -= (uint32_t)(head->size);
    --(g_heap_stat[head->heap].m_existing_allocs);

    _platform_free(mem);
}

MemHeap use_mem_heap(MemHeap _heap)
{
    MemHeap old = *(g_current_heap.get());
    *(g_current_heap.get()) = _heap;
    return old;
}

uint32_t mem_usage(MemHeap heap)
{
    SCOPED_CS(&g_mem_cs);

    return g_heap_stat[heap].m_mem_usage;
}

uint32_t total_mem_usage()
{
    SCOPED_CS(&g_mem_cs);

    uint32_t use = 0;
    for (size_t i = 0; i < MEMHEAP_MAX_COUNT; ++i)
    {
        use += g_heap_stat[i].m_mem_usage;
    }

    return use;
}


} } //  namespace makeplay::core

// global untraced allocations
void* operator new (size_t size)
{ return makeplay::core::aligned_alloc(size, makeplay::core::MEMALIGN_8); }

void* operator new[](size_t size)
{ return makeplay::core::aligned_alloc(size, makeplay::core::MEMALIGN_8); }

void  operator delete (void* ptr)
{
    makeplay::core::aligned_free(ptr);
}

void  operator delete[](void* ptr)
{ makeplay::core::aligned_free(ptr); }