//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#ifndef MAKEPLAY_INC_NONCOPYABLE_H
#define MAKEPLAY_INC_NONCOPYABLE_H
//-----------------------------------------------------------------------------

#ifndef MAKEPLAY_INC_PROTO_H
# include "proto.h"
#endif // MAKEPLAY_INC_PROTO_H

namespace makeplay { namespace core {

//-----------------------------------------------------------------------------
// NonCopyable
//-----------------------------------------------------------------------------
class NonCopyable
{
protected:
     NonCopyable() {};
    ~NonCopyable() {}

private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator= (const NonCopyable&);
};


}} // makeplay::core

//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_NONCOPYABLE_H


