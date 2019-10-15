//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_LOBBYCLIENTRECEPTIONIST_H
#define MICROMACHINES_LOBBYCLIENTRECEPTIONIST_H

#include "Thread.h"
#include "LobbyGamesOrganizer.h"
#include "Protocol.h"
#include <atomic>

class LobbyClientReceptionist : public Thread {
private:
    Protocol protocol;
    std::atomic<bool> dead;
    LobbyGamesOrganizer& gamesOrganizer;
public:
    LobbyClientReceptionist(Socket& socket, LobbyGamesOrganizer& gamesOrganizer);
    bool isDead();
    void run() override;
    void stop();
    ~LobbyClientReceptionist() override;
};

#endif //MICROMACHINES_LOBBYCLIENTRECEPTIONIST_H
