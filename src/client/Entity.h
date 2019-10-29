#ifndef MICROMACHINES_ENTITY_H
#define MICROMACHINES_ENTITY_H

#include <entities/Entity.h>

class Entity {
public:
    Entity() {}
    virtual void render() = 0;
    virtual int getXPos() {
        return 0;
    }
    virtual int getYPos() {
        return 0;
    }

    virtual void setPos(int x, int y, int angle){

    }

    ~Entity(){

    }
};

#endif
