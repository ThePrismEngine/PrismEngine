#pragma once
#include <vector>
#include <optional>
#include <stdexcept>
#include <vulkan/vulkan.h>
#include "utils.h"
#include "layersMacroses.h"

DECLARE_PGC_LAYER_INSTANCE(L3)
class DeviceWrapper {
public:
	static VkPhysicalDeviceProperties getDeviceProperties(VkPhysicalDevice device);
	static void getDeviceExtensionProperties(VkPhysicalDevice device, std::vector<VkExtensionProperties>* properties);
	static VkPhysicalDeviceMemoryProperties getDeviceMemoryProperties(VkPhysicalDevice device);
	static prism::PGC::utils::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
	static prism::PGC::utils::SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
	static VkFormatProperties getDeviceFormatProperties(VkPhysicalDevice device, VkFormat format);
	static VkFormat findDepthFormat(VkPhysicalDevice physicalDevice);
	static uint32_t findMemoryType(VkPhysicalDevice device, uint32_t typeFilter, VkMemoryPropertyFlags properties);
	static VkFormat findSupportedFormat(VkPhysicalDevice physicalDevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
};
END_NAMESPACE_DECLARATION