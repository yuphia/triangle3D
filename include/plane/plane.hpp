#pragma once

#include "../line/line.hpp"

namespace geometry
{

struct Plane_t {
    Vector_t normal;
    double d = std::numeric_limits<double>::quiet_NaN();
    
    Degeneracy_t degeneracy = Degeneracy_t::POIZON;

    Plane_t ()
    {
        degeneracy = Degeneracy_t::INVALID;
    }
    
    Plane_t (const Point_t& pt1, const Point_t& pt2, const Point_t& pt3) : 
                                                                                    normal{ ( (Vector_t(pt2) - Vector_t(pt1)) % (Vector_t(pt3) - Vector_t(pt1)) ).normalize() } 
    {
        if (normal.degeneracy != Degeneracy_t::NONE || pt1.degeneracy == Degeneracy_t::INVALID)
            degeneracy = Degeneracy_t::INVALID;
        else
            degeneracy = Degeneracy_t::NONE;

        d = normal * Vector_t (pt1);
    }

    Plane_t (const Point_t& pt, const Vector_t& n) : 
                                                              normal{(static_cast<Vector_t> (n)).normalize()} 
    {
        if (normal.degeneracy != Degeneracy_t::NONE || pt.degeneracy == Degeneracy_t::INVALID)
            degeneracy = Degeneracy_t::INVALID;
        else
            degeneracy = Degeneracy_t::NONE;

        d = normal * Vector_t (pt);
    }
    
    Plane_t (const double A, const double B, const double C, const double D) :
                                                                                        normal{ (Vector_t{A, B, C}).normalize()}
    {
        if ( normal.degeneracy != Degeneracy_t::NONE || std::isnan(A) || std::isnan(B) 
                                                     || std::isnan(C) || std::isnan(D) )
            degeneracy = Degeneracy_t::INVALID;
        else
            degeneracy = Degeneracy_t::NONE;
        
        d = -(D / sqrt (sqr(A) + sqr(B) + sqr(C)));
    }

    bool operator| (const Plane_t& rhs) const {
        return (rhs.normal == normal);
    }

    bool operator== (const Plane_t& rhs) const {
        return ((normal == rhs.normal) && (d == rhs.d));
    }
};

}//geometry
