//
// Created by leobellaera on 18/10/19.
//

#include "Car.h"
#include "HealthBooster.h"

#define INITIAL_HEALTH 100

Car::Car(b2World* world, b2Body* body, std::map<std::string, float>& config) :
        Entity(Identifier::CAR, body),
        carBody(world, body, config),
        health(INITIAL_HEALTH) {}

void Car::move(int action) {
    //if status..
    carBody.move(action);
}

/*void Car::setStatus() {
    status = EXPLODING, etc
}*/

void Car::collide(Entity* object) {
    if (object->getIdentifier() == HEALTHBOOSTER) {
        auto healthBooster = dynamic_cast<HealthBooster*>(object);
        healthBooster->boost(this);
    }
}

void Car::receiveHealing(int healingPoints) {
    health.receiveHealing(healingPoints);
}

int Car::getHealth() {
    return health.getHealth();
}

Car::~Car() {}
