//
// Created by leobellaera on 29/10/19.
//

#ifndef MICROMACHINES_MODELSTATUSSERIALIZER_H
#define MICROMACHINES_MODELSTATUSSERIALIZER_H

#include <nlohmann/json.hpp>
#include "../model/Car.h"
#include "RaceJudge.h"
#include <unordered_map>
#include <string>

class ModelStatusSerializer {
public:
    static std::string serialize(
            RaceJudge& raceJudge,
            std::unordered_map<std::string, Car*>& cars,
            std::unordered_map<int, Entity*>& entities);
};

#endif //MICROMACHINES_MODELSTATUSSERIALIZER_H
