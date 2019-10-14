//
// Created by leobellaera on 13/10/19.
//

#include "LobbyClientOperator.h"
#include <string>
#include <iostream>

#define CREATE_GAME '1'
#define JOIN_GAME '2'

LobbyClientOperator::LobbyClientOperator(Socket& socket, LobbyGamesManager& gamesManager) :
    clientSocket(std::move(socket)),
    /*gameJoined(false),*/
    gamesManager(gamesManager) {}


void LobbyClientOperator::run() {
    /*while (!gameJoined) {*/
    //std::string clientMessage = protocol.receiveMessage();
    char mode = '\0';
    std::cin >> mode;
    if (mode == CREATE_GAME) {
        gamesManager.createGame(5, "example", 3);
        gamesManager.getAvailableGames();
    }
    } else if (mode == JOIN_GAME) {
        gamesManager.joinClientToGame("example", "leonardo");
        gamesManager
    }
}

void LobbyClientOperator::stop() {
    //to do
}

LobbyClientOperator::~LobbyClientOperator() {
    //to do
}
