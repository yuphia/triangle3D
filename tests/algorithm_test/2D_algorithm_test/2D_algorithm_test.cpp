#include "Triangle_intersection_algorithm/Triangle_intersection_algorithm.hpp"
#include "gtest/gtest.h"


namespace geometry
{

namespace testing
{

namespace in_the_same_plane_case_test
{

namespace in_the_same_plane_case_functions_testing
{

TEST (constructingPerpendicularLineTesting, general)
{
    Plane_t plane1 {0, 0, 1, 1};
    Plane_t plane2 {4, 5, 6, 3};
    Plane_t plane3 {0, 1, 0, 0};

    Point_t point1 {1, 1, 1};
    Point_t point2 {4, 1, -3};
    Point_t point3 {1, 0, 1};

    Line_t line1 {  Vector_t{1, 1,  0}, point1 };
    Line_t line2 {  Vector_t{2, 2, -3}, point2 };
    Line_t line3 {  Vector_t{1, 0,  0}, point3 };

    Line_t perp1 { Vector_t{-1,   1,  0}, point1 };
    Line_t perp2 { Vector_t{ 2,   1,  0}, point1 };
    Line_t perp3 { Vector_t{-27 / sqrt(77), 24 / sqrt(77), -2 / sqrt(77)}, point2 };
    Line_t perp4 { Vector_t{ 0, 0, -1}, point3 };

    EXPECT_EQ ( construct_perpendicular_line_in_plane(plane1, line1) == perp1, true);
    EXPECT_EQ ( construct_perpendicular_line_in_plane(plane1, line1) == perp2, false);

    EXPECT_EQ ( construct_perpendicular_line_in_plane(plane2, line2) == perp3, true);
    EXPECT_EQ ( construct_perpendicular_line_in_plane(plane2, line2) == perp2, false);

    EXPECT_EQ ( construct_perpendicular_line_in_plane(plane3, line3) == perp4, true);
    EXPECT_EQ ( construct_perpendicular_line_in_plane(plane3, line3) == perp1, false);
}

TEST (trianglesInPlaneIntersectionTesting, general)
{
    Plane_t plane1 {0, 0, 1, 1};

    Point_t p0 {0, 0, 1};
    Point_t p1 {-1, 4, 1};
    Point_t p2 {1, 5, 1};
    Point_t p3 {2, 0, 1};
    Point_t p4 {10, 10, 1};
    Point_t p5 {0, 3, 1};
    Point_t p6 {5, 5, 1};
    Point_t p7 {6, 6, 1};
    Point_t p8 {5, 6, 1};
    Point_t p9 {12, 13, 1};
    Point_t p10 {14, 17, 1};

    Triangle_t triangle1 {p0,  p1, p2};
    Triangle_t triangle2 {p3,  p4, p5};
    Triangle_t triangle3 {p6,  p7, p8};
    Triangle_t triangle4 {p7,  p8, p4};
    Triangle_t triangle5 {p9, p10, p4};

    EXPECT_EQ (do_triangles_in_the_same_plane_intersect (plane1, triangle1, triangle2), true);
    EXPECT_EQ (do_triangles_in_the_same_plane_intersect (plane1, triangle1, triangle3), false);

    EXPECT_EQ (do_triangles_in_the_same_plane_intersect (plane1, triangle3, triangle4), true);
    EXPECT_EQ (do_triangles_in_the_same_plane_intersect (plane1, triangle2, triangle5), true);
    EXPECT_EQ (do_triangles_in_the_same_plane_intersect (plane1, triangle3, triangle3), true);

}

} //in_the_same_plane_case_functions_testing
} //in_the_same_place_case_test
} //testing
} //geometry

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}