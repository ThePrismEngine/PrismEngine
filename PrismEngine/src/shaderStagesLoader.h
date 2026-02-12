#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include "layersMacroses.h"
#include "utils.h"

DECLARE_PGC_LAYER_INSTANCE(L2)
class ShaderStagesLoader {
public:
	ShaderStagesLoader(utils::Context* context, utils::Settings* settings) : context(context), settings(settings) {}
	std::array<VkPipelineShaderStageCreateInfo, 2> load(utils::PipelineSettings pipelineSettings);
private:
	std::vector<char> readShaderFile(const std::string& filename);
	VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);

	utils::Context* context;
	utils::Settings* settings;
};
END_NAMESPACE_DECLARATION