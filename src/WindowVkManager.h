#pragma once

#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include <vulkan/vulkan.h>
#include <optional>
#include <stdexcept>
#include <utility> // для std::pair
#include <SDL_vulkan.h>
#include <memory> 
#include <set>
#include <iostream>
#include <map>
#include <algorithm>
#include "config.h"
#include "logger.h"

namespace prism {
    namespace view {

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


        class WindowVkManager {
        public:
            // === Деструктор и контрруктор ===
            WindowVkManager();
            void init(SDL_Window* window);
            void drawFrame();
            void cleanup();
            void awaitRenderingCompletion();

            bool framebufferResized = false;
            bool windowMinimized = false;

        private:
            void createInstance();
            void setupDebugMessenger();
            void pickPhysicalDevice();
            void createLogicalDevice();
            void createSurface();
            void createSwapChain();
            void createImageViews();
            void createGraphicsPipeline();
            void createRenderPass();
            void createFramebuffers();
            void createCommandPool();
            void createCommandBuffer();
            void createSyncObjects();

            void recreateSwapChain();
            void cleanupSwapChain();

            const int MAX_FRAMES_IN_FLIGHT = 2;

            SDL_Window* window;
            VkInstance instance;
            VkDebugUtilsMessengerEXT debugMessenger;
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            VkDevice device;
            VkQueue graphicsQueue;
            VkQueue presentQueue;
            VkSurfaceKHR surface;
            std::vector<VkImageView> swapChainImageViews;

            VkSwapchainKHR swapChain;
            std::vector<VkImage> swapChainImages;
            VkFormat swapChainImageFormat;
            VkExtent2D swapChainExtent;

            VkRenderPass renderPass;
            VkPipelineLayout pipelineLayout;

            VkPipeline graphicsPipeline;
            
            std::vector<VkFramebuffer> swapChainFramebuffers;

            VkCommandPool commandPool;
            std::vector<VkCommandBuffer> commandBuffers;

            std::vector<VkSemaphore> imageAvailableSemaphores;
            std::vector<VkSemaphore> renderFinishedSemaphores;
            std::vector<VkFence> inFlightFences;

            uint32_t currentFrame = 0;
            bool wasRenderingActive = true;

            bool isWindowReadyForRendering(SDL_Window* window);
            std::vector<const char*> getRequiredExtensions();
            void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
            bool checkValidationLayerSupport();
            bool isDeviceSuitable(VkPhysicalDevice device);
            bool checkDeviceExtensionSupport(VkPhysicalDevice device);
            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
            int rateDeviceSuitability(VkPhysicalDevice device);
            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

            static std::vector<char> readShaderFile(const std::string& filename);
            VkShaderModule createShaderModule(const std::vector<char>& code);

            void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

            const std::vector<const char*> validationLayers = {
                "VK_LAYER_KHRONOS_validation"
            };

            const std::vector<const char*> deviceExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };

            static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
                std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

                return VK_FALSE;
            }

#ifdef NDEBUG
            const bool enableValidationLayers = false;
#else
            const bool enableValidationLayers = true;
#endif
        };

    } // namespace view
} // namespace prism