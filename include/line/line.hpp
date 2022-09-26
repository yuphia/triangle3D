#pragma once

#include "vector/vector.hpp"

namespace geometry
{

class Line_t
{
public:
    Vector_t direction_vec;
    Vector_t point_on_line;

    Line_t (const Point_t& a, const Point_t& b);
    Line_t (const Point_t& point_on_line_, const Vector_t& direction_vec_);
    Line_t (const Vector_t& point_on_line_, const Vector_t& direction_vec_);

    inline bool operator== (const Line_t& rhs) const;    
};

} // geometry
