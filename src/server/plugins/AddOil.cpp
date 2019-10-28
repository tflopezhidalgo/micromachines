//
// Created by eliana on 27/10/19.
//

#ifndef MICROMACHINES_ADDOIL_CPP
#define MICROMACHINES_ADDOIL_CPP

#include <stdlib.h>
#include "Plugin.h"
#include "entities/Car.h"
#include "entities/World.h"

class AddOil : public Plugin {
public:
    // agrega aceite en una posicion random del mapa
    void updateModel(std::vector<Car*> cars, World* world) {
        world->addOil(rand() % 100, rand() % 100);
    }
};


#endif //MICROMACHINES_DECREASESPEED_CPP