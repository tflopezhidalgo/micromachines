//
// Created by leobellaera on 4/11/19.
//

#include "RaceManager.h"
#include "ModelSerializer.h"

#define X_POS_IDX 0
#define Y_POS_IDX 1
#define ANGLE_IDX 2

RaceManager::RaceManager(std::string& mapName, std::map<std::string,float> &config, int raceLaps) :
    stageBuilder(mapName, config),
    raceJudge(raceLaps) {
    world = stageBuilder.buildWorld();
    entitiesManager.setWorld(world);
    stageBuilder.addRaceSurface(world, floors, checkpoints, raceJudge);

}

void RaceManager::addPlayer(std::string& nickname) {
    std::vector<float> startingPosition = stageBuilder.getStartingPosition();
    Car* car = world->addCar(nickname, startingPosition[X_POS_IDX],
            startingPosition[Y_POS_IDX], startingPosition[ANGLE_IDX]);
    cars.emplace(nickname, car);
    raceJudge.addCar(nickname);
}

bool RaceManager::raceFinished() {
    return raceJudge.raceFinished();
}

void RaceManager::updateModel(std::vector<Event> &events) {
    if (raceJudge.raceFinished()) {
        //todo
    }

    entitiesManager.updateProjectilesFriction();

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
    entitiesManager.updateProjectilesStatus();
}

std::string RaceManager::getRaceStatus() {
    return std::move(ModelSerializer::serialize(cars, entitiesManager.getEntities()));
}

RaceManager::~RaceManager() {
 //todo
}