//
// Created by leobellaera on 25/10/19.
//

#include <iostream>
#include <SocketException.h>
#include "Client.h"

#define QUIT 'Q'

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
            std::vector<char> actions;
            actions.push_back(QUIT);
            Event event(clientId, actions);
            finished = true;
        }
    }
}

void Client::sendMessage(std::string& message) {
    proxy.sendMessage(message);
}

void Client::stop() {
    proxy.stop();
    finished = true;
}

Client::~Client() {
    proxy.stop(); //todo
}
