//
// Created by eliana on 9/11/19.
//

#include "DecreaseSpeed.h"


void DecreaseSpeed::updateModel(World *world, std::vector<Car *> cars) {
    for (auto car : cars) {
        if (car->getHealth() <= SEVERAL_DAMAGED_POINTS) {
            car->setMaxForwardSpeed(NEWFORDWARDSPEED);
        }
    }
}

extern "C" Plugin* create() {
    return new DecreaseSpeed;
}
