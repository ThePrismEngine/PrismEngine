
.. _program_listing_file_PrismEngine_src_transformComponent.h:

Program Listing for File transformComponent.h
=============================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_transformComponent.h>` (``PrismEngine\src\transformComponent.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   
   namespace prism {
       namespace scene {
           struct Position {
               float x, y, z;
           };
   
           struct Rotation {
               float x, y, z;
           };
   
           struct Scale {
               float x, y, z;
           };
   
           struct TransformComponent
           {
               Position pos;
               Rotation rot;
               Scale scale;
           };
       }
   }
