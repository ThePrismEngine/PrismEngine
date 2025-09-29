#include "Window.h"


namespace prism {
    namespace render {

        Window::Window(const char* title, int width, int height)
            : Window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN) {
        }

        Window::Window(const char* title, int width, int height, Uint32 sdlFlags)
            : Window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, sdlFlags) {
        }

        Window::Window(const char* title, int x, int y, int width, int height)
            : Window(title, x, y, width, height, SDL_WINDOW_SHOWN) {
        }

        Window::Window(const char* title, int width, int height, const std::string& iconPath)
            : Window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN) {
            SDL_Surface* icon = SDL_LoadBMP(iconPath.c_str());
            if (icon) {
                SDL_SetWindowIcon(sdlWindow, icon);
                SDL_FreeSurface(icon);
            }
        }

        Window Window::CreateCentered(const char* title, int width, int height) {
            return Window(title, width, height);
        }

        Window::Window(const char* title, int width, int height,
            int minWidth, int minHeight, int maxWidth, int maxHeight)
            : Window(title, width, height) {
            SDL_SetWindowMinimumSize(sdlWindow, minWidth, minHeight);
            SDL_SetWindowMaximumSize(sdlWindow, maxWidth, maxHeight);
        }

        Window::Window(const char* title, int x, int y, int width, int height, Uint32 sdlFlags) : m_isDestroyed(false) {
            if (!prism::isInit) {
                prism::logger::logError(prism::logger::Error::PRISM_ENGINE_NOT_INITIALIZE, "it was called during the initialization of prism::view::Window");
            }

            sdlWindow = SDL_CreateWindow(title, x, y, width, height, sdlFlags | SDL_WINDOW_VULKAN);
            if (!sdlWindow) {
                prism::logger::logError(prism::logger::Error::WINDOW_INSTANCE_CREATE_ERROR, SDL_GetError());
            }
        }

        Window::~Window() {
            destroy();
        }

        const char* Window::getTitle() const {
            return SDL_GetWindowTitle(sdlWindow);
        }

        void Window::setTitle(const char* title) {
            SDL_SetWindowTitle(sdlWindow, title);
        }

        int Window::getWidth() {
            int width;
            SDL_GetWindowSize(sdlWindow, &width, nullptr);
            return width;
        }

        int Window::getHeight() {
            int height;
            SDL_GetWindowSize(sdlWindow, nullptr, &height);
            return height;
        }

        void Window::getSize(int* width, int* height) {
            SDL_GetWindowSize(sdlWindow, width, height);
        }

        void Window::setWidth(int width) {
            int height;
            SDL_GetWindowSize(sdlWindow, nullptr, &height);
            SDL_SetWindowSize(sdlWindow, width, height);
        }

        void Window::setHeight(int height) {
            int width;
            SDL_GetWindowSize(sdlWindow, &width, nullptr);
            SDL_SetWindowSize(sdlWindow, width, height);
        }

        void Window::setSize(int width, int height) {
            SDL_SetWindowSize(sdlWindow, width, height);
        }

        void Window::setFullscreen(bool enabled) {
            SDL_SetWindowFullscreen(sdlWindow, enabled ? SDL_WINDOW_FULLSCREEN : 0);
        }

        void Window::setBorderless(bool enabled) {
            SDL_SetWindowBordered(sdlWindow, enabled ? SDL_FALSE : SDL_TRUE);
        }

        void Window::setResizable(bool enabled) {
            SDL_SetWindowResizable(sdlWindow, enabled ? SDL_TRUE : SDL_FALSE);
        }

        void Window::setGrabMouse(bool enabled) {
            SDL_SetWindowGrab(sdlWindow, enabled ? SDL_TRUE : SDL_FALSE);
        }

        bool Window::isFullscreen() const {
            return (SDL_GetWindowFlags(sdlWindow) & SDL_WINDOW_FULLSCREEN) != 0;
        }

        bool Window::isBorderless() const {
            return (SDL_GetWindowFlags(sdlWindow) & SDL_WINDOW_BORDERLESS) != 0;
        }

        bool Window::isResizable() const {
            return (SDL_GetWindowFlags(sdlWindow) & SDL_WINDOW_RESIZABLE) != 0;
        }

        bool Window::isGrabMouse() const {
            return SDL_GetWindowGrab(sdlWindow) == SDL_TRUE;
        }

        void Window::setPosition(int x, int y) {
            SDL_SetWindowPosition(sdlWindow, x, y);
        }

        std::pair<int, int> Window::getPosition() const {
            int x, y;
            SDL_GetWindowPosition(sdlWindow, &x, &y);
            return { x, y };
        }

        void Window::centerWindow() {
            SDL_SetWindowPosition(sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        }

        void Window::setMinSize(int minWidth, int minHeight) {
            SDL_SetWindowMinimumSize(sdlWindow, minWidth, minHeight);
        }

        void Window::setMaxSize(int maxWidth, int maxHeight) {
            SDL_SetWindowMaximumSize(sdlWindow, maxWidth, maxHeight);
        }

        bool Window::shouldClose() const {
            return m_isDestroyed;
        }

        void Window::setCloseRequested(bool value) {
            m_isDestroyed = value;
        }

        void Window::handleEvents() {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    m_isDestroyed = true;
                }
                else if (event.type == SDL_WINDOWEVENT) {
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        windowResized = true;
                    }
                    else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                        windowMinimized = true;
                    }
                    else if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
                        windowMinimized = false;
                    }
                }
            }
        }

        void Window::clear() {
            // Реализация очистки окна будет зависеть от используемого API рендеринга
        }

        void Window::update() {
            // Реализация обновления окна будет зависеть от используемого API рендеринга
        }

        void Window::destroy() {
            if (sdlWindow) {
                SDL_DestroyWindow(sdlWindow);
                sdlWindow = nullptr;
                m_isDestroyed = true;
            }
        }
    } // namespace render
} // namespace prism