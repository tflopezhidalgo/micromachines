//
// Created by leobellaera on 4/11/19.
//

#include "RaceManager.h"
#include "StatusSerializer.h"
#include "Constants.h"

#define X_POS_IDX 0
#define Y_POS_IDX 1
#define ANGLE_IDX 2

RaceManager::RaceManager(std::string& mapName, std::map<std::string,float> &config, int raceLaps) :
    config(config),
    stageBuilder(mapName, config),
    world(std::move(stageBuilder.buildWorld())),
    raceJudge(raceLaps),
    entitiesManager(world) {
    pluginsManager = new PluginsManager();
    pluginsManager->start();
    stageBuilder.addRaceSurface(world, tracks, grassTiles, checkpoints, raceJudge);
    //stageBuilder.addGrandstands(world, grandstands);
}

void RaceManager::addPlayer(std::string& nickname) {
    std::vector<float> startingPosition = stageBuilder.getStartingPosition();
    Car* car = world.addCar(nickname, startingPosition[X_POS_IDX],
            startingPosition[Y_POS_IDX], startingPosition[ANGLE_IDX], timedEvents);
    cars.emplace(nickname, car);
    raceJudge.addCar(nickname);
}

bool RaceManager::raceFinished() {
    return raceJudge.raceFinished();
}

void RaceManager::updateModel(std::vector<Event> &events) {
    entitiesManager.deleteDeadEntities();
    entitiesManager.updateProjectilesStatus();
    entitiesManager.updateProjectilesFriction();

    for (auto & grandstand : grandstands) {
        grandstand->throwProjectiles(entitiesManager);
    }

    pluginsManager->applyPlugins();

    auto it = timedEvents.begin();
    while (it != timedEvents.end()) {
        if (it->update(1.f / config.find(FPS_KEY)->second)) {
            it = timedEvents.erase(it);
        } else {
            it++;
        }
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

    world.step();
}

std::string RaceManager::getRaceStatus() {
    return std::move(StatusSerializer::serialize(raceJudge, cars, entitiesManager.getEntities()));
}

RaceManager::~RaceManager() {

    pluginsManager->stop();
    pluginsManager->join();
    delete pluginsManager;

    for (auto & car : cars) {
        delete car.second;
    }
    for (auto & grandstand : grandstands) {
        delete grandstand;
    }
    for (auto & track : tracks) {
        delete track;
    }
    for (auto & grassTile : grassTiles) {
        delete grassTile;
    }
    for (auto & checkpoint : checkpoints) {
        delete checkpoint;
    }
}
