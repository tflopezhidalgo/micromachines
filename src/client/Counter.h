#ifndef MICROMACHINES_COUNTER_H
#define MICROMACHINES_COUNTER_H

#include <vector>
#include "Proxy.h"
#include "Window.h"
#include "Texture.h"
#include <functional>

class Counter {
private:
    Window& window;
    Texture& ready;
    Texture& set;
    Texture& go;
    int counter;

public:
    Counter(Window& window);
    void count();
    void render(int x, int y);
};


#endif
