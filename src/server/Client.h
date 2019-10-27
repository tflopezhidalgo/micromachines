//
// Created by leobellaera on 25/10/19.
//

#ifndef MICROMACHINES_CLIENT_H
#define MICROMACHINES_CLIENT_H

#include <string>
#include <atomic>
#include "ProtectedQueue.h"
#include "Proxy.h"
#include "Thread.h"

class Client : public Thread {
private:
    Proxy proxy;
    ProtectedQueue<std::string>& eventsQueue;
    std::atomic<bool> finished;
public:
    Client(Proxy proxy, ProtectedQueue<std::string> &eventsQueue);
    void sendMessage(std::string message);
    void run() override;
    void stop();
    ~Client() override;
};

#endif //MICROMACHINES_CLIENT_H
