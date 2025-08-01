#include "deviceWrapper.h"

VkPhysicalDeviceProperties prism::PGC::DeviceWrapper::getDeviceProperties(VkPhysicalDevice device)
{
   VkPhysicalDeviceProperties props;
   vkGetPhysicalDeviceProperties(device, &props);
   return props;
}

void prism::PGC::DeviceWrapper::getDeviceExtensionProperties(VkPhysicalDevice device, std::vector<VkExtensionProperties>* extensions)
{
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
    extensions->resize(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, extensions->data());
}

VkPhysicalDeviceMemoryProperties prism::PGC::DeviceWrapper::getDeviceMemoryProperties(VkPhysicalDevice device)
{
    VkPhysicalDeviceMemoryProperties memProps;
    vkGetPhysicalDeviceMemoryProperties(device, &memProps);
    return memProps;
}

prism::PGC::utils::QueueFamilyIndices prism::PGC::DeviceWrapper::findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    prism::PGC::utils::QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

        if (presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }

        i++;
    }

    return indices;
}

prism::PGC::utils::SwapChainSupportDetails prism::PGC::DeviceWrapper::querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    PGC::utils::SwapChainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}

