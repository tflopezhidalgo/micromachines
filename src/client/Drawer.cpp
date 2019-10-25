#include "Drawer.h"
#include "Window.h"

Drawer::Drawer(Window& main) : main(main){
    this->running = true;
}

void Drawer::addEntity(Entity &entity) {
    this->entities.push_back(entity);
}

void Drawer::run() {
    while (running){
        for (Entity& e : entities) {
            e.render();
        }

        this->main.update();
    }
}

void Drawer::stop() {
    running = false;
}
