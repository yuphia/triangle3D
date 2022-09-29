#include "gtest/gtest.h"
#include "point/point.hpp"
#include "vector_geom/vector_geom.hpp"
#include "line/line.hpp"

namespace geometry
{
namespace testing 
{
namespace line_testing
{

namespace constructor_testing 
{

TEST (constructorTesting, constructor2PointsSimple)
{
    Point_t p0 {1, 1, 1};
    Point_t p1 {2, 2, 2};

    Vector_t direction_vec = Vector_t {p1} - Vector_t {p0};
    Vector_t point_on_line {p0};

    Line_t line {p0, p1};

    EXPECT_EQ (line.direction_vec, direction_vec);
    EXPECT_EQ (line.point_on_line, point_on_line);
    EXPECT_EQ (line.degeneracy, Degeneracy_t::NONE);
}

TEST (constructorTesting, constructor2PointsPoint)
{
    Point_t p0 {1, 1, 1};
    Point_t p1 {1, 1, 1};

    Vector_t direction_vec = Vector_t {p1} - Vector_t {p0};
    Vector_t point_on_line {p0};

    Line_t line {p0, p1};

    EXPECT_EQ (line.direction_vec, direction_vec);
    EXPECT_EQ (line.point_on_line, point_on_line);
    EXPECT_EQ (line.degeneracy, Degeneracy_t::POINT);
}

TEST (constructorTesting, constructor2PointsInvalid)
{
    Point_t p0 {1, 1, 1};
    Point_t p1;

    Line_t line {p0, p1};

    EXPECT_EQ (line.degeneracy, Degeneracy_t::INVALID);
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