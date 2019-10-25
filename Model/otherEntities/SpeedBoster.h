//
// Created by eliana on 20/10/19.
//

#ifndef TESTING_BOOSTS_H
#define TESTING_BOOSTS_H

#include "CollidableObject.h"

class Boosts : public CrashObject {
private:
    b2Body *body;
    CrashType type;
public:
    // elevan la velocidad máxima durante algunos segundos
    Boosts(b2World *world, b2Vec2 &pos);

    CrashType get_type();

    const b2Vec2 getPosition();
};

#endif //TESTING_BOOSTS_H
