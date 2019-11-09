//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_LOBBYCLIENTRECEPTIONIST_H
#define MICROMACHINES_LOBBYCLIENTRECEPTIONIST_H

#include "Thread.h"
#include "MatchesAdministrator.h"
#include "Proxy.h"
#include <atomic>
#include "nlohmann/json.hpp"

class LobbyClientReceptionist : public Thread {
private:
    Proxy proxy;
    std::atomic<bool> finished;
    MatchesAdministrator& matchesAdministrator;
    void createNewMatch(nlohmann::json& initiationMsg);
    void joinMatch(nlohmann::json& initiationMsg);
public:
    LobbyClientReceptionist(Socket socket, MatchesAdministrator& matchesAdministrator);
    bool isDead();
    void run() override;
    void stop();
    ~LobbyClientReceptionist();
};

#endif //MICROMACHINES_LOBBYCLIENTRECEPTIONIST_H
