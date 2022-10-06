#pragma once

#include "Triangle_intersection_algorithm/Triangle_intersection_algorithm.hpp"
#include <list>
#include <unordered_map>

namespace geometry
{

using AABB_Triag_index = std::pair <AABB_joint_Triangle_t, int>;

class BSP_tree_node
{
private:
    std::list<AABB_Triag_index> triangles;

    std::list<AABB_Triag_index> front;
    std::list<AABB_Triag_index> back;

public:
    void run_algo (std::list<AABB_Triag_index>& candidates, std::unordered_map<int, int>& already_intersected);
    BSP_tree_node (std::list<AABB_Triag_index>& triangles_) : triangles{}
    {
        for (auto& x : triangles_)
        {
            AABB_t aabb = x.first.get_AABB();
            Triangle_t triangle {x.first.triangle.points[0], x.first.triangle.points[1], x.first.triangle.points[2]};
            AABB_joint_Triangle_t t {triangle, aabb};

            triangles.push_back (std::make_pair (t, x.second));
        }
    };
};

class BSP_tree
{
private:
    
    BSP_tree_node root;
    std::list<AABB_Triag_index> candidates;
    std::unordered_map<int, int> already_intersected;

public:

    BSP_tree (std::list<AABB_Triag_index>& all_triangles) : 
                                            root {all_triangles}
    {
        for (auto& x : all_triangles)
        {
            AABB_t aabb = x.first.get_AABB();
            Triangle_t triangle {x.first.triangle.points[0], x.first.triangle.points[1], x.first.triangle.points[2]};
            AABB_joint_Triangle_t t {triangle, aabb};
            AABB_Triag_index candidate = std::make_pair (t, x.second);
            candidates.push_back (candidate);
        }
    };
    
    void run_algo ();
};

void run_algo_n_squared (std::list<AABB_Triag_index> triangles, std::unordered_map<int, int>& already_intersected);

} // geometry
