#ifndef MICROMACHINES_CLIENT_H
#define MICROMACHINES_CLIENT_H

#include <string>
#include <atomic>
#include "Event.h"
#include "ProtectedQueue.h"
#include "Proxy.h"
#include "Thread.h"

class Client : public Thread {
private:
    Proxy proxy;
    std::string clientId;
    ProtectedQueue<Event>& eventsQueue;
    std::atomic<bool> finished;
    std::atomic<bool> started;
public:
    Client(Proxy proxy, std::string clientId, ProtectedQueue<Event> &eventsQueue);
    void sendMessage(std::string& message);
    void run() override;
    void stop();
    bool hasStarted();
    ~Client() override;
};

#endif //MICROMACHINES_CLIENT_H
