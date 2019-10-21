//
// Created by eliana on 20/10/19.
//

#ifndef TESTING_STONE_H
#define TESTING_STONE_H

#include "CrashObject.h"

class Stone : public CrashObject {
private:
    b2Body* body;
    CrashType type;
public:
    Stone(b2World *world, b2Vec2 &pos);
    CrashType get_type();

    const b2Vec2 getPosition();
};


#endif //TESTING_STONE_H
