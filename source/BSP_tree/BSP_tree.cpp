#include "BSP_tree/BSP_tree.hpp"
#include <cassert>
#include <unistd.h>

namespace geometry
{

std::vector<int> BSP_tree::run_algo ()
{
    root.run_algo (candidates, already_intersected);

    std::vector<int> result = {already_intersected.begin(), already_intersected.end()};

    return result;
}

void BSP_tree_node::run_algo (std::vector<AABB_Triag_index>& candidates, std::unordered_set<int>& already_intersected)
{
    if (candidates.size() <= 1)
        return;

    size_t intersected = 0;
    bool does_splitter_intersect = false;

    bool found_splitter = false;
    auto it_and_bool = find_splitter (candidates);

    found_splitter = it_and_bool.second;

    if (!found_splitter)
    {
        run_algo_n_squared (candidates, already_intersected);
        return;
    }

    AABB_Triag_index splitter = *(it_and_bool.first);

    candidates.erase (it_and_bool.first);

    intersected += bisect_and_print_intersected (candidates, splitter, already_intersected, does_splitter_intersect);

    auto it1 = already_intersected.find (splitter.second);   
    if (it1 == already_intersected.end() && does_splitter_intersect)
    {
        already_intersected.insert (splitter.second);
    }

    if ((candidates.size()/2 < intersected) ||
        ((front.size() - 150 < intersected) && (back.size() - 150 < intersected)))
    {  
        run_algo_n_squared (candidates, already_intersected);
        return;
    }

    BSP_tree_node front_node;
    BSP_tree_node  back_node;

    front_node.run_algo (front, already_intersected);
    back_node.run_algo  (back, already_intersected);

}

Find_res_set_bool_t BSP_tree_node::find_splitter (std::vector<AABB_Triag_index>& candidates)
{
    bool found_splitter = false;
    auto degeneracy_check = [](AABB_Triag_index x) {return x.first.triangle.degeneracy == Degeneracy_t::NONE;};

    auto it = std::find_if (candidates.begin(), candidates.end(), degeneracy_check);

    if (it != candidates.end())
        found_splitter = true;

    return {it, found_splitter};
}

int BSP_tree_node::bisect_and_print_intersected (std::vector<AABB_Triag_index>& candidates, const AABB_Triag_index& splitter, 
                                                 std::unordered_set<int>& already_intersected, bool& does_splitter_intersect)
{
    int intersected = 0;
    Plane_t splitter_plane {splitter.first.triangle.points[0], 
                            splitter.first.triangle.points[1], 
                            splitter.first.triangle.points[2]};


    for (auto& t : candidates)
    {
        if  (
             is_triangle_in_negative_halfspace_relative_to_plane (t.first.triangle, splitter_plane)
            )
        {
            back.push_back (t);
        }
        else if (
                 is_triangle_in_positive_halfspace_relative_to_plane (t.first.triangle, splitter_plane)
                )
        {
            front.push_back(t);
        }
        else
        {
            back.push_back (t);
            front.push_back (t);
            
            intersected++;
            if (AABB_joint_Triangle_t::overlap_AABB (splitter.first, t.first))
            {
                if (do_triangles_intersect (splitter.first.triangle, t.first.triangle))
                {
                    already_intersected.insert (t.second);
                    does_splitter_intersect = true;
                }
            }
        }
    }

    return intersected;
}

void run_algo_n_squared (std::vector<AABB_Triag_index> triangles, std::unordered_set<int>& already_intersected)
{
    assert (static_cast<bool> (std::cin));

    std::list<AABB_Triag_index> triangle_list_unintersected;
    std::vector<AABB_Triag_index> triangle_vector_intersected;

    for (auto &x : triangles)
    {
        bool is_intersected_at_all = false;
        bool is_curr_intersected = false;
        is_intersected_at_all = check_intersection_with_all_unintersected (x, triangle_list_unintersected, triangle_vector_intersected, already_intersected);

        if (!is_intersected_at_all)   
            is_intersected_at_all = check_intersection_with_intersected (x, triangle_list_unintersected, triangle_vector_intersected, already_intersected);
        else 
        {
            already_intersected.insert (x.second);

            triangle_vector_intersected.push_back (x);
        }

        if (!is_intersected_at_all)
        {
            triangle_list_unintersected.push_back (x);
        }
    }   
}

bool check_intersection_with_all_unintersected (AABB_Triag_index& x, 
                                                std::list<AABB_Triag_index>& triangle_list_unintersected,
                                                std::vector<AABB_Triag_index> triangle_vector_intersected,
                                                std::unordered_set<int>& already_intersected)
{
    bool is_curr_intersected = false;
    bool is_intersected_at_all = false;

    for (auto list_iter = triangle_list_unintersected.begin(); list_iter != triangle_list_unintersected.end();)
    {
        if (geometry::AABB_joint_Triangle_t::overlap_AABB (x.first, list_iter->first))
        {
            is_curr_intersected = geometry::do_triangles_intersect (x.first.triangle, list_iter->first.triangle);
            if (is_curr_intersected)
            {
                is_intersected_at_all = true;
                triangle_vector_intersected.push_back (*list_iter);

                already_intersected.insert (list_iter->second);

                auto it_to_erase = list_iter;
                list_iter++;
                triangle_list_unintersected.erase (it_to_erase);   
            }
            else
                ++list_iter;
        }
        else
            ++list_iter;
    }
    return is_intersected_at_all;
}

bool check_intersection_with_intersected (const AABB_Triag_index& x, 
                                          std::list<AABB_Triag_index>& triangle_list_unintersected,
                                          std::vector<AABB_Triag_index> triangle_vector_intersected,
                                          std::unordered_set<int>& already_intersected)
{
    bool is_curr_intersected = false;
    bool is_intersected_at_all = false;

    auto vector_iter = triangle_vector_intersected.begin();
    for (; vector_iter != triangle_vector_intersected.end(); ++vector_iter)
    {
        if (geometry::AABB_joint_Triangle_t::overlap_AABB (x.first, vector_iter->first))
        {
            is_curr_intersected = geometry::do_triangles_intersect (x.first.triangle, vector_iter->first.triangle);
            if (is_curr_intersected)
            {
                triangle_vector_intersected.push_back (x);

                already_intersected.insert (x.second);

                is_intersected_at_all = true;
                break;
            }
        }
    }
    return is_intersected_at_all;
}


} //geometry