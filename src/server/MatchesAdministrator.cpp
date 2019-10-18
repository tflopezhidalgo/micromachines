//
// Created by leobellaera on 13/10/19.
//

#include "nlohmann/json.hpp"
#include "MatchesAdministrator.h"
#include "MatchesAdministratorException.h"

#define MATCH_EQUAL_NAMED "There is already a match with that name"
#define CLIENT_EQUAL_NAMED "There is already a client with that name"
#define FULL_MATCH "Match is already full"

MatchesAdministrator::MatchesAdministrator() {}

//en lugar de un creatorId podria ser un objeto Player

void MatchesAdministrator::createMatch(std::string& creatorId, std::string& matchName,
                                      std::string& mapName, int playersAmount, int raceLaps) {
    for (auto it = matches.begin() ; it != matches.end(); ++it) {
        if ((*it)->compareName(matchName)) {
            throw MatchesAdministratorException(MATCH_EQUAL_NAMED);
        }
    }
    //Match* match = new Match ... //habria que lanzar la partida si la cant de jugadores es 1
}

void MatchesAdministrator::joinClientToMatch(std::string& matchName, std::string& clientId) {
    //puede joinear, partida llena o ya hay un cliente con ese nombre
}

nlohmann::json getAvailablematches() {
    //to do
    /*"availablematches" : {
        "MatchName1": gameLaps
        "MatchName2": gameLaps
    }*/
}

MatchesAdministrator::~MatchesAdministrator() {
    //to do
}
