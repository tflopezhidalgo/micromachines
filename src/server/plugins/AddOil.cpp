//
// Created by eliana on 27/10/19.
//

#ifndef MICROMACHINES_ADDOIL_CPP
#define MICROMACHINES_ADDOIL_CPP

#include <stdlib.h>
#include "entities/Car.h"
#include "entities/World.h"

#define MAX 100

class AddOil {
public:
    // agrega aceite en una posicion random del mapa
    void updateModel(std::vector<Car*> cars, World* world) {
        world->addOil(getPosition(), getPosition());
    }

    float getPosition() {
        float val = rand() % MAX;
        float newVal = val + val % 5;
        return newVal;
    }
};


#endif //MICROMACHINES_ADDSTONE_CPP