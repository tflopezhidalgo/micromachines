#include "SDLWrapper.h"
#include <iostream>
#include <zconf.h>
#include "ProtectedQueue.h"
#include "Car.h"
#include "Camera.h"
#include "TileMap.h"
#include "Drawer.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    Window main("Game", 1200, 600);

    Car oneCar("../media/sprites/pitstop_car_1.png", 100, 100, main);
    Car otherCar("../media/sprites/pitstop_car_1.png", 100, 100, main);
    TileMap lazy_map(main, "../media/maps/lazy.map");
    Camera cam(main, oneCar);

    Drawer drawer(main);

    drawer.addEntity(lazy_map);
    drawer.addEntity(cam);
    drawer.addEntity(otherCar);
    drawer.addEntity(oneCar);

    drawer.run();

    /*try {
        SDLWrapper SDL;

        SDL.start();
        SDL.join();
    } catch(std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }*/

    usleep(200000000);

    drawer.stop();
    drawer.join();

    SDL_Quit();

   return 0;
}
