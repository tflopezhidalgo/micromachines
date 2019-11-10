//
// Created by eliana on 9/11/19.
//

#include "IncreaseSpeed.h"


void IncreaseSpeed::updateModel(World *world, std::vector<Car *> cars) {
    for (auto car : cars) {
        /* if (car->getRacePosition() == cars.size()) {
            car->setMaxForwardSpeed(NEWFORDWARDSPEED);
        } */
    }
}

extern "C" Plugin* create() {
    return new IncreaseSpeed;
}
