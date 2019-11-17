#ifndef MICROMACHINES_COUNTER_H
#define MICROMACHINES_COUNTER_H

#include <vector>
#include "Proxy.h"
#include "Window.h"
#include "Texture.h"
#include <functional>

class Counter {
private:
    Proxy* proxy;
    Window& window;
    std::vector<Texture*> textures;

public:
    Counter(Proxy* proxy, Window& window);

    void count();

};


#endif
