//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#ifndef MAKEPLAY_INC_SINGLETON_H
#define MAKEPLAY_INC_SINGLETON_H
//-----------------------------------------------------------------------------

#ifndef MAKEPLAY_INC_PROTO_H
# include "proto.h"
#endif // MAKEPLAY_INC_PROTO_H


namespace makeplay { namespace core {

//-----------------------------------------------------------------------------
// Singleton
//-----------------------------------------------------------------------------
template<class T>
class Singleton
{
public:
    static T *  get() { return m_singleton; } 
    static void set(T* _singleton)
    {
        if (m_singleton)
        {
            delete m_singleton;
        }
        m_singleton = _singleton;
    }

private:
    static T* m_singleton;
};

template<class T> T* Singleton<T>::m_singleton = NULL;

}} // namespace makeplay::core


//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_SINGLETON_H