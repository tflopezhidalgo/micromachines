//
// Created by leobellaera on 3/11/19.
//

#ifndef MICROMACHINES_GRANDSTAND_H
#define MICROMACHINES_GRANDSTAND_H

#include "Box2D/Box2D.h"
#include <vector>
#include "Entity.h"

class GrandStand {
private:
    b2Body* body;
    int objectsThrownNumber;
public:
    GrandStand(b2Body* body, int objectsThrownNumber, float x_pos, float y_pos);
    void throwObjectsToPilots(std::vector<Entity*> entities);
    ~GrandStand();
};


#endif //MICROMACHINES_GRANDSTAND_H
