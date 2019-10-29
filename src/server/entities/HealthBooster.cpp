//
// Created by leobellaera on 24/10/19.
//

#include "HealthBooster.h"
#include "Car.h"


HealthBooster::HealthBooster(b2Body* body, float healthBoost) :
    Entity(HEALTHBOOSTER, body),
    healthBoost(healthBoost) {}

void HealthBooster::collide(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        Car* car = dynamic_cast<Car*>(entity);
        boost(car);
        this->exploit();
    }
}

void HealthBooster::boost(Car* car) {
    car->receiveHealing(healthBoost);
}

void HealthBooster::endCollision(Entity *entity) {
    this->die();
}

