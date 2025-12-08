#pragma once
#include <string>
#include <vulkan/vulkan.h>
#include <vector>

namespace prism {
	namespace PGC {
		namespace utils {
			struct ShadersSettings
			{
				std::string vertexShaderFilename;
				std::string fragmentShaderFilename;
				std::string shadersDirectory;
			};

			struct InputAssemblySettings {
				VkPrimitiveTopology topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				VkBool32 primitiveRestartEnable = VK_FALSE;
			};

			struct RasterizationSettings {
				VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL;
				float lineWidth = 1.0f;
				VkCullModeFlags cullMode = VK_CULL_MODE_BACK_BIT;
				VkFrontFace frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
				VkBool32 depthClampEnable = VK_FALSE;
				VkBool32 rasterizerDiscardEnable = VK_FALSE;
				VkBool32 depthBiasEnable = VK_FALSE;
			};

			struct DepthStencilSettings {
				VkBool32 depthTestEnable = VK_TRUE;
				VkBool32 depthWriteEnable = VK_TRUE;
				VkCompareOp depthCompareOp = VK_COMPARE_OP_LESS;
				VkBool32 depthBoundsTestEnable = VK_FALSE;
				float minDepthBounds = 0.0f;
				float maxDepthBounds = 1.0f;
				VkBool32 stencilTestEnable = VK_FALSE;
				VkStencilOpState front = {};
				VkStencilOpState back = {};
			};

			enum MultisampleSelectionStrategy {
				MINIMAL,  // Минимальный уровень после 1x(обычно 2x)
				MIDDLE,   // Среднее значение из доступных
				MAXIMAL,  // Максимальное значение
				CUSTOM,   // Значение из цели или максимально приближенное
				//ADAPTIVE, // Оценка по баллам устройства
			};

			struct MultisampleSettings {
				VkBool32 sampleShadingEnable = VK_FALSE;
				VkSampleCountFlagBits rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
				MultisampleSelectionStrategy strategy = MultisampleSelectionStrategy::MAXIMAL;
			};

			struct ColorBlendSettings {
				std::vector<VkPipelineColorBlendAttachmentState> attachments = {
					VkPipelineColorBlendAttachmentState{
						VK_TRUE,                                    // blendEnable
						VK_BLEND_FACTOR_SRC_ALPHA,                  // srcColorBlendFactor
						VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,        // dstColorBlendFactor
						VK_BLEND_OP_ADD,                            // colorBlendOp
						VK_BLEND_FACTOR_ONE,                        // srcAlphaBlendFactor
						VK_BLEND_FACTOR_ZERO,                       // dstAlphaBlendFactor
						VK_BLEND_OP_ADD,                            // alphaBlendOp
						VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
						VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT // colorWriteMask
					}
				};

				VkBool32 logicOpEnable = VK_FALSE;
				VkLogicOp logicOp = VK_LOGIC_OP_COPY;
				float blendConstants[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			};

			struct DynamicStateSettings {
				std::vector<VkDynamicState> dynamicStates = {
					VK_DYNAMIC_STATE_VIEWPORT,
					VK_DYNAMIC_STATE_SCISSOR
				};
			};

			struct ViewportStateSettings {
				uint32_t viewportCount = 1;
				uint32_t scissorCount = 1;
			};

			struct PipelineSettings {
				ShadersSettings shaders = { "vert.spv", "frag.spv", "shaders/" };;
				InputAssemblySettings inputAssembly;
				RasterizationSettings rasterization;
				DepthStencilSettings depthStencil;
				MultisampleSettings multisample;
				ColorBlendSettings colorBlend;
				DynamicStateSettings dynamicState;
				ViewportStateSettings viewportState;

				bool operator==(const PipelineSettings& other) const;
				static bool colorBlendAttachmentsEqual(const std::vector<VkPipelineColorBlendAttachmentState>& a, const std::vector<VkPipelineColorBlendAttachmentState>& b);
				static bool dynamicStatesEqual(const std::vector<VkDynamicState>& a, const std::vector<VkDynamicState>& b);
				size_t getHash() const;

				void withOpaquePBR();
				void withSkybox(bool cullFront = false);
				void withWireframeDebug();
			};
			VkPipelineColorBlendAttachmentState createColorBlendAttachment(bool blendEnable);
		}
	}
}

namespace std {
	template<>
	struct hash<prism::PGC::utils::PipelineSettings> {
		size_t operator()(const prism::PGC::utils::PipelineSettings& settings) const noexcept {
			size_t hash = 0;

			hash_combine(hash, settings.shaders.vertexShaderFilename);
			hash_combine(hash, settings.shaders.fragmentShaderFilename);
			hash_combine(hash, settings.shaders.shadersDirectory);
			hash_combine(hash, static_cast<int>(settings.inputAssembly.topology));
			hash_combine(hash, settings.inputAssembly.primitiveRestartEnable);
			hash_combine(hash, static_cast<int>(settings.rasterization.polygonMode));
			hash_combine(hash, settings.rasterization.lineWidth);
			hash_combine(hash, static_cast<int>(settings.rasterization.cullMode));
			hash_combine(hash, static_cast<int>(settings.rasterization.frontFace));
			hash_combine(hash, settings.rasterization.depthClampEnable);
			hash_combine(hash, settings.rasterization.rasterizerDiscardEnable);
			hash_combine(hash, settings.rasterization.depthBiasEnable);
			hash_combine(hash, settings.depthStencil.depthTestEnable);
			hash_combine(hash, settings.depthStencil.depthWriteEnable);
			hash_combine(hash, static_cast<int>(settings.depthStencil.depthCompareOp));
			hash_combine(hash, settings.depthStencil.depthBoundsTestEnable);
			hash_combine(hash, settings.depthStencil.minDepthBounds);
			hash_combine(hash, settings.depthStencil.maxDepthBounds);
			hash_combine(hash, settings.depthStencil.stencilTestEnable);
			hash_combine(hash, settings.multisample.sampleShadingEnable);
			hash_combine(hash, static_cast<int>(settings.multisample.rasterizationSamples));
			hash_combine(hash, static_cast<int>(settings.multisample.strategy));
			hash_combine(hash, settings.colorBlend.logicOpEnable);
			hash_combine(hash, static_cast<int>(settings.colorBlend.logicOp));

			// Хешируем массив blendConstants
			for (int i = 0; i < 4; ++i) {
				hash_combine(hash, settings.colorBlend.blendConstants[i]);
			}

			// Хешируем attachments
			hash_combine(hash, settings.colorBlend.attachments.size());
			for (const auto& attachment : settings.colorBlend.attachments) {
				hash_combine(hash, attachment.blendEnable);
				hash_combine(hash, attachment.srcColorBlendFactor);
				hash_combine(hash, attachment.dstColorBlendFactor);
				hash_combine(hash, attachment.colorBlendOp);
				hash_combine(hash, attachment.srcAlphaBlendFactor);
				hash_combine(hash, attachment.dstAlphaBlendFactor);
				hash_combine(hash, attachment.alphaBlendOp);
				hash_combine(hash, attachment.colorWriteMask);
			}

			// Хешируем dynamicStates
			for (const auto& state : settings.dynamicState.dynamicStates) {
				hash_combine(hash, static_cast<int>(state));
			}

			hash_combine(hash, settings.viewportState.viewportCount);
			hash_combine(hash, settings.viewportState.scissorCount);

			return hash;
		}

	private:
		template<typename T>
		void hash_combine(size_t& seed, const T& value) const noexcept {
			seed ^= std::hash<T>{}(value)+0x9e1772b8 + (seed << 6) + (seed >> 2);
		}
	};
}