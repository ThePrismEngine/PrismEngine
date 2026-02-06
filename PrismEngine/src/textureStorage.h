#pragma once
#include <memory>
#include "utils.h"
#include "textureLoader.h"

namespace prism {
	namespace PGC {
		class TextureStorage {
		public:
			TextureStorage() : context(nullptr), settings(nullptr) {};
			void init(PGC::utils::Context* context, PGC::utils::Settings* settings);
			
			TextureId load(std::string texturePath);
			std::shared_ptr<PGC::Texture> get(TextureId textureId);
			bool remove(TextureId textureId);
			void cleanup();

		private:
			void updateDescriptors();
			uint32_t getNextAvailableIndex(utils::Context* context);

			utils::Context* context;
			utils::Settings* settings;

			std::vector<PGC::Texture> textures;
			std::vector<uint32_t> freeTextureIndices;
			PGC::L2::TextureLoader* textureLoader;
		};
	}
}