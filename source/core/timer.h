//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#ifndef MAKEPLAY_INC_TIMER_H
#define MAKEPLAY_INC_TIMER_H
//-----------------------------------------------------------------------------

#ifndef MAKEPLAY_INC_PROTO_H
# include "proto.h"
#endif // MAKEPLAY_INC_PROTO_H

namespace makeplay { namespace core {

//-----------------------------------------------------------------------------
// Timer
//-----------------------------------------------------------------------------
class Timer
{
public:
    Timer() { reset(); m_bPause = true; }

    float delta_time();
    void  pause( bool bPause )   { m_bPause = bPause; }
    void  reset()                { m_LastTime = time_passed(); }

    static double time_passed();

protected:
    double	m_LastTime;
    bool	m_bPause;
};



inline float Timer::delta_time() 
{ 
    if (m_bPause)
    {
        m_LastTime = time_passed();
        return 0.f;
    }

    double time = time_passed();
    double deltatime = time - m_LastTime;
    m_LastTime = time;
    return (float)deltatime;
}



}} // namespace makeplay::core


#ifdef MP_WINDOWS
# include "win/timer_win.inl"
#endif // MP_WINDOWS


//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_TIMER_H

