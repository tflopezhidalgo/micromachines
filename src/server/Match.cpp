//
// Created by leobellaera on 15/10/19.
//

#include <unordered_set>
#include <nlohmann/json.hpp>
#include "Match.h"
#include "ModelSerializer.h"

#define FPS "framesPerSecond"
#define NO_ACTION '0'
#define QUIT_ACTION 'Q'

Match::Match(std::string mapName, int playersAmount,
        int raceLaps, std::map<std::string,float> &config) :
    matchStarted(false),
    matchFinished(false),
    mapName(mapName),
    raceLaps(raceLaps),
    playersAmount(playersAmount),
    framesPerSecond(config.find(FPS)->second),
    world(500, 500, config) {
    /* make world from map...
       World* world = worldBuilder.build(mapName, world, config);
       (build is a static method that builds map tracks)
     */
}

void Match::addPlayer(std::string nickname, Client* client) {
    //we need to see where to put every car
    Car* car = world.addCar(100.f, 100.f);
    cars.emplace(nickname, car);
    clients.emplace(nickname, client);
    if (cars.size() == playersAmount) {
        matchStarted = true;
        start();
    }
}

bool Match::hasStarted() {
    return matchStarted;
}

bool Match::nicknameIsAvailable(std::string& nickname) {
    return clients.count(nickname) != 1;
}

ProtectedQueue<Event>& Match::getEventsQueue() {
    return eventsQueue;
}

void Match::run() {
    //ready, set, go
    startClientsThread();
    while (!matchFinished) {
        auto initial = std::chrono::high_resolution_clock::now();

        std::vector<Event> events = eventsQueue.emptyQueue();
        updateModel(events);
        sendUpdateToClients();

        auto final = std::chrono::high_resolution_clock::now();
        auto loopDuration = std::chrono::duration_cast<std::chrono::milliseconds>(final - initial);
        long sleepTime = (1 / framesPerSecond) * 1000 - loopDuration.count();
        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    }
}

void Match::updateModel(std::vector<Event> &events) {
    std::unordered_set<std::string> updatedCars;

    for (auto & event : events) {
        std::string& clientId = event.getClientId();
        std::vector<char> actions = event.getActions();

        for (char action : actions) {
            if (action == QUIT_ACTION) {
                //todo
            }
            cars.find(clientId)->second->update(action);
        }
        updatedCars.emplace(std::move(clientId));
    }

    //friction update to remaining cars
    for (auto & car : cars) {
        auto setIter = updatedCars.find(car.first);
        if (setIter == updatedCars.end()) {
            car.second->update(NO_ACTION);
        }
    }
    world.step();
}

void Match::sendUpdateToClients() {
    //model serializer will receive all unordered_maps as arguments
    std::string modelSerialized = ModelSerializer::serialize(cars);
    for (auto & client : clients) {
        client.second->sendMessage(modelSerialized);
    }
}

void Match::startClientsThread() {
    for (auto & client : clients) {
        client.second->start();
    }
}

bool Match::finished() {
    //no lock?
    return matchFinished;
}

nlohmann::json Match::getMatchInfo() {
    nlohmann::json matchInfo;
    if (hasStarted()) {
        return matchInfo;
    }
    matchInfo.push_back(mapName);
    matchInfo.push_back(raceLaps);
    matchInfo.push_back(playersAmount);
    return matchInfo;
}

void Match::stop() {
    //todo
}

Match::~Match() {
    //todo
}
