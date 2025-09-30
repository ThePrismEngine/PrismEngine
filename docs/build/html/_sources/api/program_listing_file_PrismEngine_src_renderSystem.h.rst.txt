
.. _program_listing_file_PrismEngine_src_renderSystem.h:

Program Listing for File renderSystem.h
=======================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_renderSystem.h>` (``PrismEngine\src\renderSystem.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "scene.h"
   #include "renderer.h"
   
   
   namespace prism {
       namespace scene {
           class RenderSystem : public ISystem {
           public:
               RenderSystem(Scene* scene, render::Renderer* renderer) : scene(scene), renderer(renderer) {}
               void update(float deltaTime) override;
   
           private:
               prism::scene::Scene* scene;
               prism::render::Renderer* renderer;
           };
       }
   }
