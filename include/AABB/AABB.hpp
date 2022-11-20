#pragma once

#include "../triangle/triangle.hpp"
#include <algorithm>

namespace geometry
{

struct AABB_t
{
    Point_t pMin;
    Point_t pMax;

    AABB_t (const Triangle_t& triangle) : pMin {triangle.get_min_point()}, pMax {triangle.get_max_point()} {}

    static bool overlap (const AABB_t& lhs, const AABB_t& rhs)
    {   
        bool are_overlapping =                    lhs.pMax.x - rhs.pMin.x >= 0 && rhs.pMax.x - lhs.pMin.x >= 0;
        are_overlapping      = are_overlapping && lhs.pMax.y - rhs.pMin.y >= 0 && rhs.pMax.y - lhs.pMin.y >= 0;
        are_overlapping      = are_overlapping && lhs.pMax.z - rhs.pMin.z >= 0 && rhs.pMax.z - lhs.pMin.z >= 0;

        return are_overlapping;
    }
};

class AABB_joint_Triangle_t
{
private:
    AABB_t aabb;

public:    
    Triangle_t triangle;

    AABB_joint_Triangle_t (Triangle_t triangle_, AABB_t aabb_) : aabb{triangle_}, triangle{triangle_.points[0], triangle_.points[1], triangle_.points[2]}{};

    static bool overlap_AABB (const AABB_joint_Triangle_t& lhs, const AABB_joint_Triangle_t& rhs) 
    {
        return AABB_t::overlap (lhs.aabb, rhs.aabb);
    }

    const AABB_t& get_AABB() &
    {
        return aabb;
    }
};

} // geometry