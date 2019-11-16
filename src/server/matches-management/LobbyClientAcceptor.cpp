#include "LobbyClientAcceptor.h"
#include "SocketException.h"
#include "LobbyClientReceptionist.h"

LobbyClientAcceptor::LobbyClientAcceptor(int backlog,
        const char* port,
        MatchesAdministrator& matchesAdministrator) :
        socketAcceptor(backlog, port),
        matchesAdministrator(matchesAdministrator),
        keepRunning(true) {}

void LobbyClientAcceptor::run() {
    while (keepRunning) {
        try {
            Socket peerSocket = socketAcceptor.accept();
            auto receptionist = new LobbyClientReceptionist(
                    std::move(peerSocket),
                    matchesAdministrator);
            receptionist->start();
            receptionists.push_back(receptionist);
            deleteDeadReceptionists();
        } catch (const SocketException& e) {
            return;
        }
    }
}

void LobbyClientAcceptor::deleteDeadReceptionists() {
    auto it = receptionists.begin();
    while (it != receptionists.end()) {
        if ((*it)->isDead()) {
            (*it)->join();
            delete (*it);
            it = receptionists.erase(it);
        } else {
            ++it;
        }
    }
}

void LobbyClientAcceptor::stop() {
    keepRunning = false;
    int size = receptionists.size();
    for (int i = 0; i < size; i++) {
        receptionists[i]->stop();
        receptionists[i]->join();
        delete receptionists[i];
    }
    socketAcceptor.close();
}

LobbyClientAcceptor::~LobbyClientAcceptor() {}
