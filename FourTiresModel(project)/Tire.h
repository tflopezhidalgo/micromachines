//
// Created by leobellaera on 18/10/19.
//

#ifndef TESTING_TIRE_H
#define TESTING_TIRE_H

#include "Box2D/Box2D.h"

class Tire {
private:
    float maxForwardSpeed;
    float maxBackwardSpeed;
    float maxDriveForce;
    float maxLateralImpulse;
    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();
public:
    b2Body* body;
    Tire(b2World* world);
    ~Tire();
    void updateDrive(int key);
    void updateTurn(int key);
    void updateFriction();
    void setCharacteristics(float maxFSpeed, float maxBSpeed, float maxDForce, float maxLatImpulse);
};

#endif //TESTING_TIRE_H
