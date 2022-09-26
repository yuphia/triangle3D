#include "line_segment/line_segment.hpp"


namespace geometry 
{

    Line_segment_t::Line_segment_t (const Line_t& l, const double t1, const double t2) {
        
        if (equal_eps (t1, t2)) {
            t_min = t1;
            t_max = t2;
            //degenerate to point
        }
        else if (t1 < t2) {
            t_min = t1;
            t_max = t2;
        }
        else {
            t_min = t2;
            t_max = t1;
        }

        line.point_on_line = l.point_on_line;
        line.direction_vec = l.direction_vec;
    }

    bool Line_segment_t::operator^ (const Line_segment_t& rhs) {
        return (! ((t_max < rhs.t_min) || (t_min > rhs.t_max)) );
    }

} //geometry