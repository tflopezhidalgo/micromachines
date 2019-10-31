//
// Created by eliana on 20/10/19.
//

#include <iostream>
#include "Oil.h"

#define OIL_FRICTION "oilFriction"

Oil::Oil(b2Body *body, std::map<std::string, float>& config) :
        Entity(OIL, body),
        friction(config.find(OIL_FRICTION)->second) {}

void Oil::collide(Entity *entity) {
    if (entity->getIdentifier() == CAR /*&& isActive()*/) {
        Car* car = dynamic_cast<Car*>(entity);
        setFriction(car);
        die();
    }
}

void Oil::endCollision(Entity *entity) {
    if (entity->getIdentifier() == CAR) {
        Car *car = dynamic_cast<Car*>(entity);
        resetFriction(car);
    }
}

void Oil::resetFriction(Car *car) {
    car->resetTiresFriction();
}

void Oil::setFriction(Car *car) {
    car->setTiresFriction(friction);
}
