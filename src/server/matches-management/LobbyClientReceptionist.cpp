#include "LobbyClientReceptionist.h"
#include "Constants.h"
#include "Client.h"
#include <string>
#include <SocketException.h>

#define UNKOWN_ERROR_MSG "Unknown error happened"

LobbyClientReceptionist::LobbyClientReceptionist(Socket socket,
        MatchesAdministrator& matchesAdministrator) :
        proxy(std::move(socket)),
        finished(false),
        matchesAdministrator(matchesAdministrator) {}

void LobbyClientReceptionist::run() {
    while (!finished) {
        try {
            std::string clientInitiationMessage = proxy.receiveMessage();
            nlohmann::json initiationMsg = nlohmann::json::parse(clientInitiationMessage);
            std::string mode = initiationMsg["mode"].get<std::string>();
            if (mode == CREATE_MATCH) {

                createNewMatch(initiationMsg);

            } else {  //client wants to join a match

                std::string availableMatches = std::move(matchesAdministrator.getAvailableMatches());
                proxy.sendMessage(availableMatches);

                std::string message = proxy.receiveMessage();
                nlohmann::json matchInfo = nlohmann::json::parse(message);

                joinMatch(matchInfo);

            }
        } catch (const SocketException& e) {
            std::cerr << e.what() << std::endl;
            finished = true;
            return;
        } catch (...) {
            std::cerr << UNKOWN_ERROR_MSG << std::endl;
            finished = true;
            return;
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
    proxy.stop();
}

LobbyClientReceptionist::~LobbyClientReceptionist() {
    proxy.stop();
}
