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
    BaseSprite car2(mainW, "../media/sprites/pitstop_car_1.png", 100,100);
    TileMap lazy_map(mainW, "../media/maps/lazy.map");
    Camera cam(mainW, car);

    bool cont = true;
    int velocityX = 0;
    int velocityY = 0;
    SDL_Event e;
    while (cont){
        while (SDL_PollEvent(&e)) {
            mainW.clear();
            car.handle(e, velocityX, velocityY);

            if (e.key.keysym.sym == SDLK_q) {
                cont = false;
            }
        }
        car.move(velocityX, velocityY, 0);
        lazy_map.render();
        cam.update();
        car2.render();
        car.render();
        mainW.update();
    }
}

SDLWrapper::~SDLWrapper() {
    SDL_Quit();
}