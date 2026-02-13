#include "systemManager.h"

void prism::scene::SystemManager::enableSystem(SystemId systemId)
{
	if (systemId < systems.size() && !systems[systemId]->isEnabled()) {
		systems[systemId]->enabled = true;
		activeSystems.push_back(systems[systemId].get());
	}
}

void prism::scene::SystemManager::disableSystem(SystemId systemId)
{
	if (systemId < systems.size() && systems[systemId]->isEnabled()) {
		systems[systemId]->enabled = false;
		auto it = std::find(activeSystems.begin(), activeSystems.end(), systems[systemId].get());
		if (it != activeSystems.end()) activeSystems.erase(it);
	}
}

void prism::scene::SystemManager::update()
{
	for (auto& system : activeSystems) {
		if (!system->isStarted()) {
			system->start();
			system->started = true;
		}
		system->update();
	}
}