//
// Created by eliana on 27/10/19.
//

#ifndef MICROMACHINES_DECREASESPEED_CPP
#define MICROMACHINES_DECREASESPEED_CPP

#include "Plugin.h"
#include "../entities/Car.h"
#include "../entities/World.h"

#define NEWFORDWARDSPEED 70

class DecreaseSpeed : public Plugin {
public:
    void updateModel(std::vector<Car*> cars, World* world) {
        for (auto car : cars) {
            if (car->getStatus() == Status::SEVERALDAMAGED) {
                car->setMaxForwardSpeed(NEWFORDWARDSPEED);
            }
        }
    }
};


#endif //MICROMACHINES_DECREASESPEED_CPP
