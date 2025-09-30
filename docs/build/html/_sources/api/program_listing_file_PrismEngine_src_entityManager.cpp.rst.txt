
.. _program_listing_file_PrismEngine_src_entityManager.cpp:

Program Listing for File entityManager.cpp
==========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_entityManager.cpp>` (``PrismEngine\src\entityManager.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "entityManager.h"
   
   
   prism::scene::Entity prism::scene::EntityManager::createEntity()
   {
       if (!freeList.empty()) {
           Entity id = freeList.front();
           freeList.pop();
           return id;
       }
       return nextEntityId++;
   }
   
   bool prism::scene::EntityManager::destroyEntity(Entity entityId)
   {
       if (entityId == INVALID_ENTITY_ID || entityId >= nextEntityId) {
           return false;
       }
       freeList.push(entityId);
       return true;
   }
   
   bool prism::scene::EntityManager::isEntityValid(Entity entityId) const
   {
       return entityId != INVALID_ENTITY_ID && entityId < nextEntityId;
   }
