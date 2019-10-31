#include "BaseSprite.h"
#include "Window.h"
#include "Camera.h"

BaseSprite::BaseSprite(Window& main,
                       const std::string& path,
                       int height, int width) :
                       texture(main.createTextureFrom(path)) {
    this->h = height;
    this->w = width;
}

void BaseSprite::render(int x, int y, int angle, Camera& cam) {
    SDL_Rect rect = {x - cam.x , y - cam.y , w * cam.zoom, h * cam.zoom};
    if ((rect.x + rect.w) > 0 || (rect.y + rect.h) > 0)
        this->texture.render(rect, angle);
}

BaseSprite::~BaseSprite() { }
