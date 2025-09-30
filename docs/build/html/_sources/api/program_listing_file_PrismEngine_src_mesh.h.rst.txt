
.. _program_listing_file_PrismEngine_src_mesh.h:

Program Listing for File mesh.h
===============================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_mesh.h>` (``PrismEngine\src\mesh.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <cstdint>
   
   namespace prism {
       typedef uint32_t Mesh;
   
       namespace PGC {
           struct Mesh
           {
               uint32_t vertexOffset;
               uint32_t indexOffset;
               uint32_t vertexCount;
               uint32_t indexCount;
           };
       }
   }
