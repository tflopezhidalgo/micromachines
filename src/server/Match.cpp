//
// Created by leobellaera on 15/10/19.
//

#include <zconf.h> //borrar
#include <iostream>
#include "nlohmann/json.hpp"
#include "Match.h"

Match::Match(std::string mapName, std::string matchName,
        int playersAmount, int raceLaps, std::map<std::string,float> &config) :
    matchStarted(false),
    matchFinished(false),
    matchName(matchName),
    mapName(mapName),
    playersAmount(playersAmount),
    raceLaps(raceLaps),
    world(500, 500, config) {
    //make world from map
}

void Match::addPlayer(std::string nickname, Client* client) {
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

ProtectedQueue<std::string>& Match::getEventsQueue() {
    return eventsQueue;
}

void Match::run() {
    while (!matchFinished) {
        usleep(100);

        std::string aux = clients.find("tomas")->second->receiveMessage();
        nlohmann::json action = nlohmann::json::parse(aux);

        char accionDeTomas = action["action"].get<char>();
        std::cout<<accionDeTomas<<std::endl;
        cars.find("tomas")->second->move(accionDeTomas);

        world.step();
        b2Vec2 position = cars.find("tomas")->second->getPosition();
        nlohmann::json response;
        response["x"] = int(position.x);
        response["y"] = int(position.y);
        clients.find("tomas")->second->sendMessage(response.dump());
        /*while (!eventsQueue.isEmpty()) {
            std::string action = eventsQueue.pop();
            nlohmann::json
        }*/
    }
}

nlohmann::json Match::getMatchInfo() {
    nlohmann::json matchInfo;
    if (hasStarted()) {
        return matchInfo;
    }
    matchInfo[matchName] = {mapName, raceLaps, playersAmount};
    return matchInfo;
}


void Match::stop() {
    //to do
}

Match::~Match() {}
