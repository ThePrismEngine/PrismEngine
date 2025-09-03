#pragma once
#include "entity.h"
#include <queue>

namespace prism {
	namespace world {
        class EntityManager
        {
        public:
            EntityManager() : nextEntityId(1) {}

            Entity createEntity();
            bool destroyEntity(Entity entityId);
            bool isEntityValid(Entity entityId) const;

        private:
            Entity nextEntityId;
            std::queue<Entity> freeList;
        };
	}
}