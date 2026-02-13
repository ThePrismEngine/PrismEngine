#pragma once
#include "entity.h"
#include <unordered_map>
#include <set>
#include <typeindex>
#include <memory>
#include <algorithm>
#include <iterator>
#include <vector>

namespace prism {
    namespace scene {
        /// @brief Менеджер для управления компонентами сущностей
        /// @details Обеспечивает хранение, добавление, удаление и поиск компонентов
        class ComponentManager
        {
        public:
            ComponentManager() = default;

            /// @brief Добавляет компонент к сущности
            /// @tparam T Тип компонента
            /// @param entityId Идентификатор сущности
            /// @param component Компонент для добавления
            /// @return true если компонент успешно добавлен, false в противном случае
            /// @details Создает копию компонента и связывает его с сущностью
            template<typename T>
            bool addComponent(Entity entityId, T component) {
                ComponentStorage<T>& storage = getComponentStorage<T>();
				storage.addComponent(entityId, std::move(component));
                return true;
            }

            /// @brief Удаляет компонент у сущности
            /// @tparam T Тип компонента
            /// @param entityId Идентификатор сущности
            /// @return true если компонент существовал и был удален, false в противном случае
            template<typename T>
            bool removeComponent(Entity entityId) {
                ComponentStorage<T>& storage = getComponentStorage<T>();
				return storage.removeComponent(entityId);
            }

            /// @brief Проверяет, есть ли у сущности компонент типа T
            template<typename T>
            bool hasComponent(Entity entityId) const {
                const ComponentStorage<T>* storage = getComponentStorageConst<T>();
                return storage ? storage->hasComponent(entityId) : false;
            }

            /// @brief Получает компонент сущности
            /// @tparam T Тип компонента
            /// @param entityId Идентификатор сущности
            /// @return Указатель на компонент или nullptr если компонент не найден
            template<typename T>
            T* getComponent(Entity entityId) {
                ComponentStorage<T>& storage = getComponentStorage<T>();
				return storage.getComponent(entityId);
            }

            /// @brief Получает все сущности, имеющие компонент указанного типа
            /// @tparam T Тип компонента
            /// @return Константная ссылка на множество сущностей с компонентом
            template<typename T>
            const std::vector<Entity>& getEntitiesWithConst() const {
                static const std::vector<Entity> emptySet;
                const ComponentStorage<T>* storage = getComponentStorageConst<T>();
                return storage ? storage->entities : emptySet;
            }
            
            template<typename T>
            std::vector<Entity>& getEntitiesWith() {
                return getComponentStorage<T>().entities;
            }

            /// @brief Получает все сущности, имеющие все указанные типы компонентов
            /// @tparam ComponentTypes Типы компонентов для поиска
            /// @return Вектор сущностей, содержащих все запрошенные компоненты
            /// @details Выполняет пересечение множеств сущностей для каждого типа компонента
            template<typename... ComponentTypes>
            std::set<Entity> getEntitiesWithAll() const {
                if constexpr (sizeof...(ComponentTypes) == 0) {
                    return std::set<Entity>();
                }
                else {
                    // Собираем векторы сущностей для каждого типа
                    std::vector<const std::vector<Entity>*> entityVectors;
                    (entityVectors.push_back(&this->getEntitiesWithConst<ComponentTypes>()), ...);

                    // Выбираем самый маленький вектор для итерации
                    auto smallestIt = std::min_element(entityVectors.begin(), entityVectors.end(),
                        [](const auto* a, const auto* b) { return a->size() < b->size(); });
                    const auto& smallestVec = **smallestIt;

                    std::set<Entity> result;
                    for (Entity e : smallestVec) {
                        if ((hasComponent<ComponentTypes>(e) && ...)) {
                            result.insert(e);
                        }
                    }
                    return result;
                }
            }

            /// @brief Удаляет все компоненты у сущности
            /// @param entityId Идентификатор сущности
            void removeAllComponents(Entity entityId);

        private:
            /// @brief Базовый интерфейс хранилища компонентов
            struct IComponentStorage {
                virtual ~IComponentStorage() = default;

                /// @brief Удаляет все компоненты сущности из хранилища
                /// @param entityId Идентификатор сущности
                virtual void removeEntity(Entity entityId) = 0;
            };

            /// @brief Конкретная реализация хранилища для типа компонента
            /// @tparam T Тип компонента
            template<typename T>
            struct ComponentStorage : public IComponentStorage {
                /// @brief Плотный массив компонентов
                std::vector<T> components;

                // @brief Сущности, соответствующие компонентам
                std::vector<Entity> entities;

                // @brief Позиция в массивах
                std::unordered_map<Entity, size_t> entityToIndex;

                void addComponent(Entity entity, T&& component) {
                    auto it = entityToIndex.find(entity);
                    if (it != entityToIndex.end()) {
                        components[it->second] = std::move(component);
                        return;
                    }
                    size_t index = components.size();
                    components.push_back(std::move(component));
                    entities.push_back(entity);
                    entityToIndex[entity] = index;
                }

                bool removeComponent(Entity entity) {
                    auto it = entityToIndex.find(entity);
                    if (it == entityToIndex.end()) return false;

                    size_t index = it->second;
                    size_t lastIndex = components.size() - 1;

                    if (index != lastIndex) {
                        components[index] = std::move(components[lastIndex]);
                        entities[index] = entities[lastIndex];
                        entityToIndex[entities[index]] = index;
                    }

                    components.pop_back();
                    entities.pop_back();
                    entityToIndex.erase(it);
                    return true;
                }

                T* getComponent(Entity entity) {
                    auto it = entityToIndex.find(entity);
                    if (it == entityToIndex.end()) return nullptr;
                    return &components[it->second];
                }

                bool hasComponent(Entity entity) const {
                    return entityToIndex.find(entity) != entityToIndex.end();
                }

                void removeEntity(Entity entityId) override {
                    removeComponent(entityId);
                }
            };

            /// @brief Получает или создаёт хранилище для конкретного типа компонента
            /// @tparam T Тип компонента
            /// @return Ссылка на хранилище компонентов типа T
            template<typename T>
            ComponentStorage<T>& getComponentStorage() {
                auto typeIndex = std::type_index(typeid(T));
                auto it = componentStorages.find(typeIndex);
                if (it == componentStorages.end()) {
                    auto storage = std::make_unique<ComponentStorage<T>>();
                    auto* ptr = storage.get();
                    componentStorages[typeIndex] = std::move(storage);
                    return *ptr;
                }
                return static_cast<ComponentStorage<T>&>(*it->second);
            }

            template<typename T>
            const ComponentStorage<T>* getComponentStorageConst() const {
                auto typeIndex = std::type_index(typeid(T));
                auto it = componentStorages.find(typeIndex);
                if (it == componentStorages.end()) return nullptr;
                return static_cast<const ComponentStorage<T>*>(it->second.get());
            }

            // Карта "тип -> хранилище"
            std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> componentStorages;
        };
    }
}
