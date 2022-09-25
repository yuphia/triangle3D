#pragma once

#include <cmath>
#include "vector/vector.hpp"

namespace geometry
{

const double EPS = 10e-9;

double sqr (const double x);
bool equal_eps (const double x, const double y);
Vector_t cross_product (const Vector_t& a, const Vector_t& b);

double sqr (const double x)
{
    return x * x;
}

bool equal_eps (const double x, const double y)
{
    return (x - y) < EPS;    
}

}