#pragma once

#include "point/point.hpp"
#include "common_math_operations/common_math_operations.hpp"

namespace geometry
{

struct Vector_t
{
    double x = std::numeric_limits<double>::quiet_NaN();
    double y = std::numeric_limits<double>::quiet_NaN(); 
    double z = std::numeric_limits<double>::quiet_NaN();

    Degeneracy_t degeneracy = Degeneracy_t::POIZON;


    Vector_t()
    {
        degeneracy = Degeneracy_t::INVALID;
    }

    Vector_t (const double x_, const double y_, const double z_) : x(x_), y(y_), z(z_)
    {
        if (std::isnan(x) || std::isnan(y) || std::isnan(z))
            degeneracy = Degeneracy_t::INVALID;
        else if (equal_eps (x, 0.0) && equal_eps (y, 0.0) && equal_eps (z, 0.0))
            degeneracy = Degeneracy_t::NULL_VECTOR;
        else  
            degeneracy = Degeneracy_t::NONE;
    }

    Vector_t (const Point_t& point) : x(point.x), y(point.y), z(point.z)
    {
        if (point.degeneracy == Degeneracy_t::INVALID)
            degeneracy = Degeneracy_t::INVALID;
        else if (equal_eps (point.x, 0.0) && equal_eps (point.y, 0.0) && equal_eps (point.z, 0.0))
            degeneracy = Degeneracy_t::NULL_VECTOR;
        else 
            degeneracy = Degeneracy_t::NONE;
    }

    bool operator== (const Vector_t& rhs) const
    {
        return (equal_eps(x, rhs.x) && equal_eps(y, rhs.y) && equal_eps(z, rhs.z));
    }

    Vector_t operator+ (const Vector_t& rhs) const 
    {
        Vector_t sum (x + rhs.x, y + rhs.y, z + rhs.z);
        return sum;
    }

    Vector_t operator-() const
    {
        Vector_t negation (-x, -y, -z);
        return negation;
    }

    Vector_t operator- (const Vector_t& rhs) const 
    {
        return operator+ (-rhs);
    }

    bool is_collinear_to (const Vector_t& vec) const
    {
        return (equal_eps (((*this) % vec).squared_length(), 0.0));
    }

    Vector_t operator* (const double rhs) const 
    {
        return Vector_t{x * rhs, y * rhs, z * rhs};
    }

    double operator*  (const Vector_t& rhs) const 
    {
        return (x * rhs.x + y * rhs.y + z * rhs.z);
    }

    Vector_t operator%  (const Vector_t& rhs) const
    {
        return (Vector_t {y * rhs.z - z * rhs.y, 
                        -(x * rhs.z - z * rhs.x), 
                          x * rhs.y - y * rhs.x});
    }

    double squared_length() const 
    {
        return (sqr (x) + sqr (y) + sqr (z));
    }

    Vector_t normalize() const
    {
        if (degeneracy == Degeneracy_t::INVALID || degeneracy == Degeneracy_t::NULL_VECTOR)
            return *this;
        
        const double norm = sqrt (squared_length());
        Vector_t retVal {x/norm, y/norm, z/norm};
        return retVal;
    }
};

} //geometry