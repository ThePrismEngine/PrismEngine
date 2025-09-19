#include "entityManager.h"


prism::scene::Entity prism::scene::EntityManager::createEntity()
{
    if (!freeList.empty()) {
        Entity id = freeList.front();
        freeList.pop();
        return id;
    }
    return nextEntityId++;
}

bool prism::scene::EntityManager::destroyEntity(Entity entityId)
{
    if (entityId == INVALID_ENTITY_ID || entityId >= nextEntityId) {
        return false;
    }
    freeList.push(entityId);
    return true;
}

bool prism::scene::EntityManager::isEntityValid(Entity entityId) const
{
    return entityId != INVALID_ENTITY_ID && entityId < nextEntityId;
}
