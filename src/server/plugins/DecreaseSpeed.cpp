//
// Created by eliana on 27/10/19.
//

#ifndef MICROMACHINES_DECREASESPEED_CPP
#define MICROMACHINES_DECREASESPEED_CPP

#include "entities/Car.h"
#include "World.h"

#define NEWFORDWARDSPEED 70
#define SEVERAL_DAMAGED_POINTS 50

class DecreaseSpeed {
public:
    void updateModel(std::vector<Car*> cars, World* world) {
        for (auto car : cars) {
            if (car->getHealth() == SEVERAL_DAMAGED_POINTS) {
                car->setMaxForwardSpeed(NEWFORDWARDSPEED);
            }
        }
    }
};


#endif //MICROMACHINES_DECREASESPEED_CPP
