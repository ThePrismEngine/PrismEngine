
.. _program_listing_file_PrismEngine_src_Config.h:

Program Listing for File Config.h
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_Config.h>` (``PrismEngine\src\Config.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   
   namespace prism {
   
       struct Version
       {
           int MAJOR;
           int MINOR;
           int PATCH;
       };
       
       struct PrismVersion {
           static constexpr int MAJOR = 0;
           static constexpr int MINOR = 1;
           static constexpr int PATCH = 0;
           static constexpr const char* STRING = "0.1.0";
       };
   
       struct PrismInfo {
           static constexpr const char* NAME = "PrismEngine";
           static constexpr const char* DESCRIPTION = "lightweight Vulkan Engine";
       };
   }
