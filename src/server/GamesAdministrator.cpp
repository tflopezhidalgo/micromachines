//
// Created by leobellaera on 13/10/19.
//

#include "nlohmann/json.hpp"
#include "GamesAdministrator.h"
#include "GamesAdministratorException.h"

#define GAME_EQUAL_NAMED "There is already a game with that name"
#define CLIENT_EQUAL_NAMED "There is already a client with that name"
#define FULL_GAME "Game is already full"

GamesAdministrator::GamesAdministrator() {}

//en lugar de un creatorId podria ser un objeto Player

void GamesAdministrator::createGame(std::string& creatorId, std::string& gameName,
                std::string& mapName, int playersAmount, int raceLaps) {
    for (auto it = games.begin() ; it != games.end(); ++it) {
        if ((*it)->compareName(gameName)) {
            throw GamesAdministratorException(GAME_EQUAL_NAMED);
        }
    }
    //Game* game = new Game ... //habria que lanzar la partida si la cant de jugadores es 1
}

void GamesAdministrator::joinClientToGame(std::string& gameName, std::string& clientId) {
    //puede joinear, partida llena o ya hay un cliente con ese nombre
}

nlohmann::json getAvailableGames() {
    //to do
    /*"availableGames" : {
        "gameName1": gameLaps
        "gameName2": gameLaps
    }*/
}

GamesAdministrator::~GamesAdministrator() {
    //to do
}
