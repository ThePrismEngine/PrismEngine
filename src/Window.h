#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include <vulkan/vulkan.h>
#include <optional>
#include <stdexcept>
#include <utility> // для std::pair
#include <SDL_vulkan.h>
#include <memory> 
#include <set>
#include <map>
#include <iostream>
#include "logger.h"
#include "init.h"

namespace prism {
    namespace render {
        class Window {
        public:
            Window(Window&&) = delete;
            Window& operator=(Window&&) = delete;
            Window(const Window&) = delete;
            Window& operator=(const Window&) = delete;

            // === Конструкторы ===
            Window(const char* title, int width, int height);
            Window(const char* title, int width, int height, Uint32 sdlFlags);
            Window(const char* title, int x, int y, int width, int height);
            Window(const char* title, int width, int height, const std::string& iconPath);

            // Специальные конструкторы
            static Window CreateCentered(const char* title, int width, int height);
            Window(const char* title, int width, int height,
                int minWidth, int minHeight, int maxWidth, int maxHeight);

            // === Деструктор ===
            ~Window();

            // === Управление окном ===
            const char* getTitle() const;
            void setTitle(const char* title);
            int getWidth();
            int getHeight();
            void getSize(int* width, int* height);
            void setWidth(int width);
            void setHeight(int height);
            void setSize(int width, int height);

            // === Режимы окна ===
            void setFullscreen(bool enabled);
            void setBorderless(bool enabled);
            void setResizable(bool enabled);
            void setGrabMouse(bool enabled);
            bool isFullscreen() const;
            bool isBorderless() const;
            bool isResizable() const;
            bool isGrabMouse() const;

            // === Позиция и размер ===
            void setPosition(int x, int y);
            std::pair<int, int> getPosition() const;
            void centerWindow();
            void setMinSize(int minWidth, int minHeight);
            void setMaxSize(int maxWidth, int maxHeight);

            // === События и рендеринг ===
            bool shouldClose() const;
            void setCloseRequested(bool value);
            void handleEvents();
            void clear();
            void update();



            // === Дополнительные методы ===
            void destroy();

            static void setSDLInitialized(bool initialized) { s_sdlInitialized = initialized; }

            SDL_Window* sdlWindow;

            // состояния
            bool windowResized = false;
            bool windowMinimized = false;

        private:
            static bool s_sdlInitialized;
            bool m_isDestroyed;
            
            // Внутренний конструктор для делегирования
            Window(const char* title, int x, int y, int width, int height, Uint32 sdlFlags);
        };
    } // namespace render
} // namespace prism