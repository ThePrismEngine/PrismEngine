#pragma once
#include "utils.h"
#include <memory>


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
			
			std::vector<PGC::Texture> textures;

			utils::Context* context;
			utils::Settings* settings;
			std::vector<uint32_t> freeTextureIndices;
		};
	}
}