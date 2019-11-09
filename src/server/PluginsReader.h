//
// Created by eliana on 7/11/19.
//

#ifndef MICROMACHINES_PLUGINSREADER_H
#define MICROMACHINES_PLUGINSREADER_H

#include <dirent.h>
#include <cstdio>
#include <iostream>
#include <map>
#include <dlfcn.h>
#include "World.h"
#include "entities/Car.h"
#include "plugins/Plugin.h"

class PluginsReader {
private:
    std::map<std::string, void*> files;
public:
    PluginsReader(World* world, std::vector<Car*> cars);

    void applyPlugin();

    ~PluginsReader();
};


#endif //MICROMACHINES_PLUGINSREADER_H
