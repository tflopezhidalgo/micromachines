//
// Created by leobellaera on 18/10/19.
//

#ifndef TESTING_CAR_H
#define TESTING_CAR_H

#include <vector>
#include <map>
#include "../Box2D/Box2D.h"
#include "Entity.h"
#include "Tire.h"
#include "Health.h"

class Car : public Entity {
private:
    b2RevoluteJoint* frontLeftJoint;
    b2RevoluteJoint* frontRightJoint;
    int carCollisionDamage;
    std::vector<Tire*> tires;
    Health health;
public:
    Car(b2Body* body,
        std::vector<Tire*> tires,
        int carCollisionDamage,
        b2RevoluteJoint* flJoint,
        b2RevoluteJoint* frJoint);
    void updateFriction();
    void updateMove(char action);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* object) override;
    void receiveHealing(int healingPoints);
    void receiveDamage(int damagePoints);
    void setTiresFriction(float newFriction);
    void resetTiresFriction();
    int getRacePosition();
    void setMaxForwardSpeed(float newMaxForwardSpeed);
    int getHealth();
    ~Car();
};

#endif //TESTING_CAR_H
