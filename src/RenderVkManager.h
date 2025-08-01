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
#include "core.h"
#include "deviceWrapper.h"
#include "deviceChecker.h"
#include "swapChain.h"
#include "utils.h"

namespace prism {
    namespace render {
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
            void createCore();
            void createSwapChain();
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


            const int MAX_FRAMES_IN_FLIGHT = 2;

            SDL_Window* window;

            PGC::core::Core core;
            PGC::SwapChain swapChain;
            PGC::utils::CoreSettings coreSettings;

            PGC::utils::CoreContext context;

           

            VkRenderPass renderPass;
            VkPipelineLayout pipelineLayout;

            VkPipeline graphicsPipeline;

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

            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;

            uint32_t mipLevels;

            const std::string MODEL_PATH = "models/viking_room.obj";
            const std::string TEXTURE_PATH = "textures/viking_room.png";

            //UniformBufferObject ubo;
            VkCommandBuffer beginSingleTimeCommands();
            void endSingleTimeCommands(VkCommandBuffer commandBuffer);
            void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
            void updateUniformBuffer(uint32_t currentImage);
            bool isWindowReadyForRendering(SDL_Window* window);

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

            VkFormat findDepthFormat();
            VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
            bool hasStencilComponent(VkFormat format);
            void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

            VkSampleCountFlagBits getMaxUsableSampleCount();
        };

    } // namespace render
} // namespace prism