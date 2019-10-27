#ifndef MICROMACHINES_TEXTURE_H
#define MICROMACHINES_TEXTURE_H

#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture {
    private:
        SDL_Texture* texture;
        Window& window;

    public:
        Texture(SDL_Texture* txd,
                Window& mainWindow);
        Texture(Texture&& other);
        void render(SDL_Rect& dimensions, int angle);
        ~Texture();
};

#endif
