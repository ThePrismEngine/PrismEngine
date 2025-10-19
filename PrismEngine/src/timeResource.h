#pragma once
#include <cmath>


namespace prism {
	namespace scene {
        /// @brief Стандартный ресурс для управления игровым временем
        /// @details Предоставляет как масштабируемое (игровое) время, так и реальное (немасштабируемое) время.
        /// Масштабируемое время используется для игровой логики, реальное - для системных операций.
        struct TimeResource
        {
            // === Масштабируемое время (игровое) ===
            double_t deltaTime = 0.0;      /// Изменение времени за кадр с учетом timeScale
            double_t time = 0.0;           /// Накопленное время с учетом timeScale

            // === Немасштабируемое время (реальное) ===
            double_t unscaledDeltaTime = 0.0;  /// Реальное изменение времени за кадр
            double_t unscaledTime = 0.0;       /// Реальное накопленное время

            double timeScale = 1.0;      /// Масштаб времени (1.0 = нормальная скорость)

            // === Методы управления ===

            /// @brief Обновляет временные значения
            /// @param rawDeltaTime Сырое время прошедшее с предыдущего кадра
            void update(double_t rawDeltaTime) {
                unscaledDeltaTime = rawDeltaTime;
                unscaledTime += rawDeltaTime;

                deltaTime = rawDeltaTime * timeScale;
                time += deltaTime;
            }

            /// @brief Устанавливает масштаб времени
            /// @param scale Новый масштаб (1.0 = нормальная скорость)
            void setScale(double scale) {
                timeScale = scale;
            }

            /// @brief Приостанавливает время (устанавливает масштаб в 0)
            void pause() {
                timeScale = 0.0;
            }

            /// @brief Возобновляет время (устанавливает масштаб в 1.0)
            void resume() {
                timeScale = 1.0;
            }

            /// @brief Переключает паузу
            void togglePause() {
                timeScale = (timeScale == 0.0) ? 1.0 : 0.0;
            }

            /// @brief Проверяет, остановлено ли время
            /// @return true если время приостановлено (timeScale == 0)
            bool isPaused() const {
                return timeScale == 0.0;
            }

            /// @brief Сбрасывает накопленное время
            /// @param keepScale Сохранять ли текущий масштаб времени
            void reset(bool keepScale = true) {
                time = 0.0;
                unscaledTime = 0.0;
                if (!keepScale) {
                    timeScale = 1.0;
                }
            }
        };
	}
}