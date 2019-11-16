#ifndef TESTING_COLLISIONSPROCESSOR_H
#define TESTING_COLLISIONSPROCESSOR_H

#include "Box2D/Box2D.h"


class CollisionsProcessor : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
};

#endif //TESTING_COLLISIONSPROCESSOR_H
