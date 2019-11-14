//
// Created by eliana on 7/11/19.
//

#include "PluginsManager.h"
#include "PluginHandler.h"
#include "PluginHandlerException.h"

#define DIRECTORY "./plugins"
#define EXTENSION "so"

PluginsManager::PluginsManager() {}

void PluginsManager::readPluginsDirectory() {
    DIR* dir;
    struct dirent* file;

    dir = opendir(DIRECTORY);
    if (dir != nullptr) {
        while ((file = readdir(dir)) != nullptr) {
            std::string name = std::string(file->d_name);
            if(name.substr(name.find_last_of(".") + 1) == EXTENSION && plugins.count(name) != 0) {
                try {
                    PluginHandler handler(file->d_name);
                    plugins.emplace(name, handler.create());
                } catch (const PluginHandlerException& e) {
                    continue;
                }
            }
        }
        closedir(dir);
    }
}

void PluginsManager::apply(EntitiesManager& entitiesManager,
        std::unordered_map<std::string, Car*> cars, RaceJudge& raceJudge) {
    for (auto & plugin : plugins) {
        plugin.second->updateModel(entitiesManager, cars, raceJudge);
    }
}

PluginsManager::~PluginsManager() {}
