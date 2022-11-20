#pragma once

#include "../point/point.hpp"
#include "../vector_geom/vector_geom.hpp"


namespace geometry
{

struct Line_segment_t {

    Vector_t p0, p1;

    Degeneracy_t degeneracy = Degeneracy_t::POIZON;

    Line_segment_t (const Point_t& p0_, const Point_t& p1_) : p0{p0_}, p1{p1_}
    {
        if (p0.degeneracy == Degeneracy_t::INVALID || p1.degeneracy == Degeneracy_t::INVALID)
            degeneracy = Degeneracy_t::INVALID;
        else if (p0 == p1)
            degeneracy = Degeneracy_t::POINT; 
        else
            degeneracy = Degeneracy_t::NONE;
    }

    Line_segment_t ()
    {
        degeneracy = Degeneracy_t::INVALID;
    }
};

} //geometry