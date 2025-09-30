
.. _program_listing_file_PrismEngine_src_texture.h:

Program Listing for File texture.h
==================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_texture.h>` (``PrismEngine\src\texture.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "vulkan/vulkan.h"
   #include <string>
   
   
   namespace prism {
       typedef uint32_t Texture;
       const Texture INVALID_TEXTURE = 0;
   
   
       namespace PGC {
   
           struct Texture
           {
               std::string path;
               uint32_t mipLevels = 1;
   
               VkImage image;
               VkImageView imageView;
               VkDeviceMemory imageMemory;
               VkSampler sampler;
   
               int width, height, channels = 0;
   
               uint32_t bindlessIndex = UINT32_MAX;
           };
       }
   }
