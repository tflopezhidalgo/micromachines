//
// Created by leobellaera on 15/10/19.
//

#include "Match.h"

Match::Match(std::string& mapName, int playersAmount, int raceLaps) :
    matchStarted(false),
    matchFinished(false),
    playersAmount(playersAmount),
    raceLaps(raceLaps) {
    //cargar mapa
}

bool Match::addPlayer(std::string nickname, Client* client) {
    return true;
}

bool Match::hasStarted() {
    return matchStarted;
}

bool Match::nicknameIsAvailable(std::string& nickname) {
    return true;
}

ProtectedQueue<std::string>& Match::getEventsQueue() {
    return eventsQueue;
}

void Match::run() {

}

void Match::stop() {

}

Match::~Match() {}
