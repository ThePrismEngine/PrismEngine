#include "windowResource.h"
#include "string"
#include <vector>
#include "init.h"
#include "logger.h"

namespace prism {
    namespace scene {
        WindowResource::WindowResource(const char* title, int width, int height)
            : WindowResource(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN) {
        }

        WindowResource::WindowResource(const char* title, int width, int height, Uint32 sdlFlags)
            : WindowResource(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, sdlFlags) {
        }

        WindowResource::WindowResource(const char* title, int x, int y, int width, int height)
            : WindowResource(title, x, y, width, height, SDL_WINDOW_SHOWN) {
        }

        WindowResource::WindowResource(const char* title, int width, int height, const std::string& iconPath)
            : WindowResource(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN) {
            SDL_Surface* icon = SDL_LoadBMP(iconPath.c_str());
            if (icon) {
                SDL_SetWindowIcon(sdlWindowPtr.get(), icon);
                SDL_FreeSurface(icon);
            }
        }

        WindowResource::WindowResource(const char* title, int width, int height,
            int minWidth, int minHeight, int maxWidth, int maxHeight)
            : WindowResource(title, width, height) {
            SDL_SetWindowMinimumSize(sdlWindowPtr.get(), minWidth, minHeight);
            SDL_SetWindowMaximumSize(sdlWindowPtr.get(), maxWidth, maxHeight);
        }

        WindowResource WindowResource::CreateCentered(const char* title, int width, int height) {
            return WindowResource(title, width, height);
        }

        WindowResource::WindowResource(const char* title, int x, int y, int width, int height, Uint32 sdlFlags) {
            if (!prism::isInit) {
                prism::logger::logError(prism::logger::Error::PRISM_ENGINE_NOT_INITIALIZE, "it was called during the initialization of window");
            }

            SDL_Window* sdlWindow = SDL_CreateWindow(title, x, y, width, height, sdlFlags | SDL_WINDOW_VULKAN);
            if (!sdlWindow) {
                prism::logger::logError(prism::logger::Error::WINDOW_INSTANCE_CREATE_ERROR, SDL_GetError());
            }

            sdlWindowPtr = std::shared_ptr<SDL_Window>(sdlWindow, [](SDL_Window* w) {
                if (w) SDL_DestroyWindow(w);
            });
        }

        const char* WindowResource::getTitle() const {
            return SDL_GetWindowTitle(sdlWindowPtr.get());
        }

        void WindowResource::setTitle(const char* title) {
            SDL_SetWindowTitle(sdlWindowPtr.get(), title);
        }

        int WindowResource::getWidth() {
            int width;
            SDL_GetWindowSize(sdlWindowPtr.get(), &width, nullptr);
            return width;
        }

        int WindowResource::getHeight() {
            int height;
            SDL_GetWindowSize(sdlWindowPtr.get(), nullptr, &height);
            return height;
        }

        void WindowResource::getSize(int* width, int* height) {
            SDL_GetWindowSize(sdlWindowPtr.get(), width, height);
        }

        void WindowResource::setWidth(int width) {
            int height;
            SDL_GetWindowSize(sdlWindowPtr.get(), nullptr, &height);
            SDL_SetWindowSize(sdlWindowPtr.get(), width, height);
        }

        void WindowResource::setHeight(int height) {
            int width;
            SDL_GetWindowSize(sdlWindowPtr.get(), &width, nullptr);
            SDL_SetWindowSize(sdlWindowPtr.get(), width, height);
        }

        void WindowResource::setSize(int width, int height) {
            SDL_SetWindowSize(sdlWindowPtr.get(), width, height);
        }

        void WindowResource::setFullscreen(bool enabled) {
            SDL_SetWindowFullscreen(sdlWindowPtr.get(), enabled ? SDL_WINDOW_FULLSCREEN : 0);
        }

        void WindowResource::setBorderless(bool enabled) {
            SDL_SetWindowBordered(sdlWindowPtr.get(), enabled ? SDL_FALSE : SDL_TRUE);
        }

        void WindowResource::setResizable(bool enabled) {
            SDL_SetWindowResizable(sdlWindowPtr.get(), enabled ? SDL_TRUE : SDL_FALSE);
        }

        void WindowResource::setGrabMouse(bool enabled) {
            SDL_SetWindowGrab(sdlWindowPtr.get(), enabled ? SDL_TRUE : SDL_FALSE);
        }

        bool WindowResource::isFullscreen() const {
            return (SDL_GetWindowFlags(sdlWindowPtr.get()) & SDL_WINDOW_FULLSCREEN) != 0;
        }

        bool WindowResource::isBorderless() const {
            return (SDL_GetWindowFlags(sdlWindowPtr.get()) & SDL_WINDOW_BORDERLESS) != 0;
        }

        bool WindowResource::isResizable() const {
            return (SDL_GetWindowFlags(sdlWindowPtr.get()) & SDL_WINDOW_RESIZABLE) != 0;
        }

        bool WindowResource::isGrabMouse() const {
            return SDL_GetWindowGrab(sdlWindowPtr.get()) == SDL_TRUE;
        }

        void WindowResource::setPosition(int x, int y) {
            SDL_SetWindowPosition(sdlWindowPtr.get(), x, y);
        }

        void WindowResource::getPosition(int* x, int* y) {
            SDL_GetWindowPosition(sdlWindowPtr.get(), x, y);
        }

        void WindowResource::centerWindow() {
            SDL_SetWindowPosition(sdlWindowPtr.get(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        }

        void WindowResource::setMinSize(int minWidth, int minHeight) {
            SDL_SetWindowMinimumSize(sdlWindowPtr.get(), minWidth, minHeight);
        }

        void WindowResource::setMaxSize(int maxWidth, int maxHeight) {
            SDL_SetWindowMaximumSize(sdlWindowPtr.get(), maxWidth, maxHeight);
        }

        bool WindowResource::isClose() const {
            return !sdlWindowPtr;
        }

        void WindowResource::close() {
            sdlWindowPtr.reset();
        }

        SDL_Window* WindowResource::getSDLWindow() const {
            return sdlWindowPtr.get();
        }
    }
}