#pragma once
#include <memory>
#include <map>
#include "utils.h"

namespace prism {
	namespace PGC {
		class PipelineStorage {
		public:
			PipelineStorage() : context(nullptr), settings(nullptr) {};
			void init(PGC::utils::Context* context, PGC::utils::Settings* settings);

			VkPipeline add(utils::PipelineSettings pipelineSettings);

			void remove(VkPipeline pipeline);
			void cleanup(); 

		private:
			void createPipeline(VkPipeline* graphicsPipeline, utils::PipelineSettings pipelineSettings);
			
			std::map<size_t, VkPipeline> pipelines;

			utils::Context* context;
			utils::Settings* settings;
		};
	}
}