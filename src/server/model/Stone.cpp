//
// Created by eliana on 20/10/19.
//

#include "Stone.h"

Stone::Stone(b2Body* body, int damage, float speedDecrement, std::vector<TimedEvent>& timedEvents) :
    Entity(STONE, body),
    timedEvents(timedEvents),
    speedDecrement(speedDecrement),
    damage(damage) {}

void Stone::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR && !isDead()) {
        Car* car = dynamic_cast<Car*>(entity);
        damageCar(car);
        timedEvents.emplace_back(TimedEvent(car, &Car::resetMaxForwardSpeed, 10));
        die();
    }
}

void Stone::damageCar(Car* car) {
    car->receiveDamage(damage);
    car->updateMaxForwardSpeed(speedDecrement);
}

void Stone::endCollision(Entity *entity) {}

Stone::~Stone() {}
