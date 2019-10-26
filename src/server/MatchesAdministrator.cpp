//
// Created by leobellaera on 13/10/19.
//

#include "ProtectedQueue.h"
#include "nlohmann/json.hpp"
#include "Proxy.h"
#include "MatchesAdministrator.h"
#include "Client.h"

#define VALID 0
#define MATCH_HAS_STARTED 1
#define MATCH_EQUAL_NAMED 2
#define CLIENT_EQUAL_NAMED 3

//IMPORTANTE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*al construir la clase matchesAdministrator deberia leerse el archivo config y pasarselo a las partidas
 por referencia cuando se crean! ----> new Match(matchname, ..., config) */

MatchesAdministrator::MatchesAdministrator() {
    config.emplace("maxForwardSpeed", 500.f);
    config.emplace("maxBackwardSpeed", -100.f);
    config.emplace("maxDriveForce", 200.f);
    config.emplace("maxLateralImpulse", 40.f);
    config.emplace("framesPerSecond", 60.f);
}

bool MatchesAdministrator::createMatch(std::string& creatorNickname,
        Proxy clientProxy,
        std::string& matchName,
        std::string& mapName,
        int playersAmount,
        int raceLaps) {
    std::unique_lock<std::mutex> lck(mutex);
    nlohmann::json initiationResponse;

    if (matches.find(matchName) == matches.end()) {

        initiationResponse["status"] = MATCH_EQUAL_NAMED;
        std::string response = initiationResponse.dump();
        clientProxy.sendMessage(response);
        return false;

    } else {
        initiationResponse["status"] = VALID;
        std::string response = initiationResponse.dump();
        clientProxy.sendMessage(response);

        auto match = new Match(mapName, playersAmount, raceLaps, config);
        auto client = new Client(std::move(clientProxy), match->getEventsQueue());
        match->addPlayer(creatorNickname, client); //addClient() { if matchIsFull() match.run()
        matches.insert({matchName, match});
        return true;
    }
}

bool MatchesAdministrator::addClientToMatch(std::string& clientNickname,
        Proxy clientProxy, std::string& matchName) {
    std::unique_lock<std::mutex> lck(mutex);
    nlohmann::json initiationResponse;

    Match* match = matches.find(matchName)->second;

    if (match->hasStarted()) {

        initiationResponse["status"] = MATCH_HAS_STARTED;
        std::string response = initiationResponse.dump();
        clientProxy.sendMessage(response);
        return false;

    } else if (!match->nicknameIsAvailable(clientNickname)) {

        initiationResponse["status"] = CLIENT_EQUAL_NAMED;
        std::string response = initiationResponse.dump();
        clientProxy.sendMessage(response);
        return false;

    } else {

        initiationResponse["status"] = VALID;
        std::string response = initiationResponse.dump();
        clientProxy.sendMessage(response);
        auto client = new Client(std::move(clientProxy), match->getEventsQueue());
        match->addPlayer(clientNickname, client);
        matches.insert({matchName, match});
        return true;

    }
}

std::string MatchesAdministrator::getAvailableMatches() {
    //HACEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEER!!!!!!!!!!!!!!!!!!!
    /*std::unique_lock<std::mutex> lck(mutex);
    nlohmann::json availableMatches;
    //availableMatches.
    "availablematches" : {
        "MatchName1": map, raceLaps, playersAmount
        "MatchName2": map, ...
    }*/
    return "harcodeo";
}

MatchesAdministrator::~MatchesAdministrator() {
    //to do
}
