
.. _program_listing_file_PrismEngine_src_vertex.h:

Program Listing for File vertex.h
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_vertex.h>` (``PrismEngine\src\vertex.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <vulkan/vulkan_core.h>
   #include <array>
   #include "matrix.h"
   #include "glm.hpp"
   
   
   
   namespace prism {
       namespace PGC {
           struct Color
           {
               float r, g, b;
           };
           struct Vertex
           {
               glm::vec3 pos;
               glm::vec3 color;
               glm::vec2 texCoord;
   
               static VkVertexInputBindingDescription getBindingDescription();
   
               static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
   
               bool operator==(const Vertex& other) const;
           };
   
           // Отдельный функтор для хеширования
           struct VertexHasher {
               size_t operator()(const Vertex& v) const noexcept;
           };
       }
   }
