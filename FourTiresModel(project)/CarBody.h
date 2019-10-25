//
// Created by leobellaera on 23/10/19.
//

#ifndef TESTING_CARBODY_H
#define TESTING_CARBODY_H

#include <map>
#include <vector>
#include <string>
#include "Box2D/Box2D.h"
#include "CarTire.h"

class CarBody {
private:
    b2Body* body;
    std::vector<CarTire*> tires;
    b2RevoluteJoint *flJoint, *frJoint;
    void createChassisFixture();
    b2RevoluteJoint* joinTireToChassis(b2World* world,
                           b2RevoluteJointDef* jointDef,
                           CarTire* tire,
                           float x_pos,
                           float y_pos);
public:
    void move(int action);
    CarBody(b2World* world, b2Body* body, std::map<std::string, float>& config);
    //void setUserData(Car* owner);
    ~CarBody();
};

#endif //TESTING_CARBODY_H
