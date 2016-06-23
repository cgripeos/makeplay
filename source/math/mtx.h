//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************

#ifndef MAKEPLAY_INC_MATH_MTX_H
#define MAKEPLAY_INC_MATH_MTX_H
//-----------------------------------------------------------------------------

namespace makeplay { namespace math {

class SRT3;

class Mtx44
{
public:
    Vec3 m[4];

    Mtx44() {}
    Mtx44(Vec3 const& _row1, Vec3 const& _row2, Vec3 const& _row3);
    Mtx44(Vec3 const& _scale, Rot3 const& _rot, Vec3 const& _translation);

    Mtx44 operator *  (Mtx44 const& _other) const;
    void  operator *= (Mtx44 const& _other);
    Mtx44 operator *  (SRT3 const& _other) const;
    void  operator *= (SRT3 const& _other);
    Vec3  operator *  (Vec3 const& _v) const;
};



} }// namespace makeplay::math



//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_MATH_MTX_H



