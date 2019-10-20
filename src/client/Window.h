#ifndef MICROMACHINES_WINDOW_H
#define MICROMACHINES_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class Window {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Rect camera;

    public:
        explicit Window(std::string title);
        Window(std::string title, int w, int h);
        SDL_Texture* createTextureFrom(std::string img);
        void render(SDL_Texture *texture, SDL_Rect &rect, SDL_Point &point, double angle);
        void render(SDL_Texture *texture, SDL_Rect& rect);
        void setCamera(int x, int y, int scale){
            this->camera.x = x;
            this->camera.y = y;
            this->camera.w = scale;
        }

        void testMethod(){
            std::cout << "Se llamo testMethod" << std::endl;
        }

        int getHeight(){
            int h;
            SDL_GetRendererOutputSize(this->renderer, 0, &h);
            return h;
        }

        int getWidth(){
            int w;
            SDL_GetRendererOutputSize(this->renderer, &w, 0);
            return w;
        }

        void update();
        void clear();
        ~Window();
};
#endif
