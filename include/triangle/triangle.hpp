#include "point/point.hpp"
#include "vector/vector.hpp"


namespace geometry
{

class Triangle_t
{

public:
    Point_t p0, p1, p2;

    Degeneracy_t degeneracy = Degeneracy_t::POIZON;
    
    Triangle_t (const Point_t& p0_, const Point_t& p1_, const Point_t& p3_);

    inline bool operator== (const Triangle_t& rhs) const;
};

} // geometry