#ifndef MICROMACHINES_PLUGINSFACTORY_H
#define MICROMACHINES_PLUGINSFACTORY_H

#include "Plugin.h"
#include <dlfcn.h>
#include <memory>

class PluginHandler {
private:
    void * handler = nullptr;
    PluginCreator creator = nullptr;
    static void resetDlError();
    static void checkDlError();
public:
    PluginHandler(const char* file);
    Plugin* create() const;
    ~PluginHandler();

};

#endif //MICROMACHINES_PLUGINSFACTORY_H
