#include "point/point.hpp"

namespace geometry
{

Point_t::Point_t (const double x_, const double y_, const double z_) : x(x_), y(y_), z(z_) {}

inline bool Point_t::operator== (const Point_t& rhs) const
{
    return (equal_eps (x, rhs.x) && equal_eps (y, rhs.y) && equal_eps (z, rhs.z));
}

} //geometry