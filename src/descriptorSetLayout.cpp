#include "descriptorSetLayout.h"

void prism::PGC::DescriptorSetLayout::init(PGC::utils::Context* context, PGC::utils::Settings* settings)
{
    this->context = context;
    this->settings = settings;
    create();
}

prism::PGC::DescriptorSetLayout::~DescriptorSetLayout()
{
}

void prism::PGC::DescriptorSetLayout::cleanup()
{
    vkDestroyDescriptorSetLayout(context->device, context->descriptorSetLayout, nullptr);
}

void prism::PGC::DescriptorSetLayout::create()
{
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    for (int i = 0; i < settings->descriptorSetLayout.bindings.size(); i++) {
        utils::BindingConfig targetBinding = settings->descriptorSetLayout.bindings[i];
        bindings.push_back(createDescriptorSetLayoutBinding(targetBinding.binding,
            targetBinding.descriptorType,
            targetBinding.descriptorCount,
            targetBinding.stageFlags,
            targetBinding.immutableSamplers));
    }
    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    layoutInfo.pBindings = bindings.data();

    if (vkCreateDescriptorSetLayout(context->device, &layoutInfo, nullptr, &context->descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

VkDescriptorSetLayoutBinding prism::PGC::DescriptorSetLayout::createDescriptorSetLayoutBinding(uint32_t binding, VkDescriptorType descriptorType, uint32_t descriptorCount, VkShaderStageFlags stageFlags, const VkSampler* immutableSamplers)
{
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = binding;
    uboLayoutBinding.descriptorCount = descriptorCount;
    uboLayoutBinding.descriptorType = descriptorType;
    uboLayoutBinding.pImmutableSamplers = immutableSamplers;
    uboLayoutBinding.stageFlags = stageFlags;
    return uboLayoutBinding;
}
