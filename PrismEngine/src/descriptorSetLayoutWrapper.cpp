#include "descriptorSetLayoutWrapper.h"

void prism::PGC::L3::DescriptorSetLayoutWrapper::createDescriptorSetLayout(utils::Context* context, utils::Settings* settings)
{
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    for (int i = 0; i < settings->descriptorSetLayout.bindings.size(); i++) {
        utils::BindingConfig targetBinding = settings->descriptorSetLayout.bindings[i];
        bindings.push_back(createDescriptorSetLayoutBinding(targetBinding));
    }
    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    layoutInfo.pBindings = bindings.data();

    if (vkCreateDescriptorSetLayout(context->device, &layoutInfo, nullptr, &context->descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

VkDescriptorSetLayoutBinding prism::PGC::L3::DescriptorSetLayoutWrapper::createDescriptorSetLayoutBinding(utils::BindingConfig targetBinding) {
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = targetBinding.binding;
    uboLayoutBinding.descriptorCount = targetBinding.descriptorCount;
    uboLayoutBinding.descriptorType = targetBinding.descriptorType;
    uboLayoutBinding.pImmutableSamplers = targetBinding.immutableSamplers;
    uboLayoutBinding.stageFlags = targetBinding.stageFlags;
    return uboLayoutBinding;
}

void prism::PGC::L3::DescriptorSetLayoutWrapper::createDescriptorSet(utils::Context* context) {
    std::vector<VkDescriptorSetLayout> layouts(context->MAX_FRAMES_IN_FLIGHT, context->descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = context->descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(context->MAX_FRAMES_IN_FLIGHT);
    allocInfo.pSetLayouts = layouts.data();

    context->descriptorSets.resize(context->MAX_FRAMES_IN_FLIGHT);
    if (vkAllocateDescriptorSets(context->device, &allocInfo, context->descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    for (size_t i = 0; i < context->MAX_FRAMES_IN_FLIGHT; i++) {
        // CameraUBO (статический)
        VkDescriptorBufferInfo cameraBufferInfo{};
        cameraBufferInfo.buffer = context->uniformBuffers[i].camera;
        cameraBufferInfo.offset = 0;
        cameraBufferInfo.range = sizeof(CameraUBO);

        // ObjectSSBO
        VkDescriptorBufferInfo objectsBufferInfo{};
        objectsBufferInfo.buffer = context->storageBuffers[i].object;
        objectsBufferInfo.offset = 0;
        objectsBufferInfo.range = VK_WHOLE_SIZE;

        VkDescriptorBufferInfo pointLightsBufferInfo{};
        pointLightsBufferInfo.buffer = context->storageBuffers[i].pointLights;
        pointLightsBufferInfo.offset = 0;
        pointLightsBufferInfo.range = VK_WHOLE_SIZE;

        VkDescriptorBufferInfo dirLightsBufferInfo{};
        dirLightsBufferInfo.buffer = context->storageBuffers[i].directionalLights;
        dirLightsBufferInfo.offset = 0;
        dirLightsBufferInfo.range = VK_WHOLE_SIZE;

        std::array<VkWriteDescriptorSet, 4> descriptorWrites{};

        // Camera UBO (binding 0) - статический
        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = context->descriptorSets[i];
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &cameraBufferInfo;

        // Object SSBO (binding 1)
        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].dstSet = context->descriptorSets[i];
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].pBufferInfo = &objectsBufferInfo;

        // PointLights SSBO (binding 2)
        descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[2].dstSet = context->descriptorSets[i];
        descriptorWrites[2].dstBinding = 2;
        descriptorWrites[2].dstArrayElement = 0;
        descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        descriptorWrites[2].descriptorCount = 1;
        descriptorWrites[2].pBufferInfo = &pointLightsBufferInfo;

        // DirectionLights SSBO (binding 3)
        descriptorWrites[3].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[3].dstSet = context->descriptorSets[i];
        descriptorWrites[3].dstBinding = 3;
        descriptorWrites[3].dstArrayElement = 0;
        descriptorWrites[3].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        descriptorWrites[3].descriptorCount = 1;
        descriptorWrites[3].pBufferInfo = &dirLightsBufferInfo;

        vkUpdateDescriptorSets(context->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }
}
void prism::PGC::L3::DescriptorSetLayoutWrapper::cleanupDescriptorSetLayout(utils::Context* context)
{
    vkDestroyDescriptorSetLayout(context->device, context->descriptorSetLayout, nullptr);
}

void prism::PGC::L3::DescriptorSetLayoutWrapper::createTextureDescriptorSetLayout(utils::Context* context, utils::Settings* settings) {
    VkDescriptorSetLayoutBinding binding{};
    binding.binding = 0;
    binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    binding.descriptorCount = settings->MAX_TEXTURES;
    binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

    VkDescriptorBindingFlagsEXT bindingFlags = VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT | VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT;

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

    if (vkCreateDescriptorSetLayout(context->device, &layoutInfo, nullptr, &context->textureDescriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture descriptor set layout!");
    }
}
void prism::PGC::L3::DescriptorSetLayoutWrapper::createTextureDescriptorSet(utils::Context* context) {
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = context->textureDescriptorPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &context->textureDescriptorSetLayout;

    if (vkAllocateDescriptorSets(context->device, &allocInfo, &context->textureDescriptorSet) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate texture descriptor set!");
    }
}

void prism::PGC::L3::DescriptorSetLayoutWrapper::createDescriptorPool(utils::Context* context, utils::Settings* settings)
{

    // Пул для буферов
    {
        std::array<VkDescriptorPoolSize, 2> poolSizes{};
        poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSizes[0].descriptorCount = static_cast<uint32_t>(context->MAX_FRAMES_IN_FLIGHT);
        poolSizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        poolSizes[1].descriptorCount = static_cast<uint32_t>(context->MAX_FRAMES_IN_FLIGHT * 3);

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        poolInfo.pPoolSizes = poolSizes.data();
        poolInfo.maxSets = static_cast<uint32_t>(context->MAX_FRAMES_IN_FLIGHT);

        if (vkCreateDescriptorPool(context->device, &poolInfo, nullptr, &context->descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }

    // Пул для bindless текстур
    {
        VkDescriptorPoolSize poolSize{};
        poolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSize.descriptorCount = settings->MAX_TEXTURES;

        VkDescriptorPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT_EXT;
        poolInfo.poolSizeCount = 1;
        poolInfo.pPoolSizes = &poolSize;
        poolInfo.maxSets = 1;

        if (vkCreateDescriptorPool(context->device, &poolInfo, nullptr, &context->textureDescriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create texture descriptor pool!");
        }
    }
}