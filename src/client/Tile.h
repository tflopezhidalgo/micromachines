#ifndef MICROMACHINES_TILE_H
#define MICROMACHINES_TILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include "Texture.h"
#include "Camera.h"

class Tile {
    private:
        SDL_Rect box;
        Texture texture;

    public:
        Tile(Window& window,
             const std::string& img,
             int x, int y, int h, int w);

        void render();

};

#endif
