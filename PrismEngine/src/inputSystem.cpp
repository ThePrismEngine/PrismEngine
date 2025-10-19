#include "inputSystem.h"
#include "inputResource.h"

void prism::scene::InputSystem::start()
{
	if (scene->hasResource<InputResource>()) {
		scene->getResource<InputResource>()->disableAllKey();
	}
}

void prism::scene::InputSystem::update()
{
    if (scene->hasResource<InputResource>()) {
        // Сначала обновляем состояния
        scene->getResource<InputResource>()->updateKeyStates();

        // Затем проверяем "залипшие" клавиши
        scene->getResource<InputResource>()->resetStuckKeys();
    }

    SDL_Event event;
    std::vector<SDL_Event> temp_buffer;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
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
            temp_buffer.push_back(event);
            break;
        }
    }

    for (const auto& e : temp_buffer) {
        SDL_PushEvent(const_cast<SDL_Event*>(&e));
    }
}

void prism::scene::InputSystem::processKeyboardEvent(SDL_Event event)
{
    if (scene->hasResource<InputResource>()) {
        SDL_Scancode scancode = event.key.keysym.scancode;

        switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.repeat == 0) {
                scene->getResource<InputResource>()->enableKey(sdlScancodeToKeyCode(scancode));
            }
            break;
        case SDL_KEYUP:
            scene->getResource<InputResource>()->disableKey(sdlScancodeToKeyCode(scancode));
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