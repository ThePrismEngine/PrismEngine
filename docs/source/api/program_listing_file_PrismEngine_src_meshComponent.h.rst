
.. _program_listing_file_PrismEngine_src_meshComponent.h:

Program Listing for File meshComponent.h
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_meshComponent.h>` (``PrismEngine\src\meshComponent.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "mesh.h"
   
   namespace prism {
       namespace scene {
           struct MeshComponent
           {
               Mesh mesh;
           };
       }
   }
