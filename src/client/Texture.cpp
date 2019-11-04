#include "Texture.h"
#include <SDL2/SDL.h>
#include <iostream>

Texture::Texture(SDL_Texture* txd, Window& mainWindow) :
    window(mainWindow) {
        this->texture = txd;
        this->textureInfo.x = 0;
        this->textureInfo.y = 0;
        SDL_QueryTexture(txd, NULL, NULL, &textureInfo.w, &textureInfo.h);
}

Texture::Texture(SDL_Texture* txd, Window& mainWindow, SDL_Rect& info) :
    window(mainWindow) {
        this->texture = txd;
        this->textureInfo = info;
}

Texture::Texture(Texture&& other) :
    window(other.window) {
        this->texture = other.texture;
        other.texture = NULL;
        this->textureInfo = other.textureInfo;
}

void Texture::render(SDL_Rect& src, int angle) {
    this->window.render(this->texture,
                        this->textureInfo,
                        src,
                        angle);
}

Texture::~Texture() {
    SDL_DestroyTexture(this->texture);
}
