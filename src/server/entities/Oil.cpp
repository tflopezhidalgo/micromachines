//
// Created by eliana on 20/10/19.
//

#include <iostream>
#include "Oil.h"

#define INITIAL_FRICTION "tiresFriction"
#define OIL_FRICTION "oilFriction"

Oil::Oil(b2Body *body, std::map<std::string, float>& config) :
        Entity(OIL, body),
        initialFriction(config.find(INITIAL_FRICTION)->second),
        friction(config.find(OIL_FRICTION)->second) {}

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

