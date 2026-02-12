#pragma once
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"

DECLARE_PGC_LAYER_INSTANCE(L1)

class PhysicalDevice : public L1_Object<PhysicalDevice> {
public:
	void createImpl();
	void cleanupImpl();

private:
	VkSampleCountFlagBits getMsaaSamples();
	VkSampleCountFlagBits getMaxUsableSampleCount();
	std::vector<VkSampleCountFlagBits> getPossibleCounts(VkSampleCountFlagBits maxCount);
};

END_NAMESPACE_DECLARATION