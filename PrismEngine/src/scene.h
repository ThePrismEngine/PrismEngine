#pragma once
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
	namespace scene {
        /// @brief Основной класс сцены, объединяющий менеджеры сущностей, компонентов и систем
        /// @details Координирует работу всех подсистем ECS (Entity-Component-System)
        class Scene
        {
        public:
            Scene() = default;

            /// @brief Создает новую сущность на сцене
            /// @return Идентификатор созданной сущности
            /// @see prism::scene::EntityManager::createEntity
            Entity createEntity();

            /// @brief Удаляет сущность со сцены
            /// @param entityId Идентификатор сущности для удаления
            /// @return true если сущность успешно удалена
            /// @details Удаляет все компоненты сущности перед ее уничтожением
            /// @see prism::scene::ComponentManager::removeAllComponents, EntityManager::destroyEntity
            bool destroyEntity(Entity entityId);

            /// @brief Включает систему на сцене
            /// @param systemId Идентификатор системы для включения
            /// @see prism::scene::SystemManager::enableSystem
            void enableSystem(SystemId systemId);

            /// @brief Выключает систему на сцене
            /// @param systemId Идентификатор системы для выключения
            /// @see prism::scene::SystemManager::disableSystem
            void disableSystem(SystemId systemId);
            
            /// @brief Обновляет все активные системы сцены
            /// @param deltaTime Время, прошедшее с предыдущего обновления
            /// @see prism::scene::SystemManager::update
            void update(float deltaTime) {
                systemManager.update(deltaTime);
            }

            // шаблонные методы определены здесь в .h (по-другому не компилится)

            /// @brief Добавляет компонент к сущности на сцене
            /// @tparam T Тип компонента
            /// @param entityId Идентификатор сущности
            /// @param component Компонент для добавления
            /// @return true если компонент успешно добавлен
            /// @see prism::scene::ComponentManager::addComponent
            template<typename T>
            bool addComponent(Entity entityId, T component) {
                return componentManager.addComponent(entityId, component);
            };

            /// @brief Удаляет компонент у сущности на сцене
            /// @tparam T Тип компонента
            /// @param entityId Идентификатор сущности
            /// @return true если компонент существовал и был удален
            /// @see prism::scene::ComponentManager::removeComponent
            template<typename T>
            bool removeComponent(Entity entityId) {
                return componentManager.removeComponent<T>(entityId);
            };

            /// @brief Получает компонент сущности
            /// @tparam T Тип компонента
            /// @param entityId Идентификатор сущности
            /// @return Указатель на компонент или nullptr если не найден
            /// @see prism::scene::ComponentManager::getComponent
            template<typename T>
            T* getComponent(Entity entityId) {
                return componentManager.getComponent<T>(entityId);
            };

            /// @brief Получает все сущности, имеющие компонент указанного типа
            /// @tparam T Тип компонента
            /// @return Ссылка на множество сущностей с компонентом
            /// @see prism::scene::ComponentManager::getEntitiesWith
            template<typename T>
            std::set<Entity>& getEntitiesWith() {
                return componentManager.getEntitiesWith<T>();
            };

            /// @brief Получает сущности, имеющие все указанные типы компонентов
            /// @tparam ComponentTypes Типы компонентов для поиска
            /// @return Множество сущностей, содержащих все запрошенные компоненты
            /// @see prism::scene::ComponentManager::getEntitiesWithAll
            template<typename... ComponentTypes>
            std::set<Entity> getEntitiesWithAll() {
                return componentManager.getEntitiesWithAll<ComponentTypes...>();
            };

            /// @brief Регистрирует новую систему на сцене
            /// @tparam T Тип системы (должен наследоваться от ISystem)
            /// @tparam Args Типы аргументов для конструктора системы
            /// @param args Аргументы для передачи в конструктор системы
            /// @return Идентификатор зарегистрированной системы
            /// @see prism::scene::SystemManager::registerSystem
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