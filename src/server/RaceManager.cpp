//
// Created by leobellaera on 4/11/19.
//

#include "RaceManager.h"
#include "ModelStatusSerializer.h"

#define X_POS_IDX 0
#define Y_POS_IDX 1
#define ANGLE_IDX 2

RaceManager::RaceManager(std::string& mapName, std::map<std::string,float> &config, int raceLaps) :
    stageBuilder(mapName, config),
    world(stageBuilder.buildWorld()),
    raceJudge(raceLaps),
    entitiesManager(world) {
    stageBuilder.addRaceSurface(world, floors, checkpoints, raceJudge);
    stageBuilder.addGrandstands(world, grandstands);
}

void RaceManager::addPlayer(std::string& nickname) {
    std::vector<float> startingPosition = stageBuilder.getStartingPosition();
    Car* car = world->addCar(nickname, startingPosition[X_POS_IDX],
            startingPosition[Y_POS_IDX], startingPosition[ANGLE_IDX]);
    cars.emplace(nickname, car);
    raceJudge.addCar(nickname);
}

bool RaceManager::raceFinished() {
    return false;
    //todo return raceJudge.raceFinished();
}

void RaceManager::updateModel(std::vector<Event> &events) {
    if (raceJudge.raceFinished()) {
        std::cout<<raceJudge.getWinnerId()<<std::endl;
    }

    entitiesManager.updateProjectilesStatus();
    entitiesManager.updateProjectilesFriction();

    for (int i = 0; i < grandstands.size(); i++) {
        grandstands[i]->throwProjectiles(entitiesManager);
    }

    std::unordered_map<std::string, bool> updatedCars;

    for (auto & event : events) {
        std::string& clientId = event.getClientId();
        std::vector<char> actions = event.getActions();
        cars.find(clientId)->second->updateMove(actions);
        updatedCars[clientId] = true;
    }

    std::vector<char> nullAction;
    for (auto & car : cars) {
        car.second->updateFriction();
        if (updatedCars.count(car.first) == 0) {
            car.second->updateMove(nullAction);
        }
    }

    world->step();
}

std::string RaceManager::getRaceStatus() {
    return std::move(ModelStatusSerializer::serialize(raceJudge, cars, entitiesManager.getEntities()));
}

RaceManager::~RaceManager() {
    for (auto it = cars.begin(); it != cars.end(); ++it) {
        delete it->second;
    }

    for (auto it = grandstands.begin(); it != grandstands.end(); ++it) {
        delete (*it);
    }

    for (auto it = floors.begin(); it != floors.end(); ++it) {
        delete (*it);
    }
    for (auto it = checkpoints.begin(); it != checkpoints.end(); ++it) {
        delete (*it);
    }

    delete world;
}
