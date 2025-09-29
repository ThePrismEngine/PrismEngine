#pragma once
#include <array>
#include "utils.h"
#include "shaderStagesLoader.h"

namespace prism {
	namespace PGC {
		struct PushConstants {
			int textureIndex;
		};

		class GraphicsPipeline {
		public:
			GraphicsPipeline() : context(nullptr), settings(nullptr) {}
			void init(PGC::utils::Context* context, PGC::utils::Settings* settings);
			~GraphicsPipeline();
			void cleanup();
		private:
			void create();

			PGC::utils::Context* context;
			PGC::utils::Settings* settings;
		};
	}
}