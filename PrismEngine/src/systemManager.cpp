#include "systemManager.h"

void prism::scene::SystemManager::enableSystem(SystemId systemId)
{
	if (systemId < systems.size()) {
		systems[systemId]->enabled = true;
	}
}

void prism::scene::SystemManager::disableSystem(SystemId systemId)
{
	if (systemId < systems.size()) {
		systems[systemId]->enabled = false;
	}
}

void prism::scene::SystemManager::update()
{
	for (auto& system : systems) {
		if (system->enabled) {
			if (!system->started) {
				system->start();
				system->started = true;
			}
			
			system->update();
		}
	}
}