//
// Created by leobellaera on 13/10/19.
//

#include "LobbyClientReceptionist.h"
#include "Client.h"
#include <string>

#define CREATE_MATCH "create"

LobbyClientReceptionist::LobbyClientReceptionist(Socket socket,
        MatchesAdministrator& matchesAdministrator) :
        proxy(std::move(socket)),
        finished(false),
        matchesAdministrator(matchesAdministrator) {}

void LobbyClientReceptionist::run() {
    //following code will be encapsulated by a client instance
    while (!finished) {
        std::string clientInitiationMessage = proxy.receiveMessage();
        nlohmann::json initiationMsg = nlohmann::json::parse(clientInitiationMessage);
        std::string mode = initiationMsg["mode"].get<std::string>();
        if (mode == CREATE_MATCH) {
            createNewMatch(initiationMsg);
        } else {  //client wants to join a match
            //mandar partidas disponibles al chaboncito
            joinMatch(initiationMsg);
        }
    }
}

void LobbyClientReceptionist::createNewMatch(nlohmann::json& initiationMsg) {
    std::string matchName = initiationMsg["matchName"].get<std::string>();
    std::string clientId = initiationMsg["clientId"].get<std::string>();
    std::string map = initiationMsg["map"].get<std::string>();
    int matchPlayersAmount = initiationMsg["playersAmount"].get<int>();
    int raceLaps = initiationMsg["raceLaps"].get<int>();
    finished = matchesAdministrator.createMatch(clientId,
            std::move(proxy), matchName,
            map, matchPlayersAmount, raceLaps);
}

void LobbyClientReceptionist::joinMatch(nlohmann::json& initiationMsg) {
    std::string matchName = initiationMsg["matchName"].get<std::string>();
    std::string clientId = initiationMsg["clientId"].get<std::string>();
    finished = matchesAdministrator.addClientToMatch(clientId,
            std::move(proxy), matchName);
}

bool LobbyClientReceptionist::isDead() {
    return finished;
}

void LobbyClientReceptionist::stop() {
    proxy.stop();
}

LobbyClientReceptionist::~LobbyClientReceptionist() {}
