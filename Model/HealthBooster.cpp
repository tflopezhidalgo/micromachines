//
// Created by leobellaera on 24/10/19.
//

#include "HealthBooster.h"
#include "Car.h"

#define HEALTH_BOOST 40

HealthBooster::HealthBooster(b2Body* body) :
    Entity(Identifier::HEALTHBOOSTER, body),
    healthBoost(HEALTH_BOOST) {}

void HealthBooster::collide(Entity* entity) {
    if (entity->getIdentifier() == Identifier::CAR) {
        Car* car = dynamic_cast<Car*>(entity);
        this->boost(car);
    }
}

void HealthBooster::boost(Car* car) {
    car->receiveHealing(healthBoost);
}
