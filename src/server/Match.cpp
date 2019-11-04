//
// Created by leobellaera on 15/10/19.
//

#include <unordered_set>
#include <nlohmann/json.hpp>
#include "Match.h"
#include "ModelSerializer.h"
#include "Macros.h"

Match::Match(std::string& mapName, int playersAmount,
        int raceLaps, std::map<std::string,float> &config) :
        matchStarted(false),
        matchFinished(false),
        mapName(mapName),
        raceLaps(raceLaps),
        playersAmount(playersAmount),
        timeStep(1000/config.find(FPS_KEY)->second),
        entitiesCounter(0) {
        //todo nombre del mapa harcodeado
        std::string name = "simple";
        WorldBuilder worldBuilder(name, config);
        world = worldBuilder.build(floors);

}

void Match::addPlayer(std::string nickname, Client* client) {
    //we need to see where to put every car
    Car* car = world->addCar(-100.f, 0.f, 180.f);
    //todo harcodeado
    Entity* entity = world->addStone(100, 100);
    entities.emplace(entitiesCounter, entity);
    //*****************************
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
        long sleepTime = timeStep - loopDuration.count();
        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    }
}

void Match::updateModel(std::vector<Event> &events) {
    for (auto & car : cars) {
        car.second->updateFriction();
    }

    for (auto & event : events) {
        std::string& clientId = event.getClientId();
        std::vector<char> actions = event.getActions();

        if (actions[0] == QUIT_ACTION) {
            //todo
        }
        cars.find(clientId)->second->updateMove(actions);
    }
    world->step();
}

void Match::sendUpdateToClients() {
    //model serializer will receive all unordered_maps as arguments
    std::string modelSerialized = ModelSerializer::serialize(cars, entities);
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

void Match::showIfAvailable(nlohmann::json& availableMatches, std::string& matchName) {
    if (hasStarted()) {
        return;
    }
    nlohmann::json matchInfo;
    matchInfo.push_back(mapName);
    matchInfo.push_back(raceLaps);
    matchInfo.push_back(playersAmount);
    availableMatches[matchName] = matchInfo;
}

void Match::stop() {
    //todo
}

Match::~Match() {
    //todo
}
