//
// Created by leobellaera on 13/10/19.
//

#include "LobbyClientReceptionist.h"
#include "Constants.h"
#include "Client.h"
#include <string>

LobbyClientReceptionist::LobbyClientReceptionist(Socket socket,
        MatchesAdministrator& matchesAdministrator) :
        proxy(std::move(socket)),
        finished(false),
        matchesAdministrator(matchesAdministrator) {}

void LobbyClientReceptionist::run() {
    while (!finished) {
        std::string clientInitiationMessage = proxy.receiveMessage();
        nlohmann::json initiationMsg = nlohmann::json::parse(clientInitiationMessage);
        std::string mode = initiationMsg["mode"].get<std::string>();
        if (mode == CREATE_MATCH_MSG) {

            createNewMatch(initiationMsg);

        } else {  //client wants to join a match

            nlohmann::json availableMatches(matchesAdministrator.getAvailableMatches());
            std::string availableMatchesDump = availableMatches.dump();
            proxy.sendMessage(availableMatchesDump);

            std::string message = proxy.receiveMessage();
            nlohmann::json matchInfo = nlohmann::json::parse(message);

            joinMatch(matchInfo);

        }
    }
}

void LobbyClientReceptionist::createNewMatch(nlohmann::json& initiationMsg) {
    std::string matchName = initiationMsg["matchName"].get<std::string>();
    std::string clientId = initiationMsg["clientId"].get<std::string>();
    std::string map = initiationMsg["map"].get<std::string>();
    int matchPlayersAmount = initiationMsg["playersAmount"].get<int>();
    int raceLaps = initiationMsg["raceLaps"].get<int>();
    //if match created, proxy is moved to a Client instance
    finished = matchesAdministrator.createMatch(clientId,proxy,
            matchName,map, matchPlayersAmount, raceLaps);
}

void LobbyClientReceptionist::joinMatch(nlohmann::json& initiationMsg) {
    std::string matchName = initiationMsg["matchName"].get<std::string>();
    std::string clientId = initiationMsg["clientId"].get<std::string>();
    //if client added, proxy is moved to a Client instance
    finished = matchesAdministrator.addClientToMatch(clientId,
            proxy, matchName);
}

bool LobbyClientReceptionist::isDead() {
    return finished;
}

void LobbyClientReceptionist::stop() {
    finished = true;
    proxy.stop();
}

LobbyClientReceptionist::~LobbyClientReceptionist() {
    proxy.stop();
}
