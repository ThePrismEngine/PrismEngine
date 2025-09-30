
.. _program_listing_file_PrismEngine_src_meshManager.h:

Program Listing for File meshManager.h
======================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_meshManager.h>` (``PrismEngine\src\meshManager.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "mesh.h"
   #include "utils.h"
   #include <string>
   
   namespace prism {
       namespace PGC {
           class MeshManager
           {
           public:
               static prism::Mesh addMesh(utils::Context* context, std::string texturePath);
               static void update(utils::Context* context);
               static void clear(utils::Context* context);
               static prism::PGC::Mesh& getMeshInfo(utils::Context* context, prism::Mesh id);
           private:
               static uint32_t getNextAvailableIndex(utils::Context* context);
           };
       }
   }
