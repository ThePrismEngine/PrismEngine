#include "bufferWrapper.h"

void prism::PGC::BufferWrapper::createBuffer(utils::Context* context, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(context->device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(context->device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = PGC::DeviceWrapper::findMemoryType(context->physicalDevice, memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(context->device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(context->device, buffer, bufferMemory, 0);
}

void prism::PGC::BufferWrapper::copyBuffer(utils::Context* context, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(context);

    VkBufferCopy copyRegion{};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    endSingleTimeCommands(context, commandBuffer);
}

void prism::PGC::BufferWrapper::endSingleTimeCommands(utils::Context* context, VkCommandBuffer commandBuffer)
{
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(context->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(context->graphicsQueue);

    vkFreeCommandBuffers(context->device, context->commandPool, 1, &commandBuffer);
}

VkCommandBuffer prism::PGC::BufferWrapper::beginSingleTimeCommands(utils::Context* context)
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = context->commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(context->device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void prism::PGC::BufferWrapper::transitionImageLayout(utils::Context* context, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels)
{
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(context);

    VkImageMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = oldLayout;
    barrier.newLayout = newLayout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    barrier.subresourceRange.levelCount = mipLevels;

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;

    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else {
        throw std::invalid_argument("unsupported layout transition!");
    }

    vkCmdPipelineBarrier(
        commandBuffer,
        sourceStage, destinationStage,
        0,
        0, nullptr,
        0, nullptr,
        1, &barrier
    );

    endSingleTimeCommands(context, commandBuffer);
}

void prism::PGC::BufferWrapper::copyBufferToImage(utils::Context* context, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
{
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(context);

    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    region.imageOffset = { 0, 0, 0 };
    region.imageExtent = {
        width,
        height,
        1
    };

    vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    endSingleTimeCommands(context, commandBuffer);
}

void prism::PGC::BufferWrapper::createVertexBuffer(utils::Context* context)
{
    VkDeviceSize bufferSize = sizeof(context->vertices[0]) * context->vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    PGC::BufferWrapper::createBuffer(context, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(context->device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, context->vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(context->device, stagingBufferMemory);

    PGC::BufferWrapper::createBuffer(context, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, context->vertexBuffer, context->vertexBufferMemory);

    copyBuffer(context, stagingBuffer, context->vertexBuffer, bufferSize);

    vkDestroyBuffer(context->device, stagingBuffer, nullptr);
    vkFreeMemory(context->device, stagingBufferMemory, nullptr);
}

void prism::PGC::BufferWrapper::createIndexBuffer(utils::Context* context)
{
    VkDeviceSize bufferSize = sizeof(context->indices[0]) * context->indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    PGC::BufferWrapper::createBuffer(context, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(context->device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, context->indices.data(), (size_t)bufferSize);
    vkUnmapMemory(context->device, stagingBufferMemory);

    PGC::BufferWrapper::createBuffer(context, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, context->indexBuffer, context->indexBufferMemory);

    copyBuffer(context, stagingBuffer, context->indexBuffer, bufferSize);

    vkDestroyBuffer(context->device, stagingBuffer, nullptr);
    vkFreeMemory(context->device, stagingBufferMemory, nullptr);
}

void prism::PGC::BufferWrapper::createUniformBuffers(utils::Context* context)
{
    context->uniformBuffers.resize(context->MAX_FRAMES_IN_FLIGHT);

    VkDeviceSize cameraBufferSize = sizeof(render::CameraUBO);

    // Получаем требования к выравниванию
    size_t minUboAlignment = DeviceWrapper::getDeviceProperties(context->physicalDevice).limits.minUniformBufferOffsetAlignment;

    // Вычисляем выровненный размер для ObjectUBO
    size_t objectUBOSize = sizeof(render::ObjectUBO);
    context->dynamicAlignment = objectUBOSize;

    if (minUboAlignment > 0) {
        context->dynamicAlignment = (objectUBOSize + minUboAlignment - 1) & ~(minUboAlignment - 1);
    }

    // Размер динамического буфера (для MAX_OBJECTS объектов)
    VkDeviceSize objectBufferSize = context->dynamicAlignment * context->MAX_OBJECTS;

    for (size_t i = 0; i < context->MAX_FRAMES_IN_FLIGHT; i++) {
        // Создаем буфер для камеры (обычный UBO)
        PGC::BufferWrapper::createBuffer(context, cameraBufferSize,
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            context->uniformBuffers[i].camera,
            context->uniformBuffers[i].cameraMemory);

        vkMapMemory(context->device, context->uniformBuffers[i].cameraMemory, 0,
            cameraBufferSize, 0, &context->uniformBuffers[i].cameraMapped);

        // Создаем динамический буфер для объектов
        PGC::BufferWrapper::createBuffer(context, objectBufferSize,
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            context->uniformBuffers[i].object,
            context->uniformBuffers[i].objectMemory);

        vkMapMemory(context->device, context->uniformBuffers[i].objectMemory, 0,
            objectBufferSize, 0, &context->uniformBuffers[i].objectMapped);
    }

    // Инициализируем нулями динамический буфер
    for (size_t i = 0; i < context->MAX_FRAMES_IN_FLIGHT; i++) {
        memset(context->uniformBuffers[i].objectMapped, 0, objectBufferSize);
    }
}