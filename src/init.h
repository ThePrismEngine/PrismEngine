#pragma once
#include <SDL.h>

namespace prism {
    inline bool isInit = false;
    inline void init() {
        SDL_Init(SDL_INIT_EVERYTHING);
        isInit = true;
    }
}