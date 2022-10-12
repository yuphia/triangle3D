#pragma once

#include <limits>
#include <cmath>
#include "common_math_operations/common_math_operations.hpp"

namespace geometry
{

struct Point_t
{
    double x = std::numeric_limits<double>::quiet_NaN();
    double y = std::numeric_limits<double>::quiet_NaN();
    double z = std::numeric_limits<double>::quiet_NaN();
    
    Degeneracy_t degeneracy = Degeneracy_t::POIZON;


    Point_t (const double x_, const double y_, const double z_);
    Point_t ()
    {
        degeneracy = Degeneracy_t::INVALID;
    };


    bool operator== (const Point_t& rhs) const;
};

}