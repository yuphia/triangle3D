#include "triangle/triangle.hpp"   
#include <cmath> 


namespace geometry
{

    Triangle_t::Triangle_t (const Point_t& p0_, const Point_t& p1_, const Point_t& p2_) : points{p0_, p1_, p2_} 
    {
        if (points[0].degeneracy == Degeneracy_t::INVALID || 
            points[1].degeneracy == Degeneracy_t::INVALID || 
            points[2].degeneracy == Degeneracy_t::INVALID)
            degeneracy = Degeneracy_t::INVALID;
        else if (points[0] == points[1] && points[1] == points[2])
            degeneracy = Degeneracy_t::POINT;
        else if ( (Vector_t{points[1]} - Vector_t{points[0]}).is_collinear_to(Vector_t{points[2]} - Vector_t{points[0]}) )
            degeneracy = Degeneracy_t::LINE_SEGMENT;
        else 
            degeneracy = Degeneracy_t::NONE;
    }


    inline bool Triangle_t::operator == (const Triangle_t& rhs) const {
        return ((points[0] == rhs.points[0]) && (points[1] == rhs.points[1]) && (points[2] == rhs.points[2]));
    }
    
}//geometry