#include "AABB/AABB.hpp"
#include <gtest/gtest.h>

namespace geometry
{
namespace testing 
{
namespace AABB_functions_testing
{

namespace constructor_testing
{

TEST (constructorTesting, test1)
{
    Point_t p0 {231, 12321, -124};
    Point_t p1 {-123, 1324, 312/132};
    Point_t p2 {1, -1323/12344, 12312};

    Triangle_t t {p0, p1, p2};

    AABB_t aabb {t};

    EXPECT_EQ (aabb.pMin.x, -123);
    EXPECT_EQ (aabb.pMax.x, 231);
    EXPECT_EQ (aabb.pMin.y, -1323/12344);
    EXPECT_EQ (aabb.pMax.y, 12321);
    EXPECT_EQ (aabb.pMin.z, -124);
    EXPECT_EQ (aabb.pMax.z, 12312);
}

TEST (constructorTesting, test2)
{
    Point_t p0 {0, 0, 0};
    Point_t p1 {0, 0, 0};
    Point_t p2 {0, 0, 0};

    Triangle_t t {p0, p1, p2};

    AABB_t aabb {t};

    EXPECT_EQ (aabb.pMin.x, 0);
    EXPECT_EQ (aabb.pMax.x, 0);
    EXPECT_EQ (aabb.pMin.y, 0);
    EXPECT_EQ (aabb.pMax.y, 0);
    EXPECT_EQ (aabb.pMin.z, 0);
    EXPECT_EQ (aabb.pMax.z, 0);
}

}

namespace intersection_testing
{

TEST (intersectionTesting, test1)
{
    Point_t p01 {0, 0, 0};
    Point_t p11 {0, 0, 0};
    Point_t p21 {0, 0, 0};

    Triangle_t t1 {p01, p11, p21};

    AABB_t aabb1 {t1};

    Point_t p02 {0, 0, 0};
    Point_t p12 {0, 0, 0};
    Point_t p22 {0, 0, 0};

    Triangle_t t2 {p02, p12, p22};

    AABB_t aabb2 {t2};

    EXPECT_EQ (AABB_t::overlap (aabb1, aabb2), 1);
}

TEST (intersectionTesting, test2)
{
    Point_t p01 {0, 0, 0};
    Point_t p11 {0, 0, 0};
    Point_t p21 {0, 0, 0};

    Triangle_t t1 {p01, p11, p21};

    AABB_t aabb1 {t1};

    Point_t p02 {0, 0, 0};
    Point_t p12 {0, 0, 0};
    Point_t p22 {0, 0, 0};

    Triangle_t t2 {p02, p12, p22};

    AABB_t aabb2 {t2};

    EXPECT_EQ (AABB_t::overlap (aabb1, aabb2), 1);
}

TEST (intersectionTesting, test3)
{
    Point_t p01 {1, 1, 1};
    Point_t p11 {0, 0, 0};
    Point_t p21 {0, 0, 0};

    Triangle_t t1 {p01, p11, p21};

    AABB_t aabb1 {t1};

    Point_t p02 {-1, -1, -1};
    Point_t p12 {0, 0, 0};
    Point_t p22 {0, 0, 0};

    Triangle_t t2 {p02, p12, p22};

    AABB_t aabb2 {t2};

    EXPECT_EQ (AABB_t::overlap (aabb1, aabb2), 1);
}

TEST (intersectionTesting, test4)
{

    Point_t p01 {1, 1, 1};
    Point_t p11 {0, 0, 0};
    Point_t p21 {0, 0, 0};

    Triangle_t t1 {p01, p11, p21};

    AABB_t aabb1 {t1};

    Point_t p02 {-1, -1, -1};
    Point_t p12 {2, 2, 2};
    Point_t p22 {0, 0, 0};

    Triangle_t t2 {p02, p12, p22};

    AABB_t aabb2 {t2};

    EXPECT_EQ (AABB_t::overlap (aabb1, aabb2), 1);
}

TEST (intersectionTesting, test5)
{
    Point_t p01 {1, 1, 1};
    Point_t p11 {0, 0, 0};
    Point_t p21 {0, 0, 0};

    Triangle_t t1 {p01, p11, p21};

    AABB_t aabb1 {t1};

    Point_t p02 {-1, -1, -1};
    Point_t p12 {0, 0, 0};
    Point_t p22 {0, 0, 0};

    Triangle_t t2 {p02, p12, p22};

    AABB_t aabb2 {t2};

    EXPECT_EQ (AABB_t::overlap (aabb1, aabb2), 1);

}

}

} // AABB_functions_testing
} // testing
} // geometry

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}