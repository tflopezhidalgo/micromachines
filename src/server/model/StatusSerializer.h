#ifndef MICROMACHINES_STATUSSERIALIZER_H
#define MICROMACHINES_STATUSSERIALIZER_H

#include <nlohmann/json.hpp>
#include "Car.h"
#include "RaceJudge.h"
#include <unordered_map>
#include <string>

class StatusSerializer {
public:
    static std::string serialize(
            RaceJudge& raceJudge,
            std::unordered_map<std::string, Car*>& cars,
            std::unordered_map<int, Entity*>& entities);
};

#endif //MICROMACHINES_STATUSSERIALIZER_H
