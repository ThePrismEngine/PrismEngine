#pragma once
#include "vulkan/vulkan.h"
#include "utils.h"
#include <vector>

namespace prism {
	namespace PGC {
		class DeviceChecker {
		public:
			static bool check(VkPhysicalDevice device, utils::Context* context, utils::Settings* settings);

			static bool checkDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char*> deviceExtensions);
		private:
		};
	}
}