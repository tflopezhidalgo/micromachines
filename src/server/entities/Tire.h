//
// Created by leobellaera on 18/10/19.
//

#ifndef TESTING_TIRE_H
#define TESTING_TIRE_H

#include "../Box2D/Box2D.h"
#include "Entity.h"
#include <map>
#include <string>

class Tire {
private:
    float maxForwardSpeed;
    float maxBackwardSpeed;
    float maxDriveForce;
    float maxLateralImpulse;
    float frictionFactor;
    b2Body* body;
    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();
public:
    Tire(b2Body* body, float maxForwardSpeed,
                        float maxBackwardSpeed,
                        float maxDriveForce,
                        float maxLateralImpulse,
                        float frictionFactor);
    void updateDrive(char action);
    void updateFriction();
    void setFriction(float newFriction);
    void setMaxForwardSpeed(float newMaxForwardSpeed);
    ~Tire();
};

#endif //TESTING_TIRE_H
