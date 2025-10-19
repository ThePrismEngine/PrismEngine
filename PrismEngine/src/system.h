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

            /// @brief Первоначальная настройка системы, не обязательно реализовывать
            /// @details Вызывается один раз на первом кадре для первоначальнго создания динамических обьектов, запонения значений и т.д
            virtual void start() {};

            /// @brief Обновление состояния системы
            /// @details Вызывается каждый кадр для обновления логики системы
            virtual void update() = 0;

            /// @brief Флаг активности системы.
            /// @details Если true - система обновляется, если false - пропускается
            bool enabled = true;

            /// @brief Флаг был ли вызван старт системы.
            /// @details Если true - система уже прошла первое обновление, если false - сначало будет вызван start() перед update()
            bool started = false;
        };
    }
}
