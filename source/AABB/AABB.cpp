#include "AABB/AABB.hpp"

namespace geometry
{

AABB_t::AABB_t (const Triangle_t& triangle) : pMin {triangle.get_min_point()}, pMax {triangle.get_max_point()} {}

} // geometry