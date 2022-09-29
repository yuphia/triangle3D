#include "gtest/gtest.h"
#include "line_segment/line_segment.hpp"

namespace geometry
{
namespace testing
{
namespace line_segment_functions_test
{

namespace constructor_testing
{

TEST (constructorTesting, constructorDefaultnvalid)
{
    Line_segment_t line_segment;
    EXPECT_EQ (line_segment.degeneracy, Degeneracy_t::INVALID);
}

TEST (constructorTesting, constructor2PointsSimple)
{
    Point_t p0 {1, 2, 3};
    Point_t p1 {2, 3, 4};

    Line_segment_t line_segment {p0, p1};

    Vector_t v0{p0};
    Vector_t v1{p1};

    EXPECT_EQ (line_segment.p0, v0);
    EXPECT_EQ (line_segment.p1, v1);
    EXPECT_EQ (line_segment.degeneracy, Degeneracy_t::NONE);
}

TEST (constructorTesting, constructor2PointsPoint)
{
    Point_t p0 {1, 2, 3};
    Point_t p1 {1, 2, 3};

    Line_segment_t line_segment {p0, p1};

    EXPECT_EQ (line_segment.degeneracy, Degeneracy_t::POINT);
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