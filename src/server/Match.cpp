//
// Created by leobellaera on 15/10/19.
//

#include <zconf.h> //borrar
#include "nlohmann/json.hpp"
#include "Match.h"

Match::Match(std::string& mapName, int playersAmount, int raceLaps, std::map<std::string,float> &config) :
    matchStarted(false),
    matchFinished(false),
    playersAmount(playersAmount),
    raceLaps(raceLaps),
    world(500, 500, config) {
    //cargar mapa
}

void Match::addPlayer(std::string nickname, Client* client) {
    Car* car = world.addCar(100.f, 100.f);
    cars.emplace(nickname, car);
    clients.emplace(nickname, client);
    if (cars.size() == playersAmount) {
        start();
    }
    //ver que hacer con el argumento client
}

bool Match::hasStarted() {
    return matchStarted;
}

bool Match::nicknameIsAvailable(std::string nickname) {
    return true;
}

ProtectedQueue<std::string>& Match::getEventsQueue() {
    return eventsQueue;
}

void Match::run() {
    int contador = 0;
    while (contador < 100) {
        usleep(1000);
        cars.find("tomas")->second->move(1);
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
        contador++;
    }
}

void Match::stop() {

}

Match::~Match() {}
