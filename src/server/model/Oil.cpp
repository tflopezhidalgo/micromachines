#include "Oil.h"

Oil::Oil(b2Body *body, float gripDecrement, std::vector<TimedEvent>& timedEvents) :
        Entity(OIL, body),
        timedEvents(timedEvents),
        gripDecrement(gripDecrement),
        used(false) {}

void Oil::beginCollision(Entity *entity) {
    if (entity->getIdentifier() == CAR && !isDead() && !used) {
        Car* car = dynamic_cast<Car*>(entity);
        reduceGrip(car);
    }
}

void Oil::reduceGrip(Car* car) {
    used = true;
    car->updateMaxLateralImpulse(gripDecrement);
    timedEvents.emplace_back(TimedEvent(car, &Car::resetMaxLateralImpulse, 15));
    timedEvents.emplace_back(TimedEvent(this, &Entity::die, 0.5f));
}

void Oil::endCollision(Entity *entity) {}

Oil::~Oil() {}
