#include "prismGraphicCore.h"
#include "textureLoader.h"
#include "meshManager.h"
#include "descriptorSetLayoutWrapper.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

prism::PGC::PrismGraphicCore::PrismGraphicCore()
{
	//init()
}

void prism::PGC::PrismGraphicCore::init(utils::Settings settings)
{
    this->settings = settings;
    this->window = settings.window;
    createInstance();
    createDebug();
    createSurface();
    createPhysicalDevice();
    createLogicalDevice();
    createSwapChain();
    createTextureDescriptorSetLayout();
    createRenderPass();
    createDescriptorSetLayout();
    createPipelineStorage();
    createCommandPool();
    createColorResources();
    createDepthResources();
    createFramebuffers();
    createBufferObject();
    createDescriptorPool();
    createTextureDescriptorSet();
    createDescriptorSets();
    createCommandBuffer();
    createSyncObjects();
    createTextureStorage();
}


prism::PGC::utils::CameraData* prism::PGC::PrismGraphicCore::getCameraDataPtr()
{
    return &context.cameraData;
}

prism::PGC::L1::SwapChain* prism::PGC::PrismGraphicCore::getSwapChainPtr()
{
    return &swapChain;
}

bool prism::PGC::PrismGraphicCore::isWindowReadyForRendering(SDL_Window* window)
{
    Uint32 flags = SDL_GetWindowFlags(window);
    if (flags & (SDL_WINDOW_HIDDEN | SDL_WINDOW_MINIMIZED)) {
        return false;  // Окно скрыто или свёрнуто — рендерить нельзя
    }

    int width, height;
    SDL_GL_GetDrawableSize(window, &width, &height); 
    // Или: SDL_GetWindowSize(window, &width, &height);  // Если не важен HiDPI
    return (width > 0 && height > 0);
}


void prism::PGC::PrismGraphicCore::createInstance()
{
    instance.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createDebug()
{
    debug.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createSurface()
{
    surface.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createPhysicalDevice()
{
    physicalDevice.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createLogicalDevice()
{
    logicalDevice.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createSwapChain()
{
    swapChain.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createPipelineStorage()
{
    pipelineStorage.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createRenderPass()
{
    renderPass.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createFramebuffers()
{
    PGC::L3::ResourcesCreater::createFramebuffers(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createCommandPool()
{
    PGC::L3::ResourcesCreater::createCommandPool(&context);
}

void prism::PGC::PrismGraphicCore::createCommandBuffer()
{
    context.commandBuffers.resize(context.MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = context.commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)context.commandBuffers.size();

    if (vkAllocateCommandBuffers(context.device, &allocInfo, context.commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void prism::PGC::PrismGraphicCore::createSyncObjects()
{
    context.imageAvailableSemaphores.resize(context.MAX_FRAMES_IN_FLIGHT);
    context.renderFinishedSemaphores.resize(context.MAX_FRAMES_IN_FLIGHT);
    context.inFlightFences.resize(context.MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < context.MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(context.device, &semaphoreInfo, nullptr, &context.imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(context.device, &semaphoreInfo, nullptr, &context.renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(context.device, &fenceInfo, nullptr, &context.inFlightFences[i]) != VK_SUCCESS) {

            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
}

void prism::PGC::PrismGraphicCore::createDescriptorSetLayout()
{
    L3::DescriptorSetLayoutWrapper::createDescriptorSetLayout(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createTextureDescriptorSetLayout() {
    L3::DescriptorSetLayoutWrapper::createTextureDescriptorSetLayout(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createTextureDescriptorSet() {
    L3::DescriptorSetLayoutWrapper::createTextureDescriptorSet(&context);
}

void prism::PGC::PrismGraphicCore::createTextureStorage()
{
    textureStorage.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createBufferObject()
{
    PGC::BufferWrapper::createBufferObjects(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createDescriptorPool()
{
    L3::DescriptorSetLayoutWrapper::createDescriptorPool(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createDescriptorSets()
{
    L3::DescriptorSetLayoutWrapper::createDescriptorSet(&context);
}

void prism::PGC::PrismGraphicCore::createDepthResources()
{
    PGC::L3::ResourcesCreater::createDepthResources(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createColorResources()
{
    prism::PGC::L3::ResourcesCreater::createColorResources(&context, &settings);
}

VkSampleCountFlagBits prism::PGC::PrismGraphicCore::getMaxUsableSampleCount()
{
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(context.physicalDevice, &physicalDeviceProperties);

    VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
    if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
    if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
    if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
    if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
    if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
    if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

    return VK_SAMPLE_COUNT_1_BIT;
}

void prism::PGC::PrismGraphicCore::cleanup()
{
    textureStorage.cleanup();

    for (auto framebuffer : context.swapChainFramebuffers) {
        vkDestroyFramebuffer(context.device, framebuffer, nullptr);
    }
    context.swapChainFramebuffers.clear();

    pipelineStorage.cleanup();

    renderPass.cleanup();

    vkDestroyDescriptorPool(context.device, context.descriptorPool, nullptr);
    context.descriptorPool = VK_NULL_HANDLE;

    L3::DescriptorSetLayoutWrapper::cleanupDescriptorSetLayout(&context);

    for (size_t i = 0; i < context.MAX_FRAMES_IN_FLIGHT; i++) {
        if (context.uniformBuffers[i].cameraMemory != VK_NULL_HANDLE) {
            vkUnmapMemory(context.device, context.uniformBuffers[i].cameraMemory);
            vkDestroyBuffer(context.device, context.uniformBuffers[i].camera, nullptr);
            vkFreeMemory(context.device, context.uniformBuffers[i].cameraMemory, nullptr);
            context.uniformBuffers[i].cameraMemory = VK_NULL_HANDLE;
        }

        if (context.storageBuffers[i].objectMemory != VK_NULL_HANDLE) {
            vkUnmapMemory(context.device, context.storageBuffers[i].objectMemory);
            vkDestroyBuffer(context.device, context.storageBuffers[i].object, nullptr);
            vkFreeMemory(context.device, context.storageBuffers[i].objectMemory, nullptr);
            context.storageBuffers[i].objectMemory = VK_NULL_HANDLE;
        }

        if (context.storageBuffers[i].pointLightsMemory != VK_NULL_HANDLE) {
            vkUnmapMemory(context.device, context.storageBuffers[i].pointLightsMemory);
            vkDestroyBuffer(context.device, context.storageBuffers[i].pointLights, nullptr);
            vkFreeMemory(context.device, context.storageBuffers[i].pointLightsMemory, nullptr);
        }

        if (context.storageBuffers[i].directionalLightsMemory != VK_NULL_HANDLE) {
            vkUnmapMemory(context.device, context.storageBuffers[i].directionalLightsMemory);
            vkDestroyBuffer(context.device, context.storageBuffers[i].directionalLights, nullptr);
            vkFreeMemory(context.device, context.storageBuffers[i].directionalLightsMemory, nullptr);
        }
    }


    vkDestroyBuffer(context.device, context.indexBuffer, nullptr);
    context.indexBuffer = VK_NULL_HANDLE;

    vkFreeMemory(context.device, context.indexBufferMemory, nullptr);
    context.indexBufferMemory = VK_NULL_HANDLE;

    vkDestroyBuffer(context.device, context.vertexBuffer, nullptr);
    context.vertexBuffer = VK_NULL_HANDLE;

    vkFreeMemory(context.device, context.vertexBufferMemory, nullptr);
    context.vertexBufferMemory = VK_NULL_HANDLE;

    for (size_t i = 0; i < context.MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(context.device, context.renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(context.device, context.imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(context.device, context.inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(context.device, context.commandPool, nullptr);
    context.commandPool = VK_NULL_HANDLE;

    for (auto imageView : context.swapChainImageViews) {
        vkDestroyImageView(context.device, imageView, nullptr);
    }
    context.swapChainImageViews.clear();

    swapChain.cleanup();

    logicalDevice.cleanup();
    debug.cleanup();
    surface.cleanup();
    instance.cleanup();
}

void prism::PGC::PrismGraphicCore::awaitRenderingCompletion()
{
    swapChain.awaitRenderingCompletion();
}
