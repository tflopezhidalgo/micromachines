//
// Created by leobellaera on 4/11/19.
//

#ifndef MICROMACHINES_RACEMANAGER_H
#define MICROMACHINES_RACEMANAGER_H


#include <string>
#include <unordered_map>
#include <entities/Car.h>
#include <entities/Floor.h>
#include <entities/Checkpoint.h>
#include "Client.h"
#include "World.h"
#include "RaceStageBuilder.h"

class RaceManager {
private:
    World* world;
    RaceStageBuilder stageBuilder;
    RaceJudge raceJudge;
    std::unordered_map<std::string, Car*> cars;
    std::unordered_map<int,Entity*> entities;
    std::vector<Floor*> floors;
    std::vector<Checkpoint*> checkpoints;
    int nextEntityId;
public:
    RaceManager(std::string& mapName, std::map<std::string,float> &config, int raceLaps);
    void addPlayer(std::string& nickname);
    bool raceFinished();
    void updateModel(std::vector<Event> &events);
    std::string getRaceStatus();
    ~RaceManager();
};


#endif //MICROMACHINES_RACEMANAGER_H
