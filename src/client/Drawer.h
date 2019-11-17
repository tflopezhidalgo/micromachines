#ifndef MICROMACHINES_DRAWER_H
#define MICROMACHINES_DRAWER_H

#include "Counter.h"
#include "../common/Thread.h"
#include <vector>
#include "Window.h"
#include "ProtectedModel.h"

class Drawer: public Thread {
private:
    bool running;
    Window& main;
    ProtectedModel& model;

public:
    Drawer(Window& main, ProtectedModel& model);
    void run();
    void stop();
    ~Drawer() {

    }
};

#endif
