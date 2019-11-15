//
// Created by eliana on 7/11/19.
//

#ifndef MICROMACHINES_PLUGINSMANAGER_H
#define MICROMACHINES_PLUGINSMANAGER_H

#include <dirent.h>
#include <cstdio>
#include <dlfcn.h>
#include <mutex>
#include <unordered_map>
#include <atomic>
#include <vector>
#include "Plugin.h"
#include "Thread.h"
#include "PluginHandler.h"

class PluginsManager : public Thread {
private:
    std::mutex mutex;
    std::unordered_map<std::string, Plugin*> plugins;
    std::vector<PluginHandler*> handlers;
    std::atomic<bool> finished;
public:
    PluginsManager();
    void readPluginsDirectory();
    void run() override;
    void stop();
    void applyRandomPlugin(std::unordered_map<std::string, Car*>&cars);
    ~PluginsManager();
};


#endif //MICROMACHINES_PLUGINSMANAGER_H
