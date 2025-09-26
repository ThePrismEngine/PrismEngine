#pragma once
#include <vector>
#include <memory>
#include "system.h"


namespace prism {
    namespace scene {
        /// @brief Менеджер систем для регистрации, включения/выключения и обновления систем.
        /// @details Управляет коллекцией систем, обновляя их в порядке регистрации.
        class SystemManager
        {
        public:
            SystemManager() = default;

            /// @brief Регистрирует новую систему в менеджере.
            /// @tparam T Тип системы (должен быть производным от ISystem).
            /// @tparam Args Типы аргументов для конструктора системы.
            /// @param args Аргументы для передачи конструктору системы.
            /// @return Идентификатор зарегистрированной системы.
            /// @details Создает экземпляр системы и добавляет его в список управления
            template<typename T, typename... Args>
            SystemId registerSystem(Args&&... args) {
                systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
                return systems.size() - 1;
            };

            /// @brief Включает систему по идентификатору.
            /// @param systemId Идентификатор системы, которую нужно включить.
            void enableSystem(SystemId systemId);

            /// @brief Выключает систему по идентификатору.
            /// @param systemId Идентификатор системы, которую нужно выключить.
            void disableSystem(SystemId systemId);

            
            /// @brief Обновляет все активные системы
            /// @param deltaTime Время, прошедшее с предыдущего обновления
            /// @details Вызывает update() для всех включенных систем в порядке регистрации
            void update(float deltaTime);

        private:
            /// @brief Массив зарегистрированных систем
            std::vector<std::unique_ptr<ISystem>> systems;
        };
    }
}