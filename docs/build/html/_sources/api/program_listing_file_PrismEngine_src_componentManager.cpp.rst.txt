
.. _program_listing_file_PrismEngine_src_componentManager.cpp:

Program Listing for File componentManager.cpp
=============================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_componentManager.cpp>` (``PrismEngine\src\componentManager.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "componentManager.h"
   
   void prism::scene::ComponentManager::removeAllComponents(Entity entityId)
   {
       for (auto& pair : componentStorages) {
           pair.second->removeEntity(entityId);
       }
   
       for (auto& pair : entitiesWithComponentSets) {
           pair.second->erase(entityId);
       }
   }
