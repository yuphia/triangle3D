#pragma once

#include "vector_geom/vector_geom.hpp"
#include "line_segment/line_segment.hpp"

namespace geometry
{

struct Line_t
{
    Vector_t direction_vec;
    Vector_t point_on_line;

    Degeneracy_t degeneracy = Degeneracy_t::POIZON;

    Line_t (const Point_t& p0, const Point_t& p1);
    Line_t (const Line_segment_t& segment);
    Line_t (const Vector_t& direction_vec_, const Point_t& point_on_line_);
    Line_t (const Vector_t& direction_vec_, const Vector_t& point_on_line_);
    Line_t ()
    {
        degeneracy = Degeneracy_t::INVALID;
    }

    bool operator== (const Line_t& rhs) const;    
};

} // geometry
