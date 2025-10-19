#pragma once
#include "scene.h"
#include <cmath>
#include <chrono>

namespace prism {
	namespace scene {

        /// @brief Система управления временем и дельта-временем
        /// @details Отслеживает время между кадрами, вычисляет дельта-время
        /// и обновляет временные ресурсы сцены. Критически важна для 
        /// обеспечения плавной и независимой от частоты кадров симуляции.
        class TimeSystem : public ISystem {
        public:
            /// @brief Конструктор системы времени
            /// @param scene Указатель на родительскую сцену
            TimeSystem(Scene* scene) : scene(scene) {}

            /// @brief Инициализация системы времени
            /// @details Инициализирует начальное временное состояние системы
            void start() override;

            // @brief Обновление системы времени
            /// @details Вычисляет дельта-время между кадрами и обновляет TimeResource
            void update() override;

        private:
            prism::scene::Scene* scene; /// Указатель на родительскую сцену
            std::chrono::steady_clock::time_point lastTime; /// Временная точка предыдущего кадра

        };
    }
}