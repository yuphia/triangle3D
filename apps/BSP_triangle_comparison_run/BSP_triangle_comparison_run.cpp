#include "BSP_tree/BSP_tree.hpp"
#include <cassert>

int main()
{
    size_t amount = 0;
    std::cin >> amount;
    assert (std::cin.good());

    std::list <geometry::AABB_Triag_index> triangles{};

    double x, y, z;
    for (size_t i = 0; i < amount; i++)
    {
        std::cin >> x >> y >> z;
        assert (std::cin.good());
        geometry::Point_t p0 {x, y, z};

        std::cin >> x >> y >> z;
        assert (std::cin.good());
        geometry::Point_t p1 {x, y, z};
 
        std::cin >> x >> y >> z;
        assert (std::cin.good());
        geometry::Point_t p2 {x, y, z};        

        geometry::Triangle_t triangle {p0, p1, p2};

        geometry::AABB_t aabb {triangle};
        geometry::AABB_joint_Triangle_t triang_and_aabb {triangle, aabb};

        geometry::AABB_Triag_index t = std::make_pair (triang_and_aabb, i);
        triangles.push_back (t);
    }

    geometry::BSP_tree tree {triangles};
    tree.run_algo();

    return 0;
}