//
// Created by eliana on 19/10/19.
//

#ifndef MICROMACHINES_BORDER_H
#define MICROMACHINES_BORDER_H

#include "Box2D/Box2D.h"

class Border {
private:
    b2Body* body;
public:
    Border(b2World* world, int x, int y);
};


#endif //MICROMACHINES_BORDER_H
