
.. _program_listing_file_PrismEngine_src_descriptorSet.h:

Program Listing for File descriptorSet.h
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_descriptorSet.h>` (``PrismEngine\src\descriptorSet.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "utils.h"
   
   namespace prism {
       namespace PGC {
           class DescriptorSet {
           public:
               DescriptorSet() : context(nullptr), settings(nullptr) {}
               void init(PGC::utils::Context* context, PGC::utils::Settings* settings);
               ~DescriptorSet();
               void cleanup();
           private:
               void create();
   
               PGC::utils::Context* context;
               PGC::utils::Settings* settings;
           };
       }
   }
