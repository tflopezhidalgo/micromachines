//
// Created by leobellaera on 29/10/19.
//

#include "Event.h"

Event::Event(Event&& otherEvent) noexcept {
    this->clientId = std::move(otherEvent.clientId);
    this->actions = std::move(otherEvent.actions);
}

//Useful to server
Event::Event(std::string& dataDumped) {
    nlohmann::json data = nlohmann::json::parse(dataDumped);
    clientId = std::move(data["clientId"].get<std::string>());
    actions = std::move(data["actions"].get<std::vector<char>>());
}

std::string& Event::getClientId() {
    return clientId;
}

std::vector<char>& Event::getActions() {
    return actions;
}

//Useful to client
Event::Event(std::string& clientId, std::vector<char> actions) :
        clientId(clientId),
        actions(std::move(actions)) {}

std::string Event::serialize() {
    nlohmann::json data;
    data["actions"] = actions;
    data["clientId"] = clientId;
    std::string serialization = data.dump();
    return std::move(serialization);
}

Event::~Event() {}
