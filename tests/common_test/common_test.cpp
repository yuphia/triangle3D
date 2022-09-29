#include "common_math_operations/common_math_operations.hpp"
#include "gtest/gtest.h"

namespace geometry
{
namespace testing
{

namespace equalityTests
{

TEST(equality, eqTest1)
{
    double x = 1.1;
    double y = 2.2;
    EXPECT_EQ (equal_eps (x, y), 0);
}

}

}
}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}