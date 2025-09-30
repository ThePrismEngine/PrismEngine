
.. _program_listing_file_PrismEngine_src_prismGraphicCore.h:

Program Listing for File prismGraphicCore.h
===========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_prismGraphicCore.h>` (``PrismEngine\src\prismGraphicCore.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

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
               void startRender();
               prism::PGC::utils::CameraData* getCameraDataPtr();
               PGC::SwapChain* getSwapChainPtr();
   
               void cleanup();
               void awaitRenderingCompletion();
               bool isWindowReadyForRendering(SDL_Window* window);
   
               bool* windowResized;
               bool* windowMinimized;
   
               PGC::utils::Settings settings;
               PGC::utils::Context context;
           private:
               void createBase();
               void createSwapChain();
               void createGraphicsPipeline();
               void createRenderPass();
               void createFramebuffers();
               void createCommandPool();
               void createCommandBuffer();
               void createSyncObjects();
               void createDescriptorSetLayout();
               void createTextureDescriptorSetLayout();
               void createTextureDescriptorSet();
               void createUniformBuffers();
               void createDescriptorPool();
               void createDescriptorSets();
               void createDepthResources();
               void createColorResources();
   
               SDL_Window* window;
   
               PGC::base::Base base;
               PGC::SwapChain swapChain;
               PGC::RenderPass renderPass;
               PGC::DescriptorSetLayout descriptorSetLayout;
               PGC::GraphicsPipeline graphicsPipeline;
               PGC::DescriptorSet descriptorSet;
   
               void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
   
               VkSampleCountFlagBits getMaxUsableSampleCount();
           };
   
       } // namespace render
   } // namespace prism
