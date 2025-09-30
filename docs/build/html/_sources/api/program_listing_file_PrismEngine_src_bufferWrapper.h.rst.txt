
.. _program_listing_file_PrismEngine_src_bufferWrapper.h:

Program Listing for File bufferWrapper.h
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_bufferWrapper.h>` (``PrismEngine\src\bufferWrapper.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <stdexcept>
   #include <vulkan/vulkan.h>
   #include "utils.h"
   #include "deviceWrapper.h"
   
   namespace prism {
       namespace PGC {
           class BufferWrapper
           {
           public:
               static void createBuffer(utils::Context* Context, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
               static void copyBuffer(utils::Context* context, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
               static void endSingleTimeCommands(utils::Context* context, VkCommandBuffer commandBuffer);
               static VkCommandBuffer beginSingleTimeCommands(utils::Context* context);
               static void transitionImageLayout(utils::Context* context, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
               static void copyBufferToImage(utils::Context* context, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
               static void createVertexBuffer(utils::Context* context);
               static void createIndexBuffer(utils::Context* context);
               static void createUniformBuffers(utils::Context* context);
           private:
   
   
           };
       }
   }
