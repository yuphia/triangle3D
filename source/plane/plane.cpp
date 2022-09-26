#include <cmath> 
#include "plane/plane.hpp"   
    
    
namespace geometry
{

    Plane_t::Plane_t (const Point_t& pt1, const Vector_t& vec1, const Vector_t& vec2) {
        Vector_t n = vec1 % vec2;
        normal = n.normalize();
        d = (-normal) * Vector_t (pt1);
    }

    Plane_t::Plane_t (const Point_t& pt, const Line_t& line) {
        Plane_t (line.point_on_line, line.direction_vec, line.direction_vec - Vector_t (pt));
    }

    Plane_t::Plane_t (const Point_t& pt1, const Point_t& pt2, const Point_t& pt3) {
        Plane_t (pt1, Vector_t(pt2) - Vector_t(pt1), Vector_t(pt3) - Vector_t(pt1));
    }

    Plane_t::Plane_t (const Point_t& pt, const Vector_t& n) {
        normal = n.normalize();
        d = (-normal) * Vector_t (pt);
    }

    Plane_t::Plane_t (const double A, const double B, const double C, const double D) {
        Vector_t n (A, B, C);
        normal = n.normalize();

        d = D / sqrt (sqr(A) + sqr(B) + sqr(C));
    }

    bool Plane_t::operator| (const Plane_t& rhs) const {
        return (rhs.normal == normal);
    }

    bool Plane_t::operator== (const Plane_t& rhs) const {
        return ((normal == rhs.normal) && (d == rhs.d));
    }

}//geometry