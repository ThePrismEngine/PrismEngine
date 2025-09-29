#include "deviceChecker.h"
#include "deviceWrapper.h"
#include "utils.h"
#include <set>
#include <string>

bool prism::PGC::DeviceChecker::check(VkPhysicalDevice device, utils::Context* context, utils::Settings* settings)
{
    prism::PGC::utils::QueueFamilyIndices indices = DeviceWrapper::findQueueFamilies(device, context->surface);

    bool extensionsSupported = checkDeviceExtensionSupport(device, context->deviceExtensions);

    bool swapChainAdequate = false;
    if (extensionsSupported) {
        prism::PGC::utils::SwapChainSupportDetails swapChainSupport = DeviceWrapper::querySwapChainSupport(device, context->surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    VkPhysicalDeviceFeatures supportedFeatures;
    vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

    return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
}

bool prism::PGC::DeviceChecker::checkBindless(VkPhysicalDevice device)
{
    VkPhysicalDeviceVulkan12Features vulkan12Features = {};
    vulkan12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;

    VkPhysicalDeviceFeatures2 deviceFeatures2 = {};
    deviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    deviceFeatures2.pNext = &vulkan12Features;

    vkGetPhysicalDeviceFeatures2(device, &deviceFeatures2);

    if (!vulkan12Features.descriptorBindingSampledImageUpdateAfterBind ||
        !vulkan12Features.descriptorBindingPartiallyBound ||
        !vulkan12Features.runtimeDescriptorArray ||
        !vulkan12Features.shaderSampledImageArrayNonUniformIndexing) {
        return false;
    }

    return true;
}

bool prism::PGC::DeviceChecker::checkDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char*> deviceExtensions)
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}
