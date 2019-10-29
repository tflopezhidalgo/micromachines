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

MatchesAdministrator::MatchesAdministrator(const char* configPath) :
    configMapBuilder(configPath) {}

bool MatchesAdministrator::createMatch(
        std::string& creatorNickname,
        Proxy clientProxy,
        std::string& matchName,
        std::string& mapName,
        int playersAmount,
        int raceLaps) {
    std::unique_lock<std::mutex> lck(mutex);
    nlohmann::json initiationResponse;

    if (matches.count(matchName) > 0) {
        initiationResponse["status"] = MATCH_EQUAL_NAMED;
        std::string response = initiationResponse.dump();
        clientProxy.sendMessage(response);
        return false;

    } else {
        initiationResponse["status"] = VALID;
        std::string response = initiationResponse.dump();
        clientProxy.sendMessage(response);
        auto match = new Match(mapName, playersAmount, raceLaps,
                configMapBuilder.getConfigMap());
        auto client = new Client(std::move(clientProxy), match->getEventsQueue());
        match->addPlayer(creatorNickname, client);
        matches.insert({matchName, match});
        return true;
    }
}

bool MatchesAdministrator::addClientToMatch(
        std::string& clientNickname,
        Proxy& clientProxy,
        std::string& matchName) {
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

//No lock till unique thread delete finished matches
void MatchesAdministrator::deleteFinishedMatches() {
    auto it = matches.begin();
    while (it != matches.end()) {
        auto matchIterator = it++;
        auto match = matchIterator->second;
        if (match->finished()) {
            match->stop();
            match->join();
            delete match;
            matches.erase(matchIterator);
        }
    }
}

std::string MatchesAdministrator::getAvailableMatches() {
    std::unique_lock<std::mutex> lck(mutex);
    nlohmann::json availableMatches;
    for (auto it = matches.begin(); it != matches.end(); ++it) {
        availableMatches[it->first] = it->second->getMatchInfo();
    }
    return std::move(availableMatches.dump());
}

MatchesAdministrator::~MatchesAdministrator() {
    for (auto it = matches.begin(); it != matches.end(); ++it) {
        it->second->stop();
        it->second->join();
        delete (it->second);
    }
}
