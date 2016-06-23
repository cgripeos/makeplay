//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************

#ifndef MAKEPLAY_INC_MATH_VEC_H
#define MAKEPLAY_INC_MATH_VEC_H
//-----------------------------------------------------------------------------

namespace makeplay { namespace math {

    class Vec3
    {
    public:
        float x, y, z;

    private:
        static Vec3 s_x;
        static Vec3 s_y;
        static Vec3 s_z;
        static Vec3 s_zero;
        static Vec3 s_one;

    public:
        Vec3() {}
        Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
        Vec3(float _v) : x(_v), y(_v), z(_v) {}

        void set(float _x, float _y, float _z);
        float operator[] (size_t _index) const;

        bool operator== (Vec3 const& _other) const;
        bool operator!= (Vec3 const& _other) const;

        Vec3 const  operator+ (Vec3 const& _other) const;
        Vec3 const  operator- (Vec3 const& _other) const;
        float const operator* (Vec3 const& _other) const;
        Vec3 const  operator* (float _scale) const;
        Vec3 const  operator/ (float _scale) const;

        void operator+= (Vec3 const& _other);
        void operator-= (Vec3 const& _other);
        void operator*= (Vec3 const& _other);
        void operator*= (float _scale);
        void operator/= (float _scale);

        void        scale(Vec3 const& _scale);
        Vec3 const  scaled(Vec3 const& _scale) const;

        float length2() const;
        float length() const;

        Vec3 normal() const;
        void normalize();

        float det(Vec3 const& _other) const;

        Vec3 cross(Vec3 const& _other) const;

        static Vec3 const& x_vec();
        static Vec3 const& y_vec();
        static Vec3 const& z_vec();
        static Vec3 const& zero_vec();
        static Vec3 const& one_vec();
    };


    // Vec3
    inline float Vec3::operator[] (size_t _index) const
    { return (&x)[_index]; }

    inline bool Vec3::operator== (Vec3 const& _other) const
    { return x == _other.x && y == _other.y && z == _other.z; }

    inline bool Vec3::operator!= (Vec3 const& _other) const
    { return x != _other.x || y != _other.y || z != _other.z; }

    inline void Vec3::set(float _x, float _y, float _z)
    { x = _x; y = _y; z = _z; }

    inline const Vec3 Vec3::operator + (Vec3 const& _other) const
    { return Vec3(x + _other.x, y + _other.y, z + _other.z); }
    
    inline const Vec3 Vec3::operator- (Vec3 const& _other) const
    { return Vec3(x - _other.x, y - _other.y, z - _other.z); }
    
    inline const float Vec3::operator* (Vec3 const& _other) const
    { return (x * _other.x) + (y * _other.y) + (z * _other.z); }

    inline const Vec3 Vec3::operator* (float _scale) const
    { return Vec3(x * _scale, y * _scale, z * _scale); }
    
    inline const Vec3 Vec3::operator/ (float _scale) const
    { return Vec3(x / _scale, y / _scale, z / _scale); }

    inline void Vec3::operator+= (Vec3 const& _other)
    { x += _other.x; y += _other.y; z += _other.z; }

    inline void Vec3::operator-= (Vec3 const& _other)
    { x -= _other.x; y -= _other.y; z -= _other.z; }
    
    inline void Vec3::operator*= (Vec3 const& _other)
    { x *= _other.x; y *= _other.y; z *= _other.z; }
    
    inline void Vec3::operator*= (float _scale)
    { x *= _scale; y *= _scale; z *= _scale; }
    
    inline void Vec3::operator/= (float _scale)
    { *this *= (1.f/_scale); }

    inline void  Vec3::scale(Vec3 const& _scale)
    { x *= _scale.x; y *= _scale.y; z *= _scale.z; }

    inline Vec3 const  Vec3::scaled(Vec3 const& _scale) const
    { return Vec3(x*_scale.x, y*_scale.y, z*_scale.z); }

    inline float Vec3::length2() const
    { return (*this * *this); }

    inline float Vec3::length() const
    { return sqrtf(length2()); }

    inline Vec3 Vec3::normal() const
    { return *this / length(); }

    inline void Vec3::normalize()
    { *this = *this / length(); }

    inline float Vec3::det(Vec3 const& _other) const
    { 
        return   ((y*_other.z) - (z*_other.y))
               - ((x*_other.z) - (z*_other.x))
               + ((x*_other.y) - (y*_other.x));
    }

    inline Vec3 Vec3::cross(Vec3 const& _other) const
    {
        return Vec3(   ((y*_other.z) - (z*_other.y))
                    , -((x*_other.z) - (z*_other.x))
                    ,  ((x*_other.y) - (y*_other.x)) );
    }

    inline Vec3 const& Vec3::x_vec() { return s_x; }
    inline Vec3 const& Vec3::y_vec() { return s_y; }
    inline Vec3 const& Vec3::z_vec() { return s_z; }
    inline Vec3 const& Vec3::zero_vec() { return s_zero; }
    inline Vec3 const& Vec3::one_vec() { return s_one; }

    inline bool almost_equal(Vec3 const& _a, Vec3 const& _b, const float _kEpsilon = 0.0001f)
    {
        return almost_equal(_a.x, _b.x, _kEpsilon) 
            && almost_equal(_a.y, _b.y, _kEpsilon) 
            && almost_equal(_a.z, _b.z, _kEpsilon);
    }



} }// namespace makeplay::math


//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_MATH_VEC_H
