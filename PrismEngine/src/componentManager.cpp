#include "componentManager.h"

void prism::scene::ComponentManager::removeAllComponents(Entity entityId)
{
    for (auto& pair : componentStorages) {
        pair.second->removeEntity(entityId);
    }
}