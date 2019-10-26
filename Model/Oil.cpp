//
// Created by eliana on 20/10/19.
//

#include <iostream>
#include "Oil.h"

#define FRICTION 9

Oil::Oil(Identifier identifier, b2Body *body) :
    Entity(OIL, body),
    friction(FRICTION) {}

void Oil::collide(Entity *entity) {
    if (entity->getIdentifier() == CAR) {
        Car* car = dynamic_cast<Car*>(entity);
        prevFriction = car->getFriction();
        setFriction(car);
    }
}

void Oil::setFriction(Car *car) {
    car->setTiresFriction(friction);
}

void Oil::resetFriction(Car *car) {
    car->setTiresFriction(prevFriction);
}

void Oil::collideEnd(Entity *entity) {
    if (entity->getIdentifier() == CAR) {
        Car *car = dynamic_cast<Car*>(entity);
        resetFriction(car);
    }
}

