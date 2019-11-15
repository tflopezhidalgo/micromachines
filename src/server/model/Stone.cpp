//
// Created by eliana on 20/10/19.
//

#include "Stone.h"

Stone::Stone(b2Body* body, int damage) :
    Entity(STONE, body),
    damage(damage) {}

void Stone::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR && !isDead()) {
        Car* car = dynamic_cast<Car*>(entity);
        car->receiveDamage(damage);
        die();
    }
}

void Stone::damageCar(Car* car) {
    car->receiveDamage(damage);
}

void Stone::endCollision(Entity *entity) {}

Stone::~Stone() {}
