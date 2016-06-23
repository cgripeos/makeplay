//*****************************************************************************
// Copyright 2012 - 2014 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************

#define CATCH_CONFIG_MAIN
#include "core/catch.hpp"

#include "core/proto.h"
#include "core/error.h"
#include "math/math.h"

using namespace redrock;


TEST_CASE("stupid/1=2", "Prove that one equals 2")
{
    int one = 1;
    REQUIRE(one == 1);
}

TEST_CASE("Vec2a", "test construction")
{
    math::Vec2 a(0, 0);
    math::Vec2 b(2, 2);

    REQUIRE(a.x == 0.f);
    REQUIRE(a.y == 0.f);

    REQUIRE(b.x == 2.f);
    REQUIRE(b.y == 2.f);

    math::Vec2 c(b);

    REQUIRE(c.x == 2.f);
    REQUIRE(c.y == 2.f);

}

TEST_CASE("Vec2b", "test math operators")
{
    math::Vec2 a(0, 0);
    math::Vec2 b(2, 2);

    math::Vec2 c(5, 5);
    c += b;
    REQUIRE(c.x == 7.f);
    REQUIRE(c.y == 7.f);

    c.set(0, 1);
    c -= b;
    REQUIRE(c.x == -2.f);
    REQUIRE(c.y == -1.f);

    c.set(3, 4);
    c *= 2;
    REQUIRE(c.x == 6.f);
    REQUIRE(c.y == 8.f);

    c.set(6, 8);
    c /= 2.f;
    REQUIRE(c.x == 3.f);
    REQUIRE(c.y == 4.f);

    c.set(1, 3);
    float d = c * b;
    REQUIRE(d == 8.f);

    c.set(10, 0);
    c.normalize();
    REQUIRE(c.x == 1.f);
    REQUIRE(c.y == 0.f);

    c.set(10, 0);
    b = c.normal();
    REQUIRE(b.x == 1.f);
    REQUIRE(b.y == 0.f);

    a.set(1, 0);
    b.set(0, 1);
    d = a.det(b);
    REQUIRE(d == 1);

}

TEST_CASE("Vec3a", "test construction")
{
    math::Vec3 a(0, 0, 0);
    math::Vec3 b(2, 2, 2);

    REQUIRE(a.x == 0.f);
    REQUIRE(a.y == 0.f);
    REQUIRE(a.z == 0.f);

    REQUIRE(b.x == 2.f);
    REQUIRE(b.y == 2.f);
    REQUIRE(b.z == 2.f);

    math::Vec3 c(b);

    REQUIRE(c.x == 2.f);
    REQUIRE(c.y == 2.f);
    REQUIRE(c.z == 2.f);
}

TEST_CASE("Vec3b", "test math operators")
{
    math::Vec3 a(0, 0, 0);
    math::Vec3 b(2, 2, 2);

    math::Vec3 c(5, 5, 5);
    c += b;
    REQUIRE(c.x == 7.f);
    REQUIRE(c.y == 7.f);
    REQUIRE(c.z == 7.f);

    c.set(0, 1, 2);
    c -= b;
    REQUIRE(c.x == -2.f);
    REQUIRE(c.y == -1.f);
    REQUIRE(c.z ==  0.f);

    c.set(3, 4, 5);
    c *= 2;
    REQUIRE(c.x == 6.f);
    REQUIRE(c.y == 8.f);
    REQUIRE(c.z == 10.f);

    c.set(6, 8, 10);
    c /= 2.f;
    REQUIRE(c.x == 3.f);
    REQUIRE(c.y == 4.f);
    REQUIRE(c.z == 5.f);

    c.set(1, 3, 5);
    float d = c * b;
    REQUIRE(d == 18.f);

    c.set(10, 0, 0);
    c.normalize();
    REQUIRE(c.x == 1.f);
    REQUIRE(c.y == 0.f);
    REQUIRE(c.z == 0.f);

    c.set(10, 0, 0);
    b = c.normal();
    REQUIRE(b.x == 1.f);
    REQUIRE(b.y == 0.f);
    REQUIRE(b.z == 0.f);

    a.set(1, 0, 0);
    b.set(0, 1, 0);
    d = a.det(b);
    REQUIRE(d == 1);
}

TEST_CASE("Rot2a", "test construction")
{
    const math::Vec2 x(1, 0);
    const math::Vec2 y(0, 1);
    const math::Vec2 nx(-1,  0);
    const math::Vec2 ny( 0, -1);

    math::Rot2 a(math::deg_to_rad(0.f));
    REQUIRE(x == a.row(0));
    REQUIRE(y == a.row(1));

    a.set(math::deg_to_rad(90.f));
    REQUIRE(almost_equal(a.row(0), ny));
    REQUIRE(almost_equal(a.row(1), x));

    a.set(math::deg_to_rad(180.f));
    REQUIRE(almost_equal(a.row(0), nx));
    REQUIRE(almost_equal(a.row(1), ny));

    a.set(math::deg_to_rad(270.f));
    REQUIRE(almost_equal(a.row(0), y));
    REQUIRE(almost_equal(a.row(1), nx));

    math::Rot2 b;
    b = a;
    b.transpose();
    REQUIRE(b.row(0).x == a.row(0).x);
    REQUIRE(b.row(1).y == a.row(1).y);
    REQUIRE(b.row(1).x == a.row(0).y);
    REQUIRE(b.row(0).y == a.row(1).x);
}

TEST_CASE("Rot2b", "test math operators")
{
    const math::Vec2 x(1, 0);
    const math::Vec2 y(0, 1);
    const math::Vec2 nx(-1, 0);
    const math::Vec2 ny(0, -1);

    math::Vec2 va, vb;
    math::Rot2 ra, rb, rc;

    va.set(1, 0);
    ra.set(0.f);

    vb = ra * va;
    REQUIRE(almost_equal(va, vb));

    ra.set(math::deg_to_rad(90.f));
    vb = ra * va;
    REQUIRE(almost_equal(vb, y));

    ra.set(math::deg_to_rad(180.f));
    vb = ra * va;
    REQUIRE(almost_equal(vb, nx));

    ra.set(math::deg_to_rad(270.f));
    vb = ra * va;
    REQUIRE(almost_equal(vb, ny));

    ra.set(math::deg_to_rad(360.f));
    vb = ra * va;
    REQUIRE(almost_equal(vb, x));

    ra.set(math::deg_to_rad(90));
    rb.set(math::deg_to_rad(90));

    rc = ra * rb;
    REQUIRE(math::almost_equal(rc.row(0), nx));
    REQUIRE(math::almost_equal(rc.row(1), ny));

    rc = ra;
    rc *= rb;
    REQUIRE(math::almost_equal(rc.row(0), nx));
    REQUIRE(math::almost_equal(rc.row(1), ny));

    ra.set(math::deg_to_rad(-130.f));
    float angle = math::rad_to_deg( ra.decompose() );
    REQUIRE(math::almost_equal(angle, -130.f));

}

TEST_CASE("Rot3a", "test construction")
{
    const math::Vec3 x(1, 0, 0);
    const math::Vec3 y(0, 1, 0);
    const math::Vec3 z(0, 0, 1);
    const math::Vec3 nx(-1,  0,  0);
    const math::Vec3 ny( 0, -1,  0);
    const math::Vec3 nz( 0,  0, -1);

    math::Rot3 a(0.f, 0.f, 0.f);
    REQUIRE(x == a.row(0));
    REQUIRE(y == a.row(1));
    REQUIRE(z == a.row(2));

    // x rotations
    a.set(math::deg_to_rad(90.f), math::Rot3::ROT_X);
    REQUIRE(almost_equal(a.row(0), x));
    REQUIRE(almost_equal(a.row(1), nz));
    REQUIRE(almost_equal(a.row(2), y));

    a.set(math::deg_to_rad(180.f), math::Rot3::ROT_X);
    REQUIRE(almost_equal(a.row(0), x));
    REQUIRE(almost_equal(a.row(1), ny));
    REQUIRE(almost_equal(a.row(2), nz));

    a.set(math::deg_to_rad(270.f), math::Rot3::ROT_X);
    REQUIRE(almost_equal(a.row(0), x));
    REQUIRE(almost_equal(a.row(1), z));
    REQUIRE(almost_equal(a.row(2), ny));

    // y rotations
    a.set(math::deg_to_rad(90.f), math::Rot3::ROT_Y);
    REQUIRE(almost_equal(a.row(0), z));
    REQUIRE(almost_equal(a.row(1), y));
    REQUIRE(almost_equal(a.row(2), nx));

    a.set(math::deg_to_rad(180.f), math::Rot3::ROT_Y);
    REQUIRE(almost_equal(a.row(0), nx));
    REQUIRE(almost_equal(a.row(1), y));
    REQUIRE(almost_equal(a.row(2), nz));

    a.set(math::deg_to_rad(270.f), math::Rot3::ROT_Y);
    REQUIRE(almost_equal(a.row(0), nz));
    REQUIRE(almost_equal(a.row(1),  y));
    REQUIRE(almost_equal(a.row(2),  x));

    // z rotations
    a.set(math::deg_to_rad(90.f), math::Rot3::ROT_Z);
    REQUIRE(almost_equal(a.row(0), ny));
    REQUIRE(almost_equal(a.row(1),  x));
    REQUIRE(almost_equal(a.row(2),  z));

    a.set(math::deg_to_rad(180.f), math::Rot3::ROT_Z);
    REQUIRE(almost_equal(a.row(0), nx));
    REQUIRE(almost_equal(a.row(1), ny));
    REQUIRE(almost_equal(a.row(2),  z));

    a.set(math::deg_to_rad(270.f), math::Rot3::ROT_Z);
    REQUIRE(almost_equal(a.row(0),  y));
    REQUIRE(almost_equal(a.row(1), nx));
    REQUIRE(almost_equal(a.row(2),  z));


    math::Rot3 b;
    b = a;
    b.transpose();
    REQUIRE(b.row(0).x == a.row(0).x);
    REQUIRE(b.row(1).y == a.row(1).y);
    REQUIRE(b.row(2).z == a.row(2).z);
    REQUIRE(b.row(1).x == a.row(0).y);
    REQUIRE(b.row(0).y == a.row(1).x);
}

TEST_CASE("Rot3b", "test math operators")
{
    const math::Vec3  x( 1, 0, 0);
    const math::Vec3  y( 0, 1, 0);
    const math::Vec3  z( 0, 0, 1);
    const math::Vec3 nx(-1, 0, 0);
    const math::Vec3 ny( 0,-1, 0);
    const math::Vec3 nz( 0, 0,-1);

    math::Vec3 va, vb;
    math::Rot3 ra, rb, rc;

    va.set(1, 0, 0);
    ra.set(0.f, math::Rot3::ROT_Z);

    vb = ra * va;
    REQUIRE(almost_equal(va, vb));

    ra.set(math::deg_to_rad(90.f), math::Rot3::ROT_Z);
    vb = ra * va;
    REQUIRE(almost_equal(vb, y));

    ra.set(math::deg_to_rad(180.f), math::Rot3::ROT_Z);
    vb = ra * va;
    REQUIRE(almost_equal(vb, nx));

    ra.set(math::deg_to_rad(270.f), math::Rot3::ROT_Z);
    vb = ra * va;
    REQUIRE(almost_equal(vb, ny));

    ra.set(math::deg_to_rad(360.f), math::Rot3::ROT_Z);
    vb = ra * va;
    REQUIRE(almost_equal(vb, x));

    ra.set(math::deg_to_rad( 90), math::Rot3::ROT_Z);
    rb.set(math::deg_to_rad(-90), math::Rot3::ROT_Z);

    rc = ra * rb;
    REQUIRE(math::almost_equal(rc.row(0), x));
    REQUIRE(math::almost_equal(rc.row(1), y));
    REQUIRE(math::almost_equal(rc.row(2), z));

    rc = ra;
    rc *= rb;
    REQUIRE(math::almost_equal(rc.row(0), x));
    REQUIRE(math::almost_equal(rc.row(1), y));
    REQUIRE(math::almost_equal(rc.row(2), z));

    ra.set(math::deg_to_rad( 90), math::Rot3::ROT_Y);
    rb.set(math::deg_to_rad(-90), math::Rot3::ROT_Y);

    rc = ra * rb;
    REQUIRE(math::almost_equal(rc.row(0), x));
    REQUIRE(math::almost_equal(rc.row(1), y));
    REQUIRE(math::almost_equal(rc.row(2), z));

    rc = ra;
    rc *= rb;
    REQUIRE(math::almost_equal(rc.row(0), x));
    REQUIRE(math::almost_equal(rc.row(1), y));
    REQUIRE(math::almost_equal(rc.row(2), z));

    ra.set(math::deg_to_rad( 90), math::Rot3::ROT_X);
    rb.set(math::deg_to_rad(-90), math::Rot3::ROT_X);

    rc = ra * rb;
    REQUIRE(math::almost_equal(rc.row(0), x));
    REQUIRE(math::almost_equal(rc.row(1), y));
    REQUIRE(math::almost_equal(rc.row(2), z));

    rc = ra;
    rc *= rb;
    REQUIRE(math::almost_equal(rc.row(0), x));
    REQUIRE(math::almost_equal(rc.row(1), y));
    REQUIRE(math::almost_equal(rc.row(2), z));

/*
    ra.set(math::deg_to_rad(90.f), math::Rot3::ROT_Z);
    float rotX = 0, rotY = 0, rotZ = 0;
    ra.decompose(rotX, rotY, rotZ);
    rotZ = math::rad_to_deg(rotZ);
    REQUIRE(90.f == rotZ);

    ra.set(math::deg_to_rad(30.f), math::Rot3::ROT_Y);
    ra.decompose(rotX, rotY, rotZ);
    rotY = math::rad_to_deg(rotY);
    REQUIRE(30.f == rotY);

    ra.set(math::deg_to_rad(45.f), math::Rot3::ROT_X);
    ra.decompose(rotX, rotY, rotZ);
    rotX = math::rad_to_deg(rotX);
    REQUIRE(45.f == rotX);

    ra.set(   math::deg_to_rad(45.f)
            , math::deg_to_rad(30.f)
            , math::deg_to_rad(60.f));

    //    ra.transpose();
    ra.decompose(rotX, rotY, rotZ);

    rb.set(   rotX
            , rotY
            , rotZ);
            
    REQUIRE(45.f == math::rad_to_deg(rotX));
    REQUIRE(30.f == math::rad_to_deg(rotY));
    REQUIRE(60.f == math::rad_to_deg(rotZ));
*/

}

