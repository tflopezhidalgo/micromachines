#include "HealthBooster.h"
#include "Car.h"

HealthBooster::HealthBooster(b2Body* body, int healing, std::vector<TimedEvent>& timedEvents) :
    Entity(HEALTHBOOSTER, body),
    timedEvents(timedEvents),
    healthBoost(healing),
    used(false) {}

void HealthBooster::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR && !isDead() && !used) {
        Car* car = dynamic_cast<Car*>(entity);
        car->receiveHealing(healthBoost);
    }
}

void HealthBooster::heal(Car* car) {
    used = true;
    car->receiveHealing(healthBoost);
    timedEvents.emplace_back(TimedEvent(this, &Entity::die, 0.5f));
}

void HealthBooster::endCollision(Entity *entity) {}

HealthBooster::~HealthBooster() {}
