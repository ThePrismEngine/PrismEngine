
.. _program_listing_file_PrismEngine_src_meshLoader.h:

Program Listing for File meshLoader.h
=====================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_meshLoader.h>` (``PrismEngine\src\meshLoader.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <vector>
   #include "vertex.h"
   
   namespace prism {
       namespace PGC {
           struct MeshData {
               std::vector<Vertex> vertices;
               std::vector<uint32_t> indices;
           };
   
           class MeshLoader
           {
           public:
               static MeshData load(std::string texturePath);
           private:
   
           };
       }
   }
