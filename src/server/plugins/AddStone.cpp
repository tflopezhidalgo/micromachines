//
// Created by eliana on 28/10/19.
//

#ifndef MICROMACHINES_ADDSTONE_CPP
#define MICROMACHINES_ADDSTONE_CPP

#include <stdlib.h>
#include "entities/Car.h"
#include "entities/World.h"

#define MAX 100

class AddStone {
public:
    // agrega piedra en una posicion random del mapa
    void updateModel(std::vector<Car*> cars, World* world) {
        world->addStone(getPosition(), getPosition());
    }

    float getPosition() {
        auto val = rand() % MAX;
        float newVal = val + val % 5;
        return newVal;
    }
};

#endif //MICROMACHINES_ADDSTONE_CPP