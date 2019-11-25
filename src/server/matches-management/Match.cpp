#include <unordered_set>
#include <nlohmann/json.hpp>
#include "SocketException.h"
#include "Match.h"
#include "Constants.h"

Match::Match(std::string& mapName, int playersAmount,
        int raceLaps, std::map<std::string,float> &config) :
        dead(false),
        matchStarted(false),
        mapName(mapName),
        raceLaps(raceLaps),
        playersAmount(playersAmount),
        timeStep(1000/config.find(FPS_KEY)->second),
        raceManager(mapName, config, raceLaps) {}

void Match::addClient(std::string nickname, Client* client) {
    raceManager.addPlayer(nickname);
    clients.emplace(nickname, client);
    if (clients.size() == playersAmount) {
        matchStarted = true;
        start();
    }
}

bool Match::hasStarted() {
    return matchStarted;
}

bool Match::nicknameIsAvailable(std::string& nickname) {
    return clients.count(nickname) != 1;
}

ProtectedQueue<Event>& Match::getEventsQueue() {
    return eventsQueue;
}

void Match::run() {
    sendMatchDataToClients();
    startCountdown();
    startClientsThread();

    while (!dead) {

        auto initial = std::chrono::high_resolution_clock::now();
        std::vector<Event> events = eventsQueue.emptyQueue();
        raceManager.updateModel(events);

        std::string modelStatus = std::move(raceManager.getRaceStatus());
        sendMessageToClients(modelStatus);

        if (raceManager.raceFinished()) {
            dead = true;
        }

        auto final = std::chrono::high_resolution_clock::now();
        auto loopDuration = std::chrono::duration_cast<std::chrono::milliseconds>(final - initial);
        long sleepTime = timeStep - loopDuration.count();
        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    }
}

void Match::sendMessageToClients(std::string& message) {
    auto clientsIt = clients.begin();
    while (clientsIt != clients.end()) {
        try {
            clientsIt->second->sendMessage(message);
            clientsIt++;
        } catch (const SocketException& e) {
            if (clientsIt->second->hasStarted()) {
                clientsIt->second->stop();
                clientsIt->second->join();
            }
            delete clientsIt->second;
            clientsIt = clients.erase(clientsIt);
        }
    }

    if (clients.empty()) {
        dead = true;
    }

}

void Match::startClientsThread() {
    for (auto & client : clients) {
        client.second->start();
    }
}

bool Match::finished() {
    return dead;
}

void Match::showIfAvailable(nlohmann::json& availableMatches, std::string& matchName) {
    if (hasStarted()) {
        return;
    }
    nlohmann::json matchInfo;
    matchInfo.push_back(mapName);
    matchInfo.push_back(raceLaps);
    matchInfo.push_back(playersAmount);
    availableMatches[matchName] = matchInfo;
}

void Match::stop() {
    dead = true;
}

void Match::startCountdown() {
    nlohmann::json ready;
    ready["message"] = READY;
    std::string readyDump = ready.dump();
    sendMessageToClients(readyDump);

    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    nlohmann::json set;
    set["message"] = SET;
    std::string setDump = set.dump();
    sendMessageToClients(setDump);

    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    nlohmann::json go;
    go["message"] = GO;
    std::string goDump = go.dump();
    sendMessageToClients(goDump);
}

void Match::sendMatchDataToClients() {
    std::string raceData = std::move(raceManager.getRaceData());
    sendMessageToClients(raceData);
}

Match::~Match() {
    for (auto & client : clients) {
        if (client.second->hasStarted()) {
            client.second->stop();
            client.second->join();
        }
        delete (client.second);
    }
}
