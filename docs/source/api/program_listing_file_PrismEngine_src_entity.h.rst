
.. _program_listing_file_PrismEngine_src_entity.h:

Program Listing for File entity.h
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_entity.h>` (``PrismEngine\src\entity.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <cstdint>
   
   namespace prism {
       namespace scene {
           typedef uint32_t Entity;
   
           const Entity INVALID_ENTITY_ID = 0;
       }
   }
