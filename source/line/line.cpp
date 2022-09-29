#include "line/line.hpp"

namespace geometry
{

    inline bool Line_t::operator== (const Line_t& rhs) const
    {
        return ((direction_vec == rhs.direction_vec) && (point_on_line == rhs.point_on_line));
    }

    Line_t::Line_t (const Point_t& p0, const Point_t& p1) : 
                                                          direction_vec{p1.x - p0.x, p1.y - p0.y, p1.z - p0.z},
                                                          point_on_line{p0}
    {
        if (direction_vec.degeneracy == Degeneracy_t::INVALID || point_on_line.degeneracy == Degeneracy_t::INVALID)
            degeneracy = Degeneracy_t::INVALID;
        else if (direction_vec.degeneracy == Degeneracy_t::NULL_VECTOR)
            degeneracy = Degeneracy_t::POINT;
        else 
            degeneracy = Degeneracy_t::NONE;
    }

    Line_t::Line_t (const Line_segment_t& segment) :
                                             direction_vec{Vector_t{segment.p1} - Vector_t{segment.p0}},
                                             point_on_line{segment.p0}
    {
        if (direction_vec.degeneracy == Degeneracy_t::INVALID || point_on_line.degeneracy == Degeneracy_t::INVALID)
            degeneracy = Degeneracy_t::INVALID;
        else if (direction_vec.degeneracy == Degeneracy_t::NULL_VECTOR)
            degeneracy = Degeneracy_t::POINT;
        else 
            degeneracy = Degeneracy_t::NONE;
    }

    Line_t::Line_t (const Vector_t& direction_vec_, const Point_t& point_on_line_) :
                                                                                    direction_vec{direction_vec_},
                                                                                    point_on_line{point_on_line_}
    {
        if (direction_vec.degeneracy == Degeneracy_t::INVALID || point_on_line.degeneracy == Degeneracy_t::INVALID)
            degeneracy = Degeneracy_t::INVALID;
        else if (direction_vec.degeneracy == Degeneracy_t::NULL_VECTOR)
            degeneracy = Degeneracy_t::POINT;
        else 
            degeneracy = Degeneracy_t::NONE;
    }

    Line_t::Line_t (const Vector_t& direction_vec_, const Vector_t& point_on_line_) :
                                                                                     direction_vec {direction_vec_},
                                                                                     point_on_line {point_on_line_}
    {
        if (direction_vec.degeneracy == Degeneracy_t::INVALID || point_on_line.degeneracy == Degeneracy_t::INVALID)
            degeneracy = Degeneracy_t::INVALID;
        else if (direction_vec.degeneracy == Degeneracy_t::NULL_VECTOR)
            degeneracy = Degeneracy_t::POINT;
        else 
            degeneracy = Degeneracy_t::NONE;
    }

} // geometry