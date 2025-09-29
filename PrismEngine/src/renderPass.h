#pragma once
#include "utils.h"
#include "vulkan/vulkan.h"
#include "deviceWrapper.h"

namespace prism {
	namespace PGC {
		class RenderPass {
		public:
			RenderPass(): context(nullptr), settings(nullptr) {}
			void init(PGC::utils::Context* context, PGC::utils::Settings* settings);
			~RenderPass();
			void cleanup();
		private:
			void create();

			utils::Context* context;
			utils::Settings* settings;
		};
	}
}
