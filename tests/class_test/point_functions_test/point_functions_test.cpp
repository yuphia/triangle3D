#include "point/point.hpp"
#include "gtest/gtest.h"

namespace geometry
{
namespace testing
{
namespace point_function_testing
{

namespace constructor_testing
{

TEST (constructorTesting, constructorTestSimple)
{
    Point_t p0 {1, 2, 3};
    Point_t p1;

    p1.x = 1;
    p1.y = 2;
    p1.z = 3;

    EXPECT_EQ (p0, p1);
    EXPECT_EQ (p0.degeneracy, Degeneracy_t::NONE);
}

TEST (constructorTesting, constructorTestDefaultDegeneracy)
{
    Point_t p1;

    EXPECT_EQ (p1.degeneracy, Degeneracy_t::INVALID);
}

}

}
}
}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}