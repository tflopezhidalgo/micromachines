#include "Texture.h"
#include <SDL2/SDL.h>
#include <iostream>

Texture::Texture(SDL_Texture* txd, Window& mainWindow) :
    window(mainWindow) {
        this->texture = txd;
}

Texture::Texture(Texture&& other) :
    window(other.window) {
        this->texture = other.texture;
        other.texture = NULL;
}

void Texture::render(SDL_Rect& dimensions, int angle) {
    this->window.render(this->texture, dimensions, angle);
}

Texture::~Texture() {
    SDL_DestroyTexture(this->texture);

}
