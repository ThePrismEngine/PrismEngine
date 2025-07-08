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
                SDL_SetWindowIcon(m_sdlWindow, icon);
                SDL_FreeSurface(icon);
            }
        }

        Window Window::CreateCentered(const char* title, int width, int height) {
            return Window(title, width, height);
        }

        Window::Window(const char* title, int width, int height,
            int minWidth, int minHeight, int maxWidth, int maxHeight)
            : Window(title, width, height) {
            SDL_SetWindowMinimumSize(m_sdlWindow, minWidth, minHeight);
            SDL_SetWindowMaximumSize(m_sdlWindow, maxWidth, maxHeight);
        }

        Window::Window(const char* title, int x, int y, int width, int height, Uint32 sdlFlags) : m_isDestroyed(false) {
            if (!prism::isInit) {
                prism::logger::logError(prism::logger::Error::PRISM_ENGINE_NOT_INITIALIZE, "it was called during the initialization of prism::view::Window");
            }

            m_sdlWindow = SDL_CreateWindow(title, x, y, width, height, sdlFlags | SDL_WINDOW_VULKAN);
            if (!m_sdlWindow) {
                prism::logger::logError(prism::logger::Error::WINDOW_INSTANCE_CREATE_ERROR, SDL_GetError());
            }

            windowVkManager.init(m_sdlWindow);
        }

        Window::~Window() {
            destroy();
        }

        const char* Window::getTitle() const {
            return SDL_GetWindowTitle(m_sdlWindow);
        }

        void Window::setTitle(const char* title) {
            SDL_SetWindowTitle(m_sdlWindow, title);
        }

        int Window::getWidth() {
            int width;
            SDL_GetWindowSize(m_sdlWindow, &width, nullptr);
            return width;
        }

        int Window::getHeight() {
            int height;
            SDL_GetWindowSize(m_sdlWindow, nullptr, &height);
            return height;
        }

        void Window::getSize(int* width, int* height) {
            SDL_GetWindowSize(m_sdlWindow, width, height);
        }

        void Window::setWidth(int width) {
            int height;
            SDL_GetWindowSize(m_sdlWindow, nullptr, &height);
            SDL_SetWindowSize(m_sdlWindow, width, height);
        }

        void Window::setHeight(int height) {
            int width;
            SDL_GetWindowSize(m_sdlWindow, &width, nullptr);
            SDL_SetWindowSize(m_sdlWindow, width, height);
        }

        void Window::setSize(int width, int height) {
            SDL_SetWindowSize(m_sdlWindow, width, height);
        }

        void Window::setFullscreen(bool enabled) {
            SDL_SetWindowFullscreen(m_sdlWindow, enabled ? SDL_WINDOW_FULLSCREEN : 0);
        }

        void Window::setBorderless(bool enabled) {
            SDL_SetWindowBordered(m_sdlWindow, enabled ? SDL_FALSE : SDL_TRUE);
        }

        void Window::setResizable(bool enabled) {
            SDL_SetWindowResizable(m_sdlWindow, enabled ? SDL_TRUE : SDL_FALSE);
        }

        void Window::setGrabMouse(bool enabled) {
            SDL_SetWindowGrab(m_sdlWindow, enabled ? SDL_TRUE : SDL_FALSE);
        }

        bool Window::isFullscreen() const {
            return (SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_FULLSCREEN) != 0;
        }

        bool Window::isBorderless() const {
            return (SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_BORDERLESS) != 0;
        }

        bool Window::isResizable() const {
            return (SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_RESIZABLE) != 0;
        }

        bool Window::isGrabMouse() const {
            return SDL_GetWindowGrab(m_sdlWindow) == SDL_TRUE;
        }

        void Window::setPosition(int x, int y) {
            SDL_SetWindowPosition(m_sdlWindow, x, y);
        }

        std::pair<int, int> Window::getPosition() const {
            int x, y;
            SDL_GetWindowPosition(m_sdlWindow, &x, &y);
            return { x, y };
        }

        void Window::centerWindow() {
            SDL_SetWindowPosition(m_sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        }

        void Window::setMinSize(int minWidth, int minHeight) {
            SDL_SetWindowMinimumSize(m_sdlWindow, minWidth, minHeight);
        }

        void Window::setMaxSize(int maxWidth, int maxHeight) {
            SDL_SetWindowMaximumSize(m_sdlWindow, maxWidth, maxHeight);
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
                        windowVkManager.framebufferResized = true;
                    }
                    else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                        windowVkManager.windowMinimized = true;
                    }
                    else if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
                        windowVkManager.windowMinimized = false;
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

        void Window::drawFrame()
        {
            windowVkManager.drawFrame();
        }

        void Window::awaitRenderingCompletion()
        {
            windowVkManager.awaitRenderingCompletion();
        }

        void Window::destroy() {
            if (m_sdlWindow) {
                windowVkManager.cleanup();
                SDL_DestroyWindow(m_sdlWindow);
                m_sdlWindow = nullptr;
                m_isDestroyed = true;
            }
        }
    } // namespace render
} // namespace prism