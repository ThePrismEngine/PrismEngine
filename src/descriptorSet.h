#pragma once
#include "utils.h"

namespace prism {
	namespace PGC {
		class DescriptorSet {
		public:
			DescriptorSet() : context(nullptr), settings(nullptr) {}
			void init(PGC::utils::Context* context, PGC::utils::Settings* settings);
			~DescriptorSet();
			void cleanup();
		private:
			void create();

			PGC::utils::Context* context;
			PGC::utils::Settings* settings;
		};
	}
}