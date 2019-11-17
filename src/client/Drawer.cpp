#include <zconf.h>
#include "Drawer.h"
#include "Window.h"
#include "ProtectedModel.h"

Drawer::Drawer(Window& main, ProtectedModel& model, Counter& counter) :
main(main), model(model), counter(counter){
    this->running = true;
}

void Drawer::run() {

    //counter.count();

    std::chrono::high_resolution_clock::duration fixed_time(1/60);

    while (running){
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        this->main.clear();
        this->model.renderAll();
        this->main.update();
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(fixed_time - (start - end));
    }
}

void Drawer::stop() {
    running = false;
}
