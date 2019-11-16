//
// Created by eliana on 26/10/19.
//

#include "SpeedBooster.h"

SpeedBooster::SpeedBooster(b2Body *body, float speedBoost, std::vector<TimedEvent>& timedEvents) :
        Entity(SPEEDBOOSTER, body),
        timedEvents(timedEvents),
        speedBoost(speedBoost) {}

void SpeedBooster::beginCollision(Entity *entity) {
    if (entity->getIdentifier() == CAR && !isDead()) {
        auto car = dynamic_cast<Car*>(entity);
        boostMaxSpeed(car);
    }
}

void SpeedBooster::endCollision(Entity *entity) {}

void SpeedBooster::boostMaxSpeed(Car* car) {
    car->updateMaxForwardSpeed(speedBoost);
    timedEvents.emplace_back(TimedEvent(car, &Car::resetMaxForwardSpeed, 10));
    die();
}

SpeedBooster::~SpeedBooster() {}
