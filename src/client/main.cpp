#include <QApplication>
#include "EventListener.h"
#include "ProtectedQueue.h"
#include "Camera.h"
#include "Drawer.h"
#include "ProtectedModel.h"
#include "Receiver.h"
#include "Proxy.h"
#include "Dispatcher.h"
#include "ffmpeg/RecorderHandle.h"
#include "mainwindow.h"
#include "ffmpeg/Recorder.h"
#include "LuaPlayer.h"
#include "Audio.h"
#include "RecordingWidget.h"
#include "MudSplashWidget.h"
#include <SDL2/SDL_ttf.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char* argv[]) {

    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    Audio audio;
    Music ambient_music("../media/sounds/ambience_music.wav");
    ambient_music.play(-1);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();

    Proxy* proxy = w.getProxy();

    if (!w.isValidUser()){
        SDL_Quit();
        TTF_Quit();
        a.quit();
        delete proxy;
        return 1;
    }

    Window *main = NULL;
    Thread *event_handler = NULL;

    try {
        if (w.isFullScreen())
            main = new Window(GAME_NAME);
        else
            main = new Window(GAME_NAME, w.getWidthSelected(), w.getHeightSelected());

        Camera cam(*main);
        ProtectedModel model(*main, cam, w.getPlayerID());
        ProtectedQueue<Event> q;
        ProtectedVector pv;
        RecorderHandle recHandle(pv, main->getWidth(), main->getHeight());
        av_register_all();

        RecordingWidget widget(*main, recHandle);
        cam.addWidget(&widget);

        MudSplashWidget mud_widget(*main);
        cam.addWidget(&mud_widget);

        Drawer drawer(*main, model, pv);
        Receiver receiver(model, *proxy);
        Dispatcher dispatcher(q, *proxy);

        if (w.isLuaPlayer()) {
            event_handler = new LuaPlayer(q, model, w.getPlayerID(), "player.lua");
            //event_handler = new LuaPlayer(q, model, w.getPlayerID(), w.getLuaPath());
            recHandle.startRecorder();
        } else {
            event_handler = new EventListener(w.getPlayerID(), q, recHandle);
        }

        drawer.start();
        receiver.start();
        dispatcher.start();

        event_handler->run();
        
        dispatcher.stop();
        receiver.stop();
        drawer.stop();
        recHandle.stopRecorder();

    } catch(std::runtime_error &e) {
        SDL_Quit();
        TTF_Quit();
        a.quit();
        delete event_handler;
        delete main;
        return 1;
    }

    SDL_Quit();
    TTF_Quit();
    a.quit();
    delete event_handler;
    delete main;

    return 0;
}
