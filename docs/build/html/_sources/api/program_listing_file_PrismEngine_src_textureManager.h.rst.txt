
.. _program_listing_file_PrismEngine_src_textureManager.h:

Program Listing for File textureManager.h
=========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_textureManager.h>` (``PrismEngine\src\textureManager.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "texture.h"
   #include "utils.h"
   
   namespace prism {
       namespace PGC {
           class TextureManager
           {
           public:
               static uint32_t addTexture(utils::Context* context, const std::string& texturePath);
               static void removeTexture(utils::Context* context, uint32_t textureId);
               static void cleanup(utils::Context* context);
   
               static void updateDescriptors(utils::Context* context);
   
           private:
               static uint32_t getNextAvailableIndex(utils::Context* context);
           };
       }
   }
