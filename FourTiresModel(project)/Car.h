//
// Created by leobellaera on 18/10/19.
//

#ifndef TESTING_CAR_H
#define TESTING_CAR_H

#include <vector>
#include <map>
#include "Box2D/Box2D.h"
#include "Entity.h"
#include "CarTire.h"
#include "CarBody.h"
#include "Health.h"

class Car : public Entity {
private:
    CarBody carBody;
    b2Body* body;
    Health health;
public:
    Car(b2World* world, b2Body* body, std::map<std::string, float> &config);
    void move(int action);
    void collide(Entity* object) override;
    void receiveHealing(int healingPoints);
    int getHealth();
    ~Car();
};

#endif //TESTING_CAR_H
