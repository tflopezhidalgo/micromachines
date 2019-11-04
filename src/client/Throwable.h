#ifndef MICROMACHINES_THROWABLE_H
#define MICROMACHINES_THROWABLE_H

#include "Entity.h"
#include "BaseSprite.h"

class Throwable : Entity {
private:
    bool alive;
    BaseSprite sprite;
    int x;
    int y;

public:
    Throwable(BaseSprite sprite, bool alive, int x, int y);
    Throwable(Throwable&& other);
    void setPos(int x, int y);
    void setState(bool state);
    void render(Camera& cam);


};

#endif
