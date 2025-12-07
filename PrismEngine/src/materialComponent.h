#pragma once
#include "texture.h"

namespace prism {
	namespace scene {
		using Pipeline = VkPipeline;

		struct MaterialComponent
		{
			prism::TextureId texture = INVALID_TEXTURE_ID;
		};
	}
}