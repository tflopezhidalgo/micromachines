//
// Created by eliana on 9/11/19.
//

#ifndef MICROMACHINES_PLUGIN_H
#define MICROMACHINES_PLUGIN_H

#include "../World.h"
#include "entities/Car.h"

class Plugin {
public:
    virtual void updateModel(World* world, std::vector<Car*> cars) = 0;
};


#endif //MICROMACHINES_PLUGIN_H
