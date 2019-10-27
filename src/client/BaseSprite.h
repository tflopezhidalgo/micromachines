#ifndef MICROMACHINES_BASESPRITE_H
#define MICROMACHINES_BASESPRITE_H

#include "Window.h"
#include "Texture.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>

class BaseSprite {
    private:
        Texture& texture;
        SDL_Rect textureInfo;
        int angle;

    public:
        BaseSprite(Window& main,
                   const std::string& path,
                   int height, int width);
        void move(int new_x, int new_y, int new_angle);
        int getXPos();
        int getYPos();
        void render();
        void setPos(int x, int y){
            this->textureInfo.x = x;
            this->textureInfo.y = y;
        }
        ~BaseSprite();
};
#endif
