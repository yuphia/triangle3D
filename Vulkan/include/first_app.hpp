#pragma once

#include "lve_window.hpp"
#include "lve_game_object.hpp"
#include "lve_device.hpp"
#include "lve_renderer.hpp"

//std
#include <memory>
#include <vector>
#include <set>
#include <stdexcept>

namespace lve 
{

class FirstApp {

public:
    static constexpr int WIDTH  = 800;
    static constexpr int HEIGHT = 600;

    FirstApp(std::vector<LveModel::Vertex>& vertices);
    ~FirstApp();

    FirstApp (const FirstApp &) = delete;           //avoid dangling
    FirstApp &operator=(const FirstApp &) = delete; //avoid dangling


    void run();

private:
    //void loadGameObjects();
    void loadGameObjects(std::vector<LveModel::Vertex>& vertices);
    
    LveWindow lveWindow {WIDTH, HEIGHT, "Hello, Vulkan"};
    LveDevice lveDevice {lveWindow};
    
    LveRenderer lveRenderer{lveWindow, lveDevice};

    std::vector<LveGameObject> gameObjects;
};

} // namespace lve