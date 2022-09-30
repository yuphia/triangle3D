#include "plane/plane.hpp"
#include "gtest/gtest.h"

namespace geometry
{
namespace testing
{
namespace plane_functions_test
{

namespace constructor_testing
{

TEST (constructorTesting, constructorTestingDefaultDegeneracy)
{
    Plane_t plane;

    EXPECT_EQ (plane.degeneracy, Degeneracy_t::INVALID);    
}

TEST (constructorTesting, constructor3PointsSimple)
{
    Point_t p0 {1, 1, 1};
    Point_t p1 {-1, 1, -2};
    Point_t p2 {-3, 1, 2};

    Vector_t vec = {0, 1, 0};

    Plane_t plane {p0, p1, p2};

    EXPECT_EQ (plane.normal, vec);
    EXPECT_EQ (plane.d, 1);
    EXPECT_EQ (plane.degeneracy, Degeneracy_t::NONE);
}

TEST (constructorTesting, constructor3PointsToLine)
{
    Point_t p0 {1, 1, 1};
    Point_t p1 {2, 2, 2};
    Point_t p2 {3, 3, 3};

    Vector_t vec = {0, 0, 0};

    Plane_t plane {p0, p1, p2};   

    EXPECT_EQ (plane.normal, vec);
    EXPECT_EQ (plane.d, 0);
    EXPECT_EQ (plane.degeneracy, Degeneracy_t::INVALID);
}

TEST (constructorTesting, constructor3PointsToPoint)
{
    Point_t p0 {1, 1, 1};
    Point_t p1 {1, 1, 1};
    Point_t p2 {1, 1, 1};

    Vector_t vec = {0, 0, 0};

    Plane_t plane {p0, p1, p2};   

    EXPECT_EQ (plane.normal, vec);
    EXPECT_EQ (plane.d, 0);
    EXPECT_EQ (plane.degeneracy, Degeneracy_t::INVALID);
}

TEST (constructorTesting, constructorByCoeffs)
{
    Plane_t plane {1, 2, 3, 4};
    Vector_t normal {1, 2, 3};

    EXPECT_EQ (plane.normal, normal.normalize());
    EXPECT_EQ (plane.d, -4/sqrt(14));
    EXPECT_EQ (plane.degeneracy, Degeneracy_t::NONE);
}

TEST (constructorTesting, constructorByNormalAndPoint)
{
    Vector_t normal {1, 1, 1};
    Point_t point {1, 1, 1};

    Vector_t vec_for_test {point};
    double d = normal.normalize() * vec_for_test;

    Plane_t plane {point, normal};

    EXPECT_EQ (plane.normal, normal.normalize());
    EXPECT_EQ (d, plane.d);
    EXPECT_EQ (plane.degeneracy, Degeneracy_t::NONE);
}

}  

namespace operator_testing
{
/*
TEST (operatorTesting, operatorParallelSuccess)
{
    Plane_t plane {};
}*/

}

}
}
}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}