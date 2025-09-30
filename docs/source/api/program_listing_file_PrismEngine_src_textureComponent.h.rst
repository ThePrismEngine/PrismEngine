
.. _program_listing_file_PrismEngine_src_textureComponent.h:

Program Listing for File textureComponent.h
===========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_textureComponent.h>` (``PrismEngine\src\textureComponent.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "texture.h"
   
   namespace prism {
       namespace scene {
           struct TextureComponent
           {
               prism::Texture texture;
           };
       }
   }
