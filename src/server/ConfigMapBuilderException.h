//
// Created by leobellaera on 28/10/19.
//

#ifndef MICROMACHINES_CONFIGMAPBUILDEREXCEPTION_H
#define MICROMACHINES_CONFIGMAPBUILDEREXCEPTION_H

#include <stdexcept>

class ConfigMapBuilderException : public std::runtime_error {
public:
    explicit ConfigMapBuilderException(const char* error) : runtime_error(error) {}
};

#endif //MICROMACHINES_CONFIGMAPBUILDEREXCEPTION_H
