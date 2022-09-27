#pragma once

#include "point/point.hpp"
#include "line/line.hpp"


namespace geometry
{

class Line_segment_t {

public:
    Line_t line;
    double t_min, t_max = std::numeric_limits<double>::quiet_NaN();

    Degeneracy_t degeneracy = Degeneracy_t::POIZON;


    Line_segment_t (const Line_t& l, const double t1, const double t2);

    bool operator^ (const Line_segment_t& rhs);
};

} //geometry