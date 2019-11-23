#include <zconf.h>
#include "Drawer.h"
#include "Window.h"
#include "ProtectedModel.h"

Drawer::Drawer(Window& main, ProtectedModel& model) :
main(main),
model(model),
running(true) { }

void Drawer::run() {

    long fixed_time = 1000 / 60; // milisegundos / frames
    while (running){
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        this->main.clear();
        this->model.renderAll();
        this->main.update();
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (duration.count() < fixed_time){}
            std::this_thread::sleep_for(std::chrono::milliseconds(fixed_time - duration.count()));
    }
}

void Drawer::stop() {
    running = false;
}

Drawer::~Drawer() {
    this->join();
}