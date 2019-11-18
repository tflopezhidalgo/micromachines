#include "Sprite.h"
#include "Window.h"
#include "Camera.h"

Sprite::Sprite(Window& main,
               const std::string& path,
               int height, int width) :
               texture(main.createTextureFrom(path)) {
    this->h = height;
    this->w = width;
}

void Sprite::render(int x, int y, int angle, Camera& cam) {
    SDL_Rect dimensions = {x, y, w, h};
    SDL_Rect translated = cam.translate(dimensions);

    if (cam.collideWith(translated))
        this->texture.render(translated, angle);
}

Sprite::~Sprite() { }
