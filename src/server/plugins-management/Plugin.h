//
// Created by eliana on 9/11/19.
//

#ifndef MICROMACHINES_PLUGIN_H
#define MICROMACHINES_PLUGIN_H

#include <nlohmann/json.hpp>
#include "../../common/Identifiers.h"
#include "PluginsConstants.h"

class Plugin {
public:
    Plugin() {}

    void addEntities(nlohmann::json& requests,
            std::vector<std::tuple<EntityIdentifier, float, float>>& entitiesAdditions);

    void deleteEntities(nlohmann::json& requests,
            std::vector<std::tuple<int>>& entitiesDeletions);

    void addCarsModifications(nlohmann::json& requests,
            std::vector<std::tuple<std::string, float, int, int>>& carsModificationsData);

    virtual nlohmann::json updateModel(nlohmann::json& model) = 0;

    virtual ~Plugin() {}
};

using PluginCreator = Plugin *(*)();

#endif //MICROMACHINES_PLUGIN_H
