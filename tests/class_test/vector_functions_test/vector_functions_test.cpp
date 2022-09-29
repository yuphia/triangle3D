#include "common_math_operations/common_math_operations.hpp"
#include "vector/vector.hpp"
#include "gtest/gtest.h"

namespace geometry
{
namespace testing
{
namespace vector_testing
{

namespace constructorTest
{

TEST (constructorTests, degeneracyTest1)
{
    Vector_t vec {1, 1, 1};
    EXPECT_EQ (vec.degeneracy, Degeneracy_t::NONE);
}

TEST(constructorTests, pointConstr)
{
    Point_t test_point {1, 2, 3};
    Vector_t vec {test_point};
    Vector_t eq {1, 2, 3};

    EXPECT_EQ (vec, eq);
}

TEST(constructorTests, threeDoubleConstrX)
{
    Vector_t vec {1, 2, 3};
    Vector_t eq;
    eq.x = 1;

    EXPECT_EQ (vec.x, eq.x);
}

TEST(constructorTests, threeDoubleConstrY)
{
    Vector_t vec {1, 2, 3};
    Vector_t eq;
    eq.y = 2;

    EXPECT_EQ (vec.y, eq.y);
}

TEST(constructorTests, threeDoubleConstrZ)
{
    Vector_t vec {1, 2, 3};
    Vector_t eq;
    eq.z = 3;

    EXPECT_EQ (vec.z, eq.z);
}

TEST(constructorTests, nullVectorDegeneracy)
{
    Vector_t vec {0, 0, 0};
    EXPECT_EQ (vec.degeneracy, Degeneracy_t::NULL_VECTOR);
}

}

namespace crossProductTest
{

TEST(crossProduct, simpleCrossProduct)
{
    Vector_t lhs {1, 2, 3};
    Vector_t rhs {4, 5, 6};
    Vector_t res {-3, 6, -3};
    EXPECT_EQ (lhs % rhs, res);
}

TEST(crossProduct, simpleCrossProduct2)
{
    Vector_t lhs {-100, 1.590, 3};
    Vector_t rhs {400, 5.13, 6};
    Vector_t res {-5.85, 1800, -1149};
    EXPECT_EQ (lhs % rhs, res);
}

TEST(crossProduct, crossProductNULL)
{
    Vector_t lhs {1, 2, 3};
    Vector_t rhs {2, 4, 6};
    Vector_t res {0, 0, 0};
    EXPECT_EQ (lhs % rhs, res);
}

}

namespace dotProductTest
{

TEST(dotProduct, dotCrossProduct)
{
    Vector_t lhs {1, 2, 3};
    Vector_t rhs {4, 5, 6};

    EXPECT_EQ (lhs * rhs, 32);
}

TEST(dotProduct, dotCrossProduct2)
{
    Vector_t lhs {-100, 1.590, 3};
    Vector_t rhs {400, 5.13, 6};
    Vector_t res {-5.85, 1800, -1149};
    EXPECT_EQ (lhs * rhs, -39973.8433);
}

TEST(dotProduct, dotProductNULL)
{
    Vector_t lhs {1, 1, 1};
    Vector_t rhs {-1, 2, -1};

    EXPECT_EQ (lhs * rhs, 0);
}

}

namespace additionTest
{

TEST(addition, simpleAdd)
{
    Vector_t lhs {213, 31, 97};
    Vector_t rhs {16, 2342, -500};
    Vector_t res {213 + 16, 31 + 2342, 97 - 500};

    EXPECT_EQ (lhs + rhs, res);
}

}

namespace substitutionTest
{

TEST(substitute, unaryMinus)
{   
    Vector_t v{1, 1, 0};
    Vector_t res {-1, -1, 0};

    EXPECT_EQ (-v, res);
}

TEST(substitute, simpleSub)
{
    Vector_t lhs {213, 31, 97};
    Vector_t rhs {16, 2342, -500};
    Vector_t res {213 - 16, 31 - 2342, 97 + 500};

    EXPECT_EQ (lhs - rhs, res);
}

}

namespace scalingTest
{

TEST(scaling, nullScaling)
{
    Vector_t v {1, 2, 3};
    Vector_t nul {0, 0, 0};

    EXPECT_EQ (nul, v*0);
}

TEST(scaling, simpleScaling)
{
    Vector_t v {1, 2, 3};
    Vector_t res {1.519, 2*1.519, 3*1.519};

    EXPECT_EQ (res, v*1.519);
}

}

namespace collinearTest
{

TEST(collinear, simpleCollinear)
{
    Vector_t v1{1, 2, 3};
    Vector_t v2{2, 4, 6};

    EXPECT_EQ (v1.is_collinear_to(v2), 1);
}

TEST(collinear, nullCollinear)
{
    Vector_t v1{1, 2, 3};
    Vector_t v2{0, 0, 0};

    EXPECT_EQ (v1.is_collinear_to(v2), 1);
}

TEST(collinear, simpleNonCollinear)
{
    Vector_t v1{1, 2, 3};
    Vector_t v2{2, 4, 10};

    EXPECT_EQ (v1.is_collinear_to(v2), 0);
}

}

namespace squaredLenTest
{

TEST(squaredLen, squaredLenNul)
{
    Vector_t vec = {0, 0, 0};
    EXPECT_EQ (vec.squared_length(), 0);
}

TEST(squaredLen, squaredLenSimple)
{
    Vector_t vec = {1, 2, 3};
    EXPECT_EQ (vec.squared_length(), 14);
}

}

namespace normalization
{

TEST(normalization, normLen)
{
    Vector_t vec {1, 2, 3};
    Vector_t norm = vec.normalize();

    EXPECT_EQ (norm.squared_length(), 1);
}

TEST(normalization, normCollinearity)
{
    Vector_t vec {1, 2, 3};
    Vector_t norm = vec.normalize();

    EXPECT_EQ (norm.is_collinear_to(vec), 1);
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