#pragma once
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <set>
#include <queue>
#include "entityManager.h"
#include "componentManager.h"
#include "systemManager.h"


namespace prism {
	namespace world {

        class World
        {
        public:
            World() = default;

            Entity createEntity();
            bool destroyEntity(Entity entityId);

            void enableSystem(SystemId systemId);
            void disableSystem(SystemId systemId);

            void update(float deltaTime) {
                systemManager.update(deltaTime);
            }

            //с шаблонами определины здесь в .h (по другому не компилится)
            template<typename T>
            bool addComponent(Entity entityId, T component) {
                return componentManager.addComponent(entityId, component);
            };

            template<typename T>
            bool removeComponent(Entity entityId) {
                return componentManager.removeComponent<T>(entityId);
            };

            template<typename T>
            T* getComponent(Entity entityId) {
                return componentManager.getComponent<T>(entityId);
            };

            template<typename T>
            std::set<Entity>& getEntitiesWith() {
                return componentManager.getEntitiesWith<T>();
            };

            template<typename... ComponentTypes>
            std::set<Entity> getEntitiesWithAll() {
                return componentManager.getEntitiesWithAll<ComponentTypes...>();
            };

            template<typename T, typename... Args>
            SystemId registerSystem(Args&&... args) {
                return systemManager.registerSystem<T>(std::forward<Args>(args)...);
            };

        private:
            EntityManager entityManager;
            ComponentManager componentManager;
            SystemManager systemManager;
        };
    }
}