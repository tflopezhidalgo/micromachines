#ifndef MICROMACHINES_WINDOW_H
#define MICROMACHINES_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Window {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        Window();
        explicit Window(std::string title);
        Window(std::string title, int w, int h);
        void clear();
        void addTexture();
        ~Window();
};
#endif
