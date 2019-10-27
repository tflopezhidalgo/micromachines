#include "Window.h"
#include "TextureRepository.h"
#include <SDL2/SDL.h>
#include <string>

Window::Window(std::string title) {
    this->camera = {0,0 ,0,0};
    this->window = SDL_CreateWindow(title.c_str(), 0, 0, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    this->renderer = SDL_CreateRenderer(this->window, -1,
                                  SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!window || !renderer)
        throw std::runtime_error("No se pudo crear ventana");
}

Window::Window(std::string title, int w, int h) {
    this->camera = {0,0 ,0,0};
    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    this->renderer =
            SDL_CreateRenderer(this->window,-1,
                        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!window)
        throw std::runtime_error("no se pudo crear ventana");
}

Texture& Window::createTextureFrom(std::string img) {
    Texture& texture = TextureRepository::getTexture(img, *this);
    return texture;
}

void Window::render(SDL_Texture *texture, SDL_Rect &rect, int angle) {
    SDL_Rect drawingRect = {0,0,0,0};
    drawingRect.x = rect.x - camera.x;
    drawingRect.y = rect.y - camera.y;
    drawingRect.h = rect.h - camera.w;
    drawingRect.w = rect.w - camera.w;

    double pi = 3.14;
    angle = (angle/pi) * 1.8;

    SDL_Point point = {100,100};
    SDL_RenderCopyEx(this->renderer,
                     texture,
                     NULL,
                     &drawingRect,
                     angle,
                     &point,
                     SDL_FLIP_NONE
    );
}

void Window::setCamera(int x, int y, int scale){
    this->camera.x = x;
    this->camera.y = y;
    this->camera.w = scale;
}

int Window::getHeight(){
    int h;
    SDL_GetRendererOutputSize(this->renderer, 0, &h);
    return h;
}

int Window::getWidth(){
    int w;
    SDL_GetRendererOutputSize(this->renderer, &w, 0);
    return w;
}

SDL_Renderer* Window::getRenderer(){
    return this->renderer;
}

void Window::update() {
    SDL_RenderPresent(this->renderer);
}

void Window::clear() {
    SDL_RenderClear(this->renderer);
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}



