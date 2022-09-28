#pragma once

#include "point/point.hpp"
#include "vector/vector.hpp"


namespace geometry
{

class Line_segment_t {

public:
    Vector_t p0, p1;

    Degeneracy_t degeneracy = Degeneracy_t::POIZON;


    Line_segment_t (const Point_t& p0_, const Point_t& p1_);

    //bool operator^ (const Line_segment_t& rhs);
};

} //geometry