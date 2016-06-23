//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************

#include "common.h"
#include "math.h"

namespace makeplay { namespace math {

    Vec3 Vec3::s_x(1.f, 0.f, 0.f);
    Vec3 Vec3::s_y(0.f, 1.f, 0.f);
    Vec3 Vec3::s_z(0.f, 0.f, 1.f);
    Vec3 Vec3::s_zero(0.f, 0.f, 0.f);
    Vec3 Vec3::s_one(1.f, 1.f, 1.f);

    Rot3 Rot3::s_id(0.f, 0.f, 0.f);

    Quat Quat::s_id(0.f, 0.f, 0.f, 1.f);
}}