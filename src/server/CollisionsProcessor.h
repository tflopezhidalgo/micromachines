//
// Created by leobellaera on 24/10/19.
//

#ifndef TESTING_COLLISIONSPROCESSOR_H
#define TESTING_COLLISIONSPROCESSOR_H

#include "Box2D/Box2D.h"


class CollisionsProcessor : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact) override;
};

#endif //TESTING_COLLISIONSPROCESSOR_H
