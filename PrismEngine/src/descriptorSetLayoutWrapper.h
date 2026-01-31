#pragma once
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"

DECLARE_PGC_LAYER_INSTANCE(L3)

class DescriptorSetLayoutWrapper {
public:
	static void createDescriptorSet(utils::Context* context);
	static void createDescriptorSetLayout(utils::Context* context, utils::Settings* settings);
	static void cleanupDescriptorSetLayout(utils::Context* context);

	

	static void createTextureDescriptorSetLayout(utils::Context* context, utils::Settings* settings);
	static void createTextureDescriptorSet(utils::Context* context);

	static void createDescriptorPool(utils::Context* context, utils::Settings* settings);

private:
	static VkDescriptorSetLayoutBinding createDescriptorSetLayoutBinding(utils::BindingConfig targetBinding);
};
END_NAMESPACE_DECLARATION