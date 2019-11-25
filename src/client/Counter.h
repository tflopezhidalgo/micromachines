#ifndef MICROMACHINES_COUNTER_H
#define MICROMACHINES_COUNTER_H

#include "Window.h"
#include "Texture.h"

class Counter {
private:
    Window& window;
    Texture& ready;
    Texture& set;
    Texture& go;
    int counter;

public:
    explicit Counter(Window& window);
    void count();
    void render();
};


#endif
