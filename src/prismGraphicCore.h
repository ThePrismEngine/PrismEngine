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
#include "model.h"
#include "fmath.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "base.h"
#include "deviceWrapper.h"
#include "deviceChecker.h"
#include "swapChain.h"
#include "utils.h"
#include "renderPass.h"
#include "descriptorSetLayout.h"
#include "graphicsPipeline.h"
#include "bufferWrapper.h"
#include "descriptorSet.h"
#include "resourcesCreater.h"

namespace prism {
    namespace PGC {
        class PrismGraphicCore {
        public:
            // === Деструктор и контрруктор ===
            PrismGraphicCore();
            void init(utils::Settings settings);
            void drawFrame();
            void cleanup();
            void awaitRenderingCompletion();



            bool* windowResized;
            bool* windowMinimized;

        private:
            void createBase();
            void createSwapChain();
            void createGraphicsPipeline();
            void createRenderPass();
            void createFramebuffers();
            void createCommandPool();
            void createCommandBuffer();
            void createSyncObjects();
            void createVertexBuffer();///
            void createIndexBuffer();///
            void createDescriptorSetLayout();
            void createUniformBuffers();///
            void createDescriptorPool();///
            void createDescriptorSets();///
            void createTextureImage();///
            void createTextureImageView();///
            void createTextureSampler();///
            void createDepthResources();/*@*/
            void loadModel();
            void createColorResources();

            SDL_Window* window;

            PGC::base::Base base;
            PGC::SwapChain swapChain;
            PGC::RenderPass renderPass;
            PGC::DescriptorSetLayout descriptorSetLayout;
            PGC::GraphicsPipeline graphicsPipeline;
            PGC::DescriptorSet descriptorSet;

            PGC::utils::Settings settings;
            PGC::utils::Context context;

            const std::string MODEL_PATH = "models/viking_room.obj";
            const std::string TEXTURE_PATH = "textures/viking_room.png";

            //ObjectUBO ubo;
      
            void updateUniformBuffer(uint32_t currentImage);
            bool isWindowReadyForRendering(SDL_Window* window);

            void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

            void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

            VkSampleCountFlagBits getMaxUsableSampleCount();
        };

    } // namespace render
} // namespace prism