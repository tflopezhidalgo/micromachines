//
// Created by eliana on 20/10/19.
//

#ifndef PLUGINS_INCREASESPEED_H
#define PLUGINS_INCREASESPEED_H

#include "World.h"
#include "entities/Car.h"
#include "Plugin.h"

#define NEWFORDWARDSPEED 150

class IncreaseSpeed : public Plugin {
public:
    void updateModel(World* world, std::vector<Car*> cars) override;
};


#endif //PLUGINS_INCREASESPEED_H
