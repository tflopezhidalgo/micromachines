//
// Created by leobellaera on 15/10/19.
//

#ifndef MICROMACHINES_MATCH_H
#define MICROMACHINES_MATCH_H

#include "ProtectedQueue.h"
#include "Event.h"
#include <atomic>
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>
#include <RaceStageBuilder.h>
#include "../common/Thread.h"
#include "Client.h"
#include "entities/Car.h"
#include "World.h"
#include "RaceManager.h"

class Match : public Thread {
private:
    RaceManager raceManager;
    std::atomic<bool> matchStarted;
    std::string mapName;
    int playersAmount;
    int raceLaps;
    long timeStep;
    ProtectedQueue<Event> eventsQueue;
    std::unordered_map<std::string, Client*> clients;
    void startClientsThread();
    void sendUpdateToClients();
public:
    Match(std::string& mapName, int playersAmount,
            int raceLaps, std::map<std::string, float> &config);
    void showIfAvailable(nlohmann::json& availableMatches, std::string& matchName);
    void addClient(std::string nickname, Client* client);
    bool hasStarted();
    bool finished();
    bool nicknameIsAvailable(std::string& nickname);
    ProtectedQueue<Event>& getEventsQueue();
    void run() override;
    void stop();
    ~Match();

};

#endif //MICROMACHINES_MATCH_H
