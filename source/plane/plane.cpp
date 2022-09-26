#include "plane/plane.hpp"   
#include <cmath> 
    
    
namespace geometry
{

    Plane_t::Plane_t (const Point_t& pt1, const Vector_t& vec1, const Point_t& vec2) {
        Vector_t n = cross (vec1, vec2);
        normal = n.normalize();

        d = dot (-normal, Vector_t (pt1));
    }

    Plane_t::Plane_t (const Point_t& pt, const Line_t& line) {
        Plane_t (line.point_on_line, line.direction_vec, line.direction_vec - Vector_t (pt));
    }

    Plane_t::Plane_t (const Point_t& pt1, const Point_t& pt2, const Point_t& pt3) {
        Plane_t (p1, Vector_t(p2) - Vector_t(p1), Vector_t(p3) - Vector_t(p1));
    }

    Plane_t::Plane_t (const Point_t& pt, const Vector_t& n) {
        normal = n.normalize();
        d = dot (-normal, Vector_t (pt));
    }

    Plane_t::Plane_t (const double A, const double B, const double C, const double D) {
        Vector_t n (A, B, C);
        normal = n.normalize();

        d = D / sqrt (sqr(A) + sqr(B) + sqr(C));
    }

    inline bool Plane_t::operator|| (const Plane_t& rhs) const {
        return (rhs.n == n);
    }

    inline bool Plane_t::operator== (const Plane_t& rhs) const {
        return ((normal == rhs.normal) && (d == rhs.d));
    }

}