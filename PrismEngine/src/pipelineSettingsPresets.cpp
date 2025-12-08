#include "pipelineSettings.h"

void prism::PGC::utils::PipelineSettings::withOpaquePBR()
{

	// settings.shaders = { "pbr-vert.spv", "pbr-frag.spv", "shaders/" };
	shaders = { "vert.spv", "frag.spv", "shaders/" };
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

	colorBlend.attachments = {
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
	colorBlend.logicOpEnable = VK_FALSE;
}

void prism::PGC::utils::PipelineSettings::withSkybox(bool cullFront)
{
	shaders = { "albedo-vert.spv", "albedo-frag.spv", "shaders/" };

	rasterization.cullMode = cullFront ? VK_CULL_MODE_FRONT_BIT : VK_CULL_MODE_BACK_BIT;

	depthStencil.depthWriteEnable = VK_FALSE;
	depthStencil.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;

	multisample.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	colorBlend.attachments = {
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

	colorBlend.logicOpEnable = VK_FALSE;
}

void prism::PGC::utils::PipelineSettings::withWireframeDebug()
{
	shaders = { "albedo-vert.spv", "albedo-frag.spv", "shaders/" };

	rasterization.polygonMode = VK_POLYGON_MODE_LINE;
	rasterization.lineWidth = 1.5f;
	rasterization.cullMode = VK_CULL_MODE_NONE;

	multisample.sampleShadingEnable = VK_FALSE;
	multisample.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	colorBlend.attachments = {
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

	colorBlend.logicOpEnable = VK_FALSE;

	dynamicState.dynamicStates = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR,
		VK_DYNAMIC_STATE_LINE_WIDTH
	};
}
