//
// Created by eliana on 7/11/19.
//

#include "PluginsReader.h"

#define DIRECTORY "./plugins"
#define EXTENSION "so"
#define CREATE "create"


PluginsReader::PluginsReader() {
    DIR* dir;
    struct dirent *file;

    dir = opendir(DIRECTORY);
    if (dir != NULL) {
        while ((file = readdir(dir)) != NULL) {
            std::string name = std::string(file->d_name);
            if(name.substr(name.find_last_of(".") + 1) == EXTENSION) {
                void* shared_lib = dlopen(file->d_name, RTLD_NOW);
                name = name.substr(0, name.size() - 3); // remove .so
                if (!shared_lib) {
                    continue;
                }
                files[name] = shared_lib;
            }
        }
    }
    closedir(dir);
}

void PluginsReader::applyPlugin(World* world, std::vector<Car*> cars) {
    for (auto it = files.begin(); it != files.end(); ++it) {
        Plugin* plug = (Plugin*)dlsym(it->second, CREATE);
        plug->updateModel(world, cars);
    }
}

PluginsReader::~PluginsReader() {
    for (auto it = files.begin(); it != files.end(); ++it) {
        dlclose(it->second);
    }
}
