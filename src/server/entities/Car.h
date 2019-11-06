//
// Created by leobellaera on 18/10/19.
//

#ifndef TESTING_CAR_H
#define TESTING_CAR_H

#include <vector>
#include <unordered_map>
#include "Box2D/Box2D.h"
#include "Tire.h"
#include "Health.h"
#include "Entity.h"

class Car : public Entity {
private:
    std::string id;
    b2RevoluteJoint* frontLeftJoint;
    b2RevoluteJoint* frontRightJoint;
    std::vector<Tire*> tires;
    Health health;
    int carCollisionDamage;
public:
    Car(std::string id, b2Body* body, std::vector<Tire*> tires,
        int carCollisionDamage,
        b2RevoluteJoint* flJoint,
        b2RevoluteJoint* frJoint);
    void updateFriction();
    void updateMove(std::vector<char>& actions);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* object) override;
    void receiveHealing(int healingPoints);
    void receiveDamage(int damagePoints);
    void setTiresFriction(float newFriction);
    int getRacePosition();
    void setMaxForwardSpeed(float newMaxForwardSpeed);
    int getHealth();
    std::string& getId();
    ~Car();
};

#endif //TESTING_CAR_H
