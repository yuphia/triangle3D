#pragma once

#include "triangle/triangle.hpp"
#include <algorithm>

namespace geometry
{

class AABB_t
{
public:
    Point_t pMin;
    Point_t pMax;

    AABB_t (const Triangle_t& triangle);
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

    AABB_joint_Triangle_t (Triangle_t triangle_, AABB_t aabb_) : aabb{aabb_}, triangle{triangle_}{};

    static bool overlap_AABB (const AABB_joint_Triangle_t& lhs, const AABB_joint_Triangle_t& rhs) 
    {
        return AABB_t::overlap (lhs.aabb    , rhs.aabb);
    }
};

} // geometry