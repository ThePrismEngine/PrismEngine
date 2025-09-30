
.. _program_listing_file_PrismEngine_src_descriptorSetLayout.h:

Program Listing for File descriptorSetLayout.h
==============================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_descriptorSetLayout.h>` (``PrismEngine\src\descriptorSetLayout.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <array>
   #include <stdexcept>
   #include "utils.h"
   
   namespace prism {
       namespace PGC {
           class DescriptorSetLayout {
           public:
               DescriptorSetLayout() : context(nullptr), settings(nullptr) {}
               void init(PGC::utils::Context* context, PGC::utils::Settings* settings);
               ~DescriptorSetLayout();
               void cleanup();
           private:
               void create();
               VkDescriptorSetLayoutBinding createDescriptorSetLayoutBinding(uint32_t binding, VkDescriptorType descriptorType, uint32_t descriptorCount, VkShaderStageFlags stageFlags, const VkSampler* immutableSamplers);
   
               PGC::utils::Context* context;
               PGC::utils::Settings* settings;
           };
       }
   }
