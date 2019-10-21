#include "BaseSprite.h"
#include "Window.h"

BaseSprite::BaseSprite(Window& main,
                       const std::string& path,
                       int height, int width) :
                       texture(main.createTextureFrom(path),main) {
    this->textureInfo.x = 0;
    this->textureInfo.y = 0;
    this->textureInfo.h = height;
    this->textureInfo.w = width;
    this->angle = 0;
}

void BaseSprite::move(int diff_x, int diff_y, int diff_ang) {
    this->textureInfo.x += diff_x;
    this->textureInfo.y += diff_y;
    this->angle += diff_ang;
}

int BaseSprite::getXPos() { return textureInfo.x + textureInfo.w / 2; }
int BaseSprite::getYPos() { return textureInfo.y + textureInfo.h / 2; }

void BaseSprite::render() {
    this->texture.render(this->textureInfo);
}

BaseSprite::~BaseSprite() { }
