//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_LOBBYACCEPTOR_H
#define MICROMACHINES_LOBBYACCEPTOR_H


#include "Thread.h"
#include "Socket.h"
#include "LobbyGamesManager.h"
#include <atomic>
#include <vector>

class LobbyAcceptor : public Thread {
private:
    std::atomic<bool> keepRunning;
    Socket socketAcceptor;
    std::vector<LobbyGamesManager*> workers;
    void deleteDeadLobbyWorkers();
public:
    LobbyAcceptor(int backlog, const char* port);
    void run() override;
    void stop();
    ~LobbyAcceptor() override;
};

#endif //MICROMACHINES_LOBBYACCEPTOR_H
