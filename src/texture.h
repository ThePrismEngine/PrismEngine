#pragma once

namespace prism {
	namespace PGC {
		struct Texture
		{
			std::string path;
			uint32_t mipLevels;

			VkImage image;
			VkImageView imageView;
			VkDeviceMemory imageMemory;
			VkSampler sampler;

			int width, height, channels;

		};
	}
}