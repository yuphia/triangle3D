#include "triangle/triangle.hpp"   
#include <cmath> 


namespace geometry
{

    Triangle_t::Triangle_t (const Point_t& p0_, const Point_t& p1_, const Point_t& p2_) : p0(p0_), p1(p1_), p2(p2_) 
    {
        if (p0.degeneracy == Degeneracy_t::INVALID || p1.degeneracy == Degeneracy_t::INVALID || p2.degeneracy == Degeneracy_t::INVALID)
            degeneracy = Degeneracy_t::INVALID;
        else if (p0 == p1 && p1 == p2)
            degeneracy = Degeneracy_t::POINT;
        else if ( (Vector_t{p1} - Vector_t{p0}).is_collinear_to(Vector_t{p2} - Vector_t{p0}) )
            degeneracy = Degeneracy_t::LINE_SEGMENT;
        else 
            degeneracy = Degeneracy_t::NONE;
    }


    inline bool Triangle_t::operator == (const Triangle_t& rhs) const {
        return ((p0 == rhs.p0) && (p1 == rhs.p1) && (p2 == rhs.p2));
    }
    
}//geometry