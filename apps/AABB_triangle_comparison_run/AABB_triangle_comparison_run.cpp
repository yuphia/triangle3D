#include "Triangle_intersection_algorithm/Triangle_intersection_algorithm.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <set>

namespace
{
    struct pair_less
    {
        const bool operator() (const std::pair <geometry::AABB_joint_Triangle_t, size_t> &lhs, 
                                const std::pair <geometry::AABB_joint_Triangle_t, size_t> &rhs)
        {
            return rhs.second > lhs.second;
        }
    };
}

int main()
{
    size_t amount = 0;
    std::cin >> amount;

    assert (std::cin.good());

    std::vector <std::pair <geometry::AABB_joint_Triangle_t, size_t>> triangle_vector_intersected{};
    std::list <std::pair <geometry::AABB_joint_Triangle_t, size_t>> triangle_list_unintersected{};

    double x, y, z;
    for (size_t i = 0; i < amount; i++)
    {
        std::cin >> x >> y >> z;
        assert (static_cast<bool> (std::cin));
        geometry::Point_t p0 {x, y, z};

        std::cin >> x >> y >> z;
        assert (static_cast<bool> (std::cin));
        geometry::Point_t p1 {x, y, z};
 
        std::cin >> x >> y >> z;
        assert (static_cast<bool> (std::cin));
        geometry::Point_t p2 {x, y, z};        

        geometry::Triangle_t triangle {p0, p1, p2};
        geometry::AABB_t aabb {triangle};
        geometry::AABB_joint_Triangle_t triang_and_aabb {triangle, aabb};
        //triangle_vector_intersected.push_back (std::make_pair (triangle, i));

        bool is_curr_intersected = false;
        bool is_intersected_at_all = false;
        for (auto list_iter = triangle_list_unintersected.begin(); list_iter != triangle_list_unintersected.end();)
        {
            if (geometry::AABB_joint_Triangle_t::overlap_AABB (triang_and_aabb, list_iter->first) == true)
            {
                is_curr_intersected = geometry::do_triangles_intersect (triangle, list_iter->first.triangle);
                if (is_curr_intersected == true)
                {
                    is_intersected_at_all = true;

                    triangle_vector_intersected.push_back (*list_iter);
                    
                    auto it_to_erase = list_iter;
                    ++list_iter;
                    triangle_list_unintersected.erase (it_to_erase);   
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
                if (geometry::AABB_joint_Triangle_t::overlap_AABB (triang_and_aabb, vector_iter->first) == true)
                {
                    is_curr_intersected = geometry::do_triangles_intersect (triangle, vector_iter->first.triangle);
                    if (is_curr_intersected == true)
                    {
                        triangle_vector_intersected.push_back (std::make_pair (triang_and_aabb, i));
                        is_intersected_at_all = true;
                        break;
                    }
                }
            }
        }
        else 
        {
            triangle_vector_intersected.push_back (std::make_pair (triang_and_aabb, i));
        }

        if (!is_intersected_at_all)
        {
            triangle_list_unintersected.push_back (std::make_pair (triang_and_aabb, i));
        }
    }

    std::sort (triangle_vector_intersected.begin(), triangle_vector_intersected.end(), pair_less{});
    for (auto x: triangle_vector_intersected)
    {
        std::cout << x.second << "\n";
    }

    return 0;
}

