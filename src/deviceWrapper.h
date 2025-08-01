#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
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
		};
	}
}