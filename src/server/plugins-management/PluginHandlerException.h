#ifndef MICROMACHINES_PLUGINHANDLEREXCEPTION_H
#define MICROMACHINES_PLUGINHANDLEREXCEPTION_H

#include <stdexcept>

class PluginHandlerException : public std::runtime_error {
public:
    explicit PluginHandlerException(const char* error) : runtime_error(error) {}
};

#endif //MICROMACHINES_PLUGINHANDLEREXCEPTION_H
