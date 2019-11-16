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

Plugin* PluginHandler::create() const {
    return creator();
}

PluginHandler::~PluginHandler() {
    if (handler) {
        dlclose(handler);
    }
}
