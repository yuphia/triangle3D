#pragma once

#include <limits>
#include <cmath>
#include "common_math_operations/common_math_operations.hpp"

namespace geometry
{

class Point_t
{
public:
    double x, y, z = std::numeric_limits<double>::quiet_NaN();
    
    Degeneracy_t degeneracy = Degeneracy_t::POIZON;


    Point_t (const double x_, const double y_, const double z_);


    bool operator== (const Point_t& rhs) const;
};

}