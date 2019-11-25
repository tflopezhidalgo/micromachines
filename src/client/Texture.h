#ifndef MICROMACHINES_TEXTURE_H
#define MICROMACHINES_TEXTURE_H

#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture {
    private:
        SDL_Texture* texture;
        SDL_Rect textureInfo;
        Window& window;

    public:
        Texture(SDL_Texture* txd, Window& mainWindow);
        Texture(SDL_Texture* txd, Window& mainWindow, SDL_Rect& info);
        Texture(Texture&& other);
        Texture& operator=(Texture&& other);
        void render(SDL_Rect& src, int angle);
        void setRect(SDL_Rect& r);
        ~Texture();
};

#endif
