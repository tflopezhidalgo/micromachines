//
// Created by eliana on 27/10/19.
//

#ifndef MICROMACHINES_ADDOIL_CPP
#define MICROMACHINES_ADDOIL_CPP

#include <stdlib.h>
#include "entities/Car.h"
#include "World.h"
#include "Plugin.h"

#define MAX 100

class AddOil : public Plugin {
public:
    // agrega aceite en una posicion random del mapa
    void updateModel(World *world, std::vector<Car *> cars);

    float getPosition();
};


#endif //MICROMACHINES_ADDSTONE_CPP