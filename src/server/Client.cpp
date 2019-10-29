//
// Created by leobellaera on 25/10/19.
//

#include <iostream>
#include "Client.h"

Client::Client(Proxy proxy, ProtectedQueue<Event>& eventsQueue) :
        proxy(std::move(proxy)),
        eventsQueue(eventsQueue),
        finished(false) {}

void Client::run() {
    while (!finished) {
        std::string eventDumped = proxy.receiveMessage();
        Event event(eventDumped);
        eventsQueue.push(std::move(event));
    }
    //To do handling socket exceptions
}

void Client::sendMessage(std::string& message) {
    proxy.sendMessage(message);
}

void Client::stop() {
    proxy.stop();
    finished = true;
}

Client::~Client() {
    proxy.stop(); //check this
}
