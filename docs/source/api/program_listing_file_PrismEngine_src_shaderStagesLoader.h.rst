
.. _program_listing_file_PrismEngine_src_shaderStagesLoader.h:

Program Listing for File shaderStagesLoader.h
=============================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_shaderStagesLoader.h>` (``PrismEngine\src\shaderStagesLoader.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <vulkan/vulkan.h>
   #include <string>
   #include <vector>
   #include "utils.h"
   
   namespace prism {
       namespace PGC {
           class ShaderStagesLoader
           {
           public:
               static std::array<VkPipelineShaderStageCreateInfo, 2> load(PGC::utils::Context* context, PGC::utils::Settings* settings);
           private:
               static std::vector<char> readShaderFile(const std::string& filename);
               static VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);
           };
       }
   }
