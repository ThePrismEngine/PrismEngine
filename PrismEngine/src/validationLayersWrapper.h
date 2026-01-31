#pragma once
#include "layersMacroses.h"
#include "utils.h"

DECLARE_PGC_LAYER_INSTANCE(L3)

class ValidationLayersWrapper {
public:
	static bool checkValidationLayerSupport(prism::PGC::utils::Context* context);
	static void populateDebugMessengerCreateInfo(prism::PGC::utils::Settings* settings, VkDebugUtilsMessengerCreateInfoEXT& createInfo, PFN_vkDebugUtilsMessengerCallbackEXT debugCallback=prism::PGC::L3::ValidationLayersWrapper::debugCallback);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	static VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	static void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
private:

};

END_NAMESPACE_DECLARATION