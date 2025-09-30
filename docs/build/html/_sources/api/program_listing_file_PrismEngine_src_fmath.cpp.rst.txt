
.. _program_listing_file_PrismEngine_src_fmath.cpp:

Program Listing for File fmath.cpp
==================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_fmath.cpp>` (``PrismEngine\src\fmath.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "fmath.h"
   
   namespace prism {
       namespace math {
           float degToRad(float degrees) {
               return degrees * (float)M_PI / 180.0f;
           }
       }
   }
