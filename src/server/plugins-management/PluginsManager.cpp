#include "PluginsManager.h"
#include "PluginHandler.h"
#include "PluginHandlerException.h"

#define DIRECTORY "../src/server/plugins-management/plugins/libs/"
#define EXTENSION "so"

PluginsManager::PluginsManager():
    finished(false) {}

void PluginsManager::run() {
    while (!finished) {
        readPluginsDirectory();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void PluginsManager::readPluginsDirectory() {
    std::unique_lock<std::mutex> lck(mutex);
    DIR* dir;
    struct dirent* file;
    dir = opendir(DIRECTORY);
    if (dir != nullptr) {
        while ((file = readdir(dir)) != nullptr) {
            std::string fileName = std::string(file->d_name);
            if(fileName.substr(fileName.find_last_of('.') + 1) == EXTENSION
                    && plugins.count(fileName) == 0) {
                try {
                    std::string path = DIRECTORY + fileName;
                    auto handler = new PluginHandler(path.c_str());
                    Plugin* plugin = handler->create();
                    handlers.push_back(handler);
                    plugins.emplace(fileName, plugin);
                } catch (const PluginHandlerException& e) {
                    continue;
                }
            }
        }
        closedir(dir);
    }
}

nlohmann::json PluginsManager::applyRandomPlugin(nlohmann::json& model) {
    std::unique_lock<std::mutex> lck(mutex);
    if (!plugins.empty()) {
        int index = rand() % plugins.size();
        auto pluginsIt = std::next(std::begin(plugins), index);
        return std::move(pluginsIt->second->updateModel(model));
    } else {
        nlohmann::json null;
        return std::move(null);
    }
}

void PluginsManager::stop() {
    finished = true;
}

PluginsManager::~PluginsManager() {
    for (auto & plugin : plugins) {
        delete plugin.second;
    }
    for (auto & handler : handlers) {
        delete handler;
    }
}
