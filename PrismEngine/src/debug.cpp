#include "debug.h"
#include "validationLayersWrapper.h"
#include "logger.h"

void prism::PGC::L1::Debug::createImpl()
{
    if (!context->enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    L3::ValidationLayersWrapper::populateDebugMessengerCreateInfo(settings, createInfo);

    if (L3::ValidationLayersWrapper::createDebugUtilsMessengerEXT(context->instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
        logger::logError(logger::Error::VULKAN_DEBUG_MESSENGER_SETUP_FAILED, "prism::PGC::core::Core::setupDebugMessenger()");
    }
}

void prism::PGC::L1::Debug::cleanupImpl()
{
    if (debugMessenger != VK_NULL_HANDLE) {
        L3::ValidationLayersWrapper::destroyDebugUtilsMessengerEXT(context->instance, debugMessenger, nullptr);
        debugMessenger = VK_NULL_HANDLE;
    }
}
