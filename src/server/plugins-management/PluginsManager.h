//
// Created by eliana on 7/11/19.
//

#ifndef MICROMACHINES_PLUGINSMANAGER_H
#define MICROMACHINES_PLUGINSMANAGER_H

#include <dirent.h>
#include <cstdio>
#include <dlfcn.h>
#include <EntitiesManager.h>
#include "World.h"
#include "entities/Car.h"
#include "Plugin.h"

class PluginsManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Plugin>> plugins;
public:
    PluginsManager();
    void readPluginsDirectory();
    void apply(EntitiesManager& entitiesManager, std::unordered_map<std::string, Car*> cars, RaceJudge& raceJudge);
    ~PluginsManager();
};


#endif //MICROMACHINES_PLUGINSMANAGER_H
