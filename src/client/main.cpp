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

using json = nlohmann::json;

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();

    Proxy* proxy = w.getProxy();

    Window main("Game", 900, 600);
    //Window main("game");

    ProtectedQueue<Event> q;
    ProtectedModel model(main, w.getPlayerID());

    Receiver receiver(model, *proxy);
    Drawer drawer(main, model);
    EventListener handler(w.getPlayerID(), q);
    //LuaPlayer handler(q, model, w.getPlayerID());
    Dispatcher dispatcher(q, *proxy);

    receiver.start();
    dispatcher.start();
    drawer.start();
    handler.run();

    drawer.stop();
    dispatcher.stop();
    receiver.stop();
    drawer.join();
    dispatcher.join();
    receiver.join();

    SDL_Quit();
    delete proxy;

    return 0;
}
