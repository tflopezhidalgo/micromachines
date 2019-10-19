//
// Created by leobellaera on 18/10/19.
//

#ifndef TESTING_CAR_H
#define TESTING_CAR_H

#include <vector>
#include "Box2D/Box2D.h"
#include "Tire.h"

class Car {
private:
    b2Body* body;
    std::vector<Tire*> tires;
    b2RevoluteJoint *flJoint, *frJoint;
public:
    Car(b2World* world);
    void update(int key);
    b2Vec2 getPosition();
    float getAngle();
    ~Car();
};

#endif //TESTING_CAR_H
