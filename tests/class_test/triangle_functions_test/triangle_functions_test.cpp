#include "triangle/triangle.hpp"
#include "vector_geom/vector_geom.hpp"
#include "gtest/gtest.h"

namespace geometry
{
namespace testing
{
namespace triangle_testing 
{

namespace constructor_testing
{

TEST (constructorTesting, test)
{
    Point_t p0 {1, 2, 3};
    Point_t p1 {2, 3, 4};
    Point_t p2 {5, 6, 7};

    Triangle_t t {p0, p1, p2};
    Triangle_t t2;
    
    t2.points.push_back(p0);
    t2.points.push_back(p1);
    t2.points.push_back(p2);

    EXPECT_EQ (t, t2);
    EXPECT_EQ (t.degeneracy, Degeneracy_t::LINE_SEGMENT);
}

TEST (constructorTesting, testDegeneracyToPoint)
{
    Point_t p0 {1, 2, 3};
    Point_t p1 {1, 2, 3};
    Point_t p2 {1, 2, 3};

    Triangle_t t {p0, p1, p2};   

    EXPECT_EQ (t.degeneracy, Degeneracy_t::POINT);
}

TEST (constructorTesting, testDegeneracyToLineSegment1)
{
    Point_t p0 {1, 2, 3};
    Point_t p1 {1, 2, 3};
    Point_t p2 {2, 4, 6};

    Triangle_t t {p0, p1, p2};   

    EXPECT_EQ (t.degeneracy, Degeneracy_t::LINE_SEGMENT);
}

TEST (constructorTesting, testDegeneracyToLineSegment2)
{
    Point_t p0 {1, 2, 3};
    Point_t p1 {0, 0, 0};
    Point_t p2 {2, 4, 6};

    Triangle_t t {p0, p1, p2};   

    EXPECT_EQ (t.degeneracy, Degeneracy_t::LINE_SEGMENT);
}

TEST (constructorTesting, testDegeneracyToLineSegment3)
{
    Point_t p0 {1, 2, 3};
    Point_t p1 {1, 2, 3};
    Point_t p2 {2, 4, 6};

    Triangle_t t {p0, p1, p2};   

    EXPECT_EQ (t.degeneracy, Degeneracy_t::LINE_SEGMENT);
}

TEST (constructorTesting, testDefaultConstructorDegeneracy)
{
    Triangle_t t;
    EXPECT_EQ (t.degeneracy, Degeneracy_t::INVALID);
}

}

namespace max_min_point_testing
{

TEST (minTest, minTest1)
{
    Point_t p0 {1, 2, 3};
    Point_t p1 {1, 2, 3};
    Point_t p2 {2, 4, 6};

    Triangle_t t {p0, p1, p2};   

    Point_t p {1, 2, 3};

    EXPECT_EQ (p, t.get_min_point());
}

TEST (minTest, minTest2)
{
    Point_t p0 {1, 2, 3};
    Point_t p1 {1, 2, 3};
    Point_t p2 {2, 4, 6};

    Triangle_t t {p0, p1, p2};   

    Point_t p {2, 4, 6};

    EXPECT_EQ (p, t.get_max_point());
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