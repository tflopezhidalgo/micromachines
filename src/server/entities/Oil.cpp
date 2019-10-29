//
// Created by eliana on 20/10/19.
//

#include <iostream>
#include "Oil.h"

Oil::Oil(b2Body *body, float initialFriction, float friction) :
        Entity(OIL, body),
        initialFriction(initialFriction),
        friction(friction) {}

void Oil::collide(Entity *entity) {
    if (entity->getIdentifier() == CAR) {
        Car* car = dynamic_cast<Car*>(entity);
        setFriction(car);
    }
}

void Oil::setFriction(Car *car) {
    car->setTiresFriction(friction);
}

void Oil::resetFriction(Car *car) {
    car->setTiresFriction(initialFriction);
}

void Oil::endCollision(Entity *entity) {
    if (entity->getIdentifier() == CAR) {
        Car *car = dynamic_cast<Car*>(entity);
        resetFriction(car);
    }
}

