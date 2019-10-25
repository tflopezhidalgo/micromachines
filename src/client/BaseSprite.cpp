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

void BaseSprite::handle(SDL_Event& e, int& velocityX,
            int& velocityY){
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                velocityY -= 10;
                break;
            case SDLK_s:
                velocityY += 10;
                break;
            case SDLK_a:
                velocityX -= 10;
                break;
            case SDLK_d:
                velocityX += 10;
                break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                velocityY += 10;
                break;
            case SDLK_s:
                velocityY -= 10;
                break;
            case SDLK_a:
                velocityX += 10;
                break;
            case SDLK_d:
                velocityX -= 10;
                break;
        }
    }
}

int BaseSprite::getXPos() { return textureInfo.x + textureInfo.w / 2; }
int BaseSprite::getYPos() { return textureInfo.y + textureInfo.h / 2; }

void BaseSprite::render() {
    this->texture.render(this->textureInfo);
}

BaseSprite::~BaseSprite() { }
