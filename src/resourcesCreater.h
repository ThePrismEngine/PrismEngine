#pragma once
#include <stdexcept>
#include <array>
#include "utils.h"
#include "deviceWrapper.h"

namespace prism {
	namespace PGC {
		class ResourcesCreater
		{
		public:
			static void createImage(utils::Context* context, uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
			static VkImageView createImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
			static void createFramebuffers(utils::Context* context, utils::Settings* settings);
			static void createColorResources(utils::Context* context, utils::Settings* settings);
            static void createDepthResources(utils::Context* context, utils::Settings* settings);
			static void createTextureSampler(utils::Context* context, utils::Settings* settings);
		private:

		};
	}
}

