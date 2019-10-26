//
// Created by eliana on 20/10/19.
//

#include <iostream>
#include "Oil.h"

#define STARTFRICTION "tireStartFriction"
#define OILFRICTION "oilFriction"

Oil::Oil(Identifier identifier, b2Body *body, std::map<std::string, float>& config) :
    Entity(OIL, body),
    startFriction(config.find(STARTFRICTION)->second),
    friction(config.find(OILFRICTION)->second) {}

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
    car->setTiresFriction(startFriction);
}

void Oil::collideEnd(Entity *entity) {
    if (entity->getIdentifier() == CAR) {
        Car *car = dynamic_cast<Car*>(entity);
        resetFriction(car);
    }
}

