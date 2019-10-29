//
// Created by eliana on 28/10/19.
//

#ifndef MICROMACHINES_ADDSTONE_CPP
#define MICROMACHINES_ADDSTONE_CPP

#include <stdlib.h>
#include "Plugin.h"
#include "entities/Car.h"
#include "entities/World.h"

class AddStone : public Plugin {
public:
    // agrega piedra en una posicion random del mapa
    void updateModel(std::vector<Car*> cars, World* world) {
        world->addStone(rand() % 100, rand() % 100);
    }
};

#endif //MICROMACHINES_ADDSTONE_CPP