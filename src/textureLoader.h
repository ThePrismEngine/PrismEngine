#pragma once
#include "utils.h"
#include <string>
#include <vulkan/vulkan.h>

namespace prism {
	namespace PGC {
		class TextureLoader
		{
		public:
			static prism::PGC::Texture load(utils::Context* context, std::string texturePath);
			static void cleanup(utils::Context* context, PGC::Texture* texture);
		private:
			static void createTextureImage(utils::Context* context, PGC::Texture* texture);
			static void createTextureImageView(utils::Context* context, PGC::Texture* texture);
			static void createTextureSampler(utils::Context* context, PGC::Texture* texture);
			static void generateMipmaps(utils::Context* context, VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
		};
	}
}