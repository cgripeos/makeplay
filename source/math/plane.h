//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************

#ifndef MAKEPLAY_INC_MATH_PLANE_H
#define MAKEPLAY_INC_MATH_PLANE_H
//-----------------------------------------------------------------------------

namespace makeplay { namespace math {

    template<class TVec>
    class TPlane
    {
        typedef TVec Vec;
        Vec    n;
        float  d;

        TPlane() {}
        TPlane(Vec const& _n, float _d);
        TPlane(Vec const& _a, Vec const& _b, Vec const& _c);

        bool operator <  (Vec const& _p) const;
        bool operator >  (Vec const& _p) const;
        bool operator <= (Vec const& _p) const;
        bool operator >= (Vec const& _p) const;

        float intersect(Vec const& _a, Vec const& _b) const;
        Vec   project(Vec const& _a) const;
    };

    typedef TPlane<Vec3> Plane;


    // implentation
    template<class TVec>
    TPlane<TVec>::TPlane(TVec const& _n, float _d)
    : n(_n), d(_d) {}

    template<class TVec>
    TPlane<TVec>::TPlane(TVec const& _a, TVec const& _b, TVec const& _c)
    {
        n = (_c - _a).cross(_b - _a);
        n.normalize();
        d = n * _a;
    }

    template<class TVec>
    inline bool TPlane<TVec>::operator < (TVec const& _p) const
    {
        return ((n * _p) - d) < 0.f;
    }

    template<class TVec>
    inline bool TPlane<TVec>::operator > (TVec const& _p) const
    {
        return ((n * _p) - d) > 0.f;
    }

    template<class TVec>
    inline bool TPlane<TVec>::operator <= (TVec const& _p) const
    {
        return !(*this > _p);
    }

    template<class TVec>
    inline bool TPlane<TVec>::operator >= (TVec const& _p) const
    {
        return !(*this < _p);
    }

    template<class TVec>
    float TPlane<TVec>::intersect(Vec const& _a, Vec const& _b) const
    {
        return ((n * _a) - d) / (n * (_a - _b));
    }

    template<class TVec>
    TVec TPlane<TVec>::project(Vec const& _a) const
    {
        return _a - (-((n * _a) - d) * n);
    }


}}// namespace makeplay::math


//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_MATH_PLANE_H



