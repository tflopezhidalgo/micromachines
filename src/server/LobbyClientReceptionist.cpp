//
// Created by leobellaera on 13/10/19.
//

#include "LobbyClientReceptionist.h"
#include "MatchesAdministratorException.h"
#include <string>

#define CREATE_MATCH "create"
#define VALID_INIT_MSG "valid"

LobbyClientReceptionist::LobbyClientReceptionist(Socket& socket, MatchesAdministrator& matchesAdministrator) :
    protocol(socket),
    dead(false),
    matchesAdministrator(matchesAdministrator) {}

void LobbyClientReceptionist::run() {
    //following code will be encapsulated by a client instance
    while (!dead) {
        std::string clientInitiationMessage = protocol.receiveMessage();
        nlohmann::json initiationMsg = nlohmann::json::parse(clientInitiationMessage);
        std::string mode = initiationMsg["mode"].get<std::string>();
        if (mode == CREATE_MATCH) {
            createNewMatch(initiationMsg);
        } else {  //client wants to join a match
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

    nlohmann::json initiationResponse;
    try {
        matchesAdministrator.createMatch(clientId, matchName,
                map, matchPlayersAmount, raceLaps);
        initiationResponse["status"] = VALID_INIT_MSG;
        dead = true;
    } catch (const MatchesAdministratorException& e) {
        initiationResponse["status"] = e.what();
    }
    std::string responseDumped = initiationResponse.dump();
    protocol.sendMessage(responseDumped);
}

void LobbyClientReceptionist::joinMatch(nlohmann::json& initiationMsg) {
    std::string matchName = initiationMsg["matchName"].get<std::string>();
    std::string clientId = initiationMsg["clientId"].get<std::string>();
    nlohmann::json initiationResponse;
    try {
        matchesAdministrator.joinClientToMatch(matchName, clientId);
        initiationResponse["status"] = VALID_INIT_MSG;
        dead = true;
    } catch (const MatchesAdministratorException& e) {
        initiationResponse["status"] = e.what();
    }
    std::string responseDumped = initiationResponse.dump();
    protocol.sendMessage(responseDumped);
}

bool LobbyClientReceptionist::isDead() {
    return dead;
}

void LobbyClientReceptionist::stop() {
    //proxy.stop()
}

LobbyClientReceptionist::~LobbyClientReceptionist() {
    //to do!!
}
