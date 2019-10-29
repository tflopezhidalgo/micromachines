//
// Created by leobellaera on 29/10/19.
//

#include "Event.h"

Event::Event(Event&& otherEvent) noexcept {
    this->clientId = otherEvent.clientId;
    this->action = otherEvent.action;
    otherEvent.clientId = "";
    otherEvent.action = '\0';
}

//Useful to server
Event::Event(std::string& dataDumped) {
    nlohmann::json data = nlohmann::json::parse(dataDumped);
    clientId = data["clientId"].get<std::string>();
    action = data["action"].get<char>();
}

std::string& Event::getClientId() {
    return clientId;
}

char Event::getAction() {
    return action;
}


//Useful to client
Event::Event(std::string& clientId, char action) :
        clientId(clientId),
        action(action) {}

std::string Event::serialize() {
    nlohmann::json data;
    data["action"] = action;
    data["clientId"] = clientId;
    std::string serialization = data.dump();
    return std::move(serialization);
}

Event::~Event() {}
