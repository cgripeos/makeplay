//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************

#ifndef MAKEPLAY_INC_MATH_SRT_H
#define MAKEPLAY_INC_MATH_SRT_H
//-----------------------------------------------------------------------------

namespace makeplay { namespace math {

    class Vec3;
    class Rot3;

    class SRT3
    {
    public:
        Vec3 s;
        Rot3 r;
        Vec3 t;

        SRT3() {}
        SRT3(Vec3 const& _s, Rot3 const& _r, Vec3 const& _t);

        Vec3 operator * (Vec3 const& _v) const;

        void invert();
        void inverse(SRT3& _inverse) const;


    };

    SRT3::SRT3(Vec3 const& _s, Rot3 const& _r, Vec3 const& _t) : s(_s), r(_r), t(_t) {}

    inline Vec3 SRT3::operator * (Vec3 const& _v) const
    {

    }

    inline void SRT3::invert()
    {

    }

    inline void SRT3::inverse(SRT3& _inverse) const
    {

    }


} }// namespace makeplay::math


//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_MATH_SRT_H



