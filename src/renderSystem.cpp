#include "renderSystem.h"
#include "cameraComponent.h"
#include "transformComponent.h"

void prism::scene::RenderSystem::update(float deltaTime)
{
    auto cameras = scene->getEntitiesWithAll<TransformComponent, CameraComponent>();
    for (auto camera : cameras) {
        CameraComponent* cameraComponent = scene->getComponent<CameraComponent>(camera);
        if (cameraComponent->isActive) {
            TransformComponent* transformComponent = scene->getComponent<TransformComponent>(camera);
            renderer->updateCamera(transformComponent, cameraComponent);
        }
    }

    renderer->drawFrame();
}
