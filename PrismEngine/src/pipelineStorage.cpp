#include "pipelineStorage.h"
#include "shaderStagesLoader.h"

void prism::PGC::PipelineStorage::init(PGC::utils::Context* context, PGC::utils::Settings* settings)
{
    this->context = context;
    this->settings = settings;

    createPipeline(&context->graphicsPipeline, settings->defaultPipeline);
}

VkPipeline prism::PGC::PipelineStorage::add(utils::PipelineSettings pipelineSettings)
{
    size_t pipelineSettingsHash = pipelineSettings.getHash();
    if (pipelines.count(pipelineSettingsHash)) { return pipelines[pipelineSettingsHash]; }
    pipelines[pipelineSettingsHash] = VkPipeline{};
    createPipeline(&pipelines[pipelineSettingsHash], pipelineSettings);
    
    return pipelines[pipelineSettingsHash];
}

void prism::PGC::PipelineStorage::remove(VkPipeline pipeline)
{
    size_t delKey = -1;
    for (const auto& pair : pipelines) {
        if (pair.second == pipeline) {
            delKey = pair.first;
        }
    }

    if (delKey != -1) {
        vkDestroyPipeline(context->device, pipeline, nullptr);
        pipelines.erase(delKey);
    }
    
}

void prism::PGC::PipelineStorage::cleanup()
{
    for (const auto& pair : pipelines)
    {
        vkDestroyPipeline(context->device, pair.second, nullptr);
    }
    vkDestroyPipelineLayout(context->device, context->pipelineLayout, nullptr);

    pipelines.clear();
}

void prism::PGC::PipelineStorage::createPipeline(VkPipeline* graphicsPipeline, utils::PipelineSettings pipelineSettings)
{
    std::array<VkPipelineShaderStageCreateInfo, 2> stageArray = ShaderStagesLoader::load(context, pipelineSettings);
    VkPipelineShaderStageCreateInfo shaderStages[] = { stageArray[0], stageArray[1] };

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    auto bindingDescription = Vertex::getBindingDescription();
    auto attributeDescriptions = Vertex::getAttributeDescriptions();

    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = pipelineSettings.inputAssembly.topology;
    inputAssembly.primitiveRestartEnable = pipelineSettings.inputAssembly.primitiveRestartEnable;

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = pipelineSettings.viewportState.viewportCount;
    viewportState.scissorCount = pipelineSettings.viewportState.scissorCount;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = pipelineSettings.rasterization.depthClampEnable;
    rasterizer.rasterizerDiscardEnable = pipelineSettings.rasterization.rasterizerDiscardEnable;
    rasterizer.polygonMode = pipelineSettings.rasterization.polygonMode; //VK_POLYGON_MODE_LINE;
    rasterizer.lineWidth = pipelineSettings.rasterization.lineWidth;
    rasterizer.cullMode = pipelineSettings.rasterization.cullMode;
    rasterizer.frontFace = pipelineSettings.rasterization.frontFace;
    rasterizer.depthBiasEnable = pipelineSettings.rasterization.depthBiasEnable;

    VkPipelineDepthStencilStateCreateInfo depthStencil{};
    depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencil.depthTestEnable = pipelineSettings.depthStencil.depthTestEnable;
    depthStencil.depthWriteEnable = pipelineSettings.depthStencil.depthWriteEnable;
    depthStencil.depthCompareOp = pipelineSettings.depthStencil.depthCompareOp;
    depthStencil.depthBoundsTestEnable = pipelineSettings.depthStencil.depthBoundsTestEnable;
    depthStencil.minDepthBounds = pipelineSettings.depthStencil.minDepthBounds; // Optional
    depthStencil.maxDepthBounds = pipelineSettings.depthStencil.maxDepthBounds; // Optional
    depthStencil.stencilTestEnable = pipelineSettings.depthStencil.stencilTestEnable;
    depthStencil.front = pipelineSettings.depthStencil.front; // Optional
    depthStencil.back = pipelineSettings.depthStencil.back; // Optional

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = pipelineSettings.multisample.sampleShadingEnable; // I_P
    multisampling.rasterizationSamples = context->msaaSamples;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = pipelineSettings.colorBlend.logicOpEnable;
    colorBlending.logicOp = pipelineSettings.colorBlend.logicOp;
    colorBlending.attachmentCount = pipelineSettings.colorBlend.attachments.size();
    colorBlending.pAttachments = pipelineSettings.colorBlend.attachments.data();
    colorBlending.blendConstants[0] = pipelineSettings.colorBlend.blendConstants[0];
    colorBlending.blendConstants[1] = pipelineSettings.colorBlend.blendConstants[1];
    colorBlending.blendConstants[2] = pipelineSettings.colorBlend.blendConstants[2];
    colorBlending.blendConstants[3] = pipelineSettings.colorBlend.blendConstants[3];

    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(pipelineSettings.dynamicState.dynamicStates.size());
    dynamicState.pDynamicStates = pipelineSettings.dynamicState.dynamicStates.data();

    std::vector<VkDescriptorSetLayout> setLayouts = { context->descriptorSetLayout, context->textureDescriptorSetLayout };

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(setLayouts.size());
    pipelineLayoutInfo.pSetLayouts = setLayouts.data();
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;
    if (vkCreatePipelineLayout(context->device, &pipelineLayoutInfo, nullptr, &context->pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
    }

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = &dynamicState;
    pipelineInfo.layout = context->pipelineLayout;
    pipelineInfo.renderPass = context->renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineInfo.pDepthStencilState = &depthStencil;

    if (vkCreateGraphicsPipelines(context->device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, graphicsPipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

    vkDestroyShaderModule(context->device, stageArray[0].module, nullptr);
    vkDestroyShaderModule(context->device, stageArray[1].module, nullptr);
}