#include "renderSystem.h"
#include "cameraComponent.h"
#include "transformComponent.h"
#include "meshComponent.h"
#include "materialComponent.h"
#include "lightsComponent.h"

void prism::scene::RenderSystem::update()
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
        std::vector<prism::render::InstanceData> renderData;
        std::map<Mesh, std::vector<prism::render::InstanceData>> instances;
        MaterialComponent defaultTexture = { INVALID_TEXTURE_ID };

        for (auto entity : forRenderingEntites) {
            MaterialComponent* texture;

            if (scene->getComponent<MaterialComponent>(entity) != nullptr) {
                texture = scene->getComponent<MaterialComponent>(entity);
            }
            else {
                texture = &defaultTexture;
            }
            instances[scene->getComponent<MeshComponent>(entity)->mesh].push_back({ scene->getComponent<TransformComponent>(entity), texture });
        }

        for (auto instance : instances) {
            for (auto renData : instance.second) {
                renderData.push_back(renData);
            }

        }

        prism::render::LightData lightData;
        auto pointsLightEntitys =  scene->getEntitiesWith<PointLightComponent>();
        for (auto pointLightEntity : pointsLightEntitys) {
            PointLightComponent pointsLight = *scene->getComponent<PointLightComponent>(pointLightEntity);
            
            if (auto transform = scene->getComponent<TransformComponent>(pointLightEntity)) { pointsLight.pos += transform->pos; }
            lightData.pointLights.push_back(pointsLight);
        }

        auto directionalLightEntitys = scene->getEntitiesWith<DirectionalLightComponents>();
        for (auto directionalLightEntity : directionalLightEntitys) {
            DirectionalLightComponents dirLight = *scene->getComponent<DirectionalLightComponents>(directionalLightEntity);
            lightData.directionalLights.push_back(dirLight);
        }

        renderer->updateInstances(renderData);
        renderer->updateLights(&lightData);
        renderer->beginRender();

        renderer->bindDefault();
        renderer->bindObjectsData();

        uint32_t instanceOffset = 0;
        for (auto instance : instances) {
            renderer->drawMesh(instance.first, instance.second.size(), instanceOffset);
            instanceOffset+=instance.second.size();
        }

        renderer->endRender();
        renderer->endFrame();

     }
}
