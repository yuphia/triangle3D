#include "Triangle_intersection_algorithm/Triangle_intersection_algorithm.hpp"
#include "gtest/gtest.h"

namespace geometry
{
namespace testing 
{
namespace main_algorithm_test
{

namespace signed_distance_test
{

TEST (signedDistanceTest, testInPlane)
{
    Point_t p1(1.5, -4, 8.25);
    Point_t p2(7, 10, -4.25);
    Point_t p3(5, 3, -0.15);
    Point_t p4(-30.1, 2.45, -10.5);

    Plane_t plane1 {p1, p2, p3};
    double dist1 = signed_distance (p4, plane1);
    EXPECT_EQ(equal_eps(dist1, 36.400817026925), 1);

    Plane_t plane2 {p1, p2, p4};
    double dist2 = signed_distance (p3, plane2);
    EXPECT_EQ(equal_eps(dist2, -1.630383462161), 1);

    Plane_t plane3 {p1, p3, p4};
    double dist3 = signed_distance (p2, plane3);
    EXPECT_EQ(equal_eps(dist3, 2.78234169), 1);
    double dist4 = signed_distance (p1, plane3);
    EXPECT_EQ(equal_eps(dist4, 0), 1);
}

} // signed_distance_test


namespace intersection_line_test
{

TEST (intersectionLineTest, general)
{
    Plane_t plane1 {1, 2, 3, 1};
    Plane_t plane2 {-1, -34, 10, 3};
    Plane_t plane3 {0, 0, 1, 1};
    Plane_t plane4 {1, 0, 0, 2};
    Plane_t plane5 {-1, -3, 10, 10};
    Plane_t plane6 {6, 7, 39, 14};

    Vector_t vec1 {122, -13, -32};
    Vector_t vec2 {0, 2, 0};
    Vector_t vec3 {-17, 9, 1};
    
    Line_t line1 = construct_intersection_line(plane1, plane2);
    EXPECT_EQ (line1.direction_vec.is_collinear_to(vec1), true);
    Point_t p1 = {line1.point_on_line.x, line1.point_on_line.y, line1.point_on_line.z};
    EXPECT_EQ (equal_eps(signed_distance(p1, plane1), 0.0), true);
    EXPECT_EQ (equal_eps(signed_distance(p1, plane2), 0.0), true);

    Line_t line2 = construct_intersection_line(plane3, plane4);
    EXPECT_EQ (line2.direction_vec.is_collinear_to(vec2), true);
    Point_t p2 = {line2.point_on_line.x, line2.point_on_line.y, line2.point_on_line.z};
    EXPECT_EQ (equal_eps(signed_distance(p2, plane3), 0.0), true);
    EXPECT_EQ (equal_eps(signed_distance(p2, plane4), 0.0), true);

    Line_t line3 = construct_intersection_line(plane5, plane6);
    EXPECT_EQ (line3.direction_vec.is_collinear_to(vec3), true);
    Point_t p3 = {line3.point_on_line.x, line3.point_on_line.y, line3.point_on_line.z};
    EXPECT_EQ (equal_eps(signed_distance(p3, plane5), 0.0), true);
    EXPECT_EQ (equal_eps(signed_distance(p3, plane6), 0.0), true);


    EXPECT_EQ (construct_intersection_line(plane1, plane2).direction_vec.is_collinear_to(vec3), false);
}

} // intersection_line_test

namespace point_projection_test
{

TEST (distanceToLineTest, general)
{
    Line_t line1 { Vector_t{-3, 5,   3}, Point_t{-4, 8, 5} };
    Line_t line2 { Vector_t{ 0, 0,   1}, Point_t{3,  0, 0} };
    Line_t line3 { Vector_t{10, -19, 0}, Point_t{2, -4, 8} };

    Point_t p1 {4, -2, 1};  
    Point_t p2 {5, 2, 3};  
    Point_t p3 {12, -23, 8}; 
    
    EXPECT_EQ (point_on_line_projection_coeff(p1, line1), -2);
    EXPECT_EQ (point_on_line_projection_coeff(p2, line2),  3);
    EXPECT_EQ (point_on_line_projection_coeff(p3, line3),  1);
}

} //point_projection_test

namespace triangle_projection_test
{

TEST (triangleProjectionTest, general)
{
    Line_t line1 { Vector_t{-3, 5, 3}, Point_t{-4, 8, 5} };
    Point_t p1 {4, -2, 1};  
    Point_t p2 {-8, 18, 13}; 
    Point_t p3 {-4, 8, 5}; 
    double min1, max1;
    compute_triangle_projection_on_line_segment (Triangle_t {p1, p2, p3}, line1, min1, max1);
    EXPECT_EQ (min1, -2);
    EXPECT_EQ (max1, 2);

    Line_t line2 { Vector_t{ 0, 0, 1}, Point_t{3, 0, 0} };
    Point_t p4 {5, 2, 3};  
    Point_t p5 {-8, 18, 0}; 
    Point_t p6 {-4, 10, -4}; 
    double min2, max2;
    compute_triangle_projection_on_line_segment (Triangle_t {p4, p5, p6}, line2, min2, max2);
    EXPECT_EQ (min2, -4);
    EXPECT_EQ (max2, 3);

    Line_t line3 { Vector_t{10, -19, 0}, Point_t{2, -4, 8} };
    Point_t p7 {2, -4, 8};  
    Point_t p8 {22, -42, 8}; 
    Point_t p9 {-8, 15, 5}; 
    double min3, max3;
    compute_triangle_projection_on_line_segment (Triangle_t {p7, p8, p9}, line3, min3, max3);
    EXPECT_EQ (min3, -1);
    EXPECT_EQ (max3, 2);

    Line_t line4 { Vector_t{ 0, 0, 1}, Point_t{3, 0, 0} };
    Point_t p10 {3, 0, 2};  
    Point_t p11 {3, 1, 9}; 
    Point_t p12 {-4, 10, 7}; 
    double min4, max4;
    compute_triangle_projection_on_line_segment (Triangle_t {p10, p11, p12}, line4, min4, max4);
    EXPECT_EQ (min4, 2);
    EXPECT_EQ (max4, 9);
}

} //triangle_projection_test

namespace triangle_intersection_test
{

TEST (triangleIntersectionTest, general)
{
    Point_t pt1(-106.0469443923, 52.5713734098, 1168.62612723);
    Point_t pt2(-651.061758726, 168.7717457742, 694.2902541365);
    Point_t pt3(428.5401392144, -85.9438632779, 733.317083182);

    Point_t pt4(-411.2836818256, -356.8993505802, 1109.2200394315);
    Point_t pt5(-286.9602404404, 281.1077706209, 901.6945024073);
    Point_t pt6(-273.4987522435, -732.4222971763, 626.6145537568);

    Triangle_t triag1(pt1, pt2, pt3);
    Triangle_t triag2(pt4, pt5, pt6);

    EXPECT_EQ(do_triangles_intersect(triag1, triag2), 1);


    Point_t pt7(20.58046, -43.99046, 0);
    Point_t pt8(-10, -30, 0);
    Point_t pt9(40.70333, -32.11313, 12.51765);

    Point_t pt10(14.04051, -20.82335, 0);
    Point_t pt11(30, -40, 11.89029);
    Point_t pt12(56.74394, -23.46234, 0);

    Triangle_t triag3(pt7, pt8, pt9);
    Triangle_t triag4(pt10, pt11, pt12);

    EXPECT_EQ(do_triangles_intersect(triag3, triag4), 1);


    Point_t pt13(33.22144, -30.78249, 5.73506);
    Triangle_t triag5(pt13, pt7, pt8);
    EXPECT_EQ(do_triangles_intersect(triag5, triag4), 1);


    Triangle_t triag6(pt12, pt7, pt8);
    EXPECT_EQ(do_triangles_intersect(triag6, triag4), 1);


    Triangle_t triag7(pt12, pt11, pt8);
    EXPECT_EQ(do_triangles_intersect(triag7, triag4), 1);


    Point_t pt14(23.36736, -14.79033, 5.72534);
    Triangle_t triag8(pt14, pt7, pt8);
    EXPECT_EQ(do_triangles_intersect(triag8, triag4), 1);

    Point_t pt15(10.36104, -17.95187, 5.72534);
    Triangle_t triag9(pt15, pt7, pt8);
    EXPECT_EQ(do_triangles_intersect(triag9, triag4), 0);
}

} //Triangle_intersection_test


} //main_algorithm_test 
} //testing 
} //geometry

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}