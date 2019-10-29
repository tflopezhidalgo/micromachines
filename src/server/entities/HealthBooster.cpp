//
// Created by leobellaera on 24/10/19.
//

#include "HealthBooster.h"
#include "Car.h"

#define HEALTH_BOOST "healthBoost"

HealthBooster::HealthBooster(b2Body* body, std::map<std::string, float>& config) :
    Entity(HEALTHBOOSTER, body),
    healthBoost(config.find(HEALTH_BOOST)->second) {}

void HealthBooster::collide(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        Car* car = dynamic_cast<Car*>(entity);
        this->boost(car);
        //die
    }
}

void HealthBooster::boost(Car* car) {
    car->receiveHealing(healthBoost);
}

void HealthBooster::endCollision(Entity *entity) {}
