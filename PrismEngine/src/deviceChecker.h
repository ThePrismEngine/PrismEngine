#pragma once
#include "vulkan/vulkan.h"
#include "layersMacroses.h"
#include "utils.h"
#include <vector>

DECLARE_PGC_LAYER_INSTANCE(L2)
class DeviceChecker {
public:
	DeviceChecker(utils::Context* context, utils::Settings* settings) : context(context), settings(settings) {}
	bool check(VkPhysicalDevice device);
	bool checkBindless(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char*> deviceExtensions);
private:
	utils::Context* context;
	utils::Settings* settings;
};
END_NAMESPACE_DECLARATION