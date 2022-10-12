#pragma once

#include "line/line.hpp"

namespace geometry
{

struct Plane_t {
    Vector_t normal;
    double d = std::numeric_limits<double>::quiet_NaN();
    
    Degeneracy_t degeneracy = Degeneracy_t::POIZON;


    Plane_t (const Point_t& pt, const Vector_t& vec1, const Vector_t& vec2);
    
    Plane_t (const Point_t& pt1, const Line_t& line);
    
    Plane_t (const Point_t& pt1, const Point_t& pt2, const Point_t& pt3); //testing done
    
    Plane_t (const Point_t& pt, const Vector_t& n); //testing done
    
    Plane_t (const double A, const double B, const double C, const double D); //testing done

    Plane_t ()
    {
        degeneracy = Degeneracy_t::INVALID;
    }
    
    
    bool operator== (const Plane_t& rhs) const;
    bool operator| (const Plane_t& rhs) const;
};

}//geometry
