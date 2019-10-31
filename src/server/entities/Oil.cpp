//
// Created by eliana on 20/10/19.
//

#include <iostream>
#include "Oil.h"

#define OIL_SKIDDING "oilSkidding"

Oil::Oil(b2Body *body, std::map<std::string, float>& config) :
        Entity(OIL, body),
        oilSkidding(config.find(OIL_SKIDDING)->second) {}

void Oil::beginCollision(Entity *entity) {
    if (entity->getIdentifier() == CAR /*&& isActive()*/) {
        Car* car = dynamic_cast<Car*>(entity);
        //todo change car skidding (view iforce2d tut)
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
