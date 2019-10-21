#ifndef MICROMACHINES_BASESPRITE_H
#define MICROMACHINES_BASESPRITE_H

#include "Window.h"
#include "Texture.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>

class BaseSprite {
    private:
        Texture texture;
        SDL_Rect textureInfo;
        int angle;

    public:
        BaseSprite(Window& main,
                   const std::string& path,
                   int height, int width);
        void move(int diff_x, int diff_y, int diff_ang);
        int getXPos();
        int getYPos();
        void render();
        ~BaseSprite();
};
#endif
