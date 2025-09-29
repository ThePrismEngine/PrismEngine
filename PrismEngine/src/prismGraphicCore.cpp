#include "prismGraphicCore.h"
#include "textureLoader.h"
#include "textureManager.h"
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
    createUniformBuffers();
    createDescriptorPool();
    createTextureDescriptorSet();
    createDescriptorSets();
    createCommandBuffer();
    createSyncObjects();
}

void prism::PGC::PrismGraphicCore::drawFrame()
{
    //if (isRenderingActive) {

    //beginFrame

    //updateCameraTransform
    // for () {
    // updateObjectTransform
    // }

    //beginRender
    
    //bindDefault

    //for (uint32_t i = 0; i < objectCount; i++) {
    //    bindTransform
    //    pushTextureId
    //    drawMesh
    //}
    
    //endRender
    //endFrame

    //}
}

void prism::PGC::PrismGraphicCore::startRender()
{

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

void prism::PGC::PrismGraphicCore::createUniformBuffers()
{
    PGC::BufferWrapper::createUniformBuffers(&context);
}

void prism::PGC::PrismGraphicCore::createDescriptorPool()
{
    // Пул для uniform буферов
    {
        std::array<VkDescriptorPoolSize, 2> poolSizes{};
        poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSizes[0].descriptorCount = static_cast<uint32_t>(context.MAX_FRAMES_IN_FLIGHT);
        poolSizes[1].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
        poolSizes[1].descriptorCount = static_cast<uint32_t>(context.MAX_FRAMES_IN_FLIGHT);

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


void prism::PGC::PrismGraphicCore::generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels)
{
    VkFormatProperties formatProperties;
    vkGetPhysicalDeviceFormatProperties(context.physicalDevice, imageFormat, &formatProperties);

    if (!(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)) {
        throw std::runtime_error("texture image format does not support linear blitting!");
    }

    VkCommandBuffer commandBuffer = PGC::BufferWrapper::beginSingleTimeCommands(&context);

    VkImageMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.image = image;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    barrier.subresourceRange.levelCount = 1;

    int32_t mipWidth = texWidth;
    int32_t mipHeight = texHeight;

    for (uint32_t i = 1; i < mipLevels; i++) {
        barrier.subresourceRange.baseMipLevel = i - 1;
        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

        vkCmdPipelineBarrier(commandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
            0, nullptr,
            0, nullptr,
            1, &barrier);

        VkImageBlit blit{};
        blit.srcOffsets[0] = { 0, 0, 0 };
        blit.srcOffsets[1] = { mipWidth, mipHeight, 1 };
        blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        blit.srcSubresource.mipLevel = i - 1;
        blit.srcSubresource.baseArrayLayer = 0;
        blit.srcSubresource.layerCount = 1;
        blit.dstOffsets[0] = { 0, 0, 0 };
        blit.dstOffsets[1] = { mipWidth > 1 ? mipWidth / 2 : 1, mipHeight > 1 ? mipHeight / 2 : 1, 1 };
        blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        blit.dstSubresource.mipLevel = i;
        blit.dstSubresource.baseArrayLayer = 0;
        blit.dstSubresource.layerCount = 1;

        vkCmdBlitImage(commandBuffer,
            image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            1, &blit,
            VK_FILTER_LINEAR);

        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        vkCmdPipelineBarrier(commandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
            0, nullptr,
            0, nullptr,
            1, &barrier);

        if (mipWidth > 1) mipWidth /= 2;
        if (mipHeight > 1) mipHeight /= 2;
    }

    barrier.subresourceRange.baseMipLevel = mipLevels - 1;
    barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    vkCmdPipelineBarrier(commandBuffer,
        VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
        0, nullptr,
        0, nullptr,
        1, &barrier);

    PGC::BufferWrapper::endSingleTimeCommands(&context, commandBuffer);
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
    TextureManager::cleanup(&context);

    if (context.textureDescriptorSetLayout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(context.device, context.textureDescriptorSetLayout, nullptr);
        context.textureDescriptorSetLayout = VK_NULL_HANDLE;
    }

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
        // Проверка, была ли память отображена
        if (context.uniformBuffers[i].cameraMemory != VK_NULL_HANDLE) {
            vkUnmapMemory(context.device, context.uniformBuffers[i].cameraMemory);
            vkDestroyBuffer(context.device, context.uniformBuffers[i].camera, nullptr);
            vkFreeMemory(context.device, context.uniformBuffers[i].cameraMemory, nullptr);
            context.uniformBuffers[i].cameraMemory = VK_NULL_HANDLE;
        }

        if (context.uniformBuffers[i].objectMemory != VK_NULL_HANDLE) {
            vkUnmapMemory(context.device, context.uniformBuffers[i].objectMemory);
            vkDestroyBuffer(context.device, context.uniformBuffers[i].object, nullptr);
            vkFreeMemory(context.device, context.uniformBuffers[i].objectMemory, nullptr);
            context.uniformBuffers[i].objectMemory = VK_NULL_HANDLE;
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
