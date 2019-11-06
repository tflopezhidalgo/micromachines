#include "Window.h"
#include "Constants.h"
#include "TextureRepository.h"
#include <SDL2/SDL.h>
#include <string>

#define PI 3.14

Window::Window(std::string title) {
    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_SHOWN |  SDL_WINDOW_FULLSCREEN_DESKTOP);
    this->renderer = SDL_CreateRenderer(this->window, -1,
                                  SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!window || !renderer)
        throw std::runtime_error("No se pudo crear ventana");

    SDL_GetRendererOutputSize(this->renderer, &this->w, &this->h);
}

Window::Window(std::string title, int w, int h) {
    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    this->renderer =
            SDL_CreateRenderer(this->window,-1,
                        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!window)
        throw std::runtime_error("no se pudo crear ventana");
    SDL_GetRendererOutputSize(this->renderer, &this->w, &this->h);
}

Texture& Window::createTextureFrom(const std::string& img) {
    Texture& texture = TextureRepository::getTexture(img, *this);
    return texture;
}

void Window::render(SDL_Texture *texture,
                    SDL_Rect& textureInfo,
                    SDL_Rect& dstTexture,
                    int angle) {

    double precition_angle = (angle / PI ) * 180 / SERIALIZING_RESCAILING;

    SDL_Point point = {dstTexture.w / 2, dstTexture.h / 2};

    SDL_RenderCopyEx(this->renderer,
                     texture,
                     &textureInfo,
                     &dstTexture,
                     precition_angle,
                     &point,
                     SDL_FLIP_NONE);
}

int Window::getHeight(){ return h; }

int Window::getWidth(){ return w; }

SDL_Renderer* Window::getRenderer(){ return this->renderer; }

void Window::update() { SDL_RenderPresent(this->renderer); }

void Window::clear() { SDL_RenderClear(this->renderer); }

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}



