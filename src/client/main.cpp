#include "../common/Event.h"
#include "EventListener.h"
#include <iostream>
#include <zconf.h>
#include "ProtectedQueue.h"
#include "Camera.h"
#include <vector>
#include "Drawer.h"
#include "ProtectedModel.h"
#include "Receiver.h"
#include "Proxy.h"
#include "Dispatcher.h"
#include <nlohmann/json.hpp>
#include <QApplication>
#include "mainwindow.h"
#include "LuaPlayer.h"
#include "Audio.h"

using json = nlohmann::json;

struct UserData {

};


int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);
    Audio audio;
    Music ambient_music("ambience_music.wav");
    ambient_music.play();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();

    Proxy* proxy = w.getProxy();

    if (!w.isValidUser()){
        SDL_Quit();
        a.quit();
        delete proxy;
        return 1;
    }

    Window *main = NULL;
    Thread *event_handler = NULL;

    try {

        if (w.isFullScreen())
            main = new Window("Micromachines");
        else
            main = new Window("Micromachines", w.getWidthSelected(), w.getHeightSelected());

        Camera cam(*main, main->createTextureFrom("../media/sprites/mud_screen_sprite.png"));
        ProtectedModel model(*main, cam, w.getPlayerID());
        ProtectedQueue<Event> q;

        Drawer drawer(*main, model);
        Receiver receiver(model, *proxy);
        Dispatcher dispatcher(q, *proxy);

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

    /*  Tener cuidado de llamar primero a los joins y después a los destructores
     *  de los objetos compartidos, si no se bloquea en el join / sigsev
     */


    } catch(std::runtime_error &e) {
        // Avisar al server que catchee esta exception
        std::cout << "ocurrio una excepcion :( " << e.what() << std::endl;
        return 1;
    }

    delete event_handler;
    delete main;

    return 0;
}
