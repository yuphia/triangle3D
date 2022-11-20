#include "../include/first_app.hpp"

#include "../include/keyboard_movement_controller.hpp"
#include "../include/lve_camera.hpp"
#include "../include/simple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>


// std
#include <array>
#include <cassert>
#include <stdexcept>
#include <chrono>
#include <iostream>

namespace lve 
{

FirstApp::FirstApp(std::vector<LveModel::Vertex>& vertices) { 
    loadGameObjects(vertices); 
}

FirstApp::~FirstApp() {}

void FirstApp::run() {
    
    SimpleRenderSystem simpleRenderSystem {lveDevice, lveRenderer.getSwapChainRenderPass()};
    LveCamera camera{};
    
    auto viewerObject = LveGameObject::createGameObject();
    KeyboardMovementController cameraController{};

    auto currentTime = std::chrono::high_resolution_clock::now();
    while (!lveWindow.shouldClose()) {
        glfwPollEvents();

        auto newTime = std::chrono::high_resolution_clock::now();
        float frameTime =
            std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;

        cameraController.moveInPlaneXZ(lveWindow.getGLFWwindow(), frameTime, viewerObject);
        camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

        float aspect = lveRenderer.getAspectRatio();
        camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 1000.f);

        if (auto commandBuffer = lveRenderer.beginFrame()) {
            lveRenderer.beginSwapChainRenderPass(commandBuffer);

            simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);

            lveRenderer.endSwapChainRenderPass(commandBuffer);
            lveRenderer.endFrame();
        }

        vkDeviceWaitIdle(lveDevice.device());
    }
}

std::unique_ptr<LveModel> createTrianglesModel(LveDevice& device, std::vector<LveModel::Vertex>& vertices) {
    
    LveModel::Builder modelBuilder{};


    modelBuilder.vertices = vertices;
   
    return std::make_unique<LveModel>(device, modelBuilder);
}


void FirstApp::loadGameObjects(std::vector<LveModel::Vertex>& vertices) {
    
    std::shared_ptr<LveModel> lveModel = createTrianglesModel(lveDevice, vertices);
    auto triangles = LveGameObject::createGameObject();
    triangles.model = lveModel;
    triangles.transform.translation = {.0f, .0f, .0f};
    triangles.transform.scale = {1.0f, 1.0f, 1.0f};
    gameObjects.push_back(std::move(triangles));
}


} //namespace lve