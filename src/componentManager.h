#pragma once
#include "entity.h"
#include <unordered_map>
#include <set>
#include <typeindex>
#include <memory>
#include <algorithm>
#include <iterator>

namespace prism {
    namespace world {
        class ComponentManager
        {
        public:
            ComponentManager() = default;

            template<typename T>
            bool addComponent(Entity entityId, T component) {
                auto& storage = getComponentStorage<T>();
                storage.components[entityId] = std::make_shared<T>(component);
                getEntitiesWith<T>().insert(entityId);
                return true;
            }

            template<typename T>
            bool removeComponent(Entity entityId) {
                auto& storage = getComponentStorage<T>();
                auto it = storage.components.find(entityId);
                if (it == storage.components.end()) return false;

                storage.components.erase(it);
                getEntitiesWith<T>().erase(entityId);
                return true;
            }

            template<typename T>
            T* getComponent(Entity entityId) {
                auto& storage = getComponentStorage<T>();
                auto it = storage.components.find(entityId);
                if (it == storage.components.end()) return nullptr;
                return it->second.get();
            }

            template<typename T>
            const std::set<Entity>& getEntitiesWith() const {
                static const std::set<Entity> emptySet;
                auto typeIndex = std::type_index(typeid(T));
                auto it = entitiesWithComponentSets.find(typeIndex);
                if (it == entitiesWithComponentSets.end()) return emptySet;
                return *it->second;
            }

            template<typename T>
            std::set<Entity>& getEntitiesWith() {
                auto typeIndex = std::type_index(typeid(T));
                if (entitiesWithComponentSets.find(typeIndex) == entitiesWithComponentSets.end()) {
                    entitiesWithComponentSets[typeIndex] = std::make_unique<std::set<Entity>>();
                }
                return *entitiesWithComponentSets[typeIndex];
            }

            template<typename... ComponentTypes>
            std::set<Entity> getEntitiesWithAll() const {
                if constexpr (sizeof...(ComponentTypes) == 0) {
                    return std::set<Entity>();
                }
                else {
                    // Получаем множества для каждого типа компонентов
                    std::vector<const std::set<Entity>*> sets;
                    (sets.push_back(&getEntitiesWith<ComponentTypes>()), ...);

                    // Находим наименьшее множество для оптимизации
                    auto smallestIt = std::min_element(sets.begin(), sets.end(),
                        [](const std::set<Entity>* a, const std::set<Entity>* b) {
                            return a->size() < b->size();
                        });

                    std::set<Entity> result = **smallestIt;

                    // Пересекаем с остальными множествами
                    for (const auto& entitySetPtr : sets) {
                        if (entitySetPtr == *smallestIt) continue;

                        std::set<Entity> temp;
                        std::set_intersection(
                            result.begin(), result.end(),
                            entitySetPtr->begin(), entitySetPtr->end(),
                            std::inserter(temp, temp.begin())
                        );
                        result = std::move(temp);
                    }
                    
                    return result;
                }
            }

            void removeAllComponents(Entity entityId);

        private:
            struct IComponentStorage {
                virtual ~IComponentStorage() = default;
                virtual void removeEntity(Entity entityId) = 0;
            };

            template<typename T>
            struct ComponentStorage : public IComponentStorage {
                std::unordered_map<Entity, std::shared_ptr<T>> components;

                void removeEntity(Entity entityId) override {
                    components.erase(entityId);
                }
            };

            template<typename T>
            ComponentStorage<T>& getComponentStorage() {
                auto typeIndex = std::type_index(typeid(T));
                if (componentStorages.find(typeIndex) == componentStorages.end()) {
                    componentStorages[typeIndex] = std::make_unique<ComponentStorage<T>>();
                }
                return static_cast<ComponentStorage<T>&>(*componentStorages[typeIndex]);
            }

            std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> componentStorages;
            std::unordered_map<std::type_index, std::unique_ptr<std::set<Entity>>> entitiesWithComponentSets;
        };
    }
}