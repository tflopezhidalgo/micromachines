//
// Created by leobellaera on 18/10/19.
//

#ifndef TESTING_CAR_H
#define TESTING_CAR_H

#include <vector>
#include <map>
#include "Box2D/Box2D.h"
#include "Entity.h"
#include "Tire.h"
#include "Health.h"

class Car : public Entity {
private:
    b2Body* body;
    b2RevoluteJoint* frontLeftJoint;
    b2RevoluteJoint* frontRightJoint;
    std::vector<Tire*> tires;
    Health health;
public:
    Car(b2Body* body, std::vector<Tire*> tires, b2RevoluteJoint* flJoint, b2RevoluteJoint* frJoint);
    void move(int action);
    void collide(Entity* object) override;
    void receiveHealing(int healingPoints);
    void receiveDamage(int damagePoints);
    int getHealth();
    ~Car();
};

#endif //TESTING_CAR_H
