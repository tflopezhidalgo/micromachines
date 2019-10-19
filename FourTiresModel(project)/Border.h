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
    Border(b2World* world, float pos_x, float pos_y, float len_x, float len_y);

    ~Border();
};


#endif //MICROMACHINES_BORDER_H
