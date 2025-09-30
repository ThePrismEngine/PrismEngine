
.. _program_listing_file_PrismEngine_src_vector.cpp:

Program Listing for File vector.cpp
===================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_vector.cpp>` (``PrismEngine\src\vector.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "vector.h"
   
   namespace prism {
       namespace math {
           void math::Vector3d::print()
           {
               SDL_Log("%f, %f, %f, %f", x, y, z, w);
           }
           Vector3d Vector3d::operator+(Vector3d& other)
           {
               return Vector3d(x + other.x,
                   y + other.y,
                   z + other.z);
           }
           Vector3d Vector3d::operator-(Vector3d& other)
           {
               return Vector3d(x - other.x,
                   y - other.y,
                   z - other.z);
           }
           Vector3d Vector3d::operator*(float k)
           {
               return Vector3d(x * k,
                   y * k,
                   z * k);
           }
           Vector3d Vector3d::operator/(float k)
           {
               if (k == 0) { throw std::invalid_argument("Division by zero is not allowed."); }
               return Vector3d(x / k,
                   y / k,
                   z / k);
           }
   
           float Vector3d::operator[](int index)
           {
               switch (index) {
               case 0: return x;
               case 1: return y;
               case 2: return z;
               case 3: return w;
               default:
                   throw std::out_of_range("Index out of range. Valid indices are 0, 1, 2, 3.");
               }
           }
           bool Vector3d::operator==(Vector3d& other) {
               if (other.x == x && other.y == y && other.z == z) {
                   return true;
               }
               return false;
           }
   
           float Vector3d::length()
           {
               return sqrtf(Vector_DotProduct(*this, *this));
           }
   
           Vector3d Vector3d::normalise()
           {
               float l = length();
               return Vector3d(x / l,
                               y / l,
                               z / l );
           }
   
           float Vector_DotProduct(Vector3d& v1, Vector3d& v2)
           {
               return v1.x * v2.x +
                      v1.y * v2.y +
                      v1.z * v2.z;
           }
   
           Vector3d Vector_CrossProduct(Vector3d& v1, Vector3d& v2)
           {
               Vector3d v;
               v.x = v1.y * v2.z - v1.z * v2.y;
               v.y = v1.z * v2.x - v1.x * v2.z;
               v.z = v1.x * v2.y - v1.y * v2.x;
               return v;
           }
   
           Vector3d Vector_IntersectPlane(Vector3d& plane_p, Vector3d& plane_n, Vector3d& lineStart, Vector3d& lineEnd) {
               plane_n = plane_n.normalise();
               float plane_d = -Vector_DotProduct(plane_n, plane_p);
               float ad = Vector_DotProduct(lineStart, plane_n);
               float bd = Vector_DotProduct(lineEnd, plane_n);
               float t = (-plane_d - ad) / (bd - ad);
               Vector3d lineStartToEnd = lineEnd - lineStart;
               Vector3d lineToIntersect = lineStartToEnd * t;
               return lineStart + lineToIntersect;
           }
   
       }
   }
