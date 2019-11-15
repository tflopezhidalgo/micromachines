//
// Created by leobellaera on 4/11/19.
//

#ifndef MICROMACHINES_RACEMANAGER_H
#define MICROMACHINES_RACEMANAGER_H


#include <string>
#include <unordered_map>
#include "Car.h"
#include "Track.h"
#include "Checkpoint.h"
#include "Client.h"
#include "World.h"
#include "RaceStageBuilder.h"
#include "EntitiesManager.h"
#include "TimedEvent.h"

class RaceManager {
private:
    std::map<std::string,float> &config;
    std::vector<TimedEvent> timedEvents;
    RaceStageBuilder stageBuilder;
    World world;
    RaceJudge raceJudge;
    EntitiesManager entitiesManager;
    std::unordered_map<std::string, Car*> cars;
    std::vector<Grandstand*> grandstands;
    std::vector<Track*> tracks;
    std::vector<Grass*> grassTiles;
    std::vector<Checkpoint*> checkpoints;
public:
    RaceManager(std::string& mapName, std::map<std::string,float> &config, int raceLaps);

    void addPlayer(std::string& nickname);

    bool raceFinished();

    void updateModel(std::vector<Event> &events);

    std::string getRaceStatus();

    ~RaceManager();
};


#endif //MICROMACHINES_RACEMANAGER_H
