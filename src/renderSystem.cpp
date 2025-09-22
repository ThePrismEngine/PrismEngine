#include "renderSystem.h"
#include "cameraComponent.h"
#include "transformComponent.h"
#include "meshComponent.h"

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
        auto forRenderingEntites = scene->getEntitiesWithAll<TransformComponent, MeshComponent>();
        for (auto entity : forRenderingEntites) {
            renderer->updateObjectTransform(scene->getComponent<TransformComponent>(entity), entity);
        }

        renderer->beginRender();

        renderer->bindDefault();

        for (auto entity : forRenderingEntites) {
            renderer->bindTransform(entity);
            renderer->pushTextureId(0);
            renderer->drawMesh(scene->getComponent<MeshComponent>(entity)->mesh);
        }


        renderer->endRender();
        renderer->endFrame();

     }
}
