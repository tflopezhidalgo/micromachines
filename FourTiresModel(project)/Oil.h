//
// Created by eliana on 20/10/19.
//

#ifndef TESTING_OIL_H
#define TESTING_OIL_H

#include "CrashObject.h"

class Oil : public CrashObject {
private:
    b2Body* body;
    CrashType type;
public:
    Oil(b2World *world, b2Vec2 &pos);
    CrashType get_type();

    const b2Vec2 getPosition();
};


#endif //TESTING_OIL_H
