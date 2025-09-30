
.. _program_listing_file_PrismEngine_src_deviceChecker.h:

Program Listing for File deviceChecker.h
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_deviceChecker.h>` (``PrismEngine\src\deviceChecker.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "vulkan/vulkan.h"
   #include "utils.h"
   #include <vector>
   
   namespace prism {
       namespace PGC {
           class DeviceChecker {
           public:
               static bool check(VkPhysicalDevice device, utils::Context* context, utils::Settings* settings);
               static bool checkBindless(VkPhysicalDevice device);
               static bool checkDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char*> deviceExtensions);
           private:
           };
       }
   }
