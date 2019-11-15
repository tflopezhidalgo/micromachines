//
// Created by eliana on 28/10/19.
//

#ifndef MICROMACHINES_ADDSTONE_CPP
#define MICROMACHINES_ADDSTONE_CPP

#include <stdlib.h>
#include "entities/Car.h"
#include "World.h"
#include "Plugin.h"

#define MAX 100

class AddStone : public Plugin {
public:
    // agrega piedra en una posicion random del mapa
    void updateModel(World *world, std::vector<Car *> cars) override;

    float getPosition();
};

#endif //MICROMACHINES_ADDSTONE_CPP