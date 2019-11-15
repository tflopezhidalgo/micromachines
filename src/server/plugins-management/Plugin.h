//
// Created by eliana on 9/11/19.
//

#ifndef MICROMACHINES_PLUGIN_H
#define MICROMACHINES_PLUGIN_H

#include "EntitiesManager.h"
#include "../model/Car.h"

class Plugin {
public:
    Plugin() {}
    virtual void updateModel(
            EntitiesManager& entitiesManager,
            std::unordered_map<std::string, Car*> cars,
            RaceJudge& raceJudge) = 0;
    virtual ~Plugin() {}
};

using PluginCreator = Plugin *(*)();

#endif //MICROMACHINES_PLUGIN_H
