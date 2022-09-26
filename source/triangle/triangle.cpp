#include "plane/plane.hpp"   
#include <cmath> 


namespace geometry
{

    Triangle_t::Triangle_t (const Point_t& p0_, const Point_t& p1_, const Point_t& p3_) : p0(p0_), p1(p1_), p2(p2_) {}

    inline bool Triangle_t::operator == (const Triangle& rhs) const {
        return ((p0 == rhs.p0) && (p1 == rhs.p1) && (p2 == rhs.p2));
    }
    
}//geometry