//
// Created by leobellaera on 13/11/19.
//

#ifndef MICROMACHINES_PLUGINSFACTORY_H
#define MICROMACHINES_PLUGINSFACTORY_H

#include "Plugin.h"
#include <dlfcn.h>

class PluginHandler {
private:
    void * handler = nullptr;
    PluginCreator creator = nullptr;
    static void resetDlError();
    static void checkDlError();
public:
    PluginHandler(const char* file);
    std::unique_ptr<Plugin> create() const;
    ~PluginHandler();

};

#endif //MICROMACHINES_PLUGINSFACTORY_H
