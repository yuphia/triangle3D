#include "../../Vulkan/include/first_app.hpp"
#include "../../include/BSP_tree/BSP_tree.hpp"
#include "BSP_tree/BSP_tree.hpp"
#include <cassert>

int main()
{
    size_t amount = 0;
    std::cin >> amount;
    assert (std::cin.good());

    std::vector <geometry::AABB_Triag_index> triangles{};
    
    std::vector<lve::LveModel::Vertex> vertices{};
    glm::vec3 blue = {.05f, .05f, .9f};
    
    double x, y, z;

    for (size_t i = 0; i < amount; i++)
    {
        std::cin >> x >> y >> z;
        assert (static_cast<bool> (std::cin));
        geometry::Point_t p0 {x, y, z};
        
        lve::LveModel::Vertex v1;
        v1.position = {x, y, z};
        v1.color = blue;


        std::cin >> x >> y >> z;
        assert (static_cast<bool> (std::cin));
        geometry::Point_t p1 {x, y, z};
        
        lve::LveModel::Vertex v2;
        v2.position = {x, y, z};
        v2.color = blue;


        std::cin >> x >> y >> z;
        assert (static_cast<bool> (std::cin));
        geometry::Point_t p2 {x, y, z};     
        
        lve::LveModel::Vertex v3;
        v3.position = {x, y, z};
        v3.color = blue;


        glm::vec3 normal = glm::normalize(glm::cross((v2.position - v1.position), (v3.position - v1.position)));
        v1.normal = normal;
        v2.normal = normal;
        v3.normal = normal;

        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);


        geometry::Triangle_t triangle {p0, p1, p2};

        geometry::AABB_t aabb {triangle};
        geometry::AABB_joint_Triangle_t triang_and_aabb {triangle, aabb};

        geometry::AABB_Triag_index t = std::make_pair (triang_and_aabb, i);
        triangles.push_back (t);
    }

    geometry::BSP_tree tree {triangles};
    std::vector<int> intersected_indices = tree.run_algo();
    
    glm::vec3 red {.8f, .0f, .0f};
    size_t sz = intersected_indices.size();
    for (size_t i = 0; i < sz; i++) {
        vertices[3 * intersected_indices[i] + 0].color = red;
        vertices[3 * intersected_indices[i] + 1].color = red;
        vertices[3 * intersected_indices[i] + 2].color = red;
    }

    lve::FirstApp app{vertices};

    try {
        app.run();
    } 
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
