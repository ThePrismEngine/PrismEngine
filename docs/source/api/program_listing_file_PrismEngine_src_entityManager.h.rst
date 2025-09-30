
.. _program_listing_file_PrismEngine_src_entityManager.h:

Program Listing for File entityManager.h
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_entityManager.h>` (``PrismEngine\src\entityManager.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "entity.h"
   #include <queue>
   
   namespace prism {
       namespace scene {
           class EntityManager
           {
           public:
               EntityManager() : nextEntityId(1) {}
   
               Entity createEntity();
   
               bool destroyEntity(Entity entityId);
   
               bool isEntityValid(Entity entityId) const;
   
           private:
               Entity nextEntityId;
   
               std::queue<Entity> freeList;
           };
       }
   }
