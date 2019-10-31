//
// Created by leobellaera on 24/10/19.
//

#include "HealthBooster.h"
#include "Car.h"

HealthBooster::HealthBooster(b2Body* body, int healing) :
    Entity(HEALTHBOOSTER, body),
    healthBoost(healing) {}

void HealthBooster::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR && !isDead()) {
        Car* car = dynamic_cast<Car*>(entity);
        car->receiveHealing(healthBoost);
        die();
    }
}

void HealthBooster::heal(Car* car) {
    car->receiveHealing(healthBoost);
}

void HealthBooster::endCollision(Entity *entity) {}
