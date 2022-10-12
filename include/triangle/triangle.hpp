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
    
    Triangle_t (const Point_t& p0_, const Point_t& p1_, const Point_t& p3_);
    Triangle_t ()
    {
        degeneracy = Degeneracy_t::INVALID;
    };

    bool operator== (const Triangle_t& rhs) const;
    Point_t get_min_point() const;
    Point_t get_max_point() const;
};

} // geometry