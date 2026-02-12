#include "logicalDevice.h"
#include <set>
#include "deviceWrapper.h"
#include "logger.h"

void prism::PGC::L1::LogicalDevice::createImpl()
{
    PGC::utils::QueueFamilyIndices indices = L3::DeviceWrapper::findQueueFamilies(context->physicalDevice, context->surface);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};
    deviceFeatures.samplerAnisotropy = VK_TRUE;
    deviceFeatures.fillModeNonSolid = VK_TRUE;

    VkPhysicalDeviceVulkan12Features vulkan12Features{};
    vulkan12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;

    VkPhysicalDeviceFeatures2 physicalFeatures2{};
    physicalFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    physicalFeatures2.pNext = &vulkan12Features;
    physicalFeatures2.features = deviceFeatures;

    vkGetPhysicalDeviceFeatures2(context->physicalDevice, &physicalFeatures2);

    vulkan12Features.runtimeDescriptorArray = VK_TRUE;
    vulkan12Features.shaderSampledImageArrayNonUniformIndexing = VK_TRUE;
    vulkan12Features.descriptorBindingPartiallyBound = VK_TRUE;
    vulkan12Features.descriptorBindingSampledImageUpdateAfterBind = VK_TRUE;
    vulkan12Features.descriptorBindingUniformBufferUpdateAfterBind = VK_TRUE;


    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pNext = &vulkan12Features;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(context->deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = context->deviceExtensions.data();

    if (context->enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(context->validationLayers.size());
        createInfo.ppEnabledLayerNames = context->validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(context->physicalDevice, &createInfo, nullptr, &context->device) != VK_SUCCESS) {
        logger::logError(logger::Error::VULKAN_LOGICAL_DEVICE_CREATION_FAILED, __FUNCTION__);
    }

    vkGetDeviceQueue(context->device, indices.graphicsFamily.value(), 0, &context->graphicsQueue);
    vkGetDeviceQueue(context->device, indices.presentFamily.value(), 0, &context->presentQueue);
}

void prism::PGC::L1::LogicalDevice::cleanupImpl()
{
    if (context->device != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(context->device);  // Ensure all operations are completed
        vkDestroyDevice(context->device, nullptr);
        context->device = VK_NULL_HANDLE;  // Mark as destroyed
    }
}
