#include "swapChain.h"

#include "algorithm"
#include "logger.h"
#include "deviceChecker.h"
#include "deviceWrapper.h"
#include "resourcesCreater.h"


void prism::PGC::L1::SwapChain::cleanupImpl()
{
    vkDestroyImageView(context->device, context->depthImageView, nullptr);
    vkDestroyImage(context->device, context->depthImage, nullptr);
    vkFreeMemory(context->device, context->depthImageMemory, nullptr);

    vkDestroyImageView(context->device, context->colorImageView, nullptr);
    vkDestroyImage(context->device, context->colorImage, nullptr);
    vkFreeMemory(context->device, context->colorImageMemory, nullptr);

    for (auto framebuffer : context->swapChainFramebuffers) {
        vkDestroyFramebuffer(context->device, framebuffer, nullptr);
    }

    for (auto imageView : context->swapChainImageViews) {
        vkDestroyImageView(context->device, imageView, nullptr);
    }

    vkDestroySwapchainKHR(context->device, context->vkSwapChain, nullptr);
}

void prism::PGC::L1::SwapChain::createImpl()
{
    PGC::utils::SwapChainSupportDetails swapChainSupport = PGC::L3::DeviceWrapper::querySwapChainSupport(context->physicalDevice, context->surface);

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = getImageCount(swapChainSupport);

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = context->surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    PGC::utils::QueueFamilyIndices indices = PGC::L3::DeviceWrapper::findQueueFamilies(context->physicalDevice, context->surface);
    uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }
    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //PL
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;

    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(context->device, &createInfo, nullptr, &context->vkSwapChain) != VK_SUCCESS) {
        logger::logError(logger::Error::VULKAN_SWAP_CHAIN_FAILED, __FUNCTION__);
    }

    vkGetSwapchainImagesKHR(context->device, context->vkSwapChain, &imageCount, nullptr);
    context->swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(context->device, context->vkSwapChain, &imageCount, context->swapChainImages.data());

    context->swapChainImageFormat = surfaceFormat.format;
    context->swapChainExtent = extent;

    // Логируем выбранный режим
    const char* presentModeStr = "";
    switch (presentMode) {
    case VK_PRESENT_MODE_FIFO_KHR: presentModeStr = "FIFO (VSync)"; break;
    case VK_PRESENT_MODE_MAILBOX_KHR: presentModeStr = "MAILBOX (Triple Buffering)"; break;
    case VK_PRESENT_MODE_IMMEDIATE_KHR: presentModeStr = "IMMEDIATE (No VSync)"; break;
    }
    logger::info("Swapchain Present Mode: " + std::to_string(*presentModeStr));
    logger::info("Swapchain Image Count: " + std::to_string(swapChainSupport.capabilities.minImageCount + 1));
}

void prism::PGC::L1::SwapChain::awaitRenderingCompletion()
{
    vkDeviceWaitIdle(context->device);
}

void prism::PGC::L1::SwapChain::recreate()
{
    awaitRenderingCompletion();

    cleanup();

    createImpl();
    createImageViews();

    PGC::ResourcesCreater::createColorResources(context, settings);
    PGC::ResourcesCreater::createDepthResources(context, settings);
    PGC::ResourcesCreater::createFramebuffers(context, settings);

    awaitRenderingCompletion();
}

void prism::PGC::L1::SwapChain::createImageViews()
{
    context->swapChainImageViews.resize(context->swapChainImages.size());

    for (uint32_t i = 0; i < context->swapChainImages.size(); i++) {
        context->swapChainImageViews[i] = ResourcesCreater::createImageView(context->device, context->swapChainImages[i], context->swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
    }
}


VkSurfaceFormatKHR prism::PGC::L1::SwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR prism::PGC::L1::SwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
    if (settings->swapChain.enableTripleBuffering) {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }
    }
    return settings->swapChain.enableVSync ? VK_PRESENT_MODE_FIFO_KHR : VK_PRESENT_MODE_IMMEDIATE_KHR;
}

VkExtent2D prism::PGC::L1::SwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    }
    else {
        int width, height;
        SDL_GetWindowSizeInPixels(settings->window, &width, &height);

        VkExtent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

uint32_t prism::PGC::L1::SwapChain::getImageCount(PGC::utils::SwapChainSupportDetails swapChainSupport)
{
    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }
    return imageCount;
}


