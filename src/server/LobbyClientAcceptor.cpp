//
// Created by leobellaera on 13/10/19.
//

#include "LobbyAcceptor.h"
#include "SocketException.h"

LobbyAcceptor::LobbyAcceptor(int backlog, const char* port) :
        socketAcceptor(backlog, port),
        keepRunning(true) {}

void LobbyAcceptor::run() {
    while (keepRunning) {
        Socket peerSocket = socketAcceptor.accept();
        LobbyGamesManager* worker = new LobbyGamesManager(std::move(peerSocket));
        worker->start();
        workers.push_back(worker);
        this->deleteDeadLobbyWorkers();
    }
}

void LobbyAcceptor::deleteDeadLobbyWorkers() {
    auto it = workers.begin();
    while (it != workers.end()) {
        if ((*it)->isDead()) {
            ++it;
        } else {
            (*it)->join();
            delete (*it);
            it = workers.erase(it);
        }
    }
}

void LobbyAcceptor::stop() {
    int size = workers.size();
    for (int i = 0; i < size; i++) {
        workers[i]->stop();
        workers[i]->join();
        delete workers[i];
    }
    socketAcceptor.close();
    keepRunning = false;
}

LobbyAcceptor::~LobbyAcceptor() {
    //delete all workers and close socket
}

