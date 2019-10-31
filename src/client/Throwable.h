#ifndef MICROMACHINES_THROWABLE_H
#define MICROMACHINES_THROWABLE_H

#include "Entity.h"
#include "ThrowableState.h"
#include "BaseSprite.h"

class Throwable : Entity {
private:
    ThrowableState state;
    BaseSprite sprite;

public:
    Throwable();
    void render(Camera& cam);


};

#endif
