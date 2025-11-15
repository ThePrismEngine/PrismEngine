#include "prismGraphicCore.h"
#include "textureLoader.h"
#include "meshManager.h"

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
	createBase();
    createSwapChain();
    createTextureDescriptorSetLayout();
    createRenderPass();
    createDescriptorSetLayout();
    createGraphicsPipeline();
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

prism::PGC::SwapChain* prism::PGC::PrismGraphicCore::getSwapChainPtr()
{
    return &swapChain;
}

void prism::PGC::PrismGraphicCore::createBase()
{
    base.init(&context, &settings);
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


void prism::PGC::PrismGraphicCore::createSwapChain()
{
    swapChain.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createGraphicsPipeline()
{
    graphicsPipeline.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createRenderPass()
{
    renderPass.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createFramebuffers()
{
    PGC::ResourcesCreater::createFramebuffers(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createCommandPool()
{
    PGC::utils::QueueFamilyIndices queueFamilyIndices = PGC::DeviceWrapper::findQueueFamilies(context.physicalDevice, context.surface);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(context.device, &poolInfo, nullptr, &context.commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
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
    descriptorSetLayout.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createTextureDescriptorSetLayout() {
    VkDescriptorSetLayoutBinding binding{};
    binding.binding = 0;
    binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    binding.descriptorCount = settings.MAX_TEXTURES;
    binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

    VkDescriptorBindingFlagsEXT bindingFlags =
        VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT |
        VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT;

    VkDescriptorSetLayoutBindingFlagsCreateInfoEXT flagsInfo{};
    flagsInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT;
    flagsInfo.bindingCount = 1;
    flagsInfo.pBindingFlags = &bindingFlags;

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.pNext = &flagsInfo;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &binding;
    layoutInfo.flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT_EXT;

    if (vkCreateDescriptorSetLayout(context.device, &layoutInfo, nullptr, &context.textureDescriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture descriptor set layout!");
    }
}

void prism::PGC::PrismGraphicCore::createTextureDescriptorSet() {
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = context.textureDescriptorPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &context.textureDescriptorSetLayout;

    if (vkAllocateDescriptorSets(context.device, &allocInfo, &context.textureDescriptorSet) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate texture descriptor set!");
    }
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

    // Пул для буферов
    {
    std::array<VkDescriptorPoolSize, 2> poolSizes{};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = static_cast<uint32_t>(context.MAX_FRAMES_IN_FLIGHT);
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    poolSizes[1].descriptorCount = static_cast<uint32_t>(context.MAX_FRAMES_IN_FLIGHT * 3);

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(context.MAX_FRAMES_IN_FLIGHT);

    if (vkCreateDescriptorPool(context.device, &poolInfo, nullptr, &context.descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

    // Пул для bindless текстур
    {
        VkDescriptorPoolSize poolSize{};
        poolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSize.descriptorCount = settings.MAX_TEXTURES;

        VkDescriptorPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT_EXT;
        poolInfo.poolSizeCount = 1;
        poolInfo.pPoolSizes = &poolSize;
        poolInfo.maxSets = 1;

        if (vkCreateDescriptorPool(context.device, &poolInfo, nullptr, &context.textureDescriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create texture descriptor pool!");
        }
    }
}

void prism::PGC::PrismGraphicCore::createDescriptorSets()
{
    descriptorSet.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createDepthResources()
{
    PGC::ResourcesCreater::createDepthResources(&context, &settings);
}

void prism::PGC::PrismGraphicCore::createColorResources()
{
    prism::PGC::ResourcesCreater::createColorResources(&context, &settings);
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

    context.swapChainFramebuffers.clear();

    graphicsPipeline.cleanup();

    renderPass.cleanup();

    vkDestroyDescriptorPool(context.device, context.descriptorPool, nullptr);
    context.descriptorPool = VK_NULL_HANDLE;

    descriptorSetLayout.cleanup();

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

    base.cleanup(); 
}

void prism::PGC::PrismGraphicCore::awaitRenderingCompletion()
{
    swapChain.awaitRenderingCompletion();
}
