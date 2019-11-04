#ifndef MICROMACHINES_THROWABLEFACTORY_H
#define MICROMACHINES_THROWABLEFACTORY_H

#include "Throwable.h"
#include "BaseSprite.h"
#include "Window.h"

class ThrowableFactory {
private:
    Window& window;

public:
    explicit ThrowableFactory(Window& window);
    Throwable* generateThrowable(std::string& type);

};

#endif
