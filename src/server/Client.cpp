//
// Created by leobellaera on 25/10/19.
//

#include "Client.h"

Client::Client(Proxy proxy, ProtectedQueue<std::string>& eventsQueue) :
    proxy(std::move(proxy)),
    eventsQueue(eventsQueue),
    finished(false) {}

void Client::run() {
    while (!finished) {
        std::string action = proxy.receiveMessage();
        eventsQueue.push(action);
    }
    //handle errors like socket exceptions (client disconnected)
}

void Client::sendMessage(std::string message) {
    proxy.sendMessage(message);
}

void Client::stop() {
    proxy.stop();
    finished = true;
}

Client::~Client() {
    proxy.stop(); //check this
}
