//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************



namespace makeplay { namespace core {


//-----------------------------------------------------------------------------
// Thread
//------------------------------------------------------------------------------
inline Thread::Thread(ThreadCall _threadCall,
    void** _argsv,
    int _nargs,
    const char* _threadName,
    uint32_t _stackSize,
    ThreadPriority _priority,
    ThreadAffinityMask _affinity)
    : m_thread(_threadCall, _argsv, _nargs, _threadName, _stackSize, _priority, _affinity)
{
}

inline void Thread::start()
{
    m_thread.start();
}

inline void Thread::join()
{
    m_thread.join();
}



//-----------------------------------------------------------------------------
// CritiSection
//------------------------------------------------------------------------------
inline CriticalSec::CriticalSec(size_t _spinCount)
    : m_cs(_spinCount)
{
}

inline void CriticalSec::enter()
{
    m_cs.enter();
}

inline void CriticalSec::exit()
{
    m_cs.exit();
}


//------------------------------------------------------------------------------
// Conditional
//------------------------------------------------------------------------------
inline Conditional::Conditional(CriticalSec&_cs)
    : m_cond(_cs.m_cs)
    , m_cs(&_cs.m_cs)
{
}

inline void Conditional::signal()
{
    m_cond.signal();
}

inline void Conditional::signal_all()
{
    m_cond.signal_all();
}

inline void Conditional::wait()
{
    m_cond.wait();
}



//------------------------------------------------------------------------------
// TLSValue
//------------------------------------------------------------------------------
template<class ValueType>
inline TLSValue<ValueType>::TLSValue()
    : m_tls(), m_defaultValue()
{ }

template<class ValueType>
inline TLSValue<ValueType>::TLSValue(const ValueType& _default_val)
    : m_tls(), m_defaultValue(_default_val)
{ }

template<class ValueType>
inline TLSValue<ValueType>::~TLSValue()
{
    // no point in doing this, we have to do it for all threads. 
//    ValueType* value = reinterpret_cast<ValueType*>(get());
//    if (value)
//        delete value;
}

template<class ValueType>
inline ValueType* TLSValue<ValueType>::get()
{
    ValueType* value = reinterpret_cast<ValueType*>(m_tls.get());
    if (value)
        return value;

    value = new ValueType(m_defaultValue);
    m_tls.set(value);

    return value;
}

template <class ValueType>
inline const ValueType* TLSValue<ValueType>::get() const
{
    ValueType* value = reinterpret_cast<ValueType*>(m_tls.get());
    MP_ASSERT(value);
    return value;
}

template <class ValueType>
inline void TLSValue<ValueType>::operator =  (const ValueType& value)
{
    MP_ASSERT_MSG(false, "don't use!!! will lead to hard to find thread bugs!");
    get() = value;
}



}} //  namespace makeplay::core

