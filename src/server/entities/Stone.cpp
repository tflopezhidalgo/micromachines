//
// Created by eliana on 20/10/19.
//

#include "Stone.h"

#define DAMAGE 20

Stone::Stone(b2Body* body) :
    Entity(STONE, body),
    damage(DAMAGE) {}

void Stone::collide(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        Car* car = dynamic_cast<Car*>(entity);
        damageCar(car);
    }
}

void Stone::damageCar(Car* car) {
    car->receiveDamage(damage);
}

void Stone::collideEnd(Entity *entity) {
    // pass
}
