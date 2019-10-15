//
// Created by leobellaera on 13/10/19.
//

#include "LobbyClientReceptionist.h"
#include "GamesAdministratorException.h"
#include <string>

#define CREATE_GAME "create"
#define VALID_INIT_MSG "valid"

LobbyClientReceptionist::LobbyClientReceptionist(Socket& socket, GamesAdministrator& gamesAdministrator) :
    protocol(socket),
    dead(false),
    gamesAdministrator(gamesAdministrator) {}

void LobbyClientReceptionist::run() {
    //following code will be encapsulated by a client instance
    while (!dead) {
        std::string clientInitiationMessage = protocol.receiveMessage();
        nlohmann::json initiationMsg = nlohmann::json::parse(clientInitiationMessage);
        std::string mode = initiationMsg["mode"].get<std::string>();
        if (mode == CREATE_GAME) {
            createNewGame(initiationMsg);
        } else {  //client wants to join a game
            joinGame(initiationMsg);
        }
    }
}

void LobbyClientReceptionist::createNewGame(nlohmann::json& initiationMsg) {
    std::string gameName = initiationMsg["gameName"].get<std::string>();
    std::string clientId = initiationMsg["clientId"].get<std::string>();
    std::string map = initiationMsg["map"].get<std::string>();
    int gamePlayersAmount = initiationMsg["playersAmount"].get<int>();
    int raceLaps = initiationMsg["raceLaps"].get<int>();

    nlohmann::json initiationResponse;
    try {
        gamesAdministrator.createGame(clientId, gameName,
                map, gamePlayersAmount, raceLaps);
        initiationResponse["status"] = VALID_INIT_MSG;
        dead = true;
    } catch (const GamesAdministratorException& e) {
        initiationResponse["status"] = e.what();
    }
    std::string responseDumped = initiationResponse.dump();
    protocol.sendMessage(responseDumped);
}

void LobbyClientReceptionist::joinGame(nlohmann::json& initiationMsg) {
    std::string gameName = initiationMsg["gameName"].get<std::string>();
    std::string clientId = initiationMsg["clientId"].get<std::string>();
    nlohmann::json initiationResponse;
    try {
        gamesAdministrator.joinClientToGame(gameName, clientId);
        initiationResponse["status"] = VALID_INIT_MSG;
        dead = true;
    } catch (const GamesAdministratorException& e) {
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
