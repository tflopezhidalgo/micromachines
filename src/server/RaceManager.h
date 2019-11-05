//
// Created by leobellaera on 4/11/19.
//

#ifndef MICROMACHINES_RACEMANAGER_H
#define MICROMACHINES_RACEMANAGER_H


#include <string>
#include <unordered_map>
#include <entities/Car.h>
#include "Client.h"

class RaceManager {
private:
    std::unordered_map<std::string, Car*> cars;
    std::unordered_map<int,Entity*> entities;

};


#endif //MICROMACHINES_RACEMANAGER_H
