#include "surface.h"
#include <SDL_vulkan.h>
#include "logger.h"

void prism::PGC::L1::Surface::createImpl()
{
    if (!SDL_Vulkan_CreateSurface(settings->window, context->instance, &context->surface)) {
        logger::logError(logger::Error::FAILED_TO_CREATE_WINDOW_SURFACE, __FUNCTION__);
    }
}

void prism::PGC::L1::Surface::cleanupImpl()
{
    if (context->surface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(context->instance, context->surface, nullptr);
        context->surface = VK_NULL_HANDLE;
    }
}
