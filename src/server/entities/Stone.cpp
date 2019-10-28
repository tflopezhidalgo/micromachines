//
// Created by eliana on 20/10/19.
//

#include "Stone.h"

#define STONE_DAMAGE "stoneDamage"

Stone::Stone(b2Body* body, std::map<std::string, float>& config) :
    Entity(STONE, body),
    damage(config.find(STONE_DAMAGE)->second) {}

void Stone::collide(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        Car* car = dynamic_cast<Car*>(entity);
        damageCar(car);
        //die
    }
}

void Stone::damageCar(Car* car) {
    car->receiveDamage(damage);
}

void Stone::endCollision(Entity *entity) {}
