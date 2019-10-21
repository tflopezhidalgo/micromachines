//
// Created by eliana on 19/10/19.
//

#ifndef TESTING_CRASHOBJECT_H
#define TESTING_CRASHOBJECT_H

#include <Box2D/Common/b2Math.h>

enum CrashType {
    PLAYER,
    CAR,
    BORDER,
    HEALTHBOX,
    OIL,
    BOOSTS,
    STONE,
    MUD,
};

class CrashObject {
private:
    CrashType type;
    int health = 100;
public:
    virtual CrashType getType() = 0;

    virtual void getDamage(int damage) = 0;

    const b2Vec2 getPosition();
};

#endif //TESTING_CRASHOBJECT_H
