//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#ifndef MAKEPLAY_INC_MT_H
#define MAKEPLAY_INC_MT_H
//-----------------------------------------------------------------------------

#ifndef MAKEPLAY_INC_PROTO_H
# include "proto.h"
#endif // MAKEPLAY_INC_PROTO_H

#ifndef MAKEPLAY_INC_NONCOPYABLE_H
# include "noncopyable.h"
#endif // MAKEPLAY_INC_NONCOPYABLE_H

#ifdef MP_WINDOWS
# include "win/mt_win.inl"
#endif // MP_WINDOWS




namespace makeplay { namespace core {


//-----------------------------------------------------------------------------
// Thread
//-----------------------------------------------------------------------------
typedef _ThreadCall         ThreadCall;
typedef _ThreadPriority     ThreadPriority;
typedef _ThreadAffinityMask ThreadAffinityMask;
typedef _ThreadId           ThreadId;

class Thread : public NonCopyable
{
public:
    Thread( ThreadCall _threadCall,
            void** _argsv,
            int _nargs,
            const char* _threadName = nullptr, // for debugging
            uint32_t _stackSize = 0,
            ThreadPriority _priority = ThreadPriority::NORMAL,
            ThreadAffinityMask _affinity = (unsigned int)(-1));

    ~Thread();

    void start();
    void join();

private:
    _Thread m_thread;
};



//-----------------------------------------------------------------------------
// CritiSection
//------------------------------------------------------------------------------
class CriticalSec : public NonCopyable
{
    friend class Conditional;
public:
    CriticalSec(size_t spinCount = 0);

    void enter();
    void exit();

private:
    _CriticalSec m_cs;
};


class ScopedCS
{
public:
    ScopedCS(CriticalSec* _cs) : m_cs(_cs) { if (_cs) _cs->enter();  }
    ~ScopedCS() { if (m_cs) m_cs->exit(); }
private:
    CriticalSec* m_cs;
};


#define SCOPED_CS(pcs) ScopedCS __xxCSLock(pcs)


//------------------------------------------------------------------------------
// Conditional
//------------------------------------------------------------------------------
class Conditional : public NonCopyable
{
public:
    Conditional(CriticalSec& _cs);

    void signal();
    void signal_all();
    void wait();

private:
    _Conditional m_cond;
    _CriticalSec* m_cs;
};


//------------------------------------------------------------------------------
// TLSValue
//------------------------------------------------------------------------------
template<class ValueType>
class TLSValue : public NonCopyable
{
public:
     TLSValue();
     TLSValue(const ValueType& default_val);
    ~TLSValue();

    inline ValueType* get();
    inline const ValueType* get() const;

private:
    // don't use!!! will lead to hard to find thread bugs!
    void operator =  (const ValueType& value);

private:
    _TLS           m_tls;
    ValueType      m_defaultValue;
};



}} //  namespace makeplay::core


#include "mt.inl"



//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_MT_H
