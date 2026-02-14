#include "physicalDevice.h"
#include "logger.h"
#include <map>
#include "deviceWrapper.h"
#include "deviceRater.h"

void prism::PGC::L1::PhysicalDevice::createImpl()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(context->instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        logger::logError(logger::Error::VULKAN_NO_GPU_SUPPORT, __FUNCTION__);
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(context->instance, &deviceCount, devices.data());

    std::multimap<int, VkPhysicalDevice> candidates;
    L2::DeviceRater deviceRater(context, settings);
    for (const auto& device : devices) {
        int score = deviceRater.rate(device);
        candidates.insert(std::make_pair(score, device));
    }

    // Check if the best candidate is suitable at all
    if (candidates.rbegin()->first > 0) {
        context->physicalDevice = candidates.rbegin()->second;
        if (settings->defaultPipeline.multisample.rasterizationSamples)
            context->msaaSamples = getMsaaSamples();
    }
    else {
        logger::logError(logger::Error::VULKAN_NO_SUITABLE_GPU, __FUNCTION__);
    }

    // Вывод информации о выбранном устройстве
    VkPhysicalDeviceProperties deviceProps = L3::DeviceWrapper::getDeviceProperties(context->physicalDevice);
    logger::info("\n");
    logger::info("Selected Vulkan device:");
    logger::info("  - Name: " + std::string(deviceProps.deviceName));
    std::string type;
    switch (deviceProps.deviceType) {
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: type = "Integrated GPU"; break;
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: type = "Discrete GPU"; break;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: type = "Virtual GPU"; break;
    case VK_PHYSICAL_DEVICE_TYPE_CPU: type = "CPU"; break;
    default: type = "Other"; break;
    }
    logger::info("  - Type: " + type);
    logger::info("  - API Version: "
        + std::to_string(VK_VERSION_MAJOR(deviceProps.apiVersion)) + "."
        + std::to_string(VK_VERSION_MINOR(deviceProps.apiVersion)) + "."
        + std::to_string(VK_VERSION_PATCH(deviceProps.apiVersion)));
    logger::info("  - Driver Version: " + std::to_string(deviceProps.driverVersion));
    logger::info("  - Vendor ID: " + std::to_string(deviceProps.vendorID));
    logger::info("  - Device ID: " + std::to_string(deviceProps.deviceID));
    logger::info("  - Score: " + std::to_string(candidates.rbegin()->first) + "\n");
}

void prism::PGC::L1::PhysicalDevice::cleanupImpl()
{

}

VkSampleCountFlagBits prism::PGC::L1::PhysicalDevice::getMsaaSamples() {
    VkSampleCountFlagBits maxCount = getMaxUsableSampleCount();
    std::vector<VkSampleCountFlagBits> possibleCounts = getPossibleCounts(maxCount);


    if (possibleCounts.empty()) {
        return VK_SAMPLE_COUNT_1_BIT;
    }

    switch (settings->defaultPipeline.multisample.strategy) {
    case utils::MultisampleSelectionStrategy::MINIMAL:
        if (possibleCounts.size() >= 2) {
            for (size_t i = 1; i < possibleCounts.size(); ++i) {
                if (possibleCounts[i] != VK_SAMPLE_COUNT_1_BIT) {
                    return possibleCounts[i];
                }
            }
        }
        return possibleCounts[0];

    case utils::MultisampleSelectionStrategy::MIDDLE:
        if (possibleCounts.size() == 1) {
            return possibleCounts[0];
        }
        return possibleCounts[possibleCounts.size() / 2];

    case utils::MultisampleSelectionStrategy::MAXIMAL:
        return possibleCounts.back();

    case utils::MultisampleSelectionStrategy::CUSTOM:
        for (VkSampleCountFlagBits possibleCount : possibleCounts) {
            if (possibleCount == settings->defaultPipeline.multisample.rasterizationSamples) {
                return possibleCount;
            }
        }

        VkSampleCountFlagBits closest = possibleCounts[0];
        int minDiff = std::abs(static_cast<int>(closest) - static_cast<int>(settings->defaultPipeline.multisample.rasterizationSamples));

        for (size_t i = 1; i < possibleCounts.size(); ++i) {
            int diff = std::abs(static_cast<int>(possibleCounts[i]) - static_cast<int>(settings->defaultPipeline.multisample.rasterizationSamples));
            if (diff < minDiff) {
                minDiff = diff;
                closest = possibleCounts[i];
            }
        }
        return closest;

        return VK_SAMPLE_COUNT_1_BIT;
    }
}

VkSampleCountFlagBits prism::PGC::L1::PhysicalDevice::getMaxUsableSampleCount()
{
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(context->physicalDevice, &physicalDeviceProperties);

    VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
    if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
    if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
    if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
    if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
    if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
    if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

    return VK_SAMPLE_COUNT_1_BIT;
}

std::vector<VkSampleCountFlagBits> prism::PGC::L1::PhysicalDevice::getPossibleCounts(VkSampleCountFlagBits maxCount) {

    std::vector<VkSampleCountFlagBits> counts = {
          VK_SAMPLE_COUNT_1_BIT,
          VK_SAMPLE_COUNT_2_BIT,
          VK_SAMPLE_COUNT_4_BIT,
          VK_SAMPLE_COUNT_8_BIT,
          VK_SAMPLE_COUNT_16_BIT,
          VK_SAMPLE_COUNT_32_BIT,
          VK_SAMPLE_COUNT_64_BIT
    };

    std::vector<VkSampleCountFlagBits> possibleCounts;

    for (VkSampleCountFlagBits count : counts)
    {
        if (count <= maxCount) {
            possibleCounts.push_back(count);
        }
        else
        {
            break;
        }
    }
    return possibleCounts;
}