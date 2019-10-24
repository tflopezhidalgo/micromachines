#ifndef MICROMACHINES_WINDOW_H
#define MICROMACHINES_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class Texture;  //TODO: Solucionar esto

class Window {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Rect camera;

    public:
        explicit Window(std::string title);
        Window(std::string title, int w, int h);
        Texture& createTextureFrom(std::string img);
        void render(SDL_Texture *texture, SDL_Rect& rect);
        void setCamera(int x, int y, int scale);
        int getHeight();
        int getWidth();
        SDL_Renderer* getRenderer();
        void update();
        void clear();
        ~Window();
};
#endif
