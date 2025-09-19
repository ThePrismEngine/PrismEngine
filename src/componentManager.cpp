#include "componentManager.h"

void prism::scene::ComponentManager::removeAllComponents(Entity entityId)
{
	for (auto& pair : componentStorages) {
		pair.second->removeEntity(entityId);
	}

	for (auto& pair : entitiesWithComponentSets) {
		pair.second->erase(entityId);
	}
}
