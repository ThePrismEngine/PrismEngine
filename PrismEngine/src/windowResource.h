#pragma once
#include <memory>
#include <string>
#include <SDL.h>


namespace prism {
	namespace scene {
        class  WindowResource {
        public:

            // === Конструкторы ===
            WindowResource(const char* title, int width, int height);
            WindowResource(const char* title, int width, int height, Uint32 sdlFlags);
            WindowResource(const char* title, int x, int y, int width, int height);
            WindowResource(const char* title, int width, int height, const std::string& iconPath);
            WindowResource(const char* title, int width, int height, int minWidth, int minHeight, int maxWidth, int maxHeight);

            // Специальные конструкторы
            static WindowResource CreateCentered(const char* title, int width, int height);

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
            void getPosition(int* x, int* y) ;
            void centerWindow();
            void setMinSize(int minWidth, int minHeight);
            void setMaxSize(int maxWidth, int maxHeight);

            // === События и рендеринг ===
            bool isClose() const;
            void close();

            SDL_Window* getSDLWindow() const;


            std::shared_ptr<SDL_Window> sdlWindowPtr;

            bool windowResized = false;
            bool windowMinimized = false;
            // состояния
        private:

            // Внутренний конструктор для делегирования
            WindowResource(const char* title, int x, int y, int width, int height, Uint32 sdlFlags);
        };
	}
}