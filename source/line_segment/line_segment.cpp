#include "line_segment/line_segment.hpp"


namespace geometry 
{

    Line_segment_t::Line_segment_t (const Point_t& p0_, const Point_t& p1_) : 
                                                                              p0{p0_}, p1{p1_}
    {
        if (p0.degeneracy == Degeneracy_t::INVALID || p1.degeneracy == Degeneracy_t::INVALID)
            degeneracy = Degeneracy_t::INVALID;
        else if (p0 == p1)
            degeneracy = Degeneracy_t::POINT; 
        else
            degeneracy = Degeneracy_t::NONE;
    }
/*
    bool Line_segment_t::operator^ (const Line_segment_t& rhs) {
        
    }*/

} //geometry