#include "inputSystem.h"
#include "inputResource.h"
#include "windowResource.h"

void prism::scene::InputSystem::start()
{
	if (scene->hasResource<InputResource>()) {
		scene->getResource<InputResource>()->disableAllKey();
	}
}

void prism::scene::InputSystem::update()
{
    if (scene->hasResource<InputResource>()) {
        scene->getResource<InputResource>()->updateKeyStates();
        scene->getResource<InputResource>()->resetStuckKeys();
    }

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
        case SDL_WINDOWEVENT:
            processWindowEvent(event);
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            processKeyboardEvent(event);
            break;
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEWHEEL:
            processMouseEvent(event);
            break;
        default:
            break;
        }
    }
}

void prism::scene::InputSystem::processKeyboardEvent(SDL_Event event)
{
    if (scene->hasResource<InputResource>()) {
        SDL_Scancode scancode = event.key.keysym.scancode;
        KeyCode keyCode = sdlScancodeToKeyCode(scancode);

        if (keyCode == KeyCode::Unknown) {
            return;
        }

        switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.repeat == 0) {
                scene->getResource<InputResource>()->enableKey(keyCode);
            }
            break;
        case SDL_KEYUP:
            scene->getResource<InputResource>()->disableKey(keyCode);
            break;
        default:
            break;
        }
    }
}

void prism::scene::InputSystem::processMouseEvent(SDL_Event event)
{
    if (!scene->hasResource<InputResource>()) return;

    auto input = scene->getResource<InputResource>();

    switch (event.type) {
    case SDL_MOUSEMOTION:
        input->mouseX = static_cast<double>(event.motion.x);
        input->mouseY = static_cast<double>(event.motion.y);
        break;

    case SDL_MOUSEBUTTONDOWN:
        input->enableMouseKey(sdlButtonToMouseCode(event.button.button));
        break;

    case SDL_MOUSEBUTTONUP:
        input->disableMouseKey(sdlButtonToMouseCode(event.button.button));
        break;

    case SDL_MOUSEWHEEL:
        input->mouseScrollX = static_cast<double>(event.wheel.x);
        input->mouseScrollY = static_cast<double>(event.wheel.y);
        break;
    }
}

void prism::scene::InputSystem::processWindowEvent(SDL_Event event) {
    WindowResource* window = scene->getResource<WindowResource>();

    if (event.type == SDL_QUIT) {
        window->close();
    }

    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
        window->windowResized = true;
    }
    else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
        window->windowMinimized = true;
    }
    else if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
        window->windowMinimized = false;
    }
}