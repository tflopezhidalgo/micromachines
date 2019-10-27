#include "BaseSprite.h"
#include "Window.h"

BaseSprite::BaseSprite(Window& main,
                       const std::string& path,
                       int height, int width) :
                       texture(main.createTextureFrom(path)) {
    this->textureInfo.x = 0;
    this->textureInfo.y = 0;
    this->textureInfo.h = height;
    this->textureInfo.w = width;
    this->angle = 0;
}

void BaseSprite::move(int new_x, int new_y, int new_angle) {
    this->textureInfo.x = new_x;
    this->textureInfo.y = new_y;
    this->angle = new_angle;
}

int BaseSprite::getXPos() { return textureInfo.x + textureInfo.w / 2; }
int BaseSprite::getYPos() { return textureInfo.y + textureInfo.h / 2; }

void BaseSprite::render() {
    this->texture.render(this->textureInfo, this->angle);
}

BaseSprite::~BaseSprite() { }
