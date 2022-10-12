#pragma once

#include "point/point.hpp"
#include "vector_geom/vector_geom.hpp"


namespace geometry
{

struct Line_segment_t {

    Vector_t p0, p1;

    Degeneracy_t degeneracy = Degeneracy_t::POIZON;


    Line_segment_t (const Point_t& p0_, const Point_t& p1_);
    Line_segment_t ()
    {
        degeneracy = Degeneracy_t::INVALID;
    }
};

} //geometry