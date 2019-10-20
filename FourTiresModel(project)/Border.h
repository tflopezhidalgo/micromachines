//
// Created by eliana on 19/10/19.
//

#ifndef MICROMACHINES_BORDER_H
#define MICROMACHINES_BORDER_H

#include "Box2D/Box2D.h"
#include "CrashObject.h"

class Border : public CrashObject {
private:
    b2Body* body;
    CrashType type;
public:
    Border(b2World* world, float pos_x, float pos_y, float len_x, float len_y);

    CrashType getType();
    ~Border();

    void getDamage(int damage);
};


#endif //MICROMACHINES_BORDER_H
