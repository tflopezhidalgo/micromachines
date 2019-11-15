//
// Created by eliana on 9/11/19.
//

#ifndef MICROMACHINES_PLUGIN_H
#define MICROMACHINES_PLUGIN_H

#include "../model/Car.h"
#include <unordered_map>
#include <string>

class Plugin {
public:
    Plugin() {}
    virtual void updateModel(std::unordered_map<std::string, Car*>& cars) = 0;
    virtual ~Plugin() {}
};

using PluginCreator = Plugin *(*)();

#endif //MICROMACHINES_PLUGIN_H
