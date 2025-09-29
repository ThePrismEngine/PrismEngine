#pragma once
#include "texture.h"
#include "utils.h"

namespace prism {
	namespace PGC {
        class TextureManager
        {
        public:
            static uint32_t addTexture(utils::Context* context, const std::string& texturePath);
            static void removeTexture(utils::Context* context, uint32_t textureId);
            static void cleanup(utils::Context* context);

            static void updateDescriptors(utils::Context* context);

        private:
            static uint32_t getNextAvailableIndex(utils::Context* context);
        };
	}
}