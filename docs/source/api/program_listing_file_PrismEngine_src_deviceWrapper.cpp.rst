
.. _program_listing_file_PrismEngine_src_deviceWrapper.cpp:

Program Listing for File deviceWrapper.cpp
==========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_deviceWrapper.cpp>` (``PrismEngine\src\deviceWrapper.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "deviceWrapper.h"
   
   VkPhysicalDeviceProperties prism::PGC::DeviceWrapper::getDeviceProperties(VkPhysicalDevice device)
   {
      VkPhysicalDeviceProperties props;
      vkGetPhysicalDeviceProperties(device, &props);
      return props;
   }
   
   void prism::PGC::DeviceWrapper::getDeviceExtensionProperties(VkPhysicalDevice device, std::vector<VkExtensionProperties>* extensions)
   {
       uint32_t extensionCount = 0;
       vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
       extensions->resize(extensionCount);
       vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, extensions->data());
   }
   
   VkPhysicalDeviceMemoryProperties prism::PGC::DeviceWrapper::getDeviceMemoryProperties(VkPhysicalDevice device)
   {
       VkPhysicalDeviceMemoryProperties memProps;
       vkGetPhysicalDeviceMemoryProperties(device, &memProps);
       return memProps;
   }
   
   prism::PGC::utils::QueueFamilyIndices prism::PGC::DeviceWrapper::findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
   {
       prism::PGC::utils::QueueFamilyIndices indices;
   
       uint32_t queueFamilyCount = 0;
       vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
   
       std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
       vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
   
       int i = 0;
       for (const auto& queueFamily : queueFamilies) {
           if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
               indices.graphicsFamily = i;
           }
   
           VkBool32 presentSupport = false;
           vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
   
           if (presentSupport) {
               indices.presentFamily = i;
           }
   
           if (indices.isComplete()) {
               break;
           }
   
           i++;
       }
   
       return indices;
   }
   
   prism::PGC::utils::SwapChainSupportDetails prism::PGC::DeviceWrapper::querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
   {
       PGC::utils::SwapChainSupportDetails details;
       vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
   
       uint32_t formatCount;
       vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
   
       if (formatCount != 0) {
           details.formats.resize(formatCount);
           vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
       }
   
       uint32_t presentModeCount;
       vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
   
       if (presentModeCount != 0) {
           details.presentModes.resize(presentModeCount);
           vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
       }
   
       return details;
   }
   
   VkFormatProperties prism::PGC::DeviceWrapper::getDeviceFormatProperties(VkPhysicalDevice device, VkFormat format)
   {
       VkFormatProperties props;
       vkGetPhysicalDeviceFormatProperties(device, format, &props);
       return props;
   }
   
   VkFormat prism::PGC::DeviceWrapper::findDepthFormat(VkPhysicalDevice physicalDevice)
   {
       return findSupportedFormat(physicalDevice,
           { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
           VK_IMAGE_TILING_OPTIMAL,
           VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
       );
   }
   
   uint32_t prism::PGC::DeviceWrapper::findMemoryType(VkPhysicalDevice device, uint32_t typeFilter, VkMemoryPropertyFlags properties)
   {
       VkPhysicalDeviceMemoryProperties memProperties;
       vkGetPhysicalDeviceMemoryProperties(device, &memProperties);
   
       for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
           if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
               return i;
           }
       }
   
       throw std::runtime_error("failed to find suitable memory type!");
   }
   
   VkFormat prism::PGC::DeviceWrapper::findSupportedFormat(VkPhysicalDevice physicalDevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
   {
       for (VkFormat format : candidates) {
           VkFormatProperties props = getDeviceFormatProperties(physicalDevice, format);
   
           if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
               return format;
           }
           else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
               return format;
           }
       }
   
       throw std::runtime_error("failed to find supported format!");
   }
   
