#include "SpeedBooster.h"

SpeedBooster::SpeedBooster(b2Body *body, float speedBoost, std::vector<TimedEvent>& timedEvents) :
        Entity(SPEEDBOOSTER, body),
        timedEvents(timedEvents),
        speedBoost(speedBoost),
        used(false) {}

void SpeedBooster::beginCollision(Entity *entity) {
    if (entity->getIdentifier() == CAR && !isDead() && !used) {
        auto car = dynamic_cast<Car*>(entity);
        boostMaxSpeed(car);
    }
}

void SpeedBooster::endCollision(Entity *entity) {}

void SpeedBooster::boostMaxSpeed(Car* car) {
    used = true;
    car->updateMaxForwardSpeed(speedBoost);
    timedEvents.emplace_back(TimedEvent(car, &Car::resetMaxForwardSpeed, 10));
    timedEvents.emplace_back(TimedEvent(this, &Entity::die, 0.5f));
}

SpeedBooster::~SpeedBooster() {}
