#pragma once
#include <vector>
#include <optional>
#include "vulkan/vulkan.h"
#include "configs.h"
#include "config.h"
#include "SDL.h"

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

			struct CoreContext {
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


				const std::vector<const char*> validationLayers = {
					"VK_LAYER_KHRONOS_validation"
				};

				const std::vector<const char*> deviceExtensions = {
					VK_KHR_SWAPCHAIN_EXTENSION_NAME
				};

#ifdef NDEBUG
				bool enableValidationLayers = false;
#else
				bool enableValidationLayers = true;
#endif
			};

			struct AppSettings
			{
				const char* applicationName = "";
				Version applicationVersion = { 1, 0, 0 };
			};

			struct DebugSettings
			{
				VkDebugUtilsMessageSeverityFlagsEXT VulkanMessageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
				VkDebugUtilsMessageTypeFlagsEXT VulkanMessageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
#ifdef NDEBUG
				bool debugDeviceSelection = false;
#else
				bool debugDeviceSelection = true;
#endif
			};

			struct SwapChainSettings
			{

			};

			struct CoreSettings
			{
				AppSettings app;
				DeviceEvaluationWeightsSettings deviceEvaluationWeights;
				DebugSettings debug;
				SwapChainSettings swapChain;
				SDL_Window* window;
			};
		}
	}
}