//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************

#ifndef MAKEPLAY_INC_MATH_BASICS_H
#define MAKEPLAY_INC_MATH_BASICS_H
//-----------------------------------------------------------------------------

#include <cfloat>
#include <math.h>

namespace makeplay { namespace math {

    static const float PI = 3.14159265359f;
    static const float PI2 = PI*2.f;

    template<class T> void swap(T& _a, T& _b)
    {
        T temp = _a;
        _a = _b; 
        _b = temp;
    }

    inline float rad_to_deg(float _rad)
    {
        return _rad * (180.f/PI);
    }

    inline float deg_to_rad(float _deg)
    {
        return _deg * (PI/180.f);
    }
       
    inline bool almost_equal(float _a, float _b, const float _kEpsilon = 0.0001f)
    {
        return abs(_a - _b) < _kEpsilon;
    }

}}// namespace makeplay::math


//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_MATH_BASICS_H



