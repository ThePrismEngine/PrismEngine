#include "scene.h"

prism::scene::Entity prism::scene::Scene::createEntity()
{
	return entityManager.createEntity();
}

bool prism::scene::Scene::destroyEntity(Entity entityId)
{
	componentManager.removeAllComponents(entityId);
	return entityManager.destroyEntity(entityId);
}

void prism::scene::Scene::enableSystem(SystemId systemId)
{
	systemManager.enableSystem(systemId);
}

void prism::scene::Scene::disableSystem(SystemId systemId)
{
	systemManager.disableSystem(systemId);
}
