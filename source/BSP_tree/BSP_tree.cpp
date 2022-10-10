#include "BSP_tree/BSP_tree.hpp"
#include <cassert>
#include <unistd.h>

namespace geometry
{

void BSP_tree::run_algo ()
{
    root.run_algo (candidates, already_intersected);
}

void BSP_tree_node::run_algo (std::vector<AABB_Triag_index>& candidates, std::unordered_map<int, int>& already_intersected)
{
    if (triangles.size() <= 1 && candidates.size() <= 1)
        return;

    int intersected = 0;

    bool does_splitter_intersect = false;

    bool found_splitter = false;
    auto it = candidates.begin();
    for (auto it_ender = it; it_ender != candidates.end (); ++it_ender)
    {
        ++it;
        if(it->first.triangle.degeneracy == Degeneracy_t::NONE)
        {
            it_ender = --candidates.end();
            found_splitter = true;
        }
    }

    if (!found_splitter)
    {
        run_algo_n_squared (candidates, already_intersected);
        return;
    }

    Triangle_t triag {it->first.triangle.points[0], it->first.triangle.points[1], it->first.triangle.points[2]};
    AABB_joint_Triangle_t splitter {triag, it->first.get_AABB()};
    int splitter_number = it->second;

    candidates.erase (it);

    Plane_t splitter_plane {splitter.triangle.points[0], 
                            splitter.triangle.points[1], 
                            splitter.triangle.points[2]};

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
            if (it_hash == already_intersected.end() && AABB_joint_Triangle_t::overlap_AABB (splitter, t.first) == true)
                if (do_triangles_intersect (splitter.triangle, t.first.triangle))
                {
                    already_intersected.insert ({t.second, t.second});
                    std::cout << t.second << std::endl;
                    does_splitter_intersect = true;
                }
        }
    }

    auto it1 = already_intersected.find (splitter_number);   
    if (it1 == already_intersected.end() && does_splitter_intersect == true)
    {
        already_intersected.insert ({splitter_number, splitter_number});
        std::cout << splitter_number << std::endl;  
    }

    if ( (static_cast<int> (candidates.size())/2 < intersected) ||
        ((static_cast<int> (front.size()) - 150 < intersected) &&
         (static_cast<int>  (back.size()) - 150 < intersected)))
    {    
        run_algo_n_squared (candidates, already_intersected);
        return;
    }

    BSP_tree_node front_node {front};
    BSP_tree_node  back_node { back};

    front_node.run_algo (front, already_intersected);
    back_node. run_algo (back, already_intersected);

}

void run_algo_n_squared (std::vector<AABB_Triag_index> triangles, std::unordered_map<int, int>& already_intersected)
{
    assert (static_cast<bool> (std::cin));

    std::list<AABB_Triag_index> triangle_list_unintersected;
    std::vector<AABB_Triag_index> triangle_vector_intersected;

    for (auto &x : triangles)
    {
        bool is_intersected_at_all = false;
        bool is_curr_intersected = false;

        auto it_in_hash = already_intersected.find (x.second);
        if (it_in_hash == already_intersected.end())
        {
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
                            triangle_list_unintersected.erase (list_iter);   

                            std::cout << list_iter->second << std::endl;
                            break;
                        }
                        else
                            ++list_iter;
                    }
                    else
                        ++list_iter;
                }

            if (is_intersected_at_all == false)
            {   
                auto vector_iter = triangle_vector_intersected.begin();
                for (; vector_iter != triangle_vector_intersected.end(); ++vector_iter)
                {
                    if (geometry::AABB_joint_Triangle_t::overlap_AABB (x.first, vector_iter->first) == true)
                    {
                        is_curr_intersected = geometry::do_triangles_intersect (x.first.triangle, vector_iter->first.triangle);
                        if (is_curr_intersected == true)
                        {
                            triangle_vector_intersected.push_back (x);
                            std::cout << x.second << std::endl;
                            already_intersected.insert ({x.second, x.second});
                            is_intersected_at_all = true;
                            break;
                        }
                    }
                }
            }
            else 
            {
                std::cout << x.second << std::endl;
                triangle_vector_intersected.push_back (x);
                already_intersected.insert ({x.second, x.second});
            }

            if (!is_intersected_at_all)
                triangle_list_unintersected.push_back (x);
        }
    }   


}

} //geometry