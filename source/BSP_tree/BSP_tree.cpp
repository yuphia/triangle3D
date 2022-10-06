#include "BSP_tree/BSP_tree.hpp"
#include <cassert>
#include <unistd.h>

namespace geometry
{

void BSP_tree::run_algo ()
{
    root.run_algo (candidates, already_intersected);
}

void BSP_tree_node::run_algo (std::list<AABB_Triag_index>& candidates, std::unordered_map<int, int>& already_intersected)
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
            
            auto it = already_intersected.find (t.second);
            if (it == already_intersected.end() && AABB_joint_Triangle_t::overlap_AABB (splitter, t.first) == true)
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

//    std::cout <<       "front: " << front.size() << std::endl; 
//    std::cout <<        "back: " <<  back.size() << std::endl;
//    std::cout << "intersected: " <<  intersected << std::endl;

    if ((static_cast<int> (front.size()) - 150 < intersected) &&
        (static_cast<int> (back.size())  - 150 < intersected))
    {    
        run_algo_n_squared (candidates, already_intersected);
        return;
    }

    BSP_tree_node front_node {front};
    BSP_tree_node  back_node { back};

//    sleep (1);
    front_node.run_algo (front, already_intersected);
    back_node. run_algo (back, already_intersected);

}

void run_algo_n_squared (std::list<AABB_Triag_index> triangles, std::unordered_map<int, int>& already_intersected)
{
    assert (std::cin.good());

    auto it_end = triangles.end();
    auto it_hash_end = already_intersected.end();

    for (auto it0 = triangles.begin(); it0 != it_end; ++it0)
    {
        auto is_int_i0 = already_intersected.find (it0->second);
        for (auto it1 = triangles.begin(); it1 != it_end; ++it1)
        {
            if (it0 != it1)
            {
                auto is_int_i1 = already_intersected.find (it1->second);

                if (is_int_i0 == already_intersected.end() || is_int_i1 == already_intersected.end())
                {
                    if (AABB_joint_Triangle_t::overlap_AABB (it0->first, it1->first))
                        if (do_triangles_intersect (it0->first.triangle, it1->first.triangle))
                        {
                            if (is_int_i0 == it_hash_end)
                            {
                                std::cout << it0->second << std::endl;
                                already_intersected.insert ({it0->second, it0->second});
                                is_int_i0 = already_intersected.find (it0->second);
                            }

                            if (is_int_i1 == it_hash_end)
                            {
                                std::cout << it1->second << std::endl;
                                already_intersected.insert ({it1->second, it1->second});
                            }
                        }
                }
            }
        }
    }
}

} //geometry