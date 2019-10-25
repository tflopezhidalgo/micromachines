//
// Created by leobellaera on 18/10/19.
//

#ifndef TESTING_CARTIRE_H
#define TESTING_CARTIRE_H

#include "Box2D/Box2D.h"
#include "Entity.h"
#include <map>
#include <string>

class CarTire {
private:
    float maxForwardSpeed;
    float maxBackwardSpeed;
    float maxDriveForce;
    float maxLateralImpulse;
    b2Body* body;
    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();
public:
    CarTire(b2World* world, std::map<std::string, float>& config);
    void updateDrive(int action);
    void updateFriction();
    void setCharacteristics(float maxForwardSpeed, float maxBackwardSpeed,
            float maxDriveForce, float maxLateralImpulse);
    b2Body* getBody();
    ~CarTire();
};

#endif //TESTING_CARTIRE_H
