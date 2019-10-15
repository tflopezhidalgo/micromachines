//
// Created by leobellaera on 13/10/19.
//

#include "LobbyClientReceptionist.h"
#include "../../nlohmann/json.hpp"
#include <string>
#include <iostream> // debugging

LobbyClientReceptionist::LobbyClientReceptionist(Socket& socket/*, LobbyGamesManager& gamesManager*/) :
    protocol(socket),
    dead(false) {}

void LobbyClientReceptionist::run() {
    //while (!gameJoined) {
    //following line will be encapsulated by a clientProxy instance.
    std::string clientInitiationMessage = protocol.receiveMessage();
    nlohmann::json initiationMsg = nlohmann::json::parse(clientInitiationMessage);
    std::string mode = initiationMsg["mode"].get<std::string>();
    if (mode == "join") {
        std::cout<<"Join mode!\n";
        //gamesManager.createGame(5, "example", 3);
        //gamesManager.getAvailableGames();
    } else if (mode == "create") {
        std::cout<<"Create mode!\n";
        //gamesManager.joinClientToGame("example", "leonardo");
        //gamesManager
    }
    dead = true; //prev check if client couldn't join a game
}

bool LobbyClientReceptionist::isDead() {
    return dead;
}

void LobbyClientReceptionist::stop() {
    //to do!!
}

LobbyClientReceptionist::~LobbyClientReceptionist() {
    //to do!!
}
