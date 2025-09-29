#include "graphicsPipeline.h"
#include "vertex.h"

void prism::PGC::GraphicsPipeline::init(PGC::utils::Context* context, PGC::utils::Settings* settings)
{
    this->context = context;
    this->settings = settings;
    create();
}

prism::PGC::GraphicsPipeline::~GraphicsPipeline()
{
}

void prism::PGC::GraphicsPipeline::cleanup()
{
    vkDestroyPipeline(context->device, context->graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(context->device, context->pipelineLayout, nullptr);
}

void prism::PGC::GraphicsPipeline::create()
{
    std::array<VkPipelineShaderStageCreateInfo, 2> stageArray = ShaderStagesLoader::load(context, settings);
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
    inputAssembly.topology = settings->pipeline.inputAssembly.topology;
    inputAssembly.primitiveRestartEnable = settings->pipeline.inputAssembly.primitiveRestartEnable;

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = settings->pipeline.viewportState.viewportCount;
    viewportState.scissorCount = settings->pipeline.viewportState.scissorCount;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = settings->pipeline.rasterization.depthClampEnable;
    rasterizer.rasterizerDiscardEnable = settings->pipeline.rasterization.rasterizerDiscardEnable;
    rasterizer.polygonMode = settings->pipeline.rasterization.polygonMode; //VK_POLYGON_MODE_LINE;
    rasterizer.lineWidth = settings->pipeline.rasterization.lineWidth;
    rasterizer.cullMode = settings->pipeline.rasterization.cullMode;
    rasterizer.frontFace = settings->pipeline.rasterization.frontFace;
    rasterizer.depthBiasEnable = settings->pipeline.rasterization.depthBiasEnable;

    VkPipelineDepthStencilStateCreateInfo depthStencil{};
    depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencil.depthTestEnable = settings->pipeline.depthStencil.depthTestEnable;
    depthStencil.depthWriteEnable = settings->pipeline.depthStencil.depthWriteEnable;
    depthStencil.depthCompareOp = settings->pipeline.depthStencil.depthCompareOp;
    depthStencil.depthBoundsTestEnable = settings->pipeline.depthStencil.depthBoundsTestEnable;
    depthStencil.minDepthBounds = settings->pipeline.depthStencil.minDepthBounds; // Optional
    depthStencil.maxDepthBounds = settings->pipeline.depthStencil.maxDepthBounds; // Optional
    depthStencil.stencilTestEnable = settings->pipeline.depthStencil.stencilTestEnable;
    depthStencil.front = settings->pipeline.depthStencil.front; // Optional
    depthStencil.back = settings->pipeline.depthStencil.back; // Optional

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = settings->pipeline.multisample.sampleShadingEnable; // I_P
    multisampling.rasterizationSamples = context->msaaSamples;



    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = settings->pipeline.colorBlend.logicOpEnable;
    colorBlending.logicOp = settings->pipeline.colorBlend.logicOp;
    colorBlending.attachmentCount = settings->pipeline.colorBlend.attachments.size();
    colorBlending.pAttachments = settings->pipeline.colorBlend.attachments.data();
    colorBlending.blendConstants[0] = settings->pipeline.colorBlend.blendConstants[0];
    colorBlending.blendConstants[1] = settings->pipeline.colorBlend.blendConstants[1];
    colorBlending.blendConstants[2] = settings->pipeline.colorBlend.blendConstants[2];
    colorBlending.blendConstants[3] = settings->pipeline.colorBlend.blendConstants[3];

    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(settings->pipeline.dynamicState.dynamicStates.size());
    dynamicState.pDynamicStates = settings->pipeline.dynamicState.dynamicStates.data();

    VkPushConstantRange pushConstantRange{}; 
    pushConstantRange.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(PushConstants);

    std::vector<VkDescriptorSetLayout> setLayouts = { context->descriptorSetLayout, context->textureDescriptorSetLayout };

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(setLayouts.size());
    pipelineLayoutInfo.pSetLayouts = setLayouts.data();

    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

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

    if (vkCreateGraphicsPipelines(context->device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &context->graphicsPipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

    vkDestroyShaderModule(context->device, stageArray[0].module, nullptr);
    vkDestroyShaderModule(context->device, stageArray[1].module, nullptr);
}
