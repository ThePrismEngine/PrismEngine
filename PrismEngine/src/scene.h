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
#include "resourceManager.h"


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
            /// @see prism::scene::SystemManager::update
            void update() {
                systemManager.update();
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
            /// @return Ссылка на вектор сущностей с компонентом
            /// @see prism::scene::ComponentManager::getEntitiesWith
            template<typename T>
            std::vector<Entity>& getEntitiesWith() {
                return componentManager.getEntitiesWith<T>();
            };

            /// @brief Получает сущности, имеющие все указанные типы компонентов
            /// @tparam ComponentTypes Типы компонентов для поиска
            /// @return Вектор сущностей, содержащих все запрошенные компоненты
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

            /// @brief Устанавливает или заменяет глобальный ресурс на сцене
            /// @tparam T Тип ресурса
            /// @param resource Объект ресурса для установки
            /// @details Ресурсы представляют собой глобальные данные, доступные всем системам.
            /// Каждый тип ресурса может существовать только в одном экземпляре на сцене.
            /// 
            /// Пример:
            /// @code
            /// // Установка стандартных ресурсов
            /// scene.setResource<Time>(Time{});
            /// scene.setResource<Input>(Input{});
            /// scene.setResource<Config>(Config{1920, 1080, "My Game"});
            /// 
            /// // Замена ресурса
            /// scene.setResource<Config>(loadConfigFromFile("settings.cfg"));
            /// @endcode
            /// 
            /// @see prism::scene::ResourceManager::set
            template<typename T>
            void setResource(T resource) {
                resourceManager.set<T>(resource);
            }

            /// @brief Получает глобальный ресурс сцены
            /// @tparam T Тип запрашиваемого ресурса
            /// @return Указатель на ресурс или nullptr если ресурс не найден
            /// @details Обеспечивает доступ к глобальным данным сцены. Возвращаемый
            /// указатель можно использовать для модификации ресурса.
            /// 
            /// Пример:
            /// @code
            /// // В системе времени
            /// if (auto* time = scene.getResource<Time>()) {
            ///     time->update(deltaTime);
            /// }
            /// 
            /// // В системе ввода
            /// if (auto* input = scene.getResource<Input>()) {
            ///     if (input->isKeyPressed(KEY_SPACE)) {
            ///         jump();
            ///     }
            /// }
            /// @endcode
            /// 
            /// @see prism::scene::ResourceManager::get
            template<typename T>
            T* getResource() {
                return resourceManager.get<T>();
            }

            /// @brief Получает константный глобальный ресурс сцены
            /// @tparam T Тип запрашиваемого ресурса
            /// @return Константный указатель на ресурс или nullptr если ресурс не найден
            /// @details Предназначен для безопасного доступа только для чтения к глобальным
            /// ресурсам сцены. Используется в константных контекстах.
            /// 
            /// Пример:
            /// @code
            /// // В константном методе рендеринга
            /// void render(const Scene& scene) {
            ///     if (const auto* config = scene.getResource<Config>()) {
            ///         setResolution(config->width, config->height);
            ///     }
            /// }
            /// @endcode
            /// 
            /// @see prism::scene::ResourceManager::get
            template<typename T>
            const T* getResource() const {
                return resourceManager.get<T>();
            }

            /// @brief Проверяет наличие глобального ресурса на сцене
            /// @tparam T Тип проверяемого ресурса
            /// @return true если ресурс существует, false в противном случае
            /// @details Быстрая проверка существования ресурса без его загрузки.
            /// 
            /// Пример:
            /// @code
            /// // Ленивая инициализация ресурса
            /// if (!scene.hasResource<Audio>()) {
            ///     scene.setResource<Audio>(Audio{});
            ///     scene.getResource<Audio>()->initialize();
            /// }
            /// @endcode
            /// 
            /// @see prism::scene::ResourceManager::has
            template<typename T>
            bool hasResource() const {
                return resourceManager.has<T>();
            }

            /// @brief Удаляет глобальный ресурс со сцены
            /// @tparam T Тип удаляемого ресурса
            /// @return true если ресурс был удален, false если ресурс не существовал
            /// @details Освобождает память, занимаемую ресурсом. Последующие вызовы
            /// getResource() для этого типа вернут nullptr.
            /// 
            /// Пример:
            /// @code
            /// // Удаление временного ресурса
            /// scene.removeResource<DebugOverlay>();
            /// 
            /// // Удаление при перезагрузке
            /// scene.removeResource<Config>();
            /// scene.setResource<Config>(loadNewConfig());
            /// @endcode
            /// 
            /// @see prism::scene::ResourceManager::remove
            template<typename T>
            bool removeResource() {
                return resourceManager.remove<T>();
            }
        private:
            EntityManager entityManager;      /// Менеджер сущностей
            ComponentManager componentManager;/// Менеджер компонентов
            SystemManager systemManager;      /// Менеджер систем
            ResourceManager resourceManager;  /// Менеджер ресурсов
        };
    }
}