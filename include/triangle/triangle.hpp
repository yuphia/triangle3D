#include "point/point.hpp"
#include "vector/vector.hpp"


namespace geometry
{

class Triangle_t
{
private:
    Point_t p0, p1, p2 = {};

public:
    Triangle_t (const Point_t& p0_, const Point_t& p1_, const Point_t& p3_);

    inline bool Triangle_t::operator== (const Triangle_t& rhs) const;
}

} // geometry