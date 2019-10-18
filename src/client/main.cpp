#include "SDLWrapper.h"
#include <iostream>

int main() {

    SDLWrapper SDL;
    SDL.start();
    std::cout << "Se lanzo thread SDL...\n";
    SDL.join();

    return 0;
}

