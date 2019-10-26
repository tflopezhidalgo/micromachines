//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_MATCHESADMINISTRATOR_H
#define MICROMACHINES_MATCHESADMINISTRATOR_H

#include <map>
#include <string>
#include <mutex>
#include "Match.h"
#include "Proxy.h"

class MatchesAdministrator {
private:
    std::map<std::string, Match*> matches;
    std::map<std::string, float> config;
    std::mutex mutex;
public:
    MatchesAdministrator();
    bool createMatch(std::string& creatorNickname,
            Proxy clientProxy,
            std::string& matchName,
            std::string& mapName,
            int playersAmount,
            int raceLaps);
    bool addClientToMatch(std::string& clientNickname,
                          Proxy& clientProxy,
                          std::string& matchName);
    std::string getAvailableMatches();
    ~MatchesAdministrator();
};

#endif //MICROMACHINES_MATCHESADMINISTRATOR_H
