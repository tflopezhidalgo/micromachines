#ifndef MICROMACHINES_THROWABLE_H
#define MICROMACHINES_THROWABLE_H

#include "Entity.h"
#include "Sprite.h"
#include "Identifiers.h"

class Throwable : Entity {
private:
    EntityStatus state;
    Sprite sprite;
    int x;
    int y;

public:
    Throwable(Sprite sprite, EntityStatus state, int x, int y);
    Throwable(Throwable&& other);
    void setPos(int x, int y);
    int getXPos();
    int getYPos();
    void setState(EntityStatus state);
    void render(Camera& cam);


};

#endif
