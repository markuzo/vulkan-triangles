#pragma once 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class HelloTriangleApplication {
public: 
    void run();

private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    void createInstance();

    GLFWwindow* _window;

    VkInstance _instance;

    static int _width;
    static int _height;
};

