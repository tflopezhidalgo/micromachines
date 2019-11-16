#include "Oil.h"

Oil::Oil(b2Body *body, float gripDecrement, std::vector<TimedEvent>& timedEvents) :
        Entity(OIL, body),
        timedEvents(timedEvents),
        gripDecrement(gripDecrement) {}

void Oil::beginCollision(Entity *entity) {
    if (entity->getIdentifier() == CAR && !isDead()) {
        Car* car = dynamic_cast<Car*>(entity);
        reduceGrip(car);
    }
}

void Oil::reduceGrip(Car* car) {
    car->updateMaxLateralImpulse(gripDecrement);
    timedEvents.emplace_back(TimedEvent(car, &Car::resetMaxLateralImpulse, 15));
    die();
}

void Oil::endCollision(Entity *entity) {}

Oil::~Oil() {}
