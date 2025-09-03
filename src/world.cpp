#include "world.h"

prism::world::Entity prism::world::World::createEntity()
{
	return entityManager.createEntity();
}

bool prism::world::World::destroyEntity(Entity entityId)
{
	componentManager.removeAllComponents(entityId);
	return entityManager.destroyEntity(entityId);
}

void prism::world::World::enableSystem(SystemId systemId)
{
	systemManager.enableSystem(systemId);
}

void prism::world::World::disableSystem(SystemId systemId)
{
	systemManager.disableSystem(systemId);
}
