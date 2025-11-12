#pragma once
#include "texture.h"

namespace prism {
	namespace scene {
		struct MaterialComponent
		{
			prism::TextureId texture = INVALID_TEXTURE_ID;
		};
	}
}