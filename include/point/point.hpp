#pragma once

#include <limits>
#include <cmath>
#include "../common_math_operations/common_math_operations.hpp"

namespace geometry
{

struct Point_t
{
    double x = std::numeric_limits<double>::quiet_NaN();
    double y = std::numeric_limits<double>::quiet_NaN();
    double z = std::numeric_limits<double>::quiet_NaN();
    
    Degeneracy_t degeneracy = Degeneracy_t::POIZON;

    Point_t ()
    {
        degeneracy = Degeneracy_t::INVALID;
    };

    Point_t (const double x_, const double y_, const double z_) : x(x_), y(y_), z(z_) 
    {
        if (std::isnan(x) || std::isnan(y) || std::isnan(z))
            degeneracy = Degeneracy_t::INVALID;
        else
            degeneracy = Degeneracy_t::NONE;
    }

    bool operator== (const Point_t& rhs) const
    {
        return (equal_eps (x, rhs.x) && equal_eps (y, rhs.y) && equal_eps (z, rhs.z));
    }

};

}