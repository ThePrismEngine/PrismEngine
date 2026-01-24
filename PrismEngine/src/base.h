#pragma once
#include <optional>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <unordered_set>
#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>
#include "config.h"
#include "logger.h"
#include "utils.h"
#include "deviceWrapper.h"
#include "deviceRater.h"

namespace prism {
	namespace PGC {
		inline VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
			auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
			if (func != nullptr) {
				return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
			}
			else {
				return VK_ERROR_EXTENSION_NOT_PRESENT;
			}
		}

		inline void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
			if (func != nullptr) {
				func(instance, debugMessenger, pAllocator);
			}
		}


		class Base {
		public:
			Base() : context(nullptr), settings(nullptr) {}
			void init(PGC::utils::Context* context, PGC::utils::Settings* settings);
			~Base();
			void cleanup();
		private:
			void create();

			void createInstance();
			void setupDebugMessenger();
			void pickPhysicalDevice();
			void createSurface();
			void createLogicalDevice();

			PGC::utils::Context* context;
			PGC::utils::Settings* settings;

			//help
			bool checkValidationLayerSupport();
			std::vector<const char*> getRequiredExtensions();
			void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
			static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

			VkSampleCountFlagBits getMaxUsableSampleCount();

			std::vector<VkSampleCountFlagBits> getPossibleCounts(VkSampleCountFlagBits maxCount);
			VkSampleCountFlagBits getMsaaSamples();
			VkDebugUtilsMessengerEXT debugMessenger;
		};
	}
}