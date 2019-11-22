//
// Created by leobellaera on 20/11/19.
//

#ifndef MICROMACHINES_PLUGINREQUESTSPROCESSOR_H
#define MICROMACHINES_PLUGINREQUESTSPROCESSOR_H

#include <nlohmann/json.hpp>
#include "EntitiesManager.h"

class PluginRequestsProcessor {

private:
    EntitiesManager& entitiesManager;
    std::unordered_map<std::string, Car*>& cars;
public:
    PluginRequestsProcessor(
            EntitiesManager& entitiesManager,
            std::unordered_map<std::string, Car*>& cars
            );

    void process(nlohmann::json& pluginRequests);

    ~PluginRequestsProcessor();

};

#endif //MICROMACHINES_PLUGINREQUESTSPROCESSOR_H
