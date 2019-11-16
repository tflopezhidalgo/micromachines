//
// Created by leobellaera on 4/11/19.
//

#include "RaceManager.h"
#include "StatusSerializer.h"
#include "Constants.h"

#define X_POS_IDX 0
#define Y_POS_IDX 1
#define ANGLE_IDX 2

#define TIME_ELAPSE_PLUGINS 30
#define TIME_ELAPSE_GRANDSTANDS 15

RaceManager::RaceManager(std::string& mapName, std::map<std::string,float> &config, int raceLaps) :
    config(config),
    stageBuilder(mapName, config),
    world(std::move(stageBuilder.buildWorld(timedEvents))),
    raceJudge(raceLaps),
    entitiesManager(world),
    start(std::chrono::system_clock::now()){

    pluginsManager = new PluginsManager();
    pluginsManager->start();
    stageBuilder.addRaceSurface(world, tracks, grassTiles, checkpoints, raceJudge);
    stageBuilder.addGrandstands(world, grandstands);

}

void RaceManager::addPlayer(std::string& nickname) {
    std::vector<float> startingPosition = stageBuilder.getStartingPosition();
    Car* car = world.addCar(nickname, startingPosition[X_POS_IDX],
            startingPosition[Y_POS_IDX], startingPosition[ANGLE_IDX]);
    cars.emplace(nickname, car);
    raceJudge.addCar(nickname);
    entitiesManager.addEntity(MUD, 340.f, 0.f);
}

bool RaceManager::raceFinished() {
    return raceJudge.raceFinished();
}

void RaceManager::updateModel(std::vector<Event> &events) {
    entitiesManager.deleteDeadEntities();
    entitiesManager.updateProjectilesStatus();
    entitiesManager.updateProjectilesFriction();

    //activateGrandstands();

    updateTimedEvents();

    updateCars(events);

    applyPlugins();

    world.step();
}

void RaceManager::updateCars(std::vector<Event> &events) {
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
}

void RaceManager::activateGrandstands() {
    auto end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
            (end-start).count();

    if (elapsed_seconds > TIME_ELAPSE_GRANDSTANDS) {

        if (!grandstands.empty()) {

            int index = rand() % grandstands.size();
            auto grandstandsIt = std::next(std::begin(grandstands), index);
            (*grandstandsIt)->throwProjectiles(entitiesManager);

        }

        start = std::chrono::system_clock::now();

    }
}

void RaceManager::applyPlugins() {
    auto end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
            (end-start).count();
    if (elapsed_seconds > TIME_ELAPSE_PLUGINS) {
        pluginsManager->applyRandomPlugin(cars);
        start = std::chrono::system_clock::now();
    }
}

void RaceManager::updateTimedEvents() {
    auto it = timedEvents.begin();
    while (it != timedEvents.end()) {
        if (it->update(1.f / config.find(FPS_KEY)->second)) {
            it = timedEvents.erase(it);
        } else {
            it++;
        }
    }
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
