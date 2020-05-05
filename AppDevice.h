#pragma once 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <algorithm>
#include <set>

#include <stdexcept>
#include <iostream>

struct QueueFamilyIndices {
    int graphicsFamily = -1;
    int presentFamily = -1;

    bool isComplete() {
        return graphicsFamily >= 0 && presentFamily >= 0;
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class AppInstance {
public:
    VkInstance Instance;

    std::vector<const char*> Extensions;
    bool ValidationLayers;
    const std::vector<const char*> ValidationLayersNames = { "VK_LAYER_KHRONOS_validation" };


    void init(const std::vector<const char*>& extensions, bool enableValidationLayers);
    void cleanup();

private:
    void initInstance();
    void initDebugMessenger();

    bool checkValidationSupport();

    // gets instance extensions, validation, and window
    std::vector<const char*> getExtensions();

    // debug stuff
    VkDebugUtilsMessengerEXT _debugMessenger;

    // validation layer callback functions
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);

    VkResult CreateDebugUtilsMessengerEXT(
        VkInstance instance, 
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, 
        VkDebugUtilsMessengerEXT* pDebugMessenger);

    void DestroyDebugUtilsMessengerEXT(
        VkInstance instance,
        VkDebugUtilsMessengerEXT debugMessenger,
        const VkAllocationCallbacks* pAllocator);

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

};

class AppDevice {
public:
    AppInstance* Instance;
    GLFWwindow* Window;

    VkPhysicalDevice PhysicalDevice;
    VkDevice Device;
    VkSurfaceKHR Surface;
    VkQueue GraphicsQueue;
    VkQueue PresentQueue;

    VkSampleCountFlagBits DeviceMsaaSamples = VK_SAMPLE_COUNT_1_BIT;
    QueueFamilyIndices DeviceQueueFamilyIndices;

    bool FramebufferResized;

    void init(AppInstance* instance, GLFWwindow* window, const std::vector<const char*>& extensions);
    void cleanup();

    SwapChainSupportDetails getSwapChainSupportDetails();

private:
    std::vector<const char*> _deviceExtensions;

    void initDevice();

    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSurface();

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);

    VkSampleCountFlagBits getMaxUsableSampleCount();

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
};

class AppWindow {
public:
    GLFWwindow* Window;
    const int Width = 800;
    const int Height = 600;

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    void init();
    void cleanup();

    void getWindowSize(int* width, int* height);
    bool windowClosing();

    bool Resized = false;

    std::vector<const char*> DeviceExtensions;
    std::vector<const char*> InstanceExtensions;
};

class AppSurface {
public:
    AppWindow* Window;

    VkSurfaceKHR Surface;

    void init();
    void cleanup();
};



class DebugLayers {

};
