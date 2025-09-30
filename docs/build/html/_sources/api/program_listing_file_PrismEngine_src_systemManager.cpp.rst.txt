
.. _program_listing_file_PrismEngine_src_systemManager.cpp:

Program Listing for File systemManager.cpp
==========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_systemManager.cpp>` (``PrismEngine\src\systemManager.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "systemManager.h"
   
   void prism::scene::SystemManager::enableSystem(SystemId systemId)
   {
       if (systemId < systems.size()) {
           systems[systemId]->enabled = true;
       }
   }
   
   void prism::scene::SystemManager::disableSystem(SystemId systemId)
   {
       if (systemId < systems.size()) {
           systems[systemId]->enabled = false;
       }
   }
   
   void prism::scene::SystemManager::update(float deltaTime)
   {
       for (auto& system : systems) {
           if (system->enabled) {
               system->update(deltaTime);
           }
       }
   }
