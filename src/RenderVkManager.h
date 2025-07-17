#pragma once

#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include <vulkan/vulkan.h>
#include <optional>
#include <stdexcept>
#include <utility> // для std::pair
#include <SDL_vulkan.h>
#include <memory> 
#include <set>
#include <iostream>
#include <map>
#include <algorithm>
#include <chrono>
#include "config.h"
#include "logger.h"
#include "vertex.h"
#include "fmath.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace prism {
    namespace render {

        inline VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
            auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
            if (func != nullptr) {
                return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
            }
            else {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }
        }

        inline void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr) {
                func(instance, debugMessenger, pAllocator);
            }
        }

        struct QueueFamilyIndices {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;

            bool isComplete() {
                return graphicsFamily.has_value() && presentFamily.has_value();
            }
        };

        struct SwapChainSupportDetails {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;
        };


        class RenderVkManager {
        public:
            // === Деструктор и контрруктор ===
            RenderVkManager();
            void init(SDL_Window* window);
            void drawFrame();
            void cleanup();
            void awaitRenderingCompletion();

            bool framebufferResized = false;
            bool windowMinimized = false;

        private:
            void createInstance();
            void setupDebugMessenger();
            void pickPhysicalDevice();
            void createLogicalDevice();
            void createSurface();
            void createSwapChain();
            void createImageViews();
            void createGraphicsPipeline();
            void createRenderPass();
            void createFramebuffers();
            void createCommandPool();
            void createCommandBuffer();
            void createSyncObjects();
            void createVertexBuffer();
            void createIndexBuffer();
            void createDescriptorSetLayout();
            void createUniformBuffers();
            void createDescriptorPool();
            void createDescriptorSets();
            void createTextureImage();
            void createTextureImageView();
            void createTextureSampler();
            void createDepthResources();
            void loadModel();
            void createColorResources();

            void recreateSwapChain();
            void cleanupSwapChain();

            const int MAX_FRAMES_IN_FLIGHT = 2;

            SDL_Window* window;
            VkInstance instance;
            VkDebugUtilsMessengerEXT debugMessenger;
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            VkDevice device;
            VkQueue graphicsQueue;
            VkQueue presentQueue;
            VkSurfaceKHR surface;
            std::vector<VkImageView> swapChainImageViews;

            VkSwapchainKHR swapChain;
            std::vector<VkImage> swapChainImages;
            VkFormat swapChainImageFormat;
            VkExtent2D swapChainExtent;

            VkRenderPass renderPass;
            VkPipelineLayout pipelineLayout;

            VkPipeline graphicsPipeline;
            
            std::vector<VkFramebuffer> swapChainFramebuffers;

            VkCommandPool commandPool;
            std::vector<VkCommandBuffer> commandBuffers;

            std::vector<VkSemaphore> imageAvailableSemaphores;
            std::vector<VkSemaphore> renderFinishedSemaphores;
            std::vector<VkFence> inFlightFences;

            uint32_t currentFrame = 0;
            bool wasRenderingActive = true;

            VkBuffer vertexBuffer;
            VkDeviceMemory vertexBufferMemory;
            VkBuffer indexBuffer;
            VkDeviceMemory indexBufferMemory;

            std::vector<VkBuffer> uniformBuffers;
            std::vector<VkDeviceMemory> uniformBuffersMemory;
            std::vector<void*> uniformBuffersMapped;

            VkDescriptorSetLayout descriptorSetLayout;

            VkDescriptorPool descriptorPool;
            std::vector<VkDescriptorSet> descriptorSets;

            VkImage textureImage;
            VkDeviceMemory textureImageMemory;

            VkImageView textureImageView;
            VkSampler textureSampler;

            VkImage depthImage;
            VkDeviceMemory depthImageMemory;
            VkImageView depthImageView;

            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;

            uint32_t mipLevels;
            
            VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

            VkImage colorImage;
            VkDeviceMemory colorImageMemory;
            VkImageView colorImageView;

            const std::string MODEL_PATH = "models/viking_room.obj";
            const std::string TEXTURE_PATH = "textures/viking_room.png";

            //UniformBufferObject ubo;
            VkCommandBuffer beginSingleTimeCommands();
            void endSingleTimeCommands(VkCommandBuffer commandBuffer);
            void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
            void updateUniformBuffer(uint32_t currentImage);
            bool isWindowReadyForRendering(SDL_Window* window);
            std::vector<const char*> getRequiredExtensions();
            void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
            bool checkValidationLayerSupport();
            bool isDeviceSuitable(VkPhysicalDevice device);
            bool checkDeviceExtensionSupport(VkPhysicalDevice device);
            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
            int rateDeviceSuitability(VkPhysicalDevice device);
            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

            static std::vector<char> readShaderFile(const std::string& filename);
            VkShaderModule createShaderModule(const std::vector<char>& code);

            void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

            void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
            
            void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

            void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
            void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

            VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

            VkFormat findDepthFormat();
            VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
            bool hasStencilComponent(VkFormat format);
            void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

            VkSampleCountFlagBits getMaxUsableSampleCount();

            const std::vector<const char*> validationLayers = {
                "VK_LAYER_KHRONOS_validation"
            };

            const std::vector<const char*> deviceExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };

            static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
                std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

                return VK_FALSE;
            }

#ifdef NDEBUG
            const bool enableValidationLayers = false;
#else
            const bool enableValidationLayers = true;
#endif
        };

    } // namespace render
} // namespace prism