
.. _program_listing_file_PrismEngine_src_init.h:

Program Listing for File init.h
===============================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_init.h>` (``PrismEngine\src\init.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <SDL.h>
   
   namespace prism {
       inline bool isInit = false;
       inline void init() {
           SDL_Init(SDL_INIT_EVERYTHING);
           isInit = true;
       }
   }
