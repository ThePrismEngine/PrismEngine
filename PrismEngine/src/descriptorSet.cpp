#include "descriptorSet.h"

void prism::PGC::DescriptorSet::init(PGC::utils::Context* context, PGC::utils::Settings* settings)
{
    this->context = context;
    this->settings = settings;
    create();
}

prism::PGC::DescriptorSet::~DescriptorSet()
{

}

void prism::PGC::DescriptorSet::cleanup()
{

}

void prism::PGC::DescriptorSet::create()
{
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