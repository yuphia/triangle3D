#include "line/line.hpp"

namespace geometry
{

    inline bool Line_t::operator== (const Line_t& rhs) const
    {
        return ((direction_vec == rhs.direction_vec) && (point_on_line == rhs.point_on_line));
    }

    Line_t::Line_t (const Point_t& a, const Point_t& b)
    {
        Vector_t tmp_point_on_line = {a};
        point_on_line = tmp_point_on_line;
        
        Vector_t tmp_direction_vec = {b.x - a.x, b.y - a.y, b.z - a.z};
        direction_vec = tmp_direction_vec;
    }

    Line_t::Line_t (const Point_t& point_on_line_, const Vector_t& direction_vec_)
    {
        direction_vec = direction_vec;
        Vector_t tmp {point_on_line};
        point_on_line = tmp;
    }

    Line_t::Line_t (const Vector_t& point_on_line_, const Vector_t& direction_vec_)
    { 
        point_on_line = point_on_line_;
        direction_vec = direction_vec_;
    }

} // geometry