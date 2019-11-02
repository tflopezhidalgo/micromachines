//
// Created by eliana on 20/10/19.
//

#ifndef PLUGINS_INCREASESPEED_H
#define PLUGINS_INCREASESPEED_H

#include "entities/World.h"
#include "entities/Car.h"

#define NEWFORDWARDSPEED 150

class IncreaseSpeed {
public:
    void updateModel(std::vector<Car*> cars, World* world) {
        for (auto car : cars) {
            if (car->getRacePosition() == cars.size()) {
                car->setMaxForwardSpeed(NEWFORDWARDSPEED);
            }
        }
    }
};


#endif //PLUGINS_INCREASESPEED_H
