#pragma once

namespace prism {
	typedef uint32_t TextureId;
	const TextureId INVALID_TEXTURE_ID = 0;

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