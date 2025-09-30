
.. _program_listing_file_PrismEngine_src_renderSystem.cpp:

Program Listing for File renderSystem.cpp
=========================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_renderSystem.cpp>` (``PrismEngine\src\renderSystem.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "renderSystem.h"
   #include "cameraComponent.h"
   #include "transformComponent.h"
   #include "meshComponent.h"
   #include "textureComponent.h"
   
   void prism::scene::RenderSystem::update(float deltaTime)
   {
       if (renderer->isRenderingActive()) {
           renderer->beginFrame();
   
           auto cameras = scene->getEntitiesWithAll<TransformComponent, CameraComponent>();
           for (auto camera : cameras) {
               CameraComponent* cameraComponent = scene->getComponent<CameraComponent>(camera);
               if (cameraComponent->isActive) {
                   TransformComponent* transformComponent = scene->getComponent<TransformComponent>(camera);
                   renderer->updateCamera(transformComponent, cameraComponent);
               }
           }
           uint32_t i = 0;
           auto forRenderingEntites = scene->getEntitiesWithAll<TransformComponent, MeshComponent>();
           for (auto entity : forRenderingEntites) {
               renderer->updateObjectTransform(scene->getComponent<TransformComponent>(entity), i++);
           }
   
           renderer->beginRender();
   
           renderer->bindDefault();
           i = 0;
           for (auto entity : forRenderingEntites) {
               renderer->bindTransform(i++);
               if (scene->getComponent<TextureComponent>(entity) == nullptr) {
                   renderer->pushTextureId(INVALID_TEXTURE);
               }
               else {
                   renderer->pushTextureId(scene->getComponent<TextureComponent>(entity)->texture);
               }
               renderer->drawMesh(scene->getComponent<MeshComponent>(entity)->mesh);
           }
   
   
           renderer->endRender();
           renderer->endFrame();
   
        }
   }
