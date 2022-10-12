#pragma once

#include "Triangle_intersection_algorithm/Triangle_intersection_algorithm.hpp"
#include <vector>
#include <unordered_set>
#include <list>

namespace geometry
{

using AABB_Triag_index = std::pair <AABB_joint_Triangle_t, int>;

class BSP_tree_node
{
private:
    std::vector<AABB_Triag_index> front;
    std::vector<AABB_Triag_index> back;

    std::vector<AABB_Triag_index>::iterator find_splitter (std::vector<AABB_Triag_index>& candidates, bool& found_splitter);
    int bisect_and_print_intersected (std::vector<AABB_Triag_index>& candidates, const AABB_Triag_index& splitter, 
                                      std::unordered_set<int>& already_intersected, bool& does_splitter_intersect);

public:
    void run_algo (std::vector<AABB_Triag_index>& candidates, std::unordered_set<int>& already_intersected);

};

class BSP_tree
{
private:
    
    BSP_tree_node root;
    std::vector<AABB_Triag_index> candidates;
    std::unordered_set<int> already_intersected;

public:

    BSP_tree (std::vector<AABB_Triag_index>& all_triangles)
    {
        for (auto& x : all_triangles)
        {
            candidates.push_back (x);
        }
    };
    
    void run_algo ();
};

void run_algo_n_squared (std::vector<AABB_Triag_index> triangles, std::unordered_set<int>& already_intersected);
bool check_intersection_with_all_unintersected (AABB_Triag_index& x, 
                                                std::list<AABB_Triag_index>& triangle_list_unintersected,
                                                std::vector<AABB_Triag_index> triangle_vector_intersected,
                                                std::unordered_set<int>& already_intersected);
bool check_intersection_with_intersected (AABB_Triag_index& x, 
                                          std::list<AABB_Triag_index>& triangle_list_unintersected,
                                          std::vector<AABB_Triag_index> triangle_vector_intersected,
                                          std::unordered_set<int>& already_intersected);
} // geometry
