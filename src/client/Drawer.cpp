#include <zconf.h>
#include "Drawer.h"
#include "Window.h"
#include "ProtectedModel.h"

Drawer::Drawer(Window& main, ProtectedModel& model) :
main(main), model(model){
    this->running = true;
}

void Drawer::run() {
    while (running){
        this->main.clear();
        this->model.renderAll();
        this->main.update();
    }
}

void Drawer::stop() {
    running = false;
}
