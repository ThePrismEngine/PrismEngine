#pragma once
#include "resource.h"
#include <queue>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <functional>
#include <any>

namespace prism {
    namespace scene {
        /// @brief Менеджер ресурсов для управления глобальными данными в ECS-системе
        /// @details Обеспечивает типобезопасное хранение и доступ к глобальным ресурсам,
        /// используя std::any для безопасного хранения объектов различных типов.
        /// Ресурсы представляют собой синглтон-подобные объекты, доступные всем системам сцены.
        /// @see prism::scene::Resource
        class ResourceManager
        {
        public:
            ResourceManager() = default;

            /// @brief Устанавливает или заменяет ресурс указанного типа
            /// @tparam T Тип ресурса
            /// @param resource Объект ресурса для сохранения
            /// @details Сохраняет переданный объект в менеджере ресурсов. Если ресурс
            /// данного типа уже существует, он будет заменен новым.
            /// 
            /// Примеры использования :
            /// @code
            /// // Создание ресурса с конструктором по умолчанию
            /// resources.set<TimeResource>(TimeResource{});
            /// 
            /// // Создание ресурса с параметрами
            /// resources.set<WindowConfig>(WindowConfig{1280, 720, "My Game"});
            /// @endcode
            template<typename T>
            void set(T resource) {
                auto typeIndex = std::type_index(typeid(T));

                resources[typeIndex] = std::move(resource);
            }

            /// @brief Получает указатель на ресурс указанного типа
            /// @tparam T Тип запрашиваемого ресурса
            /// @return Указатель на ресурс или nullptr если ресурс не найден
            /// @details Обеспечивает быстрый доступ к ресурсу через безопасное
            /// приведение типа с помощью std::any_cast. Возвращает неконстантный
            /// указатель для возможности модификации ресурса.
            /// 
            /// /// Примеры использования:
            /// @code
            /// // Получение ресурса для модификации
            /// if (auto* time = resources.get<TimeResource>()) {
            ///     time->update(deltaTime);
            ///     time->setScale(2.0f);
            /// }
            /// 
            /// // Цепочка вызовов
            /// resources.get<WindowConfig>()->setResolution(1920, 1080);
            /// @endcode
            template<typename T>
            T* get() {
                auto typeIndex = std::type_index(typeid(T));
                auto it = resources.find(typeIndex);
                return it != resources.end() ? std::any_cast<T>(&it->second) : nullptr;
            }

            /// @brief Получает константный указатель на ресурс указанного типа
            /// @tparam T Тип запрашиваемого ресурса
            /// @return Константный указатель на ресурс или nullptr если ресурс не найден
            /// @details Предназначен для безопасного доступа только для чтения.
            /// Используется в константных контекстах для гарантии неизменяемости ресурса.
            /// 
            /// /// Примеры использования:
            /// @code
            /// // В константном методе системы
            /// void render(const ResourceManager& resources) {
            ///     if (const auto* config = resources.get<Config>()) {
            ///         // config доступен только для чтения
            ///         drawUI(config->getWidth(), config->getHeight());
            ///     }
            /// }
            /// 
            /// // Для отладочного вывода
            /// void debugPrint(const ResourceManager& resources) {
            ///     if (const auto* time = resources.get<TimeResource>()) {
            ///         std::cout << "Game time: " << time->getTotalTime() << std::endl;
            ///     }
            /// }
            /// @endcode
            template<typename T>
            const T* get() const {
                auto typeIndex = std::type_index(typeid(T));
                auto it = resources.find(typeIndex);
                return it != resources.end() ? std::any_cast<T>(&it->second) : nullptr;
            }

            /// @brief Проверяет наличие ресурса указанного типа
            /// @tparam T Тип проверяемого ресурса
            /// @return true если ресурс существует, false в противном случае
            /// @details Быстрая проверка существования ресурса без его загрузки.
            /// Используется для условной логики и ленивой инициализации ресурсов.
            /// 
            /// Примеры использования:
            /// @code
            /// // Ленивая инициализация ресурса
            /// if (!resources.has<Audio>()) {
            ///     resources.set<Audio>(Audio{});
            ///     resources.get<Audio>()->initialize();
            /// }
            /// 
            /// // Условная логика системы
            /// if (resources.has<DebugInfo>()) {
            ///     drawDebugOverlay();
            /// }
            /// @endcode
            template<typename T>
            bool has() const {
                auto typeIndex = std::type_index(typeid(T));
                return resources.find(typeIndex) != resources.end();
            }

            /// @brief Удаляет ресурс указанного типа
            /// @tparam T Тип удаляемого ресурса
            /// @return true если ресурс был удален, false если ресурс не существовал
            /// @details Освобождает память, занимаемую ресурсом. std::any гарантирует
            /// корректный вызов деструктора хранимого объекта при удалении.
            /// 
            /// Примеры использования:
            /// @code
            /// // Удаление временного ресурса
            /// resources.remove<DebugOverlay>();
            /// 
            /// // Удаление при перезагрузке
            /// resources.remove<Config>();
            /// resources.set<Config>(loadConfigFromFile());
            /// 
            /// // Проверка успешности удаления
            /// if (resources.remove<ObsoleteResource>()) {
            ///     std::cout << "Obsolete resource removed" << std::endl;
            /// }
            /// @endcode
            template<typename T>
            bool remove() {
                auto typeIndex = std::type_index(typeid(T));
                return resources.erase(typeIndex) > 0;
            }

            /// @brief Очищает все ресурсы
            /// @details Удаляет все зарегистрированные ресурсы. Используется в деструкторе
            /// и может быть вызван явно для принудительной очистки всех ресурсов.
            /// 
            /// Пример использования:
            /// @code
            /// // При перезапуске игры
            /// resources.clear();
            /// initializeDefaultResources(resources);
            /// @endcode
            void clear() {
                resources.clear();
            }

            /// @brief Деструктор
            /// @details Автоматически очищает все ресурсы при уничтожении менеджера.
            /// Гарантирует корректное освобождение памяти и вызов деструкторов
            /// для всех хранимых объектов через механизмы std::any.
            ~ResourceManager() {
                clear();
            }

        private:
            
            /// @brief Хранилище ресурсов
            /// @details Использует комбинацию std::type_index и std::any для обеспечения
            /// типобезопасного хранения ресурсов.
            std::unordered_map<std::type_index, std::any> resources;
        };
    }
}