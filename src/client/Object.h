#ifndef MICROMACHINES_OBJECT_H
#define MICROMACHINES_OBJECT_H

#include <Identifiers.h>

class Camera;

class Object {
public:
    virtual void render(Camera& cam) = 0;
    virtual void setPosition(int x, int y, int angle) = 0;
    virtual void setState(EntityStatus state) = 0;
    virtual int getXPos() = 0;
    virtual int getYPos() = 0;
};

#endif
