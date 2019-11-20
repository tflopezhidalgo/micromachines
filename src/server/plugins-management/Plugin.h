//
// Created by eliana on 9/11/19.
//

#ifndef MICROMACHINES_PLUGIN_H
#define MICROMACHINES_PLUGIN_H

#include <nlohmann/json.hpp>

class Plugin {
public:
    Plugin() {}
    virtual nlohmann::json updateModel(nlohmann::json& model) = 0;
    virtual ~Plugin() {}
};

using PluginCreator = Plugin *(*)();

#endif //MICROMACHINES_PLUGIN_H
