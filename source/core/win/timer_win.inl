//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************



namespace makeplay { namespace core {

// --------------------------------------------------------------------------
// GetTimeFreq()
// --------------------------------------------------------------------------

inline __int64 GetTimeFreq()
{
    static __int64 i64CounterFreq = -1;

    if( i64CounterFreq != -1 )
        return i64CounterFreq;

    LARGE_INTEGER kCounter;
    QueryPerformanceFrequency( &kCounter );
    return i64CounterFreq = (__int64)kCounter.QuadPart;
}
 

// --------------------------------------------------------------------------
// GetTime()
// --------------------------------------------------------------------------

double Timer::time_passed()
{
    LARGE_INTEGER kCounter;
    QueryPerformanceCounter( &kCounter );
    return ((double)kCounter.QuadPart / (double)GetTimeFreq());
}

}} //  namespace makeplay::core


