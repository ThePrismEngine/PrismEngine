
.. _program_listing_file_PrismEngine_src_textureLoader.cpp:

Program Listing for File textureLoader.cpp
==========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_textureLoader.cpp>` (``PrismEngine\src\textureLoader.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "textureLoader.h"
   #include "bufferWrapper.h"
   #include "resourcesCreater.h"
   #define STB_IMAGE_IMPLEMENTATION
   #include "stb_image.h"
   #include <stdexcept>
   
   prism::PGC::Texture prism::PGC::TextureLoader::load(utils::Context* context, std::string texturePath)
   {
       PGC::Texture texture;
       texture.path = texturePath;
       createTextureImage(context, &texture);
       createTextureImageView(context, &texture);
       createTextureSampler(context, &texture);
       return texture;
   }
   
   void prism::PGC::TextureLoader::cleanup(utils::Context* context, PGC::Texture* texture)
   {
       vkDestroySampler(context->device, texture->sampler, nullptr);
       texture->sampler = VK_NULL_HANDLE;
   
       vkDestroyImageView(context->device, texture->imageView, nullptr);
       texture->imageView = VK_NULL_HANDLE;
   
       vkDestroyImage(context->device, texture->image, nullptr);
       texture->image = VK_NULL_HANDLE;
   
       vkFreeMemory(context->device, texture->imageMemory, nullptr);
       texture->imageMemory = VK_NULL_HANDLE;
   }
   
   
   void prism::PGC::TextureLoader::createTextureImage(utils::Context* context, PGC::Texture* texture)
   {
       int texWidth, texHeight, texChannels;
       stbi_uc* pixels = stbi_load(texture->path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
       VkDeviceSize imageSize = texWidth * texHeight * 4;
       texture->mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;
       if (!pixels) {
           throw std::runtime_error("failed to load texture image!");
       }
   
       texture->width = texWidth;
       texture->height = texHeight;
       texture->channels = texChannels;
   
       VkBuffer stagingBuffer;
       VkDeviceMemory stagingBufferMemory;
       PGC::BufferWrapper::createBuffer(context, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
   
       void* data;
       vkMapMemory(context->device, stagingBufferMemory, 0, imageSize, 0, &data);
       memcpy(data, pixels, static_cast<size_t>(imageSize));
       vkUnmapMemory(context->device, stagingBufferMemory);
   
       stbi_image_free(pixels);
   
       PGC::ResourcesCreater::createImage(context, texWidth, texHeight, texture->mipLevels, VK_SAMPLE_COUNT_1_BIT, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, texture->image, texture->imageMemory);
   
   
       PGC::BufferWrapper::transitionImageLayout(context, texture->image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, texture->mipLevels);
       PGC::BufferWrapper::copyBufferToImage(context, stagingBuffer, texture->image, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
   
       vkDestroyBuffer(context->device, stagingBuffer, nullptr);
       vkFreeMemory(context->device, stagingBufferMemory, nullptr);
   
       generateMipmaps(context, texture->image, VK_FORMAT_R8G8B8A8_SRGB, texWidth, texHeight, texture->mipLevels);
   }
   
   void prism::PGC::TextureLoader::createTextureImageView(utils::Context* context, PGC::Texture* texture)
   {
       texture->imageView = PGC::ResourcesCreater::createImageView(context->device, texture->image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, texture->mipLevels);
   }
   
   void prism::PGC::TextureLoader::createTextureSampler(utils::Context* context, PGC::Texture* texture)
   {
       PGC::ResourcesCreater::createTextureSampler(context, &texture->sampler);
   }
   
   void prism::PGC::TextureLoader::generateMipmaps(utils::Context* context, VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels)
   {
       VkFormatProperties formatProperties;
       vkGetPhysicalDeviceFormatProperties(context->physicalDevice, imageFormat, &formatProperties);
   
       if (!(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)) {
           throw std::runtime_error("texture image format does not support linear blitting!");
       }
   
       VkCommandBuffer commandBuffer = PGC::BufferWrapper::beginSingleTimeCommands(context);
   
       VkImageMemoryBarrier barrier{};
       barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
       barrier.image = image;
       barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
       barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
       barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
       barrier.subresourceRange.baseArrayLayer = 0;
       barrier.subresourceRange.layerCount = 1;
       barrier.subresourceRange.levelCount = 1;
   
       int32_t mipWidth = texWidth;
       int32_t mipHeight = texHeight;
   
       for (uint32_t i = 1; i < mipLevels; i++) {
           barrier.subresourceRange.baseMipLevel = i - 1;
           barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
           barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
           barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
           barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
   
           vkCmdPipelineBarrier(commandBuffer,
               VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
               0, nullptr,
               0, nullptr,
               1, &barrier);
   
           VkImageBlit blit{};
           blit.srcOffsets[0] = { 0, 0, 0 };
           blit.srcOffsets[1] = { mipWidth, mipHeight, 1 };
           blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
           blit.srcSubresource.mipLevel = i - 1;
           blit.srcSubresource.baseArrayLayer = 0;
           blit.srcSubresource.layerCount = 1;
           blit.dstOffsets[0] = { 0, 0, 0 };
           blit.dstOffsets[1] = { mipWidth > 1 ? mipWidth / 2 : 1, mipHeight > 1 ? mipHeight / 2 : 1, 1 };
           blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
           blit.dstSubresource.mipLevel = i;
           blit.dstSubresource.baseArrayLayer = 0;
           blit.dstSubresource.layerCount = 1;
   
           vkCmdBlitImage(commandBuffer,
               image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
               image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
               1, &blit,
               VK_FILTER_LINEAR);
   
           barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
           barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
           barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
           barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
   
           vkCmdPipelineBarrier(commandBuffer,
               VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
               0, nullptr,
               0, nullptr,
               1, &barrier);
   
           if (mipWidth > 1) mipWidth /= 2;
           if (mipHeight > 1) mipHeight /= 2;
       }
   
       barrier.subresourceRange.baseMipLevel = mipLevels - 1;
       barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
       barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
       barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
       barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
   
       vkCmdPipelineBarrier(commandBuffer,
           VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
           0, nullptr,
           0, nullptr,
           1, &barrier);
   
       PGC::BufferWrapper::endSingleTimeCommands(context, commandBuffer);
   }
