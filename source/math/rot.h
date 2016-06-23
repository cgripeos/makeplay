//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************

#ifndef MAKEPLAY_INC_MATH_ROT_H
#define MAKEPLAY_INC_MATH_ROT_H
//-----------------------------------------------------------------------------

namespace makeplay { namespace math {

    class Vec3;

    class Rot3
    {
    public:
        enum RotType
        {
            ROT_X = 0,
            ROT_Y,
            ROT_Z,
        };

    private:
        Vec3 m[3];

        static Rot3 s_id;

    public:
        Rot3() {}
        Rot3(float _angle, RotType _axis)  { set(_angle, _axis); }
        Rot3(float _x, float _y, float _z) { set(_x, _y, _z); }

        void set(float _rot, RotType _axis);
        void set(float _x, float _y, float _z);
        void set_lookat(Vec3 const& _forward, RotType _foraxis, Vec3 const& _up);

        // void decompose(float& _x, float& _y, float& _z);

        Vec3 const& row(size_t _row) const;
        Vec3        col(size_t _col) const;

        void transpose();
        void transposed(Rot3& _transposed) const;
        void orthonormalize(RotType _forward);
        void orthonormalized(RotType _forward, Rot3& _normalized) const;

        Vec3 operator *  (Vec3 const & _other) const;
        Rot3 operator *  (Rot3 const & _other) const;
        void operator *= (Rot3 const & _other);

        bool operator == (Rot3 const& _other) const;
        bool operator != (Rot3 const& _other) const;

        Rot3 const& id_rot();
    };


    // Rot3
    inline void Rot3::set(float _rot, RotType _axis)
    {
        float s = sinf(_rot);
        float c = cosf(_rot);

        switch (_axis)
        {
        case RotType::ROT_X:
            m[0].set(1.f, 0.f, 0.f);
            m[1].set(0.f,   c,  -s);
            m[2].set(0.f,   s,   c);
            break;
        case RotType::ROT_Y:
            m[0].set(  c, 0.f,   s);
            m[1].set(0.f, 1.f, 0.f);
            m[2].set( -s, 0.f,   c);
            break;
        case RotType::ROT_Z:
        default:
            m[0].set(  c,  -s, 0.f);
            m[1].set(  s,   c, 0.f);
            m[2].set(0.f, 0.f, 1.f);
        }
    }

    inline void Rot3::set(float _x, float _y, float _z)
    {
        *this =  Rot3(_z, ROT_Z) 
               * Rot3(_y, ROT_Y) 
               * Rot3(_x, ROT_X);
    }

    inline void Rot3::set_lookat(Vec3 const& _forward, RotType _foraxis, Vec3 const& _up)
    {
        MP_ASSERT(_forward != _up);
        MP_ASSERT(_forward.length2() > 0.f);
        MP_ASSERT(_up.length2() > 0.f);

        const size_t v0 = _foraxis;
        const size_t v1 = (v0 + 1) % 3;
        
        m[v0] = _forward;
        m[v1] = _up;
        orthonormalize(_foraxis);
    }


    inline Vec3 const& Rot3::row(size_t _row) const
    {
        MP_ASSERT(_row < 3);
        return m[_row];
    }

    inline Vec3 Rot3::col(size_t _col) const
    {
        MP_ASSERT(_col < 2);
        return Vec3(m[0][_col], m[1][_col], m[2][_col]);
    }

    inline void Rot3::transpose()
    {
        swap(m[1].x, m[0].y);
        swap(m[2].x, m[0].z);
        swap(m[2].y, m[1].z);
    }

    inline void Rot3::transposed(Rot3& _t) const
    {
        _t.m[0].x = m[0].x; 
        _t.m[0].y = m[1].x;
        _t.m[0].z = m[2].x;

        _t.m[1].x = m[0].y;
        _t.m[1].y = m[1].y;
        _t.m[1].z = m[2].y;

        _t.m[2].x = m[0].z;
        _t.m[2].y = m[1].z;
        _t.m[2].z = m[2].z;
    }

    inline void Rot3::orthonormalize(RotType _forward)
    {
        const size_t v0 = _forward;
        const size_t v1 = (v0 + 1) % 3;
        const size_t v2 = (v1 + 1) % 3;

        m[v0].normalize();
        m[v2] = m[v0].cross(m[v1]);
        m[v2].normalize();
        m[v1] = m[v2].cross(m[v0]);
        m[v1].normalize();
    }

    inline void Rot3::orthonormalized(RotType _forward, Rot3& _result) const
    {
        _result = *this;
        _result.orthonormalize(_forward);
    }

    inline Vec3 Rot3::operator *  (Vec3 const & _other) const
    {
        return Vec3(m[0] * _other, m[1] * _other, m[2] * _other);
    }

    inline Rot3 Rot3::operator *  (Rot3 const & _other) const
    {
        Rot3 r;
        Rot3 t = _other;
        t.transpose();
      
        r.m[0] = *this * t.m[0];
        r.m[1] = *this * t.m[1];
        r.m[2] = *this * t.m[2];

        return r;
    }

    inline void Rot3::operator *= (Rot3 const & _other)
    {
        Rot3 r = *this;
        Rot3 t = _other;
        t.transpose();

        m[0] = r * t.m[0];
        m[1] = r * t.m[1];
        m[2] = r * t.m[2];
    }

    inline bool Rot3::operator == (Rot3 const& _other) const
    {
        return    (m[0] == _other.m[0])
               && (m[1] == _other.m[1])
               && (m[2] == _other.m[2]);
    }

    inline bool Rot3::operator != (Rot3 const& _other) const
    {
        return    (m[0] != _other.m[0])
               || (m[1] != _other.m[1])
               || (m[2] != _other.m[2]);
    }

    inline Rot3 const& Rot3::id_rot()
    {
        return s_id;
    }


} }// namespace makeplay::math



//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_MATH_ROT_H



