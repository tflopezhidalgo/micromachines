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
    }
}

void Stone::damageCar(Car* car) {
    car->receiveDamage(damage);
    if (car->isDead()) {
        timedEvents.emplace_back(TimedEvent(car, &Car::updatePosition, 3));
        timedEvents.emplace_back(TimedEvent(car, &Car::recoverHealth, 3));
    }
    car->updateMaxForwardSpeed(speedDecrement);
    timedEvents.emplace_back(TimedEvent(car, &Car::resetMaxForwardSpeed, 10));
    timedEvents.emplace_back(TimedEvent(this, &Entity::die, 1.5f));
}

void Stone::endCollision(Entity *entity) {}

Stone::~Stone() {}
