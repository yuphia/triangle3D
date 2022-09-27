#pragma once

#include "point/point.hpp"
#include "common_math_operations/common_math_operations.hpp"

namespace geometry
{

class Vector_t
{
public:
    double length = std::numeric_limits<double>::quiet_NaN();
    double x = std::numeric_limits<double>::quiet_NaN();
    double y = std::numeric_limits<double>::quiet_NaN(); 
    double z = std::numeric_limits<double>::quiet_NaN();

    Degeneracy_t degeneracy = Degeneracy_t::POIZON;

    Vector_t (const double x_, const double y_, const double z_);
    Vector_t (const Point_t& point);

    bool     operator== (const Vector_t& rhs) const;
    Vector_t operator+  (const Vector_t& rhs) const;
    Vector_t operator-  (const Vector_t& rhs) const;
    Vector_t operator-  () const;

    double   operator*  (const Vector_t& rhs) const; 
    Vector_t operator%  (const Vector_t& rhs) const; 

    Vector_t normalize();
    bool is_collinear_to (const Vector_t& vec) const;
};

} //geometry