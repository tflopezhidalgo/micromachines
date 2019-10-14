//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_LOBBYCLIENTOPERATOR_H
#define MICROMACHINES_LOBBYCLIENTOPERATOR_H

#include "Thread.h"
#include "LobbyGamesManager.h"
#include <atomic>
#include <Socket.h>

class LobbyClientOperator : public Thread {
private:
    //std::atomic<bool> gameJoined;
    Socket clientSocket;
    LobbyGamesManager& gamesManager;
public:
    LobbyClientOperator(Socket& socket, LobbyGamesManager& gamesManager);
    void run() override;
    void stop();
    ~LobbyClientOperator() override;
};


#endif //MICROMACHINES_LOBBYCLIENTOPERATOR_H
