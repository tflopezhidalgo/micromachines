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
#include <entities/WorldBuilder.h>
#include "../common/Thread.h"
#include "Client.h"
#include "entities/Car.h"
#include "entities/World.h"

class Match : public Thread {
private:
    World* world;
    std::atomic<bool> matchStarted;
    std::atomic<bool> matchFinished;
    std::string mapName;
    ProtectedQueue<Event> eventsQueue;
    std::vector<Floor*> floors;
    std::unordered_map<std::string, Car*> cars;
    std::unordered_map<std::string, Client*> clients;
    std::unordered_map<int,Entity*> entities;
    int playersAmount;
    int raceLaps;
    long timeStep;
    int entitiesCounter;
    void startClientsThread();
    void updateModel(std::vector<Event> &events);
    void sendUpdateToClients();
public:
    Match(std::string& mapName, int playersAmount,
            int raceLaps, std::map<std::string, float> &config);
    void showIfAvailable(nlohmann::json& availableMatches, std::string& matchName);
    void addPlayer(std::string nickname, Client* client);
    bool hasStarted();
    bool finished();
    bool nicknameIsAvailable(std::string& nickname);
    ProtectedQueue<Event>& getEventsQueue();
    void run() override;
    void stop();
    ~Match();

};

#endif //MICROMACHINES_MATCH_H
