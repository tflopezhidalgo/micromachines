//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_LOBBYCLIENTRECEPTIONIST_H
#define MICROMACHINES_LOBBYCLIENTRECEPTIONIST_H

#include "Thread.h"
#include "GamesAdministrator.h"
#include "Protocol.h"
#include <atomic>
#include "nlohmann/json.hpp"

class LobbyClientReceptionist : public Thread {
private:
    Protocol protocol;
    std::atomic<bool> dead;
    GamesAdministrator& gamesAdministrator;
    void createNewGame(nlohmann::json& initiationMsg);
    void joinGame(nlohmann::json& initiationMsg);
public:
    LobbyClientReceptionist(Socket& socket, GamesAdministrator& gamesAdministrator);
    bool isDead();
    void run() override;
    void stop();
    ~LobbyClientReceptionist() override;
};

#endif //MICROMACHINES_LOBBYCLIENTRECEPTIONIST_H
