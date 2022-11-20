#include <vector>
#include <array>
#include "point/point.hpp"
#include "vector_geom/vector_geom.hpp"


namespace geometry
{

struct Triangle_t
{
    std::array<Point_t, 3> points;

    Degeneracy_t degeneracy = Degeneracy_t::POIZON;
    
    Triangle_t ()
    {
        degeneracy = Degeneracy_t::INVALID;
    };

    Triangle_t (const Point_t& p0_, const Point_t& p1_, const Point_t& p2_) : points{p0_, p1_, p2_} 
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


    bool operator== (const Triangle_t& rhs) const {
        return ((points[0] == rhs.points[0]) && (points[1] == rhs.points[1]) && (points[2] == rhs.points[2]));
    }

    Point_t get_min_point() const
    {
        double tmpXMin = std::min<double> (points[0].x, points[1].x);
        tmpXMin        = std::min<double> (points[2].x, tmpXMin);
        double tmpYMin = std::min<double> (points[0].y, points[1].y);
        tmpYMin        = std::min<double> (points[2].y, tmpYMin);
        double tmpZMin = std::min<double> (points[0].z, points[1].z);
        tmpZMin        = std::min<double> (points[2].z, tmpZMin);

        Point_t pMin {tmpXMin, tmpYMin, tmpZMin};
        return pMin;
    }
    
    Point_t get_max_point() const
    {
        double tmpXMax = std::max<double> (points[0].x, points[1].x);
        tmpXMax        = std::max<double> (points[2].x, tmpXMax);
        double tmpYMax = std::max<double> (points[0].y, points[1].y);
        tmpYMax        = std::max<double> (points[2].y, tmpYMax);
        double tmpZMax = std::max<double> (points[0].z, points[1].z);
        tmpZMax        = std::max<double> (points[2].z, tmpZMax);

        Point_t pMax {tmpXMax, tmpYMax, tmpZMax};
        return pMax;
    }
};

} // geometry