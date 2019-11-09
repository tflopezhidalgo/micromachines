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

class PluginsReader {
private:
    std::map<std::string, void*> files;
public:
    PluginsReader();

    void applyPlugin();

    ~PluginsReader();
};


#endif //MICROMACHINES_PLUGINSREADER_H
