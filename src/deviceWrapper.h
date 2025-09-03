#pragma once
#include <vector>
#include <optional>
#include <stdexcept>
#include <vulkan/vulkan.h>
#include "utils.h"

namespace prism {
	namespace PGC {

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
	}
}