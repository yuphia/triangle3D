#include <vector>
#include <array>
#include "point/point.hpp"
#include "vector_geom/vector_geom.hpp"


namespace geometry
{

class Triangle_t
{

public:
    std::array<Point_t, 3> points;
    const size_t nVertices = 3;

    Degeneracy_t degeneracy = Degeneracy_t::POIZON;
    
    Triangle_t (const Point_t& p0_, const Point_t& p1_, const Point_t& p3_);
    Triangle_t ()
    {
        degeneracy = Degeneracy_t::INVALID;
    };

    Triangle_t (const Triangle_t& triag) : points {triag.points[0], triag.points[1], triag.points[2]}{};
    Triangle_t (Triangle_t&& triag) : points {triag.points[0], triag.points[1], triag.points[2]}{}

    Triangle_t& operator= (Triangle_t&& triag)
    {
        for (int i = 0; i < 3; i++)
        {
            points[i] = triag.points[i];
            triag.points[i] = Point_t{};
        }

        triag.degeneracy = Degeneracy_t::POIZON;

        return *this;
    }

    Triangle_t& operator= (const Triangle_t&& triag)
    {
        for (int i = 0; i < 3; i++)
            points[i] = triag.points[i];

        return *this;
    }

    bool operator== (const Triangle_t& rhs) const;
    Point_t get_min_point() const;
    Point_t get_max_point() const;
};

} // geometry