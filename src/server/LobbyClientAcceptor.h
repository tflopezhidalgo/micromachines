//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_LOBBYCLIENTACCEPTOR_H
#define MICROMACHINES_LOBBYCLIENTACCEPTOR_H


#include "Thread.h"
#include "Socket.h"
#include "LobbyGamesManager.h"
#include "LobbyClientReceptionist.h"
#include <atomic>
#include <vector>

class LobbyClientAcceptor : public Thread {
private:
    std::atomic<bool> keepRunning;
    Socket socketAcceptor;
    std::vector<LobbyClientReceptionist*> receptionists;
    void deleteDeadReceptionists();
public:
    LobbyClientAcceptor(int backlog, const char* port);
    void run() override;
    void stop();
    ~LobbyClientAcceptor() override;
};

#endif //MICROMACHINES_LOBBYCLIENTACCEPTOR_H
