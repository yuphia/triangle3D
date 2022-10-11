#include "BSP_tree/BSP_tree.hpp"
#include <cassert>
#include <unistd.h>

namespace geometry
{

struct
{
    bool operator()(const AABB_Triag_index &lhs, const AABB_Triag_index &rhs) 
    {
        return lhs.second < rhs.second; // assumes that the implementation uses a flat address space
    }
} custom_less;

void BSP_tree::run_algo ()
{
    root.run_algo (candidates, already_intersected);
    for (auto x : already_intersected)
    {
        std::cout << x.second << std::endl;
    }
}

void BSP_tree_node::run_algo (std::vector<AABB_Triag_index>& candidates, std::map<int, int>& already_intersected)
{
    if (candidates.size() <= 1)
        return;

    int intersected = 0;
    bool does_splitter_intersect = false;

    bool found_splitter = false;
    auto it = find_splitter (candidates, found_splitter);

    if (!found_splitter)
    {
        run_algo_n_squared (candidates, already_intersected);
        return;
    }

    AABB_Triag_index splitter = *it;

    candidates.erase (it);

    intersected += bisect_and_print_intersected (candidates, splitter, already_intersected, does_splitter_intersect);

    auto it1 = already_intersected.find (splitter.second);   
    if (it1 == already_intersected.end() && does_splitter_intersect == true)
    {
        already_intersected.insert ({splitter.second, splitter.second});
    }

    if ((static_cast<int> (candidates.size())/2 < intersected) ||
        ((static_cast<int> (front.size()) - 150 < intersected) && (static_cast<int>  (back.size()) - 150 < intersected)))
    {   
        run_algo_n_squared (candidates, already_intersected);
        return;
    }

    BSP_tree_node front_node;
    BSP_tree_node  back_node;

    front_node.run_algo (front, already_intersected);
    back_node. run_algo (back, already_intersected);

}

std::vector<AABB_Triag_index>::iterator BSP_tree_node::find_splitter (std::vector<AABB_Triag_index>& candidates, bool& found_splitter)
{
    auto it = candidates.begin();
    for (auto it_ender = it; it_ender != candidates.end (); ++it_ender)
    {
        if(it->first.triangle.degeneracy == Degeneracy_t::NONE)
        {
            it_ender = --candidates.end();
            found_splitter = true;
        }
        else
            ++it;
    }

    return it;
}

int BSP_tree_node::bisect_and_print_intersected (std::vector<AABB_Triag_index>& candidates, const AABB_Triag_index& splitter, 
                                                 std::map<int, int>& already_intersected, bool& does_splitter_intersect)
{
    int intersected = 0;
    Plane_t splitter_plane {splitter.first.triangle.points[0], 
                            splitter.first.triangle.points[1], 
                            splitter.first.triangle.points[2]};

    static int i = 0;

    for (auto& t : candidates)
    {
        if (signed_distance (t.first.triangle.points[0], splitter_plane) < -EPS && 
            signed_distance (t.first.triangle.points[1], splitter_plane) < -EPS &&
            signed_distance (t.first.triangle.points[2], splitter_plane) < -EPS)
        {
            back.push_back (t);
        }
        else if (signed_distance (t.first.triangle.points[0], splitter_plane) > EPS &&
                 signed_distance (t.first.triangle.points[1], splitter_plane) > EPS &&
                 signed_distance (t.first.triangle.points[2], splitter_plane) > EPS)
        {
            front.push_back(t);
        }
        else
        {
            back.push_back (t);
            front.push_back (t);
            
            intersected++;
            auto it_hash = already_intersected.find (t.second);
            if (it_hash == already_intersected.end() && AABB_joint_Triangle_t::overlap_AABB (splitter.first, t.first))
            {
                if (do_triangles_intersect (splitter.first.triangle, t.first.triangle))
                {
                    already_intersected.insert ({t.second, t.second});
                    does_splitter_intersect = true;
                }
            }
            else i++;
        }
    }

    return intersected;
}

void run_algo_n_squared (std::vector<AABB_Triag_index> triangles, std::map<int, int>& already_intersected)
{
    std::sort (triangles.begin(), triangles.end(), custom_less);
    assert (static_cast<bool> (std::cin));

    std::list<AABB_Triag_index> triangle_list_unintersected;
    std::vector<AABB_Triag_index> triangle_vector_intersected;

    for (auto &x : triangles)
    {
        bool is_intersected_at_all = false;
        bool is_curr_intersected = false;
        is_intersected_at_all = check_intersection_with_all_unintersected (x, triangle_list_unintersected, triangle_vector_intersected, already_intersected);

        if (is_intersected_at_all == false)   
            is_intersected_at_all = check_intersection_with_intersected (x, triangle_list_unintersected, triangle_vector_intersected, already_intersected);
        else 
        {
            already_intersected.insert ({x.second, x.second});

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
                                                std::map<int, int>& already_intersected)
{
    bool is_curr_intersected = false;
    bool is_intersected_at_all = false;

    for (auto list_iter = triangle_list_unintersected.begin(); list_iter != triangle_list_unintersected.end();)
    {
        if (geometry::AABB_joint_Triangle_t::overlap_AABB (x.first, list_iter->first) == true)
        {
            is_curr_intersected = geometry::do_triangles_intersect (x.first.triangle, list_iter->first.triangle);
            if (is_curr_intersected == true)
            {
                is_intersected_at_all = true;
                triangle_vector_intersected.push_back (*list_iter);

                already_intersected.insert ({list_iter->second, list_iter->second});

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

bool check_intersection_with_intersected (AABB_Triag_index& x, 
                                          std::list<AABB_Triag_index>& triangle_list_unintersected,
                                          std::vector<AABB_Triag_index> triangle_vector_intersected,
                                          std::map<int, int>& already_intersected)
{
    bool is_curr_intersected = false;
    bool is_intersected_at_all = false;

    auto vector_iter = triangle_vector_intersected.begin();
    for (; vector_iter != triangle_vector_intersected.end(); ++vector_iter)
    {
        if (geometry::AABB_joint_Triangle_t::overlap_AABB (x.first, vector_iter->first) == true)
        {
            is_curr_intersected = geometry::do_triangles_intersect (x.first.triangle, vector_iter->first.triangle);
            if (is_curr_intersected == true)
            {
                triangle_vector_intersected.push_back (x);

                already_intersected.insert ({x.second, x.second});

                is_intersected_at_all = true;
                break;
            }
        }
    }

    return is_intersected_at_all;
}


} //geometry