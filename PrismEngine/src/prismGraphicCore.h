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
#include "base.h"
#include "deviceWrapper.h"
#include "deviceChecker.h"
#include "swapChain.h"
#include "utils.h"
#include "renderPass.h"
#include "descriptorSetLayout.h"
#include "pipelineStorage.h"
#include "bufferWrapper.h"
#include "descriptorSet.h"
#include "resourcesCreater.h"
#include "textureStorage.h"

namespace prism {
    namespace PGC {
        class PrismGraphicCore {
        public:
            // === Деструктор и контрруктор ===
            PrismGraphicCore();
            void init(utils::Settings settings);
            prism::PGC::utils::CameraData* getCameraDataPtr();
            PGC::SwapChain* getSwapChainPtr();

            void cleanup();
            void awaitRenderingCompletion();
            bool isWindowReadyForRendering(SDL_Window* window);

            bool* windowResized;
            bool* windowMinimized;

            PGC::utils::Settings settings;
            PGC::utils::Context context;

            PGC::TextureStorage textureStorage;

        private:
            void createBase();
            void createSwapChain();
            void createPipelineStorage();
            void createRenderPass();
            void createFramebuffers();
            void createCommandPool();
            void createCommandBuffer();
            void createSyncObjects();
            void createDescriptorSetLayout();
            void createTextureDescriptorSetLayout();
            void createTextureDescriptorSet();
            void createBufferObject();
            void createDescriptorPool();
            void createDescriptorSets();
            void createDepthResources();
            void createColorResources();
            void createTextureStorage();

            SDL_Window* window;

            PGC::Base base;
            PGC::SwapChain swapChain;
            PGC::RenderPass renderPass;
            PGC::DescriptorSetLayout descriptorSetLayout;
            PGC::PipelineStorage pipelineStorage;
            PGC::DescriptorSet descriptorSet;


            VkSampleCountFlagBits getMaxUsableSampleCount();
        };

    } // namespace render
} // namespace prism