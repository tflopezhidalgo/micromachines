#include <SocketException.h>
#include "Client.h"


Client::Client(Proxy proxy, std::string clientId, ProtectedQueue<Event>& eventsQueue) :
        proxy(std::move(proxy)),
        clientId(clientId),
        eventsQueue(eventsQueue),
        finished(false) {}

void Client::run() {
    while (!finished) {
        try {
            std::string eventDumped = proxy.receiveMessage();
            Event event(eventDumped);
            eventsQueue.push(std::move(event));
        } catch (const SocketException& e) {
            finished = true;
        }
    }
}

void Client::sendMessage(std::string& message) {
    proxy.sendMessage(message);
}

void Client::stop() {
    finished = true;
    proxy.stop();
}

Client::~Client() {
    proxy.stop();
}
