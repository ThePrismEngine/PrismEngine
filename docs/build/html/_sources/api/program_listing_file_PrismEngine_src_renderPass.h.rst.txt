
.. _program_listing_file_PrismEngine_src_renderPass.h:

Program Listing for File renderPass.h
=====================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_renderPass.h>` (``PrismEngine\src\renderPass.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "utils.h"
   #include "vulkan/vulkan.h"
   #include "deviceWrapper.h"
   
   namespace prism {
       namespace PGC {
           class RenderPass {
           public:
               RenderPass(): context(nullptr), settings(nullptr) {}
               void init(PGC::utils::Context* context, PGC::utils::Settings* settings);
               ~RenderPass();
               void cleanup();
           private:
               void create();
   
               utils::Context* context;
               utils::Settings* settings;
           };
       }
   }
