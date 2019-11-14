//
// Created by leobellaera on 13/11/19.
//

#include "PluginHandler.h"
#include "PluginHandlerException.h"

PluginHandler::PluginHandler(const char* file) {
    handler = dlopen(file, RTLD_NOW);
    if (!handler) {
        throw PluginHandlerException(dlerror());
    }
    resetDlError();
    creator = reinterpret_cast<PluginCreator>(dlsym(handler, "create"));
    checkDlError();
}

void PluginHandler::resetDlError() {
    dlerror();
}

void PluginHandler::checkDlError() {
    const char * dlsymError = dlerror();
    if (dlsymError) {
        throw PluginHandlerException(dlsymError);
    }
}

std::unique_ptr<Plugin> PluginHandler::create() const {
    return std::unique_ptr<Plugin>(creator());
}

PluginHandler::~PluginHandler() {
    if (handler) {
        dlclose(handler);
    }
}
