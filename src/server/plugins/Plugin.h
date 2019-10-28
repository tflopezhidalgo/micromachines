//
// Created by eliana on 20/10/19.
//

#ifndef MICROMACHINES_PLUGIN_H
#define MICROMACHINES_PLUGIN_H

#include <string>
#include "entities/Car.h"
#include "entities/World.h"

enum PluginType {
    INCREASE_VELOCITY,
    DECREASE_VELOCITY
};

class Plugin {
public:
    virtual void updateModel(std::vector<Car*> cars, World* world) = 0;
};


#endif //MICROMACHINES_PLUGIN_H
