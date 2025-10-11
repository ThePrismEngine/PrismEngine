#pragma once
#include <cstdint>

namespace prism {
    namespace scene {
        /// @brief Идентификатор системы
        /// @details Уникальный числовой идентификатор для обращения к системе
        typedef uint32_t SystemId;

        /// @brief Неверный идентификатор системы
        /// @details Используется для обозначения отсутствующей или невалидной системы
        const SystemId INVALID_SYSTEM_ID = 0;

        /// @brief Базовый интерфейс для всех систем
        /// @details Системы должны наследоваться от этого интерфейса и реализовывать метод update
        class ISystem {
        public:
            virtual ~ISystem() = default;

            /// @brief Обновление состояния системы
            /// @param deltaTime Время, прошедшее с предыдущего обновления (в секундах)
            /// @details Вызывается каждый кадр для обновления логики системы
            virtual void update(float deltaTime) = 0;

            /// @brief Флаг активности системы.
            /// @details Если true - система обновляется, если false - пропускается
            bool enabled = true;
        };
    }
}
