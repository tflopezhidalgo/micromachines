#ifndef MICROMACHINES_RENDERER_H
#define MICROMACHINES_RENDERER_H

#include <SDL2/SDL.h>
#include "Window.h"
#include "Texture.h"

class Renderer {
    private:
        SDL_Renderer* renderer;

    public:
        Renderer();
        ~Renderer();
};
#endif
