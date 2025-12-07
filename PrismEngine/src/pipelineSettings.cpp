#include "pipelineSettings.h"

bool prism::PGC::utils::PipelineSettings::colorBlendAttachmentsEqual(const std::vector<VkPipelineColorBlendAttachmentState>& a,
	const std::vector<VkPipelineColorBlendAttachmentState>& b) {
	if (a.size() != b.size()) return false;

	for (size_t i = 0; i < a.size(); ++i) {
		const auto& attA = a[i];
		const auto& attB = b[i];

		if (attA.blendEnable != attB.blendEnable ||
			attA.srcColorBlendFactor != attB.srcColorBlendFactor ||
			attA.dstColorBlendFactor != attB.dstColorBlendFactor ||
			attA.colorBlendOp != attB.colorBlendOp ||
			attA.srcAlphaBlendFactor != attB.srcAlphaBlendFactor ||
			attA.dstAlphaBlendFactor != attB.dstAlphaBlendFactor ||
			attA.alphaBlendOp != attB.alphaBlendOp ||
			attA.colorWriteMask != attB.colorWriteMask) {
			return false;
		}
	}
	return true;
}

bool prism::PGC::utils::PipelineSettings::dynamicStatesEqual(const std::vector<VkDynamicState>& a,
	const std::vector<VkDynamicState>& b) {
	if (a.size() != b.size()) return false;

	for (size_t i = 0; i < a.size(); ++i) {
		if (a[i] != b[i]) return false;
	}
	return true;
}

size_t prism::PGC::utils::PipelineSettings::getHash() const {
	return std::hash<prism::PGC::utils::PipelineSettings>{}(*this);
}


bool prism::PGC::utils::PipelineSettings::operator==(const PipelineSettings& other) const
{
	return shaders.vertexShaderFilename == other.shaders.vertexShaderFilename &&
		shaders.fragmentShaderFilename == other.shaders.fragmentShaderFilename &&
		shaders.shadersDirectory == other.shaders.shadersDirectory &&
		inputAssembly.topology == other.inputAssembly.topology &&
		inputAssembly.primitiveRestartEnable == other.inputAssembly.primitiveRestartEnable &&
		rasterization.polygonMode == other.rasterization.polygonMode &&
		rasterization.lineWidth == other.rasterization.lineWidth &&
		rasterization.cullMode == other.rasterization.cullMode &&
		rasterization.frontFace == other.rasterization.frontFace &&
		rasterization.depthClampEnable == other.rasterization.depthClampEnable &&
		rasterization.rasterizerDiscardEnable == other.rasterization.rasterizerDiscardEnable &&
		rasterization.depthBiasEnable == other.rasterization.depthBiasEnable &&
		depthStencil.depthTestEnable == other.depthStencil.depthTestEnable &&
		depthStencil.depthWriteEnable == other.depthStencil.depthWriteEnable &&
		depthStencil.depthCompareOp == other.depthStencil.depthCompareOp &&
		depthStencil.depthBoundsTestEnable == other.depthStencil.depthBoundsTestEnable &&
		depthStencil.minDepthBounds == other.depthStencil.minDepthBounds &&
		depthStencil.maxDepthBounds == other.depthStencil.maxDepthBounds &&
		depthStencil.stencilTestEnable == other.depthStencil.stencilTestEnable &&
		multisample.sampleShadingEnable == other.multisample.sampleShadingEnable &&
		multisample.rasterizationSamples == other.multisample.rasterizationSamples &&
		multisample.strategy == other.multisample.strategy &&
		colorBlend.logicOpEnable == other.colorBlend.logicOpEnable &&
		colorBlend.logicOp == other.colorBlend.logicOp &&
		colorBlend.blendConstants[0] == other.colorBlend.blendConstants[0] &&
		colorBlend.blendConstants[1] == other.colorBlend.blendConstants[1] &&
		colorBlend.blendConstants[2] == other.colorBlend.blendConstants[2] &&
		colorBlend.blendConstants[3] == other.colorBlend.blendConstants[3] &&
		colorBlend.attachments.size() == other.colorBlend.attachments.size() &&
		dynamicState.dynamicStates == other.dynamicState.dynamicStates &&
		colorBlendAttachmentsEqual(colorBlend.attachments, other.colorBlend.attachments) &&
		dynamicStatesEqual(dynamicState.dynamicStates, other.dynamicState.dynamicStates) &&
		viewportState.viewportCount == other.viewportState.viewportCount &&
		viewportState.scissorCount == other.viewportState.scissorCount;
}

VkPipelineColorBlendAttachmentState prism::PGC::utils::createColorBlendAttachment(bool blendEnable)
{
	VkPipelineColorBlendAttachmentState attachment = {};
	attachment.blendEnable = blendEnable ? VK_TRUE : VK_FALSE;
	attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
		VK_COLOR_COMPONENT_G_BIT |
		VK_COLOR_COMPONENT_B_BIT |
		VK_COLOR_COMPONENT_A_BIT;

	if (blendEnable) {
		attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		attachment.colorBlendOp = VK_BLEND_OP_ADD;
		attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		attachment.alphaBlendOp = VK_BLEND_OP_ADD;
	}
	else {
		attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		attachment.colorBlendOp = VK_BLEND_OP_ADD;
		attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		attachment.alphaBlendOp = VK_BLEND_OP_ADD;
	}

	return attachment;
}