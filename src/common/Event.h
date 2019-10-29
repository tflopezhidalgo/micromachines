//
// Created by leobellaera on 29/10/19.
//

#ifndef MICROMACHINES_EVENT_H
#define MICROMACHINES_EVENT_H

#include <string>
#include <nlohmann/json.hpp>

class Event {
private:
    std::string clientId;
    char action;
public:
    Event(Event&& otherEvent) noexcept;

    //Useful to server
    explicit Event(std::string& dataDumped);
    char getAction();
    std::string& getClientId();

    //Useful to client
    Event(std::string& clientId, char action);
    std::string serialize();

    ~Event();
};

#endif //MICROMACHINES_EVENT_H
