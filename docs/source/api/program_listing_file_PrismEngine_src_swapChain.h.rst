
.. _program_listing_file_PrismEngine_src_swapChain.h:

Program Listing for File swapChain.h
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_swapChain.h>` (``PrismEngine\src\swapChain.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "utils.h"
   
   namespace prism {
       namespace PGC {
           class SwapChain
           {
           public:
               SwapChain() : context(nullptr), settings(nullptr) {}
               void init(PGC::utils::Context* context, PGC::utils::Settings* settings);
               ~SwapChain();
               void cleanup();
               void awaitRenderingCompletion();
               void recreate();
   
           private:
               void create();
               void createImageViews();
   
               VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
               VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
               VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
               uint32_t getImageCount(PGC::utils::SwapChainSupportDetails swapChainSupport);
   
               utils::Context* context;
               utils::Settings* settings;
           };
       }
   }
