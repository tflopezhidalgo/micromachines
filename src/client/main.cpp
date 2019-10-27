#include "EventListener.h"
#include <iostream>
#include <zconf.h>
#include "ProtectedQueue.h"
#include "Car.h"
#include "Camera.h"
#include "TileMap.h"
#include "Drawer.h"
#include "ProtectedModel.h"
#include "Receiver.h"
#include "Proxy.h"
#include "Socket.h"
#include "Dispatcher.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    Window main("Game", 1200, 600);

    Socket skt(argv[1], argv[2]);
    Proxy proxy(std::move(skt));

    json j;
    j["mode"] = "create";
    j["map"] = "adawd";
    j["matchName"] = "tuSantaMadre";
    j["playersAmount"] = 1;
    j["clientId"] = "tomas";
    j["raceLaps"] = 10;

    ProtectedQueue<Action> q;
    ProtectedModel model(main);

    std::string msg = j.dump();
    proxy.sendMessage(msg);

    Receiver receiver(model, proxy);
    Drawer drawer(main, model);
    EventListener handler(q);
    Dispatcher dispatcher(q, proxy);

    receiver.start();
    drawer.start();
    dispatcher.start();
    handler.run();

    drawer.stop();
    receiver.stop();
    dispatcher.stop();
    drawer.join();
    receiver.join();
    dispatcher.join();

    SDL_Quit();
>>>>>>> SDL-basics
    return 0;
}
