#ifndef MICROMACHINES_OBJECTFACTORY_H
#define MICROMACHINES_OBJECTFACTORY_H

#include "Throwable.h"
#include "Sprite.h"
#include "Window.h"

class ObjectFactory {
private:
    Window& window;

public:
    explicit ObjectFactory(Window& window);
    Object* generateObject(EntityIdentifier type);
};

#endif
