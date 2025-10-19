#include "timeSystem.h"
#include "timeResource.h"
#include <chrono>

void prism::scene::TimeSystem::start()
{
    lastTime = std::chrono::high_resolution_clock::now();
}

void prism::scene::TimeSystem::update()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    double_t deltaTime = std::chrono::duration<double_t>(currentTime - lastTime).count();
    lastTime = currentTime;

    TimeResource* time = scene->getResource<TimeResource>();
    if (!time) return;

    time->update(deltaTime);
}