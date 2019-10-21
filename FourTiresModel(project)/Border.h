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
    Border(b2World* world, b2Vec2 &pos, b2Vec2 &len);

    CrashType getType() override;
    ~Border();

    void getDamage(int damage) override;
};


#endif //MICROMACHINES_BORDER_H
