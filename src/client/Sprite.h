#ifndef MICROMACHINES_SPRITE_H
#define MICROMACHINES_SPRITE_H

#include "Window.h"
#include "Texture.h"
#include "Camera.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>

class Camera;

class Sprite {
protected:
    Texture& texture;
    int w;
    int h;

public:
    Sprite(Window& main, const std::string& path, int height, int width);
    virtual void render(int x, int y, int angle, Camera&) ;
    ~Sprite();

};
#endif
