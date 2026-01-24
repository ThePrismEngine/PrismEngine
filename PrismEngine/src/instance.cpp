#include "instance.h"
#include "logger.h"
#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>
#include <iostream>

void prism::PGC::L1::Instance::createImpl()
{
    if (context->enableValidationLayers && !checkValidationLayerSupport()) {
        logger::logError(logger::Error::VULKAN_VALIDATION_LAYERS_UNAVAILABLE, __FUNCTION__);
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = settings->app.applicationName;
    appInfo.applicationVersion = VK_MAKE_VERSION(settings->app.applicationVersion.MAJOR, settings->app.applicationVersion.MINOR, settings->app.applicationVersion.PATCH);
    appInfo.pEngineName = prism::PrismInfo::NAME;
    appInfo.engineVersion = VK_MAKE_VERSION(prism::PrismVersion::MAJOR, prism::PrismVersion::MINOR, prism::PrismVersion::PATCH);
    appInfo.apiVersion = VK_API_VERSION_1_4;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    if (context->enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(context->validationLayers.size());
        createInfo.ppEnabledLayerNames = context->validationLayers.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &context->instance) != VK_SUCCESS) {
        logger::logError(logger::Error::FAILED_TO_CREATE_VK_INSTANCE, __FUNCTION__);
    }
}

void prism::PGC::L1::Instance::cleanupImpl()
{

}

bool prism::PGC::L1::Instance::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : context->validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

std::vector<const char*> prism::PGC::L1::Instance::getRequiredExtensions()
{
    std::vector<const char*> extensions;

    unsigned extensionCount = 0;
    if (!SDL_Vulkan_GetInstanceExtensions(settings->window, &extensionCount, nullptr)) {
        logger::logError(logger::Error::SDL_VULKAN_EXTENSIONS_COUNT_FAILED, __FUNCTION__);
    }

    std::vector<const char*> sdlExtensions(extensionCount);
    if (!SDL_Vulkan_GetInstanceExtensions(settings->window, &extensionCount, sdlExtensions.data())) {
        logger::logError(logger::Error::SDL_VULKAN_EXTENSIONS_COUNT_FAILED, __FUNCTION__);
    }

    extensions.insert(extensions.end(), sdlExtensions.begin(), sdlExtensions.end());

    if (context->enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

void prism::PGC::L1::Instance::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = settings->debug.VulkanMessageSeverity;
    createInfo.messageType = settings->debug.VulkanMessageType;
    createInfo.pfnUserCallback = debugCallback;
}

VKAPI_ATTR VkBool32 VKAPI_CALL prism::PGC::L1::Instance::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}