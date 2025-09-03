#include "entityManager.h"


prism::world::Entity prism::world::EntityManager::createEntity()
{
    if (!freeList.empty()) {
        Entity id = freeList.front();
        freeList.pop();
        return id;
    }
    return nextEntityId++;
}

bool prism::world::EntityManager::destroyEntity(Entity entityId)
{
    if (entityId == INVALID_ENTITY_ID || entityId >= nextEntityId) {
        return false;
    }
    freeList.push(entityId);
    return true;
}

bool prism::world::EntityManager::isEntityValid(Entity entityId) const
{
    return entityId != INVALID_ENTITY_ID && entityId < nextEntityId;
}
