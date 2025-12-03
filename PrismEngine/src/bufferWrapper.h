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
			static void createBO(utils::Context* context, VkBuffer& buffer, size_t bufferSize, VkDeviceMemory& bufferMemory, void*& bufferMapped, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			static void createBufferObjects(utils::Context* context, utils::Settings* settings);
		private:


		};
	}
}