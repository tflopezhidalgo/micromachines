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
#include "ffmpeg/Recorder.h"
#include "LuaPlayer.h"
#include "ffmpeg/RecorderHandle.h"
#include "Counter.h"

#define LUA_PLAYER "player.lua"
using json = nlohmann::json;

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();

    Proxy* proxy = w.getProxy();
    try {
        Window main(GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);

        //std::string fileName = std::string(GAME_NAME) + std::string(EXTENSION);

        //av_register_all();
        ProtectedVector pv;
        //Recorder recorder(main.getWidth(), main.getHeight(), pv, fileName);
        RecorderHandle recorderHandle(pv);

        Camera cam(main, main.createTextureFrom("../media/sprites/mud_screen_sprite.png"));
        TileMap map(main, w.getInitialData());

        ProtectedModel model(main, w.getInitialData(), cam, map, w.getPlayerID());
        Drawer drawer(main, model, pv);
        
        ProtectedQueue<Event> q;

        Receiver receiver(model, *proxy);
        //EventListener handler(w.getPlayerID(), q);
        LuaPlayer handler(q, model, w.getPlayerID(), std::string(LUA_PLAYER));

        Dispatcher dispatcher(q, *proxy);

        //recorder.start();
        drawer.start();
        receiver.start();
        dispatcher.start();

        try {
          handler.run();
        } catch {
          std::cout << "ocurrio una excepcion en el handler.run() :( " << e.what() << std::endl;
        }

        //recorder.stop();
        drawer.stop();
        dispatcher.stop();
        receiver.stop();

        //recorder.join();
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
