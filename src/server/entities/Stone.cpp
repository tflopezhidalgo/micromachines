//
// Created by eliana on 20/10/19.
//

#include "Stone.h"


Stone::Stone(b2Body *body, float damage, float minForwardSpeed) :
    Entity(STONE, body),
    damage(damage),
    minForwardSpeed(minForwardSpeed) {}

void Stone::collide(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        Car* car = dynamic_cast<Car*>(entity);
        damageCar(car);
        this->exploit();
    }
}

void Stone::damageCar(Car* car) {
    car->receiveDamage(damage);
    car->setMaxForwardSpeed(minForwardSpeed);
}

void Stone::endCollision(Entity *entity) {
    this->die();
}
