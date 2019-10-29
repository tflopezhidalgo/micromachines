//
// Created by leobellaera on 29/10/19.
//

#ifndef MICROMACHINES_MODELSERIALIZER_H
#define MICROMACHINES_MODELSERIALIZER_H

#include <nlohmann/json.hpp>
#include "entities/Car.h"
#include <unordered_map>
#include <string>

class ModelSerializer {
public:
    static std::string serialize(std::unordered_map<std::string, Car*>& cars);
};

#endif //MICROMACHINES_MODELSERIALIZER_H
