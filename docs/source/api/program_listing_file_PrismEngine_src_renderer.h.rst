
.. _program_listing_file_PrismEngine_src_renderer.h:

Program Listing for File renderer.h
===================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_renderer.h>` (``PrismEngine\src\renderer.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "prismGraphicCore.h"
   #include "Window.h"
   #include "transformComponent.h"
   #include "cameraComponent.h"
   #include "textureComponent.h"
   #include "meshComponent.h"
   
   namespace prism {
       namespace render {
          class Renderer
           {
           public:
               Renderer() : window(nullptr) {};
               void linkWindow(Window* window);
               void setDefaultSettings();
               void init();
               ~Renderer();
   
               bool isRenderingActive();
               void beginFrame();
               void beginRender();
               void endRender();
               void endFrame();
               void updateCamera(prism::scene::TransformComponent* transform, prism::scene::CameraComponent* camera);
               void updateObjectTransform(prism::scene::TransformComponent* transform, uint32_t transformId);
               void bindDefault();
               void bindTransform(uint32_t transformId);
               void pushTextureId(uint32_t textureId);
               void drawMesh(uint32_t meshId);
               scene::TextureComponent addTexture(const std::string& texturePath);
               void removeTexture(scene::TextureComponent texture);
   
               scene::MeshComponent addMesh(std::string texturePath);
               void updateMeshes();
               void clearMeshes();
   
               void awaitRenderingCompletion();
               void destroy();
   
               PGC::utils::Settings settings;
           private:
   
               PGC::PrismGraphicCore pgc;
               Window* window;
           };
       }
   }
