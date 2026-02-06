#pragma once

#include <string>
#include <vulkan/vulkan.h>
#include "utils.h"
#include "layersMacroses.h"

DECLARE_PGC_LAYER_INSTANCE(L2)
class TextureLoader {
public:
	TextureLoader(utils::Context* context, utils::Settings* settings) : context(context), settings(settings) {};
	prism::PGC::Texture load(std::string texturePath);
	void cleanup(PGC::Texture* texture);
private:
	void createTextureImage(PGC::Texture* texture);
	void createTextureImageView(PGC::Texture* texture);
	void createTextureSampler(PGC::Texture* texture);
	void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

	utils::Context* context;
	utils::Settings* settings;
};
END_NAMESPACE_DECLARATION