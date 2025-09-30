
.. _program_listing_file_PrismEngine_src_system.h:

Program Listing for File system.h
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_system.h>` (``PrismEngine\src\system.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   namespace prism {
       namespace scene {
           typedef uint32_t SystemId;
   
           const SystemId INVALID_SYSTEM_ID = 0;
   
           class ISystem {
           public:
               virtual ~ISystem() = default;
   
               virtual void update(float deltaTime) = 0;
   
               bool enabled = true;
           };
       }
   }
