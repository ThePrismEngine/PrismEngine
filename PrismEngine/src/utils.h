#pragma once
#include <vector>
#include <optional>
#include "vulkan/vulkan.h"
#include "config.h"
#include "SDL.h"
#include <string>
#include "bufferObjects.h"
#include "vertex.h"
#include "texture.h"
#include "mesh.h"
#include "pipelineSettings.h"

namespace prism {
	namespace PGC {
		namespace utils {
			struct QueueFamilyIndices {
				std::optional<uint32_t> graphicsFamily;
				std::optional<uint32_t> presentFamily;

				bool isComplete() {
					return graphicsFamily.has_value() && presentFamily.has_value();
				}
			};

			struct SwapChainSupportDetails {
				VkSurfaceCapabilitiesKHR capabilities;
				std::vector<VkSurfaceFormatKHR> formats;
				std::vector<VkPresentModeKHR> presentModes;
			};


			struct CameraData {
				glm::vec3 pos = { 2.0f, 2.0f, 2.0f };  // Позиция
				glm::vec3 look = { 0.0f, 0.0f, 0.0f }; // Взгляд
				glm::vec3 up = { 0.0f, 0.0f, 1.0f };   // Вектор вверх

				float fovy = 45.0f;        // Угол обзора в градусах
				float aspect = 16.f / 9.f; // Соотношение сторон
				float zNear = 0.1f;        // Ближняя плоскость отсечения
				float zFar = 10.0f;        // Дальняя плоскость отсечения

				bool useСurrentWindowAspect = true; // Если истино то aspect игнорируется и соотношение камеры равно соотношению окна

			};

			struct Context {
				VkInstance instance;
				VkSurfaceKHR surface;
				VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
				VkDevice device;
				VkQueue graphicsQueue;
				VkQueue presentQueue;

				VkSwapchainKHR vkSwapChain;
				std::vector<VkImageView> swapChainImageViews;
				std::vector<VkFramebuffer> swapChainFramebuffers;
				std::vector<VkImage> swapChainImages;
				VkFormat swapChainImageFormat;
				VkExtent2D swapChainExtent;

				VkImage depthImage;
				VkDeviceMemory depthImageMemory;
				VkImageView depthImageView;

				VkImage colorImage;
				VkDeviceMemory colorImageMemory;
				VkImageView colorImageView;

				VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
				VkRenderPass renderPass;

				VkBuffer vertexBuffer = VK_NULL_HANDLE;
				VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;
				VkBuffer indexBuffer = VK_NULL_HANDLE;
				VkDeviceMemory indexBufferMemory = VK_NULL_HANDLE;

				std::vector<Vertex> allVertices;
				std::vector<uint32_t> allIndices;
				std::vector<prism::PGC::Mesh> meshes;
				std::vector<uint32_t> freeMeshIndices;
				bool meshBuffersDirty = false;

				VkDescriptorSetLayout descriptorSetLayout;

				VkPipelineLayout pipelineLayout;
				VkPipeline graphicsPipeline;

				VkCommandPool commandPool;
				std::vector<VkCommandBuffer> commandBuffers;

				std::vector<UniformBuffers> uniformBuffers;
				std::vector<StorageBuffers> storageBuffers;

				std::vector<VkSemaphore> imageAvailableSemaphores;
				std::vector<VkSemaphore> renderFinishedSemaphores;
				std::vector<VkFence> inFlightFences;

				uint32_t currentFrame = 0;
				uint32_t imageIndex;
				bool wasRenderingActive = true;

				VkDescriptorPool descriptorPool;

				VkDescriptorSet textureDescriptorSet = VK_NULL_HANDLE;
				VkDescriptorSetLayout textureDescriptorSetLayout = VK_NULL_HANDLE;
				VkDescriptorPool textureDescriptorPool;

				CameraData cameraData;

				std::vector<VkDescriptorSet> descriptorSets;

				const int MAX_FRAMES_IN_FLIGHT = 2;

				const std::vector<const char*> validationLayers = {
					"VK_LAYER_KHRONOS_validation"
				};

				const std::vector<const char*> deviceExtensions = {
					VK_KHR_SWAPCHAIN_EXTENSION_NAME,
					VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME
				};

				size_t dynamicAlignment=0;      // Выровненный размер ObjectUBO

#ifdef _DEBUG
				bool enableValidationLayers = true;
#else
				bool enableValidationLayers = false;
#endif
			};

			struct AppSettings
			{
				const char* applicationName = "";
				prism::Version applicationVersion = { 1, 0, 0 };
			};

			struct DebugSettings
			{
				VkDebugUtilsMessageSeverityFlagsEXT VulkanMessageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
				VkDebugUtilsMessageTypeFlagsEXT VulkanMessageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
#ifdef _DEBUG
				bool debugDeviceSelection = true;
#else
				bool debugDeviceSelection = false;
#endif
			};

			struct DeviceEvaluationWeightsSettings {
				float wType = 0.3f;
				float wFeatures = 0.25f;
				float wHardware = 0.35f;
				float wApi = 0.1f;
			};

			struct SwapChainSettings
			{
				bool enableVSync = true;
				bool enableTripleBuffering = true;
				VkFormat preferredFormat = VK_FORMAT_B8G8R8A8_SRGB;
			};

			// Конфигурация для одного биндинга
			struct BindingConfig {
				uint32_t binding;
				VkDescriptorType descriptorType;
				uint32_t descriptorCount;
				VkShaderStageFlags stageFlags;
				const VkSampler* immutableSamplers = nullptr;
			};

			struct TextureBindingConfig {
				uint32_t binding;
				VkDescriptorType descriptorType;
				uint32_t descriptorCount;
				VkShaderStageFlags stageFlags;
				const VkSampler* immutableSamplers = nullptr;
				VkDescriptorBindingFlagsEXT bindingFlags;
			};

			struct DescriptorSetLayoutSettings {
				std::vector<BindingConfig> bindings;
				VkDescriptorSetLayoutCreateFlags flags = 0;
			};

			struct TextureDescriptorSetLayoutSettings {
				std::vector<TextureBindingConfig> bindings;
				VkDescriptorSetLayoutCreateFlags flags = 0;
			};

			
			struct ColorBlendAttachmentSettings {
				VkBool32 blendEnable = VK_FALSE;
				VkColorComponentFlags colorWriteMask =
					VK_COLOR_COMPONENT_R_BIT |
					VK_COLOR_COMPONENT_G_BIT |
					VK_COLOR_COMPONENT_B_BIT |
					VK_COLOR_COMPONENT_A_BIT;
			};

			struct Settings
			{
				AppSettings app;
				DeviceEvaluationWeightsSettings deviceEvaluationWeights;
				DebugSettings debug;
				SwapChainSettings swapChain;
				DescriptorSetLayoutSettings descriptorSetLayout;
				TextureDescriptorSetLayoutSettings textureDescriptorSetLayout;

				uint32_t MAX_TEXTURES = 350;
				uint32_t MAX_OBJECTS = 3000;
				uint32_t MAX_POINT_LIGHTS = 50;
				uint32_t MAX_DIR_LIGHTS = 10;
				
				PipelineSettings defaultPipeline;

				SDL_Window* window;
			};
		}
	}
}