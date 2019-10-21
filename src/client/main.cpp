#include "SDLWrapper.h"
#include <iostream>
#include "ProtectedQueue.h"

int main() {
    try {
        SDLWrapper SDL;
        SDL.start();
        SDL.run();
        std::cout << "Se lanzo thread SDL...\n";
        SDL.join();
    } catch(std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

