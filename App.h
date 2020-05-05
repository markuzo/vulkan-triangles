#pragma once 

#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include "AppDevice.h"
#include "ImageWriter.h"

#include <chrono>
#include <vector>
#include <array>
#include <unordered_map>

struct Vertex {
    glm::vec3 pos;
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
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
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

    bool operator==(const Vertex& other) const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}
};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec2>()(vertex.pos) ^
                   (hash<glm::vec2>()(vertex.color) << 1)) >> 1) ^
                   (hash<glm::vec1>()(vertex.texCoord) << 1);
        }
    };
}

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

class App {
public: 
    void run();

private:
    void initVulkan();
    void mainLoop();
    void cleanup();
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& available);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& available);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void createSwapchain();
    void createImageViews();
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
    void createDescriptorSetLayout();
    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);
    void createRenderPass();
    void createFramebuffers();
    void createCommandPool();
    void createDepthResources();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);
    void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();
    void createColorResources();
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void loadModel();
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createCommandBuffers();
    void createSyncObjects();
    void drawFrame();
    void saveFrame(uint32_t currentImage);
    void updateUniformBuffer(uint32_t currentImage);
    VkCommandBuffer beginSingleTimeCommands();
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
    void transitionImageLayout(VkImage image, VkFormat format, VkAccessFlags sourceAccessFlags, VkAccessFlags destinationAccessFlags, VkImageLayout oldLayout, VkImageLayout newLayout, VkPipelineStageFlags sourceStage, VkPipelineStageFlags destinationStage, VkImageAspectFlags aspectFlags, uint32_t mipLevels); 
    void transitionImageLayout(VkCommandBuffer commandBuffer, VkImage image, VkFormat format, VkAccessFlags sourceAccessFlags, VkAccessFlags destinationAccessFlags, VkImageLayout oldLayout, VkImageLayout newLayout, VkPipelineStageFlags sourceStage, VkPipelineStageFlags destinationStage, VkImageAspectFlags aspectFlags, uint32_t mipLevels); 
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void recreateSwapchain();
    void cleanupSwapchain();

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    AppInstance _appInstance;
    AppWindow _appWindow;
    AppDevice _appDevice;
    ImageWriter _imageWriter;

    VkPhysicalDevice _physicalDevice;
    VkDevice _device;
    VkQueue _graphicsQueue;
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

    std::vector<Vertex> _vertices;
    std::vector<uint32_t> _indices;
    VkBuffer _vertexBuffer;
    VkDeviceMemory _vertexBufferMemory;
    VkBuffer _indexBuffer;
    VkDeviceMemory _indexBufferMemory;
    std::vector<VkBuffer> _uniformBuffers;
    std::vector<VkDeviceMemory> _uniformBuffersMemory;

    VkImage _colorImage;
	VkDeviceMemory _colorImageMemory;
	VkImageView _colorImageView;

    VkImage _depthImage;
    VkImageView _depthImageView;
    VkDeviceMemory _depthImageMemory;

    VkImage _offscreenImage;
    VkDeviceMemory _offscreenImageMemory;
   
    uint32_t _mipLevels;
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
    int _currentImage = 1;

    static const int _maxFramesInFlight;
    static const std::string _modelPath;
    static const std::string _texturePath;
};


