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
        Window *main = NULL;
        if (w.isFullScreen())
            main = new Window("Micromachines");
        else
            main = new Window("Micromachines", w.getWidthSelected(), w.getHeightSelected());

        Camera cam(*main, main->createTextureFrom("../media/sprites/mud_screen_sprite.png"));
        TileMap map(*main, w.getInitialData());
        ProtectedModel model(*main, w.getInitialData(), cam, map, w.getPlayerID());
        ProtectedQueue<Event> q;

        Drawer drawer(*main, model);
        Receiver receiver(model, *proxy);
        Dispatcher dispatcher(q, *proxy);
        Thread *event_handler = NULL;

        if (w.isLuaPlayer())
            event_handler = new LuaPlayer(q, model, w.getPlayerID());
        else
            event_handler = new EventListener(w.getPlayerID(), q);

        drawer.start();
        receiver.start();
        dispatcher.start();

        event_handler->run();

        drawer.stop();
        dispatcher.stop();
        receiver.stop();

        drawer.join();
        dispatcher.join();
        receiver.join();

        delete event_handler;
        delete main;
    } catch(std::runtime_error &e) {
        // Avisar al server que catchee esta exception
        std::cout << "ocurrio una excepcion :( " << e.what() << std::endl;
    }

    SDL_Quit();
    a.quit();
    delete proxy;

    return 0;
}
