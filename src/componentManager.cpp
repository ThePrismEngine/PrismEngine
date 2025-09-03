#include "componentManager.h"

void prism::world::ComponentManager::removeAllComponents(Entity entityId)
{
	for (auto& pair : componentStorages) {
		pair.second->removeEntity(entityId);
	}

	for (auto& pair : entitiesWithComponentSets) {
		pair.second->erase(entityId);
	}
}
