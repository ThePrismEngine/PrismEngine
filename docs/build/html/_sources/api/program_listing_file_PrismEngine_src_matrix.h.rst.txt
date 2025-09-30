
.. _program_listing_file_PrismEngine_src_matrix.h:

Program Listing for File matrix.h
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_matrix.h>` (``PrismEngine\src\matrix.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   
   #pragma once
   #include <stdexcept>
   #include "SDL.h"
   #include "vector.h"
   
   namespace prism {
       namespace math {
   
           struct Matrix4X4 {
               float m[4][4] = { 0 }; 
   
               void print();
   
               float* operator[](int index);
   
               bool operator==(Matrix4X4& other);
   
               Matrix4X4 getTransposed();
   
               static Matrix4X4 makeIdentity();
   
               static Matrix4X4 makeRotationX(float fAngleRad);
   
               static Matrix4X4 makeRotationY(float fAngleRad);
   
               static Matrix4X4 makeRotationZ(float fAngleRad);
   
               static Matrix4X4 makeTranslation(float x, float y, float z);
   
               static Matrix4X4 makeScale(float x, float y, float z);
   
               static Matrix4X4 makeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
   
               static Matrix4X4 Matrix_PointAt(Vector3d& pos, Vector3d& target, Vector3d& up);
           };
   
           static Matrix4X4 Matrix_MultiplyMatrix(Matrix4X4& m1, Matrix4X4& m2);
   
           Matrix4X4 Matrix_QuickInverse(Matrix4X4& m);
       } // namespace math
   } // namespace prism
