#pragma once
#include <cstdint>
#include <algorithm>
#include <SDL.h>

namespace prism {
    namespace scene {

        /// @brief Перечисление кодов клавиш клавиатуры
        /// @details Представляет все поддерживаемые клавиши, включая буквы, цифры, 
        /// функциональные клавиши, модификаторы и специальные клавиши
        enum class KeyCode : int {
            // Буквы
            A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

            // Цифры
            Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,

            // Цифровая клавиатура
            KP_0, KP_1, KP_2, KP_3, KP_4, KP_5, KP_6, KP_7, KP_8, KP_9, KP_Decimal, KP_Divide, KP_Multiply, KP_Subtract, KP_Add, KP_Enter, KP_Equal,

            // Функциональные клавиши
            F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,

            // Специальные клавиши
            Escape, Space, Enter, Tab, Backspace, Delete, Insert, CapsLock, ScrollLock, NumLock, PrintScreen, Pause,

            // Модификаторы
            LeftShift, RightShift, LeftControl, RightControl, LeftAlt, RightAlt, LeftSuper, RightSuper, Menu,

            // Навигация
            Up, Down, Left, Right, Home, End, PageUp, PageDown,

            // Символьные клавиши
            Comma, Period, Semicolon, Apostrophe, Slash, Backslash, LeftBracket, RightBracket, Minus, Equal, Grave, World1, World2,

            COUNT  // Общее количество поддерживаемых клавиш
        };

        /// @brief Преобразует SDL scancode в внутренний код клавиши
        /// @param scancode SDL scancode для преобразования
        /// @return Соответствующий KeyCode
        /// @note Если передан неизвестный scancode, поведение не определено
        inline KeyCode sdlScancodeToKeyCode(SDL_Scancode scancode)
        {
            switch (scancode) {
            case SDL_SCANCODE_A: return KeyCode::A;
            case SDL_SCANCODE_B: return KeyCode::B;
            case SDL_SCANCODE_C: return KeyCode::C;
            case SDL_SCANCODE_D: return KeyCode::D;
            case SDL_SCANCODE_E: return KeyCode::E;
            case SDL_SCANCODE_F: return KeyCode::F;
            case SDL_SCANCODE_G: return KeyCode::G;
            case SDL_SCANCODE_H: return KeyCode::H;
            case SDL_SCANCODE_I: return KeyCode::I;
            case SDL_SCANCODE_J: return KeyCode::J;
            case SDL_SCANCODE_K: return KeyCode::K;
            case SDL_SCANCODE_L: return KeyCode::L;
            case SDL_SCANCODE_M: return KeyCode::M;
            case SDL_SCANCODE_N: return KeyCode::N;
            case SDL_SCANCODE_O: return KeyCode::O;
            case SDL_SCANCODE_P: return KeyCode::P;
            case SDL_SCANCODE_Q: return KeyCode::Q;
            case SDL_SCANCODE_R: return KeyCode::R;
            case SDL_SCANCODE_S: return KeyCode::S;
            case SDL_SCANCODE_T: return KeyCode::T;
            case SDL_SCANCODE_U: return KeyCode::U;
            case SDL_SCANCODE_V: return KeyCode::V;
            case SDL_SCANCODE_W: return KeyCode::W;
            case SDL_SCANCODE_X: return KeyCode::X;
            case SDL_SCANCODE_Y: return KeyCode::Y;
            case SDL_SCANCODE_Z: return KeyCode::Z;

            case SDL_SCANCODE_0: return KeyCode::Num0;
            case SDL_SCANCODE_1: return KeyCode::Num1;
            case SDL_SCANCODE_2: return KeyCode::Num2;
            case SDL_SCANCODE_3: return KeyCode::Num3;
            case SDL_SCANCODE_4: return KeyCode::Num4;
            case SDL_SCANCODE_5: return KeyCode::Num5;
            case SDL_SCANCODE_6: return KeyCode::Num6;
            case SDL_SCANCODE_7: return KeyCode::Num7;
            case SDL_SCANCODE_8: return KeyCode::Num8;
            case SDL_SCANCODE_9: return KeyCode::Num9;

            case SDL_SCANCODE_KP_0: return KeyCode::KP_0;
            case SDL_SCANCODE_KP_1: return KeyCode::KP_1;
            case SDL_SCANCODE_KP_2: return KeyCode::KP_2;
            case SDL_SCANCODE_KP_3: return KeyCode::KP_3;
            case SDL_SCANCODE_KP_4: return KeyCode::KP_4;
            case SDL_SCANCODE_KP_5: return KeyCode::KP_5;
            case SDL_SCANCODE_KP_6: return KeyCode::KP_6;
            case SDL_SCANCODE_KP_7: return KeyCode::KP_7;
            case SDL_SCANCODE_KP_8: return KeyCode::KP_8;
            case SDL_SCANCODE_KP_9: return KeyCode::KP_9;
            case SDL_SCANCODE_KP_DECIMAL: return KeyCode::KP_Decimal;
            case SDL_SCANCODE_KP_DIVIDE: return KeyCode::KP_Divide;
            case SDL_SCANCODE_KP_MULTIPLY: return KeyCode::KP_Multiply;
            case SDL_SCANCODE_KP_MINUS: return KeyCode::KP_Subtract;
            case SDL_SCANCODE_KP_PLUS: return KeyCode::KP_Add;
            case SDL_SCANCODE_KP_ENTER: return KeyCode::KP_Enter;
            case SDL_SCANCODE_KP_EQUALS: return KeyCode::KP_Equal;

            case SDL_SCANCODE_F1: return KeyCode::F1;
            case SDL_SCANCODE_F2: return KeyCode::F2;
            case SDL_SCANCODE_F3: return KeyCode::F3;
            case SDL_SCANCODE_F4: return KeyCode::F4;
            case SDL_SCANCODE_F5: return KeyCode::F5;
            case SDL_SCANCODE_F6: return KeyCode::F6;
            case SDL_SCANCODE_F7: return KeyCode::F7;
            case SDL_SCANCODE_F8: return KeyCode::F8;
            case SDL_SCANCODE_F9: return KeyCode::F9;
            case SDL_SCANCODE_F10: return KeyCode::F10;
            case SDL_SCANCODE_F11: return KeyCode::F11;
            case SDL_SCANCODE_F12: return KeyCode::F12;
            case SDL_SCANCODE_F13: return KeyCode::F13;
            case SDL_SCANCODE_F14: return KeyCode::F14;
            case SDL_SCANCODE_F15: return KeyCode::F15;
            case SDL_SCANCODE_F16: return KeyCode::F16;
            case SDL_SCANCODE_F17: return KeyCode::F17;
            case SDL_SCANCODE_F18: return KeyCode::F18;
            case SDL_SCANCODE_F19: return KeyCode::F19;
            case SDL_SCANCODE_F20: return KeyCode::F20;
            case SDL_SCANCODE_F21: return KeyCode::F21;
            case SDL_SCANCODE_F22: return KeyCode::F22;
            case SDL_SCANCODE_F23: return KeyCode::F23;
            case SDL_SCANCODE_F24: return KeyCode::F24;

            case SDL_SCANCODE_ESCAPE: return KeyCode::Escape;
            case SDL_SCANCODE_SPACE: return KeyCode::Space;
            case SDL_SCANCODE_RETURN: return KeyCode::Enter;
            case SDL_SCANCODE_TAB: return KeyCode::Tab;
            case SDL_SCANCODE_BACKSPACE: return KeyCode::Backspace;
            case SDL_SCANCODE_DELETE: return KeyCode::Delete;
            case SDL_SCANCODE_INSERT: return KeyCode::Insert;
            case SDL_SCANCODE_CAPSLOCK: return KeyCode::CapsLock;
            case SDL_SCANCODE_SCROLLLOCK: return KeyCode::ScrollLock;
            case SDL_SCANCODE_NUMLOCKCLEAR: return KeyCode::NumLock;
            case SDL_SCANCODE_PRINTSCREEN: return KeyCode::PrintScreen;
            case SDL_SCANCODE_PAUSE: return KeyCode::Pause;

            case SDL_SCANCODE_LSHIFT: return KeyCode::LeftShift;
            case SDL_SCANCODE_RSHIFT: return KeyCode::RightShift;
            case SDL_SCANCODE_LCTRL: return KeyCode::LeftControl;
            case SDL_SCANCODE_RCTRL: return KeyCode::RightControl;
            case SDL_SCANCODE_LALT: return KeyCode::LeftAlt;
            case SDL_SCANCODE_RALT: return KeyCode::RightAlt;
            case SDL_SCANCODE_LGUI: return KeyCode::LeftSuper;
            case SDL_SCANCODE_RGUI: return KeyCode::RightSuper;
            case SDL_SCANCODE_APPLICATION: return KeyCode::Menu;

            case SDL_SCANCODE_UP: return KeyCode::Up;
            case SDL_SCANCODE_DOWN: return KeyCode::Down;
            case SDL_SCANCODE_LEFT: return KeyCode::Left;
            case SDL_SCANCODE_RIGHT: return KeyCode::Right;
            case SDL_SCANCODE_HOME: return KeyCode::Home;
            case SDL_SCANCODE_END: return KeyCode::End;
            case SDL_SCANCODE_PAGEUP: return KeyCode::PageUp;
            case SDL_SCANCODE_PAGEDOWN: return KeyCode::PageDown;

            case SDL_SCANCODE_COMMA: return KeyCode::Comma;
            case SDL_SCANCODE_PERIOD: return KeyCode::Period;
            case SDL_SCANCODE_SEMICOLON: return KeyCode::Semicolon;
            case SDL_SCANCODE_APOSTROPHE: return KeyCode::Apostrophe;
            case SDL_SCANCODE_SLASH: return KeyCode::Slash;
            case SDL_SCANCODE_BACKSLASH: return KeyCode::Backslash;
            case SDL_SCANCODE_LEFTBRACKET: return KeyCode::LeftBracket;
            case SDL_SCANCODE_RIGHTBRACKET: return KeyCode::RightBracket;
            case SDL_SCANCODE_MINUS: return KeyCode::Minus;
            case SDL_SCANCODE_EQUALS: return KeyCode::Equal;
            case SDL_SCANCODE_GRAVE: return KeyCode::Grave;
            case SDL_SCANCODE_INTERNATIONAL1: return KeyCode::World1;
            case SDL_SCANCODE_INTERNATIONAL2: return KeyCode::World2;
            }
        }

        /// @brief Преобразует внутренний код клавиши в SDL scancode
        /// @param keycode KeyCode для преобразования
        /// @return Соответствующий SDL_Scancode
        /// @note Если передан неизвестный KeyCode, поведение не определено
        inline SDL_Scancode keyCodeToSdlScancode(KeyCode keycode)
        {
            switch (keycode) {
            case KeyCode::A: return SDL_SCANCODE_A;
            case KeyCode::B: return SDL_SCANCODE_B;
            case KeyCode::C: return SDL_SCANCODE_C;
            case KeyCode::D: return SDL_SCANCODE_D;
            case KeyCode::E: return SDL_SCANCODE_E;
            case KeyCode::F: return SDL_SCANCODE_F;
            case KeyCode::G: return SDL_SCANCODE_G;
            case KeyCode::H: return SDL_SCANCODE_H;
            case KeyCode::I: return SDL_SCANCODE_I;
            case KeyCode::J: return SDL_SCANCODE_J;
            case KeyCode::K: return SDL_SCANCODE_K;
            case KeyCode::L: return SDL_SCANCODE_L;
            case KeyCode::M: return SDL_SCANCODE_M;
            case KeyCode::N: return SDL_SCANCODE_N;
            case KeyCode::O: return SDL_SCANCODE_O;
            case KeyCode::P: return SDL_SCANCODE_P;
            case KeyCode::Q: return SDL_SCANCODE_Q;
            case KeyCode::R: return SDL_SCANCODE_R;
            case KeyCode::S: return SDL_SCANCODE_S;
            case KeyCode::T: return SDL_SCANCODE_T;
            case KeyCode::U: return SDL_SCANCODE_U;
            case KeyCode::V: return SDL_SCANCODE_V;
            case KeyCode::W: return SDL_SCANCODE_W;
            case KeyCode::X: return SDL_SCANCODE_X;
            case KeyCode::Y: return SDL_SCANCODE_Y;
            case KeyCode::Z: return SDL_SCANCODE_Z;

            case KeyCode::Num0: return SDL_SCANCODE_0;
            case KeyCode::Num1: return SDL_SCANCODE_1;
            case KeyCode::Num2: return SDL_SCANCODE_2;
            case KeyCode::Num3: return SDL_SCANCODE_3;
            case KeyCode::Num4: return SDL_SCANCODE_4;
            case KeyCode::Num5: return SDL_SCANCODE_5;
            case KeyCode::Num6: return SDL_SCANCODE_6;
            case KeyCode::Num7: return SDL_SCANCODE_7;
            case KeyCode::Num8: return SDL_SCANCODE_8;
            case KeyCode::Num9: return SDL_SCANCODE_9;

            case KeyCode::KP_0: return SDL_SCANCODE_KP_0;
            case KeyCode::KP_1: return SDL_SCANCODE_KP_1;
            case KeyCode::KP_2: return SDL_SCANCODE_KP_2;
            case KeyCode::KP_3: return SDL_SCANCODE_KP_3;
            case KeyCode::KP_4: return SDL_SCANCODE_KP_4;
            case KeyCode::KP_5: return SDL_SCANCODE_KP_5;
            case KeyCode::KP_6: return SDL_SCANCODE_KP_6;
            case KeyCode::KP_7: return SDL_SCANCODE_KP_7;
            case KeyCode::KP_8: return SDL_SCANCODE_KP_8;
            case KeyCode::KP_9: return SDL_SCANCODE_KP_9;
            case KeyCode::KP_Decimal: return SDL_SCANCODE_KP_DECIMAL;
            case KeyCode::KP_Divide: return SDL_SCANCODE_KP_DIVIDE;
            case KeyCode::KP_Multiply: return SDL_SCANCODE_KP_MULTIPLY;
            case KeyCode::KP_Subtract: return SDL_SCANCODE_KP_MINUS;
            case KeyCode::KP_Add: return SDL_SCANCODE_KP_PLUS;
            case KeyCode::KP_Enter: return SDL_SCANCODE_KP_ENTER;
            case KeyCode::KP_Equal: return SDL_SCANCODE_KP_EQUALS;

            case KeyCode::F1: return SDL_SCANCODE_F1;
            case KeyCode::F2: return SDL_SCANCODE_F2;
            case KeyCode::F3: return SDL_SCANCODE_F3;
            case KeyCode::F4: return SDL_SCANCODE_F4;
            case KeyCode::F5: return SDL_SCANCODE_F5;
            case KeyCode::F6: return SDL_SCANCODE_F6;
            case KeyCode::F7: return SDL_SCANCODE_F7;
            case KeyCode::F8: return SDL_SCANCODE_F8;
            case KeyCode::F9: return SDL_SCANCODE_F9;
            case KeyCode::F10: return SDL_SCANCODE_F10;
            case KeyCode::F11: return SDL_SCANCODE_F11;
            case KeyCode::F12: return SDL_SCANCODE_F12;
            case KeyCode::F13: return SDL_SCANCODE_F13;
            case KeyCode::F14: return SDL_SCANCODE_F14;
            case KeyCode::F15: return SDL_SCANCODE_F15;
            case KeyCode::F16: return SDL_SCANCODE_F16;
            case KeyCode::F17: return SDL_SCANCODE_F17;
            case KeyCode::F18: return SDL_SCANCODE_F18;
            case KeyCode::F19: return SDL_SCANCODE_F19;
            case KeyCode::F20: return SDL_SCANCODE_F20;
            case KeyCode::F21: return SDL_SCANCODE_F21;
            case KeyCode::F22: return SDL_SCANCODE_F22;
            case KeyCode::F23: return SDL_SCANCODE_F23;
            case KeyCode::F24: return SDL_SCANCODE_F24;

            case KeyCode::Escape: return SDL_SCANCODE_ESCAPE;
            case KeyCode::Space: return SDL_SCANCODE_SPACE;
            case KeyCode::Enter: return SDL_SCANCODE_RETURN;
            case KeyCode::Tab: return SDL_SCANCODE_TAB;
            case KeyCode::Backspace: return SDL_SCANCODE_BACKSPACE;
            case KeyCode::Delete: return SDL_SCANCODE_DELETE;
            case KeyCode::Insert: return SDL_SCANCODE_INSERT;
            case KeyCode::CapsLock: return SDL_SCANCODE_CAPSLOCK;
            case KeyCode::ScrollLock: return SDL_SCANCODE_SCROLLLOCK;
            case KeyCode::NumLock: return SDL_SCANCODE_NUMLOCKCLEAR;
            case KeyCode::PrintScreen: return SDL_SCANCODE_PRINTSCREEN;
            case KeyCode::Pause: return SDL_SCANCODE_PAUSE;

            case KeyCode::LeftShift: return SDL_SCANCODE_LSHIFT;
            case KeyCode::RightShift: return SDL_SCANCODE_RSHIFT;
            case KeyCode::LeftControl: return SDL_SCANCODE_LCTRL;
            case KeyCode::RightControl: return SDL_SCANCODE_RCTRL;
            case KeyCode::LeftAlt: return SDL_SCANCODE_LALT;
            case KeyCode::RightAlt: return SDL_SCANCODE_RALT;
            case KeyCode::LeftSuper: return SDL_SCANCODE_LGUI;
            case KeyCode::RightSuper: return SDL_SCANCODE_RGUI;
            case KeyCode::Menu: return SDL_SCANCODE_APPLICATION;

            case KeyCode::Up: return SDL_SCANCODE_UP;
            case KeyCode::Down: return SDL_SCANCODE_DOWN;
            case KeyCode::Left: return SDL_SCANCODE_LEFT;
            case KeyCode::Right: return SDL_SCANCODE_RIGHT;
            case KeyCode::Home: return SDL_SCANCODE_HOME;
            case KeyCode::End: return SDL_SCANCODE_END;
            case KeyCode::PageUp: return SDL_SCANCODE_PAGEUP;
            case KeyCode::PageDown: return SDL_SCANCODE_PAGEDOWN;

            case KeyCode::Comma: return SDL_SCANCODE_COMMA;
            case KeyCode::Period: return SDL_SCANCODE_PERIOD;
            case KeyCode::Semicolon: return SDL_SCANCODE_SEMICOLON;
            case KeyCode::Apostrophe: return SDL_SCANCODE_APOSTROPHE;
            case KeyCode::Slash: return SDL_SCANCODE_SLASH;
            case KeyCode::Backslash: return SDL_SCANCODE_BACKSLASH;
            case KeyCode::LeftBracket: return SDL_SCANCODE_LEFTBRACKET;
            case KeyCode::RightBracket: return SDL_SCANCODE_RIGHTBRACKET;
            case KeyCode::Minus: return SDL_SCANCODE_MINUS;
            case KeyCode::Equal: return SDL_SCANCODE_EQUALS;
            case KeyCode::Grave: return SDL_SCANCODE_GRAVE;
            case KeyCode::World1: return SDL_SCANCODE_INTERNATIONAL1;
            case KeyCode::World2: return SDL_SCANCODE_INTERNATIONAL2;
            }
        }

        /// @brief Перечисление кодов кнопок мыши
        enum class MouseCode : int {
            Left,      /// Левая кнопка мыши
            Right,     /// Правая кнопка мыши
            Middle,    /// Средняя кнопка мыши (колесо)
            Button4,   /// Дополнительная кнопка 4
            Button5,   /// Дополнительная кнопка 5
            COUNT      /// Общее количество поддерживаемых кнопок
        };
        
        /// @brief Преобразует код кнопки SDL в внутренний код кнопки мыши
        /// @param button Код кнопки SDL
        /// @return Соответствующий MouseCode
        /// @note Для неизвестных кнопок возвращает MouseCode::Left
        inline MouseCode sdlButtonToMouseCode(Uint8 button) {
            switch (button) {
            case SDL_BUTTON_LEFT: return MouseCode::Left;
            case SDL_BUTTON_RIGHT: return MouseCode::Right;
            case SDL_BUTTON_MIDDLE: return MouseCode::Middle;
            case SDL_BUTTON_X1: return MouseCode::Button4;
            case SDL_BUTTON_X2: return MouseCode::Button5;
            default: return MouseCode::Left; // fallback
            }
        }

        /// @brief Состояния ввода (клавиш/кнопок)
        enum CodeState {
            PASSIVE,  /// Клавиша отпущена и не активна
            DOWN,     /// Момент нажатия клавиши (один кадр)
            UP,       /// Момент отпускания клавиши (один кадр)
            HELD,     /// Клавиша удерживается (после DOWN)
        };

        /// @brief Ресурс для управления состоянием ввода
        /// @details Хранит состояния всех клавиш, кнопок мыши и информацию о движении мыши
        struct InputResource {
            CodeState keys[static_cast<int>(KeyCode::COUNT)]; /// Состояния клавиш клавиатуры
            CodeState mouseKeys[static_cast<int>(MouseCode::COUNT)]; /// Состояния кнопок мыши

            double mouseX = 0.0;                    /// Текущая позиция мыши по X
            double mouseY = 0.0;                    /// Текущая позиция мыши по Y
            double mouseXPrevious = 0.0;            /// Позиция мыши по X в предыдущем кадре
            double mouseYPrevious = 0.0;            /// Позиция мыши по Y в предыдущем кадре
            double mouseScrollX = 0.0;              /// Скролл мыши по горизонтали
            double mouseScrollY = 0.0;              /// Скролл мыши по вертикали
        
            /// @brief Сбрасывает все состояния ввода в пассивное состояние
            void disableAllKey() {
                std::fill_n(keys, static_cast<int>(KeyCode::COUNT), CodeState::PASSIVE);
                std::fill_n(mouseKeys, static_cast<int>(MouseCode::COUNT), CodeState::PASSIVE);
            }

            /// @brief Получает состояние указанной клавиши
            /// @param keycode Код клавиши для проверки
            /// @return Текущее состояние клавиши
            CodeState getKeyState(KeyCode keycode) {
                return keys[static_cast<int>(keycode)];
            }

            /// @brief Получает состояние указанной кнопки мыши
            /// @param mousecode Код кнопки мыши для проверки
            /// @return Текущее состояние кнопки мыши
            CodeState getMouseState(MouseCode mousecode) {
                return mouseKeys[static_cast<int>(mousecode)];
            }

            /// @brief Обновляет состояния клавиш и кнопок мыши
            /// @details Преобразует состояния DOWN->HELD и UP->PASSIVE
            void updateKeyStates() {
                for (int i = 0; i < static_cast<int>(KeyCode::COUNT); i++) {
                    switch (keys[i]) {
                    case CodeState::DOWN:
                        keys[i] = CodeState::HELD;
                        break;
                    case CodeState::UP:
                        keys[i] = CodeState::PASSIVE;
                        break;
                    default:
                        break;
                    }
                }

                for (int i = 0; i < static_cast<int>(MouseCode::COUNT); i++) {
                    switch (mouseKeys[i]) {
                    case CodeState::DOWN:
                        mouseKeys[i] = CodeState::HELD;
                        break;
                    case CodeState::UP:
                        mouseKeys[i] = CodeState::PASSIVE;
                        break;
                    default:
                        break;
                    }
                }
            }

            /// @brief Исправляет "залипшие" клавиши
            /// @details Иногда события отпускания могут не приходить поэтому данный метод
            /// проверяет состояния HELD клавиш и сбрасывает их, если физическая клавиша больше не нажата
            void resetStuckKeys() {
                for (int i = 0; i < static_cast<int>(KeyCode::COUNT); i++) {
                    if (keys[i] == CodeState::HELD) {
                        const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
                        SDL_Scancode scancode = keyCodeToSdlScancode(static_cast<KeyCode>(i));

                        if (!currentKeyState[scancode]) {
                            keys[i] = CodeState::PASSIVE;
                        }
                    }
                }
            }

            /// @brief Отключает указанную клавишу (переводит в состояние UP)
            /// @param key Код клавиши для отключения
            void disableKey(KeyCode key) {
                int index = static_cast<int>(key);
                if (keys[index] == CodeState::DOWN || keys[index] == CodeState::HELD) {
                    keys[index] = CodeState::UP;
                }
            }

            /// @brief Включает указанную клавишу (переводит в состояние DOWN)
            /// @param key Код клавиши для включения
            void enableKey(KeyCode key) {
                int index = static_cast<int>(key);
                if (keys[index] == CodeState::PASSIVE || keys[index] == CodeState::UP) {
                    keys[index] = CodeState::DOWN;
                }
            }

            /// @brief Отключает указанную кнопку мыши (переводит в состояние UP)
            /// @param key Код кнопки мыши для отключения
            void disableMouseKey(MouseCode key) {
                int index = static_cast<int>(key);
                if (mouseKeys[index] == CodeState::DOWN || mouseKeys[index] == CodeState::HELD) {
                    mouseKeys[index] = CodeState::UP;
                }
            }

            /// @brief Включает указанную кнопку мыши (переводит в состояние DOWN)
            /// @param key Код кнопки мыши для включения
            void enableMouseKey(MouseCode key) {
                int index = static_cast<int>(key);
                if (mouseKeys[index] == CodeState::PASSIVE || mouseKeys[index] == CodeState::UP) {
                    mouseKeys[index] = CodeState::DOWN;
                }
            }

            /// @brief Вычисляет смещение мыши по X с предыдущего кадра
            /// @return Разница между текущей и предыдущей позицией мыши по X
            double getMouseDeltaX() const { return mouseX - mouseXPrevious; }

            /// @brief Вычисляет смещение мыши по Y с предыдущего кадра
            /// @return Разница между текущей и предыдущей позицией мыши по Y
            double getMouseDeltaY() const { return mouseY - mouseYPrevious; }
        }; 
    }
}