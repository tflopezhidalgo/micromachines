#ifndef MICROMACHINES_BASESPRITE_H
#define MICROMACHINES_BASESPRITE_H

#include "Window.h"
#include "Texture.h"
#include "Camera.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>

class Camera;

class BaseSprite {
    private:
        Texture& texture;
        int w;
        int h;

    public:
        BaseSprite(Window& main, const std::string& path, int height, int width);
        void render(int x, int y, int angle, Camera&);
        ~BaseSprite();
};
#endif
