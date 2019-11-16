#include "Mud.h"

Mud::Mud(b2Body *body, std::vector<TimedEvent> &timedEvents) :
    Entity(MUD, body),
    timedEvents(timedEvents) {}

void Mud::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR && !isDead()) {
        Car* car = dynamic_cast<Car*>(entity);
        reduceVision(car);
    }
}

void Mud::reduceVision(Car* car) {
    car->reduceVision();
    timedEvents.emplace_back(TimedEvent(car, &Car::recoverTotalVision, 3));
    die();
}

void Mud::endCollision(Entity* entity) {}

Mud::~Mud() {}
