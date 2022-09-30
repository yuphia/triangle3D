#include "Triangle_intersection_algorithm/Triangle_intersection_algorithm.hpp"
#include "gtest/gtest.h"

namespace geometry
{
namespace testing 
{
namespace  service_functions_test
{

namespace signed_distance_test
{

TEST (signedDistanceTest, test1)
{
    Plane_t plane {512, 34, 123, 213};
    Point_t point {1, 1, 2};

    double expected_distance = 1.097289769;
    double distance = signed_distance (point, plane);
    EXPECT_EQ (equal_eps (distance, expected_distance), 1);
}

TEST (signedDistanceTest, test2)
{
    Plane_t plane {-12, -34, 1230, 213};
    Point_t point {1, 1, 2};

    double expected_distance = 1.7886625811160317;
    double distance = signed_distance (point, plane);
    EXPECT_EQ (equal_eps (distance, expected_distance), 1);   
}

TEST (signedDistanceTest, test3)
{
    Plane_t plane {-12, -34, -1230, 213};
    Point_t point {1, 1, 2};

    double expected_distance = -2.2096199718557434;
    double distance = signed_distance (point, plane);
    EXPECT_EQ (equal_eps (distance, expected_distance), 1);   
}

TEST (signedDistanceTest, testInPlane)
{
    Plane_t plane {-12, -34, 1230, 0};
    Point_t point {0, 0, 0};

    double expected_distance = 0;
    double distance = signed_distance (point, plane);
    EXPECT_EQ (equal_eps (distance, expected_distance), 1);   
}

}

namespace 

} //main_algorithm_test 
} //testing 
} //geometry

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}