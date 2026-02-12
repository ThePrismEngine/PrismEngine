#pragma once
#include <memory>
#include <map>
#include "utils.h"
#include "pgcLayersObjsTemplate.h"
#include "layersMacroses.h"
#include "shaderStagesLoader.h"

DECLARE_PGC_LAYER_INSTANCE(L1)
class PipelineStorage : public L1_Object<PipelineStorage> {
public:
	void createImpl();
	void cleanupImpl();
	VkPipeline add(utils::PipelineSettings pipelineSettings);
	void remove(VkPipeline pipeline);

private:
	void createPipeline(VkPipeline* graphicsPipeline, utils::PipelineSettings pipelineSettings);
		
	std::map<size_t, VkPipeline> pipelines;
	PGC::L2::ShaderStagesLoader* shaderStagesLoader;
};
END_NAMESPACE_DECLARATION