//
// Created by eliana on 20/10/19.
//

#include "Oil.h"

Oil::Oil(b2Body *body, float grip) :
        Entity(OIL, body),
        grip(grip) {}

void Oil::beginCollision(Entity *entity) {
    if (entity->getIdentifier() == CAR && !isDead()) {
        Car* car = dynamic_cast<Car*>(entity);
        //todo
        //setSkidding(car);
        die();
    }
}

void Oil::endCollision(Entity *entity) {
    if (entity->getIdentifier() == CAR) {
        Car *car = dynamic_cast<Car*>(entity);
        //resetSkidding(car);
    }
}

Oil::~Oil() {}
