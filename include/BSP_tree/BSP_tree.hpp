#pragma once

#include "Triangle_intersection_algorithm/Triangle_intersection_algorithm.hpp"
#include <vector>
#include <unordered_map>
#include <list>

namespace geometry
{

using AABB_Triag_index = std::pair <AABB_joint_Triangle_t, int>;

class BSP_tree_node
{
private:
    std::vector<AABB_Triag_index> triangles;

    std::vector<AABB_Triag_index> front;
    std::vector<AABB_Triag_index> back;

    std::vector<AABB_Triag_index>::iterator find_splitter (std::vector<AABB_Triag_index>& candidates, bool& found_splitter);
    int bisect_and_print_intersected (std::vector<AABB_Triag_index>& candidates, const AABB_Triag_index& splitter, 
                                      std::unordered_map<int, int>& already_intersected, bool& does_splitter_intersect);

public:
    void run_algo (std::vector<AABB_Triag_index>& candidates, std::unordered_map<int, int>& already_intersected);
    BSP_tree_node (std::vector<AABB_Triag_index>& triangles_) : triangles{}
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
    std::vector<AABB_Triag_index> candidates;
    std::unordered_map<int, int> already_intersected;

public:

    BSP_tree (std::vector<AABB_Triag_index>& all_triangles) : 
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

void run_algo_n_squared (std::vector<AABB_Triag_index> triangles, std::unordered_map<int, int>& already_intersected);
bool check_intersection_with_all_unintersected (AABB_Triag_index& x, 
                                                std::list<AABB_Triag_index>& triangle_list_unintersected,
                                                std::vector<AABB_Triag_index> triangle_vector_intersected,
                                                std::unordered_map<int, int>& already_intersected);
bool check_intersection_with_intersected (AABB_Triag_index& x, 
                                          std::list<AABB_Triag_index>& triangle_list_unintersected,
                                          std::vector<AABB_Triag_index> triangle_vector_intersected,
                                          std::unordered_map<int, int>& already_intersected);
} // geometry
