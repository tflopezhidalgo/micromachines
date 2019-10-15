//
// Created by leobellaera on 13/10/19.
//

#include "LobbyClientReceptionist.h"
#include "nlohmann/json.hpp"
#include <string>

#define CREATE_GAME "create"

LobbyClientReceptionist::LobbyClientReceptionist(Socket& socket, LobbyGamesOrganizer& gamesOrganizer) :
    protocol(socket),
    dead(false),
    gamesOrganizer(gamesOrganizer) {}

void LobbyClientReceptionist::run() {
    //following line will be encapsulated by a proxy instance.
    std::string clientInitiationMessage = protocol.receiveMessage();
    nlohmann::json initiationMsg = nlohmann::json::parse(clientInitiationMessage);
    std::string mode = initiationMsg["mode"].get<std::string>();
    std::string gameName = initiationMsg["gameName"].get<std::string>();
    std::string clientId = initiationMsg["clientId"].get<std::string>();

    if (mode == CREATE_GAME) {
        int gamePlayersAmount = initiationMsg["playersAmount"].get<int>();
        int raceLaps = initiationMsg["raceLaps"].get<int>();
        std::string map = initiationMsg["map"].get<std::string>();
        gamesOrganizer.createGame(clientId, gameName, map, gamePlayersAmount, raceLaps);
    } else {  //client wants to join a game
        dead = gamesOrganizer.joinClientToGame(gameName, clientId);
        while (!dead) {
            std::string availableGames = gamesOrganizer.getAvailableGames().dump();
            protocol.sendMessage(availableGames);
            nlohmann::json
        }
    }
    dead = true;
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
