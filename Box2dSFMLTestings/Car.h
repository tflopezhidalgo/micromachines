//
// Created by leobellaera on 18/10/19.
//

#ifndef TESTING_CAR_H
#define TESTING_CAR_H

#include "Box2D/Box2D.h"

class Car {
private:
    b2Body* body;
    float maxForwardSpeed;
    float maxBackwardSpeed;
    float maxDriveForce;
    float maxLateralImpulse;
    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();
    void updateDrive(int key);
    void updateTurn(int key);
public:
    Car(b2World* world);
    void update(int key);
    void updateFriction();
    b2Vec2 getPosition();
    float getAngle();
    ~Car();
};

#endif //TESTING_CAR_H
