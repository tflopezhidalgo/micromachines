//
// Created by leobellaera on 13/10/19.
//

#include "nlohmann/json.hpp"
#include "LobbyGamesOrganizer.h"

LobbyGamesOrganizer::LobbyGamesOrganizer() {}

//en lugar de un creatorId podria ser un objeto Player

void createGame(std::string& creatorId, std::string& gameName,
                std::string& mapName, int playersAmount, int raceLaps) {
    //puede lanzar error debido a q ya hay una partida con ese nombre
}

void joinClientToGame(std::string& gameName, std::string& clientId) {
    //puede joinear, partida llena o ya hay un cliente con ese nombre
}

nlohmann::json getAvailableGames() {
    //to do
    /*"availableGames" : {
        "gameName1": gameLaps
        "gameName2": gameLaps
    }*/
}

LobbyGamesOrganizer::~LobbyGamesOrganizer() {
    //to do
}
