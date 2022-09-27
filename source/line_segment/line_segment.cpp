#include "line_segment/line_segment.hpp"


namespace geometry 
{

    Line_segment_t::Line_segment_t (const Line_t& l, const double t1, const double t2) : 
                                                                                         line{l.point_on_line, l.direction_vec}
    {
        if ( line.degeneracy == Degeneracy_t::INVALID || std::isnan(t1) || std::isnan(t2) )
            degeneracy = Degeneracy_t::INVALID;
        else if (line.degeneracy == Degeneracy_t::POINT)
            degeneracy = Degeneracy_t::POINT; //handle as a point using line.point as a product of degeneration
        else
            degeneracy = Degeneracy_t::NONE;
        
        if (equal_eps (t1, t2)) {
            t_min = t1;
            t_max = t2;
            degeneracy = Degeneracy_t::POINT_ON_LINE; //handle as a point using ->  <point> := <point_on_line> + <t_min> * <direction_vec>
                                                      // а вообще можно забить на это хуй
        }
        else if (t1 < t2) {
            t_min = t1;
            t_max = t2;
        }
        else {
            t_min = t2;
            t_max = t1;
        }
    }

    bool Line_segment_t::operator^ (const Line_segment_t& rhs) {
        return (! ((t_max < rhs.t_min) || (t_min > rhs.t_max)) );
    }

} //geometry