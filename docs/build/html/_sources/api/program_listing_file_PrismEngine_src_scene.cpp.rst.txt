
.. _program_listing_file_PrismEngine_src_scene.cpp:

Program Listing for File scene.cpp
==================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_scene.cpp>` (``PrismEngine\src\scene.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "scene.h"
   
   prism::scene::Entity prism::scene::Scene::createEntity()
   {
       return entityManager.createEntity();
   }
   
   bool prism::scene::Scene::destroyEntity(Entity entityId)
   {
       componentManager.removeAllComponents(entityId);
       return entityManager.destroyEntity(entityId);
   }
   
   void prism::scene::Scene::enableSystem(SystemId systemId)
   {
       systemManager.enableSystem(systemId);
   }
   
   void prism::scene::Scene::disableSystem(SystemId systemId)
   {
       systemManager.disableSystem(systemId);
   }
