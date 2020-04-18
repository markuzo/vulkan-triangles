#pragma once 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <chrono>
#include <vector>
#include <array>

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

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription = {};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

        attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
};

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

class HelloTriangleApplication {
public: 
    void run();

private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    void createInstance();
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    void setupDebugMessenger();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSurface();
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& available);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& available);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void createSwapchain();
    void createImageViews();
    VkImageView createImageView(VkImage image, VkFormat format);
    void createDescriptorSetLayout();
    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);
    void createRenderPass();
    void createFramebuffers();
    void createCommandPool();
    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createCommandBuffers();
    void createSyncObjects();
    void drawFrame();
    void updateUniformBuffer(uint32_t currentImage);
    VkCommandBuffer beginSingleTimeCommands();
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void recreateSwapchain();
    void cleanupSwapchain();

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    GLFWwindow* _window;

    VkInstance _instance;
    VkPhysicalDevice _physicalDevice;
    VkDevice _device;
    VkQueue _graphicsQueue;
    VkSurfaceKHR _surface;
    VkQueue _presentQueue;

    VkSwapchainKHR _swapchain;
    std::vector<VkImage> _swapchainImages;
    VkFormat _swapchainImageFormat;
    VkExtent2D _swapchainExtent;
    std::vector<VkImageView> _swapchainImageViews;

    VkShaderModule _vertShaderModule;
    VkShaderModule _fragShaderModule;

    VkRenderPass _renderPass;
    VkDescriptorSetLayout _descriptorSetLayout;
    VkPipelineLayout _pipelineLayout;
    VkPipeline _graphicsPipeline;

    std::vector<VkFramebuffer> _swapchainFramebuffers;
    VkCommandPool _commandPool;
    std::vector<VkCommandBuffer> _commandBuffers;
    VkBuffer _vertexBuffer;
    VkDeviceMemory _vertexBufferMemory;
    VkBuffer _indexBuffer;
    VkDeviceMemory _indexBufferMemory;
    std::vector<VkBuffer> _uniformBuffers;
    std::vector<VkDeviceMemory> _uniformBuffersMemory;

    VkImage _textureImage;
    VkImageView _textureImageView;
    VkSampler _textureSampler;
    VkDeviceMemory _textureImageMemory;

    VkDescriptorPool _descriptorPool;
    std::vector<VkDescriptorSet> _descriptorSets;

    std::vector<VkSemaphore> _imageAvailableSemaphores;
    std::vector<VkSemaphore> _renderFinishedSemaphores;
    std::vector<VkFence> _inFlightFences;
    std::vector<VkFence> _imagesInFlight;
    int _currentFrame;
    bool _framebufferResized;

    VkDebugUtilsMessengerEXT _debugMessenger;

    static const int _width;
    static const int _height;
    static const bool _enableValidationLayers;
    static const int _maxFramesInFlight;
    static const std::vector<Vertex> _vertices;
    static const std::vector<uint16_t> _indices;

    const std::vector<const char*> _deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME 
    };

    const std::vector<const char*> _validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    // validation layer callback functions
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

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

