
.. _program_listing_file_PrismEngine_src_vector.h:

Program Listing for File vector.h
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_vector.h>` (``PrismEngine\src\vector.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   
   #pragma once
   #include <stdexcept>
   #include "SDL.h"
   
   namespace prism {
       namespace math {
   
           struct Vector3d {
               float x; 
               float y; 
               float z; 
               float w = 1.0f; 
   
               Vector3d() : x(0), y(0), z(0), w(1) {}
   
               Vector3d(float x, float y, float z, float w = 1.0f) : x(x), y(y), z(z), w(w) {}
   
               void print();
   
               Vector3d operator+(Vector3d& other);
   
               Vector3d operator-(Vector3d& other);
   
               Vector3d operator*(float k);
   
               Vector3d operator/(float k);
   
               float operator[](int index);
   
               bool operator==(Vector3d& other);
   
               float length();
   
               Vector3d normalise();
           };
   
           float Vector_DotProduct(Vector3d& v1, Vector3d& v2);
   
           Vector3d Vector_CrossProduct(Vector3d& v1, Vector3d& v2);
   
           Vector3d Vector_IntersectPlane(Vector3d& plane_p, Vector3d& plane_n, Vector3d& lineStart, Vector3d& lineEnd);
   
       } // namespace math
   } // namespace prism
