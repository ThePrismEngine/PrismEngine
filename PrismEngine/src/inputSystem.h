#pragma once
#include "scene.h"
#include "renderer.h"
#include "inputResource.h"


namespace prism {
    namespace scene {
        /// @brief Система обработки ввода пользователя
        /// @details Обрабатывает события клавиатуры, мыши и обновляет состояние ввода.
        /// Наследуется от ISystem и интегрируется в главный цикл обновления сцены.
        class InputSystem : public ISystem {
        public:
            /// @brief Конструктор системы ввода
            /// @param scene Указатель на родительскую сцену
            InputSystem(Scene* scene) : scene(scene) {}

            /// @brief Инициализация системы ввода
            /// @details Вызывается при старте системы, сбрасывает все состояния ввода
            void start() override;

            /// @brief Основное обновление системы ввода
            /// @details Обрабатывает все события SDL, обновляет состояния клавиш и мыши.
            /// Вызывается каждый кадр в главном цикле обновления.
            void update() override;

        private:
            /// @brief Обрабатывает события клавиатуры
            /// @param event SDL событие для обработки
            /// @details Обрабатывает SDL_KEYDOWN и SDL_KEYUP события, обновляя
            /// состояния соответствующих клавиш в InputResource
            void processKeyboardEvent(SDL_Event event);

            /// @brief Обрабатывает события мыши
            /// @param event SDL событие для обработки
            /// @details Обрабатывает движение мыши, нажатия кнопок и прокрутку,
            /// обновляя состояние мыши в InputResource
            void processMouseEvent(SDL_Event event);

            prism::scene::Scene* scene; /// Указатель на родительскую сцену
        };
    }
}