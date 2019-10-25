#ifndef MICROMACHINES_DRAWER_H
#define MICROMACHINES_DRAWER_H

#include "../common/Thread.h"
#include "Entity.h"
#include <vector>
#include "Window.h"

class Drawer: public Thread {
private:
    std::vector<std::reference_wrapper<Entity>> entities;
    bool running;
    Window& main;

public:
    Drawer(Window& main);
    void addEntity(Entity& entity);
    void run();
    void stop();
    ~Drawer() {

    }
};

#endif
