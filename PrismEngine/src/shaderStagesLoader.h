#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include "utils.h"

namespace prism {
	namespace PGC {
		class ShaderStagesLoader
		{
		public:
			static std::array<VkPipelineShaderStageCreateInfo, 2> load(PGC::utils::Context* context, utils::PipelineSettings pipelineSettings);
		private:
			
			static std::vector<char> readShaderFile(const std::string& filename);
			static VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);
		};
	}
}