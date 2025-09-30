
.. _program_listing_file_PrismEngine_src_matrix.cpp:

Program Listing for File matrix.cpp
===================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_matrix.cpp>` (``PrismEngine\src\matrix.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "matrix.h"
   
   
   namespace prism {
       namespace math {
           void Matrix4X4::print()
           {
               SDL_Log("");
           }
           float* Matrix4X4::operator[](int index)
           {
               if (index < 0 || index >= 4)
               {
                   throw std::out_of_range("Index out of range. Valid indices are 0, 1, 2, 3.");
               }
               return m[index];
           }
   
           bool Matrix4X4::operator==(Matrix4X4& other)
           {
               return m == other.m;
           }
   
           Matrix4X4 Matrix4X4::makeIdentity()
           {
               Matrix4X4 matrix;
               matrix.m[0][0] = 1.0f;
               matrix.m[1][1] = 1.0f;
               matrix.m[2][2] = 1.0f;
               matrix.m[3][3] = 1.0f;
               return matrix;
           }
   
           Matrix4X4 Matrix4X4::makeRotationX(float fAngleRad)
           {
               Matrix4X4 matrix;
               matrix.m[0][0] = 1.0f;
               matrix.m[1][1] = cosf(fAngleRad);
               matrix.m[1][2] = sinf(fAngleRad);
               matrix.m[2][1] = -sinf(fAngleRad);
               matrix.m[2][2] = cosf(fAngleRad);
               matrix.m[3][3] = 1.0f;
               return matrix;
           }
   
   
           Matrix4X4 Matrix4X4::makeRotationY(float fAngleRad)
           {
               Matrix4X4 matrix;
               matrix.m[0][0] = cosf(fAngleRad);
               matrix.m[0][2] = sinf(fAngleRad);
               matrix.m[2][0] = -sinf(fAngleRad);
               matrix.m[1][1] = 1.0f;
               matrix.m[2][2] = cosf(fAngleRad);
               matrix.m[3][3] = 1.0f;
               return matrix;
           }
   
           Matrix4X4 Matrix4X4::makeRotationZ(float fAngleRad)
           {
               Matrix4X4 matrix;
               matrix.m[0][0] = cosf(fAngleRad);
               matrix.m[0][1] = sinf(fAngleRad);
               matrix.m[1][0] = -sinf(fAngleRad);
               matrix.m[1][1] = cosf(fAngleRad);
               matrix.m[2][2] = 1.0f;
               matrix.m[3][3] = 1.0f;
               return matrix;
           }
   
           Matrix4X4 Matrix4X4::makeTranslation(float x, float y, float z)
           {
               Matrix4X4 matrix;
               matrix.m[0][0] = 1.0f;
               matrix.m[1][1] = 1.0f;
               matrix.m[2][2] = 1.0f;
               matrix.m[3][3] = 1.0f;
               matrix.m[3][0] = x;
               matrix.m[3][1] = y;
               matrix.m[3][2] = z;
               return matrix;
           }
   
           Matrix4X4 Matrix4X4::makeScale(float x, float y, float z)
           {
               Matrix4X4 matrix;
               matrix.m[0][0] = x;
               matrix.m[1][1] = y;
               matrix.m[2][2] = z;
               matrix.m[3][3] = 1.0f;
               return matrix;
           }
   
           Matrix4X4 Matrix4X4::makeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar)
           {
               //  float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);
               Matrix4X4 matrix;
               matrix.m[0][0] = fAspectRatio * fFovDegrees;
               matrix.m[1][1] = fFovDegrees;
               matrix.m[2][2] = fFar / (fFar - fNear);
               matrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
               matrix.m[2][3] = 1.0f;
               matrix.m[3][3] = 0.0f;
               return matrix;
           }
   
           Matrix4X4 Matrix4X4::getTransposed()
           {
               Matrix4X4 matrix(*this);
               for (int i = 0; i < 4; ++i) {
                   for (int j = i + 1; j < 4; ++j) {
                       std::swap(matrix.m[i][j], matrix.m[j][i]);
                   }
               }
               return matrix;
           }
           
           Matrix4X4 Matrix4X4::Matrix_PointAt(Vector3d& pos, Vector3d& target, Vector3d& up)
           {
               // Calculate new forward direction
               Vector3d newForward = target - pos;
               newForward = newForward.normalise();
   
               // Calculate new Up direction
               Vector3d a = newForward * Vector_DotProduct(up, newForward);
               Vector3d newUp = up - a;
               newUp = newUp.normalise();
   
               // New Right direction is easy, its just cross product
               Vector3d newRight = Vector_CrossProduct(newUp, newForward);
   
               // Construct Dimensioning and Translation Matrix    
               Matrix4X4 matrix;
               matrix.m[0][0] = newRight.x;    matrix.m[0][1] = newRight.y;    matrix.m[0][2] = newRight.z;    matrix.m[0][3] = 0.0f;
               matrix.m[1][0] = newUp.x;       matrix.m[1][1] = newUp.y;       matrix.m[1][2] = newUp.z;       matrix.m[1][3] = 0.0f;
               matrix.m[2][0] = newForward.x;  matrix.m[2][1] = newForward.y;  matrix.m[2][2] = newForward.z;  matrix.m[2][3] = 0.0f;
               matrix.m[3][0] = pos.x;         matrix.m[3][1] = pos.y;         matrix.m[3][2] = pos.z;         matrix.m[3][3] = 1.0f;
               return matrix;
           }
   
           Matrix4X4 Matrix_MultiplyMatrix(Matrix4X4& m1, Matrix4X4& m2)
           {
               Matrix4X4 matrix;
               for (int c = 0; c < 4; c++)
                   for (int r = 0; r < 4; r++)
                       matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
               return matrix;
           }
           Matrix4X4 Matrix_QuickInverse(Matrix4X4& m)
           {
               Matrix4X4 matrix;
               matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
               matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
               matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
               matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
               matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
               matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
               matrix.m[3][3] = 1.0f;
               return matrix;
           }
       }
   }
