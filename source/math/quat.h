//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************

#ifndef MAKEPLAY_INC_MATH_QUAT_H
#define MAKEPLAY_INC_MATH_QUAT_H
//-----------------------------------------------------------------------------

namespace makeplay { namespace math {

    class Vec3;
    class Rot3;

    class Quat
    {
    private:
        float x, y, z, w;

        static Quat s_id;
   
    public:
        enum RotType
        {
            ROT_X = 0,
            ROT_Y,
            ROT_Z,
        };

    public:
        Quat(float _x, float _y, float _z, float _w);
        Quat(float _angle, Vec3 const& _unitaxis);
        Quat(float _angle, RotType _axis);
        Quat(Rot3 const& _rot);
        Quat(Vec3 const& _from, Vec3 const& _to);

        float operator[] (size_t _index) const;

        Vec3 operator *  (Vec3 const& _v) const;
        Quat operator *  (Quat const& _other) const;
        void operator *= (Quat const& _other);

        void normalize();
        void normalized(Quat& _out) const;

        void to_rot(Rot3& _rot);
        void decompose(Rot3& _rot);

        float length2() const;
        float length() const;

        Quat conjugate() const;

        static Quat const& id();

    };

    inline Quat::Quat(float _x, float _y, float _z, float _w)
        : x(_x), y(_y), z(_z), w(_w)
    {}

    inline Quat::Quat(float _angle, Vec3 const& _unitaxis)
    {
        float s, c, angle;

        angle = (_angle * 0.5f);
        s = sinf(angle);
        c = cosf(angle);

        x = _unitaxis.x * s;
        y = _unitaxis.y * s;
        z = _unitaxis.z * s;
        w = c;
    }
    
    Quat::Quat(float _angle, RotType _axis)
    {
        float s, c, angle;
        angle = (_angle * 0.5f);
        s = sinf(angle);
        c = cosf(angle);

        switch (_axis)
        {
        case ROT_X:
            x = s; y = 0; z = 0; w = c; break;
        case ROT_Y:
            x = 0; y = s; z = 0; w = c; break;
        case ROT_Z:
            x = 0; y = 0; z = s; w = c; break;
        };
    }

    inline Quat::Quat(Vec3 const& _unitfrom, Vec3 const& _unitto)
    {
        float cosHalfAngleX2, recipCosHalfAngleX2;
        cosHalfAngleX2 = sqrtf((2.0f * (1.0f + (_unitfrom * _unitto))));
        recipCosHalfAngleX2 = (1.0f / cosHalfAngleX2);
        *this =  Quat( (cosHalfAngleX2 * 0.5f), ((_unitfrom.cross(_unitto)) * recipCosHalfAngleX2) );
    }

    inline Quat::Quat(Rot3 const& _rot)
    {

    }

    inline float Quat::operator[] (size_t _index) const
    {
        return (&x)[_index];
    }


    inline Vec3 Quat::operator *  (Vec3 const& _v) const
    {
        float tmpX, tmpY, tmpZ, tmpW;
        tmpX = (((w * _v.x) + (y * _v.z)) - (z * _v.y));
        tmpY = (((w * _v.y) + (z * _v.x)) - (x * _v.z));
        tmpZ = (((w * _v.z) + (x * _v.y)) - (y * _v.x));
        tmpW = (((x * _v.x) + (y * _v.y)) + (z * _v.z));
        return Vec3(
                ((((tmpW * x) + (tmpX * w)) - (tmpY * z)) + (tmpZ * y)),
                ((((tmpW * y) + (tmpY * w)) - (tmpZ * x)) + (tmpX * z)),
                ((((tmpW * z) + (tmpZ * w)) - (tmpX * y)) + (tmpY * x))   );
    }

    inline Quat Quat::operator *  (Quat const& _other) const
    {
        return Quat(
                ((((w * _other.x) + (x * _other.w)) + (y * _other.z)) - (z * _other.y)),
                ((((w * _other.y) + (y * _other.w)) + (z * _other.x)) - (x * _other.z)),
                ((((w * _other.z) + (z * _other.w)) + (x * _other.y)) - (y * _other.x)),
                ((((w * _other.w) - (x * _other.x)) - (y * _other.y)) - (z * _other.z))   );
    }

    inline void Quat::operator *= (Quat const& _other)
    {
        *this = *this * _other;
    }

    inline void Quat::normalize()
    {
        normalized(*this);
    }

    inline void Quat::normalized(Quat& _out) const
    {
        float lenSqr, lenInv;
        lenSqr = length2();
        lenInv = (1.0f / sqrtf(lenSqr));

        _out.x = (x * lenInv);
        _out.y = (y * lenInv);
        _out.z = (z * lenInv);
        _out.w = (w * lenInv);        
    }

    inline void Quat::to_rot(Rot3& _rot)
    {

    }

    inline void Quat::decompose(Rot3& _rot)
    {

    }

    inline float Quat::length2() const
    {
        float result;
        result = (x * x);
        result = (result + (y * y));
        result = (result + (z * z));
        result = (result + (w * w));
        return result;
    }

    inline float Quat::length() const
    {
        return sqrtf(length2());
    }

    inline Quat Quat::conjugate() const
    {
        return Quat(-x, -y, -z, w);
    }

    inline Quat const& Quat::id()
    {
        return s_id;
    }


} }// namespace makeplay::math



//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_MATH_QUAT_H



