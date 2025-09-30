
.. _program_listing_file_PrismEngine_src_graphicsPipeline.h:

Program Listing for File graphicsPipeline.h
===========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_graphicsPipeline.h>` (``PrismEngine\src\graphicsPipeline.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <array>
   #include "utils.h"
   #include "shaderStagesLoader.h"
   
   namespace prism {
       namespace PGC {
           struct PushConstants {
               int textureIndex;
           };
   
           class GraphicsPipeline {
           public:
               GraphicsPipeline() : context(nullptr), settings(nullptr) {}
               void init(PGC::utils::Context* context, PGC::utils::Settings* settings);
               ~GraphicsPipeline();
               void cleanup();
           private:
               void create();
   
               PGC::utils::Context* context;
               PGC::utils::Settings* settings;
           };
       }
   }
