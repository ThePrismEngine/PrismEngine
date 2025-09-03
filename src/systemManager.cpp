#include "systemManager.h"

void prism::world::SystemManager::enableSystem(SystemId systemId)
{
	if (systemId < systems.size()) {
		systems[systemId]->enabled = true;
	}
}

void prism::world::SystemManager::disableSystem(SystemId systemId)
{
	if (systemId < systems.size()) {
		systems[systemId]->enabled = false;
	}
}

void prism::world::SystemManager::update(float deltaTime)
{
	for (auto& system : systems) {
		if (system->enabled) {
			system->update(deltaTime);
		}
	}
}
