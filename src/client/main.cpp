#include "SDLWrapper.h"
#include <iostream>
#include <zconf.h>
#include "ProtectedQueue.h"
#include "Car.h"
#include "Camera.h"
#include "TileMap.h"
#include "Drawer.h"
#include "ProtectedModel.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    Window main("Game", 1200, 600);


    //TileMap lazy_map(main, "../media/maps/lazy.map");
    //Camera cam(main, oneCar);

    ProtectedModel model(main);
    model.updateEntity("ahre", 0, 0, 100);
    model.updateEntity("ahrwwwe2", 10, 10, 100);
    model.updateEntity("ahre", 10, 150, 100);
    Drawer drawer(main, model);

    drawer.start();

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
