
.. _program_listing_file_PrismEngine_src_systemManager.h:

Program Listing for File systemManager.h
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_systemManager.h>` (``PrismEngine\src\systemManager.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <vector>
   #include <memory>
   #include "system.h"
   
   
   namespace prism {
       namespace scene {
           class SystemManager
           {
           public:
               SystemManager() = default;
   
               template<typename T, typename... Args>
               SystemId registerSystem(Args&&... args) {
                   systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
                   return systems.size() - 1;
               };
   
               void enableSystem(SystemId systemId);
   
               void disableSystem(SystemId systemId);
   
               
               void update(float deltaTime);
   
           private:
               std::vector<std::unique_ptr<ISystem>> systems;
           };
       }
   }
