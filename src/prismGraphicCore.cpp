#include "prismGraphicCore.h"
#include "textureLoader.h"
#include "textureManager.h"

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
//    createTextureImage();
//    createTextureImageView();
//    createTextureSampler();
    loadModel();
    createVertexBuffer();
    createIndexBuffer();
    createUniformBuffers();
    createDescriptorPool();
    createTextureDescriptorSet();
    context.textureID = TextureManager::addTexture(&context, TEXTURE_PATH);
    TextureManager::addTexture(&context, TEXTURE_PATH);
    createDescriptorSets();
    createCommandBuffer();
    createSyncObjects();

}

void prism::PGC::PrismGraphicCore::drawFrame()
{
    if (!isWindowReadyForRendering(window)) { 
        if (context.wasRenderingActive) {
            awaitRenderingCompletion();
            context.wasRenderingActive = false;
        }
        SDL_PumpEvents(); 
        SDL_Delay(10);
        return;
    }
    context.wasRenderingActive = true;
    
    vkWaitForFences(context.device, 1, &context.inFlightFences[context.currentFrame], VK_TRUE, UINT64_MAX);
    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(context.device, context.vkSwapChain, UINT64_MAX, context.imageAvailableSemaphores[context.currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        swapChain.recreate();
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }
    updateUniformBuffer(context.currentFrame);


    vkResetFences(context.device, 1, &context.inFlightFences[context.currentFrame]);

    vkResetCommandBuffer(context.commandBuffers[context.currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
    recordCommandBuffer(context.commandBuffers[context.currentFrame], imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { context.imageAvailableSemaphores[context.currentFrame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &context.commandBuffers[context.currentFrame];

    VkSemaphore signalSemaphores[] = { context.renderFinishedSemaphores[context.currentFrame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(context.graphicsQueue, 1, &submitInfo, context.inFlightFences[context.currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { context.vkSwapChain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(context.presentQueue, &presentInfo);

    //SDL_GL_SetSwapInterval(1);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || *windowResized) {
        *windowResized = false;
        swapChain.recreate();
    }
    else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }
    context.currentFrame = (context.currentFrame + 1) % context.MAX_FRAMES_IN_FLIGHT;
}

void prism::PGC::PrismGraphicCore::createBase()
{
    base.init(&context, &settings);
}

void prism::PGC::PrismGraphicCore::updateUniformBuffer(uint32_t currentImage)
{
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

///    ObjectUBO ubo{};

    // --- Замена glm::rotate ---
    // Поворот вокруг оси Z на 90 градусов * time
///    ubo.model = prism::math::Matrix4X4::makeRotationZ(prism::math::degToRad(90));

    // --- Замена glm::lookAt ---
///    prism::math::Vector3d eyePos(2.0f, 2.0f, 2.0f);
///    prism::math::Vector3d target(0.0f, 0.0f, 0.0f);
///    prism::math::Vector3d up(0.0f, 0.0f, 1.0f);
///    prism::math::Matrix4X4 viewMatrix = prism::math::Matrix4X4::Matrix_PointAt(eyePos, target, up);
///    ubo.view = Matrix_QuickInverse(viewMatrix);  // lookAt = обратная матрица "PointAt"

    // --- Замена glm::perspective ---
///    float aspect = swapChainExtent.width / (float)swapChainExtent.height;
///    ubo.proj = prism::math::Matrix4X4::makeProjection(45.0f, aspect, 0.1f, 10.0f);
///    ubo.proj[1][1] *= -1;  // Инвертируем Y для Vulkan

    // Транспонируем матрицы перед отправкой в буфер
///    ubo.model = ubo.model.getTransposed();
///    ubo.view = ubo.view.getTransposed();
///    ubo.proj = ubo.proj.getTransposed();
    
    // Обновляем UBO камеры
    // Обновляем UBO камеры
    // Обновление CameraUBO (остается без изменений)
    CameraUBO cameraUbo{};

    // Убедитесь, что камера смотрит на объект
    cameraUbo.view = glm::lookAt(
        glm::vec3(2.0f, 2.0f, 2.0f),  // Положение камеры
        glm::vec3(0.0f, 0.0f, 0.0f),  // Точка, на которую смотрит камера
        glm::vec3(0.0f, 0.0f, 1.0f)   // Вектор "вверх"
    );

    cameraUbo.proj = glm::perspective(
        glm::radians(45.0f),  // Угол обзора
        context.swapChainExtent.width / (float)context.swapChainExtent.height,  // Соотношение сторон
        0.1f, 10.0f  // Ближняя и дальняя плоскости отсечения
    );
    cameraUbo.proj[1][1] *= -1;  // Важно для Vulkan!
    cameraUbo.viewProj = cameraUbo.proj * cameraUbo.view;
    cameraUbo.cameraPos = glm::vec3(2.0f, 2.0f, 2.0f);

    // Копируем данные камеры (как и раньше)
    memcpy(context.uniformBuffers[currentImage].cameraMapped, &cameraUbo, sizeof(cameraUbo));

    // Обновление ObjectUBO для каждого объекта
    int objectCount = 1;
    for (uint32_t i = 0; i < objectCount; i++) {
        ObjectUBO objectUbo{};

        // Вычисляем трансформацию для каждого объекта
        objectUbo.model = glm::rotate(
            glm::mat4(1.0f),
            time * glm::radians(90.0f) * (i + 1),  // Разная скорость вращения для каждого объекта
            glm::vec3(0.0f, 0.0f, 1.0f)  // Вращение вокруг оси Z
        );

        // Добавляем смещение для каждого объекта
        objectUbo.model = glm::translate(objectUbo.model, glm::vec3(i * 2.0f, 0.0f, 0.0f));

        objectUbo.normals = glm::transpose(glm::inverse(objectUbo.model));

        // Копируем данные объекта в правильное место в динамическом буфере
        size_t offset = i * context.dynamicAlignment;
        memcpy((char*)context.uniformBuffers[currentImage].objectMapped + offset, &objectUbo, sizeof(objectUbo));
    }

    /*
    // Обновляем UBO объекта
    ObjectUBO objectUbo{};
    objectUbo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    objectUbo.normals = glm::transpose(glm::inverse(objectUbo.model));

    // Копируем данные объекта напрямую в отображенную память
    memcpy(uniformBuffers[currentImage].objectMapped, &objectUbo, sizeof(objectUbo));*/
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

void prism::PGC::PrismGraphicCore::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex)
{

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0; // Optional
    beginInfo.pInheritanceInfo = nullptr; // Optional

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = context.renderPass;
    renderPassInfo.framebuffer = context.swapChainFramebuffers[imageIndex];

    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = context.swapChainExtent;

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
    clearValues[1].depthStencil = { 1.0f, 0 };

    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, context.graphicsPipeline);
       
        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(context.swapChainExtent.width);
        viewport.height = static_cast<float>(context.swapChainExtent.height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = context.swapChainExtent;
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

        VkBuffer vertexBuffers[] = { context.vertexBuffer };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(commandBuffer, context.indexBuffer, 0, VK_INDEX_TYPE_UINT32);

        vkCmdBindDescriptorSets(commandBuffer,
            VK_PIPELINE_BIND_POINT_GRAPHICS,
            context.pipelineLayout,
            1, // set = 1 для текстур
            1,
            &context.textureDescriptorSet,
            0,
            nullptr);

        int objectCount = 1;
        for (uint32_t i = 0; i < objectCount; i++) {
            uint32_t dynamicOffset = i * static_cast<uint32_t>(context.dynamicAlignment);

            vkCmdBindDescriptorSets(commandBuffer,
                VK_PIPELINE_BIND_POINT_GRAPHICS,
                context.pipelineLayout,
                0, // set = 0 для текстур
                1,
                &context.descriptorSets[context.currentFrame],
                1, &dynamicOffset);

            PushConstants pushConstants{};
            pushConstants.textureIndex = static_cast<int>(context.textureID);
            vkCmdPushConstants(
                commandBuffer,
                context.pipelineLayout,
                VK_SHADER_STAGE_FRAGMENT_BIT, // Указываем, что push-константы используются во фрагментном шейдере
                0,
                sizeof(PushConstants),
                &pushConstants
            );


            // Отрисовка объекта
            vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(context.indices.size()), 1, 0, 0, 0);
        }
    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }

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

void prism::PGC::PrismGraphicCore::createVertexBuffer()
{
    PGC::BufferWrapper::createVertexBuffer(&context);
}

void prism::PGC::PrismGraphicCore::createIndexBuffer()
{
    PGC::BufferWrapper::createIndexBuffer(&context);
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

/*
void prism::PGC::PrismGraphicCore::createTextureImage()
{
    int texWidth, texHeight, texChannels;
    stbi_uc* pixels = stbi_load(TEXTURE_PATH.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    VkDeviceSize imageSize = texWidth * texHeight * 4;
    context.texture.mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;
    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    PGC::BufferWrapper::createBuffer(&context, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(context.device, stagingBufferMemory, 0, imageSize, 0, &data);
    memcpy(data, pixels, static_cast<size_t>(imageSize));
    vkUnmapMemory(context.device, stagingBufferMemory);

    stbi_image_free(pixels);

    PGC::ResourcesCreater::createImage(&context, texWidth, texHeight, context.texture.mipLevels, VK_SAMPLE_COUNT_1_BIT, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, context.texture.image, context.texture.imageMemory);


    PGC::BufferWrapper::transitionImageLayout(&context, context.texture.image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, context.texture.mipLevels);
    PGC::BufferWrapper::copyBufferToImage(&context, stagingBuffer, context.texture.image, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));

    vkDestroyBuffer(context.device, stagingBuffer, nullptr);
    vkFreeMemory(context.device, stagingBufferMemory, nullptr);

    generateMipmaps(context.texture.image, VK_FORMAT_R8G8B8A8_SRGB, texWidth, texHeight, context.texture.mipLevels);
}

void prism::PGC::PrismGraphicCore::createTextureImageView()
{
    context.texture.imageView = PGC::ResourcesCreater::createImageView(context.device, context.texture.image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, context.texture.mipLevels);
}

void prism::PGC::PrismGraphicCore::createTextureSampler()
{
    PGC::ResourcesCreater::createTextureSampler(&context, &context.texture.sampler);
}
*/
void prism::PGC::PrismGraphicCore::createDepthResources()
{
    PGC::ResourcesCreater::createDepthResources(&context, &settings);
}

void prism::PGC::PrismGraphicCore::loadModel()
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, nullptr, &err, MODEL_PATH.c_str())) {
        throw std::runtime_error(err);
    }

    std::unordered_map<prism::PGC::Vertex, uint32_t, prism::PGC::VertexHasher> uniqueVertices{};

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = { 1.0f, 1.0f, 1.0f };

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(context.vertices.size());
                context.vertices.push_back(vertex);
            }

            context.indices.push_back(uniqueVertices[vertex]);
        }
    }
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
