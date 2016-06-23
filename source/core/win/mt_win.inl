//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************

#include <process.h>

namespace makeplay { namespace core {


//-----------------------------------------------------------------------------
// _Thread
//------------------------------------------------------------------------------
typedef int(*_ThreadCall)(void** argv, size_t nArgs); 
typedef unsigned long _ThreadId;
static const _ThreadId _kImplNoThread = (_ThreadId)(-1);

enum class _ThreadPriority
{
	LOW = THREAD_PRIORITY_BELOW_NORMAL,
	NORMAL = THREAD_PRIORITY_NORMAL,
	HIGH = THREAD_PRIORITY_ABOVE_NORMAL,
	HIGHEST = THREAD_PRIORITY_HIGHEST,
};

typedef unsigned int _ThreadAffinityMask;



class _Thread
{
public:
    _Thread( _ThreadCall _threadCall,
             void** _argsv,
             int _nargs,
             const char* _threadName = nullptr, // for debugging
             uint32_t _stackSize = 0, 
             _ThreadPriority _priority = _ThreadPriority::NORMAL,
             _ThreadAffinityMask _affinity = (unsigned int)(-1) );

    ~_Thread();

    void start();
    void join();

private:
    void _set_thread_name();
    static unsigned int __stdcall _ThreadMain(void* args);


private:
    HANDLE              m_handle;
    _ThreadId           m_threadID;
    _ThreadCall         m_threadCall;
    void**              m_argsv;
    size_t              m_nargs;
    int	                m_retCode;
    std::string         m_name;
    unsigned int        m_stackSize;
    _ThreadPriority     m_priority;
    _ThreadAffinityMask m_affinity;
};

// utls
namespace __xxThread{

    typedef struct tagTHREADNAME_INFO
    {
        DWORD dwType;     // must be 0x1000
        LPCSTR szName;    // pointer to name (in user address space)
        DWORD dwThreadID; // thread ID (-1 = caller thread)
        DWORD dwFlags;    // reserved for future use, must be zero
    } THREADNAME_INFO;

}


inline unsigned int __stdcall _Thread::_ThreadMain(void* args)
{
    _Thread* desc = reinterpret_cast<_Thread*>(args);

    int ret = desc->m_threadCall(desc->m_argsv, desc->m_nargs);

    desc->m_retCode = ret;

    return ret;
}


// thread
inline _Thread::_Thread(_ThreadCall _threadCall,
                         void**		_argsv,
                         int			_nargs,
                         const char* _threadName,
                         uint32_t _stackSize,
                         _ThreadPriority _priority,
                         _ThreadAffinityMask _affinity)
    : m_handle(INVALID_HANDLE_VALUE)
    , m_threadID(0)
    , m_threadCall(_threadCall)
    , m_argsv(_argsv)
    , m_nargs(_nargs)
    , m_retCode(0)
    , m_name(_threadName)
    , m_stackSize(_stackSize)
    , m_priority(_priority)
    , m_affinity(_affinity)
{

    m_handle = (HANDLE)_beginthreadex(NULL, m_stackSize, _ThreadMain, this, CREATE_SUSPENDED, (unsigned int*)(&m_threadID));
    MP_ASSERT(m_handle != INVALID_HANDLE_VALUE);

    // the Win OS does a better job than we do at mapping thread-to-core
    // but we might want this for consoles (definitely for XB360!!)
    // ---> SetThreadAffinityMask(m_handle, m_affinity); 

    SetThreadPriority(m_handle, (LONG)m_priority);

    _set_thread_name();

}


inline _Thread::~_Thread()
{
    if (m_handle != INVALID_HANDLE_VALUE)
    {
        join(); //  hmm.. we can also manually join
    }
}


inline void _Thread::start()
{
    MP_ASSERT(m_handle != INVALID_HANDLE_VALUE);
    ResumeThread(m_handle);
}


inline void _Thread::join()
{
    MP_ASSERT(m_handle != INVALID_HANDLE_VALUE);
    WaitForSingleObject(m_handle, INFINITE);
    m_handle = INVALID_HANDLE_VALUE;
}


inline void _Thread::_set_thread_name()
{
    MP_ASSERT(m_handle != INVALID_HANDLE_VALUE);

    const DWORD MS_VC_EXCEPTION = 0x406D1388;

    __xxThread::THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = m_name.c_str();
    info.dwThreadID = (DWORD)(m_threadID);
    info.dwFlags = 0;

    __try
    {
        RaiseException(0x406D1388, 0, sizeof(info) / sizeof(DWORD), (ULONG_PTR*)&info);
    }
    __except (EXCEPTION_CONTINUE_EXECUTION)
    {
    }
}



//-----------------------------------------------------------------------------
// _CriticalSec
//------------------------------------------------------------------------------
class _CriticalSec
{
	friend class _Conditional;
public:
    _CriticalSec(size_t spinCount = 0);

    void enter();
    void exit();

private:
    CRITICAL_SECTION m_cs;
};

inline _CriticalSec::_CriticalSec(size_t spinCount)
{
    BOOL ret = InitializeCriticalSectionAndSpinCount(&m_cs, (DWORD)(spinCount));
    MP_ASSERT_MSG(ret, "failed to initialize CriticalSection object!");
}

inline void _CriticalSec::enter()
{
    EnterCriticalSection(&m_cs);
}

inline void _CriticalSec::exit()
{
    LeaveCriticalSection(&m_cs);
}




//-----------------------------------------------------------------------------
// _Conditional
//------------------------------------------------------------------------------
class _Conditional
{
public:
    _Conditional(_CriticalSec& _cs);
	
    void signal();
    void signal_all();
    void wait();

private:
    CONDITION_VARIABLE m_conditional;
    _CriticalSec* m_cs;
};

// _Conditional
inline _Conditional::_Conditional(_CriticalSec& _cs)
    : m_cs(&_cs)
{
    InitializeConditionVariable(&m_conditional);
}

inline void _Conditional::signal()
{
    WakeConditionVariable(&m_conditional);
}

inline void _Conditional::signal_all()
{
    WakeAllConditionVariable(&m_conditional);
}

inline void _Conditional::wait()
{
    SleepConditionVariableCS(&m_conditional, &(m_cs->m_cs), INFINITE);
}

//-----------------------------------------------------------------------------
// _TLS
//------------------------------------------------------------------------------

class _TLS
{
public:
     _TLS();
    ~_TLS();

    void  set(void* _value);
    void* get() const;

private:
    DWORD m_tlsKey;
};



inline _TLS::_TLS()
{
    m_tlsKey = TlsAlloc();
    MP_ASSERT_MSG(m_tlsKey != TLS_OUT_OF_INDEXES, "Failed to create key for 'Thread Local Storage' object!");
}

inline _TLS::~_TLS()
{
    TlsFree(m_tlsKey);
}


inline void _TLS::set(void* _value)
{
    BOOL ret = TlsSetValue(m_tlsKey, _value);
    MP_ASSERT_MSG(ret, "Failed to set value in 'Thread Local Storage' object!");
}

inline void* _TLS::get() const
{
    return TlsGetValue(m_tlsKey);
}

}} //  namespace makeplay::core
