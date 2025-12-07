#include "pipelineSettings.h"

prism::PGC::utils::PipelineSettings prism::PGC::utils::PipelineSettings::OpaquePBR()
{
	PipelineSettings settings;

	// settings.shaders = { "pbr-vert.spv", "pbr-frag.spv", "shaders/" };
	settings.shaders = { "vert.spv", "frag.spv", "shaders/" };
	settings.inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

	settings.colorBlend.attachments = {
		VkPipelineColorBlendAttachmentState{
			VK_FALSE,                                  // blendEnable
			VK_BLEND_FACTOR_ONE,                       // srcColorBlendFactor
			VK_BLEND_FACTOR_ZERO,                      // dstColorBlendFactor
			VK_BLEND_OP_ADD,                           // colorBlendOp
			VK_BLEND_FACTOR_ONE,                       // srcAlphaBlendFactor
			VK_BLEND_FACTOR_ZERO,                      // dstAlphaBlendFactor
			VK_BLEND_OP_ADD,                           // alphaBlendOp
			VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
			VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
		}
	};
	settings.colorBlend.logicOpEnable = VK_FALSE;

	return settings;
}

prism::PGC::utils::PipelineSettings prism::PGC::utils::PipelineSettings::Skybox()
{
	PipelineSettings settings;
	settings.shaders = { "albedo-vert.spv", "albedo-frag.spv", "shaders/" };

	settings.rasterization.cullMode = VK_CULL_MODE_FRONT_BIT;

	settings.depthStencil.depthWriteEnable = VK_FALSE;
	settings.depthStencil.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;

	settings.multisample.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	settings.colorBlend.attachments = {
			VkPipelineColorBlendAttachmentState{
				VK_FALSE,                                  // blendEnable
				VK_BLEND_FACTOR_ONE,                       // srcColorBlendFactor
				VK_BLEND_FACTOR_ZERO,                      // dstColorBlendFactor
				VK_BLEND_OP_ADD,                           // colorBlendOp
				VK_BLEND_FACTOR_ONE,                       // srcAlphaBlendFactor
				VK_BLEND_FACTOR_ZERO,                      // dstAlphaBlendFactor
				VK_BLEND_OP_ADD,                           // alphaBlendOp
				VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
				VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
			}
	};

	settings.colorBlend.logicOpEnable = VK_FALSE;

	return settings;
}

prism::PGC::utils::PipelineSettings prism::PGC::utils::PipelineSettings::WireframeDebug()
{
	PipelineSettings settings;
	settings.shaders = { "albedo-vert.spv", "albedo-frag.spv", "shaders/" };

	settings.rasterization.polygonMode = VK_POLYGON_MODE_LINE;
	settings.rasterization.lineWidth = 1.5f;
	settings.rasterization.cullMode = VK_CULL_MODE_NONE;

	settings.multisample.sampleShadingEnable = VK_FALSE;
	settings.multisample.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	settings.colorBlend.attachments = {
			VkPipelineColorBlendAttachmentState{
				VK_FALSE,                                  // blendEnable
				VK_BLEND_FACTOR_ONE,                       // srcColorBlendFactor
				VK_BLEND_FACTOR_ZERO,                      // dstColorBlendFactor
				VK_BLEND_OP_ADD,                           // colorBlendOp
				VK_BLEND_FACTOR_ONE,                       // srcAlphaBlendFactor
				VK_BLEND_FACTOR_ZERO,                      // dstAlphaBlendFactor
				VK_BLEND_OP_ADD,                           // alphaBlendOp
				VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
				VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
			}
	};

	settings.colorBlend.logicOpEnable = VK_FALSE;

	settings.dynamicState.dynamicStates = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR,
		VK_DYNAMIC_STATE_LINE_WIDTH
	};

	return settings;
}
