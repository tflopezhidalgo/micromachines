#include "RaceManager.h"
#include "StatusSerializer.h"
#include "Constants.h"

#define X_POS_IDX 0
#define Y_POS_IDX 1
#define ANGLE_IDX 2

RaceManager::RaceManager(std::string& mapName, std::map<std::string,float> &config, int raceLaps) :
        config(config),
        stageBuilder(mapName, config),
        world(std::move(stageBuilder.buildWorld(timedEvents))),
        raceJudge(raceLaps),
        entitiesManager(world),
        pluginRequestsProcessor(entitiesManager, cars),
        grandstandsTimeStart(std::chrono::system_clock::now()),
        pluginsTimeStart(std::chrono::system_clock::now()) {

    pluginsManager.start();
    stageBuilder.addRaceSurface(world, tracks, grassTiles, checkpoints, raceJudge);
    stageBuilder.addGrandstands(world, grandstands, timedEvents);

}

void RaceManager::addPlayer(std::string& nickname) {
    std::vector<float> startingPosition = stageBuilder.getStartingPosition();
    Car* car = world.addCar(nickname, startingPosition[X_POS_IDX],
            startingPosition[Y_POS_IDX]);
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

    activateGrandstands();

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
            (end - grandstandsTimeStart).count();

    if (elapsed_seconds > TIME_ELAPSE_GRANDSTANDS) {

        if (!grandstands.empty()) {

            int index = rand() % grandstands.size();
            auto grandstandsIt = std::next(std::begin(grandstands), index);
            (*grandstandsIt)->throwProjectiles(entitiesManager);

        }

        grandstandsTimeStart = std::chrono::system_clock::now();

    }
}

void RaceManager::applyPlugins() {
    auto end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
            (end - pluginsTimeStart).count();
    if (elapsed_seconds > TIME_ELAPSE_PLUGINS) {
        nlohmann::json modelSerialization =
                std::move(StatusSerializer::getPluginsModelSerialization(
                        raceJudge, cars, entitiesManager.getEntities()));
        nlohmann::json requests = std::move(pluginsManager.applyRandomPlugin(modelSerialization));
        pluginRequestsProcessor.process(requests);
        pluginsTimeStart = std::chrono::system_clock::now();
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
    return std::move(StatusSerializer::getClientsModelSerialization(
            raceJudge, cars, entitiesManager.getEntities()));
}

std::string RaceManager::getRaceData() {
    std::string status = StatusSerializer::getClientsModelSerialization(
            raceJudge, cars, entitiesManager.getEntities());
    nlohmann::json raceStatus = nlohmann::json::parse(status);
    raceStatus.erase("entitiesData");
    raceStatus.erase("carsArrivalOrder");
    nlohmann::json raceData = stageBuilder.getRaceData();

    raceData["carsData"] = raceStatus["carsData"];
    return std::move(raceData.dump());
}

RaceManager::~RaceManager() {

    pluginsManager.stop();
    pluginsManager.join();

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
