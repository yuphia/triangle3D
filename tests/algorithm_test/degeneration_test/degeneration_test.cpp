#include "Triangle_intersection_algorithm/Triangle_intersection_algorithm.hpp"
#include "gtest/gtest.h"

namespace geometry
{

namespace testing
{

namespace degeneration_cases_test
{

namespace degeneration_case_functions_testing
{

TEST (convertingToLineSegmentTesting, general)
{
    Point_t p1 {1, 1, 1};
    Point_t p2 {2, 2, 2};
    Point_t p3 {3, 3, 3};
    Point_t p4 {4, 4, 4};

    Triangle_t triangle1 {p1, p2, p3};    
    EXPECT_EQ ( (Vector_t) p1 == convert_to_line_segment(triangle1).p0, true);
    EXPECT_EQ ( (Vector_t) p3 == convert_to_line_segment(triangle1).p1, true);

    Triangle_t triangle2 {p2, p4, p3};
    EXPECT_EQ ( (Vector_t) p2 == convert_to_line_segment(triangle2).p0, true);
    EXPECT_EQ ( (Vector_t) p4 == convert_to_line_segment(triangle2).p1, true);

    Triangle_t triangle3 {p2, p1, p4};
    EXPECT_EQ ( (Vector_t) p1 == convert_to_line_segment(triangle3).p0, true);
    EXPECT_EQ ( (Vector_t) p4 == convert_to_line_segment(triangle3).p1, true);

    Triangle_t triangle4 {p2, p2, p4};
    EXPECT_EQ ( (Vector_t) p2 == convert_to_line_segment(triangle4).p0, true);
    EXPECT_EQ ( (Vector_t) p4 == convert_to_line_segment(triangle4).p1, true);

    Triangle_t triangle5 {p2, p4, p2};
    EXPECT_EQ ( (Vector_t) p2 == convert_to_line_segment(triangle5).p0, true);
    EXPECT_EQ ( (Vector_t) p4 == convert_to_line_segment(triangle5).p1, true);
}

TEST (pointIntersectTriangleTesting, general)
{
    Point_t p1 {0, 0, 0};
    Point_t p2 {2, 0, 0};
    Point_t p3 {2, 2, 2};
    Point_t p4 {1.5, 0.5, 0.5};
    Point_t p5 {3, 3, 3};

    Triangle_t triangle1{p1, p2, p3};    
    EXPECT_EQ (do_point_and_triangle_intersect(p4, triangle1), 1);
    EXPECT_EQ (do_point_and_triangle_intersect(p5, triangle1), 0);
    EXPECT_EQ (do_point_and_triangle_intersect(p2, triangle1), 1);
    EXPECT_EQ (do_point_and_triangle_intersect(Point_t{1, 0, 0}, triangle1), 1);
}

TEST (segmentsIntersectTesting, general)
{
    Point_t p1 {0, 0, 0};
    Point_t p2 {2, 0, 0};
    Point_t p3 {0, -1, -1};
    Point_t p4 {1, 1, 1};
    Point_t p5 {-1, -4, -2};
    Point_t p6 {3, 3, 3};
    Point_t p7 {1, 2, 1};
    Point_t p8 {1, 0, 1};
    Point_t p9 {3, 6, 4};
    Point_t p10 {3, 0, 0};
    Point_t p11 {4, 0, 0};

    EXPECT_EQ (do_line_segments_intersect(Line_segment_t{p1, p2}, Line_segment_t{p3, p4}), 1);
    EXPECT_EQ (do_line_segments_intersect(Line_segment_t{p1, p4}, Line_segment_t{p3, p1}), 1);
    EXPECT_EQ (do_line_segments_intersect(Line_segment_t{p1, p4}, Line_segment_t{p3, p2}), 0);
    EXPECT_EQ (do_line_segments_intersect(Line_segment_t{p1, p4}, Line_segment_t{p3, p2}), 0);
    EXPECT_EQ (do_line_segments_intersect(Line_segment_t{p5, p9}, Line_segment_t{p1, p6}), 1);
    EXPECT_EQ (do_line_segments_intersect(Line_segment_t{p6, p4}, Line_segment_t{p8, p7}), 1);
    EXPECT_EQ (do_line_segments_intersect(Line_segment_t{p1, p1}, Line_segment_t{p1, p2}), 1);
    EXPECT_EQ (do_line_segments_intersect(Line_segment_t{p1, p10}, Line_segment_t{p2, p11}), 1);
    EXPECT_EQ (do_line_segments_intersect(Line_segment_t{p10, p11}, Line_segment_t{p10, p11}), 1);
}

TEST (SegmentIntersectTriangleTesting, general)
{
    
    Point_t p1 {-1, 0, 0};
    Point_t p2 {20, 0, 1};
    Point_t p3 {1, 10, -1};
    Point_t p4 {6, 4, 6};
    Point_t p5 {6, 6, -4};
    Point_t p6 {-10, -10, -1};
    Point_t p7 {-5, 0, -1};
    Point_t p8 {10, 0, 3};
    Point_t p9 {10, 0, -1};

    Triangle_t triangle{p1, p2, p3};

    EXPECT_EQ (do_line_segment_and_triangle_intersect(Triangle_t{p4, p4, p5}, triangle), 1);
    EXPECT_EQ (do_line_segment_and_triangle_intersect(Triangle_t{p6, p6, p7}, triangle), 0);
    EXPECT_EQ (do_line_segment_and_triangle_intersect(Triangle_t{p6, p1, p1}, triangle), 1);
    EXPECT_EQ (do_line_segment_and_triangle_intersect(Triangle_t{p6, p7, p6}, triangle), 0);
    EXPECT_EQ (do_line_segment_and_triangle_intersect(Triangle_t{p8, p9, p9}, triangle), 1);

}

TEST (mainDegenerationCaseAlgorithmTesting, general)
{
    
    Point_t p0  {0, 0, 0};
    Point_t p1  {1, 0, 0};
    Point_t p2  {4, 0, 0};
    Point_t p3  {6, 0, 0};
    Point_t p4  {6, 4, 6};
    Point_t p5  {7, 4, 7};
    Point_t p6  {8, 4, 8};
    Point_t p7  {-10, -10, -1};
    Point_t p8  {6, 6, 0};
    Point_t p9  {0, 0, 6};
    Point_t p10 {-3, 0, 0};
    Point_t p11 {6, 0, -1};
    Point_t p12 {6, 10, 6};
    Point_t p13 {10, 0, 0};
    Point_t p14 {0, 0, 10};
    Point_t p15 {10, 0, 10};


    Triangle_t point_triag1   {p1, p1, p1};
    Triangle_t point_triag2   {p1, p1, p1};
    Triangle_t point_triag3   {p2, p2, p2};

    Triangle_t segment_triag1 {p0, p3, p3};
    Triangle_t segment_triag2 {p4, p5, p6};
    Triangle_t segment_triag3 {p9, p8, p9};
    Triangle_t segment_triag4 {p2, p13, p13};
    Triangle_t segment_triag5 {p13, p13, p14};
    Triangle_t segment_triag6 {p1, p15, p1};

    Triangle_t triag1         {p3, p5, p0};
    Triangle_t triag2         {p7, p3, p5};
    Triangle_t triag3         {p7, p10, p0};
    Triangle_t triag4         {p0, p3, p12};
    Triangle_t triag5         {p0, p3, p9};

    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(point_triag1, point_triag2), 1);
    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(point_triag1, point_triag3), 0);

    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(point_triag1, segment_triag1), 1);
    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(point_triag1, segment_triag2), 0);

    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(point_triag1, triag1), 1);
    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(point_triag1, triag2), 0);



    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(segment_triag1, point_triag1), 1);
    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(segment_triag2, point_triag1), 0);

    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(segment_triag1, segment_triag4), 1);
    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(segment_triag6, segment_triag5), 1);
    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(segment_triag2, segment_triag5), 0);

    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(segment_triag3, triag4), 1);
    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(segment_triag3, triag3), 0);



    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(triag1, point_triag3), 1);
    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(triag2, point_triag2), 0);

    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(triag4, segment_triag3), 1);
    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(triag3, segment_triag3), 0);
    
    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(triag1, segment_triag1), 1);
    EXPECT_EQ (select_and_run_algo_for_degenerated_triangles(triag5, segment_triag5), 0);

}

} //degeneration_case_functions_testing
} //degeneration_cases_test
} //testing
} //geometry

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}