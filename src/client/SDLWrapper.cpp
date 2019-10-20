#include "SDLWrapper.h"
#include "Window.h"
#include "BaseSprite.h"
#include "Camera.h"
#include "TileMap.h"
#include <SDL2/SDL.h>

SDLWrapper::SDLWrapper() {
    SDL_Init(SDL_INIT_VIDEO);
}

void SDLWrapper::run() {
    Window mainW("Testing", 1200, 600);
    BaseSprite car(mainW, "../media/sprites/pitstop_car_1.png", 100,100);
    TileMap lazy_map(mainW, "../media/maps/lazy.map");
    Camera cam(mainW, car);

    int velocityX = 0;
    int velocityY = 0;
    bool cont = true;
    SDL_Event e;
    while (cont){
        if (SDL_PollEvent(&e)) {
            mainW.clear();

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
                    case SDLK_q:
                        cont = false;
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
        car.move(velocityX, velocityY, 0);
        cam.update();
        lazy_map.render();
        car.render();
        mainW.update();
    }
}

SDLWrapper::~SDLWrapper() {
    SDL_Quit();
}