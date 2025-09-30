
.. _program_listing_file_PrismEngine_src_ubo.h:

Program Listing for File ubo.h
==============================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_ubo.h>` (``PrismEngine\src\ubo.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "glm.hpp"
   #include <vulkan/vulkan_core.h>
   
   
   namespace prism {
       namespace PGC {
           struct ObjectUBO {
               alignas(16) glm::mat4 model;
               alignas(16) glm::mat4 normals;
           };
   
           struct CameraUBO {
               alignas(16) glm::mat4 view;
               alignas(16) glm::mat4 proj;
               alignas(16) glm::mat4 viewProj;
               alignas(16) glm::vec3 cameraPos;
           };
   
           struct UniformBuffers {
               VkBuffer camera;
               VkDeviceMemory cameraMemory;
               void* cameraMapped;
   
               VkBuffer object;
               VkDeviceMemory objectMemory;
               void* objectMapped;
           };
       }
   }
