#ifndef MICROMACHINES_EVENT_H
#define MICROMACHINES_EVENT_H

#include <string>
#include <nlohmann/json.hpp>

class Event {
private:
    std::string clientId;
    std::vector<char> actions;
public:
    Event(Event&& otherEvent) noexcept;

    //Useful to server
    explicit Event(std::string& dataDumped);
    std::vector<char>& getActions();
    std::string& getClientId();

    //Useful to client
    Event(std::string& clientId, std::vector<char> actions);
    std::string serialize();

    ~Event();
};

#endif
