#pragma once

#include "triangle/triangle.hpp"
#include <algorithm>

namespace geometry
{

class AABB_t
{
private: 
    Point_t pMin;
    Point_t pMax;

public:
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
public:    
    Triangle_t triangle;
    AABB_t aabb;

    AABB_joint_Triangle_t (Triangle_t triangle_, AABB_t aabb_) : triangle{triangle_}, aabb{aabb_}{};
};

} // geometry