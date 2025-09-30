
.. _program_listing_file_PrismEngine_src_component.h:

Program Listing for File component.h
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_component.h>` (``PrismEngine\src\component.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <cstdint>
   
   namespace prism {
       namespace scene {
           typedef uint32_t ComponentType;
   
           const ComponentType INVALID_COMPONENT_TYPE = 0;
       }
   }
