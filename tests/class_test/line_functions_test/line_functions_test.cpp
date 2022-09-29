#include "gtest/gtest.h"
#include "point/point.hpp"
#include "vector_geom/vector_geom.hpp"
#include "line/line.hpp"
#include <iostream>

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

TEST (constructorTesting, constructorDefault)
{
    Line_t line;

    EXPECT_EQ (line.degeneracy, Degeneracy_t::INVALID);
}

TEST (constructorTesting, constructorPointVectorSimple)
{
    Point_t p0 {1, 1, 1};
    Vector_t v0 {1, 1, 1};

    Line_t line {p0, v0};
    
    Vector_t vec {p0};

    EXPECT_EQ (line.point_on_line, vec);
    EXPECT_EQ (line.direction_vec, v0);
    EXPECT_EQ (line.degeneracy, Degeneracy_t::NONE);
}

TEST (constructorTesting, constructorPointVectorDegenerateToPoint)
{
    Point_t p0 {1, 1, 1};
    Vector_t v0 {0, 0, 0};

    Line_t line {v0, p0};

    EXPECT_EQ (line.degeneracy, Degeneracy_t::POINT);
}

TEST (constructorTesting, constructorPointVectorInvalid)
{
    Point_t p0 {1, 1, 1};
    Vector_t v0;

    Line_t line {v0, p0};
    
    Vector_t vec {p0};

    EXPECT_EQ (line.point_on_line, vec);
    EXPECT_EQ (line.degeneracy, Degeneracy_t::INVALID);
}

TEST (constructorTesting, constructorVectorVectorSimple)
{
    Vector_t v0 {1, 1, 1};
    Vector_t v1 {1, 1, 1};

    Line_t line {v0, v1};
    

    EXPECT_EQ (line.point_on_line, v1);
    EXPECT_EQ (line.direction_vec, v0);
        EXPECT_EQ (line.degeneracy, Degeneracy_t::NONE);
}

TEST (constructorTesting, constructorVectorVectorDegenerateToPoint)
{
    Vector_t v0 {0, 0, 0};
    Vector_t v1 {1, 1, 1};

    Line_t line {v0, v1};

    EXPECT_EQ (line.degeneracy, Degeneracy_t::POINT);
}

TEST (constructorTesting, constructorVectorVectorInvalid)
{
    Point_t v1 {1, 1, 1};
    Vector_t v0;

    Line_t line {v0, v1};

    EXPECT_EQ (line.point_on_line, v1);
    EXPECT_EQ (line.degeneracy, Degeneracy_t::INVALID);
}

TEST (constructorTesting, constructorLineSegmentSimple)
{
    Point_t p0 {1, 1, 1};
    Point_t p1 {2, 2, 2};

    Vector_t dir = Vector_t{p1} - Vector_t{p0};
    Vector_t point {p0};

    Line_segment_t line_seg {p0, p1};

    Line_t line {line_seg};

    EXPECT_EQ (line.point_on_line, point);
    EXPECT_EQ (line.direction_vec, dir);
    EXPECT_EQ (line.degeneracy, Degeneracy_t::NONE);
}

TEST (constructorTesting, constructorLineSegmentPoint)
{
    Point_t p0 {1, 1, 1};
    Point_t p1 {1, 1, 1};

    Vector_t point {p0};

    Line_segment_t line_seg {p0, p1};

    Line_t line {line_seg};

    EXPECT_EQ (line.point_on_line, point);
    EXPECT_EQ (line.degeneracy, Degeneracy_t::POINT);
}

TEST (constructorTesting, constructorLineSegmentInvalid)
{
    Point_t p0 {1, 1, 1};
    Point_t p1;

    Line_segment_t line_seg {p0, p1};

    Line_t line {line_seg};

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