#pragma once
#include "vulkan/vulkan.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"
#include "utils.h"
#include <vector>

DECLARE_PGC_LAYER_INSTANCE(L2)
class DeviceChecker : public L2_Object<DeviceChecker> {
public:
	using L2_Object<DeviceChecker>::L2_Object;

	bool check(VkPhysicalDevice device);
	bool checkBindless(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char*> deviceExtensions);
};
END_NAMESPACE_DECLARATION