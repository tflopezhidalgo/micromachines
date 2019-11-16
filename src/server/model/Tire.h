#ifndef TESTING_TIRE_H
#define TESTING_TIRE_H

#include <vector>
#include <map>
#include <string>
#include "Box2D/Box2D.h"

class Tire {
private:
    float maxForwardSpeed;
    float maxBackwardSpeed;
    float maxDriveForce;
    float maxLateralImpulse;
    float defaultMaxForwardSpeed;
    float actualFriction;
    b2Body* body;
    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();
public:
    Tire(
        b2Body* body,
        float maxFwSpeed,
        float maxBwSpeed,
        float maxDriveForce,
        float maxLatImpulse,
        float defaultFriction
    );
    void updateDrive(std::vector<char>& actions);
    void updateFriction();
    void setFriction(float newFriction);
    void setTransform(b2Vec2 position, float angle);
    void updateMaxForwardSpeed(float difference);
    void resetMaxForwardSpeed();
    ~Tire();
};

#endif //TESTING_TIRE_H
