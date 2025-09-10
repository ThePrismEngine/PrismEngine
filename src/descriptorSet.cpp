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

        // ObjectUBO (динамический)
        VkDescriptorBufferInfo objectBufferInfo{};
        objectBufferInfo.buffer = context->uniformBuffers[i].object;
        objectBufferInfo.offset = 0; // Смещение будет устанавливаться при binding'е
        objectBufferInfo.range = sizeof(ObjectUBO); // Размер одного UBO

        VkDescriptorImageInfo imageInfo{};
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = context->texture.imageView;
        imageInfo.sampler = context->texture.sampler;

        std::array<VkWriteDescriptorSet, 3> descriptorWrites{};

        // Camera UBO (binding 0) - статический
        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = context->descriptorSets[i];
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &cameraBufferInfo;

        // Texture sampler (binding 1)
        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].dstSet = context->descriptorSets[i];
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].pImageInfo = &imageInfo;

        // Object UBO (binding 2) - динамический
        descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[2].dstSet = context->descriptorSets[i];
        descriptorWrites[2].dstBinding = 2;
        descriptorWrites[2].dstArrayElement = 0;
        descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC; // Изменено на DYNAMIC
        descriptorWrites[2].descriptorCount = 1;
        descriptorWrites[2].pBufferInfo = &objectBufferInfo;

        vkUpdateDescriptorSets(context->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }
}