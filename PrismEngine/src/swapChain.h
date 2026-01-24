#pragma once
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"

DECLARE_PGC_LAYER_INSTANCE(L1)
class SwapChain : public L1_Object<SwapChain> {
public:
	void createImpl();
	void cleanupImpl();
	void awaitRenderingCompletion();
	void recreate();

private:
	void createImageViews();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	uint32_t getImageCount(PGC::utils::SwapChainSupportDetails swapChainSupport);
};
END_NAMESPACE_DECLARATION