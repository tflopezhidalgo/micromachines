#include "../common/Event.h"
#include "EventListener.h"
#include <iostream>
#include <zconf.h>
#include "ProtectedQueue.h"
#include "Car.h"
#include "Camera.h"
#include <vector>
#include "TileMap.h"
#include "Drawer.h"
#include "ProtectedModel.h"
#include "Receiver.h"
#include "Proxy.h"
#include "Dispatcher.h"
#include <nlohmann/json.hpp>
#include <QApplication>
#include "mainwindow.h"
#include "LuaPlayer.h"
#include "Counter.h"

using json = nlohmann::json;

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();

    Proxy* proxy = w.getProxy();
    try {
        Window main("Micromachines", 1920, 1080);

        Camera cam(main, main.createTextureFrom("../media/sprites/mud_screen_sprite.png"));
        TileMap map(main, w.getInitialData());

        ProtectedModel model(main, w.getInitialData(), cam, map, w.getPlayerID());
        Drawer drawer(main, model);
        drawer.start();

        ProtectedQueue<Event> q;

        Receiver receiver(model, *proxy);
        EventListener handler(w.getPlayerID(), q);
        //LuaPlayer handler(q, model, w.getPlayerID());

        Dispatcher dispatcher(q, *proxy);

        receiver.start();
        dispatcher.start();
        handler.run();

        drawer.stop();
        dispatcher.stop();
        receiver.stop();

        drawer.join();
        dispatcher.join();
        receiver.join();
    } catch(std::runtime_error &e) {
        // Avisar al server que catchee esta exception
        std::cout << "ocurrio una excepcion :( " << e.what() << std::endl;
    }

    SDL_Quit();
    a.quit();
    delete proxy;

    return 0;
}
